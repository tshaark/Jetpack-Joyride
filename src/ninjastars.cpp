#include "ninjastars.h"
#include "main.h"

Ninjastars::Ninjastars( float x, float y, color_t color1,color_t color2) {
   this->position = glm::vec3(x, y, 0);
   this->rotation = 0;
   this->speedX=0.01;
   this->speedY=0.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
        -0.1f,0.1f,0.0f,
         0.1f,0.1f,0.0f,
         0.1f,-0.1f,0.0f,

        -0.1f,0.1f,0.0f,
        -0.1f,-0.1f,0.0f,
         0.1f,-0.1f,0.0f,

    };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color1, GL_FILL);
    static const GLfloat vertex_buffer_data2[] = {
         0.1f,0.1f,0.0f,
         0.25f,0.0f,0.0f,
         0.1f,-0.1f,0.0f,

        -0.1f,0.1f,0.0f,
        -0.25f,0.0f,0.0f,
         -0.1f,-0.1f,0.0f,

         -0.1f,0.1f,0.0f,
        0.0f,0.25f,0.0f,
         0.1f,0.1f,0.0f,

         -0.1f,-0.1f,0.0f,
        0.0f,-0.25f,0.0f,
         0.1f,-0.1f,0.0f,

    };
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, color2, GL_FILL);


}

void Ninjastars::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, 1, 0));
    Matrices.model *= (translate*rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Ninjastars::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ninjastars::tick() {
    this->rotation+=0.1f;
    this->speedY+=0.0633;
    this->position.x-=0.4;
    this->position.y-=this->speedY;
}



