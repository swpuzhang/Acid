#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

layout(set = 0, binding = 0, rgba8) uniform writeonly image2D writeColour;

layout(set = 0, binding = 1) uniform sampler2D samplerColour;

layout(location = 0) in vec2 inUv;

void main() 
{
	vec3 textureColour = texture(samplerColour, inUv).rgb;
	vec4 colour = vec4(1.0f - textureColour, 1.0f);
	
	imageStore(writeColour, ivec2(inUv * imageSize(writeColour)), colour);
}
