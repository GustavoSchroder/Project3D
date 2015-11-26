#include <Windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

float angulo = 0.0f;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 5.0f;



void drawImage() { // desenha o objeto 3d
	glColor3f(0.5, 0.7, 0.9);
	glBegin(GL_POLYGON);
	glVertex3f(1, -0.5, 1);
	glVertex3f(1, -0.5, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glEnd();
}

void drawFloor() { // desenha o chao em tres cores

	glColor3f(0, 0, 1);

	glBegin(GL_POLYGON);
	glVertex3f(-5, -0.5, -5);
	glVertex3f(-5, -0.5, 0);
	glVertex3f(0, -0.5, 0);
	glVertex3f(0, -0.5, -5);
	glEnd();

	glColor3f(1, 0, 0);

	glBegin(GL_POLYGON);
	glVertex3f(-5, -0.5, 0);
	glVertex3f(0, -0.5, 0);
	glVertex3f(0, -0.5, 5);
	glVertex3f(-5, -0.5, 5);
	glEnd();

	glColor3f(0, 1, 0);

	glBegin(GL_POLYGON);
	glVertex3f(0, -0.5, -5);
	glVertex3f(5, -0.5, -5);
	glVertex3f(5, -0.5, 0);
	glVertex3f(0, -0.5, 0);
	glEnd();

	glColor3f(1, 1, 0);

	glBegin(GL_POLYGON);
	glVertex3f(0, -0.5, 0);
	glVertex3f(5, -0.5, 0);
	glVertex3f(5, -0.5, 5);
	glVertex3f(0, -0.5, 5);
	glEnd();	

}

void processSpecialKeys(int key, int xx, int yy) {
	//http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard/

	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angulo -= 0.02f;
		lx = sin(angulo);
		lz = -cos(angulo);
		break;
	case GLUT_KEY_RIGHT:
		angulo += 0.02f;
		lx = sin(angulo);
		lz = -cos(angulo);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}

void renderScene(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);

	drawFloor();
	drawImage();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("hello");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(reshape);
	glutSpecialFunc(processSpecialKeys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 0;   /* ISO C requires main to return int. */
}
