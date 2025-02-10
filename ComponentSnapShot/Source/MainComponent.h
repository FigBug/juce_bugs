#pragma once

#include <JuceHeader.h>

class Source : public juce::Component
{
public:
	void paint (juce::Graphics& g) override
	{
		g.setColour (juce::Colours::red);
		g.setFont (juce::FontOptions (50.0f));
		g.drawText (juce::Time::getCurrentTime().toString (false, true), getLocalBounds(), juce::Justification::centred);
	}
};

class Dest : public juce::Component
{
public:
	void paint (juce::Graphics& g) override
	{
		if (image.isValid())
			g.drawImageAt (image, 0, 0);
	}

	juce::Image image;
};


//==============================================================================
class MainComponent : public juce::Component,
					  private juce::Timer
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
	void timerCallback() override;

	Source source;
	Dest dest;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
