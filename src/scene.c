#include "scene.h"
#include "string.h"

#include <GL/glut.h>

#include <math.h>
#include <obj/load.h>
#include <obj/draw.h>


void object_reader(Scene* scene)
{
    int i = 0;
    FILE *fp;
    char str[1000];
    char* filename = "data/objects/objloader.txt";
    char name[200];
    char *names;
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        
    }
   
    while (fgets(str, sizeof name, fp) != NULL){
        
        names = strtok(str," ");

        while( names != NULL ) {
           
            printf("%s\n", (char*)names );
        
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
    char str[1000];
    char* filename = "data/textures/texturesloader.txt";
    char name[200];
    char *names;
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        
    }
   
    while (fgets(str, sizeof name, fp) != NULL){
        
        names = strtok(str," ");

        while( names != NULL ) {
           
            printf("%s\n", (char*)names );
        
            scene->textures[i] = load_texture((char*)names);
            
            names = strtok(NULL, " ");
            i++;
        } 
    }
    
    fclose(fp);
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


void set_lighting()
{
    float diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

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
    glEnable(GL_TEXTURE_2D);
    set_material(&(scene->material));
    set_lighting();
    /*draw_particle();*/

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
    glBindTexture(GL_TEXTURE_2D, scene->textures[6]);
    draw_model(&(scene->model[6]));
    glPopMatrix();
    /*toilet*/
    glPushMatrix();
    glTranslatef(1.75, 7.87, 0);
    glRotatef(90, 50, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->textures[4]);
    draw_model(&(scene->model[4]));
    glPopMatrix();
    /*gollum*/
    glPushMatrix();
    glTranslatef(2.55, 5.87,0);
    glRotatef(90, 50, 1, 1);
    glBindTexture(GL_TEXTURE_2D, scene->textures[5]);
    draw_model(&(scene->model[5]));
    glPopMatrix();
    
}

void draw_help(int texture) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(1024, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(1024, 768, 0);

	glTexCoord2f(0, 1);
	glVertex3f(0, 768, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
    
}

void draw_particle()
{
    /*glBegin(GL_QUADS);

    glColor3f(1, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();*/

    glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(4, 0, 0);

	glTexCoord2f(4, 4);
	glVertex3f(4, 4, 0);

	glTexCoord2f(0, 1);
	glVertex3f(0, 4, 0);
	glEnd();
}