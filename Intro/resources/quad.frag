#version 330

out vec4 colour;
in vec2 texloc_f;

uniform sampler2D texsampler;

void main(){
	colour = texture(texsampler, texloc_f);
}
