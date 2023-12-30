#pragma once

#include <cstdlib>
#include <vector>
#include <iostream>
#include <GL/glut.h>


#define INACTIVE 0
#define POINT 1
#define LINE 2
#define RECTANGLE 3
#define CIRCLE 4
#define NUMBERPRIMITIVES 5






// Point class.
class Point
{
public:
	Point(int xVal, int yVal)
	{
		x = xVal; y = yVal;
	}
	void drawPoint(void); // Function to draw a point.
private:
	int x, y; // x and y co-ordinates of point.
	static float size; // Size of point.
};


// Line class.
class Line
{
public:
	Line(int x1Val, int y1Val, int x2Val, int y2Val)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
	}
	void drawLine();
private:
	int x1, y1, x2, y2; // x and y co-ordinates of endpoints.
};



// Rectangle class.
class Rect
{
public:
	Rect(int x1Val, int y1Val, int x2Val, int y2Val)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
	}
	void drawRectangle();
private:
	int x1, y1, x2, y2; // x and y co-ordinates of diagonally opposite vertices.
};


//circle class
class Circle
{
public:
	Circle(int x1Val, int y1Val, int x2Val, int y2Val)
	{
		x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val; 
	}
	void drawCircle();
private:
	int x1, y1, x2, y2 ;  // x and y co-ordinates of diagonally opposite vertices.
	
};


class Pen
{
public:
	Pen();
	void draw();
	static void mouseControl(int button, int state, int x, int y);
	static void mouseMotion(int x, int y);
	static void clean();

	//static std::vector<Pen> drawings; // Make drawings public

private:
	std::vector<std::pair<int, int>> penCoordinates;
};


