/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

struct PopupMenuCallback : public PopupMenu::CustomCallback
{
    PopupMenuCallback (std::function<void()> fn)
        : function (std::move (fn))
    {
    }

    bool menuItemTriggered() override
    {
        if (function)
            function();

        return false;
    }

private:
    std::function<void()> function;
};

//==============================================================================
/** Simple dialog window that deletes its contents when closed. */
class OwnedDialogWindow   : public DialogWindow,
                            public DeletedAtShutdown
{
public:
    OwnedDialogWindow (DialogWindow::LaunchOptions& options);

    void closeButtonPressed() override;

    void setContentComponentBorder (BorderSize<int>);
    BorderSize<int> getContentComponentBorder() override;

private:
    BorderSize<int> contentComponentBorder;
    bool contentComponentBorderSet = false;

    JUCE_DECLARE_NON_COPYABLE (OwnedDialogWindow)
};

//==============================================================================
/** Simple dialog window that deletes its contents when closed. */
OwnedDialogWindow::OwnedDialogWindow (DialogWindow::LaunchOptions& options)
    : DialogWindow (options.dialogTitle, options.dialogBackgroundColour,
        options.escapeKeyTriggersCloseButton, true)
{
    setUsingNativeTitleBar (options.useNativeTitleBar);

    if (options.content.willDeleteObject())
        setContentOwned (options.content.release(), true);
    else
        setContentNonOwned (options.content.release(), true);

    centreAroundComponent (options.componentToCentreAround, getWidth(), getHeight());
    setResizable (options.resizable, options.useBottomRightCornerResizer);
}

void OwnedDialogWindow::closeButtonPressed()
{
    setVisible (false);
    delete this;
}

void OwnedDialogWindow::setContentComponentBorder (BorderSize<int> bs)
{
    contentComponentBorder = bs;
    contentComponentBorderSet = true;
    resized();
}

BorderSize<int> OwnedDialogWindow::getContentComponentBorder()
{
    return contentComponentBorderSet ? contentComponentBorder : DialogWindow::getContentComponentBorder();
}

struct AsyncFocusGrabber : public CallbackMessage
{
    AsyncFocusGrabber (Component& comp) : c (&comp) {}

    ~AsyncFocusGrabber()
    {
        if (c != nullptr)
            c->grabKeyboardFocus();
    }

    void messageCallback() override {}

    Component::SafePointer<Component> c;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AsyncFocusGrabber)
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
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
}

void MainComponent::resized()
{
}

void MainComponent::mouseDown (const MouseEvent&) 
{
    auto callback1 = []
    {
        auto callback2 = []
        {
            DialogWindow::LaunchOptions o;
            o.dialogTitle                   = TRANS("Dialog");
            o.dialogBackgroundColour        = Colours::white;
            o.escapeKeyTriggersCloseButton  = true;
            o.useNativeTitleBar             = false;
            o.resizable                     = true;
            o.useBottomRightCornerResizer   = false;

            auto c = new Component();
            c->setSize (250, 160);
            o.content.setOwned (c);

            OwnedDialogWindow* odw = new OwnedDialogWindow (o);
            odw->setAlwaysOnTop (true);
            odw->setVisible (true);
            odw->setTitleBarHeight (0);
            (new AsyncFocusGrabber (*c))->post();
        };

        PopupMenu m2;

        PopupMenu::Item mi;
        mi.text << "Show Dialog";
        mi.itemID = -1;
        mi.customCallback = new PopupMenuCallback (std::move (callback2));
        m2.addItem (mi);

        m2.show();
    };

    PopupMenu m;

    PopupMenu::Item mi;
    mi.text << "Show Menu";
    mi.itemID = -1;
    mi.customCallback = new PopupMenuCallback (std::move (callback1));
    m.addItem (mi);

    m.show();
}