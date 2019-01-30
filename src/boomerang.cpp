#include "boomerang.h"
#include "main.h"
#include "math.h"


Boomerang::Boomerang(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    static const GLfloat vertex_buffer_data[] = {
        -0.5f,-0.5f,0.0f,
        -0.25f,0.25f,0.0f,
        -0.25f,-0.25f,0.0f,
        
        -0.25f,0.25f,0.0f,
        -0.25f,-0.25f,0.0f,
         0.25f,-0.25f,0.0f,
        
        -0.25f,0.25f,0.0f,
         0.25f,-0.25f,0.0f,
         0.25f,0.25f,0.0f,
        
         0.25f,-0.25f,0.0f,
         0.25f,0.25f,0.0f,
         0.5f,-0.5f,0.0f,

    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick() {
    if(flag==0)
    {
        this->flag=1;
        this->iniX=this->position.x;
    }
    this->rotation += 1.0f;
    // }
    this->position.x=12.0*cos(this->ro)-(12.0-this->iniX);
    // if(this->position)
    this->position.y=3.0f*sin(this->ro)+2.0f;
    ro+=0.01f;
}



