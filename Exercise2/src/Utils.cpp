#include "Utils.hpp"
#include "PolygonalMesh.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
using namespace PolygonalLibrary;

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

            converter >>  id >>tmp>> marker >>tmp >> mesh.Cell1DsExtrema(0, id) >> tmp >> mesh.Cell1DsExtrema(1, id);
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

    // ***************************************************************************
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

            unsigned int id;
            array<unsigned int, 3> vertices;
            array<unsigned int, 3> edges;

            converter >> id;
            for (unsigned int i = 0; i < 3; i++)
                converter >> vertices[i];
            for (unsigned int i = 0; i < 3; i++)
                converter >> edges[i];

            mesh.Cell2DsId.push_back(id);
            mesh.Cell2DsVertices.push_back(vertices);
            mesh.Cell2DsEdges.push_back(edges);
        }

        return true;
    }
}
