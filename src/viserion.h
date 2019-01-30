#include "main.h"

#ifndef VISERION_H
#define VISERION_H


class Viserion {
public:
    Viserion() {}
    Viserion(float x, float y, color_t color1, color_t color2, color_t color3);
    glm::vec3 position;
    // float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int flag2);
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif 
