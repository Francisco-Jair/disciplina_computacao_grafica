// Funcao que implementa desenho de poligonos (atividade e))
// Para desenhar eh necessario utilizar um metodo de desenho de reta. 
// Foi utilizado o bresenham.
void drawPolygon(std::vector<double> pointsArray)
{
	// enquanto o array de pontos tiver as coordenadas do quarto clique
	for (int i = 0 ; i < pointsArray.size(); i = i + 2)
	{
		if(pointsArray.size() - 2 == i)
		{
			bresenham((int) pointsArray[i], (int) pointsArray[i + 1], (int) pointsArray[0], (int) pointsArray[1]);
		}
		else
			bresenham((int) pointsArray[i], (int) pointsArray[i + 1], (int) pointsArray[i + 2], (int) pointsArray[i + 3]);
	}
}

// Funcao que realiza processo de rasterizacao do poligono
void rasterizePolybon(double x1, double y1, double x2, double y2)
{
	double x;
	double Dx;
	double xmin;
	double y;
	double Dy;
	double ymin;
	double tamanho;

	int i = 1; // contador de tamanho

	if (abs(x2 - x1) >= abs(y2 - y1))
	{
		tamanho = abs(x2 - x1);
	}
	else
	{
		tamanho = abs(y2 - y1);
	}

	Dx = (x2 - x1) / tamanho;
	Dy = (y2 - y1) / tamanho;

	if (y1 < y2){
		ymin = y1;
	} else{
		ymin = y2;
	}

	if (x1 < x2){
		xmin = x1;
	}else{
		xmin = x2;
	}

	x = xmin;
	y = ymin;

	while(i <= tamanho)
	{
		pushPonto((int) x, (int) y);
		x = x + Dx;
		y = y + Dy;
		i++;
	}
}
