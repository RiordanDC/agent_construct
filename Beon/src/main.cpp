// Local Headers
#include "beon.hpp"
#include "shader.hpp"
#include "CameraController.hpp"
#include "model.hpp"
#include "Plane.hpp"

#include "objloader.hpp"

static bool running = true;

//define functions
void cleanup();
void render(std::vector<glm::vec3>& vertices, GLuint vertexbuffer, Shader& shader);

WindowManager* Manager = WindowManager::getInstance();

int main()
{
    if(Manager->initWindow("Beon", 800, 600) == -1){
        std::cout << "Window failed to initialize." << std::endl;
        return -1;
    };

    GLFWwindow* window = Manager->getWindow();
    InitController(window, mWidth, mHeight);


    Shader mShader = Shader("shaders/TransformVertexShader.vert", "shaders/TextureFragmentShader.frag");

    // Read our .obj file
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals; // Won't be used at the moment.
    bool res = loadOBJ("cube.obj", vertices, uvs, normals);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    std::cout << GetCurrentWorkingDir()+"/cube.obj" << std::endl;;

    Plane plane;
    plane.Move(0, 0, -5);
    plane.axis = glm::vec3(1.f,0.f,0.f);
    float x = 0;
    //mShader.use();

    // Game Loop //
    while (glfwWindowShouldClose(window) == false && running) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        getDeltaTime();

        updateController(window, deltaTime);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        updateCamera(mShader);


        //plane.Move(0,0,x);
        //plane.angle += 0.5 * deltaTime;
        //x += 0.5 * deltaTime;
        plane.Draw(mShader);


        /*
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        glm::mat4 model(1.0);
        mShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        */
        render(vertices, vertexbuffer, mShader);
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);

    cleanup();
    return 0;
}

void render(std::vector<glm::vec3>& vertices, GLuint vertexbuffer, Shader& shader){
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glm::mat4 model(1.0);
    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void cleanup()
{
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}



