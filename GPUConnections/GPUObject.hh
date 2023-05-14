#ifndef GPUOBJECT_HH
#define GPUOBJECT_HH

#include "Model/Modelling/Objects/Object.hh"
#include "GPUConnectable.hh"
#include "GPUMaterial.hh"
#include "GPUMaterialFactory.hh"

class GPUObject : public Object, public GPUConnectable,public QObject{
public:
    explicit GPUObject();
    virtual void read (const QJsonObject &json) override;
    ~GPUObject();
    virtual Capsa3D calculCapsa3D() = 0;
    virtual void print(int indentation) const override;

protected:
    shared_ptr<GPUMaterial> gpumaterial;
};

#endif // GPUOBJECT_HH
