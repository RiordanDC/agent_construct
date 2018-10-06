//Renderable Object
#include "shader.hpp"
#include <map>
#include <string>

class Renderable{
public:
	bool visable;
	std::map<string, Shader*> shaders;
	Shader shader;

	Renderable(){
		this->visable = true;
		this->shader = Shader();
	}

	void AddShader(string name, Shader shader){
		this->shaders[name] = &shader;
		this->shader = shader;
	}

	Shader* GetShader(string name){
		return this->shaders[name];
	}
};