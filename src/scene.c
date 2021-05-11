#include "scene.h"
#include "callbacks.h"
#include "camera.h"
#include "string.h"

#include <GL/glut.h>

#include <math.h>
#include <obj/load.h>
#include <obj/draw.h>

int sorszam =0;
void object_reader(Scene* scene)
{
    int i = 0;
    FILE *fp;
    char str[10000];
    char* filename = "data/objects/objloader.txt";
    char name[2000];
    char *names;
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename); 
    }
   
    while (fgets(str, sizeof name, fp) != NULL){
        
        names = strtok(str," ");

        while( names != NULL ) {
           
            /*printf("%s\n", (char*)names );*/
        
            load_model(&(scene->model[i]), (char*)names);
        
            names = strtok(NULL, " ");

            i++;
        } 
    }
    
    fclose(fp);
}

void texture_reader(Scene* scene)
{
    int i = 0;
    FILE *fp;
    char str[10000];
    char* filename = "data/textures/texturesloader.txt";
    char name[2000];
    char *names;
    fp = fopen(filename, "r");
    if (fp == NULL){

        printf("Could not open file %s",filename);   

    }
   
    while (fgets(str, sizeof name, fp) != NULL){
        
        names = strtok(str," ");

        while( names != NULL ) {
           
            /*printf("%s\n", (char*)names );*/
        
            scene->textures[i] = load_texture((char*)names);
            
            names = strtok(NULL, " ");

            i++;
        } 
    }
    
    fclose(fp);
}

void gollum_reader(Gollum* gollum)
{
    int i = 0;
    FILE *fp;
    char str[10000];
    char* filename = "data/animation/gollum.txt";
    char name[2000];
    char *names;
    fp = fopen(filename, "r");
    if (fp == NULL){

        printf("Could not open file %s",filename);
        
    }
   
    while (fgets(str, sizeof name, fp) != NULL){
        
        names = strtok(str," ");

        while( names != NULL ) {
           
            /*printf("%s\n", (char*)names );*/
        
            load_model(&(gollum->animation_gollum[i]), (char*)names);
        
            names = strtok(NULL, " ");

            i++;
        } 
    }

    gollum->texture_gollum = load_texture("data/animation/gollum.jpg");
    
    fclose(fp);
}

void fire_reader(Fire* fire)
{
    int i = 0;
    FILE *fp;
    char str[10000];
    char* filename = "data/animation/fire.txt";
    char name[2000];
    char *names;
    fp = fopen(filename, "r");

    if (fp == NULL){
        printf("Could not open file %s",filename);
        
    }
   
    while (fgets(str, sizeof name, fp) != NULL){
        
        names = strtok(str," ");

        while( names != NULL ) {
           
            /*printf("%s\n", (char*)names );*/
        
            load_model(&(fire->animation_fire[i]), (char*)names);
        
            names = strtok(NULL, " ");

            i++;
        } 
    }

    fire->texture_fire = load_texture("data/animation/fire.png");
    
    fclose(fp);
}


void init_gollum(Gollum* gollum)
{
    gollum_reader(gollum);

    gollum->gollum_material.ambient.red = 0.2;
    gollum->gollum_material.ambient.green = 0.2;
    gollum->gollum_material.ambient.blue = 0.2;

    gollum->gollum_material.diffuse.red = 0.2;
    gollum->gollum_material.diffuse.green = 0.2;
    gollum->gollum_material.diffuse.blue = 0.2;

    gollum->gollum_material.specular.red = 0.0;
    gollum->gollum_material.specular.green = 0.0;
    gollum->gollum_material.specular.blue = 0.0;

    gollum->gollum_material.shininess = 0.1;


}

