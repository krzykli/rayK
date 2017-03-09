#include "stdafx.h"
#include "Scene.h"


bool Scene::hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (int i = 0; i < GetChildrenNumber(); i++)
    {
        if (IHitable * hitable = dynamic_cast<IHitable *>(m_flatObjList[i]))
        {
            if (hitable->hit(ray, t_min, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
    }
    return hit_anything;
}

unsigned int Scene::GetChildrenNumber() const
{
    return m_flatObjList.size();
}

void Scene::AddObject(Object3d * obj)
{
    m_objNumber++;
    m_flatObjList.push_back(obj);
}
