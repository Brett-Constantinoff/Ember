#pragma once
#include <GL/glew.h>
#include <stdint.h>
#include <iostream>
#include <vector>


class Texture
{
public:
	Texture(bool cubeMap = false);
	~Texture();
	void active(uint32_t index);
	void bind(void);
	void unBind(void);
	void load2D(const char* file);
	void loadSkybox(std::vector<const char*> files);

private:
	uint32_t m_id;
	uint32_t m_type;
	const char* m_file;
};