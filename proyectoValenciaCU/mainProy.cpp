//#include <gl/gl.h>     // The GL Header File
//#include <windows.h>	//Solo para Windows
//#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
//#include <stdlib.h>		// Descomentar para Linux
//#include <stdio.h>
//#include <string.h>
//#include <malloc.h>		// Solo para Windows

#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"

CModel rectoria;
CModel facultadD;
CModel biblioteca;
CModel islas;

//wevos

CFiguras pasto;
CFiguras isla;
CFiguras camino;
CTexture t_placasRectoria;
CTexture t_escalerasIslas;
CTexture t_caminoIslas;
CTexture texturaPasto;
CTexture t_piedra;

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
CCamera objCamera;

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 
//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int font = (int)GLUT_BITMAP_HELVETICA_18;

//Otras opciones son:
/*GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18*/



GLUquadricObj *quadratic;				// Storage For Our Quadratic Objects ( NEW )


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = { 22 };



float colorR = 0.0;
float colorG = 0.0;
float colorB = 0.0;


void InitGL()     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	//Para construir la figura comentar esto
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	glEnable(GL_COLOR_MATERIAL);					//Habilitar GlColor3f
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_BACK, GL_LINE);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE);			// Set The Blending Function For Translucency
	//glColor4f(1.0f, 1.0f, 1.0f, 0.5); 

	rectoria._3dsLoad("rectoria/rectoria.3ds");
	rectoria.LoadTextureImages();
	rectoria.GLIniTextures();
	rectoria.ReleaseTextureImages();

	biblioteca._3dsLoad("biblioteca/biblioteca.3ds");
	biblioteca.LoadTextureImages();
	biblioteca.GLIniTextures();
	biblioteca.ReleaseTextureImages();

	//islas._3dsLoad("islas/islas.3ds");
	//islas.LoadTextureImages();
	//islas.GLIniTextures();
	//islas.ReleaseTextureImages();

	texturaPasto.LoadTGA("city/pasto01.tga");
	texturaPasto.BuildGLTexture();
	texturaPasto.ReleaseImage();

	facultadD._3dsLoad("derecho3DS/derecho.3ds");
	facultadD.LoadTextureImages();
	facultadD.GLIniTextures();
	facultadD.ReleaseTextureImages();

	t_placasRectoria.LoadTGA("city/pasto01.tga");
	t_placasRectoria.BuildGLTexture();
	t_placasRectoria.ReleaseImage();

	t_escalerasIslas.LoadTGA("cuadrosrectoria/texturaEsc.tga");
	t_escalerasIslas.BuildGLTexture();
	t_escalerasIslas.ReleaseImage();

	t_caminoIslas.LoadTGA("caminoIslas/techo_2.tga");
	t_caminoIslas.BuildGLTexture();
	t_caminoIslas.ReleaseImage();

	t_piedra.LoadTGA("caminoIslas/volcan.tga");
	t_piedra.BuildGLTexture();
	t_piedra.ReleaseImage();

	quadratic = gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )


	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);



}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
	//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void generaCuadro(GLfloat ax, GLfloat ay, GLfloat az, GLuint text){
	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_QUADS);//para que se vea la textura bien xD
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0, 0); glVertex3f(ax, ay, az);
	glTexCoord2f(1.0, 0); glVertex3f(ax + 3.7, ay, az);
	glTexCoord2f(1.0, 1.0); glVertex3f(ax + 3.7, ay, az + 3.7);
	glTexCoord2f(1, 0.0); glVertex3f(ax, ay, az + 3.7);
	glEnd();
}

