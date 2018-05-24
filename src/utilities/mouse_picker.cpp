#include "mouse_picker.h"
#include "maths.h"
#include <engine/window_manager.h>

MousePicker::MousePicker(const Camera &cam, const glm::mat4 &projMat, const Terrain &terrain) :
        _camera(cam), _projectionMatrix(projMat), _viewMatrix(Maths::createViewMatrix(cam)), _terrain(terrain) {}

void MousePicker::update() {
    //update view matrix
    _viewMatrix = Maths::createViewMatrix(_camera);
    _currentRay = calculateMouseRay();
    if (intersectionInRange(0, RAY_RANGE, _currentRay)) {
        _currentTerrainPoint = binarySearch(0, 0, RAY_RANGE, _currentRay);
    } else {
        _currentTerrainPoint = { 0, 0, 0};
    }
}

glm::vec3 MousePicker::calculateMouseRay() {
    auto mousePos = WindowManager::getCursorPosition();
    auto deviceCoords = toDeviceCoords(mousePos.x, mousePos.y);
    glm::vec4 clipCoords = { deviceCoords.x, deviceCoords.y, -1.f, 1.f };
    auto eyeCoords = toEyeCoords(clipCoords);
    auto worldRay = toWorldCoords(eyeCoords);

    return worldRay;
}

glm::vec2 MousePicker::toDeviceCoords(float mouseX, float mouseY) {
    auto windowSize = WindowManager::getWindowSize();
    auto x = (2.f * mouseX) / windowSize.x - 1.f;
    auto y = (2.f * mouseY) / windowSize.y - 1.f;
    return glm::vec2(x, -y);
}

glm::vec4 MousePicker::toEyeCoords(const glm::vec4 &clipCoords) {
    auto invertedProjection = glm::inverse(_projectionMatrix);
    auto eyeCoords = invertedProjection * clipCoords;
    return glm::vec4(eyeCoords.x, eyeCoords.y, -1.f, 0.f);
}

glm::vec3 MousePicker::toWorldCoords(const glm::vec4 &eyeCoords) {
    auto invertedView = glm::inverse(_viewMatrix);
    auto rayWorld = invertedView * eyeCoords;
    glm::vec3 mouseRay = { rayWorld.x, rayWorld.y, rayWorld.z };
    mouseRay = glm::normalize(mouseRay);

    return mouseRay;
}


glm::vec3 MousePicker::getCurrentRay() {
    return _currentRay;
}

glm::vec3 MousePicker::getPointOnRay(const glm::vec3 &ray, float distance) {
    auto camPos = _camera.getPosition();
    auto scaledRay = ray * distance;
    return camPos + scaledRay;
}

glm::vec3 MousePicker::binarySearch(int count, float start, float finish, const glm::vec3 &ray) {
    auto half = start + ((finish - start) / 2.f);
    if(count >= RECURSION_COUNT) {
        return getPointOnRay(ray, half);
    }

    if (intersectionInRange(start, half, ray)) {
        return binarySearch(count + 1, start, half, ray);
    } else {
        return binarySearch(count + 1, half, finish, ray);
    }
}

bool MousePicker::intersectionInRange(float start, float finish, const glm::vec3 &ray) {
    auto startPoint = getPointOnRay(ray, start);
    auto endPoint = getPointOnRay(ray, finish);

    return !isUnderground(startPoint) && isUnderground(endPoint);
}

bool MousePicker::isUnderground(const glm::vec3 &position) {
    auto height = _terrain.getHeightOfTerrain(position.x, position.z);
    return position.y < height;
}

const glm::vec3 &MousePicker::getIntersectionPos() const {
    return _currentTerrainPoint;
}







