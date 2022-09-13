#include "RenderUtils.h"

/*!
 * Draw a one pixel wide border around a rectangle
 * */
void RenderUtils::drawOutline(SDL_Rect rect, SDL_Color c, SDL_Renderer* renderer){
    // Set color
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    // Draw x-border
    for(int u = rect.x; u < rect.x + rect.w; u++){
        SDL_RenderDrawPoint(renderer, u, rect.y);
        SDL_RenderDrawPoint(renderer, u, rect.y + rect.h);
    }
    // Draw y-border
    for(int v = rect.y; v < rect.y + rect.h; v++){
        SDL_RenderDrawPoint(renderer, rect.x, v);
        SDL_RenderDrawPoint(renderer, rect.x + rect.w, v);
    }
}

void RenderUtils::drawOutline(Vector2 pos, Vector2 size, SDL_Color c, SDL_Renderer* renderer){
    // Set color
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    // Draw x-border
    for(int u = pos.x; u < pos.x + size.x; u++){
        SDL_RenderDrawPoint(renderer, u, pos.y);
        SDL_RenderDrawPoint(renderer, u, pos.y + size.y);
    }
    // Draw y-border
    for(int v = pos.y; v < pos.y + size.y; v++){
        SDL_RenderDrawPoint(renderer, pos.x, v);
        SDL_RenderDrawPoint(renderer, pos.x + size.x, v);
    }
}

void RenderUtils::drawCross(Vector2 point, int size, SDL_Color c, SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    for(int u = point.x - size; u < point.x + size; u++){
        SDL_RenderDrawPoint(renderer, u, point.y);
    }
    for(int v = point.y - size; v < point.y + size; v++){
        SDL_RenderDrawPoint(renderer, point.x, v);
    }
}
