#include "main.h"

#ifndef NINJASTARS_H
#define NINJASTARS_H


class Ninjastars {
public:
    Ninjastars() {}
    Ninjastars(float x, float y,color_t color1,color_t color2);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedX;
    double speedY;
private:
    VAO *object1;
    VAO *object2;
};

#endif 
