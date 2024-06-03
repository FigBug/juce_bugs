#include "MainComponent.h"

class Content : public juce::Component
{
public:
    Content()
    {
        setSize (70, 40);

        button.setName ("click");
        button.setButtonText ("click");
        button.setBounds (10, 10, 50, 20);
        addAndMakeVisible (button);
        button.onClick = [this]
        {
            juce::Timer::callAfterDelay (1000, [this]
            {
                if (auto c = findParentComponentOfClass<juce::CallOutBox>())
                    c->dismiss();
            });

            juce::FileChooser fc ("Open");
            if (fc.browseForMultipleFilesToOpen())
            {
            }
        };
    }

    juce::TextButton button;
};

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);

    button.setName ("click");
    button.setButtonText ("click");
    addAndMakeVisible (button);
    button.onClick = [this]
    {
        auto area = localAreaToGlobal (button.getBounds());
        juce::CallOutBox::launchAsynchronously (std::make_unique<Content>(), area, nullptr);
    };
}

MainComponent::~MainComponent()
{
}

void MainComponent::mouseUp (const juce::MouseEvent&)
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    button.setBounds (getLocalBounds().withSizeKeepingCentre (50, 20));
}
