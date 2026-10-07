#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioPluginAudioProcessor::AudioPluginAudioProcessor() 
    : AudioProcessor (ProcessedAudio, 1, 0) {}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor() {}

void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {}

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    float* channelData = buffer.getReadPointer(0);
    int bufferSize = buffer.getNumSamples();
    float sum = 0;
    for (int i = 0; i < bufferSize; ++i) sum += channelData[i];
    float mean = sum / bufferSize;

    float maxCorr = -1.0f;
    int bestLag = -1;
    for (int lag = 20; lag < bufferSize / 2; ++lag) {
        float corr = 0;
        for (int i = 0; i < bufferSize - lag; ++i) {
            corr += (channelData[i] - mean) * (channelData[i + lag] - mean);
        }
        if (corr > maxCorr) {
            maxCorr = corr;
            bestLag = lag;
        }
    }

    if (bestLag != -1) {
        float frequency = getSampleRate() / bestLag;
        int midiNote = std::round(12.0f * std::log2(frequency / 440.0f) + 69.0f);
        if (midiNote >= 0 && midiNote <= 127) {
            if (midiNote != lastMidiNote) {
                if (lastMidiNote != -1) midiMessages.addEvent(juce::MidiMessage::noteOff(lastMidiNote), 0);
                midiMessages.addEvent(juce::MidiMessage::noteOn(midiNote, 0.8f), 0);
                lastMidiNote = midiNote;
            }
        }
    } else if (lastMidiNote != -1) {
        midiMessages.addEvent(juce::MidiMessage::noteOff(lastMidiNote), 0);
        lastMidiNote = -1;
    }
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor() { return new AudioPluginAudioProcessorEditor(*this); }
