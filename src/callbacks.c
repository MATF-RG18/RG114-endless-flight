#include "include/callbacks.h"


void on_display(void)
{
  /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
  GLfloat light_position[] = { 1, 1, 1, 0 };

  /* Ambijentalna boja svetla. */
  GLfloat light_ambient[] = { 0.9, 0.9, 0.9, 1 };

  /* Difuzna boja svetla. */
  GLfloat light_diffuse[] = { 0, 0, 0, 1 };

  /* Spekularna boja svetla. */
  GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

  /* Koeficijenti ambijentalne refleksije materijala. */
  GLfloat ambient_coeffs[] = { 1.0, 0.5, 0.1, 1 };

  /* Koeficijenti difuzne refleksije materijala. */
  GLfloat diffuse_coeffs[] = { 0.0, 0.0, 0.8, 1 };

  /* Koeficijenti spekularne refleksije materijala. */
  GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

  /* Koeficijent glatkosti materijala. */
  GLfloat shininess = 10;

  /* Brise se prethodni sadrzaj prozora. */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* Podesava se vidna tacka. */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(3.0, 6.0, 1.0, 3.0, 0.0, -5.0, 0.0, 1.0, 0.0);

  /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  /* Podesavaju se parametri materijala. */
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);

  /* Kreira se objekat. */
  // TODO 
  // Create paper plane function
  glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(player_x, 0, 0);
    glutSolidSphere(0.8, 40, 40);
  glPopMatrix();

  glLineWidth(10);
  glBegin(GL_LINES);
    glVertex3f(0, 0, 10);
    glVertex3f(0, 0, -100);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(6, 0, 10);
  glVertex3f(6, 0, -100);
  glEnd();


  glShadeModel(GL_SMOOTH);

  /* Nova slika se salje na ekran. */
  glutSwapBuffers();
}

void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluPerspective(80, (float) width / height, 1, 40);
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.0, 40.0);
    glMatrixMode (GL_MODELVIEW);
}

void on_keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      /* Zavrsava se program. */
      exit(0);
      break;

    case 'a':
    case 'A':
    if(player_x > 1)
        player_x -= 2.0;
      glutPostRedisplay();
    break;

    case 'd':
    case 'D':
      if(player_x < 5)
        player_x += 2.0;  
      glutPostRedisplay();
    break;

    case 'w':
    case 'W':
      if(player_z > -2)
        player_z -= 2.0;  
      glutPostRedisplay();
    break;

    case 's':
    case 'S':
      if(player_z < 0)
        player_z += 2.0;  
      glutPostRedisplay();
    break;

    case 'n':
    case 'N':
      if(!animation_active){
        glutTimerFunc(50, on_timer, 0);
        animation_active = 1;
      }

      {
        int i, run = 1;
        for (i = 0; run && (i < MAX_OBSTACLES); i++)
          if (obstacles_x[i] < 0) {
            obstacles_z[i] = 0;
            obstacles_x[i] = cos(animation_parameter / 10.0f);
            run = 0;
        }
        }
  }
}

void on_timer(int value){
  if(value != 0)
    return;

  animation_parameter++;

  glutPostRedisplay();

  //TODO 
  //Pomeranje prepreka

  //Po potrebi se ponovo postavlja timer
  if(animation_active)
    glutTimerFunc(50, on_timer, 0);
}