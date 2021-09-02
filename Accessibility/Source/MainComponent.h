#pragma once

#include <JuceHeader.h>

//==============================================================================
class MainComponent  : public juce::Component,
					   private juce::ListBoxModel
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

	int getNumRows() override;
	void paintListBoxItem (int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
	juce::String getNameForRow (int rowNumber) override;

private:
    //==============================================================================
	juce::ListBox box;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
