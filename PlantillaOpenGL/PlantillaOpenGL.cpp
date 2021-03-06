// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

float posicionXTriangulo = 0.0f;
float posicionYTriangulo = 0.0f;

float angulo = 0.0f;

enum Direccion { Izquierda, Derecha, Arriba, Abajo };
Direccion direccionTrianguloH = Izquierda; //Horizontal
Direccion direccionTrianguloV = Abajo; //Vertical


void dibujarTriangulo() {
	//Utilizar una matrix identidad (para darle transformaciones)
	glPushMatrix();


	//Transformaciones (el orden importa)
	          //(angulo, x,     y,    z)
	/*glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(-0.25f, 0.0f, 0.0f);
	glScalef(0.2f, 0.2f, 0.2f);*/

	glTranslatef(posicionXTriangulo, posicionYTriangulo, 0.0f);
	glRotatef(angulo, 0.7f, 1.0f, 1.0f);
		   
	//Dibujar los vertices
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.8f, 0.0f);

	glVertex3f(-0.2f, -0.2f, 0);
	glVertex3f(0.2f, -0.2f, 0);
	glVertex3f(0.0f, 0.2f, 0);

	glEnd();
	
	//Soltar la matriz
	glPopMatrix();

}

void dibujar() {

	dibujarTriangulo();

}

void actualizar() {

	if (angulo >= 360){
		angulo = 0.0f;
	}
	angulo += 0.1f;

	if (direccionTrianguloH == Direccion::Izquierda) {
		if (posicionXTriangulo > -0.8f) {

			posicionXTriangulo -= 0.001f;

		}
		else {
			direccionTrianguloH = Direccion::Derecha;
		}
	}

	if (direccionTrianguloH == Direccion::Derecha) {
		if (posicionXTriangulo < 0.8f) {
			posicionXTriangulo += 0.001f;
		}
		else {
			direccionTrianguloH = Direccion::Izquierda;
		}
	}

	if (direccionTrianguloV == Direccion::Arriba) {
		if (posicionYTriangulo > -0.8f) {

			posicionYTriangulo -= 0.0005f;

		}
		else {
			direccionTrianguloV = Direccion::Abajo;
		}
	}

	if (direccionTrianguloV == Direccion::Abajo) {
		if (posicionYTriangulo < 0.8f) {

			posicionYTriangulo += 0.0005f;

		}
		else {
			direccionTrianguloV = Direccion::Arriba;
		}
	}
	
}

int main()
{

	//Declaramos apuntador de ventana
	GLFWwindow *window;

	//Si no se pudo iniciar glfw
	//terminamos ejecución
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	//Si se pudo iniciar GLFW
	//Entonces inicializamos la ventana
	window = glfwCreateWindow(1024,768,"Ventana",NULL,NULL);

	//Si no podemos iniciar la ventana 
	//Entonces terminamos ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto, activamos funciones modernas
	//Esto solo va a funcionar si ya establecido el contexto
	glewExperimental = true;
	GLenum errorGlew = glewInit();

	if (errorGlew != GLEW_OK) {

		cout << glewGetErrorString(errorGlew);

	}

	//Variable para la version de OPENGL
	const GLubyte *versionGL = glGetString(GL_VERSION);
	//Imprimir la variable
	cout << "Versión OPENGL: " << versionGL; //Salida de C++

	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establece region de dibujo
		glViewport(0, 0, 1024, 768);

		//Establece el color de borrado
		glClearColor(0.2, 0.2, 1, 1);
		
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();


		//Cambiar los buffers
		glfwSwapBuffers(window);

		//Reconocer si hay entradas
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;

}

