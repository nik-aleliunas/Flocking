#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include "structures.h"

//#include "myVector.cpp"
/* local function declarations */
void display(void);
void init(void);
void keyboard (unsigned char key, int x, int y);
void glCircle3i(GLint x, GLint y, GLint radius);

#define PI 3.1415926
int W=700;  /* window width */
int H=700;  /* window height */
float time_step = 0.1;
float non_ran_freq = 1.3;
float non_ran_reset_strength = 1;
int randomness = 1;
int flash_stimulus = 1;
using namespace std;
std::vector<Firefly*> Fireflies_Stack;
int main (int argc, char** argv) {
  int win;
	int i = 0;
	srand(time(NULL));
  glutInit(&argc,argv);
	glutInitWindowSize(W,H);
  glutInitWindowPosition(0,0);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  win = glutCreateWindow("Fireflies");
  glutSetWindow(win);
  glutKeyboardFunc(keyboard);
  init();
  glutDisplayFunc(display);
	glutIdleFunc(display);
  glutMainLoop();
  return 0;
}

void keyboard (unsigned char key, int x, int y){
	GLint params[2];
	Firefly *firefly1;
	
	std::vector<Firefly*>::iterator it;
	switch(key){
		case 'q':
			exit(0);
			break;
	  case 'w':
		  while(Fireflies_Stack.empty()==false){
			  Fireflies_Stack.pop_back();
		}
		break;
	  case 'e':
		  while(Fireflies_Stack.empty()==false){
			Fireflies_Stack.pop_back();
		  }
		  for (int i = 0; i < 50; i++){
			firefly1 = new Firefly((float)(rand() % 1000)/3000 + 0.7, //r (0.7 to 1)
								   (float)(rand() % 1000)/3000 + 0.7, //g
								   (float)(rand() % 1000)/3000 + 0.7, //b
								   (float)((rand() - (RAND_MAX/2)) % 50), //x (-50 to 50)
								   (float)((rand() - (RAND_MAX/2)) % 50),	//y	
								   (float)((rand() - (RAND_MAX/2)) % 50), //z
								   (float)(rand() % 1000)*PI/500, //starting phase (0 and 2PI)
								   (float)((rand() - (RAND_MAX/2)) % 1000)/10000 + non_ran_freq, //frequency
								   (float)((rand() - (RAND_MAX/2)) % 1000)/10000 + non_ran_reset_strength, //resetting strength
								   (float)((rand() - (RAND_MAX/2)) % 1000)/2000, //velocity x y & z
								   (float)((rand() - (RAND_MAX/2)) % 1000)/2000,
								   (float)((rand() - (RAND_MAX/2)) % 1000)/2000);
			Fireflies_Stack.push_back(firefly1);
		  }
		  display();
		  break;
	  case 'r':
			if( randomness == 0)
				randomness = 1;
			else
				randomness = 0;
			printf("Randomness changed to %d\n", randomness);
			break;
		case 'f':
			if( flash_stimulus == 0)
				flash_stimulus = 1;
			else
				flash_stimulus = 0;
			printf("Flash Stimulus changed to %d\n", flash_stimulus);
			break;
		  
		case '[':
		if (non_ran_reset_strength > 0.1)
			  non_ran_reset_strength -= 0.1;
		  printf("Resetting Strength base changed to %f\n", non_ran_reset_strength);
		  break;
	  case ']':
		  non_ran_reset_strength += 0.1;
		  printf("Resetting Strength base changed to %f\n", non_ran_reset_strength);
		  break;
		case ';':
		  if (non_ran_freq > 0.1)
			  non_ran_freq -= 0.1;
		  printf("Frequency base changed to %f\n", non_ran_freq);
		  break;
		case '\'':
		  non_ran_freq += 0.1;
		  printf("Frequency base changed to %f\n", non_ran_freq);
		  break;
		case ',':
			if (Fireflies_Stack.empty() == false) {
				Fireflies_Stack.pop_back();
			}
			break;
		case '.':
			firefly1 = new Firefly((float)(rand() % 1000)/3000 + 0.7, //r (0.7 to 1)
														 (float)(rand() % 1000)/3000 + 0.7, //g
														 (float)(rand() % 1000)/3000 + 0.7, //b
														 (float)((rand() - (RAND_MAX/2)) % 50), //x (-50 to 50)
														 (float)((rand() - (RAND_MAX/2)) % 50),	//y	
														 (float)((rand() - (RAND_MAX/2)) % 50), //z
														 (float)(rand() % 1000)*PI/500, //starting phase (0 and 2PI)
														 (float)((rand() - (RAND_MAX/2)) % 1000)/10000 + non_ran_freq, //frequency
														 (float)((rand() - (RAND_MAX/2)) % 1000)/10000 + non_ran_reset_strength, //resetting strength
														 (float)((rand() - (RAND_MAX/2)) % 1000)/2000, //velocity x y & z
														 (float)((rand() - (RAND_MAX/2)) % 1000)/2000,
														 (float)((rand() - (RAND_MAX/2)) % 1000)/2000);
			Fireflies_Stack.push_back(firefly1);
			(*firefly1).print();
			printf("new firefly\n");
			display();
			break;
		default:
			break;
	}
}

