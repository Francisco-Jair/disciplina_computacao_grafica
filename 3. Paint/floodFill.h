// Funcao que implementa floodfill com vizinhanca 4. (atividade i))
void floodFill(GLint x, GLint y, float* fillColor, float* bc)
{
	float color[3];
	glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
	if((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) && (
				color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2]))
	{
		glColor3f(fillColor[0], fillColor[1], fillColor[2]);
		cor1 = fillColor[0];
		cor2 = fillColor[1];
		cor3 = fillColor[2];
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
		pushPonto(x, y);
		glutSwapBuffers();
		floodFill(x + 1, y, fillColor, bc);
		floodFill(x - 2, y, fillColor, bc);
		floodFill(x, y + 2, fillColor, bc);
		floodFill(x, y - 2, fillColor, bc);
	}
}
