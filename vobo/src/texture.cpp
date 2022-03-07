#include "texture.h"

Texture::Texture(const std::string& source, int desiredChannels) {
    /* Load in the image from the source directory  */
    int width, height, channels;
    stbi_uc* data =
        stbi_load(source.c_str(), &width, &height, &channels, desiredChannels);
    if (data) {
        VOBO_DEBUG_LOG("[Texture] Loaded image from"
                       << source << "\n\tChannels: " << channels);
    } else {
        VOBO_ERROR_LOG("[Texture] Could not load image from: " << source);
    }

    /* Get an ID */
    glCreateTextures(GL_TEXTURE_2D, 1, &renderID_);
    /* Allocate space on the GPU */
    glTextureStorage2D(renderID_, 1, GL_SRGB8, width, height);
    /* Set texture parameters */
    glTextureParameteri(renderID_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(renderID_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /* Upload our texture */
    glTextureSubImage2D(renderID_, 0, 0, 0, width, height, GL_RGB,
                        GL_UNSIGNED_BYTE, data);
    /* Don't need the texture in CPU memory anymore */
    stbi_image_free(data);
}

Texture::~Texture() {
    /* Delete the texture from the GPU */
    glDeleteTextures(1, &renderID_);
}

void Texture::bind(unsigned int slot) { glBindTextureUnit(slot, renderID_); }
