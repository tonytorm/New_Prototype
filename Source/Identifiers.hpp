
#pragma once
/** helpers to ID various parameters*/
namespace IDs {

    #define DECLARE_ID(name) const String name (#name);

    DECLARE_ID(inputVolume)            // Input volume of the effects chain
    DECLARE_ID(outputVolume)        // Output volume of the effects chain
    DECLARE_ID(wetDry)                // Wet / dry control of the plugin

    #undef DECLARE_ID

}