void init() {
	glClearColor(0.0, 0.1, 0.1, 0.0);  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glColor3f(0.0, 0.1, .3);
	glBegin(GL_POLYGON);
	glVertex2f(-50.0, 100.0);
	glVertex2f(50, 100.0);
	glColor3f(0.0, 0.1, .3);
	glVertex2f(50, 0);
	glVertex2f(-50, 0);
	glEnd();
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10);
	//create a viewing volume, see pg 124 of OGL Programming book (Version1.1)
	//note: numbers should be proportional to window size
	
	glOrtho(-50.0/*left*/, 50.0/*right*/, -50.0/*bottom*/, 50.0/*top*/, -1.0/*near*/, 1.0/*far*/);
	//thus the center in screen x is 0, bottom in y is 0, top is 80;
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	int average = 0;
	float stimulus_change = 0;
	glOrtho(-50.0/*left*/, 50.0/*right*/, -50.0/*bottom*/, 50.0/*top*/, -1.0/*near*/, 1.0/*far*/);
	std::vector<Firefly*>::iterator it;
	std::vector<Firefly*>::iterator it2;
	for (it = Fireflies_Stack.begin(); it < Fireflies_Stack.end(); it++) {
		if ((*it)->flashed > 0) { 
			glColor3f((*it)->c.x(), (*it)->c.y(), (*it)->c.z());
			(*it)->flashed--;

		} else
			glColor4f(0,0,0,1);
		glCircle3i((*it)->place.x(), (*it)->place.y(), 1);
		glColor4f(0,0,0,1);
		glCircle3i((*it)->place.x()+1, (*it)->place.y(), 0.2);

		(*it)->move((*it)->place.x() + time_step*(*it)->velocity.x(), (*it)->place.y() + time_step*(*it)->velocity.y());
		if ((*it)->place.x() >= 50.0 || (*it)->place.x() <= -50.0)
			(*it)->velocity.x(-(*it)->velocity.x());
		if ((*it)->place.y() >= 50.0 || (*it)->place.y() <= -50.0)
			(*it)->velocity.y(-(*it)->velocity.y());
		
		//Change in theta_phase
		if (randomness == 1)
			(*it)->theta_phase = time_step*((*it)->frequency + (*it)->resetting_strength*sin((*it)->stimulus - (*it)->theta_phase)) + (*it)->theta_phase;
		else
			(*it)->theta_phase = time_step*(non_ran_freq + non_ran_reset_strength*sin((*it)->stimulus - (*it)->theta_phase)) + (*it)->theta_phase;
		while((*it)->theta_phase > 2*PI) {
			(*it)->theta_phase -= 2*PI;
			(*it)->flashed = 3;
			if (flash_stimulus == 1){
				for (it2 = Fireflies_Stack.begin(); it2 < Fireflies_Stack.end(); it2++) {
					if (it != it2)
						(*it2)->stimulus = (*it)->theta_phase - (*it2)->theta_phase;
				}
			}
		}
		while((*it)->theta_phase < 0) {
			(*it)->theta_phase += 2*PI;
			(*it)->flashed = 3;
			if (flash_stimulus == 1){
				for (it2 = Fireflies_Stack.begin(); it2 < Fireflies_Stack.end(); it2++) {
					if (it != it2)
						(*it2)->stimulus = (*it)->theta_phase - (*it2)->theta_phase;
				}
			}
		}
		//printf("Theta: %f\nStimulus: %f\n",(*it)->theta_phase,(*it)->stimulus);
		// STIMULUS
		if (flash_stimulus == 0) {
			stimulus_change = 0;
			average = 0;
			for (it2 = Fireflies_Stack.begin(); it2 < Fireflies_Stack.end(); it2++) {
				if (it != it2) {
					average++;
					stimulus_change += (*it2)->theta_phase;
				}
			}
			(*it)->stimulus = stimulus_change;
			if (average > 1)
				(*it)->stimulus /= average;
			while((*it)->stimulus > 2*PI)
				(*it)->stimulus -=2*PI;
			while((*it)->stimulus < 0)
				(*it)->stimulus +=2*PI;
		}
	}
  glFlush();
}

void glCircle3i(GLint x, GLint y, GLint radius) { 
	float angle = 0; 
	//glColor3f(1.0f, 1.0f, 1.0f);  
	glBegin(GL_POLYGON); 
	for(int i = 0; i < 100; i++) { 
		glVertex2f(x + (cos(angle) * radius), y + (sin(angle) * radius));
		angle += 2*M_PI/100;
	} 
	glEnd(); 
}  








