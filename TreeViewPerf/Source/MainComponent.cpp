#include "MainComponent.h"

class Item : public juce::TreeViewItem
{
public:
    Item (int i) : num(i)
    {
        
    }
    
    bool mightContainSubItems() override
    {
        return num == 0;
    }
    
    void paintItem (juce::Graphics& g, int width, int height) override
    {
        auto rc = juce::Rectangle<int>(0, 0, width, height);
        
        g.setColour(juce::Colours::white);
        g.drawText(juce::String (num), rc, juce::Justification::centred);
    }
    
    int num = 0;
};

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    addAndMakeVisible (tree);
    
  
    auto root = new Item (0);
    
    for (int i = 0; i < 10000; i++)
    {
        root->addSubItem (new Item (i + 1));
    }
    
    tree.setRootItemVisible (false);
    tree.setRootItem (root);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    tree.setBounds(getLocalBounds());
}
