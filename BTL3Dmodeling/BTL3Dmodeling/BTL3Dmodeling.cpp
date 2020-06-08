#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cmath>
#include <Windows.h>
#include <freeglut.h>
#include <SOIL.h>

#define PI 3.14159265
using namespace std;
struct Point
{
	Point() {
		i = 0; j = 0; z = 0;
	}

	Point(float _x, float _y, float _z)
	{
		i = _x; j = _y; z = _z;
	}

	float i, j, z;
};

float bike_dir = -90;
Point start_pos(-1.0, 0.0, 9.0);
Point bike_pos;
GLuint texture[6];
GLfloat cam_angle = -90, cam_radius = 25.0, cam_height = 25.0;
GLuint elephant;
void* font = GLUT_BITMAP_TIMES_ROMAN_24;

GLint loadTexture(char* filename, GLuint tex_2d) {
	tex_2d = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	return tex_2d;
}

void loadObj(char* fname)
{
	FILE* fp;
	int read;
	GLfloat x, y, z;
	char ch;
	elephant = glGenLists(1);
	fp = fopen(fname, "r");
	if (!fp)
	{
		printf("can't open file %s\n", fname);
		exit(1);
	}
	glPointSize(2.0);
	glNewList(elephant, GL_COMPILE);
	{
		glPushMatrix();
		glBegin(GL_POINTS);
		while (!(feof(fp)))
		{
			read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
			if (read == 4 && ch == 'v')
			{
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
	glPopMatrix();
	glEndList();
	fclose(fp);
}



void DrawCoordinate()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();

	glEnable(GL_LIGHTING);
}

void drawBike() {
	glPushMatrix();
	glTranslatef(bike_pos.i, bike_pos.j, bike_pos.z);
	glColor3f(1.0, 0, 0);
	glutSolidCube(0.5);
	glPopMatrix();
}

void renderBitmapString(
	float x,
	float y,
	float z,
	void* font,
	char* string) {
	char* c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}
void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void OnKeyUp(unsigned char ch, int x, int y)
{
	switch (ch)
	{
	case 'A':
		break;
	case 'a':
		break;
	default:
		break;
	}
}

void OnKeyDown(unsigned char ch, int x, int y)
{
	switch (ch)
	{
	case 'a':cam_angle += 1.0;
		break;
	case 'd':cam_angle -= 1.0;
		break;
	case 'w':cam_height += 1.0;
		break;
	case 's':cam_height -= 1.0;
		break;
	case 'e':bike_pos = start_pos;
		break;
	case 'q': {cam_angle = -90; cam_height = 25.0; }
			break;
	case 27:exit(0);
		break;
	default:
		break;
	}
}

void OnSpecialKeyDown(int key, int x, int y)
{
	//switch (key)
	//{
	//case GLUT_KEY_UP: bike_pos.z -= 0.1;
	//	break;
	//case GLUT_KEY_DOWN:bike_pos.z += 0.1;
	//	break;
	//case GLUT_KEY_LEFT:bike_pos.i -= 0.1;
	//	break;
	//case GLUT_KEY_RIGHT:bike_pos.i += 0.1;
	//	break;
	//default:
	//	break;
	//}
	switch (key)
	{
	case GLUT_KEY_UP: {bike_pos.z += sin(bike_dir * PI / 180) * 0.1; bike_pos.i -= cos(bike_dir * PI / 180) * 0.1; }
					break;
	case GLUT_KEY_DOWN: {bike_pos.z -= sin(bike_dir * PI / 180) * 0.1; bike_pos.i += cos(bike_dir * PI / 180) * 0.1; }
					  break;
	case GLUT_KEY_LEFT:bike_dir += 1;
		break;
	case GLUT_KEY_RIGHT:bike_dir -= 1;
		break;
	default:
		break;
	}
}

void OnSpecialKeyUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	default:
		break;
	}
}

void MouseButton(int type_button, int state, int x, int y)
{
	if (type_button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{

		}
		else
		{

		}
	}
	else if (type_button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_UP)
		{

		}
		else
		{
			//Todo
		}
	}
}

void mouseMove(int x, int y)
{

	//Todo

}

