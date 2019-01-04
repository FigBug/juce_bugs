/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================


struct Thingy
{
    ~Thingy();
    int cnt = 0;
};

ScopedPointer<Thingy> thingy;

Thingy::~Thingy()
{
    cnt++;
    if (cnt == 2)
        printf ("Deconstructors should only be called once!\n");
    
    thingy.reset();
}

int main (int argc, char* argv[])
{
    thingy.reset (new Thingy());
    thingy.reset();
    
    return 0;
}
