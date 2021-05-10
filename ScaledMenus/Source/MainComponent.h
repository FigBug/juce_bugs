#pragma once

#include <JuceHeader.h>

//==============================================================================
class WackyLookAndFeel : public juce::LookAndFeel_V4
{
public:
	WackyLookAndFeel()
	{
	}

	void preparePopupMenuWindow (juce::Component& newWindow) override
	{
		newWindow.setOpaque (false);
	}
};

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
	juce::Component frame;
	juce::TextButton menuButton { "menu" };
	WackyLookAndFeel wackyLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
