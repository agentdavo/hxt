// Gmsh - Copyright (C) 1997-2008 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to <gmsh@geuz.org>.
//
// Contributor(s):
//   Jonathan Lambrechts
//

#include <list>
#include <math.h>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

#ifdef HAVE_MATH_EVAL
#include "matheval.h"
#endif
#ifdef HAVE_ANN
#include "ANN/ANN.h"
#endif

#include "Context.h"
#include "Field.h"
#include "GeoInterpolation.h"
#include "GModel.h"
#include "GmshMessage.h"
#include "Numeric.h"

#if !defined(HAVE_NO_POST)
#include "OctreePost.h"
#include "PViewDataList.h"
#include "MVertex.h"
#endif

extern Context_T CTX;

class FieldOptionDouble : public FieldOption
{
 public:
  double &val;
  FieldOptionType get_type(){ return FIELD_OPTION_DOUBLE; }
  FieldOptionDouble(double &_val, std::string _help, bool *_status=0)
    : FieldOption(_help, _status), val(_val){}
  double numerical_value() const { return val; }
  void numerical_value(double v){ modified(); val = v; }
  void get_text_representation(std::string &v_str)
  {
    std::ostringstream sstream;
    sstream.precision(16);
    sstream << val;
    v_str = sstream.str();
  }
};

class FieldOptionInt : public FieldOption
{
 public:
  int &val;
  FieldOptionType get_type(){ return FIELD_OPTION_INT; }
  FieldOptionInt(int &_val, std::string _help, bool *_status=0) 
    : FieldOption(_help, _status), val(_val){}
  double numerical_value() const { return val; }
  void numerical_value(double v){ modified(); val = (int)v; }
  void get_text_representation(std::string & v_str)
  {
    std::ostringstream sstream;
    sstream << val;
    v_str = sstream.str();
  }
};

class FieldOptionList : public FieldOption
{
 public:
  std::list<int> &val;
  FieldOptionType get_type(){ return FIELD_OPTION_LIST; }
  FieldOptionList(std::list<int> &_val, std::string _help, bool *_status=0) 
    : FieldOption(_help, _status), val(_val) {}
  std::list<int> &list(){ modified(); return val; }
  const std::list<int>& list() const { return val; }
  void get_text_representation(std::string & v_str)
  {
    std::ostringstream sstream;
    sstream << "{";
    for(std::list<int>::iterator it = val.begin(); it != val.end(); it++) {
      if(it != val.begin())
        sstream << ", ";
      sstream << *it;
    }
    sstream << "}";
    v_str = sstream.str();
  }
};

class FieldOptionString : public FieldOption
{
 public:
  std::string & val;
  virtual FieldOptionType get_type(){ return FIELD_OPTION_STRING; }
  FieldOptionString(std::string &_val, std::string _help, bool *_status=0)
    : FieldOption(_help, _status), val(_val) {}
  std::string &string() { modified(); return val; }
  const std::string &string() const { return val; }
  void get_text_representation(std::string &v_str)
  {
    std::ostringstream sstream;
    sstream << "\"" << val << "\"";
    v_str = sstream.str();
  }
};

class FieldOptionPath : public FieldOptionString
{
 public:
  virtual FieldOptionType get_type(){ return FIELD_OPTION_PATH; }
  FieldOptionPath(std::string &_val, std::string _help, bool *_status=0)
    : FieldOptionString(_val, _help, _status) {}
};

class FieldOptionBool : public FieldOption
{
 public:
  bool & val;
  FieldOptionType get_type(){ return FIELD_OPTION_BOOL; }
  FieldOptionBool(bool & _val, std::string _help, bool *_status=0)
    : FieldOption(_help, _status), val(_val) {}
  double numerical_value() const { return val; }
  void numerical_value(double v){ modified(); val = v; }
  void get_text_representation(std::string & v_str)
  {
    std::ostringstream sstream;
    sstream << val;
    v_str = sstream.str();
  }
};

void FieldManager::reset()
{
  for(std::map<int, Field *>::iterator it = begin(); it != end(); it++) {
    delete it->second;
  }
  clear();
}

Field *FieldManager::get(int id)
{
  iterator it = find(id);
  if(it == end()) return NULL;
  return it->second;
}

Field *FieldManager::new_field(int id, std::string type_name)
{
  if(find(id) != end()) {
    Msg::Error("Field id %i is already defined.", id);
    return 0;
  }
  if(map_type_name.find(type_name) == map_type_name.end()) {
    Msg::Error("Unknown field type \"%s\".", type_name.c_str());
    return 0;
  }
  Field *f = (*map_type_name[type_name]) ();
  if(!f)
    return 0;
  f->id = id;
  (*this)[id] = f;
  return f;
}

int FieldManager::new_id()
{
  int i = 0;
  iterator it = begin();
  while(1) {
    i++;
    while(it != end() && it->first < i)
      it++;
    if(it == end() || it->first != i)
      break;
  }
  return std::max(i, 1);
}

int FieldManager::max_id()
{
  if(!empty())
    return rbegin()->first;
  else
    return 0;
}

void FieldManager::delete_field(int id)
{
  iterator it = find(id);
  if(it == end()) {
    Msg::Error("Cannot delete field id %i, it does not exist.", id);
    return;
  }
  delete it->second;
  erase(it);
}

