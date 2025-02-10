#pragma once

#include <JuceHeader.h>

class Keyboard : public juce::Component
{
public:
    Keyboard()
    {
    }

    int noteToY (int note)
    {
        return note * 10;
    }

    int getNoteHeight()
    {
        return 10;
    }

    void paint (juce::Graphics& g) override
    {
        bool rectlist = true;

        g.fillAll (juce::Colours::white);

        const int noteH = juce::jmax (2, getNoteHeight());

        float topY = (float) noteToY (0);
        float y = topY;

        // the note offset of the white notes, then the blacks
        static const int reorderedNotes[12] = { 0, 2, 4, 5, 7, 9, 11, 1, 3, 6, 8, 10 };

        g.setFont (juce::jmin (noteH * 1.3f, 10.0f));

        {
            juce::RectangleList<float> lines, highlights;
            const float w = getWidth() - 2.0f;

            for (int octave = 0; octave < 128; octave += 12)
            {
                const float nextOctaveY = (float) noteToY (octave + 12);
                const float dwy = (nextOctaveY - y) / 7.0f;
                float wy = y;

                for (int white = 0; white < 7; ++white)
                {
                    const juce::Rectangle<float> l (juce::Rectangle<float> (1.0f, wy, w, 0.5f));
                    lines.addWithoutMerging (l);
                    highlights.add (l.translated (0.0f, -1.0f));
                    highlights.add (l.translated (0.0f, 1.0f));

                    wy += dwy;
                }

                y = nextOctaveY;
            }

            g.setColour (juce::Colours::yellow.withAlpha (1.0f));
            
            if (rectlist)
                g.fillRectList (highlights);
            else
                for (auto r : highlights)
                    g.fillRect(r);

            g.setColour (juce::Colours::black.withAlpha (0.8f));

            if (rectlist)
                g.fillRectList (lines);
            else
                for (auto r : lines)
                    g.fillRect(r);
        }

        y = topY;

        for (int octave = 0; octave < 128; octave += 12)
        {
            const float nextOctaveY = (float) noteToY (octave + 12);
            int n = 7;

            const int bw = proportionOfWidth (0.6f);

            for (int black = 0; black < 5; ++black)
            {
                const int note = octave + reorderedNotes[n++];
                const int ypos = noteToY (note + 1);
                juce::Rectangle<int> r (0, ypos, bw, noteH);

                if (! getLocalBounds().expanded (noteH).getVerticalRange().contains (ypos))
                    continue;

                g.setColour (juce::Colours::black);
                g.fillRect (r);

                g.setColour (juce::Colours::yellow.withAlpha (0.16f));
                g.drawRect (r.reduced (1).withTrimmedRight (-2).translated (-2, 0));

                g.setColour (juce::Colours::black);
                g.drawRect (r.withTrimmedRight (-1).translated (-1, 0));
            }

            y = nextOctaveY;
        }
    }

};


class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    Keyboard k;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
