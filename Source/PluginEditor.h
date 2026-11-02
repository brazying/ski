#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SkiAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit SkiAudioProcessorEditor(SkiAudioProcessor&);
    ~SkiAudioProcessorEditor() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    SkiAudioProcessor& audioProcessor;

    juce::Slider inputGainSlider;
    juce::Slider outputGainSlider;
    juce::Label inputGainLabel;
    juce::Label outputGainLabel;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> inputGainAttachment;
    std::unique_ptr<SliderAttachment> outputGainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SkiAudioProcessorEditor)
};
