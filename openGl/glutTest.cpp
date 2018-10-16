#include <GL/glut.h>
#include <iostream>



void display(void){
  glClear(GL_COLOR_BUFFER_BIT);


  glColor3f(1.0,0.0,0.0);

  glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0.25,0.25,0.0);
    glVertex3f(0.75,0.25,0.0);
    glVertex3f(0.75,0.75,0.0);
    glVertex3f(0.25,0.75,0.0);

  glEnd();


  /*glBegin(GL_POLYGON);
    glVertex3f(0.25,0.25,0.0);
    glVertex3f(0.0,0.5,0.0);
    glVertex3f(1,1,0.25);


  glEnd();*/


  glFlush();
}


void init (void){
  glClearColor(0.0,0.0,0.0,0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);

}

int main(int argc, char** argv){

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowSize(600,400);
  glutInitWindowPosition(100,100);
  glutCreateWindow("hello");
  init();
  glutDisplayFunc(display);
  glutMainLoop();




  return 0;
}
