/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

//==============================================================================
int main (int argc, char* argv[])
{
    auto start = juce::Time::getCurrentTime();
    system ("whoami");
    auto end = juce::Time::getCurrentTime();

    DBG((end - start).getDescription());


    return 0;
}
