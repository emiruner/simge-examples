#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <simge/geom/Edge.hpp>
#include <simge/geom/Polygon.hpp>
#include <simge/glut/Planar.hpp>

class MainWin : public simge::glut::Planar
{
public:
    MainWin();
    
protected:
    void paintGL();
    void mouseGL(int button, int state, int x, int y);
    void keyboardGL(unsigned char key, int x, int y);
    
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

    bool isPolygonComplete() const 
    {
        return polygonComplete_;
    }
    
    void selectNewPoint()
    {
        ++clickCount_;
    }

    void writeMessage(char const* msg);

    simge::geom::Edge<2> ray_;
    simge::geom::Polygon<2> polygon_;
    bool polygonComplete_;
    int clickCount_;
};

#endif
