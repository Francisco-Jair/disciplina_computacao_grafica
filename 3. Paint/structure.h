// VARIAVEIS DE USO GLOBAL

bool click1 = false;
bool click2 = false;
bool click3 = false;
bool click4 = false;
bool click5 = false;

// poligonos
bool reta = false;
bool quadrilatero = false;
bool triangulo = false;
bool poligono = false;
bool circunferencia = false;
double raio = 45;

bool aux = false;
bool floodFill_aux = false;

int cont1 = 4, cont2 = 4;

float cor1 = 0;
float cor2 = 0;
float cor3 = 0;
// cor selecionado pro flood fill
float floodFillColor[] = {0, 0, 0};

// vetor que guarda os pontos para desenho
std::vector<double> pointsArray;
int x_1, y_1, x_2, y_2;

// Largura e altura da janela (fixar esse tamanho e evitar usuário aumentar a tela)
int width = 1024, height = 600;

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
