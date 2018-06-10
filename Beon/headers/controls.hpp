#ifndef CONTROLS_HPP
#define CONTROLS_HPP
#pragma once
#include <GLFW/glfw3.h>

class Controls{
private:
	// Initial position : on +Z
    glm::vec3 position; //Default = glm::vec3( 0, 0, 5 );
	// Initial horizontal angle : toward -Z
    float horizontalAngle; //Default = 3.14f;
	// Initial vertical angle : none
    float verticalAngle; //Default = 0.0f;
	// Initial Field of View 
    float initialFoV; //Default = 70.0f;

    float speed; //Default = 3.0f; // 3 units / second
    float mouseSpeed; //Default = 0.005f;

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
public:
    Controls();
	Controls(glm::vec3 pos, float hangle, float vangle, float mouseSense, float movspeed, float fov);
	~Controls();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void computeMatricesFromInputs(GLFWwindow* window);
	void initControl(glm::vec3 pos, float hangle, float vangle, float mouseSense, float speed, float fov);
};

#endif
