////////////////////////////////////////////////////////////////////////////////////        
// canvas.cpp
//
// This program allows the user to draw simple shapes on a canvas.
//
// Interaction:
// Left click on a box on the left to select a primitive.
// Then left click on the drawing area: once for point, twice for line or rectangle.
// Right click for menu options.
//
//  Sumanta Guha.
//////////////////////////////////////////////////////////////////////////////////// 

#include <cstdlib>
#include <vector>
#include <iostream>

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif


#  include "classes.h"
#  include "toolbar.h"
#  include "color.h"
#  include "color_palette.h"



#define PI 3.141592653589793241

bool isSelecting = false; // Flag to indicate if the user is currently selecting a region
bool isCopying = false;   // Flag to indicate if the user is currently copying
bool isPasting = false;   // Flag to indicate if the user is currently pasting
int startX, startY;      // Starting coordinates of the selection rectangle
int endX, endY;          // Ending coordinates of the selection rectangl


int cursorX;
int cursorY;


int windowWidth = 800;   // Width of the window
int windowHeight = 600;  // Height of the window


using namespace std;



// Use the STL extension of C++.
using namespace std;

// Structure to store the coordinates
struct Coordinate
{
	float x, y;
};
std::vector<Coordinate> penCoordinates;





float rc ;
float gc ;
float bc ;


float Point::size = pointSize; // Set point size.

// Function to draw a point.
void Point::drawPoint()
{  
	glPointSize(size);
	glBegin(GL_POINTS);
	glColor3f(r, g, b);
	glVertex3f(x, y, 0.0);
	glEnd();

}

// Vector of points.
vector<Point> points;

// Iterator to traverse a Point array.
vector<Point>::iterator pointsIterator; 

// Function to draw all points in the points array.
void drawPoints(void)
{
   // Loop through the points array drawing each point.
   pointsIterator = points.begin();
   while(pointsIterator != points.end() )
   {
      pointsIterator->drawPoint();
	  pointsIterator++;
   }
}



// Function to draw a line.
void Line::drawLine()
{

	glBegin(GL_LINES);
	glColor3f(r,g,b);
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y2, 0.0);

	glEnd();
	

	
}

// Vector of lines.
vector<Line> lines;


// Iterator to traverse a Line array.
vector<Line>::iterator linesIterator;

// Function to draw all lines in the lines array.
void drawLines(void)
{

   // Loop through the lines array drawing each line.
   linesIterator = lines.begin();
   
   while(linesIterator != lines.end() )
   {

      linesIterator->drawLine();
	  linesIterator++;
   }

}



// Function to draw a rectangle.
void Rect::drawRectangle()
{
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glColor3f(r, g, b);
   glRectf(x1, y1, x2, y2);
}

// Vector of rectangles.
vector<Rect> rectangles;

// Iterator to traverse a Rect array.
vector<Rect>::iterator rectanglesIterator;

// Function to draw all rectangles in the rectangles array.
void drawRectangles(void)
{
   // Loop through the rectangles array drawing each rectangle.
   rectanglesIterator = rectangles.begin();
   while(rectanglesIterator != rectangles.end() )
   {
      rectanglesIterator->drawRectangle();
	  rectanglesIterator++;
   }
}


// Function to draw a circle.
void Circle::drawCircle()
{
    double R ; // Radius of circle.
	static int numVertices = 70; // Number of vertices on circle.
	float t = 0; // Angle parameter.
	int i;

	// Draw a line loop with vertices at equal angles apart on a circle
	// with center at (X, Y) and radius R, The vertices are colored randomly.
	double cx = (x1 + x2)/2;
	double cy = (y1 + y2)/2;
	
	R = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) / 2;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i < numVertices; ++i)
	{
		glColor3f(r, g, b);
		glVertex3f(cx + R * cos(t), cy + R * sin(t), 0.0);
		t += 2 * PI / numVertices;
	}
	glEnd();

}

// Vector of rectangles.
vector<Circle> circles;

// Iterator to traverse a Circle array.
vector<Circle>::iterator circlesIterator;

// Function to draw all circles in the circles array.
void drawCircles(void)
{
	// Loop through the circles array drawing each circle.
	circlesIterator = circles.begin();
	while (circlesIterator != circles.end())
	{
		circlesIterator->drawCircle();
		circlesIterator++;
	}
}



std::vector<Pen> drawings;
/*std::vector<std::pair<int, int>> penCoordinates*/;

Pen::Pen()
{
}

