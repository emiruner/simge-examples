#include "Editor.hpp"

#include <simge/util/Utility.hpp>
#include <simge/util/PolylineFile.hpp>

#include <cstdio>
#include <fstream>
#include <algorithm>

using namespace simge::geom;
using namespace simge::glut;
using namespace simge::util;

// Singleton instances
EditorState EditorState::instance_;
UserDrawingState UserDrawingState::instance_;
DeletePointState DeletePointState::instance_;
MovePointState MovePointState::instance_;

namespace
{
    const int kProximityLimit = 3;
    
    inline void drawPolyline(Polyline2D const& line)
    {
        Polyline2D::PointVec::const_iterator i, end = line.points.end();
        Point<2> last = line.points[0];
        
        for(i = line.points.begin() + 1; i != end; ++i)
        {
            float r, g, b;
            line.color.normalize(r, g, b);
            glColor3f(r, g, b);
            
            glBegin(GL_LINES);
            vertex(last);
            vertex(*i);
            glEnd();
            last = *i;
        }

        for(i = line.points.begin(); i != end; ++i)
        {
            drawGrabHandle(*i, kProximityLimit * 2);
        }
    }

    int withinProximity(Polyline2D const& l, Point<2> const& p, int d)
    {
        Polyline2D::PointVec::const_iterator i, end = l.points.end();
        int idx = 0;
        
        for(i = l.points.begin(); i != end; ++i, ++idx)
        {
            if(closeEnough(*i, p, d))
            {
                return idx;
            }
        }
        
        return -1;
    }
    
    void writeLine(std::ostream& out, Polyline2D const& line)
    {
        out << line.points.size();
        if(line.color != Color::black())
        {
            out << ' ' << line.color;
        }
        out << '\n';
        
        Polyline2D::PointVec::const_iterator i, end = line.points.end();
        for(i = line.points.begin(); i != end; ++i)
        {
            out << (*i)[0] << ' ' << (*i)[1] << '\n';
        }
    }
    
} // namespace <unnamed>

Editor::Editor(char const* name, char const* filename)
: Planar(name), file_(filename), state_(EditorState::instance())
{
    glEnable(GL_COLOR_LOGIC_OP);
    glClearColor(0.88, 0.94, 0.99, 0);
    setSize(640, 480);

    std::ifstream in(file_.c_str());
    
    if(in.is_open())
    {
        PolylineFile<Point<2> > pf(in);
        int lineCount = pf.getPolylineCount();
        
        for(int i = 0; i < lineCount; ++i)
        {
            lines_.push_back(pf.getNext());
        }
    }
}

Editor::~Editor()
{
    std::ofstream out(file_.c_str());
    
    out << lines_.size() << '\n';

    Polyline2DVec::const_iterator linei, lineend = lines_.end();
    for(linei = lines_.begin(); linei != lineend; ++linei)
    {
        writeLine(out, *linei);
    }
}

void Editor::paintGL()
{
    state_->onPaint(this);
}

void Editor::mouseGL(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        state_->onMouseDown(this, button, x, y);
    }
    else if(state == GLUT_UP)
    {
        state_->onMouseUp(this, button, x, y);
    }
}

void Editor::passiveMotionGL(int x, int y)
{
    state_->onMouseMove(this, x, y);
}

void Editor::motionGL(int x, int y)
{
    state_->onMouseMove(this, x, y);
}

void Editor::keyboardGL(unsigned char key, int x, int y)
{
    Planar::keyboardGL(key, x, y);
    state_->onKeypress(this, key, x, y);
}

// ---- EditorState methods ---------------------------------------------------
void EditorState::onPaint(Editor* ed)
{
    glClear(GL_COLOR_BUFFER_BIT);
    std::for_each(ed->getLines().begin(), ed->getLines().end(), &drawPolyline);
    glFlush();
}

void EditorState::onKeypress(Editor* ed, unsigned char key, int x, int y)
{
    if(key == 'b' || key == 'B')
    {
        changeState(ed, UserDrawingState::instance());
    }
    else if(key == 'd' || key == 'D')
    {
        changeState(ed, DeletePointState::instance());
    }
    else if(key == 'm' || key == 'M')
    {
        changeState(ed, MovePointState::instance());
    }
    else if(key == 'q' || key == 'Q')
    {
        exit(0);
    }
}

// ---- UserDrawingState methods ----------------------------------------------
void UserDrawingState::onPaint(Editor* editor)
{
    EditorState::onPaint(editor);
    drawPolyline(current_);
    glFlush();
}

