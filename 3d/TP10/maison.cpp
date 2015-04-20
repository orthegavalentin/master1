///////////////////////////////////////////////////////////////////////////////
// IUT de Provence, site d'Arles                                      2003-2004
// Département Informatique
// 2ème année
// ----------------------------------------------------------------------------
// IN - Synthèse d'images - Rendu réaliste
// Auteur : Sébastien Thon
// ----------------------------------------------------------------------------
// Base du TP 1
// Base d'un programme permettant d'afficher une scène composée d'un sol, de
// maisons et d'arbres. On placera des sources de lumière, on spécifiera les
// matériaux des différents objets et on utilisera un effet de brouillard.
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include "glut.h"
#include <GL/glut.h> 
#include <iostream>
#include <vector>
#define WIDTH   640										// Largeur de la fenêtre OpenGL
#define HEIGHT  480										// Hauteur de la fenêtre OpenGl

#define KEY_ESC 27

										// Code ASCII de la touche Echap

#define MAISON  1										// Code identificant la display list de la maison
#define ARBRE   2										// Code identificant la display list de l'arbre

float	xpos = 0, zpos = -50;							// Position de la caméra
int		angle_x = 0, angle_y = 0;						// Orientation de la caméra
int		mouse_x = 0, mouse_y = 0;						// Position de la souris

int xLight = 0;
int yLight = 3;
int zLight = 0;

//*****************************************************************
//* A FAIRE :
//* Déclarer des tableaux contenant les caractéristiques (Ambient,
//* diffus, spéculaire) pour différents matériaux :
//*    - sol
//*    - mur de maison
//*    - toit de maison
//*    - tronc d'arbre
//*    - feuillage d'arbre
//* Ex:
//*   GLfloat MatAmbient_sol[] = {0.0f, 0.5f, 0.0f, 1.0f};
//*   GLfloat MatDiffuse_sol[] = {0.0f, 0.7f, 0.0f, 1.0f};
//*   GLfloat MatSpecular_sol[]= {0.1f, 0.1f, 0.1f, 1.0f};
//*   GLfloat MatShininess_sol[1]={5.0f};
//*****************************************************************



///////////////////////////////////////////////////////////////////////////////
// Intitialisation de certains paramètres d'OpenGL.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid initGL() {
  glClearColor(0, 0, 0, 1);							// Couleur servant à effacer la fenêtre (noir)
  glShadeModel(GL_SMOOTH);							// Modèle d'ombrage : lissage de Gouraud
  glEnable(GL_CULL_FACE);								// Ne traite pas les faces cachées
  glEnable(GL_DEPTH_TEST);							// Active le Z-Buffer
  glDepthFunc(GL_LEQUAL);								// Mode de fonctionnement du Z-Buffer
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Active la correction de perspective (pour ombrage, texture, ...)
		
  GLfloat Light0Dif[4] = {1.0f, 0.37f, 0.0f, 1.0f};
  GLfloat Light0Spec[4] = {1.0f, 0.37f, 0.0f, 1.0f};
  GLfloat Light0Amb[4] = {0.5f, 0.5f, 0.5f, 1.0f};

  glLightfv(GL_LIGHT0,GL_DIFFUSE, Light0Dif);
  glLightfv(GL_LIGHT0,GL_SPECULAR, Light0Spec);
  glLightfv(GL_LIGHT0,GL_AMBIENT, Light0Amb);
  // GLint direction[] = {0,10,10,1};

  // glLightiv(GL_LIGHT0, GL_POSITION, direction);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

	//*****************************************************************
	//* A FAIRE :
	//*
	//* 1. Créer la source de lumière 0 (GL_LIGHT0) en tant que source de
	//*    lumière directionnelle, en précisant :
	//*      - sa position
	//*      - sa couleur ambiante
	//*      - sa couleur diffuse
	//*      - sa couleur spéculaire
	//*
	//* 2. Activer la source de lumière 0.
	//*
	//* 3. Activer l'éclairage général
	//*****************************************************************
}



