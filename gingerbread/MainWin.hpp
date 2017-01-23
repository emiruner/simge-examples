#ifndef MY_MAINWIN_HPP_INCLUDED
#define MY_MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/glut/Point.hpp>

class MainWin : public simge::glut::Planar
{
public:
    MainWin(char const* name, int m, int l, int dotCount);
    
protected:
    void paintGL();
    void mouseGL(int button, int state, int x, int y);
    
private:
    int m_;
    int l_;
    int dotCount_;
    simge::geom::Point<2> start_;
};

#endif
