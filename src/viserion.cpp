#include "viserion.h"
#include "main.h"

Viserion::Viserion(float x, float y, color_t color1, color_t color2, color_t color3) {
   this->position = glm::vec3(x, y, 0);
    // speed = 0.01;
    // this->speedY = 0;
    // this->speedX = 0;

    // speed = -0.01;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
       0.0f,0.0f,0.0f,
       0.5f,0.5f,0.0f,
       1.0f,0.0f,0.0f,

       0.0f,0.0f,0.0f,
       0.5f,-0.5f,0.0f,
       1.0f,0.0f,0.0f,

       0.0f,0.0f,0.0f,
      -0.5f,0.5f,0.0f,
      -1.0f,0.0f,0.0f,

       0.0f,0.0f,0.0f,
      -0.5f,-0.5f,0.0f,
      -1.0f,0.0f,0.0f,

    };

    this->object1 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color1, GL_FILL);

    static const GLfloat vertex_buffer_data1[] = {
      0.0f,0.0f,0.0f,
      0.0f,1.0f,0.0f,
      0.5f,1.0f,0.0f,

      0.0f,0.0f,0.0f,
      0.0f,-1.0f,0.0f,
      0.5f,-1.0f,0.0f,
    };
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color2, GL_FILL);

    static const GLfloat vertex_buffer_data2[] = {
      1.0f,0.0f,0.0f,
      1.5f,0.5f,0.0f,
      1.5f,-0.5f,0.0f,

      -0.5f,1.0f,0.0f,
      0.0f,1.5f,0.0f,
      0.5f,1.0f,0.0f,

      -0.5f,-1.0f,0.0f,
      0.0f,-1.5f,0.0f,
      0.5f,-1.0f,0.0f,

      -0.75f,0.25f,0.0f,
      -0.5f,0.5f,0.0f,
      -1.0f,0.5f,0.0f,

      -0.75f,-0.25f,0.0f,
      -0.5f,-0.5f,0.0f,
      -1.0f,-0.5f,0.0f,

      -0.75f,0.25f,0.0f,
      -1.5f,0.0f,0.0f,
      -1.0f,0.0f,0.0f,

       -0.75f,-0.25f,0.0f,
      -1.5f,0.0f,0.0f,
      -1.0f,0.0f,0.0f,     
    };
    this->object3 = create3DObject(GL_TRIANGLES, 7*3, vertex_buffer_data2, color3, GL_FILL);

}

void Viserion::draw(glm::mat4 VP) {
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

void Viserion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Viserion::tick(int flag2) {
    if(flag2==1)
      this->position.y-=0.05;
    else
      this->position.y+=0.05;
    
}



