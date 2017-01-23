#ifndef STIPPLEWIN_HPP_INCLUDED
#define STIPPLEWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/glut/Point.hpp>
#include <vector>

class StippleWin : public simge::glut::Planar
{
public:
    StippleWin(int factor, int pattern);    

protected:
    virtual void mouseGL(int button, int state, int x, int y);
    virtual void paintGL();
    
private:
    typedef std::vector<simge::geom::Point<2> > PointVec;
    PointVec points_;
};

#endif
