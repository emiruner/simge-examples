#include "Golden.hpp"

using namespace simge::glut;

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

    inline float ratio(int n)
    {
        float pre = fibonacci(n);
        float prepre = fibonacci(n - 1);
        
        return pre / prepre;
    }
    
} // namespace <unnamed>

Golden::Golden(int n)
: Planar("Golden Ratio"), n_(n)
{
    glClearColor(0.8, 0.9, 1, 0);
    glColor3f(1, 0, 0);
    setSize(640, 480);
}

#include <cstdio>

void Golden::paintGL()
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
    const float ycoeff = (float)(getHeight() - kMargin * 2) / 2;
    
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    for(int i = 1; i < n_; ++i)
    {
        glVertex2i(2 * kMargin + (int)((float)i * xcoeff),
                   2 * kMargin + (int)(ratio(i) * ycoeff));
    }
    glEnd();
    
    glFlush();
}
