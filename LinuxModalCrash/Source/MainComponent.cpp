/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

struct PopupMenuCallback    : public PopupMenu::CustomCallback
{
    PopupMenuCallback (std::function<void()> fn, Component::SafePointer<Component> componentToWatch = nullptr)
        : function (std::move (fn)), component (componentToWatch), checkComponent (componentToWatch != nullptr)
    {
        jassert (function);
    }
    
    bool menuItemTriggered() override
    {
        if (! checkComponent || component != nullptr)
            function();
        
        return false;
    }
    
private:
    std::function<void()> function;
    Component::SafePointer<Component> component;
    bool checkComponent = false;
};

static inline void addCustomCallback (PopupMenu& m, const String& text, std::function<void()> callback)
{
    PopupMenu::Item mi;
    mi.text << text;
    mi.itemID = -1;
    mi.customCallback = new PopupMenuCallback (std::move (callback));
    m.addItem (mi);
}

class AnotherWindow : public DocumentWindow
{
public:
    AnotherWindow() : DocumentWindow ("Another Window", Colours::pink, DocumentWindow::closeButton, false)
    {
        setVisible (true);
        toFront (false);

        centreWithSize (30, 30);        
        
        setAlwaysOnTop (true);
        addToDesktop();
    }
    
    void closeButtonPressed() override
    {
        setVisible (false);
    }
    
};

class InterrupterComponent : public Component
{
    void paint (Graphics& g) override
    {
        g.fillAll (Colours::green);
    }
};

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::mouseUp (const MouseEvent&)
{
    PopupMenu m;
    addCustomCallback (m, "Crash",
                           [&] {
                               InterrupterComponent c ;
                               addAndMakeVisible (&c);
                               c.setBounds (getLocalBounds());
                               
                               int i = 250;
                               while (--i > 0)
                                   if (! MessageManager::getInstance()->runDispatchLoopUntil (10))
                                       break;
                               
                               c.exitModalState (0);
                               c.setVisible (false);
                               
                               aw = new AnotherWindow();
                           });
    
    m.showMenu (PopupMenu::Options());
}

void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
}
