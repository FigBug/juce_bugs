#pragma once

#include <JuceHeader.h>

class Child : public juce::Component, public juce::SettableTooltipClient
{
public:
	Child()
	{
		setTooltip ("Pika Pika");
		setTransform (juce::AffineTransform().scaled (0.5f));
	}

	void paint (juce::Graphics& g) override
	{
		g.fillAll (juce::Colours::red);
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
	juce::TooltipWindow tooltip;
	Child child;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
