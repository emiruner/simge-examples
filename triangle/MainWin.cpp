#include "MainWin.hpp"

#include <math.h>
#include <algorithm>
#include <simge/geom/Operations.hpp>
#include <simge/util/Utility.hpp>

using namespace simge::geom;
using namespace simge::glut;
using namespace simge::util;

namespace
{
    inline void findOuterCircle(Point<2> const& A, Point<2> const& B, Point<2> const& C, Point<2>& center, double& r)
    {
        const Vector<2> a = B - A;
        const Vector<2> b = C - B;
        const Vector<2> c = A - C;
        
        const double normADotC = dot(a.ccwNormal(), c);
        const double bDotC = dot(b, c);
        
        center = A + 0.5 * (a + (bDotC / normADotC) * a.ccwNormal());
        r = (a.length() / 2) * sqrt(bDotC * bDotC / (normADotC * normADotC) + 1);
    }
    
    inline void findCenter(Point<2> const& R, Point<2> const& S, Point<2> const& T, Point<2>& center)
    {
        const double p = R[0] - S[0];
        const double q = R[1] - S[1];
        const double r = S[0] - T[0];
        const double s = S[1] - T[1];

        const double t = R[0] * R[0] - S[0] * S[0] + R[1] * R[1] - S[1] * S[1];
        const double u = S[0] * S[0] - T[0] * T[0] + S[1] * S[1] - T[1] * T[1];
        
        const double o = (q * r - s * p) * 2;
        
        center[0] = (q * u - s * t) / o;
        center[1] = (r * t - p * u) / o;
    }
    
    inline void findInnerCircle(Point<2> const& A, Point<2> const& B, Point<2> const& C, Point<2>& center, double& r)
    {
        const Vector<2> a = B - A;
        const Vector<2> b = C - B;
        const Vector<2> c = A - C;

        const double La = (a.length() + c.length() - b.length()) / 2.0;
        const double Lb = (a.length() + b.length() - c.length()) / 2.0;
        const double Lc = (c.length() + b.length() - a.length()) / 2.0;
        
        const Point<2> R = A + La * a.unit();
        const Point<2> S = B + Lb * b.unit();
        const Point<2> T = C + Lc * c.unit();

        findCenter(R, S, T, center);
        r = (R - center).length();
    }    
}

MainWin::MainWin()
: Planar("Triangle's Circles", GLUT_RGBA | GLUT_DOUBLE), selectedVertex_(-1)
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(620, 460);

    vertexes_[0] = point(140, 140);
    vertexes_[1] = point(290, 380);
    vertexes_[2] = point(440, 140);    
}

void MainWin::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw triangle
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    vertex(vertexes_[0]);
    vertex(vertexes_[1]);
    vertex(vertexes_[2]);
    glEnd();

    Point<2> center;
    double radius;

    findInnerCircle(vertexes_[0], vertexes_[1], vertexes_[2], center, radius);
    drawCircle(center, radius);

    findOuterCircle(vertexes_[0], vertexes_[1], vertexes_[2], center, radius);
    drawCircle(center, radius);
    
    // Draw grab handles
    drawGrabHandle(vertexes_[0], 6);
    drawGrabHandle(vertexes_[1], 6);
    drawGrabHandle(vertexes_[2], 6);

    // Status line
    glLineWidth(3);
    glColor3f(0.4, 0.7, 0.2);
    glBegin(GL_LINES);
    glVertex2i(0, 30);
    glVertex2i(getWidth(), 30);
    glEnd();
    glLineWidth(1);
    glColor3f(1, 0, 0);

    drawText(GLUT_BITMAP_8_BY_13, point(10, 10), "Drag corners of the triangle!");
    
    glFlush();
    glutSwapBuffers();
}

void MainWin::mouseGL(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            for(int i = 0; i < 3; ++i)
            {
                if(closeEnough(windowToGl(x, y), vertexes_[i], 3))
                {
                    selectedVertex_ = i;
                }
            }
        }
        else if(state == GLUT_UP)
        {
            selectedVertex_ = -1;
        }
    }
}

void MainWin::motionGL(int x, int y)
{
    if(selectedVertex_ != -1)
    {
        vertexes_[selectedVertex_] = windowToGl(x, y);
        invalidate();
    }
}
