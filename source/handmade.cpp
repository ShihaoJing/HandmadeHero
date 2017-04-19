//
// Created by Shihao Jing on 4/18/17.
//

#include "handmade.h"

internal void
GameOutputSound(game_sound_output_buffer* SoundBufer, int ToneHz)
{
  local_persist real32 tSine;
  int16 ToneVolume = 3000;
  int WavePeriod = SoundBufer->SamplesPerSecond / ToneHz;

  int16* SampleOut = SoundBufer->Samples;
  for (int SampleIndex = 0;
       SampleIndex < SoundBufer->SampleCount;
       ++SampleIndex)
  {
    real32 SineValue = sinf(tSine);
    int16  SampleValue = (int16)(SineValue * ToneVolume);
    *SampleOut++ = SampleValue;
    *SampleOut++ = SampleValue;

    tSine += 2.0 * Pi32 * 1.0f / (real32)WavePeriod;
  }
}

internal void
RenderWeirdGradient(game_offscreen_buffer *Buffer,
                    int BlueOffset,
                    int GreenOffset)
{
  // TODO(casey): Let's see what the optimizer does

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
      uint8 Blue = (uint8)(X + BlueOffset);
      uint8 Green = (uint8)(Y + GreenOffset);

      *Pixel++ = ((Green << 8) | Blue);
    }

    Row += Buffer->Pitch;
  }
}

internal void
GameUpdateAndRender(game_offscreen_buffer* Buffer, int BlueOffset,
                    int GreenOffset, game_sound_output_buffer* SoundBuffer,
                    int ToneHz)
{
  GameOutputSound(SoundBuffer, ToneHz);
  RenderWeirdGradient(Buffer, BlueOffset, GreenOffset);
}