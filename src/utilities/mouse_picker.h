#ifndef RENDERENGINE_MOUSE_PICKER_H
#define RENDERENGINE_MOUSE_PICKER_H

#include <glm/glm.hpp>

#include <entities/camera.h>

class MousePicker {
public:
    MousePicker(const Camera &cam, const glm::mat4 &projMat, const Terrain &terrain);
    void update();
    glm::vec3 calculateMouseRay();
    glm::vec2 toDeviceCoords(float mouseX, float mouseY);
    glm::vec4 toEyeCoords(const glm::vec4& clipCoords);
    glm::vec3 toWorldCoords(const glm::vec4& eyeCoords);
    glm::vec3 getCurrentRay();

    const glm::vec3 &getIntersectionPos() const;

private:
    const int RECURSION_COUNT = 200;
    const float RAY_RANGE = 600.f;

    glm::vec3 _currentRay;
    glm::mat4 _projectionMatrix;
    glm::mat4 _viewMatrix;
    const Camera& _camera;
    Terrain _terrain;
    glm::vec3 _currentTerrainPoint;

    glm::vec3 getPointOnRay(const glm::vec3& ray, float distance);
    glm::vec3 binarySearch(int count, float start, float finish, const glm::vec3& ray);
    bool intersectionInRange(float start, float finish, const glm::vec3& ray);
    bool isUnderground(const glm::vec3& position);
};


#endif //RENDERENGINE_MOUSE_PICKER_H
