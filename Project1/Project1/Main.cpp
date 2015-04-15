#include "WindowsAndOpenGL.h"
#include "cTexture.h"
#include "Sprite.h"
#include "cBullet.h"

void render();
void reshape(int w, int h);
void keyboard(unsigned char c, int x, int y);
void special(int key, int x, int y);

int shipVelocity = 20;
int sceneLoaded = 0;

vector<Sprite*> sprites;

// used to create the level
void CreateLevel()
{
	if (sceneLoaded == 0)
	{
		//draws background
		cTexture backgroundTexture = cTexture("Images/background.png");
		Sprite* background = new Sprite();
		background->position = vec2(0, 0);
		background->rotation = 0;
		background->size = vec2(700, 900);
		background->setTexture(backgroundTexture.getTexture());
		sprites.push_back(background);

		//draws your ship
		cTexture shipTexture = cTexture("Images/ship.png");
		Sprite* ship = new Sprite();
		ship->position = vec2(350, 800);
		ship->rotation = 0;
		ship->size = vec2(100, 100);
		ship->setTexture(shipTexture.getTexture());
		sprites.push_back(ship);

		//draws option for start
		cTexture startTexture = cTexture("Images/start.png");
		Sprite* start = new Sprite();
		start->EnableCollisions = true;
		start->position = vec2(100, 250);
		start->rotation = 0;
		start->size = vec2(140, 100);
		start->setTexture(startTexture.getTexture());
		sprites.push_back(start);

		//draws option for quit
		cTexture quitTexture = cTexture("Images/quit.png");
		Sprite* quit = new Sprite();
		quit->EnableCollisions = true;
		quit->position = vec2(460, 250);
		quit->rotation = 0;
		quit->size = vec2(140, 100);
		quit->setTexture(quitTexture.getTexture());
		sprites.push_back(quit);


		//draw instructions
		cTexture instructionsTexture = cTexture("Images/instructions.png");
		Sprite* instructions = new Sprite();
		instructions->position = vec2(30, 400);
		instructions->rotation = 0;
		instructions->size = vec2(640, 400);
		instructions->setTexture(instructionsTexture.getTexture());
		sprites.push_back(instructions);
		

		//plays background music
		mciSendString("open Sounds/background.mp3 type mpegvideo alias music", NULL, 0, 0);
		mciSendString("play music repeat", NULL, 0, 0);
	}
	else if (sceneLoaded == 1)
	{
		//create second scene
		//draws background
		cTexture backgroundTexture = cTexture("Images/background.png");
		Sprite* background = new Sprite();
		background->position = vec2(0, 0);
		background->rotation = 0;
		background->size = vec2(700, 900);
		background->setTexture(backgroundTexture.getTexture());
		sprites.push_back(background);

		//draws your ship
		cTexture shipTexture = cTexture("Images/ship.png");
		Sprite* ship = new Sprite();
		ship->position = vec2(350, 800);
		ship->rotation = 0;
		ship->size = vec2(100, 100);
		ship->setTexture(shipTexture.getTexture());
		sprites.push_back(ship);

		//draws enemies
		cTexture enemyTexture = cTexture("Images/enemyShip.png");
		Sprite* enemy = new Sprite();
		enemy->EnableCollisions = true;
		enemy->position = vec2(100, 100);
		enemy->rotation = 0;
		enemy->size = vec2(100, 100);
		enemy->setTexture(enemyTexture.getTexture());
		sprites.push_back(enemy);

		Sprite* enemy1 = new Sprite();
		enemy1->EnableCollisions = true;
		enemy1->position = vec2(300, 100);
		enemy1->rotation = 0;
		enemy1->size = vec2(100, 100);
		enemy1->setTexture(enemyTexture.getTexture());
		sprites.push_back(enemy1);

		Sprite* enemy2 = new Sprite();
		enemy2->EnableCollisions = true;
		enemy2->position = vec2(500, 100);
		enemy2->rotation = 0;
		enemy2->size = vec2(100, 100);
		enemy2->setTexture(enemyTexture.getTexture());
		sprites.push_back(enemy2);

		Sprite* enemy3 = new Sprite();
		enemy3->EnableCollisions = true;
		enemy3->position = vec2(200, 300);
		enemy3->rotation = 0;
		enemy3->size = vec2(100, 100);
		enemy3->setTexture(enemyTexture.getTexture());
		sprites.push_back(enemy3);

		Sprite* enemy4 = new Sprite();
		enemy4->EnableCollisions = true;
		enemy4->position = vec2(400, 300);
		enemy4->rotation = 0;
		enemy4->size = vec2(100, 100);
		enemy4->setTexture(enemyTexture.getTexture());
		sprites.push_back(enemy4);
	}
}

