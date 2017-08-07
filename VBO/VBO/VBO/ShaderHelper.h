#ifndef _SHADER_HELPER__
#define _SHADER_HELPER__

#include <glew.h>
#include <freeglut.h>
#include <cstring>
#include <string>

class ShaderHelper {
private:
	//static const std::string TAG;

public:
	ShaderHelper();
	static std::string readShaderFileFromResource(const char* pFileName);
	static GLuint compileVertexShader(const char* shaderCode);
	static GLuint compileFragmentShader(const char* shaderCode);
	static GLuint compileShader(GLenum ShaderType, const char* shaderCode);
	static GLuint linkProgram(GLuint vertexShaderId, GLuint fragmentShaderId);
	static GLint validateProgram(GLuint programObjectId);
	static void compileAndLinkShaders(std::string vertex_shader, std::string fragment_shader, GLuint& program);
};

//std::string TAG = "ShaderHelper";
#endif