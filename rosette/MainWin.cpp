#include "MainWin.hpp"
#include <vector>

using namespace simge::geom;
using namespace simge::glut;
using namespace simge::util;

typedef std::vector<Point<2> > PointVec;

namespace 
{
    const int kEdgeLength = 48;
    const int kNGon = 16;
    const float turnAngle = 360.0 / kNGon;
    
    /**
     * Draws lines starting from `fixed' to all points specified
     * in the `others' vector.
     */
    void oneToMany(Point<2> const& fixed, PointVec const& others)
    {
        PointVec::const_iterator p, end = others.end();
        
        glBegin(GL_LINES);
        for(p = others.begin(); p != end; ++p)
        {
            vertex(fixed);
            vertex(*p);
        }
        glEnd();
    }
}

MainWin::MainWin()
: Planar("Rosette")
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(640, 480);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);

    Turtle t;
    PointVec v;
    
    t.moveTo(point(320, 40));

    for(int i = 0; i < kNGon; ++i)
    {
        t.turn(turnAngle);
        t.forward(kEdgeLength);
        oneToMany(t.getPosition(), v);
        v.push_back(t.getPosition());
    }
    
    glFlush();
}
