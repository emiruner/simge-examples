#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/util/Turtle.hpp>

class MainWin : public simge::glut::Planar
{
public:
    MainWin();

protected:
    void paintGL();
};

#endif
