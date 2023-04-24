#pragma once

#include <vector>
#include "library/Common.h"

using namespace std;

typedef vec4 Vertices;
// Face - representa una cara d'un objecte 3D
class Face
{
 public:
    Face();

    // constructor a partir de 3 o 4 indexs a vertex
    Face(int i1, int i2, int i3, int i4=-1);

    vector<int> idxVertices;  // vector amb els indexs dels vertexs de la cara
    vector<int> idxNormals;
    vector<int> idxTextures;

    vec3 normal;
    void calculaNormal(vector<Vertices> &);
};


