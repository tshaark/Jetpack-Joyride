#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y,color_t color);
    glm::vec3 position;
    float ro;
    float iniX;
    int flag=0;
    float rotation;
    float direction=-1.0;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif 