void Pen::draw()
{
	glBegin(GL_LINE_STRIP);
	glColor3f(r, g, b); // Set color 

	// Draw the pen coordinates
	for (const auto& coordinate : penCoordinates)
	{
		glVertex2f(static_cast<float>(coordinate.first), static_cast<float>(coordinate.second));
	}

	glEnd();

	glutSwapBuffers();
}




// Function to draw unused part of left selection area.
void drawInactiveArea(void)
{
   glColor3f(0.6, 0.6, 0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.0, 0.1*width, (1 - NUMBERPRIMITIVES*0.1)*height);

   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.0, 0.1*width, (1 - NUMBERPRIMITIVES*0.1)*height);
}

// Function to draw temporary point.
void drawTempPoint(void)
{
   glColor3f(1.0, 0.0, 0.0);
   glPointSize(pointSize);
   glBegin(GL_POINTS);
   glVertex3f(tempX, tempY, 0.0);
   glEnd(); 
}

// Function to draw a grid.
void drawGrid(void)
{
   int i;
   
   glEnable(GL_LINE_STIPPLE);
   glLineStipple(1, 0x5555); 
   glColor3f(0.75, 0.75, 0.75);

   glBegin(GL_LINES);
	  for (i=2; i <=9; i++)
	  {
         glVertex3f(i*0.1*width, 0.0, 0.0);
         glVertex3f(i*0.1*width, height, 0.0);
	  }
	  for (i=1; i <=9; i++)
	  {
         glVertex3f(0.1*width, i*0.1*height, 0.0);
         glVertex3f(width, i*0.1*height, 0.0);
	  }
   glEnd();
   glDisable(GL_LINE_STIPPLE);
}

void drawing()
{
	// Loop through the pens vector and draw each pen.
	for (auto& pen : drawings)
	{
		pen.draw();
	}
}



// Function to pick primitive if click is in left selection area.
void pickPrimitive(int y)
{
   if ( y < (1- NUMBERPRIMITIVES*0.1)*height ) primitive = INACTIVE;
   else if (y <  (1 - 5*0.1)*height) primitive = COPY;
   else if (y <  (1 - 4*0.1)*height) primitive = PEN;
   else if (y <  (1 - 3*0.1)*height ) primitive = CIRCLE;
   else if (y <  (1 - 2*0.1)*height ) primitive = RECTANGLE;
   else if (y <  (1 - 1*0.1)*height ) primitive = LINE;
   else primitive = POINT;
}


// Function to pick primitive if click is in left selection area.
void pickPrimitive_color(int x)
{
	if (x < (1 - 10 * 0.08) * width)primitive_color = INACTIVE_COLOR;
	else if (x < (1 - 9 * 0.08) * width) primitive_color = PINK;
	else if (x < (1 - 7 * 0.08) * width) primitive_color = YELLOW;
	else if (x < (1 - 6 * 0.08) * width) primitive_color = ORANGE;
	else if (x < (1 - 5 * 0.08) * width) primitive_color = PURPLE;
	else if (x < (1 - 4 * 0.08) * width) primitive_color = GREEN;
	else if (x < (1 - 3 * 0.08) * width) primitive_color = BLUE;
	else if (x < (1 - 2 * 0.08) * width) primitive_color = RED;
	else if (x < (1 - 1 * 0.08) * width) primitive_color = WHITE ;
	else primitive_color = BLACK;
}


