# ski

**ski** is a Windows x64 VST3 audio effect built with C++17, JUCE, and CMake.

Its focus is hybrid granular audio processing, scale-aware harmonization, modulation, and a flexible multi-effects chain. It is an audio effect, not a standalone synthesizer.

## Product direction

- **Granular engine:** live input, rolling audio buffer, recording, freeze, grain position, size, density, jitter, spray, overlap, and reverse.
- **Pitch engine:** pitch shifting and pitch analysis for monophonic material.
- **Harmonizer:** user-selected key and scale; harmony voices are mapped to scale degrees rather than fixed semitone offsets.
- **Modulation:** LFOs, random modulation, and envelope following.
- **Effects:** modular effects chain with reorderable processing stages.
- **Workflow:** develop incrementally and test each audio milestone in FL Studio.

## Technology

- C++17
- JUCE
- CMake
- Windows x64
- VST3

## Development principles

- Keep audio processing real-time safe: no blocking locks, heap allocations, or file I/O in the audio callback.
- Prepare buffers and DSP state outside the processing callback.
- Keep DSP modules independent from the editor/UI.
- Expose parameters through JUCE's parameter system for host automation and state recall.
- Build and test each milestone before expanding the feature set.

## Milestones

1. Project scaffold and VST3 build.
2. Audio input/output, rolling buffer, recording, and freeze.
3. First granular engine.
4. Pitch engine and scale-aware harmonizer.
5. Modulation and effects chain.
6. UI, presets, optimization, and host validation.

## Status

Early development. The first milestone is establishing a clean, buildable JUCE/CMake VST3 project.
