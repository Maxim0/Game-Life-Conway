#include "game.h"

Game g;
int sz = g.getSize();

int Scale = 20;

int w = sz*Scale;
int h = sz*Scale;

bool canStart = 1;
bool state = 0;

void drawField()
{
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
		for(int i = 0; i < w; i += Scale)
		{
			glVertex2i(i, 0); glVertex2i(i, h);
			glVertex2i(0, i); glVertex2i(h, i);
		}
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawField();
	if(canStart == 1)
	{
		g.Move();
	}
	else
	{
		g.draw();
	}

	glutSwapBuffers();
}

void timer(int)
{
	display();
	glutTimerFunc(70, timer, 0);
}

void MousePresses(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(canStart == 0)
		{
			g.initMyPoint(y/Scale, x/Scale);
//			g.printBuffer(g.field1);
		}
	}
}

void MenuCheck(int v)
{
	switch (v)
	{
		case 0:
			g.gameType = 0;
			break;
		case 1:
			g.gameType = 1;
			break;
		case 2:
			g.clear();
			state = 0;
			break;
	}
}

void SubMenuCheck(int v)
{
	if(state == 0)
	{
		switch(v)
		{
			case 0:
				g.initLine();
				break;
			case 1:
				g.initGlader();
				break;
			case 2:
				g.initTetramino();
				break;
			case 3:
				g.initLetterS();
				break;
		}
		state = 1;
	}
}

void ResearchMenu(int v)
{
	if(state == 0)
	{
		switch (v)
		{
			case 0:
				canStart = 0;
				break;
			case 1:
				canStart = 1;
				state = 1;
				break;
		}
	}
}

void MenuInit()
{
	int Main = glutCreateMenu(MenuCheck); // создали меню
	int exist = glutCreateMenu(SubMenuCheck); // создали субменю
	int research = glutCreateMenu(ResearchMenu);

	glutSetMenu(exist); // сообщаем, что именно это меню мы будем редактировать
	glutAddMenuEntry("Line", 0);
	glutAddMenuEntry("Glader", 1);
	glutAddMenuEntry("Tetramino", 2);
	glutAddMenuEntry("Letter S", 3);

	glutSetMenu(research);
	glutAddMenuEntry("Mark cells", 0);
	glutAddMenuEntry("Start game!", 1);

	glutSetMenu(Main);
	glutAddSubMenu("Research existing elements", exist);
	glutAddSubMenu("Make your own game", research);
	glutAddMenuEntry("Usual game", 0);
	glutAddMenuEntry("Other game", 1);
	glutAddMenuEntry("End the game", 2);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(w, h);
	glutCreateWindow("game");

	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutDisplayFunc(display);
	MenuInit();
	glutTimerFunc(700, timer, 0);
	glutMouseFunc(MousePresses);

	glutMainLoop();
}
