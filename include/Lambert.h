#ifndef LAMBERTH
#define LAMBERTH

#include "Material.h"

class Lambert : public Material
{
public:
    Lambert();

    bool scatter(const Ray& ray, const hit_record& rec, Ray & bounce) const;
};

#endif // LAMBERTH
