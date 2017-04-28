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

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

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

inline game_controller_input* GetController(game_input *Input, int unsigned ControllerIndex)
{
  Assert(ControllerIndex < ArrayCount(Input->Controllers));

  game_controller_input *Result = &Input->Controllers[ControllerIndex];
  return Result;
}

internal void GameUpdateAndRender(game_memory *Memory, game_input *Input,
                                  game_offscreen_buffer *Buffer,
                                  game_sound_output_buffer *SoundBuffer);


#endif //HANDMADE_H