// StructuredField
class StructuredField : public Field
{
  double o[3], d[3];
  int n[3];
  double *data;
  bool error_status;
  bool text_format;
  std::string file_name;
 public:
  StructuredField()
  {
    options["FileName"] = new FieldOptionPath(file_name, "Name of the input file", 
					      &update_needed);
    text_format = false;
    options["TextFormat"] = new FieldOptionBool(text_format, "True for ASCII input "
						"files, false for binary files\n"
						"(4 bite signed integers for n, "
						"double precision floating points "
						"for v, D and O)",
						&update_needed);
    data = 0;
  }
  std::string get_description()
  {
    return "Linearly interpolate between data provided on a 3D rectangular structured grid. "
      "The format of the input file is : \n"
      "Ox Oy Oz \n"
      "Dx Dy Dz \n"
      "nx ny nz \n"
      "v(0,0,0) v(0,0,1) v(0,0,2) ... \n"
      "v(0,1,0) v(0,1,1) v(0,1,2) ... \n"
      "v(0,2,0) v(0,2,1) v(0,2,2) ... \n"
      "...      ...      ... \n"
      "v(1,0,0) ...      ... \n"
      "where O are the coordinates of the first node, "
      "D are the distances between nodes in each direction, "
      "n are the numbers of nodes in each directions, "
      "and v are the values on each nodes.";
  }
  const char *get_name()
  {
    return "Structured";
  }
  virtual ~StructuredField()
  {
    if(data) delete[]data;
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    if(update_needed) {
      error_status = false;
      try {
        std::ifstream input;
        if(text_format)
          input.open(file_name.c_str());
        else
          input.open(file_name.c_str(),std::ios::binary);
        if(!input.is_open())
          throw(1);
        input.
          exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::
                     ifstream::badbit);
        if(!text_format) {
          input.read((char *)o, 3 * sizeof(double));
          input.read((char *)d, 3 * sizeof(double));
          input.read((char *)n, 3 * sizeof(int));
          int nt = n[0] * n[1] * n[2];
          if(data)
            delete[]data;
          data = new double[nt];
          input.read((char *)data, nt * sizeof(double));
        }
        else {
          input >> o[0] >> o[1] >> o[2] >> d[0] >> d[1] >> d[2] >> n[0] >>
            n[1] >> n[2];
          int nt = n[0] * n[1] * n[2];
          if(data)
            delete[]data;
          data = new double[nt];
          for(int i = 0; i < nt; i++)
            input >> data[i];
        }
        input.close();
      }
      catch(...) {
        error_status = true;
        Msg::Error("Field %i : error reading file %s", this->id, file_name.c_str());
      }
      update_needed = false;
    }
    if(error_status)
      return MAX_LC;
    //tri-linear
    int id[2][3];
    double xi[3];
    double xyz[3] = { x, y, z };
    for(int i = 0; i < 3; i++) {
      id[0][i] = (int)floor((xyz[i] - o[i]) / d[i]);
      id[1][i] = id[0][i] + 1;
      id[0][i] = std::max(std::min(id[0][i], n[i] - 1), 0);
      id[1][i] = std::max(std::min(id[1][i], n[i] - 1), 0);
      xi[i] = (xyz[i] - (o[i] + id[0][i] * d[i])) / d[i];
      xi[i] = std::max(std::min(xi[i], 1.), 0.);
    }
    double v = 0;
    for(int i = 0; i < 2; i++)
      for(int j = 0; j < 2; j++)
        for(int k = 0; k < 2; k++) {
          v += data[id[i][0] * n[1] * n[2] + id[j][1] * n[2] + id[k][2]]
            * (i * xi[0] + (1 - i) * (1 - xi[0]))
            * (j * xi[1] + (1 - j) * (1 - xi[1]))
            * (k * xi[2] + (1 - k) * (1 - xi[2]));
        }
    return v;
  }
};

class UTMField : public Field
{
  int field_id, zone;
  double a, b, n, n2, n3, n4, n5, e, e2, e1, e12, e13, e14, J1, J2, J3, J4,
    Ap, Bp, Cp, Dp, Ep, e4, e6, ep, ep2, ep4, k0, mu_fact;
 public:
  std::string get_description()
  {
    return "Evaluate Field[IField] in Universal Transverse Mercator coordinates. "
      "The formulas for the coordinates transformation are taken from "
      "http://www.uwgb.edu/dutchs/UsefulData/UTMFormulas.HTM\n";
  }
  UTMField()
  {
    field_id = 1;
    zone = 0;
    options["IField"] = new FieldOptionInt(field_id, "Index of the field to evaluate");
    options["Zone"] = new FieldOptionInt(zone, "Zone of the UTM projection");
    a = 6378137;                /* Equatorial Radius */
    b = 6356752.3142;           /* Rayon Polar Radius */
    /* see http://www.uwgb.edu/dutchs/UsefulData/UTMFormulas.HTM */
    n = (a - b) / (a + b);
    n2 = n * n;
    n3 = n * n * n;
    n4 = n * n * n * n;
    n5 = n * n * n * n * n;
    e = sqrt(1 - b * b / a / a);
    e2 = e * e;
    e1 = (1 - sqrt(1 - e2)) / (1 + sqrt(1 - e2));
    e12 = e1 * e1;
    e13 = e1 * e1 * e1;
    e14 = e1 * e1 * e1 * e1;
    J1 = (3 * e1 / 2 - 27 * e13 / 32);
    J2 = (21 * e12 / 16 - 55 * e14 / 32);
    J3 = 151 * e13 / 96;
    J4 = 1097 * e14 / 512;
    Ap = a * (1 - n + (5. / 4.) * (n2 - n3) + (81. / 64.) * (n4 - n5));
    Bp = -3 * a * n / 2 * (1 - n + (7. / 8.) * (n2 - n3) +
                           (55. / 64.) * (n4 - n5));
    Cp = 14 * a * n2 / 16 * (1 - n + (3. / 4) * (n2 - n3));
    Dp = -35 * a * n3 / 48 * (1 - n + 11. / 16. * (n2 - n3));
    Ep = +315 * a * n4 / 51 * (1 - n);
    e4 = e2 * e2;
    e6 = e2 * e2 * e2;
    ep = e * a / b;
    ep2 = ep * ep;
    ep4 = ep2 * ep2;
    k0 = 0.9996;
    mu_fact = 1 / (k0 * a * (1 - e2 / 4 - 3 * e4 / 64 - 5 * e6 / 256));
  }
  const char *get_name()
  {
    return "UTM";
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    double r = sqrt(x * x + y * y + z * z);
    double lon = atan2(y, x);
    double lat = asin(z / r);
    double meridionalarc = Ap * lat + Bp * sin(2 * lat)
      + Cp * sin(4 * lat) + Dp * sin(6 * lat) + Ep;
    double slat = sin(lat);
    double clat = cos(lat);
    double slat2 = slat * slat;
    double clat2 = clat * clat;
    double clat3 = clat2 * clat;
    double clat4 = clat3 * clat;
    double tlat2 = slat2 / clat2;
    double nu = a / sqrt(1 - e * e * slat2);
    double p = lon - ((zone - 0.5) / 30 - 1) * M_PI;
    double p2 = p * p;
    double p3 = p * p2;
    double p4 = p2 * p2;
    double utm_x =
      k0 * nu * clat * p + (k0 * nu * clat3 / 6) * (1 - tlat2 +
                                                    ep2 * clat2) * p3 + 5e5;
    double utm_y =
      meridionalarc * k0 + k0 * nu * slat * clat / 2 * p2 +
      k0 * nu * slat * clat3 / 24 * (5 - tlat2 + 9 * ep2 * clat2 +
                                     4 * ep4 * clat4) * p4;
    Field *field = GModel::current()->getFields()->get(field_id);
    if(!field) return MAX_LC;
    return (*field)(utm_x, utm_y, 0);
  }
};

