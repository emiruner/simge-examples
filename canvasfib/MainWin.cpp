#include "MainWin.hpp"

using namespace simge::glut;
using namespace simge::util;

namespace
{
    const int kMargin = 16;

    int fibonacci(int k)
    {
        if(k == 0 || k == 1)
        {
            return 1;
        }
        else
        {
            int pre = 1, prepre = 1;
            
            for(int i = 1; i < k; ++i)
            {
                int tmp = pre + prepre;
                
                prepre = pre;
                pre = tmp;
            }
            
            return pre;
        }
    }
} // namespace <unnamed>

MainWin::MainWin(int n)
: Planar("Fibonaci Series"), n_(n)
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(640, 480);
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

    const float xcoeff = (float)(getWidth() - kMargin * 2) / (float)n_;
    const float ycoeff = (float)(getHeight() - kMargin * 2) /
        (float)fibonacci(n_);
    
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    for(int i = 0; i < n_; ++i)
    {
        glVertex2i(2 * kMargin + (int)(i * xcoeff),
                   2 * kMargin + (int)(fibonacci(i) * ycoeff));
    }
    glEnd();
    
    glFlush();
}
