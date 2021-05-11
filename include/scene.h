#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "utils.h"

#include <obj/model.h>

typedef struct Scene
{
    Model model[15];
    
    Material material;
    Material sky_material;
    Material ground_material;
    
    GLuint textures[12];

    float rotation;
} Scene;


typedef struct Gollum
{
    Model animation_gollum[51];

    Material gollum_material;

    GLuint texture_gollum;
    
    float rotation;
    
    int last_frame_time;
    int last_frame_number;
    int time;

} Gollum;

typedef struct Fire
{
    Model animation_fire[3];

    Material fire_material;

    GLuint texture_fire;
    
    float rotation;
    
    int last_frame_time;
    int last_frame_number;
    int time;

} Fire;

typedef struct Particle
{
    Model particle;
    GLuint texture_particle;
    Material particle_material;
    float particle_size;           
    vec3 particle_pos;             
    vec3 particle_speed;           
    float rotation;
    int particle_time;
    int last_particle_time;
    int last_particle_number;

} Particle;

void object_reader(Scene* scene);
void texture_reader(Scene* scene);

void gollum_reader(Gollum* gollum);
void fire_reader(Fire* fire);

void draw_gollum(Gollum* gollum, Camera* camera);
void draw_fire(Fire* fire, Camera* camera);

void init_gollum(Gollum* gollum);
void init_fire(Fire* fire, Particle *particles, int numberOfParticles);

void update_gollum(Gollum* gollum);
void update_fire(Fire* fire);

void draw_particle(Particle *particles, Camera* camera, int numberOfParticles);
void update_particle(Particle *particles, int numberOfParticles);
/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

void set_lighting_fire();

/**
 * Set the current material.
 */
void set_material(const Material* material);
/**
 * Draw and update the scene objects.
 */
void update_scene(Scene* scene, double time);
/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */

#endif /* SCENE_H */