class LonLatField : public Field
{
  int field_id;
 public:
  std::string get_description()
  {
    return "Evaluate Field[IField] in geographic coordinates (longitude,latitude). \n"
      "F = Field[IField](arctan(y/x),arcsin(z/sqrt(x^2+y^2+z^2))";
  }
  LonLatField()
  {
    field_id = 1;
    options["IField"] = new FieldOptionInt(field_id, "Index of the field to evaluate.");
  }
  const char *get_name()
  {
    return "LonLat";
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    Field *field = GModel::current()->getFields()->get(field_id);
    if(!field) return MAX_LC;
    return (*field)(atan2(y, x), asin(z / sqrt(x * x + y * y + z * z)), 0);
  }
};

class BoxField : public Field
{
  double v_in, v_out, x_min, x_max, y_min, y_max, z_min, z_max;
 public:
  std::string get_description()
  {
    return "The value of this field is VIn inside the box, VOut outside the box. \n"
      "The box is given by Xmin<=x<=XMax && YMin<=y<=YMax && ZMin<=z<=ZMax";
  }
  BoxField()
  {
    v_in = v_out = x_min = x_max = y_min = y_max = z_min = z_max = 0;
    options["VIn"] = new FieldOptionDouble(v_in, "Value inside the box");
    options["VOut"] = new FieldOptionDouble(v_out, "Value outside the box");
    options["XMin"] = new FieldOptionDouble(x_min, "Minimum X coordinate of the box");
    options["XMax"] = new FieldOptionDouble(x_max, "Maximum X coordinate of the box");
    options["YMin"] = new FieldOptionDouble(y_min, "Minimum Y coordinate of the box");
    options["YMax"] = new FieldOptionDouble(y_max, "Maximum Y coordinate of the box");
    options["ZMin"] = new FieldOptionDouble(z_min, "Minimum Z coordinate of the box");
    options["ZMax"] = new FieldOptionDouble(z_max, "Maximum Z coordinate of the box");
  }
  const char *get_name()
  {
    return "Box";
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    return (x <= x_max && x >= x_min && y <= y_max && y >= y_min && z <= z_max
            && z >= z_min) ? v_in : v_out;
  }
};

class ThresholdField : public Field
{
  int iField;
  double dmin, dmax, lcmin, lcmax;
  bool sigmoid, stopAtDistMax;
 public:
  const char *get_name()
  {
    return "Threshold";
  }
  std::string get_description()
  {
    return "F = LCMin if Field[IField] <= DistMin\n"
      "F = LCMax if Field[IField] >= DistMax\n"
      "F = Interpolation between LcMin and LcMax if DistMin<Field[IField]<DistMax";
  }
  ThresholdField()
  {
    iField = 0;
    dmin = 1;
    dmax = 10;
    lcmin = 0.1;
    lcmax = 1;
    sigmoid = false;
    stopAtDistMax = false;
    options["IField"] = new FieldOptionInt(iField, "Index of the field to evaluate");
    options["DistMin"] = new FieldOptionDouble(dmin, "Distance from entity up to which "
					       "element size will be LcMin");
    options["DistMax"] = new FieldOptionDouble(dmax, "Distance from entity after which"
					       "element size will be LcMax");
    options["LcMin"] = new FieldOptionDouble(lcmin, "Element size inside DistMin");
    options["LcMax"] = new FieldOptionDouble(lcmax, "Element size outside DistMax");
    options["Sigmoid"] = new FieldOptionBool(sigmoid, "True to interpolate between LcMin "
					     "and LcMax using a sigmoid, false to "
					     "interpolate linearly");
    options["StopAtDistMax"] = new FieldOptionBool(stopAtDistMax, "True to not impose "
						   "element size outside DistMax (i.e. "
						   "F = a very big value if "
						   "Field[IField]>DistMax)");
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    Field *field = GModel::current()->getFields()->get(iField);
    if(!field) return MAX_LC;
    double r = ((*field) (x, y, z) - dmin) / (dmax - dmin);
    r = std::max(std::min(r, 1.), 0.);
    double lc;
    if(stopAtDistMax && r >= 1.){
      lc = MAX_LC;
    }
    else if(sigmoid){
      double s = exp(12. * r - 6.) / (1. + exp(12. * r - 6.));
      lc = lcmin * (1. - s) + lcmax * s;
    }
    else{ // linear
      lc = lcmin * (1 - r) + lcmax * r;
    }
    return lc;
  }
};

