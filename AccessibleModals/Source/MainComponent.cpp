#include "MainComponent.h"

class Modal : public juce::Component
{
public:
    Modal()
    {
        addAndMakeVisible (close);
        close.setBounds ( 10, 10, 75, 20 );
        close.onClick = [ this ] { delete this; };
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::white);
    }

    juce::TextButton close { "close" };
};

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(open);
    open.onClick = [ this ]
    {
        auto m = new Modal();
        m->setBounds (200, 100, 200, 200);
        addAndMakeVisible (m);
        m->enterModalState();
    };

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
    open.setBounds ( 10, 10, 75, 20 );
}