int main(int argc, char **argv)
{
	// Start Glut
	glutInit(&argc, argv);

	//Set up memory buffers for display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	//setup glut window
	glutInitWindowSize(700, 900);
	glutCreateWindow("Space Blast");

	//Game
	CreateLevel();

	//steup OpenGL Methods
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	//Very important! This initializes the entry point in the OpenGL driver so we can 
	//call the functions in the api
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW error");
		return 1;
	}

	//Start up a loop that runs in the background
	glutMainLoop();
	return 0;
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//detecting collision
	for (Sprite* s : sprites)
	{
		s->render();
		if (s->EnableCollisions)
		{
			for (Sprite* cS : sprites)
			{
				//enable collisions on other sprites
				if (cS->EnableCollisions && cS != s)
				{
					//calculate distance from objects
					if (glm::distance(s->position + vec2(0, 0), cS->position + vec2(0, 0)) < (cS->radius + s->radius) / 2)
					{
						s->IsColloding = true;
					}
					else
						s->IsColloding = false;
				}
			}
		}
	}

	if (sceneLoaded == 0)
	{
		// trigger when quit shot
		if (sprites[3]->IsColloding)
		{
			exit(0);
		}
	
		//trigger when start shot
		if (sprites[2]->IsColloding)
		{
			sceneLoaded = 1;
			sprites.clear();
			CreateLevel();
		}
	}

	if (sceneLoaded == 1)
	{
		//trigger when enemies shot
		if (sprites[2]->IsColloding)
		{
			sprites.erase(sprites.begin() + 2);
			cout << "hit" << endl;
		}
		if (sprites[3]->IsColloding)
		{
			sprites.erase(sprites.begin() + 3);
			cout << "hit" << endl;
		}
		if (sprites[4]->IsColloding)
		{
			sprites.erase(sprites.begin() + 4);
			cout << "hit" << endl;
		}
		if (sprites[5]->IsColloding)
		{
			sprites.erase(sprites.begin() + 5);
			cout << "hit" << endl;
		}
		if (sprites[6]->IsColloding)
		{
			sprites.erase(sprites.begin() + 6);
			cout << "hit" << endl;
		}
	}
	glutSwapBuffers();
	glutPostRedisplay();
}


// controls for A&D usage and space
void keyboard(unsigned char c, int x, int y)
{
		if (c == 'd')

		{
			if (sprites[1]->position.x < 600)
			{

				sprites[1]->position.x += shipVelocity;
			}
		}
		if (c == 'a')
		{
			if (sprites[1]->position.x > 000)
			{
				sprites[1]->position.x -= shipVelocity;
			}
		}
		if (c == ' ')
		{
			cout << "space" << endl;
			// Add new bullet sprite to the vector array
			cTexture t = cTexture("Images/bullet.png");
			cBullet* bullet = new cBullet();
			bullet->EnableCollisions = true;
			bullet->setTexture(t.getTexture());
			bullet->size = vec2(50, 50);
			bullet->position = sprites[1]->position + vec2(25, 0);
			bullet->rotation = 0;
			sprites.push_back(bullet);

			//play sound when fired
			mciSendString("stop pew", NULL, 0, 0);
			mciSendString("close pew", NULL, 0, 0);
			mciSendString("open Sounds/pew.wav alias pew", NULL, 0, 0);
			mciSendString("play pew", NULL, 0, 0);

		}
	}

// contrtols for left and right keys
void special(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT)
		
	{
		if (sprites[1]->position.x < 600)
		{
			sprites[1]->position.x += shipVelocity;
		}
	}

	if (key == GLUT_KEY_LEFT)
	{
		if (sprites[1]->position.x > 000)
		{

			sprites[1]->position.x -= shipVelocity;

		}
	}
}