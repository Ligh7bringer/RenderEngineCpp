#ifndef RENDERENGINE_MATHS_H
#define RENDERENGINE_MATHS_H

#include <glm/glm.hpp>

class Maths {
public:
    static glm::mat4 createTransformationMatrix(const glm::vec3& translation, float rx, float ry, float rz, float scale);
private:

};


#endif //RENDERENGINE_MATHS_H
