#include <stdio.h>
#include <SDL2/SDL.h>
#include "setup.cpp"
#include "inpututils.cpp"

using namespace std;

int main(int argc, char* args[]){
    
    if(!init()){
        printf("Failed to initialize SDL, error: %s\n", SDL_GetError());
    }
    else{
            //Main loop flag
            bool quit = false;
            //Event handler
            SDL_Event e;
            //Run the window until quit is true 
            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    //Request to quit
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN){
                        testArrows(e);
                    }
                }
                //Clear screen
                SDL_RenderClear(gRenderer);

                //Render texture to screen
                SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

                //Update screen
                SDL_RenderPresent(gRenderer); 
            }
        
    }
    
    close();
    return 0;
}