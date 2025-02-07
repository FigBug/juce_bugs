#include <JuceHeader.h>

juce::String code = R"(

var ignore = 0;

function MyObj() {
    this.i = 0;
    this.func = function() {
        // we need to do a bunch of stuff here to make sure interupt handler runs
        for (var i = 1; i < 10000; i++)
            ignore = i;

        this.i++;
        return this.i;
    }
}

var myObj = new MyObj();

)";

//==============================================================================
int main (int argc, char* argv[])
{
    auto err = juce::Result::ok();

    juce::JavascriptEngine eng;
    eng.maximumExecutionTime = juce::RelativeTime::seconds (10);

    err = eng.execute (code);
    if (! err.wasOk())
    {
        printf ("%s\n", err.getErrorMessage().toRawUTF8());
        return 1;
    }

    for (auto i = 0; i < 100; i++)
    {
        auto root = eng.getRootObject();
        auto child = root.getChild (juce::Identifier ("myObj"));

        // uncomment to work around bug
        //eng.execute (";");

        auto res = child.invokeMethod ("func", {}, &err);

        if (! err.wasOk())
        {
            printf ("\n\n%s\n", err.getErrorMessage().toRawUTF8());
            return 1;
        }

        printf ("%d\n", int (res));

        juce::Thread::sleep (1000);
    }

    return 0;
}
