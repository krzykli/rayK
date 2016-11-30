#pragma once
#include <stack>
#include <list>
#include "glm\glm.hpp"
#include "Transformation.h"
#include "Lambert.h"

using namespace glm;
class Material;

class Object3d
{
public:
    Object3d();

    virtual ~Object3d();

    const Transformation & GetTransform() const;

    void SetTransform(Transformation & in_transform);

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
    Transformation m_transform;
};

