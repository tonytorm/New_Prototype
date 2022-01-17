#pragma once

#include <JuceHeader.h>

/** Simple FilePlayer class - strams audio from a file. */
class FilePlayer :  public AudioSource
{
public:
    /** Constructor */
    FilePlayer();
    
    /** Destructor */
    ~FilePlayer();
    
    /** Starts or stops playback of the looper */
    void setPlaying (bool newState);
    
    /** Gets the current playback state of the looper */
    bool isPlaying() const;
    
    /** Loads the specified file into the transport source */
    void loadFile (const File& newFile);
    
    // AudioSource
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
private:
    std::unique_ptr<AudioFormatReaderSource> currentAudioFileSource;    
    AudioTransportSource audioTransportSource;
    TimeSliceThread thread;    //  thread for the transport source
};
