// Gmsh - Copyright (C) 1997-2016 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to the public mailing list <gmsh@onelab.info>.

#ifndef BASISFACTORY_H
#define BASISFACTORY_H

#include <map>
class nodalBasis;
class GradientBasis;
class bezierBasis;
class CondNumBasis;
class JacobianBasis;
class FuncSpaceData;

class BasisFactory
{
 private:
  static std::map<int, nodalBasis*> fs;
  static std::map<int, CondNumBasis*> cs;
  static std::map<FuncSpaceData, JacobianBasis*> js;
  static std::map<FuncSpaceData, bezierBasis*> bs;
  static std::map<FuncSpaceData, GradientBasis*> gs;

 public:
  // Caution: the returned pointer can be NULL

  // Nodal
  static const nodalBasis* getNodalBasis(int tag);

  // Jacobian
  // Warning: bases returned by BasisFactory::getJacobianBasis(int tag) are the
  // only safe bases for using Bezier on the jacobian determinant!
  static const JacobianBasis* getJacobianBasis(FuncSpaceData);
  static const JacobianBasis* getJacobianBasis(int tag, int order);
  static const JacobianBasis* getJacobianBasis(int tag);

  // Condition number
  static const CondNumBasis* getCondNumBasis(int tag, int cnOrder = -1);

  // Gradients
  static const GradientBasis* getGradientBasis(FuncSpaceData);
  static const GradientBasis* getGradientBasis(int tag, int order);
  static const GradientBasis* getGradientBasis(int tag);

  // Bezier
  static const bezierBasis* getBezierBasis(FuncSpaceData);
  static const bezierBasis* getBezierBasis(int parentTag, int order);
  static const bezierBasis* getBezierBasis(int tag);

  static void clearAll();
};

#endif
