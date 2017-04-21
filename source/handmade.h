//
// Created by Shihao Jing on 4/18/17.
//
#include <math.h>
#include <stdint.h>

#ifndef HANDMADE_H
#define HANDMADE_H

/*
 +  NOTE(casey):
 +
 +  HANDMADE_INTERNAL:
 +    0 - Build for public release
 +    1 - Build for developer only
 +
 +  HANDMADE_SLOW:
 +    0 - Not slow code allowed!
 +    1 - Slow code welcome.
 +*/

#if HANDMADE_SLOW

#define Assert(Expression) if(!(Expression)) {*(int *)0 = 0;}
#else
#define Assert(Expression)
#endif

#define Kilobytes(Value) ((Value)*1024LL)
#define Megabytes(Value) (Kilobytes(Value)*1024LL)
#define Gigabytes(Value) (Megabytes(Value)*1024LL)
#define Terabytes(Value) (Gigabytes(Value)*1024LL)

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

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
typedef int32 bool32;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;


inline uint32
SafeTruncateUInt64(uint64 Value)
{
  // TODO(casey): Defines for maximum values
  Assert(Value <= 0xFFFFFFFF);
  uint32 Result = (uint32)Value;
  return Result;
}

/*
 -  TODO(casey): Services that the platform layer provides to the game
 +  NOTE(casey): Services that the platform layer provides to the game
 +*/
#if HANDMADE_INTERNAL
/* IMPORTANT(casey):
 +
 +   These are NOT for doing anything in the shipping game - they are
 +   blocking and the write doesn't protect against lost data!
  */
struct debug_read_file_result
{
  uint32 ContentsSize;
  void* Contents;
};
internal debug_read_file_result DEBUGPlatformReadEntireFile(char *Filename);
internal void DEBUGPlatformFreeFileMemory(void *Memory);
internal bool32 DEBUGPlatformWriteEntireFile(char *Filename, uint32 MemorySize, void *Memory);
#endif

struct game_memory
{
  bool32 IsInitialized;

  uint64 PermanentStorageSize;
  void *PermanentStorage;
  uint64 TransientStorageSize;
  void *TransientStorage;
};

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

struct game_state
{
  int BlueOffset;
  int GreenOffset;
  int ToneHz;
};

struct game_button_state
{
  int HalfTransitionCount;
  bool32 EndedDown;
};

struct game_controller_input
{
  bool32 IsConnected;
  bool32 IsAnalog;
  real32 StickAverageX;
  real32 StickAverageY;

  union
  {
    game_button_state Buttons[12];
    struct
    {
      game_button_state MoveUp;
      game_button_state MoveDown;
      game_button_state MoveLeft;
      game_button_state MoveRight;

      game_button_state ActionUp;
      game_button_state ActionDown;
      game_button_state ActionLeft;
      game_button_state ActionRight;

      game_button_state LeftShoulder;
      game_button_state RightShoulder;

      game_button_state Back;
      game_button_state Start;

      // NOTE(casey): All buttons must be added above this line

      game_button_state Terminator;
    };
  };
};

struct game_input
{
  game_controller_input Controllers[5];
};

inline game_controller_input* GetController(game_input *Input, int unsigned ControllerIndex)
{
  Assert(ControllerIndex < ArrayCount(Input->Controllers));

  game_controller_input *Result = &Input->Controllers[ControllerIndex];
  return(Result);
}


internal void
GameUpdateAndRender(game_memory *Memory, game_input *Input,
                    game_offscreen_buffer *Buffer,
                    game_sound_output_buffer *SoundBuffer);

#endif //HANDMADE_H