// The mouse callback routine.
void Pen::mouseControl(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {

      y = height - y; // Correct from mouse to OpenGL co-ordinates.

	  // Click outside canvas - do nothing.
      if ( x < 0 || x > width || y < 0 || y > height ) ;

	  else if (y > 0.92 * height)
	  {
		  pickPrimitive_color(x);
	  }

	  // Click in left selection area.
      else if ( x < 0.1*width ) 
	  {
	     pickPrimitive(y);
		 pointCount = 0;
	  }

	  // Click in canvas.
      else
	  {
	     if (primitive == POINT) points.push_back( Point(x,y) );

         else if (primitive == LINE) 
		 { 
			 
	        if (pointCount == 0)
			{
               tempX = x; tempY = y;
		       pointCount++;
			}
	        else 
			{
               lines.push_back( Line(tempX, tempY, x, y) );
		       pointCount = 0;
			}
		 }

		 else if (primitive == RECTANGLE)
		 {
			 if (pointCount == 0)
			 {
				 tempX = x; tempY = y;
				 pointCount++;
			 }
			 else
			 {
				 rectangles.push_back(Rect(tempX, tempY, x, y));
				 pointCount = 0;
			 }
		 }
		 else if (primitive == CIRCLE)
		 {
			 if (pointCount == 0)
			 {
				 tempX = x; tempY = y;
				 pointCount++;
			 }
			 else
			 {
				 circles.push_back(Circle(tempX, tempY, x, y));
				 pointCount = 0;
			 }
		 }

		 else if (primitive == PEN)
		 {
			 // Create a new pen instance and store it in the drawings vector
			 Pen newPen;
			 drawings.push_back(newPen);

			 // Add the initial mouse position to the pen coordinates
			 drawings.back().penCoordinates.push_back(std::make_pair(x, y));

			 glutMotionFunc(mouseMotion); // Register the mouse motion callback

		 }


		 else if (primitive == COPY)
		 {
			 startX = x;
			 startY = y;
			 endX = x;
			 endY = y;
			 isSelecting = true;

		 }


		 else if (primitive_color == BLACK)
		 {
			 // Create a new color instance
			 Color newcolor;
			 newcolor.blue = b;
			 newcolor.green = g;
			 newcolor.red = r;

			 rc = r;
			 gc = g;
			 bc = b;
		 }

		 else if (primitive_color == WHITE)
		 {
			 // Create a new color instance 
			 Color newcolor;
			 newcolor.blue = b;
			 newcolor.green = g;
			 newcolor.red = r;

			 rc = r;
			 gc = g;
			 bc = b;
		 }

		 else if (primitive_color == RED)
		 {
			 // Create a new color instance 
			 Color newcolor2;
			 newcolor2.blue = b;
			 newcolor2.green = g;
			 newcolor2.red = r;

			 rc = r;
			 gc = g;
			 bc = b;
		 }

		 else if (primitive_color == GREEN)
		 {
		   // Create a new color instance

			 Color newcolor;
			 newcolor.blue = b;
			 newcolor.green = g;
			 newcolor.red = r;

			 rc = r;
			 gc = g;
			 bc = b;
		 }


		 else if (primitive_color == BLUE)
		 {
			 // Create a new color instance 
			 Color newcolor;
			 newcolor.blue = b;
			 newcolor.green = g;
			 newcolor.red = r;

			 rc = r;
			 gc = g;
			 bc = b;
		 }

		 else if (primitive_color == PURPLE)
		 {
			 // Create a new color instance 
			 Color newcolor;
			 newcolor.blue = b;
			 newcolor.green = g;
			 newcolor.red = r;

			 rc = r;
			 gc = g;
			 bc = b;
		 }


		 else if (primitive_color == ORANGE)
		 {
			 // Create a new color instance
			 Color newcolor;
			 newcolor.blue = b;
			 newcolor.green = g;
			 newcolor.red = r;

			 rc = r;
			 gc = g;
			 bc = b;
		 }

		 else if (primitive_color == BROWN)
		 {
			 // Create a new color instance 
			 Color newcolor;
			 newcolor.blue = b;
			 newcolor.green = g;
			 newcolor.red = r;


			 rc = r;
			 gc = g;
			 bc = b;
		 }


		 else if (primitive_color == YELLOW)
		 {
			 // Create a new color instance 
			 Color newcolor;
			 newcolor.blue = b;
			 newcolor.green = g;
			 newcolor.red = r;

			 rc = r;
			 gc = g;
			 bc = b;
		 }


		 else if (primitive_color == PINK)
		 {
			 // Create a new color instance and store it in the drawings vector
			 Color newcolor;
			 newcolor.blue = b;
			 newcolor.green = g;
			 newcolor.red = r;

			 rc = r;
			 gc = g;
			 bc = b;

			 }

	  }
   }

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
	   if (isSelecting) 
	   {
		   isSelecting = false;
		   endX = x;
		   endY = y;
		   // Perform copy operation here
		   isCopying = true;
	   }
		glutMotionFunc(nullptr); // Unregister the mouse motion callback
	}


	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// Perform paste operation here
		isPasting = true;
	}

   glutPostRedisplay();
}







std::vector<GLubyte> capturedPixels;

void copyPixels() {
	// Calculate the coordinates and dimensions of the selected region
	int copyX = std::min(startX, endX);
	int copyY = std::min(startY, endY);
	int copyWidth = std::abs(endX - startX);
	int copyHeight = std::abs(endY - startY);

	// Allocate memory for the captured pixels
	capturedPixels.resize(copyWidth * copyHeight);

	// Read the pixel data from the framebuffer into the capturedPixels vector
	glReadPixels(copyX, copyY, copyWidth, copyHeight, GL_RGBA, GL_UNSIGNED_BYTE, &capturedPixels[0]);
}

