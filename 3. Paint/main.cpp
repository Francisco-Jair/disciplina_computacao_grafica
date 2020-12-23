/**
 * TUTORIAL:
 *
 * Opcoes no teclado
 * 0 - DESENHAR RETA
 * 1 - DESENHAR TRIANGULO
 * 2 - DESENHAR QUADRILATERO
 * 3 - RESENHAR POLIGONO
 * 4 - DESENHAR CIRCUNFERENCIA
 * 5 - MUDAR COR PARA PRETO
 * 6 - MUDAR COR PARA VERMELHO
 * 7 - MUDAR COR PARA VERDE
 * 8 - MUDAR COR PARA AZUL
 * 9 - ATIVAR FLOOD FILL
 * - - LIMPAR TELA
 * ESC - FECHA PROGRAMA
 *
 * Opcoes no mause:
 * BOTAO ESQUERDO EXECUTA ACAO SELECIONADA
 *
 * Observacoes:
 * 1) Para desenhar eh necessario selecionar a forma desejada, e depois clicar
 * na tela para desenha-lo. Caso seja uma reta ou quadrilatero eh preciso 2
 * cliques.
 * Se for um triangulo, 3 cliques. E se for um poligono, eh possivel desenhar a
 * partir de 3 cliques e logo depois clique com o botao direito para fechar
 * o poligono.
 * 2) Para colorir uma figura, primeiro selecione uma cor e depois selecione a
 * opcao de flood fill.  Depois basta clicar com o botao esquerdo dentro da
 * figura e ele ira automaticamente preenche-la. Tem um possivel bug no preenchimento
 * que acontece quando eh diminuido a largura da linha. Depois de alguns testes
 * foi fixado com tamanho 3, mas ainda pode ocorrer do floodfill encontrar uma
 * brecha na figura e desenhar o fundo da tela. Se isso ocorrer ele ficara em loop
 * desenhando o fundo e nunca vai acabar.
 *
 */


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "structure.h"
#include "bresenham.h"
#include "drawQuadrilateral.h"
#include "drawTriangle.h"
#include "drawPolygon.h"
#include "rasterizeCircumference.h"
#include "floodFill.h"
#include "menu.h"

// Funcoes necessarios do GLUT
void init(void);
void reshape(int w, int h);
void display(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

// Funcao que percorre a lista de pontos desenhando-os na tela
void drawPontos();

int lineHight = 15, lineMargin = 5, currentHight = 15;

// Funcao Principal do C
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (width, height);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Editor Grafico");

	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard); // funcao callback do teclado
	glRasterPos2f(lineMargin, currentHight);
	glutMouseFunc(mouse); // funcao callback do mouse

	glutDisplayFunc(display); //funcao callback de desenho
	init(); // Chama funcao init();
	glutMainLoop(); // executa o loop do OpenGL
	return 0; // retorna 0 para o tipo inteiro da funcao main();
}

// Funcao com alguns comandos para a inicializacao do OpenGL;
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
}

void reshape(int w, int h)
{
	// Reinicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Definindo o Viewport para o tamanho da janela
	glViewport(0, 0, w, h);

	width = w;
	height = h;
	glOrtho (0, w, 0, h, -1 , 1);

	// muda para o modo GL_MODELVIEW (n�o pretendemos alterar a projec��o
	// quando estivermos a desenhar na tela)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	click1 = true; //Para redesenhar os pixels selecionados
	click2 = true;
	click3 = true;
	click4 = true;
	click5 = true;
}

// Callback para utilizacao das teclas do teclado
void keyboard(unsigned char key, int x, int y)
{
	switch (key)   // key - variavel que possui valor ASCII da tecla precionada
	{
	case 27: // codigo ASCII da tecla ESC
		exit(0); // comando pra finalizacao do programa
		break;
	case 48: // tecla 0 (desenha reta)
		menuPictures(0);
		break;
	case 49: // tecla 1 (desenha triangulo)
		menuPictures(2);
		break;
	case 50: // tecla 2 (desenha quadrado)
		menuPictures(1);
		break;
	case 51: // tecla 3 (desenha poligono)
		menuPictures(3);
		break;
	case 52: // tecla 4 (desenha circunferencia)
		menuPictures(4);
		break;
	case 53: // tecla 5 (muda para cor preto)
		menufloodFillColors(0);
		break;
	case 54: // tecla 6 (muda para cor vermelho)
		menufloodFillColors(1);
		break;
	case 55: // tecla 7 (muda para cor verde)
		menufloodFillColors(2);
		break;
	case 56: // tecla 8 (muda para cor azul)
		menufloodFillColors(3);
		break;
	case 57: // tecla 9 (ativar flood fill - preenchimento de poligono)
		menuFloodFill(0);
		break;
	}
}

