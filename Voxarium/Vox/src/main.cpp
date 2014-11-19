#include <iostream>
#include <vector>
#include "../include/Octree.hpp"
#include "../include/Chunk.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#define TAILLE 1
#define PROFONDEUR 2


void makeCubes(std::vector<float> cubePosition){

    GLfloat cubePositionGL[cubePosition.size()];

    for(int i = 0; i < cubePosition.size(); ++i){
        cubePositionGL[i] = (GLfloat) cubePosition[i];
    }

    GLuint vboVertexPosition;
    GLuint vboCubePosition;
    //GLuint vboCubeColor;

    glGenBuffers(1, &vboVertexPosition);
    glGenBuffers(1, &vboCubePosition);
    //glGenBuffers(3, &vboCubeColor);

    glBindBuffer(GL_ARRAY_BUFFER, vboVertexPosition);

    GLfloat taille = TAILLE / (2<<(PROFONDEUR+1));

    GLfloat vertices[108] = { -taille, -taille, -taille,
                            taille, -taille, -taille,
                            -taille, taille, -taille,
                            taille, taille, -taille,
                            taille, -taille, -taille,
                            -taille, taille, -taille,

                            -taille, -taille, taille,
                            taille, -taille, taille,
                            -taille, taille, taille,
                            taille, taille, taille,
                            taille, -taille, taille,
                            -taille, taille, taille,

                            -taille, -taille, -taille,
                            taille, -taille, -taille,
                            -taille, -taille, taille,
                            taille, -taille, taille,
                            taille, -taille, -taille,
                            -taille, -taille, taille,

                            -taille, taille, -taille,
                            taille, taille, -taille,
                            -taille, taille, taille,
                            taille, taille, taille,
                            taille, taille, -taille,
                            -taille, taille, taille,

                            -taille, -taille, -taille,
                            -taille, taille, -taille,
                            -taille, -taille, taille,
                            -taille, taille, taille,
                            -taille, taille, -taille,
                            -taille, -taille, taille,

                            taille, -taille, -taille,
                            taille, taille, -taille,
                            taille, -taille, taille,
                            taille, taille, taille,
                            taille, taille, -taille,
                            taille, -taille, taille};

    glBufferData(   GL_ARRAY_BUFFER, 
                    108 * sizeof(GLfloat), 
                    vertices, 
                    GL_STATIC_DRAW );

    GLuint vaoVertexPosition;
    glGenVertexArrays(1, &vaoVertexPosition);
    glBindVertexArray(vaoVertexPosition);
    const GLuint vertexPositionIndex = 0;
    glEnableVertexAttribArray(vertexPositionIndex);
    glVertexAttribPointer(vertexPositionIndex, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0*sizeof(GLfloat));

    glBindBuffer(GL_ARRAY_BUFFER, vboCubePosition);

    glBufferData(   GL_ARRAY_BUFFER, 
                    cubePosition.size() * sizeof(GLfloat), 
                    cubePositionGL, 
                    GL_STATIC_DRAW );

    GLuint vaoCubePosition;
    glGenVertexArrays(1, &vaoCubePosition);
    glBindVertexArray(vaoCubePosition);
    const GLuint cubePositionIndex = 1;
    glEnableVertexAttribArray(cubePositionIndex);
    glVertexAttribPointer(cubePositionIndex, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0*sizeof(GLfloat));

    /*glBindBuffer(GL_ARRAY_BUFFER, vboCubeColor);

    glBufferData(   GL_ARRAY_BUFFER, 
                    cubePosition.size() * sizeof(GLfloat), 
                    cubePositionGL, 
                    GL_STATIC_DRAW );*/

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glVertexAttribDivisor(cubePositionIndex, 1);
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0, cubePosition.size()/3);
 }

using namespace glimac;

int main(int argc, char** argv) {

	voxarium::Chunk terrain = voxarium::Chunk();
	std::vector<float> vertice;
	terrain.root.getAllCoordinates(TAILLE, vertice);
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "Voxarium");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
    FilePath applicationPath(argv[0]);
    Program program = glimac::loadProgram(applicationPath.dirPath() + "Vox/shaders/color2D.vs.glsl",
                     applicationPath.dirPath() + "Vox/shaders/color2D.fs.glsl");
    program.use();


    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    
    makeCubes(vertice);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        // Update the display
        windowManager.swapBuffers();
    }

	return EXIT_SUCCESS;
}