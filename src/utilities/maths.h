#ifndef RENDERENGINE_MATHS_H
#define RENDERENGINE_MATHS_H

#include <glm/glm.hpp>

#include <entities/camera.h>

class Maths {
public:
    static glm::mat4 createTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &rotation, float scale);
    static glm::mat4 createTransformationMatrix(const glm::vec2 &translation, const glm::vec2& scale);
    static glm::mat4 createViewMatrix(Camera& camera);
    static float toRadians(float deg);
    static float barryCentricInterpolation(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec2& pos);
};


#endif //RENDERENGINE_MATHS_H
