#ifndef __Shapes_H_
#define __Shapes_H_

#define _USE_MATH_DEFINES 
#include <math.h>

#include "Base.h"
#include "Container.h"

class Shape : virtual public Printable{
public:
	Shape(){
		GetCount(1);
	}
	static size_t GetCount( int iDelta = 0 ){
		static size_t size = 0;
		return size += iDelta;
	}
	virtual ~Shape(){ 
		GetCount( -1 );
	}
};

class Point : public Shape, public Named{
public:
	Point( double iX, double iY ) 
		: Named( "Point" )
		, m_x( iX )
		, m_y( iY )
	{}
	Point(  Point const & iPoint )
		: Named( "Point" )
	{ m_x = iPoint.GetX(); m_y = iPoint.GetY(); }
	double GetX() const { return m_x; }
	double GetY() const { return m_y; }
	void Print() const {
		Named::Print();
		std::cout << *this << '\n' << '\n';
	}
	friend std::ostream & operator << ( std::ostream & iStream,  Point const & iPoint );
private:
	double m_x;
	double m_y;
};

std::ostream & operator << ( std::ostream & iStream,  Point const & iPoint ) {
	return iStream << '(' << iPoint.m_x << ',' << iPoint.m_y << ')';
}

class Circle : public Shape, public Named{
public:
	Circle( Point const & iCenter, double iRadius )
		: Named( "Circle" )
		, m_centre( iCenter )
		, m_radius( iRadius )
	{
		m_area = M_PI * pow( m_radius, 2 );
	}
	void Print() const {
		Named::Print();
		std::cout << *this << '\n' << '\n';
	}
	friend std::ostream & operator << ( std::ostream & iStream, Circle const & iCircle );
private:
	Point  m_centre;
	double m_radius;
	double m_area;
};
std::ostream & operator << ( std::ostream & iStream, Circle const & iCircle ) {
	return iStream << "centre = " << iCircle.m_centre<< '\t' << "radius=" << iCircle.m_radius << '\t' << "area=" << iCircle.m_area;
}

class Rect : public Shape, public Named{
public:
	Rect( Point const & iFirstvertex, Point const & iSecondvertex )
		: Named( "Rect" )
		, m_firstVertex( iFirstvertex )
		, m_secondVertex( iSecondvertex )
	{
		double length = abs( m_firstVertex.GetX() - m_secondVertex.GetX() );
		double breadth = abs( m_firstVertex.GetY() - m_secondVertex.GetY() );
		m_area = length * breadth;
		m_perimeter = 2 * length + 2 * breadth;
	}
	void Print() const {
		Named::Print();
		std::cout << *this << '\n' << '\n';
	}
	friend std::ostream & operator << ( std::ostream & iStream, Rect const & iRect );
private:
	Point m_firstVertex;
	Point m_secondVertex;
	double m_area;
	double m_perimeter;
};
std::ostream & operator << ( std::ostream & iStream, Rect const & iRect ) {
	return iStream << "area = " << iRect.m_area << '\t' << "perimeter = " << iRect.m_perimeter;
}

class Square : public Shape, public Named{
public:
	Square( Point const & iVertex, double iLengthSide )
		: Named( "Square" )
		, m_vertex( iVertex )
		, m_lengthSide( iLengthSide )
	{
		m_area = pow( m_lengthSide, 2 );
		m_perimeter = 4 * m_lengthSide;
	}
	void Print() const {
		Named::Print();
		std::cout << *this << '\n' << '\n';
	}
	friend std::ostream & operator << ( std::ostream & iStream, Square const & iSquare );
private:
	Point m_vertex;
	double m_lengthSide;
	double m_area;
	double m_perimeter;
};
std::ostream & operator << ( std::ostream & iStream, Square const & iSquare ) {
	return iStream << "area = " << iSquare.m_area << '\t' << "perimeter = " << iSquare.m_perimeter;
}

class Polyline : public Shape, public Named{
public:
	Polyline()
		: Named( "Polyline" )
	{
		m_lenght = 0;
		m_vertexes = new  Container < Point > ;
	}
	void AddPoint( Point const & iPoint ){
		Point const * tailPoint = m_vertexes->GetTail();
		if ( m_vertexes->GetSize() > 0 ){
			m_lenght += sqrt( pow( iPoint.GetX() - tailPoint->GetX(), 2 ) + pow( iPoint.GetY() - tailPoint->GetY(), 2 ) );
		}
		m_vertexes->PushBack( iPoint );
	}
	~Polyline(){
		delete m_vertexes;
	}
	void Print() const {
		if ( m_vertexes->GetSize() < 2 ){
			throw std::invalid_argument( "The broken line should contain more than 1 point." );
		}
		Named::Print();
		std::cout << *this << '\n' << '\n';
	}
	friend std::ostream & operator << ( std::ostream & iStream, Polyline const & iPolyline );
private:
	Container< Point > * m_vertexes;
	double m_lenght;
};
std::ostream & operator << ( std::ostream & iStream, Polyline const & iPolyline ) {
	return iStream << "lenght = " << iPolyline.m_lenght;
}

class Polygon : public Shape, public Named{
public:
	Polygon()
		: Named( "Polygon" )
	{
		m_vertexes = new  Container < Point >;
		m_perimeter = 0;
	}
	void AddPoint( Point const& iPoint ){
		Point const * tailPoint = m_vertexes->GetTail();
		if ( m_vertexes->GetSize() > 0 ){
			m_perimeter += sqrt( pow( iPoint.GetX() - tailPoint->GetX(), 2 ) + pow( iPoint.GetY() - tailPoint->GetY(), 2 ) );
		}
		m_vertexes->PushBack( iPoint );
	}
	~Polygon(){
		delete m_vertexes;
	}
	void Print() const {
		if ( m_vertexes->GetSize() < 3 ){
			throw std::invalid_argument( "Polygon has to contain more than 2 points." );
		}
		Named::Print();
		std::cout << *this << '\n' << '\n' << '\n';
	}
	friend std::ostream & operator << ( std::ostream & iStream, Polygon const & iPolygon );
private:
	Container< Point > * m_vertexes;
	double m_perimeter;
};
std::ostream & operator << ( std::ostream & iStream, Polygon const & iPolygon ) {
	Point const * headVertex = iPolygon.m_vertexes->GetHead();
	Point const * tailVertex = iPolygon.m_vertexes->GetTail();
	return iStream << "perimeter = " << iPolygon.m_perimeter + sqrt( pow( headVertex->GetX() - tailVertex->GetX(), 2 ) + pow( headVertex->GetY() - tailVertex->GetY(), 2 ) );
}
#endif // __Shapes_H_