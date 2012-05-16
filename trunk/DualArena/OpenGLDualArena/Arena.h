#include <glut.h>
#include <gl/GL.h>

void Display(void);
void Reshape(GLint width, GLint height);
void InitGraphics(void);
void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void IdleFunc(void);
void Keyboard(unsigned char key, int x, int y);
int main(int argc, char* argv[]);
