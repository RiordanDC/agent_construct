// Local Headers
#include "beon.hpp"
#include "shader.hpp"
#include "CameraController.hpp"
#include "model.hpp"
#include "Plane.hpp"
#include "objloader.hpp"
#include "Object.cpp"
#include "Render.hpp"

static bool running = true;

//define functions
void cleanup();
void render(const VertexBuffer& vb, const IndexBuffer& ib, Shader& shader);

WindowManager* Manager = WindowManager::getInstance();

int main()
{
    if(Manager->initWindow("Beon", 800, 600) == -1){
        std::cout << "Window failed to initialize." << std::endl;
        return -1;
    };

    GLFWwindow* window = Manager->getWindow();
    InitController(window, mWidth, mHeight);

    Render MainView(&camera, mWidth, mHeight);


    Shader mShader = Shader("shaders/TransformVertexShader.vert", "shaders/TextureFragmentShader.frag");
    //Shader mShader = Shader("StandardShading.vertexshader", "StandardShading.fragmentshader" );

    //Model crysis(GetCurrentWorkingDir()+"/nanosuit/nanosuit.obj", true);
    Object crysis(GetCurrentWorkingDir()+"/nanosuit/nanosuit.obj");
    crysis.AddShader("basic", mShader);

    std::cout << GetCurrentWorkingDir()+"/cube.obj" << std::endl;;
    
    mShader.use();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //Plane plane;
    //GLuint LightID = glGetUniformLocation(mShader.ID, "LightPosition_worldspace");


    // Game Loop //
    while (glfwWindowShouldClose(window) == false && running) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        getDeltaTime();
        updateController(window, deltaTime);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        MainView.Update();
        MainView.Draw(crysis);

        //glm::vec3 lightPos = glm::vec3(4,4,4);
        //mShader.setVec3("LightPosition_worldspace", lightPos.x, lightPos.y, lightPos.z);
        //crysis.Draw(mShader);
        
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

void render(const VertexBuffer& vb, const IndexBuffer& ib, Shader& shader){

}

void cleanup()
{
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
}


