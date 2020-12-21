// Bibliotecas utilizadas pelo OpenGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Biblioteca com funcoes matematicas
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <stdlib.h>




// Variaveis Globais
bool click1 = false, click2 = false;
bool quadrilatero_ = false;


double x_1, y_1, x_2, y_2;

int width = 512, height = 512; //Largura e altura da janela

// Estrututa de dados para o armazenamento dinamico dos pontos
// selecionados pelos algoritmos de rasterizacao
struct ponto
{
	int x;
	int y;
	ponto * prox;
};

// Lista encadeada de pontos
// indica o primeiro elemento da lista
ponto * pontos = NULL;

// Funcao para armazenar um ponto na lista
// Armazena como uma Pilha (empilha)
ponto * pushPonto(int x, int y)
{
	ponto * pnt;
	pnt = new ponto;
	pnt->x = x;
	pnt->y = y;
	pnt->prox = pontos;
	pontos = pnt;
	return pnt;
}

// Funcao para desarmazenar um ponto na lista
// Desarmazena como uma Pilha (desempilha)
ponto * popPonto()
{
	ponto * pnt;
	pnt = NULL;
	if(pontos != NULL)
	{
		pnt = pontos->prox;
		delete pontos;
		pontos = pnt;
	}
	return pnt;
}

// Declaracoes forward das funcoes utilizadas
void GerenciaMouse(int button, int state, int x, int y);
void init(void);
void reshape(int w, int h);
void display(void);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

// Funcao que implementa o Algoritmo Imediato para rasterizacao de retas
void retaImediata(double x1, double y1, double x2, double y2);
//Função que implementa o Algoritmo de Bresenham
void algoritmoDeBresenham(int x1, int y1, int x2, int y2);

////Função que implementa o Algoritmo de Bresenham Com redução ao primeiro octante
void algoritmoDeBresenhamReducao1Octante(int x1, int y1, int x2, int y2);

// Funcao que percorre a lista de pontos desenhando-os na tela
void drawPontos();

//Função para criar quadrilateros
void quadrilateros(int x1, int y1, int x2, int y2);


// Funcao Principal do C
int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Passagens de parametro C para o glut
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); // Selecao do Modo do Display e do Sistema de cor utilizado
	glutInitWindowSize (width, height);  // Tamanho da janela do OpenGL
	glutInitWindowPosition (100, 100); //Posicao inicial da janela do OpenGL
	glutCreateWindow ("Paint"); // Da nome para uma janela OpenGL
	//glutMouseFunc(GerenciaMouse);
	init(); // Chama funcao init();
	glutReshapeFunc(reshape); //funcao callback para redesenhar a tela
	glutKeyboardFunc(keyboard); //funcao callback do teclado
	glutMouseFunc(mouse); //funcao callback do mouse
	glutDisplayFunc(display); //funcao callback de desenho
	glutMainLoop(); // executa o loop do OpenGL
	return 0; // retorna 0 para o tipo inteiro da funcao main();
}

void MenuPrincipal(int op)
{
}


void Figuras(int op)
{
	printf("%d\n", op);
	int r, g, b;
	switch(op)
	{
	case 0:

		break;
	case 1:
		r = 0.0f;
		g = 1.0f;
		b = 0.0f;
		break;
	case 2:
		r = 0.0f;
		g = 0.0f;
		b = 1.0f;
		break;
	}

	glutPostRedisplay();
}

void limparTela(int op)
{

	switch(op)
	{
	case 0:
		init();
		break;
	default:
		break;
	}


	glutPostRedisplay();
}

// Criacao do Menu
void CriaMenu(int button, int state, int x, int y)
{
	int menu, submenu1, submenu2;

	submenu1 = glutCreateMenu(Figuras);
	glutAddMenuEntry("Quadrilateros", 0);
	// glutAddMenuEntry("Verde", 1);
	// glutAddMenuEntry("Azul", 2);

	submenu2 = glutCreateMenu(limparTela);
	glutAddMenuEntry("Limpar", 0);

	menu = glutCreateMenu(MenuPrincipal);
	glutAddSubMenu("Cor", submenu1);
	glutAddSubMenu("Limpar tela", submenu2);


	glutAttachMenu(GLUT_RIGHT_BUTTON);
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

	// muda para o modo GL_MODELVIEW (não pretendemos alterar a projecção
	// quando estivermos a desenhar na tela)
	glMatrixMode(GL_MODELVIEW);
	click1 = true; //Para redesenhar os pixels selecionados
	click2 = true;
}