class GradientField : public Field
{
  int iField, kind;
  double delta;
 public:
  const char *get_name()
  {
    return "Gradient";
  }
  std::string get_description()
  {
    return "Compute the finite difference gradient of Field[IField].\n "
      "F = (Field[IField](X + Delta/2) - Field[IField](X - Delta/2))/Delta";
  }
  GradientField() : iField(0), kind(3), delta(CTX.lc / 1e4)
  {
    iField = 1;
    kind = 0;
    delta = 0.;
    options["IField"] = new FieldOptionInt(iField, "Field index");
    options["Kind"] = new FieldOptionInt(kind, "Component of the gradient to evaluate :"
					 " 0 for X, 1 for Y, 2 for Z, 3 for the norm");
    options["Delta"] = new FieldOptionDouble(delta, "Finite difference step");
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    Field *field = GModel::current()->getFields()->get(iField);
    if(!field) return MAX_LC;
    double gx, gy, gz;
    switch (kind) {
    case 0:    /* x */
      return ((*field) (x + delta / 2, y, z) -
              (*field) (x - delta / 2, y, z)) / delta;
    case 1:    /* y */
      return ((*field) (x, y + delta / 2, z) -
              (*field) (x, y - delta / 2, z)) / delta;
    case 2:    /* z */
      return ((*field) (x, y, z + delta / 2) -
              (*field) (x, y, z - delta / 2)) / delta;
    case 3:    /* norm */
      gx =
        ((*field) (x + delta / 2, y, z) -
         (*field) (x - delta / 2, y, z)) / delta;
      gy =
        ((*field) (x, y + delta / 2, z) -
         (*field) (x, y - delta / 2, z)) / delta;
      gz =
        ((*field) (x, y, z + delta / 2) -
         (*field) (x, y, z - delta / 2)) / delta;
      return sqrt(gx * gx + gy * gy + gz * gz);
    default:
      Msg::Error("Field %i : Unknown kind (%i) of gradient.", this->id,
		 kind);
      return MAX_LC;
    }
  }
};

class CurvatureField : public Field
{
  int iField;
  double delta;
 public:
  const char *get_name()
  {
    return "Curvature";
  }
  std::string get_description()
  {
    return "Compute the curvature of Field[IField]. \n"
      "F = divergence( || grad( Field[IField] ) || )";
  }
  CurvatureField() : iField(0), delta(CTX.lc / 1e4)
  {
    iField = 1;
    delta = 0.;
    options["IField"] = new FieldOptionInt(iField, "Field index");
    options["Delta"] = new FieldOptionDouble(delta, "Step of the finite differences");
  }
  void grad_norm(Field &f,double x,double y,double z, double *g)
  {
    g[0] = f(x + delta / 2, y, z) - f(x - delta / 2, y, z);
    g[1] = f(x, y + delta / 2, z) - f(x, y - delta / 2, z);
    g[2] = f(x, y, z + delta / 2) - f(x, y, z - delta / 2);
    double n=sqrt(g[0] * g[0] + g[1] * g[1] + g[2] * g[2]);
    g[0] /= n;
    g[1] /= n;
    g[2] /= n;
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    Field *field = GModel::current()->getFields()->get(iField);
    if(!field) return MAX_LC;
    double grad[6][3];
    grad_norm(*field, x + delta / 2, y, z, grad[0]);
    grad_norm(*field, x - delta / 2, y, z, grad[1]);
    grad_norm(*field, x, y + delta / 2, z, grad[2]);
    grad_norm(*field, x, y - delta / 2, z, grad[3]);
    grad_norm(*field, x, y, z + delta / 2, grad[4]);
    grad_norm(*field, x, y, z - delta / 2, grad[5]);
    return (grad[0][0] - grad[1][0] + grad[2][1] - 
	    grad[3][1] + grad[4][2] - grad[5][2]) / delta;
  }
};

class MaxEigenHessianField : public Field
{
  int iField;
  double delta;
 public:
  const char *get_name()
  {
    return "MaxEigenHessian";
  }
  std::string get_description()
  {
    return "Compute the maximum eigenvalue of the Hessian matrix of Field[IField], "
      "with the gradients evaluated by finite differences."
      "F = max ( eigenvalues ( grad ( grad ( Field[IField] ) ) ) ) ";
  }
  MaxEigenHessianField() : iField(0), delta(CTX.lc / 1e4)
  {
    iField = 1;
    delta = 0.;
    options["IField"] = new FieldOptionInt(iField, "Field index");
    options["Delta"] = new FieldOptionDouble(delta, "Step used for the finite differences");
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    Field *field = GModel::current()->getFields()->get(iField);
    if(!field) return MAX_LC;
    double mat[3][3], eig[3];
    mat[1][0] = mat[0][1] = (*field) (x + delta / 2 , y + delta / 2, z)
      + (*field) (x - delta / 2 , y - delta / 2, z)
      - (*field) (x - delta / 2 , y + delta / 2, z)
      - (*field) (x + delta / 2 , y - delta / 2, z);
    mat[2][0] = mat[0][2] = (*field) (x + delta/2 , y, z + delta / 2)
      + (*field) (x - delta / 2 , y, z - delta / 2)
      - (*field) (x - delta / 2 , y, z + delta / 2)
      - (*field) (x + delta / 2 , y, z - delta / 2);
    mat[2][1] = mat[1][2] = (*field) (x, y + delta/2 , z + delta / 2)
      + (*field) (x, y - delta / 2 , z - delta / 2)
      - (*field) (x, y - delta / 2 , z + delta / 2)
      - (*field) (x, y + delta / 2 , z - delta / 2);
    double f = (*field)(x, y, z);
    mat[0][0] = (*field)(x + delta, y, z) + (*field)(x - delta, y, z) - 2 * f;
    mat[1][1] = (*field)(x, y + delta, z) + (*field)(x, y - delta, z) - 2 * f;
    mat[2][2] = (*field)(x, y, z + delta) + (*field)(x, y, z - delta) - 2 * f;
    eigenvalue(mat, eig);
    return eig[0] / (delta * delta);
  }
};

