/*-------------------------------GPL-------------------------------------//
//
// QADCModules - A library for working with ADCIRC models
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
#include "qkdtree2.h"
#include "boost/array.hpp"
#include "boost/multi_array.hpp"

qKdtree2::qKdtree2(QObject *parent) : QObject(parent)
{
    this->initialized = false;
    this->numDataPoints = 0;
}



//-----------------------------------------------------------------------------------------//
//...Function that constructs a kd-tree for a given X/Y pair
//-----------------------------------------------------------------------------------------//
/**
 * \fn qKdtree2::build(QVector<QPointF> &pointCloud)
 * \brief Generates a kdtree2 search tree
 *
 * \author Zach Cobell
 *
 * @param[in] pointCloud Vector of QPointF used to generate the search tree
 *
 * This function uses the kdtree2 library to generate a search tree
 *
 **/
//-----------------------------------------------------------------------------------------//
int qKdtree2::build(QVector<QPointF> &pointCloud)
{
    int i;
    typedef boost::multi_array<float,2> array2d;

    this->numDataPoints = pointCloud.size();

    array2d data(boost::extents[pointCloud.size()][2]);

    for(i=0;i<pointCloud.size();i++)
    {
        data[i][0] = static_cast<float>(pointCloud[i].x());
        data[i][1] = static_cast<float>(pointCloud[i].y());
    }

    this->tree = QSharedPointer<kdtree2>(new kdtree2(data,true));

    return ERROR_NOERROR;
}
//-----------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------//
//...Function that constructs a kd-tree for a given X/Y pair
//-----------------------------------------------------------------------------------------//
/**
 * \overload qKdtree2::build(QVector<double> &x, QVector<double> &y)
 * \brief Generates a kdtree2 search tree
 *
 * \author Zach Cobell
 *
 * @param[in] x Vector of x-coordinates
 * @param[in] y Vector of y-coordinates
 *
 * This function uses the kdtree2 library to generate a search tree
 *
 **/
//-----------------------------------------------------------------------------------------//
int qKdtree2::build(QVector<double> &x, QVector<double> &y)
{
    int i;
    typedef boost::multi_array<float,2> array2d;

    if(x.size()!=y.size())
        return ERROR_QKDTREE2_SIZEMISMATCH;

    this->numDataPoints = x.size();

    array2d data(boost::extents[x.size()][2]);

    for(i=0;i<x.size();i++)
    {
        data[i][0] = static_cast<float>(x[i]);
        data[i][1] = static_cast<float>(y[i]);
    }

    this->tree = QSharedPointer<kdtree2>(new kdtree2(data,true));

    return ERROR_NOERROR;
}
//-----------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------//
//...Function that constructs a kd-tree for a given X/Y pair
//-----------------------------------------------------------------------------------------//
/**
 * \overload qKdtree2::build(QVector<QVector3D> &pointCloud)
 * \brief Generates a kdtree2 search tree
 *
 * \author Zach Cobell
 *
 * @param[in] pointCloud Vector of QVector3D used to generate the search tree
 *
 * This function uses the kdtree2 library to generate a search tree
 *
 **/
//-----------------------------------------------------------------------------------------//
int qKdtree2::build(QVector<QVector3D> &pointCloud)
{
    int i;
    typedef boost::multi_array<float,2> array2d;

    this->numDataPoints = pointCloud.size();

    array2d data(boost::extents[pointCloud.size()][2]);

    for(i=0;i<pointCloud.size();i++)
    {
        data[i][0] = pointCloud[i].x();
        data[i][1] = pointCloud[i].y();
    }

    this->tree = QSharedPointer<kdtree2>(new kdtree2(data,true));

    return ERROR_NOERROR;
}
//-----------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------//
//...Function that uses a kd-tree to find the nearest point to a given set of coordinates
//-----------------------------------------------------------------------------------------//
/**
 * \fn qKdtree2::findNearest(QPointF pointLocation, int &index)
 * \brief Function that uses a kd-tree to find the nearest point to a given set of coordinates
 *
 * \author Zach Cobell
 *
 * @param[in]  pointLocation  location of point to search for
 * @param[out] index          location in array that created kd-tree of nearest point
 *
 * Function that uses a kd-tree to find the nearest point to a given set of coordinates
 *
 **/
//-----------------------------------------------------------------------------------------//
int qKdtree2::findNearest(QPointF pointLocation, int &index)
{
    kdtree2_result_vector result_vector;
    kdtree2_result        result;
    vector<float>         query(2);

    query[0] = static_cast<float>(pointLocation.x());
    query[1] = static_cast<float>(pointLocation.y());

    this->tree->n_nearest(query,1,result_vector);

    result = result_vector.at(0);
    index  = result.idx;

    return ERROR_NOERROR;
}
//-----------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------//
//...Function that uses a kd-tree to find the nearest point to a given set of coordinates
//-----------------------------------------------------------------------------------------//
/**
 * \overload qKdtree2::findNearest(double x, double y, int &index)
 * \brief Function that uses a kd-tree to find the nearest point to a given set of coordinates
 *
 * \author Zach Cobell
 *
 * @param[in]  x      x-coordinate of point to search for
 * @param[in]  y      y-coordinate of point to search for
 * @param[out] index  location in array that created kd-tree of nearest point
 *
 * Function that uses a kd-tree to find the nearest point to a given set of coordinates
 *
 **/
