#include "MainWin.hpp"
#include <algorithm>
#include <simge/geom/Operations.hpp>
#include <simge/util/Utility.hpp>

using namespace simge::geom;
using namespace simge::glut;
using namespace simge::util;

void drawColoredEdges(Polygon<2> const& polygon, Edge<2> const& ray)
{
    Polygon<2>::const_iterator i, end;
    
    for(i = polygon.begin(), end = polygon.end(); i != end; ++i)
    {
        Edge<2> edge;

		Polygon<2>::const_iterator next = i;
		++next;
		
        if(next == end)
        {
            edge = Edge<2>(*i, *polygon.begin());
        }
        else
        {
            edge = Edge<2>(*i, *(next));
        }
        
        const HitType hitType = hitQueryLeftIsInterior(ray, edge);
        
        if(hitType == HitType::NoHit())
        {
        	glColor3f(0, 0, 0);
        }
        else if(hitType == HitType::Entering())
        {
        	glColor3f(1, 0, 0);
        }
        else if(hitType == HitType::Exiting())
        {
        	 glColor3f(0, 1, 0);
        }
        
        drawArrow(edge[0],  edge.direction0_1(), edge.length());
    }
}

MainWin::MainWin()
: Planar("EnterLeave Test", GLUT_RGBA | GLUT_DOUBLE),polygon_(PolygonType::RightIsInterior()), polygonComplete_(false)
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(620, 460);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(isSecondPointSelected() && isPolygonComplete())
    {
        drawColoredEdges(polygon_, ray_);
    }
    else
    {
        drawLineLoop(polygon_);
    }
    
    // Status line
    glLineWidth(3);
    glColor3f(0.4, 0.7, 0.2);
    glBegin(GL_LINES);
    glVertex2i(0, 30);
    glVertex2i(getWidth(), 30);
    glEnd();

    glLineWidth(1);
    glColor3f(1, 0, 0);

    if(isPolygonComplete())
    {
        writeMessage("Select beginning and ending points of the ray. "
                     "Press `n' for new polygon.");

        if(isSecondPointSelected())
        {
            drawArrow(ray_[0], ray_.direction0_1(), ray_.length());
        }
    }
    else
    {
        writeMessage("Select vertexes of polygon in counter-clockwise direction. Finish by right button.");
    }
    
    glutSwapBuffers();
}

void MainWin::mouseGL(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        if(button == GLUT_RIGHT_BUTTON)
        {
            if(!isPolygonComplete())
            {
                polygonComplete_ = true;
                clickCount_ = 0;
                invalidate();
            }
        }
        else if(button == GLUT_LEFT_BUTTON)
        {
            if(isPolygonComplete())
            {
                if(isFirstPointSelected())
                {
                    ray_[1] = windowToGl(x, y);
                    invalidate();
                }
                else
                {
                    ray_[0] = windowToGl(x, y);
                }
                
                selectNewPoint();
            }
            else
            {
                polygon_.addVertex(windowToGl(x, y));
                invalidate();
            }
        }
    }
}

void MainWin::keyboardGL(unsigned char key, int x, int y)
{
    if((key == 'n' || key == 'N') && isPolygonComplete())
    {
        polygonComplete_ = false;
        polygon_.clear();
        invalidate();
    }

    Planar::keyboardGL(key, x, y);
}

void MainWin::writeMessage(char const* msg)
{
    drawText(GLUT_BITMAP_8_BY_13, point(10, 10), msg);
}
