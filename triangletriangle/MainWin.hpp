#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/util/Utility.hpp>
#include <vector>

typedef std::vector<simge::geom::Point<3> > PointVec;

class MainWin : public simge::glut::Window
{
public:
    MainWin(simge::geom::Point<3> const* t1, simge::geom::Point<3> const* t2,
            PointVec const& dots);

protected:
    void paintGL();
    void mouseGL(int button, int state, int x, int y);
    void reshapeGL(int width, int height);
    void keyboardGL(unsigned char key, int x, int y);

private:
    simge::geom::Point<3> t1_[3];
    simge::geom::Point<3> t2_[3];
    PointVec dots_;
    double rot_;
};

#endif
