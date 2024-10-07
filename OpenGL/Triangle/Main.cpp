#include<iostream>

// Biblioteca para cargar punteros a funciones de OpenGL
#include<glad/glad.h>

 // Biblioteca para crear ventanas y gestionar eventos
#include<GLFW/glfw3.h>

// Fuente del shader de vértices
// Se utiliza GLSL (OpenGL Shading Language) versión 330
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;  // Entrada de posición del vértice
layout (location = 1) in vec3 aColor;  // Entrada de color del vértice

out vec3 ourColor;  // Color que será pasado al fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);  // Calcula la posición del vértice en espacio de clip
    ourColor = aColor;  // Pasa el color al fragment shader
}
)";

// Fuente del shader de fragmento
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 ourColor;  // Entrada del color desde el vertex shader
out vec4 FragColor;  // Color de salida final del fragmento

void main()
{
    FragColor = vec4(ourColor, 1.0f);  // Asigna el color al fragmento, con alfa = 1.0
}
)";

int main() {

    // Inicialización de GLFW
    glfwInit();

    // Configuración del contexto de OpenGL (versión 3.3 y core profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crear ventana GLFW con dimensiones 800x800
    GLFWwindow* window = glfwCreateWindow(800, 800, "Colored Triangle", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Hacer que el contexto de la ventana creada sea el contexto actual de OpenGL
    glfwMakeContextCurrent(window);

    // Cargar todas las funciones de OpenGL utilizando GLAD
    gladLoadGL();

    // Especificar el tamaño del área de renderizado en la ventana
    glViewport(0, 0, 800, 800);

    // Crear y compilar el shader de vértices
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Crear y compilar el shader de fragmento
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Crear el programa de shader, adjuntar los shaders y enlazarlos
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Borrar shaders compilados ya que están enlazados al programa
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Definir los vértices de un triángulo y sus colores
    GLfloat vertices[] = {-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f, 0.87f, 0.0f, 0.0f, 0.0f, 1.0f};

    // Crear un VAO (Vertex Array Object) y un VBO (Vertex Buffer Object)
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Enlazar el VAO
    glBindVertexArray(VAO);

    // Enlazar el VBO y copiar los datos de los vértices al buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Especificar la estructura de los datos de posición de los vértices y activar los artibutos (colores)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Bucle de renderizado: se ejecuta hasta que la ventana es cerrada
    while (!glfwWindowShouldClose(window))
    {
        // Detectar si se ha presionado la tecla Escape para cerrar la ventana
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Limpiar la pantalla con un color gris oscuro
        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Usar el programa de shaders y dibujar el triángulo
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Intercambiar los buffers de la ventana para mostrar el renderizado actual
        glfwSwapBuffers(window);
        
        // Procesar eventos de entrada y salida de la ventana
        glfwPollEvents();
    }

    // Limpiar los recursos generados (VAO, VBO, programa de shaders)
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Destruir la ventana y terminar el contexto GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
