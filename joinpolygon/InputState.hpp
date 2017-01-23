#ifndef INPUTSTATE_HPP_INCLUDED
#define INPUTSTATE_HPP_INCLUDED

#include <simge/util/Enum.hpp>

class InputState : public simge::util::Enum<short>
{
private:
    InputState(short val)
    : simge::util::Enum<short>(val)
    {
    }
    
public:
    inline static InputState EnteringSubject()
    {
        return InputState(0);
    }
    
    inline static InputState EnteringClip()
    {
        return InputState(1);
    }
    
    inline static InputState Display()
    {
        return InputState(2);
    }
};

#endif
