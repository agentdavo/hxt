#ifndef HXT_OCTREE_H
#define HXT_OCTREE_H

// GMSH INCLUDES
#include "rtree.h"

#ifdef HAVE_P4EST
#include <p4est_to_p8est.h>
#include <p8est_extended.h>
#endif

extern "C" {
  #include "hxt_api.h"
  #include "hxt_mesh.h"
  #include "hxt_bbox.h"
}

// Information needed to create and compute an HXTForest
typedef struct HXTForestOptions{
  double 				hmax;
  double 				hmin;
  double 				hbulk;
  double 				gradMax;
  int           nRefine;
  int           nodePerTwoPi;
  int           nodePerGap;
  double       *bbox;
  double      (*sizeFunction)(double, double, double, double);
  const char   *forestFile;
  RTree<uint64_t,double,3>  *triRTree;
  HXTMesh                   *mesh;
  double                    *nodalCurvature;
  double                    *nodeNormals;
} HXTForestOptions;

// The structure containing the size field information
typedef struct HXTForest{
#ifdef HAVE_P4EST
  p4est_t *p4est;
#endif 
  HXTForestOptions *forestOptions;
} HXTForest;

// Data available on each tree cell
typedef struct size_data{
  double size;
#ifdef HAVE_P4EST
  // Size gradient
  double ds[P4EST_DIM];
#endif
  double h;
  // Half cell length for finite differences
  double h_xL, h_xR;
  double h_yD, h_yU;
  double h_zB, h_zT;
  int isBoundary;
} size_data_t;

// A node to search in the tree
typedef struct size_point{
  double x;
  double y;
  double z;
  double size;
  bool isFound;
} size_point_t;

// Additional user-defined size function : currently not used
typedef struct size_fun{
  double (*myFun)(double, double, double, double);
} size_fun_t;

// API ---------------------------------------------------------------------------------------------
HXTStatus hxtForestOptionsCreate(HXTForestOptions **forestOptions);
HXTStatus hxtForestOptionsDelete(HXTForestOptions **forestOptions);

HXTStatus hxtForestCreate(int argc, char **argv, HXTForest **forest, const char* filename, HXTForestOptions *forestOptions);
HXTStatus hxtForestDelete(HXTForest **forest);

HXTStatus hxtForestSave(HXTForest *forest);
HXTStatus hxtForestExport(HXTForest *forest);
HXTStatus hxtForestLoad(HXTForest **forest, const char* filename, HXTForestOptions *forestOptions);

HXTStatus hxtForestRefine(HXTForest *forest);
HXTStatus hxtForestSizeSmoothing(HXTForest *forest);
HXTStatus hxtForestCloseSurfaces(HXTForest *forest);

HXTStatus hxtOctreeElementEstimation(HXTForest *forest, double *elemEstimate);
HXTStatus hxtForestSearchOne(HXTForest *forest, double x, double y, double z, double *size, int linear);

#endif
