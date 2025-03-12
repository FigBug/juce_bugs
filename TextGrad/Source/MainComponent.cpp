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

    auto bounds = getLocalBounds().withSizeKeepingCentre (300, 200);

	auto c1 = juce::Colours::blue;
	auto c2 = juce::Colours::green;

	auto gradRect = bounds.withTrimmedLeft (bounds.getWidth() / 2);
	auto grad = juce::ColourGradient::horizontal (c1, c2, gradRect);

	g.setGradientFill (grad);
	g.setFont (juce::Font (juce::FontOptions(40)));
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);

	g.fillRect (bounds.getX(), bounds.getCentreY() + 30, bounds.getWidth(), 30);
}

void MainComponent::resized()
{

}
