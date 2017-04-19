//
// Created by Shihao Jing on 4/18/17.
//
#include <math.h>
#include <iostream>

#ifndef HANDMADE_H
#define HANDMADE_H

#define Pi32 3.14159265358979f

#define internal static
#define global_variable static
#define local_persist static

typedef float real32;
typedef double real64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

struct game_offscreen_buffer
{
  void* Memory;
  int Width;
  int Height;
  int Pitch;
};

struct game_sound_output_buffer
{
  int SamplesPerSecond;
  int SampleCount;
  int16 *Samples;
};

internal void
GameUpdateAndRender(game_offscreen_buffer* Buffer, int BlueOffset,
                    int GreenOffset, game_sound_output_buffer* SoundBuffer,
                    int ToneHz);

#endif //HANDMADE_H
