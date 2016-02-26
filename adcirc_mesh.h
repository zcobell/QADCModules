/*-------------------------------GPL-------------------------------------//
//
// ADCMESH - A library for working with ADCIRC models
// Copyright (C) 2016  Zach Cobell
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------*/
/**
 * \class adcirc_mesh
 *
 * \brief Class that describes an ADCIRC mesh
 *
 * \author Zach Cobell
 *
 * The ADCIRC mesh class is a set of routines that is designed to read/write
 * ADCIRC format meshes. The setup is such that it can be easily manipulated
 * so that codes/routines can be written using this class to manipulate meshes
 *
 * Contact: zcobell@gmail.com
 *
 */
#ifndef ADCIRC_MESH_H
#define ADCIRC_MESH_H


#include <QObject>
#include <QVector>
#include <QFile>
#include <QMap>

#include "QADCModules_global.h"
#include "adcirc_node.h"
#include "adcirc_element.h"
#include "adcirc_boundary.h"
#include "adcirc_errors.h"


class QADCMODULESSHARED_EXPORT adcirc_mesh : public QObject
{
    Q_OBJECT

public:

    explicit adcirc_mesh(QObject *parent = 0);

    //...Public variables...//

    ///Filename for this ADCIRC mesh
    QString                            filename;

    ///Title, or header, from the mesh file
    QString                            title;

    ///Number of elements contained within the mesh file
    int                                numElements;

    ///Number of nodes contained with the mesh file
    int                                numNodes;

    ///Vector made up of the class adcirc_node with x, y, and z information for nodes in this mesh
    QVector<adcirc_node*>              nodes;

    ///Vector made up of the class adcirc_element with connectivity information
    QVector<adcirc_element*>           elements;

    ///Number of open boundary conditions contained within the mesh
    int                                numOpenBoundaries;

    ///Total number of open boundary nodes in this mesh
    int                                totNumOpenBoundaryNodes;

    ///Number of land boundary conditions within the mesh
    int                                numLandBoundaries;

    ///Total number of land boundary nodes in this mesh
    int                                totNumLandBoundaryNodes;

    ///Vector made up of the class adcirc_boundary with the open boundary information
    QVector<adcirc_boundary*>          openBC;

    ///Vector made up of the class adcirc_boundary with the land boundary information
    QVector<adcirc_boundary*>          landBC;

    ///adcirc_error class to track the error codes generated by routines in this class
    adcirc_errors*                     error;


    //...Public functions...///

    int read();
    int read(QString inputFile);

    int write(QString outputFile);

    int setIgnoreMeshNumbering(bool value);


private:

    //...PRIVATE VARIABLES...//

    ///Variable that is checked to decide if non-sequential mesh numbering is a fatal error. Default = false
    bool ignoreMeshNumbering;

    ///Variable that lets other portions of the code know if the mesh is correctly numbered or not
    bool meshNeedsNumbering;

    ///Map function between a node ID and its position in the node vector
    QMap<int,int> nodeMapping;

    ///Map function between an element ID and its position in the element vector
    QMap<int,int> elementMapping;


protected:

    //...PROTECTED FUNCTIONS...//

    int readMesh();

    int writeMesh(QString filename);

    int allocateNodes();

    int allocateElements();

    int readOpenBoundaries(int &position, QStringList &fileData);

    int readLandBoundaries(int &position, QStringList &fileData);

};

#endif // ADCIRC_MESH_H