void pastePixels(int x, int y) {
	// Set the raster position to the paste coordinates
	glRasterPos2i(x, y);

	// Draw the pixels using glDrawPixels
	int pasteWidth = std::abs(endX - startX);
	int pasteHeight = std::abs(endY - startY);
	glDrawPixels(pasteWidth, pasteHeight, GL_RGBA, GL_UNSIGNED_BYTE, &capturedPixels[0]);
}


void Pen::mouseMotion(int x, int y)
{

	if (isSelecting) 
	{
		endX = x;
		endY = y;
	}

	y = height - y;
	// Add the current mouse position to the pen coordinates
	drawings.back().penCoordinates.push_back(std::make_pair(x, y));

	glutPostRedisplay(); // Trigger a redraw
}



void mouseClick(int button, int state, int x, int y) 
{
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		// Perform paste operation here
		isPasting = true;
	}
}




// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Set viewing box dimensions equal to window dimensions.
   glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);
   
   // Pass the size of the OpenGL window to globals.
   width = w; 
   height = h;  

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch (key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

// Clear the canvas and reset for fresh drawing.

//void Pen::clean()
//{
//	drawings.clear();
//}


void clearAll(void)
{
   points.clear();
   lines.clear();
   rectangles.clear();
   circles.clear();
   drawings.clear();
   primitive = INACTIVE;
   pointCount = 0;
}

// The right button menu callback function.
void rightMenu(int id)
{
   if (id==1) 
   {
	  clearAll();
	  glutPostRedisplay();
   }
   if (id==2) exit(0);
}

// The sub-menu callback function.
void grid_menu(int id)
{
   if (id==3) isGrid = 1;
   if (id==4) isGrid = 0;
   glutPostRedisplay();
}

// Function to create menu.
void makeMenu(void)
{
   int sub_menu;
   sub_menu = glutCreateMenu(grid_menu);
   glutAddMenuEntry("On", 3);
   glutAddMenuEntry("Off",4);

   glutCreateMenu(rightMenu);
   glutAddSubMenu("Grid", sub_menu);
   glutAddMenuEntry("Clear",1);
   glutAddMenuEntry("Quit",2);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0); 

   makeMenu(); // Create menu.
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Left click on a box on the left to select a primitive." << endl
        << "Then left click on the drawing area: once for point, twice for line or rectangle." << endl
        << "Right click for menu options." <<  endl; 
}




// Drawing routine.
void drawScene(void)
{

	// ...

 // Draw the selection rectangle if the user is currently selecting
	if (isSelecting) {
		glColor3f(1.0, 1.0, 1.0); // Set the rectangle color
		glBegin(GL_LINE_LOOP);
		glVertex2i(startX, startY);
		glVertex2i(endX, startY);
		glVertex2i(endX, endY);
		glVertex2i(startX, endY);
		glEnd();
	}

	// Perform copy or paste operations based on the flags
	if (isCopying) {
		copyPixels();
		isCopying = false;
	}

	if (isPasting)
	{
		pastePixels(endX, endY); // Use the ending coordinates of the selection rectangle as the paste coordinates
		isPasting = false;
	}




	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	drawPointSelectionBox();
	drawLineSelectionBox();
	drawRectangleSelectionBox();
	drawCircleSelectionBox();
	drawBox();
	drawcopyBox();





	drawblackBox();
	drawwhiteBox();
	drawredBox();
	drawblueBox();
	drawgreenBox();
	drawpurpleBox();
	draworangeBox();
	drawbrownBox();
	drawyellowBox();
	drawpinkBox();

	drawInactiveArea();

	drawPoints();
	drawLines();
	drawRectangles();
	drawCircles();
	drawing();
	if (((primitive == LINE) || (primitive == RECTANGLE) || (primitive == CIRCLE) || (primitive == PEN)) &&
		(pointCount == 1)) drawTempPoint();

	if (!isGrid) drawGrid();

	// Loop through the pens vector and draw each pen.

	glutSwapBuffers();
}






// Main routine.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);

   glutInitContextVersion(4, 3);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
   glutInitWindowSize(800, 600);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("canvas.cpp");

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 800, 0, 600, -1, 1);
   glMatrixMode(GL_MODELVIEW);

   glutDisplayFunc(drawScene); 
   


   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   //glutMouseFunc(mouseControl); 

   glutMouseFunc(Pen::mouseControl);
   glutMotionFunc(Pen::mouseMotion);
   glutPassiveMotionFunc(Pen::mouseMotion);
   glutMouseFunc(mouseClick);

   glewExperimental = GL_TRUE;
   glewInit();

   setup(); 

   glutMainLoop(); 
}
