#pragma once
#include "WindowsAndOpenGL.h"

class Sprite
{
	//protected to only allow its self and subclasses to use it
protected:
	GLint TextureID;

public:
	vec2 position;
	double rotation;
	vec2 size;
	float radius;
	bool IsColloding;
	bool EnableCollisions;

	void render();
	virtual void update(){}
	void setTexture(GLint t);

	Sprite();
	~Sprite();
};

