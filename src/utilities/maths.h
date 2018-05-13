#ifndef RENDERENGINE_MATHS_H
#define RENDERENGINE_MATHS_H

#include <glm/glm.hpp>
#include <entities/camera.h>

class Maths {
public:
    static glm::mat4 createTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &rotation, float scale);
    static glm::mat4 createViewMatrix(Camera& camera);
};


#endif //RENDERENGINE_MATHS_H
