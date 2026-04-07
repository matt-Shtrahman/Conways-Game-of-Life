#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

#define WIDTH 900
#define HEIGHT 600
#define CELL_WIDTH 10
#define COLUMNS WIDTH / CELL_WIDTH
#define ROWS HEIGHT / CELL_WIDTH
#define LINE_WIDTH 2

Uint32 COLOR_WHITE = 0xFFFFFF;
Uint32 COLOR_GRAY = 0x2F2F2F2F;
Uint32 COLOR_BLACK = 0x00000000;

void draw_cell(SDL_Surface* surface, int cell_x, int cell_y, int cell_value)
{
  int pixel_x = cell_x * CELL_WIDTH;
  int pixel_y = cell_y * CELL_WIDTH;
  Uint32 color = cell_value == 0 ? COLOR_BLACK : COLOR_WHITE;

  SDL_Rect cell = (SDL_Rect){pixel_x, pixel_y, CELL_WIDTH, CELL_WIDTH};
  SDL_FillRect(surface, &cell, color);
}

void draw_grid(SDL_Surface* surface)
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

void draw_game_matrix(SDL_Surface* surface, int rows, int columns, int game_matrix[][columns])
{
  for (int i=0; i<rows; i++)
  {
    for (int j=0; j<columns; j++)
    {
      int cell_value = game_matrix[i][j];
      draw_cell(surface, j, i, cell_value);
    }
  }
}

void initialize_game_matrix(int rows, int columns, int game_matrix[][columns])
{
  for (int i=0; i<rows; i++)
  {
    for (int j=0; j<columns; j++)
    {
      game_matrix[i][j] = rand() % 2;
    }
  }
}

int count_neighbors(int i, int j, int rows, int columns, int game_matrix[][columns])
{
  int neighbor_counter = 0;

  //left neighbor
  if (j > 0)
  {
    neighbor_counter += game_matrix[i][j-1];
  }

  //right neighbor
  if (j < (columns - 1))
  {
    neighbor_counter += game_matrix[i][j+1];
  }
  
  //above neighbor
  if (i > 0)
  {
    neighbor_counter += game_matrix[i-1][j];
  }

  //below neighbor
  if (i < (rows - 1))
  {
    neighbor_counter += game_matrix[i+1][j];
  }
  
  //above left neighbor
  if (i > 0 && j > 0)
  {
    neighbor_counter += game_matrix[i-1][j-1];
  }

  //above right neighbor
  if (i > 0 && j < (columns - 1))
  {
    neighbor_counter += game_matrix[i-1][j+1];
  }
  
  //below left neighbor
  if (i < (rows - 1) && j > 0)
  {
    neighbor_counter += game_matrix[i+1][j-1];
  }

  //below right neighbor
  if (i < (rows - 1) && j < (columns - 1))
  {
    neighbor_counter += game_matrix[i+1][j+1];
  }

  return neighbor_counter;
}

void simulation_step(int rows, int columns, int game_matrix[][columns])
{

  int neighbor_count[rows][columns];

  for (int i=0; i<rows; i++)
  {
    for (int j=0; j<columns; j++)
    {
      neighbor_count[i][j] = count_neighbors(i,j, rows, columns, game_matrix);
    }
  }

  for (int i=0; i<rows; i++)
  {
    for (int j=0; j<columns; j++)
    {
      if (neighbor_count[i][j] < 2)
      {
        game_matrix[i][j] = 0;
      }

      if ((neighbor_count[i][j] > 3) && (game_matrix[i][j] != 0))
      {
        game_matrix[i][j] = 0;
      }

      if ((neighbor_count[i][j] == 3) && (game_matrix[i][j] == 0))
      {
        game_matrix[i][j] = 1;
      }

    }
  }

}

void main()
{
  SDL_Init(SDL_INIT_VIDEO);

  char* window_title = "Conway's Game of Life";

  int columns = WIDTH / CELL_WIDTH;
  int rows = HEIGHT / CELL_WIDTH;

  SDL_Window* window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  SDL_Surface* surface = SDL_GetWindowSurface(window);
  SDL_Rect rect = (SDL_Rect){WIDTH/2, HEIGHT/2, 20, 20};

  int game_matrix[rows][columns];
  int cell_x = 10;
  int cell_y = 5;

  initialize_game_matrix(rows, columns, game_matrix);
  
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
    
  simulation_step(rows, columns, game_matrix);
  draw_game_matrix(surface, rows, columns, game_matrix);
  draw_grid(surface);
  SDL_UpdateWindowSurface(window);
  SDL_Delay(500);
  }

}
