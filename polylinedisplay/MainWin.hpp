#ifndef MY_MAINWIN_HPP_INCLUDED
#define MY_MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/util/Polyline.hpp>
#include <vector>

typedef simge::util::Polyline<simge::geom::Point<2> > Polyline2D;
typedef std::vector<Polyline2D> Polyline2DVec;

class MainWin : public simge::glut::Planar
{
public:
    MainWin(char const* name, Polyline2DVec const& lines);
    
protected:
    void paintGL();
    
private:
    Polyline2DVec lines_;
};

#endif
