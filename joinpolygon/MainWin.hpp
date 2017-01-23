#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <vector>
#include <simge/glut/Planar.hpp>
#include <simge/geom/Polygon.hpp>

#include "InputState.hpp"

class MainWin : public simge::glut::Planar
{
public:
    MainWin();

protected:
    void paintGL();
    void mouseGL(int button, int state, int x, int y);
    void keyboardGL(unsigned char key, int x, int y);
    
private:
    simge::geom::Polygon<2> subject_;
    simge::geom::Polygon<2> clip_;
    simge::geom::Polygon<2> joined_;
    InputState state_;
};

#endif
