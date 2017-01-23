#include "MainWin.hpp"
#include <algorithm>
#include <simge/geom/Operations.hpp>
#include <simge/util/Utility.hpp>
#include <simge/geom/Edge.hpp>

#include "IsChord.hpp"

using namespace simge::geom;
using namespace simge::glut;
using namespace simge::util;

namespace
{
    void putHandle(Point<2> const& point)
    {
        drawGrabHandle(point, 8);
    }

    void putAllHandles(Polygon<2> const& poly)
    {
        glBegin(GL_LINE_LOOP);
        std::for_each(poly.begin(), poly.end(), &putHandle);
        glEnd();
    }

    bool findCloseEnoughPoint(Polygon<2> const& poly, Point<2> const& point, Point<2>& match)
    {
        const Polygon<2>::const_iterator end = poly.end();
        
        for(Polygon<2>::const_iterator it = poly.begin(); it != end; ++it)
        {
            if(closeEnough(*it, point, 5))
            {
                match = *it;
                return true;
            }   
        }

        return false;
    }
}

MainWin::MainWin()
: Planar("Convex Test", GLUT_RGBA | GLUT_DOUBLE),
  polygon_(PolygonType::LeftIsInterior()), selectCount_(-1)
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(620, 460);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(1);
    glColor3f(1, 0, 0);
    drawLineLoop(polygon_);
    
    // Status line
    glLineWidth(3);
    glColor3f(0.4, 0.7, 0.2);
    glBegin(GL_LINES);
    glVertex2i(0, 30);
    glVertex2i(getWidth(), 30);
    glEnd();


    if(selectCount_ >= 0)
    {
        glLineWidth(1);
        putAllHandles(polygon_);

        if(selectCount_ == 2)
        {
            const Edge<2> edge(first_, second_);
            
            glLineWidth(2);
            glColor3f(0, 0, 1);
            drawEdge(edge);

            if(isChord(polygon_, edge))
            {
                writeMessage("Selected diagonal is a chord.");
            }
            else 
            {
                writeMessage("Selected diagonal is not a chord.");
            }
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
            if(selectCount_ == -1)
            { 
                selectCount_ = 0;
            }
        }
        else if(button == GLUT_LEFT_BUTTON)
        {
            Point<2> selected = windowToGl(x, y);
            
            if(selectCount_ == -1)
            {
                polygon_.addVertex(selected);
            }
            else
            {
                if(selectCount_ == 2)
                {
                    selectCount_ = 0;
                }
                
                Point<2> match;
                
                if(findCloseEnoughPoint(polygon_, selected, match))
                {
                    if(selectCount_ == 0)
                    {
                        first_ = match;
                        ++selectCount_;
                    }
                    else if(selectCount_ == 1)
                    {
                        second_ = match;
                        ++selectCount_;
                    }
                }
            }
        }    
    }

    invalidate();
}

void MainWin::keyboardGL(unsigned char key, int x, int y)
{
    if((key == 'n' || key == 'N'))
    {
        selectCount_ = -1;
        polygon_.clear();
        invalidate();
    }

    Planar::keyboardGL(key, x, y);
}

void MainWin::writeMessage(char const* msg)
{
    glColor3f(1, 0, 0);
    drawText(GLUT_BITMAP_8_BY_13, point(10, 10), msg);
}
