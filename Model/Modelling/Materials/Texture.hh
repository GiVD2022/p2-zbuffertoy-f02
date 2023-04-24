//
// Created by anna on 20/01/2021.
//

#pragma once

#include <QImage>
#include <QColor>

#include <string>
#include <iostream>
#include "library/Common.h"


using namespace std;

class Texture
{
private:
    QImage image;
    bool success;

public:
    Texture(QString nomfitxer);
    virtual ~Texture();

    vec3 getColorPixel(vec2 uv);

};