void escalerasIslasRectoria(GLfloat ax, GLfloat ay, GLfloat az, GLuint text, GLint cont){
	GLfloat ancho;
	if (cont == 10 || cont == 20)
		ancho = 2.5;
	else
		ancho = 0.3;

	glBindTexture(GL_TEXTURE_2D, text);
	glBegin(GL_QUADS);//para que se vea la textura bien xD
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0, 0); glVertex3f(ax, ay, az);
	glTexCoord2f(1.0, 0); glVertex3f(ax + ancho, ay, az);
	glTexCoord2f(1.0, 1.0); glVertex3f(ax + ancho, ay, az + 31.65);
	glTexCoord2f(1, 0.0); glVertex3f(ax, ay, az + 31.65);


	glEnd();
}

void escalerasIslasRectoria1(GLfloat ax, GLfloat ay, GLfloat az, GLuint text, GLint cont){

	GLfloat ancho;
	if (cont == 10 || cont == 20)
		ancho = 2.5;
	else
		ancho = 0.3;
	glBindTexture(GL_TEXTURE_2D, text);

	glBegin(GL_QUADS);//para que se vea la textura bien xD
	glColor3f(1.0, 1.0, 1.0);
	glTexCoord2f(0, 0); glVertex3f(ax + ancho, ay, az);
	glTexCoord2f(1.0, 0); glVertex3f(ax + ancho, ay - 0.24, az);
	glTexCoord2f(1.0, 1.0); glVertex3f(ax + ancho, ay - 0.24, az + 31.65);
	glTexCoord2f(1, 0.0); glVertex3f(ax + ancho, ay, az + 31.65);

	glEnd();
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();


	glPushMatrix();
	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();

	glPushMatrix(); //Rectoria
	glDisable(GL_LIGHTING);
	glRotatef(-4, 0, 1, 0);
	glTranslatef(-235, 7.0, 86.0);
	glScalef(0.017, 0.017, 0.017);
	rectoria.GLrender(NULL, _SHADED, 1);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Biblioteca
	glDisable(GL_LIGHTING);
	glTranslatef(-208.0, 7.0, 5.0);
	glScalef(0.45, 0.45, 0.45);
	biblioteca.GLrender(NULL, _SHADED, 1);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto islas
	glDisable(GL_LIGHTING);
	glTranslatef(-20.0, 0.5, 40.0);
	glRotatef(185, 0, 1, 0);
	glScalef(210.0, 0.0, 100.0);
	pasto.prisma2(texturaPasto.GLindex, texturaPasto.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //camino islas abajo
	glDisable(GL_LIGHTING);
	glTranslatef(-15.0, 0.5, 92.0);
	glRotatef(185, 0, 1, 0);
	glScalef(210.0, 0.5, 5.0);
	camino.prisma2(t_caminoIslas.GLindex, t_piedra.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //camino islas arriba
	glDisable(GL_LIGHTING);
	glTranslatef(-24.0, 0.5, -10.0);
	glRotatef(185, 0, 1, 0);
	glScalef(210.0, 0.5, 5.0);
	camino.prisma2(t_caminoIslas.GLindex, t_piedra.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //camino islas derecha
	glDisable(GL_LIGHTING);
	glTranslatef(81.0, 0.5, 32.0);
	glRotatef(185, 0, 1, 0);
	glScalef(8.0, 0.5, 100.0);	
	camino.prisma2(t_caminoIslas.GLindex, t_piedra.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //camino islas izquierda
	glDisable(GL_LIGHTING);
	glTranslatef(-120.0, 0.5, 50.0);
	glRotatef(185, 0, 1, 0);
	glScalef(8.0, 0.5, 100.0);
	camino.prisma2(t_caminoIslas.GLindex, t_piedra.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //barra de derecho
	glDisable(GL_LIGHTING);
	glTranslatef(-30.0, 0.5, -20.0);
	glRotatef(185, 0, 1, 0);
	glScalef(210.0, 5.0, 5.0);
	camino.prisma2(t_piedra.GLindex, t_piedra.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Isla Inge
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTranslatef(25.0, -3.0, 60.0);
	glScalef(5.0, 2.0, 3.0);
	isla.esfera(5.0, 15.0, 15.0, texturaPasto.GLindex);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Isla Derecho
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTranslatef(25.0, -3.0, 9.0);
	glScalef(5.0, 2.0, 3.0);
	isla.esfera(5.0, 15.0, 15.0, texturaPasto.GLindex);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //Isla Filos
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTranslatef(-60.0, -3.0, 20.0);
	glScalef(5.0, 2.0, 3.0);
	isla.esfera(5.0, 15.0, 15.0, texturaPasto.GLindex);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //facultad de derecho
	glDisable(GL_LIGHTING);
	glRotatef(-4, 0, 1, 0);
	glTranslatef(-32.0, 0.0, -9.0);
	glScalef(0.7, 0.7, 0.7);
	facultadD.GLrender(NULL, _SHADED, 1);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();//pastoRectoria
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_ONE_MINUS_SRC_ALPHA,GL_ONE_MINUS_DST_COLOR GL_ONE_MINUS_SRC_COLOR
	for (int i = 17616; i > 6943; i = i - 422){
		GLfloat aux = GLfloat(GLfloat(i) / 100) - 52;
		//printf("\n%.02f", aux);
		for (int j = 23129; j > 12000; j = j - 422){
			GLfloat aux1 = GLfloat(-GLfloat(j) / 100) - 52;
			//printf("\n%.02f", aux1);
			generaCuadro(aux1, 7.1, aux, t_placasRectoria.GLindex);
		}
	}
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glPopMatrix();

	glPushMatrix();//escaleras
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	int j = 710;
	int cont = 0;
	for (int i = 16914; i > 14014; i = i - 30){
		/*for (int i = 710; i > 0; i = i - 23){
		printf("ebtri2");
		GLfloat aux1 = GLfloat(GLfloat(i) / 100);
		escalerasIslasRectoria(aux, aux1, 141.1, t_escalerasIslas.GLindex);
		}*/
		GLfloat aux1 = GLfloat(GLfloat(j) / 100);
		GLfloat aux = GLfloat(-GLfloat(i) / 100);
		printf("\n%.02f", aux);
		escalerasIslasRectoria(aux, aux1, 19.18, t_escalerasIslas.GLindex, cont);
		escalerasIslasRectoria1(aux, aux1, 19.18, t_escalerasIslas.GLindex, cont);
		if (cont == 10 || cont == 20){
			i = i - 190;
			printf("entro en cont=[%d]\n", cont);
		}
		j = j - 23;
		cont++;

	}
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	glColor3f(1.0, 1.0, 1.0);		//Para que los demas elementos regresen a su color de su textura y no permanescan rojos
	glPopMatrix();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	pintaTexto(-0.25, 0.23, -0.25, (void *)font, "Practica 9");
	pintaTexto(-0.25, 0.21, -0.25, (void *)font, "Textura en Movimiento");
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers();

}

void animacion()
{

}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 300.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case 'r':		//Cambia posicion de la camara desee arriba
	case 'R':
		objCamera.Position_Camera(-31.099323, 160.699631, 9.364282, -33.938477, 160.699631, -24.574570, 0.000000, 1.000000, 0.000000);
		g_lookupdown = 89.0;
		break;

	case 'f':		// Posicion inicial
	case 'F':
		objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);
		g_lookupdown = 0.0;
		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	case 'p':
		//pos_camY -= 0.5f;
		//pos_cam.y += 0.5f;
		//eye_cam.y += 0.5f;
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case 'l':
		//pos_camY += 0.5f;
		//pos_cam.y -= 0.5f;
		//eye_cam.y -= 0.5f;
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		//pos_camY -= 0.5f;
		//pos_cam.y += 0.5f;
		//eye_cam.y += 0.5f;
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		//pos_camY += 0.5f;
		//pos_cam.y -= 0.5f;
		//eye_cam.y -= 0.5f;
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Practica 9"); // Nombre de la Ventana
	//glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);
	glutMainLoop();          // 

	return 0;
}
