#include "MainWin.hpp"

#include <cmath>
#include <cassert>

using namespace simge::glut;
using namespace simge::util;

namespace
{
    const double kPi = 4.0 * atan(1.0);
    
    inline double degreeToRadians(double degree)
    {
        return degree * kPi / 180.0;
    }
    
    void drawStar(simge::geom::Point<2> center, double len, double turnAngle)
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

MainWin::MainWin()
: Planar("Twenty One")
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(400, 400);
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 1);

    Turtle t;
    
    drawStar(simge::geom::point(200, 200), 100, 0);

    t.moveTo(simge::geom::point(200, 200));
    t.turnTo(43);
    t.forward(80, false);

    t.turn(72);
    
    float edgeLen = 2.0 * 80.0 * sin(degreeToRadians(18));

	int i;
    for(i = 0; i < 10; ++i)
    {
        drawStar(t.getPosition(), 16, 0);
        t.turn(36);
        t.forward(edgeLen, false);
    }
    
    t.moveTo(simge::geom::point(200, 200));
    t.turnTo(43);
    t.forward(120, false);

    t.turn(72);
    
    edgeLen = 2.0 * 120.0 * sin(degreeToRadians(18));

    for(i = 0; i < 10; ++i)
    {
        drawStar(t.getPosition(), 16, 0);
        t.turn(36);
        t.forward(edgeLen, false);
    }
    
    glFlush();
}
