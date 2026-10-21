#include <juce_core/juce_core.h>
#include <juce_javascript/juce_javascript.h>

// Repro: a var holding a JS function outlives the JavascriptEngine that created it.
//
// The NativeFunction wrapper (detail::quickJSToJuce, Callable) stores a raw
// JSContext* plus two JSValues and calls JS_FreeValue on them in its destructor.
// Once the engine is destroyed the JSContext/JSRuntime are gone, so destroying
// the var (or calling it) is a use-after-free.

int main (int argc, char* argv[])
{
    const bool callAfterDeath = argc > 1 && juce::String (argv[1]) == "call";

    juce::var fn;

    {
        juce::JavascriptEngine engine;

        auto err = juce::Result::ok();
        fn = engine.evaluate ("(function (x) { return x * 2; })", &err);

        if (! err.wasOk())
        {
            printf ("evaluate failed: %s\n", err.getErrorMessage().toRawUTF8());
            return 1;
        }

        jassert (fn.isMethod());

        juce::var args[] = { 21 };
        auto result = fn.getNativeFunction() (juce::var::NativeFunctionArgs (juce::var(), args, 1));
        printf ("call while engine alive: %d\n", int (result));

        printf ("destroying engine...\n");
    }

    printf ("engine destroyed, var still alive\n");

    if (callAfterDeath)
    {
        printf ("calling function after engine destroyed...\n");
        juce::var args[] = { 21 };
        auto result = fn.getNativeFunction() (juce::var::NativeFunctionArgs (juce::var(), args, 1));
        printf ("call after engine destroyed: %d\n", int (result));
    }

    printf ("releasing var...\n");
    fn = juce::var();
    printf ("survived\n");

    return 0;
}
