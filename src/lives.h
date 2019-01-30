#include "main.h"

#ifndef LIVES_H
#define LIVES_H


class Lives {
public:
    Lives() {}
    Lives(float x, float y,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif 