void UserDrawingState::onMouseDown(Editor* e, int button, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        current_.points.push_back(point(x, e->getHeight() - y));
        oldx_ = -1;
        onPaint(e);
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        current_.color = Color::blue();
        e->getLines().push_back(current_);
        e->invalidate();

        changeState(e, EditorState::instance());
    }
}

void UserDrawingState::onMouseMove(Editor* editor, int x, int y)
{
    glColor3f(1, 0, 0);

    if(current_.points.size() > 0)
    {
        const Point<2> last = *(current_.points.end() - 1);
            
        glLogicOp(GL_XOR);
        
        if(oldx_ != -1)
        {
            glBegin(GL_LINES);
            glVertex2d(last[0], last[1]);
            glVertex2d(oldx_, oldy_);
            glEnd();
        }
        
        glBegin(GL_LINES);
        glVertex2d(last[0], last[1]);
        glVertex2d(x, editor->getHeight() - y);
        glEnd();
        oldx_ = x;
        oldy_ = editor->getHeight() - y;
        glLogicOp(GL_COPY);
    }
}

void UserDrawingState::onKeypress(Editor* e, unsigned char key, int x, int y)
{
    current_.color = Color::blue();
    e->getLines().push_back(current_);    
    e->invalidate();
    EditorState::onKeypress(e, key, x, y);
}

// ---- DeletePointState ------------------------------------------------------
void DeletePointState::onMouseDown(Editor* editor, int button, int x, int y)
{
    if(button != GLUT_LEFT_BUTTON)
    {
        return;
    }

    Polyline2DVec::iterator linei, lineend = editor->getLines().end();
    for(linei = editor->getLines().begin(); linei != lineend; ++linei)
    {
        int pidx = withinProximity(*linei, point(x,
                       editor->getHeight() - y), kProximityLimit);

        if(pidx != -1)
        {
            linei->points.erase(linei->points.begin() + pidx);
            if(linei->points.size() < 2)
            {
                editor->getLines().erase(linei);
            }
            editor->invalidate();
            return;
        }        
    }
}

// ---- MovePointState ------------------------------------------------------
void MovePointState::onMouseDown(Editor* ed, int button, int x, int y)
{
    if(button != GLUT_LEFT_BUTTON)
    {
        return;
    }

    if(idx != -1)
    {
        printf("Warning! Spurious mouse down while still a point selected!\n");
        return;
    }
    
    Polyline2DVec::iterator linei, lineend = ed->getLines().end();
    for(linei = ed->getLines().begin(); linei != lineend; ++linei)
    {
        idx = withinProximity(*linei, point(x,
                  ed->getHeight() - y), kProximityLimit);

        if(idx != -1)
        {
            line = linei;
            break;
        }
    }
}

void MovePointState::onMouseUp(Editor* ed, int button, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        idx = -1;
        ed->invalidate();
    }
}

void MovePointState::onMouseMove(Editor* ed, int x, int y)
{
    if(idx == -1)
    {
        return;
    }

    Point<2> p1, p2, p3;

    p3[0] = -1;
    
    if(idx == 0)
    {
        p1 = line->points[1];
        p2 = line->points[0];
    }
    else if(idx == (int)(line->points.size() - 1))
    {
        p1 = line->points[idx - 1];
        p2 = line->points[idx];
    }
    else
    {
        p1 = line->points[idx - 1];
        p2 = line->points[idx];
        p3 = line->points[idx + 1];
    }

    glLogicOp(GL_XOR);    
    glBegin(GL_LINES);
    vertex(p1);
    vertex(p2);
    if(p3[0] != -1)
    {
        vertex(p2);
        vertex(p3);
    }

    p2[0] = x;
    p2[1] = ed->getHeight() - y;
    line->points[idx] = p2;

    vertex(p1);
    vertex(p2);
    if(p3[0] != -1)
    {
        vertex(p2);
        vertex(p3);
    }
    glEnd();
    glLogicOp(GL_COPY);
    glFlush();
}

void MovePointState::onPaint(Editor* ed)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    Polyline2DVec::const_iterator linei, lineend = ed->getLines().end();
    for(linei = ed->getLines().begin(); linei != lineend; ++linei)
    {
        // Skip active line
        if(idx == -1)
        {
            drawPolyline(*linei);
        }
        else if(line != linei)
        {
            drawPolyline(*linei);
        }
    }
    glFlush();    
}
