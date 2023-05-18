#ifndef GPUOBJECT_HH
#define GPUOBJECT_HH

#include "Model/Modelling/TG/TG.hh"
#include "Model/Modelling/TG/TranslateTG.hh"
#include "Model/Modelling/TG/ScaleTG.hh"
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
    virtual void aplicaTG(shared_ptr<TG>) override = 0 ;
    bool translation = false;
    bool scale = false;

protected:
    shared_ptr<GPUMaterial> gpumaterial;

};

#endif // GPUOBJECT_HH