// Callback para a utilizacao dos botoes do mouse
void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:// Clique com o botao esquerdo identificado

		if (state == GLUT_DOWN)
		{
			if(click1 && !click2) // quando fizer o primeiro clique
			{
				click2 = true;
				pointsArray.push_back(x);
				x_2 = x;
				pointsArray.push_back(height - y);
				y_2 = height - y;
				printf("x2y2(%d,%d)\n", x, height - y);
				glutPostRedisplay();
			}
			else if(click1 && click2 && !click3) // quando fizer o segundo clique
			{
				click3 = true;
				pointsArray.push_back(x);
				pointsArray.push_back(height - y);
				printf("x3y3(%d,%d)\n", x, height - y);
				glutPostRedisplay();
			}
			else // quando fizer todos os cliques
			{
				click1 = true;
				pointsArray.push_back(x);
				x_1 = x;
				pointsArray.push_back(height - y);
				y_1 = height - y;
				printf("x1y1(%d,%d)\n", x, height - y);
				glutPostRedisplay();
			}

		}
		break;
	case GLUT_RIGHT_BUTTON:// Clique com o botao direito identificado
		if (state == GLUT_DOWN)
		{
			// se houver 3 cliques e for maior que 3 permitir desenho (caso poligono)
			if(click1 && click2 && click3 && pointsArray.size() > 3 && !click4)
			{
				click5 = true;
				aux = true;
			}
			click4 = true;
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
}


// Funcao usada na funcao callback para desenhar na tela
void display(void)
{
	cor1 = 0, cor2 = 0, cor3 = 0;
	glColor3f (0.0, 0.0, 0.0); // menu preto
	glClear(GL_COLOR_BUFFER_BIT); // Limpa o Buffer de Cores

	// barra de menu
	glBegin(GL_QUADS);
	glVertex2f(200, 1000);
	glVertex2f(0, 1000);
	glVertex2f(0, 0);
	glVertex2f(200, 0);
	glEnd();

	glColor3f (1.0, 1.0, 1.0); // quadro branco
	// quadro de desenho
	glBegin(GL_QUADS);
	glVertex2f(2000, 1000);
	glVertex2f(150, 1000);
	glVertex2f(150, 0);
	glVertex2f(2000, 0);
	glEnd();

	glPointSize(5);

	if(reta && !quadrilatero && !triangulo && !poligono && !circunferencia)  //bresenham e quadrilatero
	{
		if(click1 && click2)
		{
			bresenham(x_1, y_1, x_2, y_2);
			drawPontos();
			click1 = false;
			click2 = false;
			click3 = false;
			pointsArray.clear();// Limpa o vetor de pontos
		}
	}
	else if(!reta && quadrilatero && !triangulo && !poligono && !circunferencia)  //bresenham e quadrilatero
	{
		if(click1 && click2)
		{
			drawQuadrilateral(pointsArray);
			drawPontos();
			click1 = false;
			click2 = false;
			click3 = false;
			pointsArray.clear();//limpa o vetor de pontos
		}

	}

	else if(!reta && !quadrilatero && triangulo && !poligono && !circunferencia)
	{
		// identificar sequencia de cliques do triangulo
		if(click1 && click2 && click3)
		{
			drawTriangle(pointsArray);
			drawPontos();
			click1 = false;
			click2 = false;
			click3 = false;
			click4 = false;
			click5 = false;
			pointsArray.clear();//limpa o vetor de pontos


		}
	}
	else if(!reta && !quadrilatero && !triangulo && poligono && !circunferencia)
	{
		if(click1 && click2 && click3 && click4 && click5)
		{
			click1 = false;
			click2 = false;
			click3 = false;
			click4 = false;
			click5 = false;
			cont1 = 4;
			cont2 = 4;
			drawPolygon(pointsArray);
			drawPontos();
			pointsArray.clear();//limpa o vetor de pontos

		}

		if(click1 && click2 && click3 && click4 && !click5)
		{
			click4 = false;
		}
		if(aux) //cria menu novamente apos o desenho de poligono
		{
			aux = false;
			poligono = false;
			// menuPressionado = false;
		}
	}
	else if(!reta && !quadrilatero && !triangulo && !poligono && circunferencia)
	{
		if(click1)
		{
			rasterizeCircumference(x_1, y_1, raio); //especificar raio!
			drawPontos();
			click1 = false;
			click2 = false;
			pointsArray.clear();//limpa o vetor de pontos

		}

	}
	else if(floodFill_aux && !reta && !quadrilatero && !triangulo && !poligono && !circunferencia)
	{
		if(click1)
		{

			float bCol[] = {0, 0, 0}; //cor do pixel clicado no caso clicou dentro da figura ent�o � branco

			glPointSize(2);//tamanho do ponto de pintura
			floodFill(x_1, y_1, floodFillColor, bCol);
			click1 = false;
			click2 = false;

			pointsArray.clear();//limpa o vetor de pontos

		}
	}
	glutSwapBuffers();// manda o OpenGl renderizar as primitivas


}

