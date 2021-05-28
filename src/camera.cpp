#include <camera.h>
#include <cmath>

camera::camera(float fov, float near, float far, float width, float height){
    pos = glm::vec3(0.0f);
    this->fov = fov;
    this->near = near;
    this->far = far;
    orientation = glm::vec3(1.0f,0.0f,0.0f);
    this->width = width;
    this->height = height;
}

void camera::avancer(float distance){
    //modifier la position de la camera
    this->pos += distance*this->orientation;
}

glm::mat4 camera::calculermatrice(){
    //projection en perspective
    float aspect = this->width/this->height;
    return glm::perspective(this->fov, aspect, this->near, this->far)*glm::lookAt(pos, pos+orientation, glm::vec3(0.0f,0.0f,1.0f));
}

void camera::setdimension(float sw, float sh){
    this->width = sw;
    this->height = sh;
}

void camera::setangle(float angle){
    this->orientation = glm::vec3(std::cos(angle), std::sin(angle), 0);
}