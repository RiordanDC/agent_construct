#include "camera.hpp"
#include "shader.hpp"

class Render{
public:
	Camera* camera;
	int viewWidth;
	int viewHeight;

	Render(Camera *camera, int viewWidth, int viewHeight){
		this->camera = camera;
		this->viewWidth = viewWidth;
		this->viewHeight = viewHeight;
	}

	void Update(){
		this->camera->UpdateCamera(this->viewWidth, this->viewHeight);
	}

	void Draw(Object &object){
		this->UpdateShader(object.shader);
		object.Render();
	}


private:
	void UpdateShader(Shader shader){
        shader.setMat4("Projection", this->camera->ProjectionMatrix);

        shader.setMat4("View", this->camera->ViewMatrix);

        shader.setVec3("cameraPos", this->camera->Position);
	}

	void UpdateShader(Shader shader, glm::mat4 &ModelMatrix){

        glm::mat4 MVP = this->camera->ProjectionMatrix * this->camera->ViewMatrix * ModelMatrix;
        shader.setMat4("MVP", MVP);

        shader.setVec3("cameraPos", this->camera->Position);
	}

};