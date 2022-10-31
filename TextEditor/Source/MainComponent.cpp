#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible (t1);
    addAndMakeVisible (t2);
    t1.setText ("Test1");
    t2.setText ("Test2");
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
    auto rc = getLocalBounds().reduced (8);
    t1.setBounds (rc.removeFromTop (24));
    rc.removeFromTop (8);
    t2.setBounds(rc.removeFromTop (24));
}
