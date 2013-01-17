/*
This program is based on http://www.videotutorialsrock.com - an awsome page.

During my first year of studies one of our professors told us:

"There's no reason for you to write something that was already written, because it was written way better
than you will be able to write it"

Coords are mine :)
*/

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include "imageloader.h"

using namespace std;

GLfloat _angle = 0.0;

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			exit(0);
	}
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}
GLuint _textureId;

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	Image* image = loadBMP("Pyramid.bmp");
	_textureId = loadTexture(image);
	delete image;
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(0.0, (double)w / (double)h, 1.0, 200.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, -0.3f, 0.0f);

	// Light - no idea what I'm doing :(

	// Ambient light
	GLfloat ambientColor[] = {0.6f, 0.6f, 0.6f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	// Positioned light
	GLfloat lightColor0[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	// Directed light
	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f};
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	// OK, it's different, so I guess it works

	// Enabling textures - halfway there
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glColor3f(0.2f, 0.0f, 0.0f);

	// This I understand
	glScalef(0.7f, 0.7f, 0.7f);
	glRotatef(_angle, 0.0f, 1.0f, 0.0f);
	
	// I can see bottom of the pyramid - it's there!
//	glRotatef(-15.0, 1.0, 0.0, 0.0);
	

	// No way I can draw it again

	// I don't know how I did this, but after trial-error I managed to put texture on that thing
	// Now I'm happy, and it's only 9pm :)
	glBegin(GL_QUADS);
//		glColor3f(1.0f, 1.0f, 1.0f);

		glVertex3f(-0.5f, 0.0f, 0.5f);
		glVertex3f(0.5f, 0.0f, 0.5f);
		glVertex3f(0.5f, 0.0f, -0.5f);
		glVertex3f(-0.5f, 0.0f, -0.5f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 0.5f);
//		glColor3f(1.0f, 1.0f, 0.0f);
		
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, 0.0f, 0.5f);
		
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.5f);
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 0.5f);
//		glColor3f(1.0f, 1.0f, 0.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.5f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, -0.5f);
		
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 0.5f);
//		glColor3f(1.0f, 1.0f, 0.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, -0.5f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, 0.0f, -0.5f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, 0.5f);
//		glColor3f(1.0f, 1.0f, 0.0f);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, 0.0f, -0.5f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5, 0.0, 0.5);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glutSwapBuffers();
}

void update(int value) {
	_angle += 2.0f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	glutCreateWindow("Pyramid");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0);
	glutMainLoop();
	
	return 0;
}