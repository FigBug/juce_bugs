/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   OpenSansRegular_ttf;
    const int            OpenSansRegular_ttfSize = 217360;

    extern const char*   RobotoLight_ttf;
    const int            RobotoLight_ttfSize = 140276;

    extern const char*   RobotoMonoRegular_ttf;
    const int            RobotoMonoRegular_ttfSize = 114624;

    extern const char*   TitilliumWebRegular_ttf;
    const int            TitilliumWebRegular_ttfSize = 63728;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 4;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
