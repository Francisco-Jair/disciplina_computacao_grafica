/*
	1 - As coordenadas devem ser colocadas no sentido anti-horário
*/

#include <math.h>
#define PI 3.1415926535898


void cruz()
{
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(100.0, 185.0);
	glVertex2f(100.0, 72.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(50.0, 149.0);
	glVertex2f(155.0, 149.0);
	glEnd();
}


void retangulo()
{

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0); //AZUL -> RGB

	glVertex2f(-300.0, 0.0);
	glVertex2f(-300.0, 300.0);
	glVertex2f(-160.0, 300.0);
	glVertex2f(-160.0, 0.0);

	glEnd();
}

void retangulo_porta()
{

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0);

	glVertex2f(-210.0, 0.0);
	glVertex2f(-210.0, 155.0);
	glVertex2f(-100.0, 155.0);
	glVertex2f(-100.0, 0.0);

	glEnd();
}

void retangulo2()
{

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0); //AZUL -> RGB

	glVertex2f(300.0, 0.0);
	glVertex2f(300.0, 300.0);
	glVertex2f(160.0, 300.0);
	glVertex2f(160.0, 0.0);

	glEnd();
}

void triangulo()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);

	glVertex2f(0.0, 100.0);
	glVertex2f(100.0, 0.0);
	glVertex2f(-100.0, 0.0);

	glEnd();
}

void quadrado()
{

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);

	glVertex2f(100.0, 0.0);
	glVertex2f(100.0, 300.0);
	glVertex2f(350.0, 300.0);
	glVertex2f(350.0, 0.0);

	glEnd();
}

void circulo(float raio , int num_linhas, bool preechido)
{
	int i;
	float angulo, x = 0, y = 0;

	glColor3f(0.0, 1.0, 0.0);
	angulo = (2 * M_PI) / num_linhas;

	if(preechido)
	{
		glBegin(GL_TRIANGLE_FAN);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
	}

	for(i = 1; i <= num_linhas; i++)
	{
		x = raio * cos(i * angulo);
		y = raio * sin(i * angulo);
		glVertex2f(x, y);
	}

	glEnd();
}
