#include "MaterialTextura.hh"

MaterialTextura::MaterialTextura(const vec3& color): Material()
{
    Kd = color;
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k):
    Material(a, d, s, k) {
}

MaterialTextura::MaterialTextura(const vec3& a, const vec3& d, const vec3& s, const float k, const float o):
    Material(a, d, s, k, o) {

}

MaterialTextura::~MaterialTextura()
{
}

vec3 MaterialTextura::getDiffuse(vec2 point) const {
    return Kd;
}

shared_ptr<Texture> MaterialTextura::getTextura() const {
    return textura;
}

bool MaterialTextura::scatter(const Ray& r_in, const HitInfo& rec, vec3& color, Ray & r_out) const  {
    vec3 target = rec.p + rec.normal + Hitable::RandomInSphere();
    r_out =  Ray(rec.p, target-rec.p);
    color = Kd;
    return false;
}

void MaterialTextura::read(const QJsonObject &json){
    Material::read(json);
    if (json.contains("textureFile") && json["textureFile"].isString())
        textura = make_shared<Texture>(json["textureFile"].toString());
}

void MaterialTextura::print(int indentation) const{
    const QString indent(indentation * 2, ' ');

    QTextStream(stdout) << "Material:" << "\n";

    QTextStream(stdout) << indent << "type:\t" << "MATERIALTEXTURA"<<"\n";

    Material::print(indentation);

}
