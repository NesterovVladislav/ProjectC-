#ifndef __FabrikaShape_H_
#define __FabrikaShape_H_

#include "Container.h"
#include "Shapes.h"

class Fabrika{
public:
	Shape * CreaterPoint(){
		Shape * point = new Point( double( rand() % 100 ), double( rand() % 100 ) );
		return point;
	}
	Shape * CreatervCircle( size_t & iSize ){
		Point centre( double( rand() % 100 ), double( rand() % 100 ) );
		iSize += 1;
		Shape * circle = new Circle( centre, double( rand() % 100 ) );
		return circle;
	}
	Shape * CreaterRect( size_t & iSize ){
		Point firstVertex( double( rand() % 100 ), double( rand() % 100 ) );
		Point secondVertex( double( rand() % 100 ), double( rand() % 100 ) );
		iSize += 2;
		Shape * rect = new Rect( firstVertex, secondVertex );
		return rect;
	}
	Shape * CreaterSquare( size_t & iSize ){
		Point vertex( double( rand() % 100 ), double( rand() % 100 ) );
		iSize += 1;
		Shape * square = new Square( vertex,  double( rand() % 100 ) );
		return square;
	}
	Shape * CreaterPolyline( size_t & iSize ){
		Polyline * polyline = new Polyline();
		size_t numberVertexes = 3 + rand() % 5;
		iSize += numberVertexes;
		for ( size_t i = 0; i < numberVertexes; ++i ){
			Point vertex( double( rand() % 100 ), double( rand() % 100 ) );
			polyline->AddPoint( vertex );
		}
		return polyline;
	}
	Shape * CreaterPolygon( size_t & iSize ){
		Polygon * polygon = new Polygon();
		size_t numberVertexes = 3 + rand() % 5;
		iSize += numberVertexes;
		for ( size_t i = 0; i < numberVertexes; ++i ){
			Point  vertex( double( rand() % 100 ), double( rand() % 100 ) );
			polygon->AddPoint( vertex );
		}
		return polygon;
	}
};
#endif // __FabrikaShape_H_