///////////////////////////////////////////////////////////////////////////////
// Affiche le sol de la scène.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_sol()
{
	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du matériau
	//* crée pour le sol.
	//*****************************************************************
	// glColor3f(0.0f,0.8f,0.0f);	

  // glutSolidTeapot(2);

						// Couleur courante : vert
  float greenDiff[4] = {0, 1, 0, 1};
  float greenSpec[4] = {0, 1, 0, 1};
  float greenAmb[4] = {0, 1, 0, 1};
  glMaterialfv(GL_FRONT, GL_DIFFUSE, greenDiff);
  glMaterialfv(GL_FRONT, GL_SPECULAR, greenSpec);
  glMaterialfv(GL_FRONT, GL_AMBIENT, greenAmb);
  glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
  glNormal3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);									// Affichage d'un quadrilatère
  glVertex3d(-20, 0, -20);
  glVertex3d(-20, 0,  20);
  glVertex3d( 20, 0,  20);
  glVertex3d( 20, 0, -20);
  glEnd();

   glPushMatrix();
  glTranslatef(-10,3,-10);
  glColor3ub(0,255,255);
  glutSolidTeapot(2);
  glPopMatrix();
    
  glPushMatrix();
  glTranslatef(10,3,-10);
  glColor3ub(0,255,255);
  glutSolidTeapot(2);
  glPopMatrix();
  
  float brown[4] = {0.4f, 0.2f, 0.2f, 1};
  glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
  glMaterialfv(GL_FRONT, GL_SPECULAR, brown);
  glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
  glMaterialf(GL_FRONT, GL_SHININESS, 10.0);

  glPushMatrix();
  glTranslatef(-10,0,-10);
  glColor3ub(0,255,255);
  glRotatef(-90, 1.0f, 0, 0);
  glutSolidCone(1, 2, 10, 10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(10,0,-10);
  glColor3ub(0,255,255);
  glRotatef(-90, 1.0f, 0, 0);
  glutSolidCone(1, 2, 10, 10);
  glPopMatrix();

}



///////////////////////////////////////////////////////////////////////////////
// he une maison.
//-----------------------------------------------------------------------------
// Paramètres :
//    xp,yp,zp (in) : position de la maison.
//    yr       (in) : angle de rotation (en degrés) de la maison p/r à l'axe y.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_maison( float xp, float yp, float zp, float yr )
{
	glPushMatrix();										// Sauve la matrice de vue actuelle
	glTranslatef(xp, yp, zp);							// Positionne la maison avec une translation
	glRotatef(yr, 0,1,0);								// et une rotation
	glCallList(MAISON);									// Appelle la display list de la maison
	glPopMatrix();										// Restaure la matrice de vue
}



///////////////////////////////////////////////////////////////////////////////
// Affiche un arbre.
//-----------------------------------------------------------------------------
// Paramètres :
//    xp,yp,zp (in) : position de l'arbre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_arbre( float xp, float yp, float zp )
{
	//*****************************************************************
	//* A FAIRE :
	//* Afficher un arbre en faisant appel à sa display list.
	//*****************************************************************
}



