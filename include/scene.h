#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <model.h>

typedef struct Scene
{
    Model ring;
    Model sky;
    Model Tree;
    Model ground;
    Model house;
    Model toilet;
    Model gollum;
    
    Material material;
    Material sky_material;
    Material ground_material;
    

    GLuint texture_id;
    GLuint ground_texture_id;
    GLuint sky_texture_id;
    GLuint house_texture_id;
    GLuint toilet_texture_id;
    GLuint gollum_texture_id;

    float rotation;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

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
void draw_origin();

#endif /* SCENE_H */
