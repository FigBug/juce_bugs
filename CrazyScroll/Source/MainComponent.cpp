#include "MainComponent.h"

class Frame : public juce::Component
{
public:
    Frame()
    {
        setSize(2000, 100);

        for (int i = 0; i < 20; i++)
        {
            auto b = new juce::TextButton ("hi");
            b->setBounds(i * 100, 0, 100, 24);
            b->onClick = [b]
            {
                delete b;
            };
            addAndMakeVisible (b);
        }
    }

    ~Frame() override
    {
        deleteAllChildren();
    }
};

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    addAndMakeVisible (viewport);
    viewport.setViewedComponent (new Frame());
    viewport.setScrollOnDragMode (juce::Viewport::ScrollOnDragMode::all);
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
    viewport.setBounds (getLocalBounds());
}
