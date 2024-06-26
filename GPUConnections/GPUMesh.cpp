#include "GPUMesh.hh"
#include <math.h>

GPUMesh::GPUMesh()
{
	numPoints = NUMPOINTS;
	points = new vec4[numPoints];
	normals= new vec4[numPoints];
    textures = new vec2[numPoints];
    qDebug() << "Constructor de GPUMesh 1\n";
    type = GPUMaterialFactory::MATERIAL_TYPES::LAMBERTIAN;
	make();
}

GPUMesh::GPUMesh(const QString &fileName): Mesh(fileName)
{
    numPoints = NUMPOINTS;
    points = new vec4[numPoints];
    normals = new vec4[numPoints];
    textures = new vec2[numPoints];
    qDebug() << "Constructor de GPUMesh 2\n";
    type = GPUMaterialFactory::MATERIAL_TYPES::LAMBERTIAN;
    make();
}

GPUMesh::GPUMesh(const int npoints, const QString &fileName): Mesh(fileName)
{
    numPoints = npoints;
    points = new vec4[numPoints];
    normals = new vec4[numPoints];
    textures = new vec2[numPoints];
    qDebug() << "Constructor de GPUMesh 3\n";
    type = GPUMaterialFactory::MATERIAL_TYPES::LAMBERTIAN;
    make();
}


void GPUMesh::read(const QJsonObject &json) {
    numPoints = NUMPOINTS;
    points = new vec4[numPoints];
    normals= new vec4[numPoints];
    textures = new vec2[numPoints];

    Mesh::read(json);

    if(json.contains("material") && json["material"].isObject()){
        QJsonObject auxMat = json["material"].toObject();
        if(auxMat.contains("type") && auxMat["type"].isString()){
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

/**
 * @brief GPUMesh::~GPUMesh()
 */
GPUMesh::~GPUMesh() {

    if (points!= nullptr) delete points;
    if (normals!= nullptr) delete normals;
    if (textures!= nullptr) delete textures;
}

/**
 * @brief GPUMesh::toGPU
 * @param pr
 */
void GPUMesh::toGPU(shared_ptr<QGLShaderProgram> pr) {
    // TO  DO: A modificar a la fase 1 de la practica 2

    qDebug() << "Obj to GPU.....";

    program = pr;

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

    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal passar les normals a la GPU

    glBufferData( GL_ARRAY_BUFFER, sizeof(vec4)*Index + sizeof(vec4)*Index + sizeof(vec2)*Index, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vec4)*Index, points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec4)*Index, sizeof(vec4)*Index, normals );
    if(type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec4)*(2 * Index), sizeof(vec2)*Index, textures );
    }

    // set up vertex arrays
    glBindVertexArray( vao );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(vec4)*Index));
    glEnableVertexAttribArray(1);

    if(type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA){
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(vec4)*(2 * Index)));
        glEnableVertexAttribArray(2);
    }

}


/**
 * Pintat en la GPU.
 * @brief GPUMesh::draw
 */
void GPUMesh::draw(){

    glEnable( GL_DEPTH_TEST );
    glEnable(GL_TEXTURE_2D);

    // Aqui s'ha de fer el pas de dades a la GPU per si hi ha més d'un objecte
    // Activació a GL del Vertex Buffer Object.
    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal activar també les normals  a la GPU
    gpumaterial->toGPU(program);
    glBindVertexArray( vao );
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

    glDisable( GL_DEPTH_TEST );
    glDisable(GL_TEXTURE_2D);
}

/**
 * @brief GPUMesh::make
 */
void GPUMesh::make(){

    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal calcular la normal a cada vertex a la CPU

    qDebug() << "making gpu mesh\n";

    Index = 0;
    for(unsigned int i=0; i<cares.size(); i++){
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
            points[Index] = vertexs[cares[i].idxVertices[j]];
            normals[Index] = normalsVertexs[cares[i].idxNormals[j]];
            if(type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA && !Mesh::getIndirectMapping()){
                textures[Index] = textVertexs[cares[i].idxTextures[j]];
            }
            Index++;
        }
	}


    if(type == GPUMaterialFactory::MATERIAL_TYPES::MATERIALTEXTURA && Mesh::getIndirectMapping()){
        compute_indirect_mapping();
    }
}


/**
 * @brief GPUMesh::initTexture
 */
void GPUMesh::initTexture()
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

void GPUMesh::setTexture(shared_ptr<QOpenGLTexture> t){
   texture = t;
}

Capsa3D GPUMesh::calculCapsa3D()
{
    vec3    pmin, pmax;
    int     i;
    Capsa3D capsa;

    pmin.x = points[0].x;
    pmin.y = points[0].y;
    pmin.z = points[0].z;
    pmax = pmin;
	for(i=1; i<Index; i++) {
        if(points[i].x <pmin[0])
            pmin[0] = points[i].x;
        if(points[i].y <pmin[1])
            pmin[1] = points[i].y;
        if(points[i].z <pmin[2])
            pmin[2] = points[i].z;

        if(points[i].x >pmax[0])
            pmax[0] = points[i].x;
        if(points[i].y >pmax[1])
            pmax[1] = points[i].y;
        if(points[i].z >pmax[2])
            pmax[2] = points[i].z;
    }
    capsa.pmin = pmin;
    capsa.a = pmax[0]-pmin[0];
    capsa.h = pmax[1]-pmin[1];
    capsa.p = pmax[2]-pmin[2];
    return capsa;
}

void GPUMesh::compute_indirect_mapping(){
    // Center of the box
    Capsa3D capsa = GPUMesh::calculCapsa3D();

    vec3 c = vec3(capsa.pmin.x + (capsa.a)/2, capsa.pmin.y + (capsa.h)/2, capsa.pmin.z + (capsa.p)/2);

    //Vector del centre al vertex
    if (textures!= nullptr) delete textures;
    textures = new vec2[numPoints];

    for(int i = 0; i < Index; i++){
        vec3 c_vtx = vec3(points[i].x - c.x, points[i].y - c.y, points[i].z - c.z);
        float u = 0.5 - atan2(c_vtx.z, c_vtx.x)/2*M_PI;
        float v = 0.5 - asin(c_vtx.y)/M_PI;
        textures[i] = vec2(u,v);
    }
}

bool GPUMesh::hit(Ray& r, float tmin, float tmax, HitInfo& info)const {
    return false;
}

void GPUMesh::aplicaTG(shared_ptr<TG> tg) {
    qDebug() << "I'm animating the GPUMesh!";
    if (auto translateTG = dynamic_cast<TranslateTG*>(tg.get())) {
        qDebug() << "It's a translation!";
        for (int i = 0; i < vertexs.size(); i++) {
            this->vertexs[i] = tg->getTG() * this->vertexs[i];
        }

    }
    else if (auto scaleTG = dynamic_cast<ScaleTG*>(tg.get())) {
            qDebug() << "It's a scaling transformation!";
            for (int i = 0; i < vertexs.size(); i++) {
                this->vertexs[i] = tg->getTG() * this->vertexs[i];  // Apply scaling to each vertex
            }
        }
    make();
}
