#ifndef __CAMERA_H__

#define __CAMERA_H__

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

class camera {
    glm::vec3 pos;
    float fov;
    float near;
    float far;
    glm::vec3 orientation;
    float width;
    float height;

    public:

    camera(float fov, float near, float far, float width, float height);                    //constructeur
    void avancer(float distance);
    glm::mat4 calculermatrice();                                                            //projection en perspective
    void setdimension(float sw, float sh);
    void setangle(float angle);
};

#endif