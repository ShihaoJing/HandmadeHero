//
// Created by Shihao Jing on 4/18/17.
//
#ifndef HANDMADE_H
#define HANDMADE_H

#define Kilobytes(Value) ((Value)*1024)
#define Megabytes(Value) (Kilobytes(Value)*1024)
#define Gigabytes(Value) (Megabytes(Value)*1024)

/*
 * NOTE: Services that the platform layer provides to the game.
 */

/*
 * NOTE: Services that the game provides to the platform layer.
 */

// FOUR THINGS - timing, controller/keyboard,
// input, bitmap buffer, sound buffer
struct game_offscreen_buffer
{
  // NOTE: Pixels are alwasy 32-bits wide, Memory Order BB GG RR XX
  void *Memory;
  int Width;
  int Height;
  int Pitch;
};

struct game_sound_output_buffer
{
  int16 *Samples;
  int SampleCount;
  int SamplesPerSecond;

};

struct game_button_state
{
  int HalfTransitionCount;
  bool32 EndedDown;
};

struct game_controller_input
{
  bool32 IsAnalog;

  real32 StartX;
  real32 StartY;

  real32 MinX;
  real32 MinY;

  real32 MaxX;
  real32 MaxY;

  real32 EndX;
  real32 EndY;

  union
  {
    game_button_state Button[6];
    struct {
      game_button_state Up;
      game_button_state Down;
      game_button_state Left;
      game_button_state Right;
      game_button_state LeftShoulder;
      game_button_state RightShoulder;
    };
  };
};

struct game_input
{
  game_controller_input Controllers[4];
};

struct game_state
{
  int GreenOffset;
  int BlueOffset;
  int ToneHz;
};

struct game_memory
{
  uint64 PermanenStorageSize;
  void *PermanentStorage; //NOTE: Required to be clear to 0 when allocated
  bool32 IsInitialized;
};

struct game_asset
{

};

internal void GameUpdateAndRender(game_memory *Memory, game_input *Input,
                                  game_offscreen_buffer *Buffer,
                                  game_sound_output_buffer *SoundBuffer);


#endif //HANDMADE_H
