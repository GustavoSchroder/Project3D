
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;

int cont = 0;
int r, g, b;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void drawRect(float x, float y, float weight, float height, int r, int g, int b) {
	glColor3ub(r, g, b);
	glBegin(GL_QUADS);
	glVertex2f(x + weight, y - height);
	glVertex2f(x + 2 + weight, y - height);
	glVertex2f(x + 2 + weight, y - 2 - height);
	glVertex2f(x + weight, y - 2 - height);
	glEnd();
}

void display(void)
{		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Reset transformations
		glLoadIdentity();
		// Set the camera
		gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);

		/* Draw ground
		glColor3f(0.9f, 0.9f, 0.9f);
		glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, 100.0f);
		glVertex3f(100.0f, 0.0f, -100.0f);
		glEnd();*/

		// Draw 4 rectangles
		float xx = 2;  //x inicial da tela
		float yy = 2; // y inicial da tela
		if (cont == 0) {
			r = 255;
			g = 255;
			b = 255;
		}
		else if (cont == 1) {
			r = 155;
			g = 155;
			b = 155;
		}
		else if (cont == 2) {
			r = 255;
			g = 0;
			b = 0;
		}
		else {
			r = 0;
			g = 255;
			b = 0;
		}
		for (int i = 0; i < 3; i++)
			for (int j = -3; j < 3; j++) {
				glPushMatrix();
				glTranslatef(i*10.0, 0, j * 10.0);
				drawRect(-34, 34, xx, yy, r, g, b);
				glPopMatrix();
				xx += 2;
				cont++;
			}
		yy += 2;

		glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int xx, int yy)
{
	float fraction = 0.1f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}