#if !defined(POINT_H)
#define POINT_H

class Point
{
public:
	
	int X;
	int Y;

	
	Point();
	Point(int x, int y);
	virtual ~Point();
	double Distance(Point* other);
};

#endif
#pragma once
