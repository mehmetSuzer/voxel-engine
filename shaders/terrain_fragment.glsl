
#version 330

struct PointLight
{
    vec3 colour;
    vec3 position;
    float quadratic;
    float linear;
};

struct DirectionalLight
{
    vec3 colour;
    vec3 direction;
    float attenuation;
};

struct SpotLight
{
    vec3 colour;
    vec3 position;
    vec3 direction;
    float quadratic;
    float linear;
    float cosInnerCutoff;
    float cosOuterCutoff;
};

in vec3 positionOut;
in vec3 normalOut;
in vec2 uvOut;
flat in uint voxelOut;

out vec4 colourOut;

uniform PointLight pointLight;
uniform vec3 cameraPosition;
uniform sampler2D textureAtlas;

vec3 GetPointLighting(PointLight light)
{
    vec3 toLightPosition = light.position - positionOut;
    float distance = length(toLightPosition);

    vec3 lightDirection = toLightPosition / distance;
    vec3 viewDirection = normalize(cameraPosition - positionOut);
    vec3 halfWayDirection = normalize(viewDirection + lightDirection);

    float shininess = 32.0f;

    float ambient = 0.2f;
    float diffuse = max(dot(lightDirection, normalOut), 0.0f);
    float specular = pow(max(dot(halfWayDirection, normalOut), 0.0f), shininess);

    float attenuation = 1.0f / (distance * (distance * light.quadratic + light.linear) + 1.0f);

    return (ambient + attenuation * (diffuse + specular)) * light.colour;
}

vec3 GetDirectionalLighting(DirectionalLight light)
{
    vec3 viewDirection = normalize(cameraPosition - positionOut);
    vec3 halfWayDirection = normalize(viewDirection - light.direction);

    float shininess = 32.0f;

    float ambient = 0.2f;
    float diffuse = max(-dot(light.direction, normalOut), 0.0f);
    float specular = pow(max(dot(halfWayDirection, normalOut), 0.0f), shininess);

    return (ambient + light.attenuation * (diffuse + specular)) * light.colour;
}

vec3 GetSpotLighting(SpotLight light)
{
    vec3 toLightPosition = light.position - positionOut;
    float distance = length(toLightPosition);

    vec3 lightDirection = toLightPosition / distance;
    vec3 viewDirection = normalize(cameraPosition - positionOut);
    vec3 halfWayDirection = normalize(viewDirection + lightDirection);

    float shininess = 32.0f;

    float ambient = 0.2f;
    float diffuse = max(dot(lightDirection, normalOut), 0.0f);
    float specular = pow(max(dot(halfWayDirection, normalOut), 0.0f), shininess);

    float cosAngle = -dot(light.direction, lightDirection);
    float cosCutoffDifference = light.cosInnerCutoff - light.cosOuterCutoff;
    float intensity = clamp((cosAngle - light.cosOuterCutoff) / cosCutoffDifference, 0.0f, 1.0f);
    float attenuation = 1.0f / (distance * (distance * light.quadratic + light.linear) + 1.0f);
    attenuation *= intensity;

    return (ambient + attenuation * (diffuse + specular)) * light.colour;
}

void main()
{
    float texCoordPerVoxel = 1.0f / 16.0f;
    
    uint row = 15u - (voxelOut / 16u);
    uint col = voxelOut % 16u;

    vec2 texCoordInTextureAtlas = texCoordPerVoxel * (vec2(col, row) + uvOut);
    vec4 textureSample = texture(textureAtlas, texCoordInTextureAtlas);
    vec3 lighting = GetPointLighting(pointLight);
    colourOut = vec4(textureSample.rgb * lighting, 1.0f);
}

