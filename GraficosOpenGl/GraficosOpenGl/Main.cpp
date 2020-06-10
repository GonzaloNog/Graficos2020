#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

using namespace std;

void Move(GLfloat* temp) {	for (int a = 0; a < 6; a++) {
		cout << *temp;
		*temp -= 0.1f;
		temp++;
	}}
//1
const GLchar* vertexSource = R"glsl(
#version 150 core
in vec2 position;
void main()
{
gl_Position = vec4(position, 0.0, 1.0);
}
)glsl";
//2
const GLchar* fragmentSource = R"glsl(
#version 150 core
out vec4 outColor;
void main()
{
outColor = vec4(1.0, 1.0, 0.0, 0.5);
}
)glsl";
//3
int main(int argc, char* argv[])
{
	//4
	glfwInit();
	//5
	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL", glfwGetPrimaryMonitor(), NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();
	//6
	GLfloat vertices[] =
	{
	0.5f, 0.5f,
	0.5f, -0.5f,
	-0.5f, -0.5f,
	-0.5f, 0.5f
	};
	//GLfloat* ver;
	/*ver = &vertices[0];
	for (int a = 0; a < 6; a++) {
		vertices[a] += 0.5f;	
	}*/
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//7
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	//8
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	//9
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);
	//10
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);	
		glfwPollEvents();
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glfwSwapBuffers(window);
	}
	//11
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &vbo);
}/*	- 1		In - define la etapa en el proceso cuando se ejecuta, en este caso se define en In el tamaño y la posicion		Versión 150 - esto define para que vercion de GLSL se debe compilar en este caso es para que el compilador compile en la vercion 1.5		o nos de un mensaje de error, en caso que nos e especifique la vercion se usara la 1.1		gl_Position -  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/gl_Position.xhtml	- 2		out - se ejecuta en la siguiente etapa y en este caso se usa para definir el color 		outColor - es una variable de tipo Vector4 en la cual asignamos el color que contendra nuestro shader						RGBA							R - red							G - green							B - blue							A - alpha / opacity	- 3		int main(int argc, char* argv[]) https://stackoverflow.com/questions/3024197/what-does-int-argc-char-argv-mean/3024202	- 4		glfInit() esta funcion inicializa la biblioteca GLFW https://www.glfw.org/docs/3.3/group__init.html#ga317aac130a235ab08c6db0834907d85e	- 5 		GLFWwindow crea una ventana, le podes pasar los parametros (acho, alto, nombre ventana, especificacion de la ventana, null)		https://www.glfw.org/docs/3.3/window_guide.html				glfwMakeContextCurrent genera el contexto para la ventana https://www.glfw.org/docs/3.3/group__context.html#ga1c04dc242268f827290fe40aa1c91157		glewExperimental = GL_TRUE; tiene que llamarse antes del glewInit(); y definirse en TRUE https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library		glewInit() inica Glew para poder usar OpenGL	- 6		GLfloat vertices[] array de float con los putnos de los vertices		GLuint vbo Un numero entero sin signo		glGenBuffers(1, &vbo); debuelve un numero entero que no haya utilizado como nombre de bufer		glBindBuffer crea o usa un bufer con un nombre int dado http://docs.gl/es2/glBindBuffer		glBufferData crea un nuevo almacén de datos para el bufer vinculado atraves de GL_ARRAY_BUFFER			Parametros				primero					Le pasamos el bufer que queremos suar, que esta en el array bufer				segudno					le decimos cuantos bytes va a tener el nuvo almacén de datos 				tercero 					Especificamos un puntero a los datos que se copiaron en el almacen de datos para la inicializacion 				cuarto 					Especifica el patrón de uso esperado del almacén de datos. La constante simbólica debe ser					GL_STREAM_DRAW, GL_STATIC_DRAWo GL_DYNAMIC_DRAW.					http://docs.gl/es2/glBufferData	- 7		glCreateShader Crea un shader y le pasamos el tipo de shader 			GL_VERTEX_SHADER 				es un sombreador diseñado para ejecutarse en el procesador de vértices programable			GL_FRAGMENT_SHADER 				es un sombreador diseñado para ejecutarse en el procesador de fragmentos programable			GL_COMPUTE_SHADERes 				un sombreador diseñado para ejecutarse en el procesador de cómputo programable.				glShaderSource implementa el codigo del shader (shader, cantidad de elementos del shader, puntero con el codigo que se carga en el shader)		http://docs.gl/es2/glShaderSourcehttp://docs.gl/es2/glShaderSource		glCompileShader compila el shader pasado	- 8		glCreateProgram crea un objeto vació y proporciona un medio para verificar la compatibilidad de los shader.		Por ejemplo verifica la compatibilidad entre un vertex shader y un fragment shader		glAttachShader(	Programa GLuint ,GLuint shader) agrega los elemntos que se suaran para crear el shader creando una lista		glLinkProgram vincula el shader al programa		glUseProgram le dice a openGl que el shader va a ser parte del programa		glGetAttribLocation - Devuelve la ubicación de una variable de atributo https://opengl.developpez.com/docs/man/man/glGetAttribLocation	- 9		glVertexAttribPointer especifica la ubicación y el formato de datos de la matriz de atributos de vértices http://docs.gl/es2/glVertexAttribPointer				glEnableVertexAttribArray - habilita o deshabilita una matriz genérica de atributos de vértices http://docs.gl/es2/glEnableVertexAttribArray	- 10		glfwWindowShouldClose(window), no dice si una ventana esta abierta o no devuelve True o False		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) Comprueba si se esta precionando la tecla Esc				glfwSetWindowShouldClose(window, GL_TRUE); Cierra una ventana dada		void glfwPollEvents	Esta función procesa solo aquellos eventos que ya están en la cola de eventos y luego regresa de inmediato. 		El procesamiento de eventos hará que se invoquen las devoluciones de llamada de ventana y entrada asociadas con esos eventos.		glClearColor(); limpia el color de buffer
				glClear(GL_COLOR_BUFFER_BIT); limpia el color de buffer y coloca el nuevo color establecido 		glDrawArrays Dibuja apartir de una matriz de datos http://docs.gl/es3/glDrawArrays		glfwSwapBuffers actualiza la pantalla	- 10 Destrulle todo lo creado para liverar la memoria antes de termianr el programa		*//*GLfloat vertices[] =
	{
	0.5f, 0.5f,
	0.5f, -0.5f,
	-0.5f, -0.5f,
	-0.5f, 0.5f
	};*/