
#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace calcolo{
	double EdgeLength(const double& x1, const double& y1,const double& x2, const double& y2);
}

namespace PolygonalLibrary
{

bool ImportMesh(PolygonalMesh& mesh);

bool ImportCell0Ds(PolygonalMesh& mesh);


bool ImportCell1Ds(PolygonalMesh& mesh);

bool ImportCell2Ds(PolygonalMesh& mesh);

bool CheckEdges(const PolygonalMesh& mesh, const double& eps);

//bool CheckAreas(const PolygonalMesh& mesh, const double& eps);


}
