#include "MainComponent.h"
#include "font_roboto_medium.h"

//==============================================================================
MainComponent::MainComponent()
{
    auto tf = juce::Typeface::createSystemTypefaceFor (RobotoMedium_ttf, sizeof (RobotoMedium_ttf));
    font = juce::Font(tf);

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

    auto rc = getLocalBounds().reduced(100);

    g.setColour(juce::Colours::purple);
    g.fillRect(rc);

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);

    auto text = juce::String ("Artist_Series 7_Skies_2");
    text = text.replace ( "_", juce::CharPointer_UTF8 ( "\xc2\xa0" ) );

    //g.setFont(font);
    g.drawFittedText ( text, rc, juce::Justification::centred, 3, 1.0f );
}

void MainComponent::resized()
{
}