// Funcao usada na funcao callback para utilizacao das teclas normais do teclado
void keyboard(unsigned char key, int x, int y)
{
	switch (key)   // key - variavel que possui valor ASCII da tecla precionada
	{
	case 27: // codigo ASCII da tecla ESC
		exit(0); // comando pra finalizacao do programa
		break;
	}
}

//Funcao usada na funcao callback para a utilizacao do mouse
void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			if(click1)
			{
				click2 = true;
				x_2 = x;
				y_2 = height - y;
				printf("x2y2(%.0f,%.0f)\n", x_2, y_2);
				glutPostRedisplay();
			}
			else
			{
				click1 = true;
				x_1 = x;
				y_1 = height - y;
				printf("x1y1(%.0f,%.0f)\n", x_1, y_1);
			}
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			// CriaMenu(button, state, x, y);
			int menu, submenu1, submenu2;

			submenu1 = glutCreateMenu(Figuras);
			glutAddMenuEntry("Quadrilateros", 0);


			menu = glutCreateMenu(MenuPrincipal);
			glutAddSubMenu("Cor", submenu1);
			glutAddSubMenu("Limpar tela", submenu2);

			glutAttachMenu(GLUT_RIGHT_BUTTON);
		}


		break;
		/*
		      case GLUT_MIDDLE_BUTTON:
		         if (state == GLUT_DOWN) {
		            glutPostRedisplay();
		         }
		         break;
		      case GLUT_RIGHT_BUTTON:
		         if (state == GLUT_DOWN) {
		            glutPostRedisplay();
		         }
		         break;
		*/
	default:
		break;
	}
}

// Funcao usada na funcao callback para desenhar na tela
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //Limpa o buffer de cores e reinicia a matriz
	glLoadIdentity();

	glColor3f (0.0, 0.0, 0.0); // Seleciona a cor default como preto


	if(click1 && click2)
	{
		// retaImediata(x_1, y_1, x_2, y_2);
		//algoritmoDeBresenham(x_1, y_1, x_2, y_2);
		algoritmoDeBresenhamReducao1Octante(x_1, y_1, x_2, y_2);
		drawPontos();
		click1 = false;
		click2 = false;
	}

	glutSwapBuffers(); // manda o OpenGl renderizar as primitivas

}

//Funcao que desenha os pontos contidos em uma lista de pontos
void drawPontos()
{
	ponto * pnt;
	pnt = pontos;
	glBegin(GL_POINTS); // Seleciona a primitiva GL_POINTS para desenhar
	while(pnt != NULL)
	{
		glVertex2i(pnt->x, pnt->y);
		pnt = pnt->prox;
	}
	glEnd();  // indica o fim do desenho
}

void retaImediata(double x1, double y1, double x2, double y2)
{
	double m, b, yd, xd;
	double xmin, xmax, ymin, ymax;
	//Armazenando os extremos para desenho
	pontos = pushPonto((int)x1, (int)y1);
	pontos = pushPonto((int)x2, (int)y2);

	if(x2 - x1 != 0) //Evita a divisão por zero
	{
		m = (y2 - y1) / (x2 - x1);
		b = y1 - (m * x1);

		if(m >= -1 && m <= 1) // Verifica se o declive da reta tem tg de -1 a 1, se verdadeira calcula incrementando x
		{
			xmin = (x1 < x2) ? x1 : x2;
			xmax = (x1 > x2) ? x1 : x2;

			for(int x = (int)xmin + 1; x < xmax; x++)
			{
				yd = (m * x) + b;
				yd = floor(0.5 + yd);
				pontos = pushPonto(x, (int)yd);
			}
		}
		else   // Se menor que -1 ou maior que 1, calcula incrementado os valores de y
		{
			ymin = (y1 < y2) ? y1 : y2;
			ymax = (y1 > y2) ? y1 : y2;

			for(int y = (int)ymin + 1; y < ymax; y++)
			{
				xd = (y - b) / m;
				xd = floor(0.5 + xd);
				pontos = pushPonto((int)xd, y);
			}
		}

	}
	else   // se x2-x1 == 0, reta perpendicular ao eixo x
	{
		ymin = (y1 < y2) ? y1 : y2;
		ymax = (y1 > y2) ? y1 : y2;
		for(int y = (int)ymin + 1; y < ymax; y++)
		{
			pontos = pushPonto((int)x1, y);
		}
	}
}

