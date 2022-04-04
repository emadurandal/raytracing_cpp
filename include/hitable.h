//
//  hitable.h
//  MyRaytracing
//
//  Created by emadurandal on 2019/02/15.
//  Copyright © 2019 Yuki Shimada. All rights reserved.
//

#ifndef hitable_h
#define hitable_h

#include "ray.h"
#include <Eigen/Dense>
using namespace Eigen;

class material;

struct hit_record {
    float t;
    Vector3f p;
    Vector3f normal;
    material *mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif /* hitable_h */
