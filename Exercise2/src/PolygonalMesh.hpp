#pragma once

#include <iostream>
#include "Eigen/Eigen"
#include <vector>

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
    unsigned int NumCell0Ds = 0; 
    std::vector<unsigned int> Cell0DsId = {};
    Eigen::MatrixXd Cell0DsCoordinates = {};
    std::map<unsigned int, list<unsigned int>> MarkerCell0Ds = {}; 

    unsigned int NumCell1Ds = 0; 
    std::vector<unsigned int> Cell1DsId = {}; 
    Eigen::MatrixXi Cell1DsExtrema = {};
    std::map<unsigned int, list<unsigned int>> MarkerCell1Ds = {}; 
    
    unsigned int NumCell2Ds = 0;
    std::vector<unsigned int> Cell2DsId = {}; 
    map<unsigned int, list<unsigned int>> NumVert2Ds = {};
    std::vector<vector<unsigned int>> Cell2DsVertices = {}; 
    map<unsigned int, list<unsigned int>> NumEdges2Ds= {}; 
    std::vector<vector<unsigned int>> Cell2DsEdges = {}; 
    
};

}

