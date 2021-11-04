/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class Foo
{
public:
    ~Foo()
    {
        DBG("I'm deleted!");
    }

private:
    JUCE_LEAK_DETECTOR(Foo);
};

int main (int argc, char* argv[])
{
    OptionalScopedPointer<Foo> foo;
    foo.set (new Foo(), true);
    foo.reset();
    foo.release();

    return 0;
}
