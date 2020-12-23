// Funcao que implementa desenho de triangulo (atividade d))
// Para desenhar eh necessario utilizar um metodo de desenho de reta. 
// Foi utilizado o bresenham.
void drawTriangle(std::vector<double> pointsArray)
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
