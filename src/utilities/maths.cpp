#include "maths.h"
#include <glm/gtc/matrix_transform.hpp>
#include <Log.h>

//creates a transformation matrix
glm::mat4 Maths::createTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &rotation, float scale) {
    glm::mat4 matrix(1.0f); // <- creates an identity matrix

    //convenient glm methods to calculate the final matrix
    //has to be done in this order
    matrix = glm::translate(matrix, translation);
    matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3{1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3{0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3{0, 0, 1});
    matrix = glm::scale(matrix, glm::vec3{scale, scale, scale});

    return matrix;
}

//creates a view matrix so that the camera can be moved
glm::mat4 Maths::createViewMatrix(Camera &camera) {
    glm::mat4 matrix(1.0f);

    matrix = glm::rotate(matrix, glm::radians(camera.getPitch()), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(camera.getYaw()), {0, 1, 0});
    //don't forget to translate in the opposite direction!
    matrix = glm::translate(matrix, -camera.getPosition());

    return matrix;
}

float Maths::toRadians(float deg) {
    return static_cast<float>(deg * M_PI / 180.0);
}
