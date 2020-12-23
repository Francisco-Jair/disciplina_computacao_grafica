// Funcao que implementa desenho de quadrilatero (atividade c))
void drawQuadrilateral(std::vector<double> pointsArray)
{
	for(int i = 0; i < pointsArray.size(); i = i + 2)
	{
		bresenham((int) pointsArray[i], (int) pointsArray[i + 1], (int) pointsArray[i], (int) pointsArray[i + 3]);
		bresenham((int) pointsArray[i], (int) pointsArray[i + 3], (int) pointsArray[i + 2], (int) pointsArray[i + 3]);
		bresenham((int) pointsArray[i + 2], (int) pointsArray[i + 3], (int) pointsArray[i + 2], (int) pointsArray[i + 1]);
		bresenham((int) pointsArray[i + 2], (int) pointsArray[i + 1], (int) pointsArray[i], (int) pointsArray[i + 1]);
		break;
	}
}
