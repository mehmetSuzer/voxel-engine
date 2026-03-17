
#version 330

in vec3 positionOut;
in vec3 normalOut;
in vec2 uvOut;
flat in uint voxelOut;

out vec4 colourOut;

uniform vec3 lightPosition;
uniform vec3 lightColour;
uniform vec3 viewPosition;
uniform sampler2D textureAtlas;

vec3 GetShading()
{
    vec3 lightDirection = normalize(lightPosition - positionOut);
    vec3 viewDirection = normalize(viewPosition - positionOut);
    vec3 halfWayDirection = normalize(lightDirection + viewDirection);

    float shininess = 32.0f;

    float ambient = 0.2f;
    float diffuse = max(dot(lightDirection, normalOut), 0.0f);
    float specular = pow(max(dot(halfWayDirection, normalOut), 0.0f), shininess);

    return (ambient + diffuse + specular) * lightColour;
}

void main()
{
    float texCoordPerVoxel = 1.0f / 16.0f;
    
    uint row = voxel / 16;
    uint col = voxel % 16;

    vec2 texCoordInTextureAtlas = texCoordPerVoxel * (vec2(col, row) + uv);
    vec4 textureSample = texture(textureAtlas, texCoordInTextureAtlas);
    colourOut = vec4(textureSample.rgb * GetShading(), 1.0f);
}

