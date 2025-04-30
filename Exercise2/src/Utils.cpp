#include "Utils.hpp"
#include "PolygonalMesh.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
using namespace PolygonalLibrary;

namespace calcolo {
double EdgeLength(const double& x1, const double& y1,const double& x2, const double& y2)
{
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}
}

namespace PolygonalLibrary
{
    // ***************************************************************************
    bool ImportMesh(PolygonalMesh& mesh)
    {
        if (!ImportCell0Ds(mesh))
            return false;

        if (!ImportCell1Ds(mesh))
            return false;

        if (!ImportCell2Ds(mesh))
            return false;

        return true;
    }

    // ***************************************************************************
    bool ImportCell0Ds(PolygonalMesh& mesh)
    {
        ifstream file("./Cell0Ds.csv");

        if (file.fail())
            return false;

        list<string> listLines;
        string line;
        while (getline(file, line))
            listLines.push_back(line);

        file.close();

        // remove header
        listLines.pop_front();

        mesh.NumCell0Ds = listLines.size();

        if (mesh.NumCell0Ds == 0)
        {
            cerr << "There is no cell 0D" << endl;
            return false;
        }

        mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
        mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);  // Correct size ?
 
        for (const string& line : listLines)
        {
          istringstream converter(line);
          unsigned int id;
          unsigned int marker;
          Vector2d coord;

          // Read the values
          char tmp;
          converter >>  id >>tmp>> marker >>tmp>>mesh.Cell0DsCoordinates(0,id)>>tmp>>mesh.Cell0DsCoordinates(1,id); 
         mesh.Cell0DsId.push_back(id);

         // markers
         if (marker != 0)
          {
            const auto it = mesh.MarkerCell0Ds.find(marker);
            if (it == mesh.MarkerCell0Ds.end())
              {
                mesh.MarkerCell0Ds.insert({marker, {id}});
              }
         else
            {
            it->second.push_back(id);
          }
       }
}


