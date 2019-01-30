#include "main.h"

#ifndef TUNNEL_H
#define TUNNEL_H


class Tunnel {
public:
    Tunnel() {}
    Tunnel(float x, float y, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
