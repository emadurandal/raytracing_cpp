//
//  main.cpp
//  MyRaytracing
//
//  Created by emadurandal on 2019/02/15.
//  Copyright © 2019 Yuki Shimada. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "material.h"
#include <limits>
#include <Eigen/Dense>
using namespace Eigen;


Vector3f color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec)) {
        ray scattered;
        Vector3f attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            auto col = color(scattered, world, depth + 1);
            return Vector3f(attenuation.x() * col.x(), attenuation.y() * col.y(), attenuation.z() * col.z());
        } else {
            return Vector3f(0, 0, 0);
        }
    } else {
        Vector3f unit_direction = r.direction().normalized();
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vector3f(1.0, 1.0, 1.0) + t * Vector3f(0.5, 0.7, 1.0);
    }
}

hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    list[0] = new sphere(Vector3f(0, -1000, 0), 1000, new lambertian( Vector3f(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = drand48();
            Vector3f center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
            if ((center - Vector3f(4, 0.2, 0)).norm() > 0.9) {
                if (choose_mat < 0.8) {// diffuse
                    list[i++] = new sphere(center, 0.2, new lambertian( Vector3f(drand48() * drand48(), drand48() * drand48(), drand48() * drand48())));
                } else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere( center, 0.2, new metal( Vector3f( 0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48()) ), 0.5 * drand48()));
                } else { // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }
    list[i++] = new sphere(Vector3f(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(Vector3f(-4, 1, 0), 1.0, new lambertian(Vector3f(0.4, 0.2, 0.1)));
    list[i++] = new sphere(Vector3f(4, 1, 0), 1.0, new metal(Vector3f(0.7, 0.6, 0.5), 0.0));
    
    return new hitable_list(list,i);
}
        

int main(int argc, const char * argv[]) {
    int nx = 200;
    int ny = 100;
    int ns = 100;
    std::ofstream outputfile("test.ppm");
    outputfile << "P3\n" << nx << " " << ny << "\n255\n";
    
    hitable *list[5];
    list[0] = new sphere(Vector3f(0,0,-1), 0.5, new lambertian(Vector3f(0.1, 0.2, 0.5)));
    list[1] = new sphere(Vector3f(0,-100.5,-1), 100, new lambertian(Vector3f(0.8, 0.8, 0.0)));
    list[2] = new sphere(Vector3f(1,0,-1), 0.5, new metal(Vector3f(0.8, 0.6, 0.2), 0.0));
    list[3] = new sphere(Vector3f(-1,0,-1), 0.5, new dielectric(1.5));
    list[4] = new sphere(Vector3f(-1,0,-1), -0.45, new dielectric(1.5));
    hitable *world = new hitable_list(list,5);
    world = random_scene();
        
    Vector3f lookfrom(3, 3, 2); Vector3f lookat(0, 0, -1);
    float dist_to_focus = (lookfrom - lookat).norm();
    float aperture = 2.0;
    camera cam(lookfrom, lookat, Vector3f(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);
    
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vector3f col(0, 0, 0);
            
            for (int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            col = Vector3f(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            outputfile << ir << " " << ig << " " << ib << "\n";
        }
    }
}