void init_fire(Fire* fire, Particle *particles, int numberOfParticles)
{
    fire_reader(fire);

    set_lighting_fire();

    int i=0;
    for(i=0;i<numberOfParticles;i++)
    {
        load_model(&(particles[i].particle), ("data/objects/particle.obj"));
        particles[i].last_particle_time =0;
        particles[i].particle_pos.x = 0;
        particles[i].particle_pos.y = -1.25;
        particles[i].particle_pos.z = 0.3;
        particles[i].texture_particle = load_texture("data/animation/fire.png");
    }

    

    fire->fire_material.ambient.red = 0.8;
    fire->fire_material.ambient.green = 0.8;
    fire->fire_material.ambient.blue = 0.8;

    fire->fire_material.diffuse.red = 0.8;
    fire->fire_material.diffuse.green = 0.8;
    fire->fire_material.diffuse.blue = 0.8;

    fire->fire_material.specular.red = 0.8;
    fire->fire_material.specular.green = 0.8;
    fire->fire_material.specular.blue = 0.8;

    fire->fire_material.shininess = 0.2;

}

void init_scene(Scene* scene)
{
    object_reader(scene);
    texture_reader(scene);
   
   
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

void draw_gollum(Gollum* gollum, Camera* camera)
{   
    glEnable(GL_TEXTURE_2D);
    set_lighting();
    set_material(&(gollum->gollum_material));

    gollum->rotation = camera->rotation.z;
    glTranslatef(3.55, 4.87, 0.05);
    glRotatef(95, 10, 0, 0);
    glRotatef(gollum->rotation-90, 0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, gollum->texture_gollum);
    draw_model(&(gollum->animation_gollum[gollum->last_frame_number]));
}

void draw_fire(Fire* fire, Camera* camera)
{
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_COLOR );
    
    glEnable(GL_TEXTURE_2D);

    fire->rotation = (camera->rotation.z);
    
    set_material(&(fire->fire_material));
    glTranslatef(0, -1.25, 0.3);
    glRotatef(95, 10, 0, 0);
    glRotatef(fire->rotation-90, 0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, fire->texture_fire);
    draw_model(&(fire->animation_fire[fire->last_frame_number]));

    glDisable( GL_BLEND );
}

void draw_particle(Particle *particles, Camera* camera,int numberOfParticles)
{   
    glEnable(GL_TEXTURE_2D);

    glColor3f(1, 0.4, 0);
    int i =0;

    for(i=0;i<numberOfParticles;i++)
    {
        glPushMatrix();
        particles[i].rotation = (camera->rotation.z);
        glTranslatef(particles[i].particle_pos.x, particles[i].particle_pos.y, particles[i].particle_pos.z);
        glRotatef(95, 10, 0, 0);
        glRotatef(particles[i].rotation-90, 0, 1, 0);
        glBindTexture(GL_TEXTURE_2D, particles[i].texture_particle);
        draw_model(&(particles[i].particle));
        glPopMatrix();
    }
}

void draw_scene(const Scene* scene)
{
    glEnable(GL_TEXTURE_2D);
    set_material(&(scene->material));
    set_lighting();

    /*ring1*/
    glPushMatrix();
    glTranslatef(-1,-4,0.9);
    glRotatef(scene->rotation, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, scene->textures[0]);
    draw_model(&(scene->model[0]));
    glPopMatrix();
    /*ring2*/
    glPushMatrix();
    glTranslatef(-2,3,0.9);
    glRotatef(scene->rotation, 0, 1, -1);
    draw_model(&(scene->model[0]));
    glPopMatrix();
    /*ring3*/
    glPushMatrix();
    glTranslatef(1.75, 7.87,0.45);
    glRotatef(scene->rotation, 0, 1, -1);
    draw_model(&(scene->model[0]));
    glPopMatrix();

    /*skybox*/
    set_material(&(scene->sky_material));
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(180, 0, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->textures[1]);
    draw_model(&(scene->model[1]));
    glPopMatrix();
    /*ground*/
    set_material(&(scene->ground_material));
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(180, 0, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->textures[2]);
    draw_model(&(scene->model[2]));
    glPopMatrix();
    /*house*/
    glPushMatrix();
    glTranslatef(0, 0, 0.3);
    glRotatef(180, 0, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->textures[3]);
    draw_model(&(scene->model[3]));
    glPopMatrix();
    /*fireplace*/
    glPushMatrix();
    glTranslatef(0, -1.44, 0);
    glRotatef(180, 0, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->textures[5]);
    draw_model(&(scene->model[5]));
    glPopMatrix();
    /*toilet*/
    glPushMatrix();
    glTranslatef(1.75, 7.87, 0);
    glRotatef(90, 50, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->textures[4]);
    draw_model(&(scene->model[4]));
    glPopMatrix();
    
}

