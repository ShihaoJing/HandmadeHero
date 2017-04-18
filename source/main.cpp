#include <iostream>
#include <SDL.h>
#include <sys/mman.h>

#define internal static
#define global_variable static

struct sdl_offscreen_buffer
{
  // NOTE(casey): Pixels are alwasy 32-bits wide, Memory Order BB GG RR XX
  SDL_Texture *Texture;
  void *Memory;
  int Width;
  int Height;
  int Pitch;
};

struct sdl_Window_dimension
{
  int Width;
  int Height;
};

global_variable sdl_offscreen_buffer GlobalBackBuffer;

#define MAX_CONTROLLERS 4
SDL_GameController* ControllerHandles[MAX_CONTROLLERS];
SDL_Haptic* RumbleHandles[MAX_CONTROLLERS];

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

internal void
RenderWeirdGradient(sdl_offscreen_buffer Buffer,
                    int BlueOffset,
                    int GreenOffset)
{
  int Width = Buffer.Width;
  int Height = Buffer.Height;

  uint8* Row = (uint8*)Buffer.Memory;
  for(int Y = 0; Y < Height; ++Y)
  {
    uint32* Pixel = (uint32 *)Row;
    for(int X = 0; X < Width; ++X)
    {
      uint8 Blue = (X + BlueOffset);
      uint8 Green = (Y + GreenOffset);

      *Pixel++ = ((Green << 8) | Blue);
    }

    Row += Buffer.Pitch;
  }
}

internal void
SDLResizeTexture(sdl_offscreen_buffer* Buffer,
                 SDL_Renderer *Renderer,
                 int Width,
                 int Height)
{
  const int BytesPerPixel = 4;
  if (Buffer->Memory)
  {
    munmap(Buffer->Memory,
           Buffer->Width * Buffer->Height * BytesPerPixel);
  }
  if (Buffer->Texture)
  {
    SDL_DestroyTexture(Buffer->Texture);
  }
  Buffer->Texture = SDL_CreateTexture(Renderer,
                                      SDL_PIXELFORMAT_ARGB8888,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      Width,
                                      Height);
  Buffer->Width = Width;
  Buffer->Height = Height;
  Buffer->Pitch = Width * BytesPerPixel;
  Buffer->Memory = mmap(0,
                        Buffer->Width * Buffer->Height * BytesPerPixel,
                        PROT_READ | PROT_WRITE,
                        MAP_ANONYMOUS | MAP_PRIVATE,
                        -1,
                        0);

}

sdl_Window_dimension
SDLGetWindowDimension(SDL_Window* Window)
{
  sdl_Window_dimension Result;
  SDL_GetWindowSize(Window, &Result.Width, &Result.Height);

  return Result;
}

internal void
SDLUpdateWindow(SDL_Window* Window, SDL_Renderer* Renderer, sdl_offscreen_buffer* Buffer)
{
  SDL_UpdateTexture(Buffer->Texture,
                    0,
                    Buffer->Memory,
                    Buffer->Pitch);
  SDL_RenderCopy(Renderer, Buffer->Texture, 0, 0);
  SDL_RenderPresent(Renderer);
}

internal void
SDLOpenGameControllers()
{
  int MaxJoySticks = SDL_NumJoysticks();
  int ControllerIndex = 0;
  for (int JoystickIndex = 0; JoystickIndex < MaxJoySticks; ++JoystickIndex)
  {
    if (!SDL_IsGameController(JoystickIndex))
      continue;
    if (ControllerIndex >= MAX_CONTROLLERS)
      continue;
    ControllerHandles[ControllerIndex] = SDL_GameControllerOpen(JoystickIndex);
    RumbleHandles[ControllerIndex] = SDL_HapticOpen(JoystickIndex);
    if (RumbleHandles[ControllerIndex]
        && SDL_HapticRumbleInit(RumbleHandles[ControllerIndex]) != 0)
    {
      SDL_HapticClose(RumbleHandles[ControllerIndex]);
      RumbleHandles[ControllerIndex] = 0;
    }

    ControllerIndex++;
  }
}

internal void
SDLCloseGameControllers()
{
  for (int ControllerIndex = 0; ControllerIndex < MAX_CONTROLLERS; ++ControllerIndex)
  {
    if (ControllerHandles[ControllerIndex])
      SDL_GameControllerClose(ControllerHandles[ControllerIndex]);

    if (RumbleHandles[ControllerIndex])
      SDL_HapticClose(RumbleHandles[ControllerIndex]);
  }
}


