#pragma once

#include <JuceHeader.h>

//==============================================================================
class Bar : public juce::Component
{
public:
	Bar (bool fa) : fillAll (fa)
	{
		setOpaque (true);
	}

	void paint (juce::Graphics& g) override
	{
        if (fillAll)
        {
            g.fillAll (juce::Colours::darkgrey);
        }
        else
        {
            g.setColour (juce::Colours::darkgrey);
            g.fillRect (getLocalBounds().expanded (100));
        }
	}

	juce::ComponentDragger myDragger;

	void mouseDown (const juce::MouseEvent& e) override
	{
		myDragger.startDraggingComponent (this, e);
	}

	void mouseDrag (const juce::MouseEvent& e) override
	{
		myDragger.dragComponent (this, e, nullptr);
	}

    bool fillAll = false;
};

//==============================================================================
class Wrapper : public juce::Component
{
public:
	Wrapper ()
	{
		setTransform (juce::AffineTransform ().scaled (0.70f));

		addAndMakeVisible (bar1);
		addAndMakeVisible (bar2);
	}

	void paint ( juce::Graphics& g) override
	{
		g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
	}

	void resized () override
	{
        bar1.setBounds (209, 194, 100, 100);
        bar2.setBounds (209, 194 + 105, 100, 100);
	}

    Bar bar1 { true };
    Bar bar2 { false };
};

//==============================================================================
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
	Wrapper wrapper;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
