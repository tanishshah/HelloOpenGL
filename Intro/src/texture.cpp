#include "texture.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif 

#include "stb/stb_image.h"

Texture::Texture(const std::string& texture_file) : is_good(1), texture(0){
	GLint im_x, im_y, im_channels;
	unsigned char* img = stbi_load(texture_file.c_str(), &im_x, &im_y, &im_channels, 0);
	if (!img) {
		std::cerr << "Failed to load texture: " << texture_file << std::endl;
		this->is_good = false;
		return;
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, im_x, im_y, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);
	// using the default texture wrapping mode for now

	stbi_image_free(img);
}

Texture::~Texture() {}

void Texture::use() {
	if (this->is_good) {
		glBindTexture(GL_TEXTURE_2D, this->texture);
	}
	else {
		std::cerr << "Tried to use texture when texture was not good " << std::endl;
	}
}