bool HandleEvent(SDL_Event* Event)
{
  bool ShouldQuit = false;
  switch (Event->type)
  {
    case SDL_QUIT:
    {
      printf("SDL_QUIT\n");
      ShouldQuit = true;
    } break;

    case SDL_KEYDOWN:

    case SDL_KEYUP:
    {
      SDL_Keycode KeyCode = Event->key.keysym.sym;
      bool IsDown = (Event->key.state == SDL_PRESSED);
      bool WasDown = false;
      if (Event->key.state == SDL_RELEASED)
      {
        WasDown = true;
      }
      else if (Event->key.repeat != 0)
      {
        WasDown = true;
      }

      // NOTE: In the windows version, we used "if (IsDown != WasDown)"
      // to detect key repeats. SDL has the 'repeat' value, though,
      // which we'll use.
      if (Event->key.repeat == 0)
      {
        if(KeyCode == SDLK_w)
        {
        }
        else if(KeyCode == SDLK_a)
        {
        }
        else if(KeyCode == SDLK_s)
        {
        }
        else if(KeyCode == SDLK_d)
        {
        }
        else if(KeyCode == SDLK_q)
        {
        }
        else if(KeyCode == SDLK_e)
        {
        }
        else if(KeyCode == SDLK_UP)
        {
        }
        else if(KeyCode == SDLK_LEFT)
        {
        }
        else if(KeyCode == SDLK_DOWN)
        {
        }
        else if(KeyCode == SDLK_RIGHT)
        {
        }
        else if(KeyCode == SDLK_ESCAPE)
        {
          printf("ESCAPE: ");
          if(IsDown)
          {
            printf("IsDown ");
          }
          if(WasDown)
          {
            printf("WasDown");
          }
          printf("\n");
        }
        else if(KeyCode == SDLK_SPACE)
        {
        }
      }
    }

    case SDL_WINDOWEVENT:
    {
      switch (Event->window.event)
      {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
        {
          printf("SDL_WINDOWEVENT_SIZE_CHANGED (%d, %d)\n",
                 Event->window.data1,
                 Event->window.data2);
        } break;

        case SDL_WINDOWEVENT_FOCUS_GAINED:
        {
          printf("SDL_WINDOWEVENT_FOCUS_GAINED\n");
        } break;

        case SDL_WINDOWEVENT_EXPOSED:
        {
          SDL_Window* Window = SDL_GetWindowFromID(Event->window.windowID);
          SDL_Renderer* Renderer = SDL_GetRenderer(Window);
          SDLUpdateWindow(Window, Renderer, &GlobalBackBuffer);
        } break;
      }
    } break;

  }
  return ShouldQuit;
}

int main()
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);
  // Initialise Game Controllers.
  SDLOpenGameControllers();
  // Create Window.
  SDL_Window* Window;
  Window = SDL_CreateWindow("Handmade Hero",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            640,
                            480,
                            SDL_WINDOW_RESIZABLE);
  if (Window)
  {
    // Create a "Renderer" for our Window
    SDL_Renderer* Renderer = SDL_CreateRenderer(Window,
                                                -1,
                                                0);
    if (Renderer)
    {
      bool Running = true;
      sdl_Window_dimension Dimension = SDLGetWindowDimension(Window);
      SDLResizeTexture(&GlobalBackBuffer,
                       Renderer,
                       Dimension.Width, Dimension.Height);
      int XOffset = 0;
      int YOffset = 0;
      while (Running)
      {
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
          if (HandleEvent(&Event))
          {
            Running = false;
          }
        }

        // Poll our controllers for input.
        for (int ControllerIndex = 0;
             ControllerIndex < MAX_CONTROLLERS;
             ++ControllerIndex)
        {
          if(ControllerHandles[ControllerIndex] != 0
              && SDL_GameControllerGetAttached(ControllerHandles[ControllerIndex]))
          {
            // NOTE: We have a controller with index ControllerIndex.
            bool Up = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex],
                                                  SDL_CONTROLLER_BUTTON_DPAD_UP);
            bool Down = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex],
                                                    SDL_CONTROLLER_BUTTON_DPAD_DOWN);
            bool Left = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex],
                                                    SDL_CONTROLLER_BUTTON_DPAD_LEFT);
            bool Right = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex],
                                                     SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
            bool Start = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex],
                                                     SDL_CONTROLLER_BUTTON_START);
            bool Back = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex],
                                                    SDL_CONTROLLER_BUTTON_BACK);
            bool LeftShoulder = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex],
                                                            SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
            bool RightShoulder = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex],
                                                             SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
            bool AButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex],
                                                       SDL_CONTROLLER_BUTTON_A);
            bool BButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex],
                                                       SDL_CONTROLLER_BUTTON_B);
            bool XButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex],
                                                       SDL_CONTROLLER_BUTTON_X);
            bool YButton = SDL_GameControllerGetButton(ControllerHandles[ControllerIndex],
                                                       SDL_CONTROLLER_BUTTON_Y);

            int16 StickX = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex],
                                                     SDL_CONTROLLER_AXIS_LEFTX);
            int16 StickY = SDL_GameControllerGetAxis(ControllerHandles[ControllerIndex],
                                                     SDL_CONTROLLER_AXIS_LEFTY);

            if (AButton)
            {
              YOffset += 2;
            }
            if (BButton)
            {
              if (RumbleHandles[ControllerIndex])
              {
                SDL_HapticRumblePlay(RumbleHandles[ControllerIndex], 0.5f, 2000);
              }
            }

          }
          else
          {
            // TODO: This controller is not plugged in.
          }
        } // end of controller polling

        RenderWeirdGradient(GlobalBackBuffer, XOffset, YOffset);
        SDLUpdateWindow(Window, Renderer, &GlobalBackBuffer);

        ++XOffset;
      }
    }
    else
    {
      //TODO: Log
    }
  }
  else
  {
    //TODO: Log
  }

  SDL_Quit();
  return 0;
}