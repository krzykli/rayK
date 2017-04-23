#include "stdafx.h"
#include "Scene.h"


bool Scene::hit(const Ray & ray, float t_min, float t_max, hit_record & rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;
    for (int i = 0; i < GetChildrenNumber(); i++)
    {
        if (IHitable * hitable = (IHitable *)(flatObjList[i]))
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


size_t Scene::GetChildrenNumber() const
{
    return sizeof(flatObjList) / sizeof(flatObjList[0]);
}


size_t Scene::GetLightsNumber() const
{
    return sizeof(lightList) / sizeof(lightList[0]);
}


void Scene::AddObject(void *obj, int index)
{
    objNumber++;
    flatObjList[index] = obj;
}

void Scene::AddLight(Light *obj, int index)
{
    lightNumber++;
    lightList[index] = obj;
}
