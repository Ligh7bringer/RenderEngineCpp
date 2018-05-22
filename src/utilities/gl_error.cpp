#include "gl_error.h"
#include"../Log.h"

#include <string>

#include <glad/glad.h>

using namespace std;

void _check_gl_error(const char *file, int line) {
    GLenum err (glGetError());

    while(err!=GL_NO_ERROR) {
        string error;

        switch(err) {
            case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
            case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
            case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
            case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
        }

        LOG(ERR) << "GL_" << error << " - " << file << ":" << line;
        err=glGetError();
    }
}

