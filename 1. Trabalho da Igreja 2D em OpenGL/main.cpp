/*
 * FreeGLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in FreeGLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <GL/gl.h> //ADD
#include <GL/glu.h> //ADD
#include <GL/glut.h>
#include <stdlib.h>
#include "figuras.h"





void inicio(void);
void altSystemCoordenadas(int w, int h); // Altera o tipo de projeção
void desenho(void);


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize (1280, 1024);  // Tamanho da janela do OpenGL
	glutInitWindowPosition (100, 100); //Posicao inicial da janela do OpenGL
	glutCreateWindow ("IGREJA"); // Da nome para uma janela OpenGL

	inicio(); // Chama a funcao init();

	glutReshapeFunc(altSystemCoordenadas);
	glutDisplayFunc(desenho);
	glutMainLoop();

	return EXIT_SUCCESS;
}

void inicio(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
}

void altSystemCoordenadas(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	glOrtho (-(w / 2), (w / 2), -(h / 2), (h / 2), -1 , 1);
	glMatrixMode(GL_MODELVIEW);
}



void desenho(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();


	// retangulo();
	// triangulo();
	// quadrado();
	// circulo(100, 5, true);


	// glRotatef(180, 1, 0, 0);// grau, x, y, z
	// glTranslatef(-200, -100, 0); x, y, z
	// glScalef(-0.5, -1, 1);




	//Montado Igreja
	glTranslatef(-80, -250, 0);
	retangulo2();//Pilar direito
	glTranslatef(-190, 0, 0);
	quadrado(); //Predio do meio
	glTranslatef(390, 0, 0);
	retangulo_porta();//Porta
	glTranslatef(-120, 0, 0);
	retangulo();//Pilar esquerdo
	glTranslatef(150, 230, 0);
	circulo(55, 100, true);//Circulo Direito
	glTranslatef(-380, 0, 0);
	circulo(55, 100, true);//Circulo Esquerdo
	glTranslatef(0, 70, 0);
	glScalef(0.7, 1, 1);
	triangulo();// Triangulo esquerdo
	glTranslatef(543, 0, 0);
	glScalef(1, 1, 1);
	triangulo();//Triangulo direito
	glTranslatef(-272, 0, 0);
	glScalef(1.72, 1.9, 1);
	triangulo();//Triangulo Central
	glTranslatef(-207.1, 16, 0);
	glScalef(0.5, 0.5, 1);
	cruz();//Cruz da esquerda
	glTranslatef(631.1, 0, 0);
	glScalef(1, 1, 1);
	cruz();//Cruz da direita
	glTranslatef(-317.1, 96, 0);
	glScalef(1, 1, 1);
	cruz();//Cruz central


	/*
		Comandos

		glViewport(0,0, w, h) -> Define a area de janela
		glOrtho(left, right, bottom, top, near, far) -> Define qual projeção ortograficas será utilizado (x1, x2, y1, y2, z1, z2)
		glMatrixModel(GL_PROJECTION) -> Avisa ao OpenGL que todas as operações de transformações futuras irão afetar a camera
		glMatrixModel(GL_MODELVIEW) -> ---------------||--------------------------------- -------------------------- os modelos da cena
		glLoadIdentity() -> Reinicia o sistema de coordenada
	*/


	glFlush();
}
