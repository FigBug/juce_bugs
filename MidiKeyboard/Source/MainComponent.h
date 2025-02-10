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

    juce::Array<int> highlightedNotes, pressedNotes;

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::white);

        juce::Array<int> selectedNotes;

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
            g.fillRectList (highlights);

            g.setColour (juce::Colours::black.withAlpha (0.8f));
            g.fillRectList (lines);
        }

        y = topY;

        for (int octave = 0; octave < 128; octave += 12)
        {
            const float nextOctaveY = (float) noteToY (octave + 12);
            const float dwy = (nextOctaveY - y) / 7.0f;
            float wy = y;
            int n = 0;

            for (int white = 0; white < 7; ++white)
            {
                const int note = octave + reorderedNotes[n++];
                if (selectedNotes.contains (note))
                {
                    g.setColour (juce::Colours::pink.withAlpha (highlightedNotes.contains (note) ? 0.6f : 0.3f));
                    g.fillRect (1.0f, wy - std::abs (dwy) + 0.5f, getWidth() - 2.0f, std::abs (dwy) - 0.5f);
                }
                else if (highlightedNotes.contains (note))
                {
                    g.setColour (juce::Colours::orange);
                    g.fillRect (1.0f, wy - std::abs (dwy) + 0.5f, getWidth() - 2.0f, std::abs (dwy) - 0.5f);
                }

                if (pressedNotes.contains (note))
                {
                    auto rc = juce::Rectangle<float> (1.0f, wy - std::abs (dwy) + 0.5f, getWidth() - 2.0f, std::abs (dwy) - 0.5f);
                    rc = rc.removeFromRight (rc.getHeight()).reduced (1.5f);

                    g.setColour (juce::Colours::black.withAlpha (0.8f));
                    g.fillEllipse (rc);
                }

                wy += dwy;
            }

            const int bw = proportionOfWidth (0.6f);

            for (int black = 0; black < 5; ++black)
            {
                const int note = octave + reorderedNotes[n++];
                const int ypos = noteToY (note + 1);
                juce::Rectangle<int> r (0, ypos, bw, noteH);

                if (! getLocalBounds().expanded (noteH).getVerticalRange().contains (ypos))
                    continue;

                if (selectedNotes.contains (note))
                {
                    g.setColour (juce::Colours::pink.withAlpha (highlightedNotes.contains (note) ? 0.6f : 0.3f));
                    g.fillRect (r);
                }
                else if (highlightedNotes.contains (note))
                {
                    g.setColour (juce::Colours::orange);
                    g.fillRect (r);
                }
                else
                {
                    g.setColour (juce::Colours::black);
                    g.fillRect (r);

                    g.setColour (juce::Colours::yellow.withAlpha (0.16f));
                    g.drawRect (r.reduced (1).withTrimmedRight (-2).translated (-2, 0));
                }

                g.setColour (juce::Colours::black);
                g.drawRect (r.withTrimmedRight (-1).translated (-1, 0));

                if (pressedNotes.contains (note))
                {
                    auto rc = r.toFloat();
                    rc = rc.removeFromRight (rc.getHeight()).reduced (1.5f);

                    g.setColour (selectedNotes.contains (note) ? juce::Colours::black.withAlpha (0.8f) : juce::Colours::yellow.withAlpha (1.0f));
                    g.fillEllipse (rc);
                }
            }

            auto noteName = juce::MidiMessage::getMidiNoteName (octave, true, true, 4);
            g.setColour (juce::Colours::black);

            auto tx = proportionOfWidth (0.7f);
            auto ty = (int) (y - noteH / 3);

            if (noteH > 5)
                g.drawSingleLineText (noteName, tx, ty);

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
