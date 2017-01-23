#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/util/Turtle.hpp>

class MainWin : public simge::glut::Planar
{
public:
    MainWin(int n);

protected:
    void paintGL();
    
private:
    const int n_;
};

#endif
