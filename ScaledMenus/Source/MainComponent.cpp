#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible (frame);
    frame.setTransform (juce::AffineTransform().scale (0.5f));
    frame.addAndMakeVisible (menuButton);
    setSize (600, 400);

    menuButton.onClick = [this]
    {
        juce::PopupMenu m;
        m.setLookAndFeel (&wackyLookAndFeel);

        m.addItem("A", [](){});
        m.addItem("B", [](){});
        m.addItem("C", [](){});
        m.addItem("D", [](){});

        m.showMenuAsync (juce::PopupMenu::Options().withTargetComponent (menuButton).withDeletionCheck (menuButton));
    };
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
    frame.setBounds(getLocalBounds());
    menuButton.setBounds (frame.getLocalBounds().withSizeKeepingCentre (47, 47));
}
