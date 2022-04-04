//
//  camera.h
//  MyRaytracing
//
//  Created by emadurandal on 2019/02/15.
//  Copyright © 2019 Yuki Shimada. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include "ray.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <Eigen/Dense>
using namespace Eigen;

#ifdef WIN32
#define drand48() (rand() / (RAND_MAX + 1.0))
#endif // WIN32


Vector3f random_in_unit_disk() {
    Vector3f p;
    
    do {
        p = 2.0 * Vector3f(drand48(), drand48(), 0) - Vector3f(1, 1, 0);
    } while (dot(p, p) >= 1.0);
    
    return p;
}


class camera {
public:
    camera(Vector3f lookfrom, Vector3f lookat, Vector3f vup, float vfov, float aspect, float aperture, float focus_dist) {
        lens_radius = aperture / 2;
        float theta = vfov * M_PI / 180;
        float half_height = tan(theta / 2);
        float half_width = aspect * half_height;
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
    }
    
    ray get_ray(float s, float t) {
        Vector3f rd = lens_radius * random_in_unit_disk();
        Vector3f offset = u * rd.x() + v * rd.y();
        return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
    }

    Vector3f origin;
    Vector3f lower_left_corner;
    Vector3f horizontal;
    Vector3f vertical;
    Vector3f u, v, w;
    float lens_radius;
};


#endif /* camera_h */
