#ifndef _texture_h_
#define _texture_h_


#include "vobo_pch.h"
#include "glad.h"
#include "stb_image.h"
#include "log.h"

class Texture
{
private:
	unsigned int width_;
	unsigned int height_;
	unsigned int renderID_;
public:
 /**
  * Constructs a texture object loaded in from the specified file path
  */
	Texture(const std::string & source, int desiredChannels=0);
	~Texture();
	/* Bind the texture to a particular slot on the GPU */
	void bind(unsigned int slot);
};
#endif //_texture_h_ header