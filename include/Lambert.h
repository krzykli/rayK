#ifndef LAMBERTH
#define LAMBERTH

#include "Material.h"

struct Lambert : public Material
{
    Lambert();

    bool scatter(const Ray& ray, const hit_record& rec, Ray & bounce) const;
};

#endif // LAMBERTH
