// Funcao que implementa bresenham (atividade a) e b))
void bresenham(double x1, double y1, double x2, double y2)
{
	double dx, dy, d, aux;
	double incE, incNE;
	double x, y;
	bool declive = false, simetrico = false;

	// calculo do delta
	dx = x2 - x1;
	dy = y2 - y1;

	// convertendo retas de positivos para negativos
	if (dx * dy < 0)
	{
		y1 = -y1;
		y2 = -y2;
		dy = -dy;
		simetrico = true;
	}

	// ajuste de troca do x por y em declive
	if(abs(dx) < abs(dy))
	{
		aux = y1;
		y1 = x1;
		x1 = aux;

		aux = y2;
		y2 = x2;
		x2 = aux;

		aux = dx;
		dx = dy;
		dy = aux;
		declive = true;
	}

	// ajuste para troca de extremos
	if(x1 > x2)
	{
		aux = x1;
		x1 = x2;
		x2 = aux;

		aux = y1;
		y1 = y2;
		y2 = aux;

		dx = -dx;
		dy = -dy;
	}

	d = 2 * dy - dx;
	incE = 2 * dy;
	incNE = 2 * (dy - dx);

	while(x1 < x2)
	{
		x = x1;
		y = y1;

		if(declive == true)
		{
			aux = x;
			x = y;
			y = aux;
		}

		if(simetrico == true)
		{
			y = -y;
		}

		if (d <= 0)
			d += incE;
		else
		{
			d += incNE;
			y1++;
		}
		
		x1 += 1;
		pontos = pushPonto(x, y);
	}


}