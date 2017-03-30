#ifndef OBJECT3DH
#define OBJECT3DH

#include <stack>
#include <list>
#include "vec3.h"
#include "Lambert.h"

class Material;

class Object3d
{
public:
    Object3d();

    virtual ~Object3d();

    void SetParent(Object3d *parent);

    Object3d const * GetParent() const;

    void SetName(const std::string &in_name);

    const std::string & GetName() const;

    std::list<Object3d *> GetChildren() const;

    Material * GetMaterial() const {
        return pMat;
    }
    void SetMaterial(Material * pMat) {
        pMat = pMat;
    }


private:
    enum Type {
        LOCATION,
        CAMERA,
        POLYMESH,
        SUBDMESH,
        LIGHT,
    } type;

    Object3d * pParent;
    std::string name;
    std::list<Object3d *> children;
    Material * pMat;
};

#endif // OBJECT3DH
