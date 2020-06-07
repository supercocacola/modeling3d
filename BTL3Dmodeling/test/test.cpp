#include <gl\glut.h>

float g_x = 0.0f;
float g_z = 30.0f;


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
    case 'A':
        break;
    case 'a':
        break;
    default:
        break;
    }
}

void OnSpecialKeyDown(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        g_z -= 0.2;
        break;
    case GLUT_KEY_DOWN:
        g_z += 0.2;
        break;
    case GLUT_KEY_LEFT:
        g_x -= 0.2;
        break;
    case GLUT_KEY_RIGHT:
        g_x += 0.2;
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

void ReShape(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ratio = 0.0;
    if (width > height)
        ratio = (float)width / height;
    else
        ratio = (float)height / width;

    gluPerspective(45.0, ratio, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);

}

void DrawCoordinate()
{
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-100.0, 0.0, 0.0);
    glVertex3f(100.0, 0.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -100.0, 0.0);
    glVertex3f(0.0, 100.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -100.0);
    glVertex3f(0.0, 0.0, 100.0);
    glEnd();

    glEnable(GL_LIGHTING);
}

void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(g_x, 1.0f, g_z,
        0.0, 0.0f, 0.0,
        0.0f, 1.0f, 0.0f);

    DrawCoordinate();
    glPushMatrix();
    glutSolidTeapot(10.0);
    glPopMatrix();

    glFlush();
    glutPostRedisplay();
}


void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = { 0.0, 0.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

    GLfloat diff_use[] = { 0.1, 0.2, 0.3, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff_use);

    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

    GLfloat shininess = 50.0f;
    glMateriali(GL_FRONT, GL_SHININESS, shininess);

}

void main()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Opengl Study");

    Init();
    glutReshapeFunc(ReShape);
    glutDisplayFunc(RenderScene);
    glutIdleFunc(RenderScene);
    glutKeyboardFunc(OnKeyDown);
    glutKeyboardUpFunc(OnKeyUp);
    glutSpecialFunc(OnSpecialKeyDown);
    glutSpecialUpFunc(OnSpecialKeyUp);

    // here are the new entries
    //glutIgnoreKeyRepeat(1);

    glutMainLoop();

    return;
}