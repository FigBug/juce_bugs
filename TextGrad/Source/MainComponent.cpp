#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (650, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

	auto c1 = juce::Colours::blue;
	auto c2 = juce::Colours::green;

	auto gradRect = getLocalBounds().withTrimmedLeft (getWidth() / 2);
	auto grad = juce::ColourGradient::horizontal (c1, c2, gradRect);

	g.setGradientFill (grad);
	g.setFont (juce::Font (juce::FontOptions(40)));
    g.drawText ("Hello World! Hello World! Hello World!", getLocalBounds(), juce::Justification::centred, true);

	g.fillRect (0, getHeight() / 2 + 30, getWidth(), 30);
}

void MainComponent::resized()
{

}
