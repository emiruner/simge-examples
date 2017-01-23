#ifndef MY_MAINWIN_HPP_INCLUDED
#define MY_MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include "Hailstone.hpp"

class MainWin : public simge::glut::Planar
{
public:
    MainWin(char const* name, long start);
    
protected:
    void paintGL();

private:
    long start_;
};

#endif
