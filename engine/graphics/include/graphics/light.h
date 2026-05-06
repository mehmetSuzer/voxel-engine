
#pragma once

#include <cglm/cglm.h>

typedef struct PointLight
{
    vec3 colour;
    vec3 position;
    float quadratic;
    float linear;
} PointLight;

typedef struct DirectionalLight
{
    vec3 colour;
    vec3 direction;
    float attenuation;
} DirectionalLight;

typedef struct SpotLight
{
    vec3 colour;
    vec3 position;
    vec3 direction;
    float quadratic;
    float linear;
    float cosInnerCutOff;
    float cosOuterCutOff;
} SpotLight;

