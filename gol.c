#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 900
#define HEIGHT 600
#define CELL_WIDTH 30
#define COLUMNS WIDTH / CELL_WIDTH
#define ROWS HEIGHT / CELL_WIDTH
#define LINE_WIDTH 2

Uint32 COLOR_WHITE = 0xFFFFFF;
Uint32 COLOR_GRAY = 0x2F2F2F2F;

int draw_cell(SDL_Surface* surface, int cell_x, int cell_y)
{
  int pixel_x = cell_x * CELL_WIDTH;
  int pixel_y = cell_y * CELL_WIDTH;

  SDL_Rect cell = (SDL_Rect){pixel_x, pixel_y, CELL_WIDTH, CELL_WIDTH};
  SDL_FillRect(surface, &cell, COLOR_WHITE);
}

int draw_grid(SDL_Surface* surface)
{
  for(int i=0; i<ROWS; i++)
  {
    SDL_Rect row = (SDL_Rect){0, (i+1) * CELL_WIDTH, WIDTH, LINE_WIDTH};
    SDL_FillRect(surface, &row, COLOR_GRAY);
  }

  for(int i=0; i<COLUMNS; i++)
  {
    SDL_Rect column = (SDL_Rect){(i+1) * CELL_WIDTH, 0, LINE_WIDTH, HEIGHT};
    SDL_FillRect(surface, &column, COLOR_GRAY);
  }
} 

int main()
{
  SDL_Init(SDL_INIT_VIDEO);

  char* window_title = "Conway's Game of Life";

  int columns = WIDTH / CELL_WIDTH;
  int rows = HEIGHT / CELL_WIDTH;

  SDL_Window* window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Surface* surface = SDL_GetWindowSurface(window);
  SDL_Rect rect = (SDL_Rect){WIDTH/2, HEIGHT/2, 20, 20};

  int cell_x = 10;
  int cell_y = 5;

  draw_cell(surface, cell_x, cell_y);
  draw_grid(surface);


  SDL_UpdateWindowSurface(window);

  int app_running = 1;
  while(app_running)
  {
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        app_running = 0;
      }
    }
  }

}
