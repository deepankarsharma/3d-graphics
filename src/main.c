#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

// This is our game window
SDL_Window* window = NULL;

// This is our game renderer
SDL_Renderer* renderer = NULL;

// Boolean variable that controls whether our program is running.
// We initialize it to false here because initially our program is not running.
bool is_running = false;


uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;

const int WINDOW_WIDTH=800;
const int WINDOW_HEIGHT=800;

// We call this function at the start of main.
// This function is responsible for creating the window for our game.
int initialize_window(void) {

  // SDL is the library that we are using for
  // 1. creating windows
  // 2. accepting user input
  // 3. drawing items in the window


  // We are initializing the SDL library here.
  // SDL_Init is an example of how C functions usually do error handling.
  // When the function is able to do its tasks without any errors, it will return 0.
  // When the function runs into some error, it will return some non-zero value.
  // Sometimes users can use the non zero values to understand exactly what went wrong.
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr," Error initializing SDL .\n");
    return -1;
  }

  // Create a SDL window
  window = SDL_CreateWindow(
                            NULL,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            WINDOW_WIDTH,
                            WINDOW_HEIGHT,
                            SDL_WINDOW_BORDERLESS);

  if (!window) {
    fprintf(stderr, "Error creating SDL window. \n");
    return -2;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    fprintf(stderr, "Error creating SDL renderer. \n");
    return -3;
  }
  
  return 0;
}


void setup(void) {
  color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);
}

void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);
  
  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN: 
    if (event.key.keysym.sym == SDLK_ESCAPE) {
      is_running = false;
    }
    break;
  }
}

void update(void) {

}

void destroy_window(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void render(void) {
  // Set the color that the renderer will use for drawing.
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  // Actually draw using the currently active color.
  SDL_RenderClear(renderer);

  // Now copy the drawing from renderer into the window.
  SDL_RenderPresent(renderer);
}

// When a C program starts, the first function
// to execute is always called main
int main(void) {

  // We are now in main because the user ran renderer
  // hence we are running. so lets update the is_running
  // variable and set it to the value returned by initialize_window.
  is_running = (initialize_window() == 0);

  if (!is_running) {
    fprintf(stderr, "We were unable to initialize the window. Exiting");
    return -1;
  }
  
  setup();

  while (is_running) {
    // Our game loop will look like this, no matter how simple or complex the game

    // First step: Accept user input
    process_input();

    // Second step: Update the variables based on user input
    update();

    // Third step: Now make a new drawing so that we can see updates
    render();
  }

  destroy_window();
  
  return 0;
}
