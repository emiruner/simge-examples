#ifndef MAINWIN_HPP_INCLUDED
#define MAINWIN_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/util/Utility.hpp>

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
    void writeMessage(std::string const& msg);
    
    simge::geom::Polygon<2> polygon_;
    bool finished_;
};

#endif
