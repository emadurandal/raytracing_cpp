//
//  sphere.h
//  MyRaytracing
//
//  Created by emadurandal on 2019/02/15.
//  Copyright © 2019 Yuki Shimada. All rights reserved.
//

#ifndef sphere_h
#define sphere_h

#include "hitable.h"
#include <Eigen/Dense>
using namespace Eigen;

class sphere: public hitable {
    public: sphere() {}
    sphere(Vector3f cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    Vector3f center;
    float radius;
    material *mat_ptr;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    Vector3f oc = r.origin() - center;
    float a = r.direction().dot(r.direction());
    float b = oc.dot(r.direction());
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - a * c;
    
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp; rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
            
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp; rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        
    }
    return false;
    
}

#endif /* sphere_h */
