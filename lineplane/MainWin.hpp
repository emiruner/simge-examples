#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/util/Utility.hpp>
#include <vector>

typedef std::vector<simge::geom::Point<3> > PointVec;

class MainWin : public simge::glut::Window
{
public:
    MainWin(simge::geom::Point<3> const* triangle, simge::geom::Point<3> const* line, simge::geom::Point<3> const& dot);

protected:
    void paintGL();
    void mouseGL(int button, int state, int x, int y);
    void reshapeGL(int width, int height);
    void keyboardGL(unsigned char key, int x, int y);

private:
    simge::geom::Point<3> triangle_[3];
    simge::geom::Point<3> line_[2];
    simge::geom::Point<3> dot_;
    double rot_;
};

#endif
