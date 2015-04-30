#include "game.h"

void Game::clearMain(bool** arr)
{
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(arr[i][j] != 0)
				arr[i][j] = 0;
}

void Game::checkCellGame(bool** arr1, bool** arr2, int r, int c, bool state)
{
	int count = 0;
	if(arr1[r-1][c] == 1) // сверху
		++count;
	if(arr1[r-1][c-1] == 1) // сверху слева
		++count;
	if(arr1[r][c-1] == 1) // слева
		++count;
	if(arr1[r+1][c-1] == 1) // снизу слева
		++count;
	if(arr1[r+1][c] == 1) // снизу
		++count;
	if(arr1[r+1][c+1] == 1) // снизу справа
		++count;
	if(arr1[r][c+1] == 1) // справа
		++count;
	if(arr1[r-1][c+1] == 1) // сверху справа
		++count;

	if(state == 0) // рождение
	{
		if(count == 3)
			arr2[r][c] = 1;
	}

	else if(state == 1) // смерть
	{
		if(count == 2 || count == 3)
			arr2[r][c] = 1;
	}
}

void Game::checkCellMy(bool** arr1, bool** arr2, int r, int c, bool state)
{
	int count = 0;
	if(arr1[r-1][c] == 1) // сверху
		++count;
	if(arr1[r][c-1] == 1) // слева
		++count;
	if(arr1[r+1][c] == 1) // снизу
		++count;
	if(arr1[r][c+1] == 1) // справа
		++count;

	if(state == 0) // рождение
	{
		if(count == 1)
			arr2[r][c] = 1;
	}

	else if(state == 1) // смерть
	{
		if(count == 4)
			arr2[r][c] = 1;
	}
}

void Game::makeBorn(bool** arr1, bool** arr2)
{
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(arr1[i][j] == 0 && i > 0 && j > 0 && i < size-1 && j < size-1)
			{
				if(gameType == 0) checkCellGame(arr1, arr2, i, j, 0);
				else checkCellMy(arr1, arr2, i, j, 0);
			}
}

void Game::makeDead(bool** arr1, bool** arr2)
{
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(arr1[i][j] == 1 && i > 0 && j > 0 && i < size-1 && j < size-1)
			{
				if(gameType == 0) checkCellGame(arr1, arr2, i, j, 1);
				else checkCellMy(arr1, arr2, i, j, 1);
			}
}

void Game::Move()
{
	static bool state = 0;

	if(state == 0)
	{
		makeBorn(field1, field2);
		makeDead(field1, field2);
		clearMain(field1);
//		printBuffer(field2);
		draw(field2);
	}
	else
	{
		makeBorn(field2, field1);
		makeDead(field2, field1);
		clearMain(field2);
//		printBuffer(field1);
		draw(field1);
	}

	state = !state;
}

void Game::clear()
{
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			field1[i][j] = field2[i][j] = 0;
}

void Game::printFields()
{
	cout << "field1:\n";
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			cout << field1[i][j] << " ";
		}cout << endl;
	}cout << endl;

	cout << "field2:\n";
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			cout << field2[i][j] << " ";
		}cout << endl;
	}cout << endl;
}

void Game::printBuffer(bool** arr)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			cout << arr[i][j] << " ";
		}cout << endl;
	}cout << endl;
}

void Game::draw(bool** arr)
{
	int Scale = 20;
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j++)
			{
				if(arr[i][j] == 1)
				{
					glVertex2i(j*Scale, i*Scale);
					glVertex2i(j*Scale, i*Scale+Scale-1);
					glVertex2i(j*Scale+Scale-1, i*Scale+Scale-1);
					glVertex2i(j*Scale+Scale-1, i*Scale);
				}
			}
		}
	glEnd();
}

void Game::draw()
{
	bool** arr = field1;
	int Scale = 20;
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j++)
			{
				if(arr[i][j] == 1)
				{
					glVertex2i(j*Scale, i*Scale);
					glVertex2i(j*Scale, i*Scale+Scale-1);
					glVertex2i(j*Scale+Scale-1, i*Scale+Scale-1);
					glVertex2i(j*Scale+Scale-1, i*Scale);
				}
			}
		}
	glEnd();
}

Game::Game()
{
	field1 = new bool*[size]; for(int i = 0; i < size; i++) field1[i] = new bool[size];
	field2 = new bool*[size]; for(int i = 0; i < size; i++) field2[i] = new bool[size];
}

Game::Game(int s)
{
	field1 = new bool*[size]; for(int i = 0; i < size; i++) field1[i] = new bool[size];
	field2 = new bool*[size]; for(int i = 0; i < size; i++) field2[i] = new bool[size];
	switch(s)
	{
		case LINE:
			initLine();
			break;
		case GLAIDER:
			initGlader();
			break;
		case TETRAMINO:
			initTetramino();
			break;
		case LETTER_S:
			initLetterS();
			break;
	}
}

Game::~Game()
{
	for(int i = 0; i < size; i++)
	{
		delete field1[i];
		delete field2[i];
	}
}

void Game::initLine()
{
	field1[3][3] = 1; field1[3][2] = 1; field1[3][4] = 1;
}

void Game::initGlader()
{
	field1[3][3] = 1; field1[4][4] = 1; field1[5][4] = 1; field1[5][3] = 1; field1[5][2] = 1;
}

void Game::initTetramino()
{
	int r = size/2, c = size/2;
	field1[r][c] = 1; field1[r][c-1] = 1; field1[r][c+1] = 1;
	field1[r-1][c] = 1;
}

void Game::initLetterS()
{
	int r = size/2, c = size/2;
	field1[r][c] = 1; field1[r-1][c] = 1; field1[r][c-1] = 1; field1[r-1][c+1] = 1;
}

void Game::initMyPoints(vector<pair<int,int> > v)
{
	for(size_t i = 0; i < v.size(); i++)
		field1[v[i].first][v[i].second] = 1;
}

void Game::initMyPoint(int r, int c)
{
	field1[r][c] = 1;
}