void draw_help(int texture) {

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glLoadIdentity();
    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.99, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1.99, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1.99, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1.99, -1.5, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
}

void update_gollum(Gollum* gollum)
{
    int frames_lenght = 52;
    double elapsed_time;
    
    int i = gollum->last_frame_number;
        
        gollum->time = glutGet(GLUT_ELAPSED_TIME);   
      
        elapsed_time = (double)(gollum->time - gollum->last_frame_time) / 100;

        if(i == (int)elapsed_time%frames_lenght)
        {
            i++;
           
        }
        if(i >= 51)
        {
             i=0;
            gollum->last_frame_time = gollum->time;
         }
         gollum->last_frame_number=i;   
}

void update_fire(Fire* fire)
{
    int frames_lenght = 3;
    double elapsed_time;
    
    int i = fire->last_frame_number;
        
        fire->time = glutGet(GLUT_ELAPSED_TIME);   
       
        elapsed_time = (double)(fire->time - fire->last_frame_time) / 500;
           
        if(i == (int)elapsed_time%frames_lenght)
        {
            i++;
        }
        if(i >= 3)
        {
             i=0;
            fire->last_frame_time = fire->time;
         }
         fire->last_frame_number=i;
  
}

void update_particle(Particle *particles, int numberOfParticles)
{
        double elapsed_time;
        
        particles[sorszam].particle_time = glutGet(GLUT_ELAPSED_TIME);
        if(particles[sorszam].last_particle_time==0){
            particles[sorszam].last_particle_time = particles[sorszam].particle_time;
        }
        
        elapsed_time = (double)((particles[sorszam].particle_time - particles[sorszam].last_particle_time)/10);
    
        if(sorszam == (int)elapsed_time%numberOfParticles)
        {   
            float random1 = (rand() % 10)+1;
            float random2 = (rand() % 10)+1;
            
            if((int)random1%2==0)
            {
                particles[sorszam].particle_pos.x+=(random1/(random2*25));
                particles[sorszam].particle_pos.z+=(random1/(random2*25));
            }
            else if((int)random2%2==0)
            {
                particles[sorszam].particle_pos.x-=(random1/(random2*25));
                particles[sorszam].particle_pos.z+=(random1/(random2*25));

            }
            
            if(particles[sorszam].particle_pos.z >= 0.6 || particles[sorszam].particle_pos.x >= 0.2 || particles[sorszam].particle_pos.x <= -0.2)
            {   
                particles[sorszam].particle_pos.x=0;
                particles[sorszam].particle_pos.z=0.3;
            }

            sorszam++;
            particles[sorszam].last_particle_time = particles[sorszam-1].particle_time;
            
        }
        
        if(sorszam >= numberOfParticles-1)
        {
            particles[0].last_particle_time = particles[sorszam-1].particle_time;
             sorszam=0;
            
         }
}
void update_scene(Scene* scene, double time)
{
    scene->rotation += 60 * time;
}


void set_lighting()
{
    float diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 8.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    float position_fire[] = { 0.0f, -1.25f, 0.3f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT1, GL_POSITION, position_fire);
}
void set_lighting_fire()
{
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };    
    float position_fire[] = { 0.0f, -1.25f, 0.4f, 1.0f };

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT1, GL_POSITION, position_fire);
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