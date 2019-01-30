#include "tunnel.h"
#include "main.h"

Tunnel::Tunnel(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    static GLfloat vertex_buffer_data[10000];
    int j=0;
    for (int i = 0; i < 180; ++i)
    {
        vertex_buffer_data[j++]=10*0.20*cos((float)i*M_PI/180.0);
        vertex_buffer_data[j++]=10*0.20*sin((float)i*M_PI/180.0);
        vertex_buffer_data[j++]=10*0.0f;
        vertex_buffer_data[j++]=10*0.1*cos((float)i*M_PI/180.0);
        vertex_buffer_data[j++]=10*0.1*sin((float)i*M_PI/180.0);
        vertex_buffer_data[j++]=10*0.0f;
        vertex_buffer_data[j++]=10*0.1*cos((float)(i+1)*M_PI/180.0);
        vertex_buffer_data[j++]=10*0.1*sin((float)(i+1)*M_PI/180.0);
        vertex_buffer_data[j++]=10*0.0f;

    }

    this->object = create3DObject(GL_TRIANGLES, 1000*3, vertex_buffer_data, color, GL_FILL);
}

void Tunnel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Tunnel::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Tunnel::tick() {
    
}



