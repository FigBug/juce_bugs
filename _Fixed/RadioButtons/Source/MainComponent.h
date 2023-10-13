#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
	juce::ToggleButton toggleA { "cow" };
	juce::ToggleButton toggleB { "moose" };
	juce::ToggleButton toggleC { "duck" };
	juce::ToggleButton toggleD { "fish" };

	juce::Array<juce::ToggleButton*> buttons = { &toggleA, &toggleB, &toggleC, &toggleD };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
