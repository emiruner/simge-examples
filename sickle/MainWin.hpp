#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <vector>
#include <simge/glut/Planar.hpp>
#include <simge/geom/Polygon.hpp>

class MainWin : public simge::glut::Planar
{
    enum InputState
    {
        EnteringSubject,
        EnteringClip,
        Display
    };
    
public:
    MainWin();

protected:
    void paintGL();
    void mouseGL(int button, int state, int x, int y);
    void keyboardGL(unsigned char key, int x, int y);
    
private:
    simge::geom::Polygon<2> p_;
    simge::geom::Polygon<2> q_;
    InputState state_;
    simge::geom::Polygon<2> intersection_;
};

#endif
