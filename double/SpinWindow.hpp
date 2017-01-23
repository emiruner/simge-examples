#ifndef SPINWINDOW_HPP_INCLUDED
#define SPINWINDOW_HPP_INCLUDED

#include <simge/glut/Window.hpp>
#include <simge/glut/IdleWorker.hpp>

class SpinWindow : public simge::glut::Window, public simge::glut::IdleWorker
{
public:
    SpinWindow();
    ~SpinWindow();
    
protected:
    void reshapeGL(int width, int height);
    void paintGL();
    void mouseGL(int button, int state, int x, int y);
    void keyboardGL(unsigned char key, int x, int y);
    void spinDisplay();    
    void idle();
    
private:
    bool spin_;
    int spinAngle_;
    int idleCount_;
};

#endif
