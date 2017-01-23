#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/util/Utility.hpp>
#include <vector>

typedef std::vector<simge::geom::Point<2> > PointVec;

class MainWin : public simge::glut::Planar
{
public:
    MainWin();

protected:
    void paintGL();
    void mouseGL(int button, int state, int x, int y);
    void keyboardGL(unsigned char key, int x, int y);

private:
    void writeMessage(char const* msg);
        
    simge::geom::Polygon<2> convexHull_;
    PointVec points_;

    bool pointsSelected_;
};

#endif
