// Funcao responsavel por rasterizar (desenhar) circunferencia de raio definido 
// em variavel padrao. Atividade (h))
void rasterizeCircumference(double x1, double y1, double Raio)
{
	double x;
	double y;
	double d;
	double deltaE;
	double deltaSE;

	if(x1 != 0 && y1 != 0)
	{
		d = 1 - Raio;
		deltaE = 3;
		deltaSE = -2 * Raio + 5;
		x = 0, y = Raio;
		
		pontos = pushPonto(x1, y1 + (int) Raio);
		pontos = pushPonto(x1, y1 - (int) Raio);
		pontos = pushPonto(x1 + (int) Raio, y1);
		pontos = pushPonto(x1 - (int) Raio, y1);

		while(y > x)
		{
			if (d < 0)
			{
				d += deltaE;
				deltaE += 2;
				deltaSE += 2;
			}
			else
			{
				d += deltaSE;
				deltaE += 2;
				deltaSE += 4;
				y--;
			}

			x++;
			pontos = pushPonto((int)x + x1, (int) y + y1);
			pontos = pushPonto((int)y + x1, (int) x + y1);
			pontos = pushPonto((int)y + x1, (int) - x + y1);
			pontos = pushPonto((int)x + x1, (int) - y + y1);
			pontos = pushPonto((int) - x + x1, (int) - y + y1);
			pontos = pushPonto((int) - y + x1, (int) - x + y1);
			pontos = pushPonto((int) - y + x1, (int) x + y1);
			pontos = pushPonto((int) - x + x1, (int) y + y1);
		}
	}

}