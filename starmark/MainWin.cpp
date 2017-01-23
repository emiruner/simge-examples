#include "MainWin.hpp"

#include <cmath>
#include <cassert>
#include <algorithm>

using namespace simge::glut;
using namespace simge::util;

namespace
{
    const int kMargin = 16;
    
    inline double degreeToRadians(double degree)
    {
        return degree * 0.01745329251994329576;
    }
    
    void drawStar(simge::geom::Point<2> const& center, double len, double turnAngle)
    {
        Turtle t;
        
        const float radius = len * cos(degreeToRadians(18)) / 2.0;
        
        t.moveTo(center);
        t.turnTo(306.0 + turnAngle);
        t.forward(radius, false);
        t.turnTo(108 + turnAngle);
        t.forward(len);
        t.turn(144);
        t.forward(len);
        t.turn(144);
        t.forward(len);
        t.turn(144);
        t.forward(len);
        t.turn(144);
        t.forward(len);
    }

} // namespace <unnamed>

MainWin::MainWin(IntVec& xs, IntVec& ys)
: Planar("Star Marker")
{
    assert(xs.size() == ys.size());
    assert(xs.size() > 0);
    
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);

    std::swap(xs_, xs);
    std::swap(ys_, ys);
    setSize(3 * kMargin + *std::max_element(xs_.begin(), xs_.end()),
            3 * kMargin + *std::max_element(ys_.begin(), ys_.end()));
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex2i(kMargin * 2, kMargin);
    glVertex2i(kMargin * 2, getHeight() - kMargin);
    glVertex2i(kMargin, 2 * kMargin);
    glVertex2i(getWidth() - kMargin, 2 * kMargin);
    glEnd();

    const int elemCount = xs_.size();
    
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
	int i;
    for(i = 0; i < elemCount; ++i)
    {
        glVertex2i(kMargin * 2 + xs_[i], kMargin * 2 + ys_[i]);
    }
    glEnd();

    glColor3f(0.5, 0.7, 0.5);
    for(i = 0; i < elemCount; ++i)
    {
        drawStar(simge::geom::point(kMargin * 2 + xs_[i], kMargin * 2 + ys_[i]),20,0);
    }
    
    glFlush();
}
