#include "collisions.h"
#include <math.h>
#include <algorithm>

glm::vec2 Collisions::centre(SDL_Rect& a) {
    return glm::vec2(a.x + a.w * 0.5f, a.y + a.h * 0.5f);
}

bool Collisions::isOverlapping(SDL_Rect& a, SDL_Rect& b) {
    // a is to the left
    if ((a.x + a.w) <= b.x) {
        return false;
    }

    // a is to the right
    if (a.x >= (b.x + b.w)) {
        return false;
    }

    // a is above
    if ((a.y + a.h) <= b.y) {
        return false;
    }
    
    // a is below 
    if (a.y >= (b.y + b.h)) {
        return false;
    }

    return true;
}

void Collisions::resolveCollision(
    glm::vec2& position,
    glm::vec2& velocity,
    SDL_Rect& a,
    SDL_Rect& b) {

    // Use position of centre of rect for physics calcs
    glm::vec2 aP = Collisions::centre(a);
    glm::vec2 bP = Collisions::centre(b);

    // We only want to change one position and velocity axis per collision
    
    // Get difference between positions 
    // glm::vec2 ds = glm::vec2(aP.x, aP.y) - glm::vec2(b.x, b.y);
    glm::vec2 ds = aP - bP;

    // Minimum magnitude needed on each axis to avoid collision
    float minXDs = float(a.w) * 0.5f + float(b.w) * 0.5f;
    float minYDs = float(a.h) * 0.5f + float(b.h) * 0.5f;

    // This approach seems to be slightly broken on block edges with very slightly overlaps and low velocity
    // Units of time needed on each access to avoid collision. The smaller one is the axis we collided from
    float horizontal = (minXDs - fabs(ds.x)) / std::max<float>(fabs(velocity.x), 0.0001f); 
    float vertical = (minYDs - fabs(ds.y)) / std::max<float>(fabs(velocity.y), 0.0001f); 

    // printf("Min xds %f %f %f\n", minXDs, fabs(ds.x), fabs(velocity.x));
    // printf("Horiz %f Vert %f\n", horizontal, vertical);
    bool xColl= horizontal < vertical; // True if collision was horizontal
    if (xColl) {
        printf("ALpha %f %f\n", horizontal, vertical);
        if (velocity.x > 0) {
            aP.x = bP.x - minXDs;
            
        } else {
            aP.x = bP.x + minXDs;
        }
        velocity.x = 0.0f;
    } else {
        // printf("Bravo");
        if (velocity.y > 0) {
            // printf("%f %f %f cheese\n", float(bP.y), float(position.y), minYDs);
            aP.y = bP.y - minYDs;
            
        } else {
            aP.y = bP.y + minYDs;
        }
        velocity.y = 0.0f;
    }

    a.x = aP.x - a.w * 0.5f; // So shit doing this subtraction like this
    a.y = aP.y - a.h * 0.5f;
    position.x = a.x;
    position.y = a.y;
}
