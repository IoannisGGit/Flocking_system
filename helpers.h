#pragma once

#include "ofMain.h"

using namespace glm;

float remapNoise(float x, float min, float max);
float remapNoise(float x);
float noiseWithOctaves(float x, int numOctaves);
float noiseWithOctaves(vec2 p, int numOctaves);
float noiseWithOctaves(vec3 p, int numOctaves);
float noiseWithOctaves(vec4 p, int numOctaves);
float noiseWithOctavesRemapped(float x, int numOctaves);
float noiseWithOctavesRemapped(vec2 p, int numOctaves);
float noiseWithOctavesRemapped(vec3 p, int numOctaves);
float noiseWithOctavesRemapped(vec4 p, int numOctaves);
float fourier(float x, int numHarmonics);
float bias(float x, float b);
float gain(float x, float g);
void calcNormals(ofMesh &curMesh);
void removeDuplicateVertices(ofMesh &curMesh, float threshold);
