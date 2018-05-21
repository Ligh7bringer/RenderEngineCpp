#ifndef RENDERENGINE_GUI_TEXTURE_H
#define RENDERENGINE_GUI_TEXTURE_H

#include "../../lib/glm/glm/vec2.hpp"

class GuiTexture {
public:
    GuiTexture(unsigned int id, const glm::vec2& pos, const glm::vec2 scale) :
            _id(id), _position(pos), _scale(scale) {}

    unsigned int getID() const {
        return _id;
    }

    const glm::vec2 &getPosition() const {
        return _position;
    }

    const glm::vec2 &getScale() const {
        return _scale;
    }

private:
    unsigned int _id;
    glm::vec2 _position;
    glm::vec2 _scale;
};


#endif //RENDERENGINE_GUI_TEXTURE_H
