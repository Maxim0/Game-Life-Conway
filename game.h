#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include <GL/glut.h>
using namespace std;

class Game
{
	bool** field1; // основной
	bool** field2; // за кадром
	int size = /*10*//*20*/30;

	void checkCellGame(bool** arr1, bool** arr2, int, int, bool);
	void checkCellMy(bool** arr1, bool** arr2, int, int, bool);

	void makeBorn(bool** arr1, bool** arr2);
	void makeDead(bool** arr1, bool** arr2);
	void clearMain(bool** arr);

	void printBuffer(bool** arr);

	void draw(bool** arr);
	void printFields();


public:
	bool gameType = 0;
	enum {LINE, GLAIDER, TETRAMINO, LETTER_S};

	Game();
	Game(int s);
	~Game();

	void Move();
	void draw();

	int getSize(){return size;}
	void clear();

	void initLine();
	void initGlader();
	void initTetramino();
	void initLetterS();
	void initMyPoints(vector<pair<int,int> >);
	void initMyPoint(int r, int c);
};

#endif // GAME_H
