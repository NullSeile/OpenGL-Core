#pragma once

#include <string>

#include <glad/glad.h>

namespace GLCore::Utils {

	GLuint CreateShader(const std::string& source);
	std::optional<std::string> ValidateShader(std::string_view source);

}