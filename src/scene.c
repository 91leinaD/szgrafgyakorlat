#include "scene.h"

#include <GL/glut.h>

#include <math.h>
#include <obj/load.h>
#include <obj/draw.h>


void init_scene(Scene* scene)
{
    load_model(&(scene->ring), "data/objects/ring.obj");
    load_model(&(scene->sky), "data/objects/sky.obj");
    load_model(&(scene->ground), "data/objects/ground.obj"); 
    load_model(&(scene->house), "data/objects/house.obj");
    load_model(&(scene->toilet), "data/objects/toilet.obj");
    load_model(&(scene->gollum), "data/objects/gollum.obj");
    

    scene->texture_id = load_texture("data/textures/ring.png"); 
    scene->sky_texture_id = load_texture("data/textures/sky.png"); 
    scene->ground_texture_id = load_texture("data/textures/ground.png"); 
    scene->house_texture_id = load_texture("data/textures/house.jpg");
    scene->toilet_texture_id = load_texture("data/textures/toilet.jpg");
    scene->gollum_texture_id = load_texture("data/textures/gollum.jpg");

    /*rings*/
    scene->material.ambient.red = 0.24725;
    scene->material.ambient.green = 0.1995;
    scene->material.ambient.blue = 0.0745;

    scene->material.diffuse.red = 0.25164;
    scene->material.diffuse.green = 0.30648;
    scene->material.diffuse.blue = 0.22648;

    scene->material.specular.red = 0.628281;
    scene->material.specular.green = 0.555802;
    scene->material.specular.blue = 0.366065;

    scene->material.shininess = 51.2;
    
    /*sky*/
    scene->sky_material.ambient.red = 0.5;
    scene->sky_material.ambient.green = 0.5;
    scene->sky_material.ambient.blue = 0.5;

    scene->sky_material.diffuse.red = 0.5;
    scene->sky_material.diffuse.green = 0.5;
    scene->sky_material.diffuse.blue = 0.5;

    scene->sky_material.specular.red = 0.0;
    scene->sky_material.specular.green = 0.0;
    scene->sky_material.specular.blue = 0.0;

    scene->sky_material.shininess = 0.0;


    /*ground*/
    scene->ground_material.ambient.red = 0.2;
    scene->ground_material.ambient.green = 0.2;
    scene->ground_material.ambient.blue = 0.2;

    scene->ground_material.diffuse.red = 0.2;
    scene->ground_material.diffuse.green = 0.2;
    scene->ground_material.diffuse.blue = 0.2;

    scene->ground_material.specular.red = 0.0;
    scene->ground_material.specular.green = 0.0;
    scene->ground_material.specular.blue = 0.0;

    scene->ground_material.shininess = 0.0;

    
}

void set_lighting()
{
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene, double time)
{
    scene->rotation += 60 * time;
}

void draw_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    
    glPushMatrix();
    glTranslatef(-1,-4,0.9);
    glRotatef(scene->rotation, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    draw_model(&(scene->ring));
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2,3,0.9);
    glRotatef(scene->rotation, 0, 1, -1);
    draw_model(&(scene->ring));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.75, 7.87,0.45);
    glRotatef(scene->rotation, 0, 1, -1);
    draw_model(&(scene->ring));
    glPopMatrix();


    set_material(&(scene->sky_material));
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(180, 0, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->sky_texture_id);
    draw_model(&(scene->sky));
    glPopMatrix();

    set_material(&(scene->ground_material));
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(180, 0, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->ground_texture_id);
    draw_model(&(scene->ground));
    glPopMatrix();
    /*house*/
    glPushMatrix();
    glTranslatef(0, 0, 0.3);
    glRotatef(180, 0, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->house_texture_id);
    draw_model(&(scene->house));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.75, 7.87, 0);
    glRotatef(90, 50, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->toilet_texture_id);
    draw_model(&(scene->toilet));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.55, 5.87,0);
    glRotatef(90, 50, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->gollum_texture_id);
    draw_model(&(scene->gollum));
    glPopMatrix();
    
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}