#include "MainWin.hpp"
#include <simge/glut/Point.hpp>
#include <iostream>

using namespace simge;
using namespace simge::geom;
using namespace simge::glut;
using namespace simge::util;

namespace
{
    GLfloat LightAmbient[]  = {0.5f, 0.5f, 0.5f, 1.0f}; 
    GLfloat LightDiffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f}; 
    GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f};
} // namespace <unnamed>

MainWin::MainWin(geom::Point<3> const* triangle, geom::Point<3> const* line, geom::Point<3> const& dot)
: Window("Line-Plane Intersection", GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH), dot_(dot), rot_(0)
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0, 0, 0, 0);
    glClearDepth(1);
    glPointSize(5);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    for(int i = 0; i < 3; ++i)
    {
        triangle_[i] = triangle[i];
    }
    
    for(int i = 0; i < 2; ++i)
    {
        line_[i] = line[i];
    }
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0, -1, -4);
    glRotatef(rot_, 0, 1, 0);
    
    glColor3f(1, 0.5, 0.8);

    void (*vertexer)(Point<3> const&) = &vertex;

    glBegin(GL_POINTS);
    std::for_each(&triangle_[0], &triangle_[3], vertexer);
    std::for_each(&line_[0], &line_[2], vertexer);
    glEnd();
    
    glColor3f(1, 0, 0);
    
    glBegin(GL_TRIANGLES);
    std::for_each(&triangle_[0], &triangle_[3], vertexer);
    glEnd();
    
    glColor3f(0, 1, 0);
    
    glBegin(GL_LINES);
    std::for_each(&line_[0], &line_[2], vertexer);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_POINTS);
    vertex(dot_);
    glEnd();
    
    glutSwapBuffers();
}

void MainWin::reshapeGL(int width, int height)
{
    if(height == 0)
    {
        height = 1;
    }
    
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, static_cast<double>(width) / static_cast<double>(height), 0.1, 400);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    setSize(640, 480);
}

void MainWin::mouseGL(int button, int state, int x, int y)
{
}

void MainWin::keyboardGL(unsigned char key, int x, int y)
{
    if(key == 27)
    {
        exit(0);
    }

    if(key == 'a')
    {
        rot_ += 1;
    }
    
    if(key == 'z')
    {
        rot_ -= 1;
    }

    invalidate();
}
