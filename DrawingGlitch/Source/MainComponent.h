#pragma once

#include <JuceHeader.h>

//==============================================================================
class Bar : public juce::Component,
			public juce::Timer
{
public:
	Bar ()
	{
		setOpaque (true);
		startTimerHz ( 30 );
	}

	void timerCallback() override
	{
		pos += 0.01f;
		if (pos > 1.0f)
			pos -= 1.0f;
		repaint();
	}

	void paint (juce::Graphics& g) override
	{
		g.fillAll (juce::Colour (4281151797U));
		g.setColour (juce::Colour (4280337383U));
		g.fillRect (getLocalBounds().toFloat().withWidth (getWidth() * (1.0 - pos)));
	}

	float pos = 0.0f;
};


//==============================================================================
class Wrapper : public juce::Component
{
public:
	Wrapper ()
	{
		setTransform (juce::AffineTransform ().scaled (0.75f));
		addAndMakeVisible (bar);
		bar.setBounds (10, 10, 150, 24);
	}

	void paint ( juce::Graphics& g) override
	{
		g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
	}

	Bar bar;
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