//Funcao que desenha os pontos contidos em uma lista de pontos
void drawPontos()
{
	ponto * pnt;
	pnt = pontos;
	glBegin(GL_POINTS); // Seleciona a primitiva GL_POINTS para desenhar
	while(pnt != NULL)
	{
		glColor3f(0, 0, 0);
		glVertex2i(pnt->x, pnt->y);
		pnt = pnt->prox;
	}
	glEnd();  // indica o fim do desenho
}

// Funcao que realiza translacao de uma figura (atividade f))
void translationElement(double *x, double *y, double tx, double ty)
{
	double matriz[3][3] = {
		{1, 0, 0},
		{0, 1, 0},
		{tx, ty, 1}
	};
	double k[3] = {*x, *y, 1};
	double aux = 0, result[3];
	int i, j;

	for (i = 0; i < 3; i++)
	{
		aux = 0;
		for(j = 0; j < 3; j++)
		{
			aux += k[j] * matriz[j][i];
		}
		result[i] = aux;
	}

	*x = result[0];
	*y = result[1];
}

// Funcao que realiza translacao de uma escala (atividade f))
void scaleElement(double *x, double *y, double sx, double sy)
{
	double matriz[3][3] = {
		{sx, 0, 0},
		{0, sy, 0},
		{0, 0, 1}
	};
	double k[3] = {*x, *y, 1};
	double aux = 0, result[3];
	int i, j;

	for (i = 0; i < 3; i++)
	{
		aux = 0;
		for(j = 0; j < 3; j++)
		{
			aux += k[j] * matriz[j][i];
		}
		result[i] = aux;
	}

	*x = result[0];
	*y = result[1];
}

// Funcao que realiza cisalhamento de uma figura (atividade f))
void shearElement(double *x, double *y, double C, double direcao) //direcao 1 - eixo x 2- eixo y
{
	double matriz[3][3];
	double k[3] = {*x, *y, 1};
	double aux = 0, result[3];
	int i, j;

	if (direcao == 1)
	{
		int matriz[3][3] = {
			{1, 0, 0},
			{C, 1, 0},
			{0, 0, 1}
		};
	}
	else if(direcao == 2)
	{
		int matriz[3][3] = {
			{1, C, 0},
			{0, 1, 0},
			{0, 0, 1}
		};
	}
	
	for (i = 0; i < 3; i++)
	{
		aux = 0;
		for(j = 0; j < 3; j++)
		{
			aux += k[j] * matriz[j][i];
		}
		result[i] = aux;
	}
	*x = result[0];
	*y = result[1];
}

// Funcao que realiza refrexao de uma figura (atividade f))
void reflectionElement(double *x, double *y, int direcao) //direcao 1 - eixo x 2- eixo y 3-origem
{
	double matriz[3][3];
	double k[3] = {*x, *y, 1};
	double aux = 0, result[3];
	int i, j;

	if (direcao == 1)
	{
		double	matriz[3][3] = {
			{1, 0, 0},
			{0, -1, 0},
			{0, 0, 1}
		};
	}
	else if(direcao == 2)
	{
		double	matriz[3][3] = {
			{ -1, 0, 0},
			{0, 1, 0},
			{0, 0, 1}
		};
	}
	else if(direcao == 3)
	{
		double matriz[3][3] = {
			{ -1, 0, 0},
			{0, -1, 0},
			{0, 0, 1}
		};
	}

	for (i = 0; i < 3; i++)
	{
		aux = 0;
		for(j = 0; j < 3; j++)
		{
			aux += k[j] * matriz[j][i];
		}
		result[i] = aux;
	}

	*x = result[0];
	*y = result[1];
}

// Funcao que realiza rotacao de uma figura (atividade f))
void rotarionElement(double *x, double *y, double grau)
{
	int k[3] = {*x, *y, 1};
	double cosseno, seno;
	cosseno = cos( grau * M_PI / 180.0 );
	seno = sin(grau * M_PI / 180.0);
	double matriz[3][3] = {
		{cosseno, seno, 0},
		{ -seno, cosseno, 0},
		{0, 0, 1}
	};
	int aux = 0, result[3];
	int i, j;

	for (i = 0; i < 3; i++)
	{
		aux = 0;
		for(j = 0; j < 3; j++)
		{
			aux += k[j] * matriz[j][i];
		}
		result[i] = aux;
	}

	*x = result[0];
	*y = result[1];

}
