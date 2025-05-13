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

	juce::Image blurredImage (juce::Image::ARGB, 320, 200, true);

	juce::ImageConvolutionKernel blur (12);
	blur.createGaussianBlur (6);

	for (int i = 0; i < 10; ++i)
		blur.applyToImage (blurredImage, blurredImage, blurredImage.getBounds());

}

void MainComponent::resized()
{

}
