#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    startTimerHz (1);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    juce::Image::BitmapData data (img, juce::Image::BitmapData::writeOnly);

    auto h = img.getHeight();
    auto w = img.getWidth();

    auto now = juce::Time::getMillisecondCounterHiRes();
    auto num = uint32_t (now);

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            auto d = (juce::PixelARGB*)data.getPixelPointer (x, y);
            //d->setARGB (0xFF, , , );
            d->components.b = (num + x) & 0xFF;
            d->components.g = (num + y) & 0xFF;
            d->components.r = (num + x + y) & 0xFF;
            d->components.a = 0xff;
        }
    }

    auto diff = juce::Time::getMillisecondCounterHiRes() - now;
    printf ("elapsed: %.2f ms\n", diff);

    g.drawImageAt (img, 0, 0);
}

void MainComponent::resized()
{
}

void MainComponent::timerCallback()
{
    repaint();
}
