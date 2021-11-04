#include "MainComponent.h"

juce::StringArray words = { "Cow", "Moose", "Chicken", "Duck", "Clam", "Fish", "Bat", "Whale" };

//==============================================================================
MainComponent::MainComponent()
{
    words.sortNatural();

    box.setTitle ("animals");
    box.setModel (this);
    box.updateContent();
    addAndMakeVisible (box);
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    box.setBounds (getLocalBounds());
}

int MainComponent::getNumRows()
{
    return words.size();
}

void MainComponent::paintListBoxItem (int rowNumber, juce::Graphics& g, int width, int height, bool selected)
{
    if (selected)
    {
        g.setColour (juce::Colours::pink);
        g.fillRect (0, 0, width, height);
    }

    g.setColour (juce::Colours::white);
    g.drawText (words[rowNumber], 0, 0, width, height, juce::Justification::centred);
}

juce::String MainComponent::getNameForRow (int rowNumber)
{
    return words[rowNumber];
}
