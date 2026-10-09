
#pragma once

#include <cglm/cglm.h>

typedef struct PointLight
{
    vec3 colour;
    vec3 position;
    float linearCoef;
    float quadraticCoef;
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
    float linearCoef;
    float quadraticCoef;
    float cosInnerCutOff;
    float cosOuterCutOff;
} SpotLight;

