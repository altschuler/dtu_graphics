#version 150
// 02561-03-01

uniform mat4 projection;
uniform mat4 modelView;
uniform float blendValue;
uniform float normalExtrusion;

in vec3 position1;
in vec3 color1;
in vec3 normal1;

in vec3 position2;
in vec3 color2;
in vec3 normal2;

out vec3 colorV;

vec3 blend(vec3 val1, vec3 val2) {
	return (1 - blendValue) * val1 + blendValue * val2;
}

void main (void) {
    colorV = blend(color1, color2);
    vec3 pos = blend(position1, position2);
	pos += normalExtrusion * blend(normal1, normal2);

    gl_Position = projection * modelView * vec4(pos, 1.0);
}
