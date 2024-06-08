#pragma once
#include <GL/glut.h>
#include <string>
#include "color.h"

#define INACTIVE_COLOR 0
#define BLACK 100
#define WHITE 101
#define RED 102
#define BLUE 103
#define GREEN 105
#define PURPLE 106
#define ORANGE 107
#define BROWN  108
#define YELLOW 109
#define PINK 110
#define NUMBERPRIMITIVES_COLOR 10



float r;
float g;
float b;

// Globals.

static int primitive_color = INACTIVE_COLOR; // Current drawing primitive.




// Function to draw point selection box in left selection area.
void drawblackBox(void)
{
    if (primitive_color == BLACK)
    {
        glColor3f(0.201, 0.201, 0.201); // Highlight.
        r = 0.05; g = 0.05; b = 0.05;
    }
    else glColor3f(0.05, 0.05, 0.05); // No highlight.

    

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.92 * width, 0.92 * height,  width, height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.92 * width, 0.92 * height,  width, height);


}



void drawwhiteBox(void)
{
    if (primitive_color == WHITE)
    {

        glColor3f(1.0, 1.0, 1.0); // Highlight.
        r = 0.95; g = 0.95; b = 0.95;
    }
    else glColor3f(0.95, 0.95, 0.95); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.84 * width, 0.92 * height, 0.92 * width, height);

    

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.84 * width, 0.92 * height, 0.92 * width, height);


}



void drawredBox(void)
{
    if (primitive_color == RED)
    {
        glColor3f(4.0, 0.0, 0.0); // Highlight.
        r = 0.95; g = 0.0; b = 0.0;
    }
    else glColor3f(0.95, 0.0, 0.0); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.76 * width, 0.92 * height, 0.84 * width, height);

    

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.76 * width, 0.92 * height, 0.84 * width, height);


}





void drawblueBox(void)
{
    if (primitive_color == BLUE)
    {
        glColor3f(0.0, 0.0, 0.8); // Highlight.
        r = 0.0; g = 0.0; b = 1.0;
    }
    else glColor3f(0.0, 0.0, 1.0); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.68 * width, 0.92 * height, 0.76 * width, height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.68 * width, 0.92 * height, 0.76 * width, height);


}


void drawgreenBox(void)
{
    if (primitive_color == GREEN)
    {
        glColor3f(0.0, 0.8, 0.0); // Highlight.
        r = 0.0; g = 1.0; b = 0.0;
    }
    else glColor3f(0.0, 1.0, 0.0); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.60 * width, 0.92 * height, 0.68 * width, height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.60 * width, 0.92 * height, 0.68 * width, height);


}

void drawpurpleBox(void)
{
    if (primitive_color == PURPLE)
    {
        glColor3f(0.5, .0, 0.5); // Highlight.
        r = 0.45; g = 0.0; b = 0.45;
    }

    else glColor3f(0.45, 0.0, 0.45); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.52 * width, 0.92 * height, 0.6 * width, height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.52 * width, 0.92 * height, 0.6 * width, height);


}


void draworangeBox(void)
{
    if (primitive_color == ORANGE)
    {
        glColor3f(1.0, 0.45, 0.0); // Highlight.
        r = 0.95; g = 0.40; b = 0.0;
    }

    else glColor3f(0.95, 0.40, 0.0); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.44 * width, 0.92 * height, 0.52 * width, height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.44 * width, 0.92 * height, 0.52 * width, height);


}


void drawbrownBox(void)
{
    if (primitive_color == BROWN)
    {
        glColor3f(0.65, 0.40, 0.0); // Highlight.
        r = 0.6; g = 0.35; b = 0.0;
    }

    else glColor3f(0.60, 0.35, 0.0); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.36 * width, 0.92 * height, 0.44 * width, height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.36 * width, 0.92 * height, 0.44 * width, height);


}

void drawyellowBox(void)
{
    if (primitive_color == YELLOW)
    {
        glColor3f(1.0, 1.0, 0.0); // Highlight.
        r = 0.95; g = 0.95; b = 0.0;
    }

    else glColor3f(0.95, 0.95, 0.0); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.28 * width, 0.92 * height, 0.36 * width, height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.28 * width, 0.92 * height, 0.36 * width, height);


}


void drawpinkBox(void)
{
    if (primitive_color == PINK)
    {
        glColor3f(1.0, 0.75, 0.85); // Highlight.
        r = 0.95; g = 0.7; b = 0.8;
    }
    else glColor3f(0.95, 0.7, 0.8); // No highlight.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.20 * width, 0.92 * height, 0.28 * width, height);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.2 * width, 0.92 * height, 0.28 * width, height);


}
