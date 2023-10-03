#include "MainComponent.h"

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
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

	auto font = juce::Font ("Inter", 16.0f, juce::Font::plain);
    g.setFont (font);
    g.setColour (juce::Colours::white);

	auto text = "triangle -> saw";
	auto textArea = getLocalBounds().withSizeKeepingCentre(200, 20);


	g.drawText (text, textArea, juce::Justification::centred, false);
	//g.drawFittedText ( text, textArea, juce::Justification::centred, std::max ( 1, (int) ( ( float ) textArea.getHeight () / font.getHeight () ) ), 0.5f );
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
