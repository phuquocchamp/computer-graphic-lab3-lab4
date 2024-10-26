#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

float theta = 0.0f;
float phi = 0.0f;
float zoom = 1.0f;
bool wireframeMode = true; // Chế độ khung dây mặc định

void translate(float tx, float ty, float tz)
{
    glTranslatef(tx, ty, tz);
}

void scale(float sx, float sy, float sz, float x0, float y0, float z0)
{
    glTranslatef(x0, y0, z0);
    glScalef(sx, sy, sz);
    glTranslatef(-x0, -y0, -z0);
}

void rotate(float angle, float x, float y, float z)
{
    glRotatef(angle, x, y, z);
}

void mirrorXY() { glScalef(1.0f, 1.0f, -1.0f); }
void mirrorYZ() { glScalef(-1.0f, 1.0f, 1.0f); }
void mirrorXZ() { glScalef(1.0f, -1.0f, 1.0f); }

void setProjection(bool perspective)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (perspective)
    {
        gluPerspective(60.0, 1.0, 1.0, 100.0);
    }
    else
    {
        glOrtho(-2.0, 2.0, -2.0, 2.0, 1.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(5.0 * sin(theta) * cos(phi), 5.0 * sin(phi), 5.0 * cos(theta) * cos(phi),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Áp dụng các phép biến đổi tại đây
    translate(1.0, 0.0, 0.0);
    scale(zoom, zoom, zoom, 0.0, 0.0, 0.0);
    rotate(45, 0.0, 1.0, 0.0);

    // Vẽ vật thể 3D
    if (wireframeMode)
    {
        glutWireTeapot(0.5);
    }
    else
    {
        glutSolidTeapot(0.5);
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        phi += 0.1f;
        break;
    case 's':
        phi -= 0.1f;
        break;
    case 'a':
        theta -= 0.1f;
        break;
    case 'd':
        theta += 0.1f;
        break;
    case '+':
        zoom += 0.1f;
        break;
    case '-':
        zoom -= 0.1f;
        break;
    case '1': // Đối xứng qua mặt phẳng XOY
        mirrorXY();
        break;
    case '2': // Đối xứng qua mặt phẳng YOZ
        mirrorYZ();
        break;
    case '3': // Đối xứng qua mặt phẳng XOZ
        mirrorXZ();
        break;
    case 'm': // Chuyển đổi giữa mô hình khung dây và mặt đầy đủ
        wireframeMode = !wireframeMode;
        break;
    case 27: // ESC để thoát
        exit(0);
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Transformations");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    setProjection(true); // Đặt phép chiếu phối cảnh
    glutMainLoop();
    return 0;
}
