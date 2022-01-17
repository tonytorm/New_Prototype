/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   squueze_svg;
    const int            squueze_svgSize = 758;

    extern const char*   cog_2_svg;
    const int            cog_2_svgSize = 1409;

    extern const char*   squeezer_2_svg;
    const int            squeezer_2_svgSize = 1171;

    extern const char*   cog_1_svg;
    const int            cog_1_svgSize = 784;

    extern const char*   squeezer_svg;
    const int            squeezer_svgSize = 1172;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 5;

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
