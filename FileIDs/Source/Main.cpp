/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
int main (int argc, char* argv[])
{
    ignoreUnused (argc, argv);

    Array<File> roots;
    File::findFileSystemRoots (roots);
    File f = roots[0];

    File::getSpecialLocation (File::userHomeDirectory).setAsCurrentWorkingDirectory();
    int64 n1 = f.getFileIdentifier();

    File::getSpecialLocation (File::userApplicationDataDirectory).setAsCurrentWorkingDirectory();
    int64 n2 = f.getFileIdentifier();

    jassert (n1 == n2);

    return 0;
}
