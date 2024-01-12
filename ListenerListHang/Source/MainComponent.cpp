#include "MainComponent.h"

class Dialog : public juce::Component
{
public:
	Dialog (juce::Component& p) : parent (p)
	{
		frame.setBounds (0, 0, 600, 400);
		parent.addAndMakeVisible (frame);

		setBounds (50, 50, 500, 300);
		frame.addAndMakeVisible (this);
		enterModalState();
	}

	void mouseUp (const juce::MouseEvent&) override
	{
		parent.removeChildComponent (&frame);
		
		exitModalState (0);
		delete this;
	}

	void paint (juce::Graphics& g) override
	{
		g.fillAll(juce::Colours::white);
	}

	juce::Component frame;
	juce::Component& parent;
};

//==============================================================================
MainComponent::MainComponent()
{
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

void MainComponent::mouseUp (const juce::MouseEvent& e)
{
	new Dialog (*this);
}

void MainComponent::resized()
{
}
