#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>

class MainWin : public simge::glut::Planar
{
public:
    MainWin();

protected:
    void paintGL();
    void mouseGL(int button, int state, int x, int y);
    void motionGL(int x, int y);

private:
    simge::geom::Point<2> vertexes_[3];

    // == -1 if no vertex selected, otherwise vertex number
    int selectedVertex_;
};

#endif
