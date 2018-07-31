#ifndef PLANE
#define PLANE
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Plane{
	public:
		Plane();
		void Draw(Shader &shader);
		void Move(float x, float y, float z);
		void Move(glm::vec4 _pos);
		unsigned int VBO;
		unsigned int VAO;
		unsigned int EBO;

		glm::vec3 scale;
		glm::vec3 pos;
		glm::vec3 axis;
		float angle;
		float x, y, z;

		GLuint vertexbuffer;
		std::vector<float> vertices;
		std::vector<unsigned int> indices;

};

void Plane::Move(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Plane::Move(glm::vec4 _pos)
{
	pos = _pos;
}

void Plane::Draw(Shader &shader)
{

	shader.use();
	glm::mat4 model(1.0);
	/*
	glm::mat4 translation = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));
	glm::mat4 rotation = glm::rotate(model, angle, axis);
	glm::mat4 scaling = glm::scale(model, scale);

	model = translation * rotation * scaling;
	*/
	shader.setMat4("model", model);

	glBindVertexArray(VBO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	
	glDrawArrays(GL_TRIANGLES, 0, 4 * 3);
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
	
	glBindVertexArray(0); // no need to unbind it every time 

}

Plane::Plane(){
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	pos = glm::vec4(glm::vec3(0.f, 0.f, 0.0f), 1.0);
	axis = glm::vec3(1.0f, 0.0f, 0.0f);
	angle = 0;

	//std::vector< glm::vec3 > vertices;
	//std::vector< glm::vec3 > vertices;
    vertices = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    indices = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    
    //glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    //glBindVertexArray(VAO);
	
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the IBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0); 

    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

#endif