#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "utils.h"

#include <obj/model.h>

typedef struct Scene
{
    Model model[10];
    
    Material material;
    Material sky_material;
    Material ground_material;
    
    GLuint textures[10];

    float rotation;
} Scene;

typedef struct Particle
{
      float fLife;            // élettartam
      float fAlpha;           // átlátszóság
      float fFade;            // elhalványulás mértéke
      Color pColor;       // szín
      Material particle;
      float fSize;            // méret
      vec3 vPos;             // hely
      vec3 vSpeed;           // sebesség
      float fSum;           /* number of particle*/

} Particle;

void Add(Particle* particle);        // egy részecske hozzáadása

void object_reader(Scene* scene);
void texture_reader(Scene* scene);

struct Scene allmodel[1];
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
void draw_particle();

#endif /* SCENE_H */
