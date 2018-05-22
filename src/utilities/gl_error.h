#ifndef RENDERENGINE_GL_ERROR_H
#define RENDERENGINE_GL_ERROR_H

void _check_gl_error(const char *file, int line);

#define check_gl_error() _check_gl_error(__FILE__, __LINE__)

#endif //RENDERENGINE_GL_ERROR_H
