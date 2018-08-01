// Local Headers
#include "beon.hpp"
#include "shader.hpp"
#include "CameraController.hpp"
//#include "model.hpp"
#include "Plane.hpp"

#include "objloader.hpp"

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


    Shader mShader = Shader("shaders/TransformVertexShader.vert", "shaders/TextureFragmentShader.frag");

    // Read our .obj file
    std::vector<unsigned short> indices;
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals; // Won't be used at the moment.
    bool res = loadOBJ("nanosuit.obj", vertices, uvs, normals);
    //bool res = loadAssImp("nanosuit.obj", indices, vertices, uvs, normals);
    //Warning, loadAssImp will load all the models pieces into differently indexed places. Each must be rendered individually
    //otherwise only the first one will be rendered. I.E. USe a VAO

    std::cout << vertices.size() << std::endl;

    /*
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) * 3, &vertices[0], GL_STATIC_DRAW);
    */
    VertexBuffer vb(&vertices[0], vertices.size() * sizeof(float) * 3);

    
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    vb.Bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    std::cout << GetCurrentWorkingDir()+"/cube.obj" << std::endl;;
    
    mShader.use();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //Plane plane;

    // Game Loop //
    while (glfwWindowShouldClose(window) == false && running) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        getDeltaTime();

        updateController(window, deltaTime);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mShader.use();
        updateCamera(mShader);

        //plane.Draw(mShader);

        glm::mat4 model(1.0);
        mShader.setMat4("model", model);

        //glBindVertexArray(vbo);
        vb.Bind();
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());



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


