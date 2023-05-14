//
// Created by anna on 20/01/2022.
//
#include "Texture.hh"

Texture::Texture(QString nomfitxer)
{
    success = image.load(nomfitxer);
    if (!success) std::cerr << "Imatge de textura no trobada" << endl;
}
Texture::~Texture() {

}

QImage Texture::getImage()
{
    return image;
}
