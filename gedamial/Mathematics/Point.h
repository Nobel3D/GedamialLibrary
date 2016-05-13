#ifndef POINT_H
#define POINT_H

class Point
{
private:
	float x;
	float y;

public:
	Point(float xCoord, float yCoord);

	/* GETTER METHODS */
	float getX();
	float getY();

	/* SETTER METHODS */
	void setX(float xCoord);
	void setY(float yCoord);

	~Point();
};
#endif