class LaplacianField : public Field
{
  int iField;
  double delta;
 public:
  const char *get_name()
  {
    return "Laplacian";
  }
  std::string get_description()
  {
    return "Compute finite difference the Laplacian of Field[IField].\n"
      "F = divergence(gradient(Field[IField])) \n"
      "F = G(x+d,y,z)+G(x-d,y,z)+G(x,y+d,z)+G(x,y-d,z)+ "
      "+G(x,y,z+d)+G(x,y,z-d)-6*G(x,y,z) "
      "where G=Field[IField] and d=delta\n";
  }
  LaplacianField() : iField(0), delta(CTX.lc / 1e4)
  {
    iField = 1;
    delta = 0.1;
    options["IField"] = new FieldOptionInt(iField, "Field index");
    options["Delta"] = new FieldOptionDouble(delta, "Finite difference step");
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    Field *field = GModel::current()->getFields()->get(iField);
    if(!field) return MAX_LC;
    return ((*field) (x + delta , y, z)+ (*field) (x - delta , y, z)
	    +(*field) (x, y + delta , z)+ (*field) (x, y - delta , z)
	    +(*field) (x, y, z + delta )+ (*field) (x, y, z - delta )
	    -6* (*field) (x , y, z)) / (delta*delta);
  }
};

class MeanField : public Field
{
  int iField;
  double delta;
 public:
  const char *get_name()
  {
    return "Mean";
  }
  std::string get_description()
  {
    return "Very simple smoother.\n"
      "F = (G(x+delta,y,z)+G(x-delta,y,z) "
      "+G(x,y+delta,z)+G(x,y-delta,z) "
      "+G(x,y,z+delta)+G(x,y,z-delta) "
      "+G(x,y,z))/7 "
      "where G=Field[IField]";
  }
  MeanField() : iField(0), delta(CTX.lc / 1e4)
  {
    options["IField"] = new FieldOptionInt(iField, "Field index");
    options["Delta"] = new FieldOptionDouble(delta, "Distance used to compute the mean value");
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    Field *field = GModel::current()->getFields()->get(iField);
    if(!field) return MAX_LC;
    return ((*field) (x + delta , y, z) + (*field) (x - delta, y, z)
	    + (*field) (x, y + delta, z) + (*field) (x, y - delta, z)
	    + (*field) (x, y, z + delta) + (*field) (x, y, z - delta)
	    + (*field) (x, y, z)) / 7;
  }
};

#if defined(HAVE_MATH_EVAL)
class MathEvalExpression
{
  bool error_status;
  std::list<Field*> *list;
  int nvalues;
  char **names;
  double *values;
  void *eval;
  int *evaluators_id;
  std::string function;
  char *c_str_function;
 public:
  double evaluate(double x, double y, double z)
  {
    if(error_status)
      return MAX_LC;
    for(int i = 0; i < nvalues; i++){
      switch (evaluators_id[i]) {
      case -1:
        values[i] = x;
        break;
      case -2: 
	values[i] = y;
        break;
      case -3: 
	values[i] = z;
        break;
      default:
        {
          Field *f = GModel::current()->getFields()->get(evaluators_id[i]);
          values[i] = f ? (*f) (x, y, z) : MAX_LC;
        }
      }
    }
    return evaluator_evaluate(eval, nvalues, names, values);
  }
  MathEvalExpression()
  {
    eval = 0;
    values = 0;
    c_str_function = 0;
    evaluators_id = 0;
  }
  bool set_function(const std::string & f)
  {
    free_members();
    error_status = false;
    c_str_function = strdup(f.c_str());
    eval = evaluator_create(c_str_function);
    if(!eval) {
      error_status = true;
      return false;
    }
    evaluator_get_variables(eval, &names, &nvalues);
    values = new double[nvalues];
    evaluators_id = new int[nvalues];
    for(int i = 0; i < nvalues; i++) {
      int id;
      if(!strcmp("x", names[i]))
        evaluators_id[i] = -1;
      else if(!strcmp("y", names[i]))
        evaluators_id[i] = -2;
      else if(!strcmp("z", names[i]))
        evaluators_id[i] = -3;
      else if(sscanf(names[i], "F%i", &id) == 1)
        evaluators_id[i] = id;
      else {
        Msg::Error("Unknown matheval argument \"%s\"\n", names[i]);
        error_status = true;
        return false;
      }
    }
    return true;
  }
  void free_members()
  {
    if(c_str_function)
      free(c_str_function);
    if(eval)
      evaluator_destroy(eval);
    if(values)
      delete[]values;
    if(evaluators_id)
      delete evaluators_id;
  }
  ~MathEvalExpression()
  {
    free_members();
  }
};

class MathEvalField : public Field
{
  MathEvalExpression expr;
  std::string f;
 public:
  MathEvalField()
  {
    options["F"] = new FieldOptionString(f, "Mathematical function to evaluate.", 
					 &update_needed);
    f = "F2 + Sin(z)";
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    if(update_needed) {
      if(!expr.set_function(f))
        Msg::Error("Field %i : Invalid matheval expression \"%s\"",
		   this->id, f.c_str());
      update_needed = false;
    }
    return expr.evaluate(x, y, z);
  }
  const char *get_name()
  {
    return "MathEval";
  }
  std::string get_description()
  {
    return "Evaluate a mathematical expression. "
      "The expression can contains x, y, z for spatial coordinates, "
      "F0, F1, ... for field values, and mathematical functions. "
      "This evaluator is based on a modified version of the GNU libmatheval library. \n"
      "Example : F2 + Sin(z)";
  }
};

