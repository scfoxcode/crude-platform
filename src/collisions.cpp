#include "collisions.h"

bool Collisions::isOverlapping(SDL_Rect& a, SDL_Rect& b) {
    // a is to the left
    if ((a.x + a.w) < b.x) {
        return false;
    }

    // a is to the right
    if (a.x > (b.x + b.w)) {
        return false;
    }

    // a is above
    if ((a.y + a.h) < b.y) {
        return false;
    }
    
    // a is below 
    if (a.y > (b.y + b.h)) {
        return false;
    }

    return true;
}
