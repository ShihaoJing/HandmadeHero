//
// Created by Shihao Jing on 4/19/17.
//
#include "handmade.h"

#ifndef SDL_HANDMADE_H
#define SDL_HANDMADE_H

struct sdl_offscreen_buffer
{
  // NOTE(casey): Pixels are alwasy 32-bits wide, Memory Order BB GG RR XX
  SDL_Texture *Texture;
  void *Memory;
  int Width;
  int Height;
  int Pitch;
  int BytesPerPixel;
};

struct sdl_audio_ring_buffer
{
  int Size;
  int WriteCursor;
  int PlayCursor;
  void *Data;
};

struct sdl_Window_dimension
{
  int Width;
  int Height;
};

struct sdl_sound_output
{
  int SamplesPerSecond;
  int ToneHz;
  int16 ToneVolume;
  uint32 RunningSampleIndex;
  int WavePeriod;
  int BytesPerSample;
  int SecondaryBufferSize;
  real32 tSine;
  int LatencySampleCount;
};

struct sdl_debug_time_marker
{
  int PlayCursor;
  int WriteCursor;
};

#endif