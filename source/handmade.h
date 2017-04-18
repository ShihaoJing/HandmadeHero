//
// Created by Shihao Jing on 4/18/17.
//

#ifndef HANDMADE_H
#define HANDMADE_H

#define internal static
#define global_variable static

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

internal void
GameUpdateAndRender(game_offscreen_buffer* Buffer,
                    int BlueOffset,
                    int GreenOffset);

#endif //HANDMADE_H
