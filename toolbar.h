#pragma once
#include <GL/glut.h>
#include <string>


#define INACTIVE 0
#define POINT 1
#define LINE 2
#define RECTANGLE 3
#define CIRCLE 4
#define PEN 5
#define COPY 6
#define NUMBERPRIMITIVES 6


// Globals.
static int width, height; // OpenGL window size.
static float pointSize = 4.0; // Size of point
static int primitive = INACTIVE; // Current drawing primitive.
static int pointCount = 0; // Number of  specified points.
static int tempX, tempY; // Co-ordinates of clicked point.
static int isGrid = 1; // Is there grid?



// Function to draw point selection box in left selection area.
void drawPointSelectionBox(void)
{
    if (primitive == POINT) glColor3f(1.0, 1.0, 1.0); // Highlight.
    else glColor3f(0.81, 0.81, 0.81); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.9 * height, 0.1 * width, height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.9 * height, 0.1 * width, height);

    // Draw point icon.
    glPointSize(pointSize);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex3f(0.05 * width, 0.95 * height, 0.0);
    glEnd();
}

// Function to draw line selection box in left selection area.
void drawLineSelectionBox(void)
{
    if (primitive == LINE) glColor3f(1.0, 1.0, 1.0); // Highlight.
    else glColor3f(0.8, 0.8, 0.8); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.8 * height, 0.1 * width, 0.9 * height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.8 * height, 0.1 * width, 0.9 * height);

    // Draw line icon.
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.025 * width, 0.825 * height, 0.0);
    glVertex3f(0.075 * width, 0.875 * height, 0.0);
    glEnd();
}

// Function to draw rectangle selection box in left selection area.
void drawRectangleSelectionBox(void)
{
    if (primitive == RECTANGLE) glColor3f(1.0, 1.0, 1.0); // Highlight.
    else glColor3f(0.8, 0.8, 0.8); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.7 * height, 0.1 * width, 0.8 * height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.7 * height, 0.1 * width, 0.8 * height);

    // Draw rectangle icon.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.025 * width, 0.735 * height, 0.075 * width, 0.765 * height);
    //glEnd();
}

void drawCircleSelectionBox(void)
{
    #define PI 3.14159265358979324


    if (primitive == CIRCLE) glColor3f(1.0, 1.0, 1.0); // Highlight.
    else glColor3f(0.801, 0.801, 0.801); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.6 * height, 0.1 * width, 0.7 * height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.6 * height, 0.1 * width, 0.7 * height);

    // Draw circle icon.
    glColor3f(0.0, 0.0, 0.0);
    static double R; // Radius of circle.
    static int numVertices = 20; // Number of vertices on circle.
    float t = 0; // Angle parameter.
    int i;

    // Draw a line loop with vertices at equal angles apart on a circle
    // with center at (X, Y) and radius R, The vertices are colored randomly.
    double cx = (0.035 * width + 0.0 * width) / 2;
    double cy = (0.635 * height + 0.665 * height) / 2;

    R = sqrt(pow(0.035 * width - 0.0 * width, 2) + pow(0.665 * height - 0.635 * height, 2)) / 2;

    glBegin(GL_LINE_LOOP);
    for (i = 0; i < numVertices; ++i)
    {
        glColor3f(0.0, 0.0, 0.0);
        glVertex3f(0.05 * width + R * cos(t), 0.65 * height + R * sin(t), 0.0);
        t += 2 * PI / numVertices;
    }
    glEnd();
}


void drawString(const std::string& str, float x, float y)
{
    glRasterPos2f(x, y);

    for (const char& c : str)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}
// Function to draw line selection box in left selection area.
void drawBox(void)
{
    if (primitive == PEN) glColor3f(1.0, 1.0, 1.0); // Highlight.
    else glColor3f(0.8, 0.8, 0.8); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.5 * height, 0.1 * width, 0.6 * height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.5 * height, 0.1 * width, 0.6 * height);

    // Draw line icon.
    glColor3f(0.0, 0.0, 0.0);
    std::string message = "PEN";
    float x = (0.025 * width);
    float y =(0.545 * height);
    drawString(message,x,y);
    glutSwapBuffers();
    glEnd();
}


void drawcopyBox(void)
{
    if (primitive == COPY) glColor3f(1.0, 1.0, 1.0); // Highlight.
    else glColor3f(0.8, 0.8, 0.8); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.4 * height, 0.1 * width, 0.5 * height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.4 * height, 0.1 * width, 0.5 * height);

    // Draw line icon.
    glColor3f(0.0, 0.0, 0.0);
    std::string message = "COPY";
    float x = (0.015 * width);
    float y = (0.445 * height);
    drawString(message, x, y);
    glutSwapBuffers();
    glEnd();
}
