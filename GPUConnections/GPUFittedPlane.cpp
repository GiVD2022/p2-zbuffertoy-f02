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

//~GPUFittedPlane(){}

void GPUFittedPlane::make()
{
    Index = 0;
    // Triangle 1
    points[Index] = vertices[0]; normals[Index] = normal; Index++;
    points[Index] = vertices[1]; normals[Index] = normal; Index++;
    points[Index] = vertices[2]; normals[Index] = normal; Index++;
    // Triangle 2
    points[Index] = vertices[0]; normals[Index] = normal; Index++;
    points[Index] = vertices[2]; normals[Index] = normal; Index++;
    points[Index] = vertices[3]; normals[Index] = normal; Index++;

}

void GPUFittedPlane::toGPU(shared_ptr<QGLShaderProgram> p)
{
    qDebug() << "Obj to GPU.....";


    program = p;
    // Creació d'un vertex array object

    glGenVertexArrays( 1, &vao );

    // Creacio i inicialitzacio d'un vertex buffer object (VBO)
    glGenBuffers( 1, &buffer );

    // Aqui s'ha de fer el pas de dades a la GPU per si hi ha més d'un objecte
    // Activació a GL del Vertex Buffer Object

    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // Cal passar les normals a la GPU

    glBufferData( GL_ARRAY_BUFFER, sizeof(vec4)*Index + sizeof(vec4)*Index, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vec4)*Index, points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(vec4)*Index, sizeof(vec4)*Index_n, normals );

    // set up vertex arrays
    glBindVertexArray( vao );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(vec4)*Index));
    glEnableVertexAttribArray(1);

}
void GPUFittedPlane::draw()
{
    gpumaterial->toGPU(program);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, Index );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
bool GPUFittedPlane::hit(Ray& r, float tmin, float tmax, HitInfo& info) const
{
    return false;
}
void GPUFittedPlane::aplicaTG(shared_ptr<TG>){}

void GPUFittedPlane::read(const QJsonObject &json)
{
    FittedPlane::read(json);
    GPUObject::read(json);
    /*if(json.contains("material") && json["material"].isObject() ){
        QJsonObject auxMat = json["material"].toObject();
            if (auxMat.contains("type") && auxMat["type"].isString()) {
                QString tipus = auxMat["type"].toString().toUpper();
                gpumaterial->read(auxMat);
                qDebug() << gpumaterial->Ka.x <<" "<< gpumaterial->Ka.y <<" "<< gpumaterial->Ka.z  ;

            }
    }*/
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

void GPUFittedPlane::print(int indentation) const
{

}
