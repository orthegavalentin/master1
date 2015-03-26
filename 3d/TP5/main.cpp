#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "opengl.h"
#include "Voxel.h"

#include <iostream>

#include <GL/glut.h> 

#define WIDTH  480
#define HEIGHT 480

#define RED   0
#define GREEN 0
#define BLUE  0
#define ALPHA 1

#define KEY_ESC 27
#define LEFT 97
#define UP 233
#define RIGHT 105
#define DOWN 117
#define PREVIOUS 108
#define NEXT 106
#define SWITCH 32
#define PLUS 43
#define MINUS 45
#define ENTER 13

int curve;
int selected;
int par;
int zIndex = 20;

GLint winWidth=WIDTH, winHeight=HEIGHT;
GLfloat eyeX=0.0, eyeY=0.0, eyeZ=2.0;
GLfloat theta=270.0, phi=180.0;
GLfloat upX=10.0, upY=10.0, upZ=10.0;
GLfloat r=2.0;

// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 
void onMouseMove(int x, int y) ;

int main(int argc, char **argv) 
{  
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique, ainsi que son titre
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Premier exemple : carré");

  // initialisation de OpenGL et de la scène
	initGL();  
	init_scene();
	glutPassiveMotionFunc(&onMouseMove);

  // choix des procédures de callback pour 
  // le tracé graphique
	glutDisplayFunc(&window_display);
  // le redimensionnement de la fenêtre
	glutReshapeFunc(&window_reshape);
  // la gestion des événements clavier
	glutKeyboardFunc(&window_key);

  // la boucle prinicipale de gestion des événements utilisateur
	glutMainLoop();  

	return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL() 
{
	glClearColor(RED, GREEN, BLUE, ALPHA);    
	glEnable(GL_DEPTH_TEST);        
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,.6,300);           
}

void eyePosition( void ) {
	eyeX = r * sin(theta*0.0174532) * sin(phi*0.0174532);
	eyeY = r * cos(theta*0.0174532);
	eyeZ = r * sin(theta*0.0174532) * cos(phi*0.0174532);
	GLfloat dt=1.0;
	GLfloat eyeXtemp = r * sin(theta*0.0174532-dt) * sin(phi*0.0174532);
	GLfloat eyeYtemp = r * cos(theta*0.0174532-dt);
	GLfloat eyeZtemp = r * sin(theta*0.0174532-dt) * cos(phi*0.0174532); 

	upX=eyeXtemp-eyeX;
	upY=eyeYtemp-eyeY;
	upZ=eyeZtemp-eyeZ;

	glutPostRedisplay();
}

void onMouseMove(int x, int y) { 
// Mouse point to angle conversion
   theta = (360.0/(double)winHeight)*(double)y*1.0; //3.0 rotations possible
   phi = (360.0/(double)winWidth)*(double)x*1.0; 
// Restrict the angles within 0~360 deg (optional)
   if(theta > 360)theta = fmod((double)theta,360.0);
   if(phi > 360)phi = fmod((double)phi,360.0);
   eyePosition();
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
int nbr = 5;
Point** pts3;
Point** pts0;
Point* orig;
int meridians;
int parallels;
void init_scene()
{
	selected = 0;
	curve = 1;
	par = 1;
	
	pts3 = new Point*[nbr];
	pts3[0] = new Point(0,0,0);
	pts3[1] = new Point(1,2,0);
	pts3[2] = new Point(3,3,0);
	pts3[3] = new Point(2,2,0);
	pts3[4] = new Point(2,3,0);

	pts0 = new Point*[nbr];
	pts0[0] = new Point(2,0,0);
	pts0[1] = new Point(1,5,0);
	pts0[2] = new Point(1,2,0);
	pts0[3] = new Point(1,4,0);
	pts0[4] = new Point(2,1,0);
	orig = new Point(0, 0, 0);
	parallels = 10;
	meridians = 10;
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);        // set to Model View before drawing
	glLoadIdentity();
	gluLookAt(eyeX,eyeY,eyeZ,0,0,0,upX, upY, upZ);

	// glRotatef(0.1f, upX, upY, upZ);/* orbit the Y axis */
	render_scene();
	glutSwapBuffers();
	glFlush();

  // C'est l'endroit où l'on peut dessiner. On peut aussi faire appel
  // à une fonction (render_scene() ici) qui contient les informations 
  // que l'on veut dessiner
	render_scene();

  // trace la scène grapnique qui vient juste d'être définie
	glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre
int size = 20;

GLvoid window_reshape(GLsizei width, GLsizei height)
{  
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est 
  // de trop grosse taille par rapport à la fenêtre.
	glOrtho(-size, size, -size, size, -size, size);

  // toutes les transformations suivantes s´appliquent au modèle de vue 
	glMatrixMode(GL_MODELVIEW);

}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y) 
{  
	Point** p = (curve > 0)?pts3:pts0;
	int* sel = (par > 0)?&parallels:&meridians;

	switch (key) {    
		case KEY_ESC:  
		exit(1);                    
		break; 

		case SWITCH:
		curve *= -1;
		selected = 0;
		break;

		case UP:
		p[selected]->setY(p[selected]->getY() + 1);
		break;

		case DOWN:
		p[selected]->setY(p[selected]->getY() - 1);
		break;

		case LEFT:
		p[selected]->setX(p[selected]->getX() - 1);
		break;

		case RIGHT:
		p[selected]->setX(p[selected]->getX() + 1);
		break;

		case NEXT:
		if(selected < nbr - 1) selected++;
		break;

		case PREVIOUS:
		if(selected > 0) selected--;
		break;

		case ENTER:
		par *= -1;
		break;

		case PLUS:
		(*sel)++;
		break;

		case MINUS:
		if((*sel) > 1) (*sel)--;
		break;

		default:
		printf ("La touche %d n´est pas active.\n", key);
		break;
	}   
	render_scene();
}



//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//Définition de la couleur
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Voxel *v = new Voxel(orig, 5);
	// v->draw();
	// // free(v);

	/*Point*** c = cylindre(orig, 10,  20, meridians);
	drawSurface(c, 2, meridians);*/

	glColor3f(1.0, 1.0, 1.0);
	// Point*** c = sphere(orig, 10, meridians, parallels);
	// drawSurfaceQuads(c, meridians, parallels);
	// free(c);
	glColor3f(1.0, 0.0, 0.0);
	 // displaySphereVolumic(new Point(orig->getX(), orig->getY(), orig->getZ()), 10, 4);

	/**cylindre*/
	// Vector v(0, 5, 0);
	// displayCylindreVolumic(new Point(0, 0, 0), &v, 4, 5);

	/**intersection*/
	// Vector v(0, 5, 0);
	// displayIntersectionSphereCylindre(new Point(0, -5, 0), &v, 10,
	// 	new Point(orig->getX(), orig->getY(), orig->getZ()), 10, 5);

	/**union*/
	// Vector v(0, 5, 0);
	// displayUnionSphereCylindre(new Point(0, 0, 0), &v, 2,
	// 	new Point(0, 4, 0), 4, 5);

	Vector v(0, 10, 0);
	displaySoustractionSphereCylindre(new Point(2, 0, 0), &v, 2,
		new Point(0, 4, 0), 4, 5);

	glFlush();
}
