#include "main.h"

#ifndef LIVESDISPLAY_H
#define LIVESDISPLAY_H


class Livesdisplay {
public:
    Livesdisplay() {}
    Livesdisplay(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP,int num);
    void set_position(float x, float y);
    void tick();
    std::string strn[10];
private:
    VAO *object[7];
};

#endif // BALL_H
