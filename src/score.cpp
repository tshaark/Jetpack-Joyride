#include "score.h"
#include "main.h"

Score::Score(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    static const GLfloat vertex_buffer_data[] = {
        
        -0.15f,0.23f,0.0f,
         0.15f,0.23f,0.0f,
         0.15f,0.17f,0.0f,

        -0.15f,0.23f,0.0f,
        -0.15f,0.17f,0.0f,
         0.15f,0.17f,0.0f,
     };
    this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);

    static const GLfloat vertex_buffer_data1[] = {
        -0.15f,0.17f,0.0f,
        -0.1f,0.17f,0.0f,
        -0.15f,0.0f,0.0f,

        -0.1f,0.17f,0.0f,
        -0.15f,0.0f,0.0f,
        -0.1f,0.0f,0.0f,
    };
    
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color, GL_FILL);
    
    static const GLfloat vertex_buffer_data2[] = {
        -0.1f,0.0f,0.0f,
        -0.15f,0.0f,0.0f,
        -0.1f,-0.17f,0.0f,

        -0.15f,0.0f,0.0f,
        -0.1f,-0.17f,0.0f,
        -0.15f,-0.17f,0.0f,
    };
    this->object[2] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, color, GL_FILL);

    static const GLfloat vertex_buffer_data3[] = {
        -0.15f,-0.17f,0.0f,
        -0.15f,-0.23f,0.0f,
         0.15f,-0.23f,0.0f,

        -0.15f,-0.17f,0.0f,
         0.15f,-0.17f,0.0f,
         0.15f,-0.23f,0.0f,
     };
     this->object[3] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, color, GL_FILL);

    static const GLfloat vertex_buffer_data4[] = { 
         0.15f,0.17f,0.0f,
         0.1f,0.17f,0.0f,
         0.15f,0.0f,0.0f,

         0.1f,0.17f,0.0f,
         0.15f,0.0f,0.0f,
         0.1f,0.0f,0.0f,
     };
     this->object[4] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, color, GL_FILL);

    static const GLfloat vertex_buffer_data5[] = { 
         0.1f,0.0f,0.0f,
         0.15f,0.0f,0.0f,
         0.1f,-0.17f,0.0f,

         0.15f,0.0f,0.0f,
         0.1f,-0.17f,0.0f,
         0.15f,-0.17f,0.0f,
     };
     this->object[5] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data5, color, GL_FILL);

    static const GLfloat vertex_buffer_data6[] = { 

         0.1f,0.05f,0.0f,
         -0.1f,0.05f,0.0f,
         0.1f,0.0f,0.0f,

         -0.1f,0.05f,0.0f,
         0.1f,0.0f,0.0f,
         -0.1f,0.0f,0.0f,
     };
     this->object[6] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data6, color, GL_FILL);
     this->strn[0] = "1111110";
     this->strn[1] = "0000110";
     this->strn[2] = "1011101";
     this->strn[3] = "1001111";
     this->strn[4] = "0100111";
     this->strn[5] = "1101011";
     this->strn[6] = "1111011";
     this->strn[7] = "1000110";
     this->strn[8] = "1111111";
     this->strn[9] = "1101111";

}

void Score::draw(glm::mat4 VP,int num) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<7;i++)
    {
        if(strn[num][i] == '1')
            draw3DObject(this->object[i]);
    }
}

void Score::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Score::tick() {
}



