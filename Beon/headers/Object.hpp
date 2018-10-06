//World Object Class
#include <glm/glm.hpp>
#include "Renderable.hpp"

class Object: public Renderable{
	public:
		glm::mat4 Transformation;
		glm::vec3 Position;

		Object(string path){
			this->LoadModel(path);
			this->Transformation = glm::mat4(1.0);
			this->Position = glm::vec3(0.0);
		}

		void Update(float deltaTime){

		}

		void Render(){
			this->shader.use();
			this->shader.setMat4("Model", this->Transformation);
			this->ObjectModel.Draw(this->shader);
		}

		void SetPosition(glm::vec3 position){
			this->Transformation = glm::translate(this->Transformation, position);
		}

	private:
		Model ObjectModel;

		void LoadModel(string path){
			this->ObjectModel = Model(path, false);
		}
};
