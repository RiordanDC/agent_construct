#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

out vec4 FragColor;

void main(){

	// Output color = color of the texture at the specified UV
	//color = texture( myTextureSampler, UV ).rgb;
	FragColor = vec4(0.2f, 0.4f, 0.9f, 1.0f);
}