void RendenScene()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glLoadIdentity();
	gluLookAt((double)cos(cam_angle * PI / 180.0) * cam_radius, cam_height, (double)-sin(cam_angle * PI / 180.0) * cam_radius, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glDisable(GL_LIGHTING);
	glPushMatrix();
	DrawCoordinate();
	glPopMatrix();
	
	//setOrthographicProjection();
	glPushMatrix();
	char s[] = { "Arrow:Bike,WSAD:Camera,E:Restart,ESC:exit" };
	glColor3f(1.0, 0.0, 0.0);
	renderBitmapString(0.0f, 9.0f, -10.0f, (void*)font, s);
	glPopMatrix();
	//restorePerspectiveProjection();

	//Mo phong chuyen dong xe
	//glPushMatrix();
	//glDisable(GL_LIGHTING);
	//glColor3f(1.0, 0.0, 0.0);
	//drawBike();
	//glPopMatrix();

	glPushMatrix();
	glTranslatef(bike_pos.i, bike_pos.j, bike_pos.z);
	glRotatef(bike_dir, 0.0, 1.0, 0.0);
	glColor3f(1.0, 0.23, 0.27);
	glScalef(0.2, 0.2, 0.2);
	glCallList(elephant);
	glPopMatrix();
	//Mo phong moi truong
	// sa hinh
	glColor4f(0.5, 0.5, 0.5, 0.5);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	//textcoor -> image to element | vertex
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 0, 10);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 0, -10);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-9, 0, -10);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-9, 0, 10);
	glEnd();
	glPopMatrix();

	// concreate
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0.5, 0.5, 0.5);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-9, 0, 10);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-9, 0, -10);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-9, 2, -10);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-9, 2, 10);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10, 0, 10);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-10, 0, -10);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10, 2, -10);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10, 2, 10);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10, 0, -10);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-9, 0, -10);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-9, 2, -10);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10, 2, -10);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-10, 0, 10);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-9, 0, 10);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-9, 2, 10);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10, 2, 10);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-9, 2, 10);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-9, 2, -10);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10, 2, -10);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-10, 2, 10);

	// mat san building
	glTexCoord2f(1.0f, 1.0f); glVertex3f(10, 0, 10);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(10, 0, -10);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 0, -10);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 0, 10);

	glEnd();
	glPopMatrix();

	// building
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0.5, 0.5, 0.5);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2, 0, 5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2, 0, -5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2, 5, -5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2, 5, 5);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(6, 0, 5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(6, 0, -5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(6, 5, -5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(6, 5, 5);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(6, 0, -5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2, 0, -5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2, 5, -5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(6, 5, -5);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(6, 0, 5);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(2, 0, 5);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(2, 5, 5);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(6, 5, 5);

	// khoi tao rieng biet mat tren building nhu binh thuong
	glVertex3f(2, 5, -5);
	glVertex3f(2, 5, 5);
	glVertex3f(6, 5, 5);
	glVertex3f(6, 5, -5);

	glEnd();
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
}

void ReShape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	float ratio = (float)width / (float)height;
	gluPerspective(45.0, ratio, 1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}


void Init()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	char sh_filename[] = "texture/sa-hinh.jpg";
	char concrete_filename[] = "texture/concrete.jpg";
	char building_filename[] = "texture/building.jpg";
	texture[0] = loadTexture(sh_filename, texture[0]);
	texture[1] = loadTexture(concrete_filename, texture[1]);
	texture[2] = loadTexture(building_filename, texture[2]);
	// filter -> linear: slow but better quality
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// toa do texture ngoai bien -> repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLfloat light_pos[] = { 20.0, 20.0, 20.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	GLfloat ambient[] = { 1.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

	GLfloat diff_use[] = { 1.0, 0.5, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

	GLfloat shininess = 50.0f;
	glMateriali(GL_FRONT, GL_SHININESS, shininess);

	bike_pos = start_pos;

	char filename[] = "moto_simple_1.obj";
	loadObj(filename);
}

void Update() {
	Sleep(60);
	//cam_angle+=0.1;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1200, 700);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("Modeling3D");

	Init();
	glutDisplayFunc(RendenScene);
	glutReshapeFunc(ReShape);
	glutIdleFunc(Update);

	glutKeyboardFunc(OnKeyDown);
	//glutKeyboardUpFunc(OnKeyUp);
	glutSpecialFunc(OnSpecialKeyDown);
	//glutSpecialUpFunc(OnSpecialKeyUp);

	//glutMouseFunc(MouseButton);
	//glutMotionFunc(mouseMove);
	glutIgnoreKeyRepeat(0);

	glutMainLoop();
	return EXIT_SUCCESS;
}