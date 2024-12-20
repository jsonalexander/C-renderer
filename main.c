#include <stdio.h>
#include <math.h>
#include <SDL3/SDL.h>
#include <assert.h>

#include "data_structures.h"
#include "compute.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define LINE_WIDTH 5

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("Cube", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) printf("%s",SDL_GetError());

    // init model

    vector_t axes[3] = {{1,0,0},{0,1,0},{0,0,1}};
    vector_t render_axes[3];

    vector_t model_points[8] = {{-1,-1,-1},{-1,-1,1},{-1,1,-1},{1,-1,-1},{-1,1,1},{1,-1,1},{1,1,-1},{1,1,1}};
    vector_t render_points[8];

    vector_t view_normal = {0,1,0}; // project onto x-z plane (+x is right, +z is up)

    // program loop

    int quit = 0;

    int autorotate = 0;

    float theta_x = 0;
    float theta_y = 0;
    float theta_z = 0;

    const bool * keystate = SDL_GetKeyboardState(NULL);

    while(!quit)
    
    {

        SDL_PumpEvents();

        if (!autorotate)
        {
            if(keystate[SDL_SCANCODE_RIGHT]) theta_z += 0.005;
            if(keystate[SDL_SCANCODE_LEFT]) theta_z -= 0.005;
            if(keystate[SDL_SCANCODE_UP]) theta_x += 0.005;
            if(keystate[SDL_SCANCODE_DOWN]) theta_x -= 0.005;
        }

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE || e.type == SDL_EVENT_QUIT) quit = 1;

            if (e.type == SDL_EVENT_KEY_DOWN)
            {
                if (e.key.key == SDLK_SPACE) autorotate = (autorotate) ? 0 : 1;
            }
        }

        if (autorotate)
        {
            theta_x += 0.001;
            theta_y += 0.001;
            theta_z += 0.001;
        }

        if (theta_x > 6.282) theta_x -= 6.282;
        if (theta_y > 6.282) theta_y -= 6.282;
        if (theta_z > 6.282) theta_z -= 6.282;

        // render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        // change the viewing angle / zoom
        int zoom = 200;

        matrix_t R = matrix_rotate(theta_x,theta_y,theta_z);

        // viewport projection + draw lines

        for (int i = 0; i < 8; i++)
        {
            // rotate points
            vector_t rotated = vector_transform(&R, &model_points[i]);

            render_points[i] = vector_scale(&rotated, zoom/* / LINE_WIDTH*/);

            if (i < 4) {
                SDL_RenderLine(renderer, SCREEN_WIDTH/2 + render_points[0].x, SCREEN_HEIGHT/2 - render_points[0].z, SCREEN_WIDTH/2 + render_points[i].x, SCREEN_HEIGHT/2 - render_points[i].z);
                SDL_RenderLine(renderer, SCREEN_WIDTH/2 + render_points[7].x, SCREEN_HEIGHT/2 - render_points[7].z, SCREEN_WIDTH/2 + render_points[7-i].x, SCREEN_HEIGHT/2 - render_points[7-i].z);
            }
        }

        SDL_RenderLine(renderer, SCREEN_WIDTH/2 + render_points[1].x, SCREEN_HEIGHT/2 - render_points[1].z, SCREEN_WIDTH/2 + render_points[5].x, SCREEN_HEIGHT/2 - render_points[5].z);
        SDL_RenderLine(renderer, SCREEN_WIDTH/2 + render_points[1].x, SCREEN_HEIGHT/2 - render_points[1].z, SCREEN_WIDTH/2 + render_points[4].x, SCREEN_HEIGHT/2 - render_points[4].z);

        SDL_RenderLine(renderer, SCREEN_WIDTH/2 + render_points[2].x, SCREEN_HEIGHT/2 - render_points[2].z, SCREEN_WIDTH/2 + render_points[6].x, SCREEN_HEIGHT/2 - render_points[6].z);
        SDL_RenderLine(renderer, SCREEN_WIDTH/2 + render_points[2].x, SCREEN_HEIGHT/2 - render_points[2].z, SCREEN_WIDTH/2 + render_points[4].x, SCREEN_HEIGHT/2 - render_points[4].z);

        SDL_RenderLine(renderer, SCREEN_WIDTH/2 + render_points[3].x, SCREEN_HEIGHT/2 - render_points[3].z, SCREEN_WIDTH/2 + render_points[6].x, SCREEN_HEIGHT/2 - render_points[6].z);
        SDL_RenderLine(renderer, SCREEN_WIDTH/2 + render_points[3].x, SCREEN_HEIGHT/2 - render_points[3].z, SCREEN_WIDTH/2 + render_points[5].x, SCREEN_HEIGHT/2 - render_points[5].z);

        for (int i = 0; i < 3; i++)
        {
            vector_t rotated = vector_transform(&R, &axes[i]);

            render_axes[i] = vector_scale(&rotated, 50);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(renderer, 200, SCREEN_HEIGHT - 150, 200 + render_axes[0].x, SCREEN_HEIGHT - 150 - render_axes[0].z);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(renderer, 200, SCREEN_HEIGHT - 150, 200 + render_axes[1].x, SCREEN_HEIGHT - 150 - render_axes[1].z);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(renderer, 200, SCREEN_HEIGHT - 150, 200 + render_axes[2].x, SCREEN_HEIGHT - 150 - render_axes[2].z);

        SDL_RenderPresent(renderer);
    }

    // exit

    SDL_Quit();
    return 0;

    // TIMING MANAGER

    
}

// gcc -o main main.c `pkg-config sdl3 --cflags --libs`