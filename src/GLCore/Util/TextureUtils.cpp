#include <glpch.h>

#include "TextureUtils.h"

#include <stb_image_write.h>

namespace GLCore::Utils {

	static std::string ToLower(std::string& str)
	{
		for (auto c : str)
			c = (char)std::tolower((int)c);

		return str;
	}

	bool ExportTexture(GLuint textureID, const std::string& filename, bool ignore_alpha)
	{
		glBindTexture(GL_TEXTURE_2D, textureID);

		int width, height;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

		bool success = false;

		if (width > 0 && height > 0)
		{
			BYTE* pixels = new BYTE[width * height * 4];

			glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

			if (ignore_alpha)
				for (int i = 0; i < width * height; i++)
					pixels[i*4 + 3] = 255;

			// Code from SFML
			const std::size_t dot = filename.find_last_of('.');
			const std::string extension = dot != std::string::npos ? ToLower(filename.substr(dot + 1)) : "";

			stbi_flip_vertically_on_write(1);
			if (extension == "bmp")
			{
				if (stbi_write_bmp(filename.c_str(), width, height, 4, pixels))
					success = true;
			}
			else if (extension == "tga")
			{
				if (stbi_write_tga(filename.c_str(), width, height, 4, pixels))
					success = true;
			}
			else if (extension == "png")
			{
				if (stbi_write_png(filename.c_str(), width, height, 4, pixels, 0))
					success = true;
			}
			else if (extension == "jpg" || extension == "jpeg")
			{
				if (stbi_write_jpg(filename.c_str(), width, height, 4, pixels, 90))
					success = true;
			}
			else
			{
				LOG_ERROR("File extension `{0}` is not valid!", extension);
				exit(EXIT_FAILURE);
			}

			delete[] pixels;
		}
		return success;
	}

}
