#include "MainWin.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <simge/geom/Operations.hpp>
#include <simge/util/Utility.hpp>

#include "GiftWrap.hpp"

using namespace simge::geom;
using namespace simge::glut;
using namespace simge::util;

namespace
{
    Point<2>* asArray(PointVec const& pv)
    {
        Point<2>* arr = new Point<2>[pv.size() + 1];
        PointVec::const_iterator end = pv.end();
        
        int i = 0;
        for(PointVec::const_iterator it = pv.begin(); it != end; ++it, ++i)
        {
            arr[i] = *it;
        }
        
        return arr;
    }
}
        
MainWin::MainWin()
: Planar("Convex Polygon Calculation [Gift Wrapping Method]", GLUT_RGBA | GLUT_DOUBLE),
  convexHull_(PolygonType::LeftIsInterior()), pointsSelected_(false)
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(620, 460);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Status line
    glLineWidth(3);
    glColor3f(0.4, 0.7, 0.2);
    glBegin(GL_LINES);
    glVertex2i(0, 30);
    glVertex2i(getWidth(), 30);
    glEnd();

    glLineWidth(1);
    glColor3f(1, 0, 0);

    void (*vertexer)(simge::geom::Point<2> const&) = &simge::glut::vertex;

    glPointSize(4);
    glBegin(GL_POINTS);
    std::for_each(points_.begin(), points_.end(), vertexer);
    glEnd();
    
    if(pointsSelected_)
    {
        drawLineLoop(convexHull_);
        glColor3f(1, 0, 0);
        writeMessage("Press `n' for new polygon.");
    }
    else
    {
        writeMessage("Enter point set. Finish by clicking right button.");
    }
    
    glutSwapBuffers();
}

void MainWin::mouseGL(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        if(button == GLUT_RIGHT_BUTTON)
        {
            if(pointsSelected_ == false)
            {
                pointsSelected_ = true;
                Point<2>* arr = asArray(points_);
                convexHull_ = giftWrapConvexHull(arr, points_.size());
                delete[] arr;
                
                invalidate();
            }
        }
        else if(button == GLUT_LEFT_BUTTON)
        {
            if(!pointsSelected_)
            {
                points_.push_back(windowToGl(x, y));
            }
            
            invalidate();
        }
    }
}

void MainWin::keyboardGL(unsigned char key, int x, int y)
{
    if((key == 'n' || key == 'N'))
    {
        pointsSelected_ = false;
        convexHull_.clear();
        points_.clear();
        invalidate();
    }

    Planar::keyboardGL(key, x, y);
}

void MainWin::writeMessage(char const* msg)
{
    drawText(GLUT_BITMAP_8_BY_13, point(10, 10), msg);
}
