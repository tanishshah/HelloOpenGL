#include "texture.hpp"

Texture::Texture(const std::string& texture_file) : is_good(1), texture(0){
	GLint im_x, im_y, im_channels;
	unsigned char* img = stbi_load(texture_file.c_str(), &im_x, &im_y, &im_channels, STBI_rgb_alpha);
	if (!img) {
		std::cerr << "Failed to load texture: " << texture_file << std::endl;
		this->is_good = false;
		return;
	}
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// using the default texture wrapping mode for now

	stbi_image_free(img);
}

Texture::~Texture(){

}
