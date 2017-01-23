#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <vector>
#include <simge/glut/Planar.hpp>
#include <simge/geom/Polygon.hpp>

class MainWin : public simge::glut::Planar
{
public:
    MainWin();

protected:
    void paintGL();
    void mouseGL(int button, int state, int x, int y);
    void keyboardGL(unsigned char key, int x, int y);
    
private:
    simge::geom::Polygon<2> p_;
    std::vector<simge::geom::Polygon<2> > triangles_;
    bool finishedEntering_;
};

#endif
