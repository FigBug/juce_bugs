#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);

	image = juce::ImageFileFormat::loadFrom(BinaryData::pikachu_png, BinaryData::pikachu_pngSize);

	startTimerHz(60);

	juce::Timer::callAfterDelay ( 5000, [ this ]
		{
			if ( auto peer = getPeer())
			{
				auto engines = peer->getAvailableRenderingEngines ();

				peer->setCurrentRenderingEngine ( engines.indexOf ( "Software Renderer" ) );
			}
		} );
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

	g.drawImage (image, {x, 0.0f, 512.0f, 445.0f});
}

void MainComponent::resized()
{
}

void MainComponent::timerCallback()
{
	x += 0.05f;
	if ( x > getWidth() )
		x = 0;
	repaint();
}
