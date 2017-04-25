//
// Created by Shihao Jing on 4/18/17.
//

#include "handmade.h"

internal void
RenderWeirdGradient(game_offscreen_buffer *Buffer, int BlueOffset, int GreenOffset)
{
  uint8 *Row = (uint8 *)Buffer->Memory;
  for(int Y = 0;
      Y < Buffer->Height;
      ++Y)
  {
    uint32 *Pixel = (uint32 *)Row;
    for(int X = 0;
        X < Buffer->Width;
        ++X)
    {
      uint8 Blue = (X + BlueOffset);
      uint8 Green = (Y + GreenOffset);

      *Pixel++ = ((Green << 8) | Blue);
    }

    Row += Buffer->Pitch;
  }
}

internal void
GameOutputSound(game_sound_output_buffer *SoundBuffer, int ToneHz)
{
  local_persist real32 tSine;
  int16 ToneVolume = 3000;
  int WavePeriod = SoundBuffer->SamplesPerSecond / ToneHz;

  int16_t *SampleOut = SoundBuffer->Samples;
  for(int SampleIndex = 0;
      SampleIndex < SoundBuffer->SampleCount; ++SampleIndex)
  {
    real32 SineValue = sinf(tSine);
    int16 SampleValue = (int16)(SineValue * ToneVolume);
    *SampleOut++ = SampleValue;
    *SampleOut++ = SampleValue;

    tSine += 2.0f * Pi32 * 1.0f / (real32)WavePeriod;
  }
}

internal void
GameUpdateAndRender(game_offscreen_buffer *Buffer, game_sound_output_buffer *SoundBuffer)
{
  int BlueOffset = 0;
  int GreenOffset = 0;
  int ToneHz = 256;
  //TODO: Allow sample offsets here for more robust platform options
  GameOutputSound(SoundBuffer, ToneHz);
  RenderWeirdGradient(Buffer, BlueOffset, GreenOffset);
}