class ParametricField : public Field
{
  MathEvalExpression expr[3];
  std::string f[3];
  int ifield;
 public:
  ParametricField()
  {
    ifield = 1;
    options["IField"] = new FieldOptionInt(ifield, "Field index");
    options["FX"] = new FieldOptionString(f[0], "X component of parametric function",
					  &update_needed);
    options["FY"] = new FieldOptionString(f[1], "Y component of parametric function",
					  &update_needed);
    options["FZ"] = new FieldOptionString(f[2], "Z component of parametric function",
					  &update_needed);
  }
  std::string get_description()
  {
    return "Evaluate Field IField in parametric coordinate. "
      "See MathEval Field help to get a description of valid FX, FY and FZ expressions.\n"
      "F = Field[IField](FX,FY,FZ) ";
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    if(update_needed) {
      for(int i = 0; i < 3; i++) {
        if(!expr[i].set_function(f[i]))
          Msg::Error("Field %i : Invalid matheval expression \"%s\"",
		     this->id, f[i].c_str());
      }
      update_needed = false;
    }
    Field *field = GModel::current()->getFields()->get(ifield);
    if(!field) return MAX_LC;
    return (*field)(expr[0].evaluate(x, y, z),
		    expr[1].evaluate(x, y, z),
		    expr[2].evaluate(x, y, z));
  }
  const char *get_name()
  {
    return "Param";
  }
};
#endif

#if !defined(HAVE_NO_POST)
class PostViewField : public Field
{
  OctreePost *octree;
 public:
  int view_index;
  bool crop_negative_values;
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    // FIXME: should test unique view num instead, but that would be slower
    if(view_index < 0 || view_index >= (int)PView::list.size())
      return MAX_LC;
    if(update_needed){
      if(octree) delete octree;
      octree = new OctreePost(PView::list[view_index]);
      update_needed = false;
    }
    double l = 0.;
    if(!octree->searchScalar(x, y, z, &l, 0)) {
      // try really hard to find an element around the point
      /*
	double fact[4] = {1.e-6, 1.e-5, 1.e-4, 1.e-3};
	for(int i = 0; i < 4; i++){
	  double eps = CTX.lc * fact[i];
	  printf("approx search witg eps=%g\n", eps);
	  if(octree->searchScalar(x + eps, y, z, &l, 0)) break;
	  if(octree->searchScalar(x - eps, y, z, &l, 0)) break;
	  if(octree->searchScalar(x, y + eps, z, &l, 0)) break;
	  if(octree->searchScalar(x, y - eps, z, &l, 0)) break;
	  if(octree->searchScalar(x, y, z + eps, &l, 0)) break;
	  if(octree->searchScalar(x, y, z - eps, &l, 0)) break;
	  if(octree->searchScalar(x + eps, y - eps, z - eps, &l, 0)) break;
	  if(octree->searchScalar(x + eps, y + eps, z - eps, &l, 0)) break;
	  if(octree->searchScalar(x - eps, y - eps, z - eps, &l, 0)) break;
	  if(octree->searchScalar(x - eps, y + eps, z - eps, &l, 0)) break;
	  if(octree->searchScalar(x + eps, y - eps, z + eps, &l, 0)) break;
	  if(octree->searchScalar(x + eps, y + eps, z + eps, &l, 0)) break;
	  if(octree->searchScalar(x - eps, y - eps, z + eps, &l, 0)) break;
	  if(octree->searchScalar(x - eps, y + eps, z + eps, &l, 0)) break;
	}
      */
    }
    if(l <= 0 && crop_negative_values) return MAX_LC;
    return l;
  }
  const char *get_name()
  {
    return "PostView";
  }
  std::string get_description()
  {
    return "Evaluate the post processing view IView.";
  }
  PostViewField()
  {
    octree = 0;
    view_index = 0;
    options["IView"] = new FieldOptionInt(view_index, "Post-processing view index",
					  &update_needed);
    crop_negative_values = true;
    options["CropNegativeValues"] = new FieldOptionBool(crop_negative_values, 
							"return LC_MAX instead of a "
							"negative value (this option "
							"is needed for backward "
							"compatibility with the "
							"BackgroundMesh option",
							&update_needed);
  }
  ~PostViewField()
  {
    if(octree) delete octree;
  }
};
#endif

class MinField : public Field
{
  std::list<int> idlist;
 public:
  MinField()
  {
    options["FieldsList"] = new FieldOptionList(idlist, "Field indices",
						&update_needed);
  }
  std::string get_description()
  {
    return "Take the minimum value of a list of fields. ";
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    double v = MAX_LC;
    for(std::list<int>::iterator it = idlist.begin(); it != idlist.end(); it++) {
      Field *f = (GModel::current()->getFields()->get(*it));
      if(f) v = std::min(v, (*f) (x, y, z, ge));
    }
    return v;
  }
  const char *get_name()
  {
    return "Min";
  }
};

class MaxField : public Field
{
  std::list<int> idlist;
 public:
  MaxField()
  {
    options["FieldsList"] = new FieldOptionList(idlist, "Field indices", 
						&update_needed);
  }
  std::string get_description()
  {
    return "Take the maximum value of a list of fields.";
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    double v = -MAX_LC;
    for(std::list<int>::iterator it = idlist.begin(); it != idlist.end(); it++) {
      Field *f = (GModel::current()->getFields()->get(*it));
      if(f) v = std::max(v, (*f) (x, y, z, ge));
    }
    return v;
  }
  const char *get_name()
  {
    return "Max";
  }
};

class RestrictField : public Field
{
  int ifield;
  std::list<int> edges, faces, regions;
 public:
  RestrictField()
  {
    ifield = 1;
    options["IField"] = new FieldOptionInt(ifield, "Field index");
    options["EdgesList"] = new FieldOptionList(edges, "Curve indices");
    options["FacesList"] = new FieldOptionList(faces, "Surface indices");
    options["RegionsList"] = new FieldOptionList(regions, "Volume indices");
  }
  std::string get_description()
  {
    return "Restrict the application of a field to a given list of geometrical "
      "curves, surfaces or volumes. ";
  }
  double operator() (double x, double y, double z, GEntity *ge=0)
  {
    Field *f = (GModel::current()->getFields()->get(ifield));
    if(!f) return MAX_LC;
    if(!ge) return (*f) (x, y, z);
    if((ge->dim() == 0) ||
       (ge->dim() == 1 && std::find(edges.begin(), edges.end(), ge->tag()) != edges.end()) ||
       (ge->dim() == 2 && std::find(faces.begin(), faces.end(), ge->tag()) != faces.end()) ||
       (ge->dim() == 3 && std::find(regions.begin(), regions.end(), ge->tag()) != regions.end()))
      return (*f) (x, y, z);
    return MAX_LC;
  }
  const char *get_name()
  {
    return "Restrict";
  }
};

