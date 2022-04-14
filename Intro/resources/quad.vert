#version 330
layout (location = 0) in vec3 loc;
layout (location = 1) in vec2 texloc_v;

out vec2 texloc_f;

void main(){
	gl_Position = vec4(loc.x, loc.y, loc.z, 1.0);
	texloc_f = texloc_v;
}