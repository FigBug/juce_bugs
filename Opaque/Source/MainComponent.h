#pragma once

#include <JuceHeader.h>

// A tab component that is not opaque and redraws on mouse over
class TabComponent : public juce::Component
{
public:
    TabComponent (const juce::String& tabName, juce::Colour tabColour)
        : name (tabName), colour (tabColour), isMouseOver (false)
    {
        setOpaque (false);
    }

    void paint (juce::Graphics& g) override
    {
        if (isMouseOver)
            g.setColour (colour.brighter (0.3f));
        else
            g.setColour (colour);

        g.fillRoundedRectangle (getLocalBounds().toFloat(), 5.0f);

        g.setColour (juce::Colours::black);
        g.setFont (juce::FontOptions (14.0f));
        g.drawText (name, getLocalBounds(), juce::Justification::centred);
    }

    void mouseEnter (const juce::MouseEvent&) override
    {
        isMouseOver = true;
        repaint();
    }

    void mouseExit (const juce::MouseEvent&) override
    {
        isMouseOver = false;
        repaint();
    }

private:
    juce::String name;
    juce::Colour colour;
    bool isMouseOver;
};

// A tab bar component that is not opaque
class TabBarComponent : public juce::Component
{
public:
    TabBarComponent()
    {
        setOpaque (false);

        tabs.add (new TabComponent ("Tab 1", juce::Colours::lightblue));
        tabs.add (new TabComponent ("Tab 2", juce::Colours::lightgreen));
        tabs.add (new TabComponent ("Tab 3", juce::Colours::lightyellow));
        tabs.add (new TabComponent ("Tab 4", juce::Colours::lightcoral));

        for (auto* tab : tabs)
            addAndMakeVisible (tab);
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::darkgrey.withAlpha (0.5f));
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        int tabWidth = bounds.getWidth() / tabs.size();

        for (int i = 0; i < tabs.size(); ++i)
            tabs[i]->setBounds (i * tabWidth + 10, 10, tabWidth - 20, bounds.getHeight() - 20);
    }

private:
    juce::OwnedArray<TabComponent> tabs;
};

// A nested component that is opaque
class NestedComponent : public juce::Component
{
public:
    NestedComponent (int level, juce::Colour componentColour)
        : nestingLevel (level), colour (componentColour)
    {
        setOpaque (true);

        // Create the next level if we haven't reached the bottom
        if (level < 4)
        {
            nextLevel.reset (new NestedComponent (level + 1,
                juce::Colours::white.interpolatedWith (juce::Colours::black, level * 0.2f)));
            addAndMakeVisible (nextLevel.get());
        }
        else
        {
            // Create the tab bar component (not opaque)
            tabBar.reset (new TabBarComponent());
            addAndMakeVisible (tabBar.get());
        }
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (colour);

        g.setColour (juce::Colours::red);
        g.drawRect (getLocalBounds(), 2);

        g.setColour (juce::Colours::black);
        g.setFont (juce::FontOptions (12.0f));
        g.drawText ("Opaque Level " + juce::String (nestingLevel),
                    10, 10, 150, 20, juce::Justification::left);
    }

    void resized() override
    {
        // Set the next level to have the same bounds
        if (nextLevel != nullptr)
            nextLevel->setBounds (getLocalBounds());
        if (tabBar != nullptr)
            tabBar->setBounds (getLocalBounds());
    }

private:
    int nestingLevel;
    juce::Colour colour;
    std::unique_ptr<NestedComponent> nextLevel;
    std::unique_ptr<TabBarComponent> tabBar;
};

class MainComponent : public juce::Component
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    std::unique_ptr<NestedComponent> nestedComponents;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