        return true;
    }

    // ***************************************************************************
    bool ImportCell1Ds(PolygonalMesh& mesh)
    {
        ifstream file("./Cell1Ds.csv");

        if (file.fail())
            return false;

        list<string> listLines;
        string line;
        while (getline(file, line))
            listLines.push_back(line);

        file.close();

        // remove header
        listLines.pop_front();

        mesh.NumCell1Ds = listLines.size();

        if (mesh.NumCell1Ds == 0)
        {
            cerr << "There is no cell 1D" << endl;
            return false;
        }

        mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
        mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);

        //unsigned int index = 0;
        for (const string& line : listLines)
        {
            istringstream converter(line);
            unsigned int id;
            unsigned int marker;
            Vector2i vertices;
            char tmp;

            converter >>  id >>tmp>> marker >>tmp >> mesh.Cell1DsExtrema(0, id) >> tmp >>mesh.Cell1DsExtrema(1, id);
            mesh.Cell1DsId.push_back(id);

            //mesh.Cell1DsExtrema.col(index) = vertices;
            //mesh.Cell1DsId.push_back(id);

            //per i markers
            if (marker != 0)
            {
                const auto it = mesh.MarkerCell1Ds.find(marker);
                if (it == mesh.MarkerCell1Ds.end())
                {
                    mesh.MarkerCell1Ds.insert({marker, {id}});
                }
                else
                {
                    it->second.push_back(id);
                }
            }
            //++index;
        }

        return true;
    }
  
  //sistemata?
    bool ImportCell2Ds(PolygonalMesh& mesh)
    {
        ifstream file("./Cell2Ds.csv");

        if (file.fail())
            return false;

        list<string> listLines;
        string line;
        while (getline(file, line))
            listLines.push_back(line);

        file.close();

        // remove header
        listLines.pop_front();

        mesh.NumCell2Ds = listLines.size();

        if (mesh.NumCell2Ds == 0)
        {
            cerr << "There is no cell 2D" << endl;
            return false;
        }

        mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
        mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
        mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);

        for (const string& line : listLines)
        {
            istringstream converter(line);
            stringstream ss;
            string tmp;

            unsigned int id;
            unsigned int marker;
            unsigned int num_vert;
            vector<unsigned int> vertices;
            unsigned int num_edges;
            vector<unsigned int> edges;
            
            getline(converter, tmp,';');
            ss << tmp;
            ss >> id;
            ss.clear();
            
            getline(converter,tmp,';');
            ss<<tmp;
            ss>>id;
            ss.clear();
            
            getline(converter, tmp, ';');
            ss<<tmp;
            ss>>marker;
            ss.clear();
            
            getline(converter, tmp,';');
            ss<<tmp;
            ss>>num_vert;
            ss.clear();
            vertices.resize(num_vert);
            
            for (size_t i = 0; i < vertices.size(); ++i)
            {
            getline(converter, tmp, ';');
            ss << tmp;
            ss >> vertices[i];
            ss.clear();
            }
            getline(converter,tmp,';');
            ss<<tmp;
            ss>>num_edges;
            ss.clear();
            edges.resize(num_edges);
            //pure mettiamo un ciclo qua
            for(size_t i = 0; i< edges.size();++i)
            {
	            getline(converter, tmp, ';');
	            ss<<tmp;
	            ss>>edges[i];
	            ss.clear();
	            
            }
            mesh.Cell2DsId.push_back(id);
            mesh.Cell2DsVertices.push_back(vertices);
            mesh.Cell2DsEdges.push_back(edges);
            if (mesh.NumVert2Ds.find(num_vert) == mesh.NumVert2Ds.end())
            {
            mesh.NumVert2Ds.insert({num_vert, {id}});
            }
            else
            {
            mesh.NumVert2Ds[num_vert].push_back(id);
            }
            if (mesh.NumEdges2Ds.find(num_edges) == mesh.NumEdges2Ds.end())
            {
            mesh.NumEdges2Ds.insert({num_edges, {id}});
            }
            else
            {
            mesh.NumEdges2Ds[num_edges].push_back(id);
            } 

        }

        return true;
    }
    
    bool CheckEdges(const PolygonalMesh& mesh, const double& eps)
    {
    bool check = true;

    for (unsigned int i = 0; i < mesh.NumCell1Ds; ++i)
    {
        //id extrema
        unsigned int id1 = mesh.Cell1DsExtrema(0, i);
        unsigned int id2 = mesh.Cell1DsExtrema(1, i);

       
        auto it1 = id1;
        auto it2 = id2;
     
        unsigned int idx1 = it1;
        unsigned int idx2 = it2;

        double x1 = mesh.Cell0DsCoordinates(0, idx1);
        double y1 = mesh.Cell0DsCoordinates(1, idx1);
        double x2 = mesh.Cell0DsCoordinates(0, idx2);
        double y2 = mesh.Cell0DsCoordinates(1, idx2);

        double length = calcolo::EdgeLength(x1, y1, x2, y2);

        if (length <= eps)
        {
            std::cerr << "Warning: Edge " << i << " sotto tolleranza eps: (" << length << " ≤ " << eps << ")\n";
            check = false;
        }
    }
    if(check){
      cout << "segmenti validi" << endl;
    }

    return check;
    }
    
    
    
    
    //anche questa da errori di dimensioni 
    /*
    bool CheckAreas(const PolygonalMesh& mesh, const double& eps)
    {
    bool check = true;
    double x1;
    double x2;
    double y1;
    double y2;
    for (unsigned int i = 0; i < mesh.NumCell2Ds; ++i)
    {
        const std::vector<unsigned int>& edges = mesh.Cell2DsEdges[i];
        double area = 0.0;
        for (unsigned int k = 0; k < edges.size(); ++k)
        {
	        unsigned int edgeIdx = edges[k];

            if (edgeIdx >= mesh.Cell1DsExtrema.rows())
            {
                std::cerr << "Invalid edge index " << edgeIdx << " in polygon ID " << mesh.Cell2DsId[i] << std::endl;
                check = false;
                continue;
            }

            unsigned int vertice_1 = mesh.Cell1DsExtrema(edgeIdx, 0);
            unsigned int vertice_2 = mesh.Cell1DsExtrema(edgeIdx, 1);

            if (vertice_1 >= mesh.Cell0DsCoordinates.rows() || vertice_2 >= mesh.Cell0DsCoordinates.rows())
            {
                std::cerr << "Invalid vertex index (" << vertice_1 << ", " << vertice_2
                          << ") from edge " << edgeIdx << " in polygon ID " << mesh.Cell2DsId[i] << std::endl;
                check = false;
                continue;
            }
            x1 = mesh.Cell0DsCoordinates(vertice_1,0);
            x2 = mesh.Cell0DsCoordinates(vertice_2,0);
            y1 = mesh.Cell0DsCoordinates(vertice_1,1);
            y2 = mesh.Cell0DsCoordinates(vertice_2,1);
            area = area + (x1*y2 - y1*x2);
        }
        area = 0.5*abs(area);
        if (area < eps)
        {
            cout << "Polygon id: " << mesh.Cell2DsId[i] << "null area" << endl;
            check = false;
        }
    }
    if (check)
    {
        cout << "non null areas" << endl;
    }
    return check;
    
  }
 */
    
    
     
   
    
//questo qua da segmentation fault  
/*
    bool CheckAreas(const PolygonalMesh& mesh, const double& eps)
    {
    bool check = true;
    for (unsigned int i = 0; i < mesh.NumCell2Ds; ++i)
    {
        // Get the vertex IDs of the triangle
        const auto& vertex_ids = mesh.Cell2DsVertices[i];

        // Find indices of the vertices in Cell0DsCoordinates
        unsigned int idx1 = std::distance(mesh.Cell0DsId.begin(), std::find(mesh.Cell0DsId.begin(), mesh.Cell0DsId.end(), vertex_ids[0]));
        unsigned int idx2 = std::distance(mesh.Cell0DsId.begin(), std::find(mesh.Cell0DsId.begin(), mesh.Cell0DsId.end(), vertex_ids[1]));
        unsigned int idx3 = std::distance(mesh.Cell0DsId.begin(), std::find(mesh.Cell0DsId.begin(), mesh.Cell0DsId.end(), vertex_ids[2]));

        // Get coordinates of the vertices
        double x1 = mesh.Cell0DsCoordinates(0, idx1);
        double y1 = mesh.Cell0DsCoordinates(1, idx1);

        double x2 = mesh.Cell0DsCoordinates(0, idx2);
        double y2 = mesh.Cell0DsCoordinates(1, idx2);

        double x3 = mesh.Cell0DsCoordinates(0, idx3);
        double y3 = mesh.Cell0DsCoordinates(1, idx3);

        // Compute the area using the determinant (shoelace) formula
        double area = 0.5 * std::abs((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1));

        // Check if area is too small or negative (invalid triangle)
        if (area <= eps)
        {
            cerr << "Cell2D " << i << " has invalid area: " << area << endl;
            check = false;
        }
    }
    return check;
    }
    */
    
    
    
}
