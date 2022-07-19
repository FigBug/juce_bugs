#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible (a);
    addAndMakeVisible (b);

    setSize (600, 400);
    startTimerHz (30);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);

    auto ms = juce::Desktop::getInstance().getMainMouseSource();
    if (auto c = ms.getComponentUnderMouse())
        g.drawText ("Under mouse: " + c->getName(), getLocalBounds(), juce::Justification::centredTop, true);
}

void MainComponent::resized()
{
    auto rc = getLocalBounds().reduced (100);
    auto w = rc.getWidth() / 2;
    a.setBounds (rc.removeFromLeft (w));
    b.setBounds (rc.removeFromRight (w));
}

void MainComponent::timerCallback ()
{
    repaint();

    static int cnt = 0;
    cnt++;
    if (cnt % 90 == 0)
    {
        auto ms = juce::Desktop::getInstance().getMainMouseSource();

        if ((cnt / 90) % 2 == 0)
        {
            auto p = a.getScreenBounds().getCentre().toFloat();
            ms.setScreenPosition (p);
        }
        else
        {
            auto p = b.getScreenBounds().getCentre().toFloat();
            ms.setScreenPosition (p);
        }
    }
}
