#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

class Shader
{
public:
    unsigned int ID;
    Shader() = default;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode   = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    // activate the shader
    void use()
    {
        glUseProgram(ID);
    }

    void stop() {
        glUseProgram(0);
    }

    void cleanUp() {
        glDeleteProgram(ID);
    }

    void bindAttribute(unsigned int attrib, const std::string& name) {
        glBindAttribLocation(ID, attrib, name.c_str());
    }

    GLint getUniformLocation(const std::string& name) {
        return getUniformLoc(name);
    }

    // utility uniform functions
    void setBool(const std::string &name, bool value) {
        glUniform1i(getUniformLoc(name), (int)value);
    }

    void setInt(const std::string &name, int value)
    {
        glUniform1i(getUniformLoc(name), value);
    }

    void setFloat(const std::string &name, float value)
    {
        glUniform1f(getUniformLoc(name), value);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) {
        glUniform3fv(getUniformLoc(name), 1, glm::value_ptr(value));
    }

    void setVec2(const std::string &name, const glm::vec2 &value) {
        glUniform2fv(getUniformLoc(name), 1, glm::value_ptr(value));
    }

    void setMatrix(const std::string& name, const glm::mat4& mat) {
        glUniformMatrix4fv(getUniformLoc(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

private:
    std::map<std::string, GLint> _uniforms;

    // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(unsigned int shader, const std::string &type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }

    //this will ensure locations of uniforms are stored once they are retrieved
    GLint getUniformLoc(const std::string& name) {
        //check if the location has already been retrived and stored
        if(_uniforms.count(name) != 0 ) {
            //if yes, return it
            return _uniforms[name];
        }

        //if not, get it
        auto location = glGetUniformLocation(ID, name.c_str());
        //store it
        _uniforms.insert(std::make_pair(name, location));

        //and return it
        return location;
    }
};

#endif