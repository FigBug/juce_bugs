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

	int w = getWidth();
	int h = getHeight();

	juce::Image blurredImage (juce::Image::ARGB, w, h, true);

	{
		juce::Graphics gi (blurredImage);
		gi.fillAll (juce::Colours::blue);

		gi.setColour (juce::Colours::red);
		gi.drawRect (w/4, h/4, w/2, h/2, 5);
	}

	juce::ImageConvolutionKernel blur (12);
	blur.createGaussianBlur (6);

	blur.applyToImage (blurredImage, blurredImage, blurredImage.getBounds());

	g.drawImageAt (blurredImage, 0, 0);
}

void MainComponent::resized()
{

}
