    //
//  material.h
//  MyRaytracing
//
//  Created by emadurandal on 2019/02/15.
//  Copyright © 2019 Yuki Shimada. All rights reserved.
//

#ifndef material_h
#define material_h
#include <Eigen/Dense>
using namespace Eigen;

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, Vector3f& attenuation, ray& scattered) const = 0;
};

Vector3f random_in_unit_sphere() {
    Vector3f p;
    
    do {
        p = 2.0 * Vector3f(drand48(), drand48(), drand48()) - Vector3f(1, 1, 1);
    } while (p.squaredNorm() >= 1.0);
    
    return p;
    
}

class lambertian : public material {
public:
    lambertian(const Vector3f& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, Vector3f& attenuation, ray& scattered) const {
        Vector3f target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo; return true;
        
    }
    Vector3f albedo;
    
};

Vector3f reflect(const Vector3f& v, const Vector3f& n) {
    return v - 2 * v.dot(n) * n;
}

class metal : public material {
public:
    metal(const Vector3f& a, float f) : albedo(a) {
        if (f < 1) fuzz = f; else fuzz =1;
    }
    virtual bool scatter(const ray& r_in, const hit_record& rec, Vector3f& attenuation, ray& scattered) const {
        Vector3f reflected = reflect(r_in.direction().normalized(), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        
        return (scattered.direction().dot(rec.normal) > 0);
    }
    
    Vector3f albedo;
    float fuzz;
};


bool refract(const Vector3f& v, const Vector3f& n, float ni_over_nt, Vector3f& refracted) {
    Vector3f uv = v.normalized();
    float dt = uv.dot(n);
    float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    } else
        return false;
}

float schlick(float cosine, float ref_idx) {
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

class dielectric : public material {
public:
    dielectric(float ri) : ref_idx(ri) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, Vector3f& attenuation, ray& scattered) const {
        Vector3f outward_normal;
        Vector3f reflected = reflect(r_in.direction(), rec.normal);
        float ni_over_nt;
        attenuation = Vector3f(1.0, 1.0, 1.0);
        Vector3f refracted;
        float reflect_prob;
        float cosine;
        if (r_in.direction().dot(rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * r_in.direction().dot(rec.normal) / r_in.direction().norm();
        } else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -r_in.direction().dot(rec.normal) / r_in.direction().norm();
        } if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            reflect_prob = schlick(cosine, ref_idx);
        } else {
            reflect_prob = 1.0;
        } if (drand48() < reflect_prob) {
            scattered = ray(rec.p, reflected);
        } else {
            scattered = ray(rec.p, refracted);
        }
        return true;
    }
    
    float ref_idx;
};



#endif /* material_h */
