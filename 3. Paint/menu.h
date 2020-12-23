// Funcao para marcacao selecionada da cor no flood fill
void menufloodFillColors(int op)
{
	switch (op)
	{
		reta = false;
		quadrilatero = false;
		triangulo = false;
		poligono = false;
		circunferencia = false;
	case 0: // selecao para cor preto
		floodFillColor[0] = 0, floodFillColor[1] = 0, floodFillColor[2] = 0;
		break;
	case 1:  // selecao para cor vermelho
		floodFillColor[0] = 1, floodFillColor[1] = 0, floodFillColor[2] = 0;
		break;
	case 2:  // selecao para cor verde
		floodFillColor[0] = 0, floodFillColor[1] = 1, floodFillColor[2] = 0;
		break;
	case 3:  // selecao para cor azul
		floodFillColor[0] = 0, floodFillColor[1] = 0, floodFillColor[2] = 1;
		break;
	default:
		break;
	}
}

// Funcao para selecao de formatos para desenho
void menuPictures(int op)
{
	switch (op)
	{
	case 0:
		reta = true;
		quadrilatero = false;
		triangulo = false;
		poligono = false;
		circunferencia = false;
		floodFill_aux = false;
		break;
	case 1:
		reta = false;
		quadrilatero = true;
		triangulo = false;
		poligono = false;
		circunferencia = false;
		break;
	case 2:
		triangulo = true;
		reta = false;
		quadrilatero = false;
		poligono = false;
		circunferencia = false;
		floodFill_aux = false;
		break;
	case 3:
		reta = false;
		quadrilatero = false;
		triangulo = false;
		poligono = true;
		circunferencia = false;
		floodFill_aux = false;
		glutDetachMenu(GLUT_RIGHT_BUTTON);
		break;
	case 4:
		reta = false;
		quadrilatero = false;
		triangulo = false;
		poligono = false;
		circunferencia = true;
		floodFill_aux = false;
		break;
	default:
		break;


	}
	glutPostRedisplay();

}

// Funcao para marcacao da selecao do flood fill
void menuFloodFill(int op)
{
	switch (op)
	{
	case 0:
		reta = false;
		quadrilatero = false;
		triangulo = false;
		poligono = false;
		circunferencia = false;
		floodFill_aux = true;
		break;
	}
}