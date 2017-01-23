#include "MainWin.hpp"
#include <algorithm>
#include <sstream>
#include <simge/geom/Operations.hpp>
#include <simge/util/Utility.hpp>
#include <simge/geom/Edge.hpp>
#include "LegalNGon.hpp"

using namespace simge::geom;
using namespace simge::glut;
using namespace simge::util;

MainWin::MainWin()
: Planar("N-gon Validation", GLUT_RGBA | GLUT_DOUBLE),
  polygon_(PolygonType::LeftIsInterior()), finished_(false)
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(620, 460);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawLineLoop(polygon_);
    
    // Status line
    glLineWidth(3);
    glColor3f(0.4, 0.7, 0.2);
    glBegin(GL_LINES);
    glVertex2i(0, 30);
    glVertex2i(getWidth(), 30);
    glEnd();

    glLineWidth(1);
    glColor3f(1, 0, 0);

    if(finished_)
    {
        if(isLegalNgon(polygon_))
        {
            std::ostringstream oss;
            oss << "Polygon is a legal " << polygon_.size() << "-gon. Press `n' for new polygon.";
            writeMessage(oss.str());
        }
        else
        {
            writeMessage("Polygon is not a legal n-gon! Press `n' for new polygon.");
        }
    }
    else
    {
        writeMessage("Enter polygon vertexes by left button in "
                     "clockwise direction. Finish by clicking right button.");
    }
    
    glutSwapBuffers();
}

void MainWin::mouseGL(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        if(button == GLUT_RIGHT_BUTTON)
        {
            if(!finished_)
            {
                finished_ = true;
                invalidate();
            }
        }
        else if(button == GLUT_LEFT_BUTTON)
        {
            if(!finished_)
            {
                polygon_.addVertex(windowToGl(x, y));
            }
            
            invalidate();
        }
    }
}

void MainWin::keyboardGL(unsigned char key, int x, int y)
{
    if((key == 'n' || key == 'N') && finished_)
    {
        finished_ = false;
        polygon_.clear();
        invalidate();
    }

    Planar::keyboardGL(key, x, y);
}

void MainWin::writeMessage(char const* msg)
{
    drawText(GLUT_BITMAP_8_BY_13, point(10, 10), msg);
}

void MainWin::writeMessage(std::string const& msg)
{
    drawText(GLUT_BITMAP_8_BY_13, point(10, 10), msg.c_str());
}
