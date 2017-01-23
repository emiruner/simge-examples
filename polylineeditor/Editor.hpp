#ifndef MY_EDITOR_HPP_INCLUDED
#define MY_EDITOR_HPP_INCLUDED

#include <simge/glut/Planar.hpp>
#include <simge/util/Polyline.hpp>

#include <vector>
#include <string>

typedef simge::util::Polyline<simge::geom::Point<2> > Polyline2D;
typedef std::vector<Polyline2D> Polyline2DVec;

struct EditorState;

class Editor : public simge::glut::Planar
{
public:
    Editor(char const* name, char const* filename);
    ~Editor();
    
    Polyline2DVec const& getLines() const
    {
        return lines_;
    }    
    
    Polyline2DVec& getLines()
    {
        return lines_;
    }
    
protected:
    void paintGL();
    void keyboardGL(unsigned char key, int x, int y);
    void mouseGL(int button, int state, int x, int y);
    void passiveMotionGL(int x, int y);
    void motionGL(int x, int y);
    
private:
    std::string file_;
    Polyline2DVec lines_;
    EditorState* state_;
    
    friend struct EditorState;
    void changeState(EditorState* newState)
    {
        state_ = newState;
    }
};

/**
 * Serves both as a base state class and idle state.
 */
struct EditorState
{
    static EditorState instance_;
    static EditorState* instance() { return &instance_; }

    virtual ~EditorState()
    {
    }
    
    virtual void onKeypress(Editor* editor, unsigned char key, int x, int y);
    virtual void onMouseDown(Editor* editor, int button, int x, int y) {}
    virtual void onMouseMove(Editor* editor, int x, int y) {}
    virtual void onMouseUp(Editor* editor, int button, int x, int y) {}
    virtual void onPaint(Editor* editor);

    /**
     * Do steps required before being selected as the new state.
     * This is required because we are a singleton.
     */
    virtual void beforeChange(Editor* editor) {}
    
protected:
    void changeState(Editor* editor, EditorState* newState)
    {
        newState->beforeChange(editor);
        editor->changeState(newState);
    }
};
    
struct UserDrawingState : public EditorState
{
    static UserDrawingState instance_;    
    static UserDrawingState* instance() { return &instance_; }

    void beforeChange(Editor*)
    {
        current_.color = simge::util::Color::red();
        current_.points.clear();
        oldx_ = -1;
    }
    
    void onKeypress(Editor* editor, unsigned char key, int x, int y);
    void onPaint(Editor* editor);
    void onMouseDown(Editor* editor, int button, int x, int y);
    void onMouseMove(Editor* editor, int x, int y);    
    
    Polyline2D current_;
    int oldx_;
    int oldy_;
};

struct DeletePointState : public EditorState
{
    static DeletePointState instance_;
    static DeletePointState* instance() { return &instance_; }    

    void onMouseDown(Editor* editor, int button, int x, int y);
};

struct MovePointState : public EditorState
{
    static MovePointState instance_;    
    static MovePointState* instance() { return &instance_; }    

    void beforeChange(Editor*)
    {
        idx = -1;
    }

    void onMouseDown(Editor* editor, int button, int x, int y);
    void onMouseUp(Editor* editor, int button, int x, int y);
    void onMouseMove(Editor* editor, int x, int y);    
    void onPaint(Editor* editor);

    int idx;
    Polyline2DVec::iterator line;
};

#endif
