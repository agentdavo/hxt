// Gmsh - Copyright (C) 1997-2009 C. Geuzaine, J.-F. Remacle
// 
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to <gmsh@geuz.org>.
// 
// Contributed by Matti Pellikka <matti.pellikka@tut.fi>.
// 

#include <stdio.h>
#include <sstream>
#include <gmsh/Gmsh.h>
#include <gmsh/GModel.h>
#include <gmsh/MElement.h>
#include <gmsh/CellComplex.h>
#include <gmsh/ChainComplex.h>
#include <gmsh/Homology.h>

int main(int argc, char **argv)
{
  GmshInitialize(argc, argv);
  GModel *m = new GModel();
  
  m->readGEO("model.geo");
  m->mesh(3);
  // OR
  // m->readMSH("model.msh");
  
  // List of physical regions as domain for homology computation (relative to subdomain).
  std::vector<int> domain;
  std::vector<int> subdomain;
  
  Homology* homology = new Homology(m, domain, subdomain);
  std::string fileName = "homology_generators.msh";
  homology->findGenerators(fileName);
  homology->restoreHomology();
  
  Homology* homology = new Homology(m, domain, subdomain);
  fileName = "homology_dualgenerators.msh";
  homology->findDualGenerators(fileName);
  homology->restoreHomology();
  
  Homology* homology = new Homology(m, domain, subdomain);
  homology->computeBettiNumbers();
  delete homology;
  
  delete m;
  GmshFinalize();
  
}




