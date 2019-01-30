#include "magnet.h"
#include "main.h"

Magnet::Magnet( float x, float y, color_t color1, color_t color2) {
   this->position = glm::vec3(x, y, 0);
    GLfloat vertex_buffer_data[] = {
        -0.5f,0.5f,0.0f,
        0.5f,0.5f,0.0f,
        0.5f,0.25f,0.0f,

        -0.5f,0.5f,0.0f,
        -0.5f,0.25f,0.0f,
        0.5f,0.25f,0.0f,

        -0.75f,0.25f,0.0f,
        -0.5f,0.25f,0.0f,
        -0.5f,-0.25f,0.0f,

        -0.75f,0.25f,0.0f,
        -0.75f,-0.25f,0.0f,
        -0.5f,-0.25f,0.0f,

        0.75f,0.25f,0.0f,
        0.5f,0.25f,0.0f,
        0.5f,-0.25f,0.0f,

        0.75f,0.25f,0.0f,
        0.75f,-0.25f,0.0f,
        0.5f,-0.25f,0.0f,
    };

    this->object1 = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data, color1, GL_FILL);

    GLfloat vertex_buffer_data1[] = {
        -0.75f,-0.25f,0.0f,
        -0.5f,-0.25f,0.0f,
        -0.5f,-0.35f,0.0f,

        -0.75f,-0.25f,0.0f,
        -0.75f,-0.35f,0.0f,
        -0.5f,-0.35f,0.0f,
    };
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color2, GL_FILL);

    GLfloat vertex_buffer_data2[] = {
        0.75f,-0.25f,0.0f,
        0.5f,-0.25f,0.0f,
        0.5f,-0.35f,0.0f,

        0.75f,-0.25f,0.0f,
        0.75f,-0.35f,0.0f,
        0.5f,-0.35f,0.0f,
    };
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color2, GL_FILL);



}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    // this->rotation+=1.0f;
}



