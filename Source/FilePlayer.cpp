
#include "FilePlayer.hpp"

FilePlayer::FilePlayer() : thread ("FilePlayThread")
{
    thread.startThread();
}

FilePlayer::~FilePlayer()
{
    audioTransportSource.setSource (nullptr);   //unload the current file
    thread.stopThread (100);
}

void FilePlayer::setPlaying (bool newState)
{
    if(newState == true)
    {
        audioTransportSource.setPosition (0.0);
        audioTransportSource.start();
    }
    else
    {
        audioTransportSource.stop();
    }
}

bool FilePlayer::isPlaying () const
{
    return audioTransportSource.isPlaying();
}

void FilePlayer::loadFile(const File& newFile)
{
    // unload the previous file source and delete it..
    setPlaying (false);
    audioTransportSource.setSource (nullptr);
    
    // create a new file source from the file..
    // get a format manager and set it up with the basic types (wav, ogg and aiff).
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    
    if (auto reader = formatManager.createReaderFor (newFile))
    {
        //currentFile = audioFile;
        currentAudioFileSource = std::make_unique<AudioFormatReaderSource> (reader, true);
        
        // ..and plug it into our transport source
        audioTransportSource.setSource (currentAudioFileSource.get(),
                                   32768, // tells it to buffer this many samples ahead
                                   &thread,
                                   reader->sampleRate);
    }
}

//AudioSource
void FilePlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    audioTransportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void FilePlayer::releaseResources()
{
    audioTransportSource.releaseResources();
}

void FilePlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    audioTransportSource.getNextAudioBlock (bufferToFill);
}
