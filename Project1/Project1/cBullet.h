/*
=================
cBullet.h
- Header file for class definition - SPECIFICATION
- Header file for the Bullet class which is a child of cSprite class
=================
*/
#ifndef _CBULLET_H
#define _CBULLET_H
#include "WindowsAndOpenGL.h"
#include "Sprite.h"
#include "cTexture.h"


class cBullet : public Sprite
{
private:
	glm::vec2 bulletVelocity = glm::vec2(0.0f, 0.0f);

public:
	//cBullet(vector<cTexture*> tileTextList)
	void update();

	cBullet();
	~cBullet();

	void update(float deltaTime);		// Bullet update method
	void setBulletVelocity(glm::vec2 bulletVel);   // Sets the velocity for the Bullet
	glm::vec2 getBulletVelocity();				 // Gets the Bullet velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif