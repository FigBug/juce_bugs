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
        auto bounds = getLocalBounds().toFloat();

	    auto c1 = juce::Colours::red;
	    auto c2 = juce::Colours::green;

	    auto gradRect = bounds.withSizeKeepingCentre (bounds.getWidth() / 2, bounds.getHeight());
        g.setColour (juce::Colours::white.withAlpha (0.2f));
        g.drawRect (gradRect, 2);

	    auto grad1 = juce::ColourGradient::horizontal (c1, c2, gradRect);

	    g.setFont (juce::Font (juce::FontOptions(15)));

        g.setGradientFill (grad1);

        g.drawText ("Hello World! Hello World! Hello World! Hello World! Hello World! Hello World!", gradRect, juce::Justification::centred, false);
    }
};

class Box : public juce::ListBox, 
			public juce::ListBoxModel
{
public:
	Box ()
	{
		setModel (this);
	}

	int	getNumRows () override
	{ 
		return 500;
	}
 
	void paintListBoxItem (int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected) override
	{
		auto bounds = juce::Rectangle<float> (0, 0, width, height);

	    auto c1 = juce::Colours::red;
	    auto c2 = juce::Colours::green;

	    auto gradRect = bounds.withSizeKeepingCentre (bounds.getWidth() / 2, bounds.getHeight());
        g.setColour (juce::Colours::white.withAlpha (0.2f));
        g.drawRect (gradRect, 2);

	    auto grad1 = juce::ColourGradient::horizontal (c1, c2, gradRect);

	    g.setFont (juce::Font (juce::FontOptions(15)));

        g.setGradientFill (grad1);

        g.drawText ("Hello World! Hello World! Hello World! Hello World! Hello World! Hello World!", gradRect, juce::Justification::centred, false);
	}
 	
	juce::Component* refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override
	{
		return nullptr;

		//if (existingComponentToUpdate == nullptr)
		//	return new Test();

		//return existingComponentToUpdate;
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
	juce::Component scaler;
    Box box;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