#ifdef HAVE_ANN
class AttractorField : public Field
{
  ANNkd_tree *kdtree;
  ANNpointArray zeronodes;
  ANNidxArray index;
  ANNdistArray dist;
  std::list<int> nodes_id, edges_id, faces_id;
  int n_nodes_by_edge;
 public:
  AttractorField() : kdtree(0), zeronodes(0)
  {
    index = new ANNidx[1];
    dist = new ANNdist[1];
    n_nodes_by_edge = 20;
    options["NodesList"] = new FieldOptionList(nodes_id, "Indices of "
					       "nodes in the geomtric model",
					       &update_needed);
    options["EdgesList"] = new FieldOptionList(edges_id, "Indices of "
					       "curves in the geometric model",
					       &update_needed);
    options["NNodesByEdge"] = new FieldOptionInt(n_nodes_by_edge, "Number of nodes "
						 "used to discetized each curve", 
						 &update_needed);
    options["FacesList"] = new FieldOptionList(faces_id, "Indices of "
					       "surfaces in the geometric model "
					       "(Warning: might give strange "
					       "results for complex surfaces)",
					       &update_needed);
  }
  ~AttractorField()
  {
    if(kdtree) delete kdtree;
    if(zeronodes) annDeallocPts(zeronodes);
    delete[]index;
    delete[]dist;
  }
  const char *get_name()
  {
    return "Attractor";
  }
  std::string get_description()
  {
    return "Compute the distance from the nearest node in a list. "
      "It can also be used to compute distance from curves, in this case each "
      "curve is replaced by NNodesByEdge equidistant nodes and the distance "
      "from those nodes is computed. \n"
      "The ANN library is used to find the nearest node: "
      "http://www.cs.umd.edu/~mount/ANN/ ";
  }
  virtual double operator() (double X, double Y, double Z, GEntity *ge=0)
  {
    if(update_needed) {
      if(zeronodes) {
        annDeallocPts(zeronodes);
        delete kdtree;
      }
      int totpoints = nodes_id.size() + n_nodes_by_edge * edges_id.size() + 
	n_nodes_by_edge * n_nodes_by_edge * faces_id.size();
      if(totpoints)
        zeronodes = annAllocPts(totpoints, 4);
      int k = 0;
      for(std::list<int>::iterator it = nodes_id.begin();
          it != nodes_id.end(); ++it) {
        Vertex *v = FindPoint(*it);
        if(v) {
          zeronodes[k][0] = v->Pos.X;
          zeronodes[k][1] = v->Pos.Y;
          zeronodes[k++][2] = v->Pos.Z;
        }
        else {
          GVertex *gv = GModel::current()->getVertexByTag(*it);
          if(gv) {
            zeronodes[k][0] = gv->x();
            zeronodes[k][1] = gv->y();
            zeronodes[k++][2] = gv->z();
          }
        }
      }
      for(std::list<int>::iterator it = edges_id.begin();
          it != edges_id.end(); ++it) {
        Curve *c = FindCurve(*it);
        if(c) {
          for(int i = 0; i < n_nodes_by_edge; i++) {
            double u = (double)i / (n_nodes_by_edge - 1);
            Vertex V = InterpolateCurve(c, u, 0);
            zeronodes[k][0] = V.Pos.X;
            zeronodes[k][1] = V.Pos.Y;
            zeronodes[k++][2] = V.Pos.Z;
          }
        }
        else {
          GEdge *e = GModel::current()->getEdgeByTag(*it);
          if(e) {
            for(int i = 0; i < n_nodes_by_edge; i++) {
              double u = (double)i / (n_nodes_by_edge - 1);
              Range<double> b = e->parBounds(0);
              double t = b.low() + u * (b.high() - b.low());
              GPoint gp = e->point(t);
              zeronodes[k][0] = gp.x();
              zeronodes[k][1] = gp.y();
              zeronodes[k++][2] = gp.z();
            }
          }
        }
      }
      // This can lead to weird results as we generate attractors over
      // the whole parametric plane (we should really use a mesh,
      // e.g. a refined STL.)
      for(std::list<int>::iterator it = faces_id.begin();
          it != faces_id.end(); ++it) {
        Surface *s = FindSurface(*it);
        if(s) {
          for(int i = 0; i < n_nodes_by_edge; i++) {
	    for(int j = 0; j < n_nodes_by_edge; j++) {
	      double u = (double)i / (n_nodes_by_edge - 1);
	      double v = (double)j / (n_nodes_by_edge - 1);
	      Vertex V = InterpolateSurface(s, u, v, 0, 0);
	      zeronodes[k][0] = V.Pos.X;
	      zeronodes[k][1] = V.Pos.Y;
	      zeronodes[k++][2] = V.Pos.Z;
	    }
	  }
        }
        else {
          GFace *f = GModel::current()->getFaceByTag(*it);
          if(f) {
            for(int i = 0; i < n_nodes_by_edge; i++) {
	      for(int j = 0; j < n_nodes_by_edge; j++) {
		double u = (double)i / (n_nodes_by_edge - 1);
		double v = (double)j / (n_nodes_by_edge - 1);
		Range<double> b1 = ge->parBounds(0);
		Range<double> b2 = ge->parBounds(1);
		double t1 = b1.low() + u * (b1.high() - b1.low());
		double t2 = b2.low() + v * (b2.high() - b2.low());
		GPoint gp = f->point(t1, t2);
		zeronodes[k][0] = gp.x();
		zeronodes[k][1] = gp.y();
		zeronodes[k++][2] = gp.z();
	      }
	    }
          }
        }
      }
      kdtree = new ANNkd_tree(zeronodes, totpoints, 3);
      update_needed = false;
    }
    double xyz[3] = { X, Y, Z };
    kdtree->annkSearch(xyz, 1, index, dist);
    return sqrt(dist[0]);
  }
};
#endif

