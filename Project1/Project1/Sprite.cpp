#include "Sprite.h"


Sprite::Sprite()
{
	position = vec2(0, 0);
	rotation = 0;
	size = vec2(100, 100);
	radius = 50;
	EnableCollisions = false;
	IsColloding = false;
}


Sprite::~Sprite()
{
}

void Sprite::render()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, TextureID);  // Binding of GLtexture name 

	glTranslatef(position.x, position.y, 0);
	glRotatef(rotation, 0, 0, 1);
	glScalef(size.x, size.y, 0);

	glBegin(GL_QUADS);


	glTexCoord2i(0, 0);
	glVertex2i(0, 0);

	glTexCoord2i(1, 0);
	glVertex2i(1, 0);

	glTexCoord2i(1, 1);
	glVertex2i(1, 1);

	glTexCoord2i(0, 1);
	glVertex2i(0, 1);


	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();

	update();
}

void Sprite::setTexture(GLint t)
{
	TextureID = t;
}