#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H


class Firebeam {
public:
    Firebeam() {}
    Firebeam(float x, float y,color_t color);
    glm::vec3 position;
    // float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int flag1);
private:
    VAO *object;
};

#endif 
