#pragma once
#include "GL\glut.h"
#include "Pacman.h"
class Ghost {

private:

public:
	// general ghost info:
	int index;
	bool frightened;
	bool chase;
	bool scatter;
	float x, y, z;  // wspolrzedne do poruszania sie po planszy
	int tileX;
	int tileY;
	int lives;
	double angle;
	double speed;
	bool moving;
	Ghost(float r, float g, float b, int x, int y, float z);
	bool atCenter; // synchronizing boolean. Invoke onTileCenter only once!


				   // scattering functionality:
	int scatterTileX;
	int scatterTileY;

	// targeting functionality:
	int targetTileX;
	int targetTileY;

	//  visual appearance:
	float r;
	float g;
	float b;
	void Draw(); // unique ghost look



	void Move(Pacman *pacman);

	void Pad();

	void PadToCenter();



};
