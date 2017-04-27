//
// Created by Shihao Jing on 4/18/17.
//
#ifndef HANDMADE_H
#define HANDMADE_H

/*
 * HAND_MADE_INTERNAL:
 * 0 - Build for public release
 * 1 - Build for developer only
 *
 * HAND_MADE_SLOW:
 * 0 -
 */


#if HANDMADE_SLOW
#define Assert(Expression) if (!(Expression)) {*(int*)0 = 0;}
#else
#define Assert(Expression)
#endif

#define Kilobytes(Value) ((Value)*1024LL)
#define Megabytes(Value) (Kilobytes(Value)*1024LL)
#define Gigabytes(Value) (Megabytes(Value)*1024LL)
#define Terabytes(Value) (Gigabytes(Value)*1024LL)

/*
 * NOTE: Services that the platform layer provides to the game.
 */

#if HANDMADE_INTERNAL
struct debug_read_file_result
{
  uint32 ContentsSize;
  void *Contents;
};

internal debug_read_file_result DEBUGPlatformReadEntireFile(char *Filename);
internal bool32 DEBUGPlatformWriteEntireFile(char *Filename, uint32 MemorySize, void *Memory);
internal void DEBUGPlatformFreeFileMemory(void *Memory);
#endif

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
  uint64 TransientStorageSize;
  void *TransientStorage;
  bool32 IsInitialized;
};

struct game_asset
{

};

internal void GameUpdateAndRender(game_memory *Memory, game_input *Input,
                                  game_offscreen_buffer *Buffer,
                                  game_sound_output_buffer *SoundBuffer);


#endif //HANDMADE_H
