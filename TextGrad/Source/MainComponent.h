#pragma once

#include <JuceHeader.h>

class Test : public juce::Component
{
public:
    Test ()
    {
    }

    void paint (juce::Graphics& g)
    {
        auto bounds = getLocalBounds();

        g.setColour (juce::Colours::white);
        g.drawRect (getLocalBounds(), 2);

        g.reduceClipRegion (bounds);

	    auto c1 = juce::Colours::red;
	    auto c2 = juce::Colours::green;

	    auto gradRect = bounds.withSizeKeepingCentre (bounds.getWidth() / 2, bounds.getHeight());
        g.setColour (juce::Colours::white.withAlpha (0.2f));
        g.drawRect (gradRect, 2);

	    auto grad1 = juce::ColourGradient::horizontal (c1, c2, gradRect);
        auto grad2 = juce::ColourGradient::horizontal (c1, c2, getLocalBounds()); 

        grad2.addColour (gradRect.getX() / float (bounds.getWidth()), c1);
        grad2.addColour (gradRect.getRight() / float (bounds.getWidth()), c2);

	    g.setFont (juce::Font (juce::FontOptions(40)));

        auto rc = getLocalBounds();

        g.setGradientFill (grad1);
        g.drawText ("Hello World! Hello World!", rc.removeFromTop (rc.getHeight() / 2), juce::Justification::centred, false);
        g.setGradientFill (grad2);
        g.drawText ("Hello World! Hello World!", rc, juce::Justification::centred, false);
    }
};

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
    Test test;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
