#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/util/Turtle.hpp>
#include <simge/geom/Edge.hpp>
#include <vector>

typedef std::vector<simge::geom::Point<2> > Point2Vec;

class MainWin : public simge::glut::Planar
{
public:
    MainWin();

protected:
    void paintGL();
    void mouseGL(int button, int state, int x, int y);

private:

    bool isFirstPointSelected() const
    {
        return clickCount_ % 2 == 1;
    }
    
    bool isSecondPointSelected() const
    {
        if(clickCount_ > 0)
        {
            if(clickCount_ % 2 == 0)
            {
                return true;
            }
        }
         
        return false;
    }

    void selectNewPoint()
    {
        ++clickCount_;
    }
    
    int clickCount_;
    simge::geom::Edge<2> line_;
    simge::geom::Edge<2> normal_;
};

#endif