void algoritmoDeBresenham(int x1, int y1, int x2, int y2)
{
	int deltaX, deltaY, d, incE, incNE, x, y, dIni = 0, cont = 0;

	//Armazenando os extremos para desenho
	pontos = pushPonto((int)x1, (int)y1);
	pontos = pushPonto((int)x2, (int)y2);

	//calculando os valores
	deltaX = x2 - x1;
	deltaY = y2 - y1;
	d = (2 * deltaY) - deltaX;
	incE = 2 * deltaY;
	incNE = 2 * (deltaY - deltaX);

	//inicializado x e y
	x = x1;
	y = y1;

	while(x < x2)
	{
		if(dIni <= 0)
		{
			if(cont != 1)
			{
				dIni = d;
				cont++;
			}
			else
			{
				dIni += incE;
			}
		}
		else
		{
			dIni += incNE;
			y += 1;
		}

		x += 1;
		pontos = pushPonto(x, y);
	}
}

void algoritmoDeBresenhamReducao1Octante(int x1, int y1, int x2, int y2)
{

	int deltaX, deltaY, d, incE, incNE, x, y, dIni = 0, cont = 0, Xaux, Yaux;
	bool S = false, D = false;
	//São necessario 3 passos

	// 1ª -> Transformar os segmentos de retas com declive negativo em positivo
	//Negativo: 90 < alfa < 180   Postivo: 0 < alfa < 90 Nulo: alfa = 0

	//2ª -> Trocar os declives superio a 1 em declives menores do que 1
	// Só trocar o segmento de cada ponto; se deltaX < deltay então m = deltaY/deltaX > 1
	// se deltaX > deltaY, m fica entre [0;1]

	//3ª -> Troco os extremos, ordenando eles pelo maior
	//Transformação inversa


	deltaX = x2 - x1;
	deltaY = y2 - y1;



	//Verificando o Simetrico
	if((deltaX * deltaY) < 0)
	{
		y1 = y1 * (-1);
		y2 = y2 * (-1);

		S = true;

		deltaX = x2 - x1;
		deltaY = y2 - y1;

	}

	//Verificando se o angulo e maior que 45 graus -> Declive
	if(abs(deltaX) < abs(deltaY))
	{
		int aux;
		//pontos A
		aux = x1;
		x1 = y1;
		y1 = aux;

		//Ponto B
		aux = x2;
		x2 = y2;
		y2 = aux;

		//Calculo delta
		deltaX = x2 - x1;
		deltaY = y2 - y1;

		D = true;
	}

	//Ordenado os valores de x
	if(x1 > x2)
	{
		int aux;

		//Trocando pontos de x;
		aux = x1;
		x1 = x2;
		x2 = aux;

		//trocando pontos de y
		aux = y1;
		y1 = y2;
		y2 = aux;

		deltaX = x2 - x1;
		deltaY = y2 - y1;
	}


	//Aplicando o algoritmo de Bresenham
	pontos = pushPonto((int)x1, (int)y1);
	pontos = pushPonto((int)x2, (int)y2);


	d = (2 * deltaY) - deltaX;
	incE = 2 * deltaY;
	incNE = 2 * (deltaY - deltaX);

	x = x1;
	y = y1;

	while(x < x2)
	{
		if(dIni <= 0)
		{
			if(cont != 1)
			{
				dIni = d;
				cont++;
			}
			else
			{
				dIni += incE;
			}
		}
		else
		{
			dIni += incNE;
			y += 1;
		}

		if(D)
		{
			Xaux = y;
			Yaux = x;
		}
		else
		{
			Xaux = x;
			Yaux = y;
		}

		if(S)
		{
			Yaux = Yaux * (-1);
		}


		x += 1;
		pontos = pushPonto(Xaux, Yaux);
	}
}

void quadrilateros(int x1, int y1, int x2, int y2)
{


}











