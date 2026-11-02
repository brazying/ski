#include "PluginProcessor.h"
#include "PluginEditor.h"

SkiAudioProcessor::SkiAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      parameters(*this, nullptr, "SKI_STATE", createParameterLayout())
{
}

juce::AudioProcessorValueTreeState::ParameterLayout
SkiAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { "inputGain", 1 },
        "Input",
        juce::NormalisableRange<float>(-24.0f, 24.0f, 0.01f),
        0.0f,
        "dB"
    ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID { "outputGain", 1 },
        "Output",
        juce::NormalisableRange<float>(-24.0f, 24.0f, 0.01f),
        0.0f,
        "dB"
    ));

    return layout;
}

void SkiAudioProcessor::prepareToPlay(double, int)
{
}

void SkiAudioProcessor::releaseResources()
{
}

void SkiAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    const auto inputDb = parameters.getRawParameterValue("inputGain")->load();
    const auto outputDb = parameters.getRawParameterValue("outputGain")->load();

    const auto gain = juce::Decibels::decibelsToGain(inputDb + outputDb);
    buffer.applyGain(gain);
}

juce::AudioProcessorEditor* SkiAudioProcessor::createEditor()
{
    return new SkiAudioProcessorEditor(*this);
}

bool SkiAudioProcessor::hasEditor() const
{
    return true;
}

const juce::String SkiAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SkiAudioProcessor::acceptsMidi() const
{
    return false;
}

bool SkiAudioProcessor::producesMidi() const
{
    return false;
}

bool SkiAudioProcessor::isMidiEffect() const
{
    return false;
}

double SkiAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SkiAudioProcessor::getNumPrograms()
{
    return 1;
}

int SkiAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SkiAudioProcessor::setCurrentProgram(int)
{
}

const juce::String SkiAudioProcessor::getProgramName(int)
{
    return {};
}

void SkiAudioProcessor::changeProgramName(int, const juce::String&)
{
}

void SkiAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    const auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());

    if (xml != nullptr)
        copyXmlToBinary(*xml, destData);
}

void SkiAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));

    if (xml != nullptr && xml->hasTagName(parameters.state.getType()))
        parameters.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SkiAudioProcessor();
}
