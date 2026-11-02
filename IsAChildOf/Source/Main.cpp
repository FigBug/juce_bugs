#include <JuceHeader.h>
#include <iostream>

//==============================================================================
// juce::File::isAChildOf() never returns for a File whose path contains no
// separators (Windows): File::getParentDirectory() returns the file itself,
// because getPathUpToLastSlash() finds no separator and returns fullPath
// unchanged, so isAChildOf() recurses until the stack overflows.
//
// Such a File is easy to create on Windows: parseAbsolutePath() accepts any
// string containing a ':' as-is, so a drive-relative path like "C:foo" -
// which is legal Windows path syntax - becomes a File with fullPath "C:foo".
//
// We hit this in production: a settings file containing a Windows path with
// unescaped backslashes ("F:\ABLETON\...") was run through juce::JSON, whose
// lenient escape handling silently turns \A into A, \r into CR, etc.,
// producing a separator-less path. Passing that File to isAChildOf() killed
// the app with a stack overflow.
//
// Note that well-formed network paths are NOT affected: a UNC path walks up
// "\\server\share" -> "\\server" -> "\" and the length check terminates the
// recursion. Only a separator-less path longer than the potential parent
// recurses forever.

int main (int, char*[])
{
    // Well-formed paths terminate, including UNC paths:
    juce::File unc ("\\\\server\\share\\folder");
    std::cout << "UNC path isAChildOf (C:\\): "
              << (unc.isAChildOf (juce::File ("C:\\")) ? "true" : "false")
              << " (returned fine)" << std::endl;

    // A drive-relative path: legal Windows syntax, accepted verbatim by the
    // juce::File constructor since it contains a ':'
    juce::File degenerate ("C:foo");

    // Its parent directory is itself...
    std::cout << "getParentDirectory() of \"C:foo\": \""
              << degenerate.getParentDirectory().getFullPathName() << "\""
              << " (== itself: "
              << (degenerate.getParentDirectory() == degenerate ? "true" : "false")
              << ")" << std::endl;

    // ...so this recurses forever: "C:" is shorter than "C:foo" and compares
    // unequal, so isAChildOf() recurses with getParentDirectory() == *this
    std::cout << "Calling isAChildOf() - stack overflow follows..." << std::endl;

    auto result = degenerate.isAChildOf (juce::File ("C:\\"));

    std::cout << "Never reached: " << (result ? "true" : "false") << std::endl;
    return 0;
}
