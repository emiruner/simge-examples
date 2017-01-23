#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/util/Turtle.hpp>

#include <string>

class MainWin : public simge::glut::Planar
{
public:
    MainWin(char const* commands);

protected:
    void paintGL();

private:
    std::string cmd_;
};

#endif
