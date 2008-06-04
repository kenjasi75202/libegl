/*
	Código adaptado de http://www.codeproject.com/KB/recipes/geometry.aspx
	Autor: Chris Maunder
	Site: Code Project - http://www.codeproject.com
*/
#include "engcomp_glib.h"
#include <stdlib.h>
#include <algorithm>
#include <functional>
#include <math.h>
#include <float.h>

CPolygon::CPolygon()
{
}

CPolygon::~CPolygon()
{
	RemoveAll();
}

void CPolygon::RemoveAll()
{
	m_point3D.clear();
}

void CPolygon::Add(POINT_3D P)
{
	m_point3D.push_back(P);
}

bool CPolygon::PointIn(POINT_3D P)
// Tests if point within polygon, or on an edge or vertex, by shooting a ray along x axis
{
	int     j, inside_flag, xflag0 ;
	double    dv0 ;
	int     crossings, yflag0, yflag1 ;
	POINT_3D Vertex0, Vertex1;

	Vertex0 = m_point3D[GetSize()-1];

	/* get test bit for above/below Y axis */
	yflag0 = ( dv0 = Vertex0.y - P.y ) >= 0.0 ;

	crossings = 0 ;
	for ( j = 0 ; j < GetSize() ; j++ ) {

		// cleverness:  bobble between filling endpoints of edges, so
		// that the previous edge's shared endpoint is maintained.
		if ( j & 0x1 ) {
			Vertex0 = m_point3D[j] ;
			yflag0 = ( dv0 = Vertex0.y - P.y ) >= 0.0 ;
		} else {
			Vertex1 = m_point3D[j] ;
			yflag1 = ( Vertex1.y >= P.y ) ;
		}

		/* check if points not both above/below X axis - can't hit ray */
		if ( yflag0 != yflag1 ) {
			/* check if points on same side of Y axis */
			if ( ( xflag0 = ( Vertex0.x >= P.x ) ) == ( Vertex1.x >= P.x ) ) {

				if ( xflag0 ) crossings++ ;
			} else {
				/* compute intersection of pgon segment with X ray, note
				* if > point's X.
				*/
				crossings += (Vertex0.x -
					dv0*( Vertex1.x-Vertex0.x)/(Vertex1.y-Vertex0.y)) >= P.x ;
			}
		}
	}

	// test if crossings is odd
	// if all we care about is winding number > 0, then just:
	//       inside_flag = crossings > 0;

	inside_flag = crossings & 0x01 ;

	return (inside_flag) ;
}
void CPolygon::BoundingBox(POINT_3D &bottomLeft, POINT_3D &topRight)
{
	double minX(m_point3D[0].x);
	double minY(m_point3D[0].y);
	double maxX(m_point3D[0].x);
	double maxY(m_point3D[0].y);
	std::vector<POINT_3D>::iterator it;
	for(it = m_point3D.begin(); it != m_point3D.end(); it++)
	{
		if(it->x < minX)
			minX = it->x;
		if(it->x >= maxX)
			maxX = it->x;
		if(it->y < minY)
			minY = it->y;
		if(it->y >= maxY)
			maxY = it->y;
	}
	bottomLeft.x = minX;
	bottomLeft.y = minY;
	topRight.x = maxX;
	topRight.y = maxY;
}
