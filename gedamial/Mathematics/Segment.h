#ifndef SEGMENT_H
#define SEGMENT_H
#include "Point.h"

class Segment
{
private:
	Point A;
	Point B;

public:
	Segment(Point vertex1, Point vertex2);

	~Segment();
};
#endif 
