#include "callbacks.h"
#include "scene.h"

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

int help, help_on = 0;
int iscrouch = 0;

struct {
    int x;
    int y;
} mouse_position;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
       
    glPushMatrix();
    set_view(&camera);
    draw_scene(&scene);
    glPopMatrix();

    if (is_preview_visible) {
        show_texture_preview();
    }
    
    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);
}

void mouse(int button, int state, int x, int y)
{
    
    mouse_position.x = x;
    mouse_position.y = y;
}

void motion(int x, int y)
{
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    /* two variables to store X and Y coordinates, as observed from the center
      of the window
    */
    int dev_x,dev_y;
    dev_x = (1024/2)-x;
    dev_y = (768/2)-y;

    /* apply the changes to pitch and yaw*/
    mouse_position.x+=(float)dev_x;
    mouse_position.y+=(float)dev_y;
    
    rotate_camera(&camera, (mouse_position.x), mouse_position.y);
    
    
    mouse_position.x = 0;
    mouse_position.y = 0;
    
}
void SpecialKeyHandler(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_F1:
            printf("semmi");
            break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
        set_camera_speed(&camera, 1);
        break;
    case 's':
        set_camera_speed(&camera, -1);
        break;
    case 'a':
        set_camera_side_speed(&camera, 1);
        break;
    case 'd':
        set_camera_side_speed(&camera, -1);
        break;
    case 'm':
        if (is_preview_visible) {
            is_preview_visible = FALSE;
        }
        else {
            is_preview_visible = TRUE;
        }
        break;
    case 'x':
        set_camera_speed(&camera, 2.5);
        break;
    case 'c':
        if (iscrouch == 0) {
            iscrouch = 1;
            crouch(&camera, iscrouch);
        }
        else {
            iscrouch = 0;
            crouch(&camera, iscrouch);
        }
		break;
     case 32:
	        jump(&camera);
            printf("semmi");
	    break;
    case '+':

		break;
	case '-':	

		break;
    case 27:
		    exit(0);
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key) {
    case 'x':
        set_camera_speed(&camera, 1);
        break;
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
    case 32:
	    jump_stop(&camera);
        break;
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time);
    update_scene(&scene, elapsed_time);
    glutWarpPointer(1024/2,768/2);
    glutPostRedisplay();
}
