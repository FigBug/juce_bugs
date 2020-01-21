/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

class MyItem : public TreeViewItem
{
public:
    bool mightContainSubItems() override { return true; }
    
    void paintItem (Graphics& g, int width, int height) override
    {
        g.setFont (12);

        int w = getOwnerView()->getWidth() / 6;

        auto r = juce::Rectangle<int> (0, 0, width, height);

        int indentX = getItemPosition (true).getX();
        
        // Draw columns
        g.setColour (Colours::lightgrey.withAlpha (0.3f));
        auto rc = juce::Rectangle<int> (0, 0, width, height);
        rc.removeFromLeft (w - indentX + rc.getHeight());
        for (int i = 0; i < 6; i++)
        {
            if (i % 2 == 0)
                g.fillRect (rc.removeFromLeft (w));
            else
                rc.removeFromLeft (w);
        }

        // Text
        Colour c = Colours::black;
        
        auto ri = r.removeFromLeft (r.getHeight());
        g.setColour (c);
        g.fillEllipse (ri.reduced (4).toFloat());

        // 1: Type
        g.setColour (Colours::black);
        auto r1 = r.removeFromLeft (w - indentX).reduced (3, 0);

        g.drawFittedText ("t1", r1, Justification::centredLeft, 1);
        
        // 2: Mode / Ident
            g.drawFittedText ("t2", r.removeFromLeft (w).reduced (3, 0), Justification::centredLeft, 1);
        
        // 3: Module
        g.drawFittedText ("t3", r.removeFromLeft (w).reduced (3, 0), Justification::centredLeft, 1);
        
        // 4: Surface
        g.drawFittedText ("t4", r.removeFromLeft (w).reduced (3, 0), Justification::centredLeft, 1);
        
        // 5: Fixed value
        r.removeFromLeft (w);

        // 6: Feedback
        const auto r6 = r.removeFromLeft (w).reduced (3, 0);
        g.setColour (Colours::pink.withAlpha (0.3f));
        g.fillRect (r6);
        g.setColour (Colours::black);
        g.drawFittedText ("t6", r6, Justification::centredLeft, 1);
    }
};

//==============================================================================
MainComponent::MainComponent()
{
    auto root = new MyItem();
    root->setOpen (true);
    tree.setRootItem (root);
    root->addSubItem (new MyItem());
    root->addSubItem (new MyItem());
    root->addSubItem (new MyItem());
    root->addSubItem (new MyItem());
    root->addSubItem (new MyItem());
    root->addSubItem (new MyItem());

    addAndMakeVisible (tree);
    setSize (330, 400);
}

MainComponent::~MainComponent()
{
    tree.deleteRootItem();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void MainComponent::resized()
{
    tree.setBounds (getLocalBounds());
}