template<class F> class FieldFactoryT : public FieldFactory {
 public:
  Field * operator()() { return new F; }
};

template<class F> Field *field_factory()
{
  return new F();
};

FieldManager::FieldManager()
{
  map_type_name["Structured"] = new FieldFactoryT<StructuredField>();
  map_type_name["Threshold"] = new FieldFactoryT<ThresholdField>();
  map_type_name["Box"] = new FieldFactoryT<BoxField>();
  map_type_name["LonLat"] = new FieldFactoryT<LonLatField>();
#if !defined(HAVE_NO_POST)
  map_type_name["PostView"] = new FieldFactoryT<PostViewField>();
#endif
  map_type_name["Gradient"] = new FieldFactoryT<GradientField>();
  map_type_name["Restrict"] = new FieldFactoryT<RestrictField>();
  map_type_name["Min"] = new FieldFactoryT<MinField>();
  map_type_name["Max"] = new FieldFactoryT<MaxField>();
  map_type_name["UTM"] = new FieldFactoryT<UTMField>();
  map_type_name["Laplacian"] = new FieldFactoryT<LaplacianField>();
  map_type_name["Mean"] = new FieldFactoryT<MeanField>();
  map_type_name["Curvature"] = new FieldFactoryT<CurvatureField>();
#if defined(HAVE_MATH_EVAL)
  map_type_name["Param"] = new FieldFactoryT<ParametricField>();
  map_type_name["MathEval"] = new FieldFactoryT<MathEvalField>();
#endif
#if defined(HAVE_ANN)
  map_type_name["Attractor"] = new FieldFactoryT<AttractorField>();
#endif
  map_type_name["MaxEigenHessian"] = new FieldFactoryT<MaxEigenHessianField>();
  background_field = -1;
}

static void evaluate(Field * field, List_T * list1, int nbElm1, int nbNod,
                     int nbComp, int comp)
{
  if(!nbElm1)
    return;
  int nb = List_Nbr(list1) / nbElm1;
  for(int i = 0; i < List_Nbr(list1); i += nb) {
    double *x = (double *)List_Pointer_Fast(list1, i);
    double *y = (double *)List_Pointer_Fast(list1, i + nbNod);
    double *z = (double *)List_Pointer_Fast(list1, i + 2 * nbNod);
    for(int j = 0; j < nbNod; j++) {
      // store data from the main view into v
      double *val1 = (double *)List_Pointer_Fast(list1,
                                                 i + 3 * nbNod +
                                                 nbNod * nbComp * 0 +
                                                 nbComp * j);
      val1[comp] = (*field) (x[j], y[j], z[j]);
    }
  }
}

Field::Field()
{
}

#if !defined(HAVE_NO_POST)
void Field::put_on_new_view()
{
  std::map<int, std::vector<double> > d;
  std::vector<GEntity*> entities;
  GModel::current()->getEntities(entities);
  for(unsigned int i = 0; i < entities.size(); i++){
    for(unsigned int j = 0; j < entities[i]->mesh_vertices.size(); j++){
      MVertex *v = entities[i]->mesh_vertices[j];
      d[v->getNum()].push_back((*this)(v->x(), v->y(), v->z(), entities[i]));
    }
  }
  std::ostringstream oss;
  oss << "Field " << id;
  PView *view= new PView(oss.str().c_str(), "NodeData", GModel::current(), d);
  view->setChanged(true);
}

void Field::put_on_view(PView * view, int comp)
{
  PViewDataList *data = dynamic_cast<PViewDataList*>(view->getData());
  if(!data)
    return;
  evaluate(this, data->SP, data->NbSP, 1, 1, 0);
  evaluate(this, data->SL, data->NbSL, 2, 1, 0);
  evaluate(this, data->ST, data->NbST, 3, 1, 0);
  evaluate(this, data->SQ, data->NbSQ, 4, 1, 0);
  evaluate(this, data->SS, data->NbSS, 4, 1, 0);
  evaluate(this, data->SH, data->NbSH, 8, 1, 0);
  evaluate(this, data->SI, data->NbSI, 6, 1, 0);
  evaluate(this, data->SY, data->NbSY, 5, 1, 0);
  for(int cc = 0; cc < 3; cc++) {
    if(comp < 0 || comp == cc) {
      evaluate(this, data->VP, data->NbVP, 1, 3, cc);
      evaluate(this, data->VL, data->NbVL, 2, 3, cc);
      evaluate(this, data->VT, data->NbVT, 3, 3, cc);
      evaluate(this, data->VQ, data->NbVQ, 4, 3, cc);
      evaluate(this, data->VS, data->NbVS, 4, 3, cc);
      evaluate(this, data->VH, data->NbVH, 8, 3, cc);
      evaluate(this, data->VI, data->NbVI, 6, 3, cc);
      evaluate(this, data->VY, data->NbVY, 5, 3, cc);
    }
  }
  for(int cc = 0; cc < 9; cc++) {
    if(comp < 0 || comp == cc) {
      evaluate(this, data->TP, data->NbTP, 1, 9, cc);
      evaluate(this, data->TL, data->NbTL, 2, 9, cc);
      evaluate(this, data->TT, data->NbTT, 3, 9, cc);
      evaluate(this, data->TQ, data->NbTQ, 4, 9, cc);
      evaluate(this, data->TS, data->NbTS, 4, 9, cc);
      evaluate(this, data->TH, data->NbTH, 8, 9, cc);
      evaluate(this, data->TI, data->NbTI, 6, 9, cc);
      evaluate(this, data->TY, data->NbTY, 5, 9, cc);
    }
  }
  data->finalize();
  view->setChanged(true);
}
#endif

void FieldManager::set_background_mesh(int iView)
{
  int id = new_id();
  Field *f = new_field(id, "PostView");
  f->options["IView"]->numerical_value(iView);
  (*this)[id] = f;
  background_field = id;
}
