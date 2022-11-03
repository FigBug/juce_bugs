#pragma once

#include <JuceHeader.h>

//==============================================================================
class MainComponent  : public juce::Component
					 , public juce::ListBoxModel
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
	int getNumRows() override
	{
		return 100;
	}

	void paintListBoxItem (int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override
	{
		if (rowIsSelected)
			g.fillAll (juce::Colours::purple);

		g.setColour (juce::Colours::white);
		g.drawText ("row " + juce::String (rowNumber + 1), 0, 0, width, height, juce::Justification::centred);
	}

	juce::String getNameForRow (int rowNumber) override
	{
		return "row " + juce::String (rowNumber + 1);
	}

    juce::ListBox box;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