///////////////////////////////////////////////////////////////////////////////
// Affiche les différents objets de la scène.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_scene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	affiche_sol();

	glPushMatrix();
	glTranslatef(xLight,yLight,zLight);
	glColor3ub(0,255,255);
	// glRotatef(-90, 1.0f, 0, 0);
	// glutSolidCone(1, 2, 10, 10);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	//*****************************************************************
	//* A FAIRE :
	//* Afficher quelques maisons et quelques arbres.
	//*****************************************************************
	affiche_maison( 0, 0, 0, 0 );
	affiche_maison( 10, 0, 10, 10 );
	

	glutSwapBuffers();							// Affiche la scène (affichage en double buffer)
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : affichage dans la fenêtre.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_display()
{
	// On efface les pixels de l'image (color buffer) et le Z-Buffer (depth buffer).
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// On initialise la matrice de vue avec la matrice identité.
	glLoadIdentity();

	// On applique une translation et une rotation à la scène pour simuler
	// un déplacement de caméra.
	glTranslatef(xpos,0,zpos);
	glRotatef(angle_x, 1,0,0);
	glRotatef(angle_y, 0,1,0);

	//*****************************************************************
	//* A FAIRE :
	//* Re-spécifier la position des sources de lumière avec
	//* glLightfv() pour qu'elles soient aussi affectées par la
	//* translation et la rotation qu'on vient d'appliquer à la scène.
	//*****************************************************************

	// On affiche la scène.
	affiche_scene();

	// On force OpenGL à afficher avant de passer à la suite.
	glFlush();
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : redimensionnement de la fenêtre.
//-----------------------------------------------------------------------------
// Paramètres :
//    width, height (in) : nouvelles largeur et hauteur de la fenêtre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des événements clavier.
//-----------------------------------------------------------------------------
// Paramètres :
//    key (in) : code ascii de la touche utilisée.
//    x,y (in) : coordonnées de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_keyboard(unsigned char key, int x, int y)
{
  std::cout << key << std::endl;
  switch (key)
    {
    case KEY_ESC:						// 'ECHAP' :
      exit(1);						// on quitte le programme
      break;
    }

}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des touches speciales du clavier.
//-----------------------------------------------------------------------------
// Paramètres :
//    key (in) : code ascii de la touche utilisée.
//    x,y (in) : coordonnées de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_special(int key, int x, int y)
{
  float speed = 1.0f;						// Vitesse de déplacement de la caméra

  switch (key)
    {
    case GLUT_KEY_UP:
      xLight++;
      // Flèche vers le haut : 
      // zpos += speed;					// on déplace la caméra selon z-
      // glutPostRedisplay();			// et on demande le réaffichage.
      break;

    case GLUT_KEY_DOWN:					// Flèche vers le bas :
      xLight--;
      // zpos -= speed;					// on déplace la caméra selon z+
      // glutPostRedisplay();			
      // et on demande le réaffichage.
      break;

    case GLUT_KEY_LEFT:					// Flèche vers la gauche :
      zLight--;
      // xpos += speed;					// on déplace la caméra selon x-
      // glutPostRedisplay();	
      // et on demande le réaffichage.
      break;

    case GLUT_KEY_RIGHT:				// Flèche vers la droite :
      zLight++;
      // xpos -= speed;					// on déplace la caméra selon x+
      // glutPostRedisplay();			// et on demande le réaffichage.
      break;
    }

  GLint direction[] = {xLight,yLight,zLight,1};
  glLightiv(GL_LIGHT0, GL_POSITION, direction);

  affiche_scene();
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion de clics souris.
//-----------------------------------------------------------------------------
// Paramètres :
//    button (in) : code du bouton utilisé.
//    state  (in) : état du bouton.
//    x,y    (in) : coordonnées de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse_x = x;
		mouse_y = y;
	}
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des déplacements de la souris.
//-----------------------------------------------------------------------------
// Paramètres :
//    x,y    (in) : coordonnées de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_motion(int x, int y)
{
	angle_x += y - mouse_y;						// Modifie la direction de vue de la caméra
	angle_y += x - mouse_x;						// en fonction de la position de la souris
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();						// Demande le réaffichage
}



///////////////////////////////////////////////////////////////////////////////
// Construit une maison dans une display-list.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////

void construit_maison()
{
	glNewList(MAISON, GL_COMPILE);

	// //*****************************************************************
	// //* A FAIRE :
	// //* Remplacer le glColor3f() suivant par l'utilisation du matériau
	// //* crée pour les murs (glMaterialfv()).
	// //*****************************************************************
	// 	// glColor3f(1.0f,1.0f,1.0f);			// Couleur courante : blanc
	// // GLfloat matspec[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	// // glMaterialfv(GL_FRONT, GL_SPECULAR, matspec);
	// // float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
	// // float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
	// // float colorBlue[4]       = { 0.0, 0.2, 1.0, 1.0 };
	// // float colorNone[4]       = { 0.0, 0.0, 0.0, 0.0 };
	
	float whiteDiff[4] = {1, 1, 1, 1};
	float whiteSpec[4] = {1, 1, 1, 1};
	float whiteAmb[4] = {1, 1, 1, 1};

	float redDiff[4] = {1, 0, 0, 1};
	float redSpec[4] = {1, 0, 0, 1};
	float redAmb[4] = {1, 0, 0, 1};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpec);
	glMaterialfv(GL_FRONT, GL_AMBIENT, whiteAmb);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);

	  // Mur de face
	  glNormal3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3d(-4, 0, 5);
	glVertex3d( 4, 0, 5);
	glVertex3d( 4, 5, 5);
	glVertex3d(-4, 5, 5);
	glEnd();

	// Mur arrière

	glNormal3f(0.0f, 0.0f, -1.0f);
	glBegin(GL_QUADS);
	glVertex3d(-4, 0, -5);
	glVertex3d(-4, 5, -5);
	glVertex3d( 4, 5, -5);
	glVertex3d( 4, 0, -5);
	glEnd();

	// Mur gauche

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3d(-4, 0, -5);
	glVertex3d(-4, 0,  5);
	glVertex3d(-4, 5,  5);
	glVertex3d(-4, 5, -5);
	glEnd();

	// Mur droit
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3d(4, 0, -5);
	glVertex3d(4, 5, -5);
	glVertex3d(4, 5,  5);
	glVertex3d(4, 0,  5);
	glEnd();

	// Triangle avant
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3d(-4, 5, 5);
	glVertex3d( 4, 5, 5);
	glVertex3d( 0, 8, 5);
	glEnd();

	// Triangle arrière
	
	glNormal3f(0.0f, 0.0f, -1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3d( 4, 5, -5);
	glVertex3d(-4, 5, -5);
	glVertex3d( 0, 8, -5);
	glEnd();

	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du matériau
	//* crée pour le toit (glMaterialfv()).
	//*****************************************************************
	// glColor3f(1.0f,0.0f,0.0f);			// Couleur courante : rouge

	// Toit versant droit

	glMaterialfv(GL_FRONT, GL_DIFFUSE, redDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, redSpec);
	glMaterialfv(GL_FRONT, GL_AMBIENT, redAmb);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);

	glNormal3f(0.6f, 0.8f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3d(0, 8,  5);
	glVertex3d(4, 5,  5);
	glVertex3d(4, 5, -5);
	glVertex3d(0, 8, -5);
	glEnd();

	// Toit versant gauche

	glNormal3f(-0.6f, 0.8f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3d( 0, 8,  5);
	glVertex3d( 0, 8, -5);
	glVertex3d(-4, 5, -5);
	glVertex3d(-4, 5,  5);
	glEnd();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpec);
	glMaterialfv(GL_FRONT, GL_AMBIENT, whiteAmb);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);

	  // Mur de face
	glNormal3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3d(-16, 0, 5);
	glVertex3d( -8, 0, 5);
	glVertex3d( -8, 5, 5);
	glVertex3d(-16, 5, 5);
	glEnd();

	// Mur arrière

	glNormal3f(0.0f, 0.0f, -1.0f);
	glBegin(GL_QUADS);
	glVertex3d(-16, 0, -5);
	glVertex3d(-16, 5, -5);
	glVertex3d( -8, 5, -5);
	glVertex3d( -8, 0, -5);
	glEnd();

	// Mur gauche

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3d(-16, 0, -5);
	glVertex3d(-16, 0,  5);
	glVertex3d(-16, 5,  5);
	glVertex3d(-16, 5, -5);
	glEnd();

	// Mur droit
	
	glNormal3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3d(-8, 0, -5);
	glVertex3d(-8, 5, -5);
	glVertex3d(-8, 5,  5);
	glVertex3d(-8, 0,  5);
	glEnd();

	// Triangle avant
	
	glNormal3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3d(-16, 5, 5);
	glVertex3d( 4, 5, 5);
	glVertex3d( 0, 8, 5);
	glEnd();

	// Triangle arrière
	
	glNormal3f(0.0f, 0.0f, -1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3d( 4, 5, -5);
	glVertex3d(-16, 5, -5);
	glVertex3d( 0, 8, -5);
	glEnd();

	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du matériau
	//* crée pour le toit (glMaterialfv()).
	//*****************************************************************
	// glColor3f(1.0f,0.0f,0.0f);			// Couleur courante : rouge

	// Toit versant droit

	glMaterialfv(GL_FRONT, GL_DIFFUSE, redDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, redSpec);
	glMaterialfv(GL_FRONT, GL_AMBIENT, redAmb);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);

	glNormal3f(0.6f, 0.8f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3d(0, 8,  5);
	glVertex3d(-8, 5,  5);
	glVertex3d(-8, 5, -5);
	glVertex3d(0, 8, -5);
	glEnd();

	// Toit versant gauche

	glNormal3f(-0.6f, 0.8f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3d( 0, 8,  5);
	glVertex3d( 0, 8, -5);
	glVertex3d(-16, 5, -5);
	glVertex3d(-16, 5,  5);
	glEnd();

	glEndList();
}



///////////////////////////////////////////////////////////////////////////////
// Construit un arbre dans une display-list.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void construit_arbre()
{
	//*****************************************************************
	//* A FAIRE :
	//* Créer dans une display list un arbre dont le tronc sera un cône :
	//*     glutSolidCone()
	//* et le feuillage une sphère :
	//*     glutSolidSphere()
	//* Préciser le matériau pour chacun de ces éléments.
	//*****************************************************************
}



///////////////////////////////////////////////////////////////////////////////
// Initialise la scène.
//-----------------------------------------------------------------------------
// Paramètres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void initialise_scene()
{
	construit_maison();
	construit_arbre();
}



///////////////////////////////////////////////////////////////////////////////
// Fonction principale du programme.
//-----------------------------------------------------------------------------
// Paramètres :
//    argc (in) : nombre d'arguments de la ligne de commande.
//    argv (in) : tableau de chaînes de caractères contenant les arguments.
// Retour :
//    Un entier contenant le code de retour du programme.
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	// Initialisation de paramètres de Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maison");

	// Intitialisation de paramètres d'OpenGL
	initGL();

	// Initialisation de la scène
	initialise_scene();

	// Déclaration des fonctions de call-back.
	glutDisplayFunc(&callback_display);
	glutReshapeFunc(&callback_reshape);
	glutKeyboardFunc(&callback_keyboard);
	glutSpecialFunc(&callback_special);
	glutMouseFunc(&callback_mouse);
	glutMotionFunc(&callback_motion);

	// Boucle principale de Glut.
	glutMainLoop();

	// Code de retour
	return 1;
}
