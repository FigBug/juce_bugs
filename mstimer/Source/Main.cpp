/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

//==============================================================================
int main (int argc, char* argv[])
{

    for (int i = 0; i < 10000; i++)
    {
        printf ("%d %f\n", Time::getMillisecondCounter() % 1000, std::fmod (Time::getMillisecondCounterHiRes(), 1000));
    }


    return 0;
}
