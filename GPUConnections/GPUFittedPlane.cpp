#include "GPUFittedPlane.hh"

GPUFittedPlane::GPUFittedPlane()
{

}

GPUFittedPlane::GPUFittedPlane(vec3 pmin, vec3 pmax): FittedPlane(pmin, pmax)
{
    make();
}

GPUFittedPlane::GPUFittedPlane(const QString &fileName): FittedPlane(fileName)
{
    make();
}

GPUFittedPlane::~GPUFittedPlane(){} // no cal fer delete perque no s'ha fet new

void GPUFittedPlane::make()
{
    Index = 0;
    // Triangle 1
    points[Index] = vertices[0]; normals[Index] = normal;
    if (type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        textures[Index] = textVertexs[0];
    }
    Index++;
    points[Index] = vertices[1]; normals[Index] = normal;
    if (type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        textures[Index] = textVertexs[1];
    }
    Index++;
    points[Index] = vertices[2]; normals[Index] = normal;
    if (type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        textures[Index] = textVertexs[2];
    }
    Index++;
    // Triangle 2
    points[Index] = vertices[0]; normals[Index] = normal;
    if (type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        textures[Index] = textVertexs[0];
    }
    Index++;
    points[Index] = vertices[2]; normals[Index] = normal;
    if (type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        textures[Index] = textVertexs[2];
    }
    Index++;
    points[Index] = vertices[3]; normals[Index] = normal;
    if (type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        textures[Index] = textVertexs[3];
    }
    Index++;

}

void GPUFittedPlane::toGPU(shared_ptr<QGLShaderProgram> p)
{
    qDebug() << "Obj to GPU.....";


    program = p;

    if(type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        program->setUniformValue("hasTexture", true);
    } else {
        program->setUniformValue("hasTexture", false);
    }

    // Creació d'un vertex array object
    glGenVertexArrays( 1, &vao );

    // Creacio i inicialitzacio d'un vertex buffer object (VBO)
    glGenBuffers( 1, &buffer );

    // Aqui s'ha de fer el pas de dades a la GPU per si hi ha més d'un objecte
    // Activació a GL del Vertex Buffer Object

    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // Cal passar les normals a la GPU

    glBufferData( GL_ARRAY_BUFFER, sizeof(vec4)*6 + sizeof(vec4)*6 + sizeof(vec2)*6, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vec4)*6, points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec4)*6, sizeof(vec4)*6, normals );
    if(type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec4)*(2 * 6), sizeof(vec2)*6, textures );
    }

    // set up vertex arrays
    glBindVertexArray( vao );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(vec4)*6));
    glEnableVertexAttribArray(1);

    if(type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(vec4)*(2 * 6)));
        glEnableVertexAttribArray(2);
    }

}
void GPUFittedPlane::draw()
{
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_TEXTURE_2D);

    gpumaterial->toGPU(program);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    if(type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        glEnableVertexAttribArray(2);
        texture->bind(0);
        program->setUniformValue("texMap", 0);
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, Index );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    if(type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        glDisableVertexAttribArray(2);
    }

    //glDisable( GL_DEPTH_TEST );
    //glDisable(GL_TEXTURE_2D);
}
bool GPUFittedPlane::hit(Ray& r, float tmin, float tmax, HitInfo& info) const
{
    return false;
}
void GPUFittedPlane::aplicaTG(shared_ptr<TG>){}

void GPUFittedPlane::read(const QJsonObject &json)
{
    FittedPlane::read(json);

    if(json.contains("material") && json["material"].isObject() ){
        QJsonObject auxMat = json["material"].toObject();
            if (auxMat.contains("type") && auxMat["type"].isString()) {
                QString tipus = auxMat["type"].toString().toUpper();
                type = GPUMaterialFactory::getInstance().getMaterialType(tipus);
                gpumaterial = GPUMaterialFactory::getInstance().createMaterial(type);
                gpumaterial->read(auxMat);
            }
    }

    if(type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        initTexture();
    }

    make();
}

Capsa3D GPUFittedPlane::calculCapsa3D()
{
    int     i;
    Capsa3D capsa;

    capsa.pmin = pmin;
    capsa.a = pmax[0]-pmin[0];
    capsa.h = pmax[1]-pmin[1];
    capsa.p = pmax[2]-pmin[2];
    return capsa;
}

void GPUFittedPlane::initTexture()
 {
    // TO DO: A implementar a la fase 1 de la practica 2
    // Cal inicialitzar la textura de l'objecte: veure l'exemple del CubGPUTextura
    qDebug() << "Initializing textures...";

    // Carregar la textura
    glActiveTexture(GL_TEXTURE0);

    shared_ptr<GPUMaterialTextura> materialTextura = dynamic_pointer_cast<GPUMaterialTextura>(gpumaterial);
    if(materialTextura != nullptr){
        auto text = materialTextura->getTextura();
        auto image = text->getImage();
        texture = make_shared<QOpenGLTexture>(image.mirrored());
        texture->setWrapMode(QOpenGLTexture::Repeat);
        texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        texture->setMagnificationFilter(QOpenGLTexture::Linear);
        texture->bind(0);
    } else {
        qDebug() << "Fatal error initializing textures";
    }

 }

void GPUFittedPlane::print(int indentation) const
{

}
