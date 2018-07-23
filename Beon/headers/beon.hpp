#ifndef BEON
#define BEON
#pragma once


// GLAD Headers
#include <glad/glad.h>

//Local WindowManager header
#include "WindowManager.hpp"


// Include GLM
#include <glm/glm.hpp>
using namespace glm;

// System Headers
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <btBulletDynamicsCommon.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
//     #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastTime = 0.0f;

//Frames per second counter
double lastFrame = glfwGetTime();
int nbFrames = 0;
double printTimer = 4; //Print FPS every 4 seconds


void getDeltaTime(){
    double currentTime = glfwGetTime();
    nbFrames++;
    // per-frame time logic
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    if ((currentTime - lastFrame) >= printTimer ){
        // printf and reset timer
        printf("%f ms/frame\n", (printTimer*1000.0)/double(nbFrames));
        nbFrames = 0;
        lastFrame += printTimer;
    }
}

#endif
