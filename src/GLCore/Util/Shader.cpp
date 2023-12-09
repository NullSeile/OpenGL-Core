#include "glpch.h"
#include "Shader.h"

#include <fstream>

namespace GLCore::Utils {

	std::optional<std::string> ValidateShader(std::string_view source)
	{
		GLuint program = glCreateProgram();

		GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);

		std::stringstream ss;
		ss << "#version 400\n";
		ss << source;
		auto src = ss.str();
		auto c_str = src.c_str();

		glShaderSource(shader, 1, &c_str, nullptr);
		glCompileShader(shader);
		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			return std::string(infoLog.data());
		}
		return {};
	}

	GLuint CreateShader(const std::string& source)
	{
		GLuint program = glCreateProgram();

		GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* src = source.c_str();

		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			LOG_ERROR("{0}", infoLog.data());
		}

		glAttachShader(program, shader);

		// Link
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			glDeleteShader(shader);

			LOG_ERROR("{0}", infoLog.data());
		}

		glDetachShader(program, shader);
		glDeleteShader(shader);

		return program;
	}

}