#include <QVector>
#include <QVector3D>

#include "Mesh.hh"

Mesh::Mesh(const QString &fileName): Object()
{
    nom = fileName;
    load(fileName);
    //material = new GPUMaterial
}


/**
 * @brief Mesh::~Mesh()
 */
Mesh::~Mesh() {
    if (cares.size() > 0) cares.clear();
    if (vertexs.size() > 0) vertexs.clear();
}

void Mesh::makeTriangles() {
    // Practica 1: TO DO Fase 1: A implementar
}


bool Mesh::hit(Ray &raig, float tmin, float tmax, HitInfo& info) const {

    // Practica 1: TODO Fase 1: A implementar
    return false;

}


void Mesh::aplicaTG(shared_ptr<TG> t) {
    // Codi de la p1:
    if (auto translateTG = dynamic_pointer_cast<TranslateTG>(t)) {
        for (int i = 0; i < vertexs.size(); i++){ //v1 es un vec3 i un 1.0f, com es veu al load
            vertexs[i] = translateTG->getTG() * vertexs[i];

        }
    } else if (auto scaleTG = dynamic_pointer_cast<ScaleTG>(t)) {
        vec3 scale = scaleTG->scaling;
        for (int i = 0; i < vertexs.size(); i++){ //v1 es un vec3 i un 1.0f, com es veu al load
            // suposem la mesh centrada en l'origen
            vec3 v1 = scale * (vec3(vertexs[i].x, vertexs[i].y, vertexs[i].z));
            vertexs[i] = vec4(v1, 1.f);
        }
    }
}

void Mesh::load (QString fileName) {
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    // if it’s a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                        // qDebug() << line.remove(0, 1).trimmed();
                    }

                    // if it’s a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        vertexs.push_back(vec4(lineParts.at(1).toFloat(),
                                               lineParts.at(2).toFloat(),
                                               lineParts.at(3).toFloat(), 1.0f));
                    }

                    // if it’s a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {
                        normalsVertexs.push_back (vec4(lineParts.at(1).toFloat(),
                                            lineParts.at(2).toFloat(),
                                            lineParts.at(3).toFloat(), 0.0f));
                    }
                    // if it’s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {
                        textVertexs.push_back(vec2(lineParts.at(1).toFloat(),
                                            lineParts.at(2).toFloat()));
                    }

                    // if it’s face data (f)
                    // there’s an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        Face *face = new Face();

                        // get points from v array
                        face->idxVertices.push_back(lineParts.at(1).split("/").at(0).toInt() - 1);
                        face->idxVertices.push_back(lineParts.at(2).split("/").at(0).toInt() - 1);
                        face->idxVertices.push_back(lineParts.at(3).split("/").at(0).toInt() - 1);
                        if(textVertexs.size() > 0) // check if really there are any UV coords
                        {
                            face->idxTextures.push_back( lineParts.at(1).split("/").at(1).toInt() - 1);
                            face->idxTextures.push_back( lineParts.at(2).split("/").at(1).toInt() - 1);
                            face->idxTextures.push_back( lineParts.at(3).split("/").at(1).toInt() - 1);
                        }

                        // get normals from vn array
                        face->idxNormals.push_back( lineParts.at(1).split("/").at(2).toInt() - 1);
                        face->idxNormals.push_back( lineParts.at(2).split("/").at(2).toInt() - 1);
                        face->idxNormals.push_back( lineParts.at(3).split("/").at(2).toInt() - 1);

                        // cara->calculaNormal();

                        cares.push_back(*face);
                    }

                }
            }
            file.close();
        } else {
            qWarning("Boundary object file can not be opened.");
        }
    } else  qWarning("Boundary object file not found.");
}

void Mesh::read (const QJsonObject &json)
{
    QTextStream(stdout) << "llegint a mesh";
    Object::read(json);
    if (json.contains("objFileName") && json["objFileName"].isString()) {
        nom = json["objFileName"].toString();
        load(nom);
    }
}

//! [1]
void Mesh::write(QJsonObject &json) const
{
    Object::write(json);
    json["objFileName"] = nom;
}
//! [1]

void Mesh::print(int indentation) const
{
    Object::print(indentation);
    const QString indent(indentation * 2, ' ');
    QTextStream(stdout) << indent << "objFileName:\t" << nom << "\n";
}



