#include "GPUMesh.hh"

GPUMesh::GPUMesh()
{
	numPoints = NUMPOINTS;
	points = new vec4[numPoints];
	normals= new vec4[numPoints];
    //colors = new vec4[numPoints];
	make();
}

GPUMesh::GPUMesh(const QString &fileName): Mesh(fileName)
{
    numPoints = NUMPOINTS;
    points = new vec4[numPoints];
    normals= new vec4[numPoints];
    //colors = new vec4[numPoints];
    make();
}

GPUMesh::GPUMesh(const int npoints, const QString &fileName): Mesh(fileName)
{
    numPoints = npoints;
    points = new vec4[numPoints];
    normals= new vec4[numPoints];
    //colors = new vec4[numPoints];
    make();
}

void GPUMesh::read(const QJsonObject &json) {
    numPoints = NUMPOINTS;
    points = new vec4[numPoints];
    normals= new vec4[numPoints];
    if(json.contains("material") && json["material"].isObject() ){
        QJsonObject auxMat = json["material"].toObject();
            if (auxMat.contains("type") && auxMat["type"].isString()) {
                QString tipus = auxMat["type"].toString().toUpper();
                gpumaterial->read(auxMat);
                qDebug() << gpumaterial->Ka.x <<" "<< gpumaterial->Ka.y <<" "<< gpumaterial->Ka.z  ;

            }
    }

    //colors = new vec4[numPoints];
    Mesh::read(json);
    make();
}

/**
 * @brief GPUMesh::~GPUMesh()
 */
GPUMesh::~GPUMesh() {

    if (points!= nullptr) delete points;
    if (normals!= nullptr) delete normals;
    //if (material!= nullptr) delete material;
}

/**
 * @brief GPUMesh::toGPU
 * @param pr
 */
void GPUMesh::toGPU(shared_ptr<QGLShaderProgram> pr) {
    // TO  DO: A modificar a la fase 1 de la practica 2

    qDebug() << "Obj to GPU.....";


    program = pr;
    // Creació d'un vertex array object

    glGenVertexArrays( 1, &vao );

    // Creacio i inicialitzacio d'un vertex buffer object (VBO)
    glGenBuffers( 1, &buffer );

    // Aqui s'ha de fer el pas de dades a la GPU per si hi ha més d'un objecte
    // Activació a GL del Vertex Buffer Object

    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal passar les normals a la GPU

    glBufferData( GL_ARRAY_BUFFER, sizeof(vec4)*Index + sizeof(vec4)*Index, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vec4)*Index, points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec4)*Index, sizeof(vec4)*Index_n, normals );
    //glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec4)*Index, sizeof(vec4)*Index, colors );

    // set up vertex arrays
    glBindVertexArray( vao );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(vec4)*Index));
    glEnableVertexAttribArray(1);
}


/**
 * Pintat en la GPU.
 * @brief GPUMesh::draw
 */
void GPUMesh::draw(){

    // Aqui s'ha de fer el pas de dades a la GPU per si hi ha més d'un objecte
    // Activació a GL del Vertex Buffer Object.
    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal activar també les normals  a la GPU
    gpumaterial->toGPU(program);
    glBindVertexArray( vao );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, Index );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);



}

/**
 * @brief GPUMesh::make
 */
void GPUMesh::make(){

    // TO  DO: A modificar a la fase 1 de la practica 2
    // Cal calcular la normal a cada vertex a la CPU

    static vec3  base_colors[] = {
        vec3( 1.0, 0.0, 0.0 ),
        vec3( 0.0, 1.0, 0.0 ),
        vec3( 0.0, 0.0, 1.0 ),
        vec3( 1.0, 1.0, 0.0 )
    };

    Index = 0;
    Index_n = 0;
    for(unsigned int i=0; i<cares.size(); i++){
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
            points[Index] = vertexs[cares[i].idxVertices[j]];
            //colors[Index] = vec4(base_colors[j%4], 1.0);
            Index++;
        }

        for(unsigned int j=0; j<cares[i].idxNormals.size(); j++){
            normals[Index_n] = normalsVertexs[cares[i].idxNormals[j]];
            Index_n++;
        }
	}
    qDebug() << "he enviat "<< Index_n <<"normals";
}


/**
 * @brief GPUMesh::initTexture
 */
void GPUMesh::initTexture()
 {
    // TO DO: A implementar a la fase 1 de la practica 2
    // Cal inicialitzar la textura de l'objecte: veure l'exemple del CubGPUTextura
    qDebug() << "Initializing textures...";

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

bool GPUMesh::hit(Ray& r, float tmin, float tmax, HitInfo& info)const {
    return false;
}

void GPUMesh::aplicaTG(shared_ptr<TG>){

}
