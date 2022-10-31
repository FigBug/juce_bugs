#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    startTimer (1000);
    setSize (600, 400);

    addAndMakeVisible(box);
    auto& m = *box.getRootMenu();
    m.addItem (1, "a");
    m.addItem ("b", [] {});
    m.addItem (2, "c");
    m.addItem ("d", [] {});
    m.addItem (3, "e");
    m.addItem ("f", [] {});
}

MainComponent::~MainComponent()
{
}

void MainComponent::timerCallback()
{
    static int count = 0;

    juce::StringArray str = { "a", "b", "c", "d", "e", "f" };

    box.setText (str[count % str.size()]);

    count++;
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    box.setBounds (10, 10, 200, 24);
}