//-----------------------------------------------------------------------------------------//
int qKdtree2::findNearest(double x, double y, int &index)
{
    int ierr = this->findNearest(QPointF(x,y),index);
    return ierr;
}
//-----------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------//
//...Function that uses a kd-tree to find the nearest point to a given set of coordinates
//-----------------------------------------------------------------------------------------//
/**
 * \overload qKdtree2::findNearest(QVector3D pointLocation, int &index)
 * \brief Function that uses a kd-tree to find the nearest point to a given set of coordinates
 *
 * \author Zach Cobell
 *
 * @param[in]  pointLocation location of point to search for
 * @param[out] index         location in array that created kd-tree of nearest point
 *
 * Function that uses a kd-tree to find the nearest point to a given set of coordinates
 *
 **/
//-----------------------------------------------------------------------------------------//
int qKdtree2::findNearest(QVector3D pointLocation, int &index)
{
    int ierr = this->findNearest(pointLocation.toPointF(),index);
    return ierr;
}
//-----------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------//
//...Function that uses a kd-tree to find the nearest point to a given set of coordinates
//-----------------------------------------------------------------------------------------//
/**
 * \fn qKdtree2::findXNearest(QPointF pointLocation, int nn, QVector<int> &indicies)
 * \brief Function that uses a kd-tree to find the N-nearest point to a given set of coordinates
 *
 * \author Zach Cobell
 *
 * @param[in]  pointLocation  location of point to search for
 * @param[in]  nn             number of locations to find
 * @param[out] indicies       vector of locations in array that created kd-tree of nearest points
 *
 * Function that uses a kd-tree to find the N-nearest point to a given set of coordinates
 *
 **/
//-----------------------------------------------------------------------------------------//
int qKdtree2::findXNearest(QPointF pointLocation, int nn, QVector<int> &indicies)
{
    int                   i;
    kdtree2_result_vector result_vector;
    kdtree2_result        result;
    vector<float>         query(2);

    if(nn>this->numDataPoints)
        nn = this->numDataPoints;

    query[0] = static_cast<float>(pointLocation.x());
    query[1] = static_cast<float>(pointLocation.y());

    this->tree->n_nearest(query,nn,result_vector);

    indicies.resize(nn);

    for(i=0;i<nn;i++)
    {
        result      = result_vector.at(i);
        indicies[i] = result.idx;
    }

    return ERROR_NOERROR;
}
//-----------------------------------------------------------------------------------------//


//-----------------------------------------------------------------------------------------//
//...Function that uses a kd-tree to find the nearest point to a given set of coordinates
//-----------------------------------------------------------------------------------------//
/**
 * \overload qKdtree2::findXNearest(double x, double y, int nn, QVector<int> &indicies)
 * \brief Function that uses a kd-tree to find the N-nearest point to a given set of coordinates
 *
 * \author Zach Cobell
 *
 * @param[in]  x              x-coordinate of point to search for
 * @param[in]  y              y-coordinate of point to search for
 * @param[in]  nn             number of locations to find
 * @param[out] indicies       vector of locations in array that created kd-tree of nearest points
 *
 * Function that uses a kd-tree to find the N-nearest point to a given set of coordinates
 *
 **/
//-----------------------------------------------------------------------------------------//
int qKdtree2::findXNearest(double x, double y, int nn, QVector<int> &indicies)
{
    int ierr = this->findXNearest(QPointF(x,y),nn,indicies);
    return ierr;
}
//-----------------------------------------------------------------------------------------//



//-----------------------------------------------------------------------------------------//
//...Function that uses a kd-tree to find the nearest point to a given set of coordinates
//-----------------------------------------------------------------------------------------//
/**
 * \overload qKdtree2::findXNearest(QVector3D pointLocation, int nn, QVector<int> &indicies)
 * \brief Function that uses a kd-tree to find the N-nearest point to a given set of coordinates
 *
 * \author Zach Cobell
 *
 * @param[in]  pointLocation  location of point to search for
 * @param[in]  nn             number of locations to find
 * @param[out] indicies       vector of locations in array that created kd-tree of nearest points
 *
 * Function that uses a kd-tree to find the N-nearest point to a given set of coordinates
 *
 **/
//-----------------------------------------------------------------------------------------//
int qKdtree2::findXNearest(QVector3D pointLocation, int nn, QVector<int> &indicies)
{
    int ierr = this->findXNearest(pointLocation.toPointF(),nn,indicies);
    return ierr;
}
//-----------------------------------------------------------------------------------------//
