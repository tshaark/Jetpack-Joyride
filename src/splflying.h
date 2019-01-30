#include "main.h"

#ifndef SPLFLYING_H
#define SPLFLYING_H


class Splflying {
public:
    Splflying() {}
    Splflying(float x, float y,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif 
