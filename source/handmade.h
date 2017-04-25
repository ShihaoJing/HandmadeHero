//
// Created by Shihao Jing on 4/18/17.
//
#ifndef HANDMADE_H
#define HANDMADE_H

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

internal void GameUpdateAndRender(game_offscreen_buffer *Buffer,
                                  game_sound_output_buffer *SoundBuffer);


#endif //HANDMADE_H
