
#pragma once

#include <cglm/cglm.h>

typedef struct
{
    vec3 colour;
    vec3 position;
    float quadraticCoef;
    float linearCoef;
} PointLight;

typedef struct
{
    vec3 colour;
    vec3 direction;
    float intensity;
} DirectionalLight;

typedef struct
{
    vec3 colour;
    vec3 position;
    vec3 direction;
    float quadraticCoef;
    float linearCoef;
    float cosInnerCutOff;
    float cosOuterCutOff;
} SpotLight;

