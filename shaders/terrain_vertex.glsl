
#version 330

layout (location = 0) in uint data;

out vec3 positionOut;
out vec3 normalOut;
out vec2 uvOut;
flat out uint voxelOut;

uniform vec3 chunkPosition;
uniform mat4 view;
uniform mat4 projection;

const vec3 NORMALS[6] = vec3[6](
    vec3( 1.0f,  0.0f,  0.0f), // Right
    vec3(-1.0f,  0.0f,  0.0f), // Left
    vec3( 0.0f,  1.0f,  0.0f), // Up
    vec3( 0.0f, -1.0f,  0.0f), // Down
    vec3( 0.0f,  0.0f,  1.0f), // Back
    vec3( 0.0f,  0.0f, -1.0f)  // Front
);

const vec2 UV[4] = vec2[4](
    vec2(0.0f, 0.0f), // Lower Left
    vec2(1.0f, 0.0f), // Lower Right
    vec2(1.0f, 1.0f), // Upper Right
    vec2(0.0f, 1.0f)  // Upper Left
);

void main()
{
    uint x      =  data         &  63u;
    uint y      = (data >>  6u) &  63u;
    uint z      = (data >> 12u) &  63u;
    uint voxel  = (data >> 18u) & 127u;
    uint normal = (data >> 25u) &   7u;
    uint uv     = (data >> 28u) &   3u;
 
    vec3 position = vec3(x, y, z) + chunkPosition;

    positionOut = position;
    normalOut = NORMALS[normal];
    uvOut = UV[uv];
    voxelOut = voxel;

    gl_Position = projection * view * vec4(position, 1.0f);
}

