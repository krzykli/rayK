#pragma once
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
        return m_pMat;
    }
    void SetMaterial(Material * pMat) {
        m_pMat = pMat;
    }


private:
    enum Type {
        LOCATION,
        CAMERA,
        POLYMESH,
        SUBDMESH,
        LIGHT,
    } m_type;

    Object3d * m_pParent;
    std::string m_name;
    std::list<Object3d *> m_children;
    Material * m_pMat;
};

