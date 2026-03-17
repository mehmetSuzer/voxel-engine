
#version 330

layout (location = 0) in uint data;

out vec3 positionOut;
out vec3 normalOut;
out vec2 uvOut;
flat out uint voxelOut;

uniform vec3 position;
uniform mat4 view;
uniform mat4 projection;

const vec3 NORMALS[6] = {
    vec3( 1.0f,  0.0f,  0.0f), // Right
    vec3(-1.0f,  0.0f,  0.0f), // Left
    vec3( 0.0f,  1.0f,  0.0f), // Up
    vec3( 0.0f, -1.0f,  0.0f), // Down
    vec3( 0.0f,  0.0f,  1.0f), // Back
    vec3( 0.0f,  0.0f, -1.0f), // Front
};

const vec2 UV[4] = {
    vec2(0.0f, 0.0f), // Bottom Left
    vec2(1.0f, 0.0f), // Bottom Right
    vec2(1.0f, 1.0f), // Top Right
    vec2(0.0f, 1.0f), // Top Left
};

void main()
{
    uint x      =  data        &  63;
    uint y      = (data >>  6) &  63;
    uint z      = (data >> 12) &  63;
    uint voxel  = (data >> 18) & 127;
    uint normal = (data >> 25) &   7;
    uint uv     = (data >> 28) &   3;

    float chunkScale = 0.1f;
    vec3 position = chunkScale * vec3(x, y, z) + worldPosition;

    positionOut = position;
    normalOut = NORMALS[normal];
    uvOut = UV[uv];
    voxelOut = voxel;

    gl_Position = projection * view * vec4(position, 1.0f);
}

