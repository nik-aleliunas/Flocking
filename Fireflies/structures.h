#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "myVector.cpp"
class Firefly {
public:
	MyVec4f c;
	MyVec4f place;
	MyVec4f velocity;
	float theta_phase;	
	float stimulus;
	float frequency;
	float resetting_strength;
	int flashed;
	Firefly() {
		c.x(1.0);
		c.y(1.0);
		c.z(1.0);
		c.w(1.0);
		place.x(0);
		place.y(0);
		place.z(0);
		place.w(1);
		theta_phase = 0;
		stimulus = 0;
		frequency = 1.0;
		resetting_strength = 1;
		velocity.x(0);
		velocity.y(0);
		velocity.z(0);
		velocity.w(1);
		flashed = 0;
	}
	Firefly(GLfloat r, GLfloat g, GLfloat b, float x, float y, float z, float thetaNew, \
					 float frequencyNew, float resetting_strengthNew, float vx, float vy, float vz) {
		c.x(r);
		c.y(g);
		c.z(b);
		c.w(1.0);
		place.x(x);
		place.y(y);
		place.z(z);
		place.w(1);
		theta_phase = thetaNew;
		stimulus = 0;
		frequency = frequencyNew;
		resetting_strength = resetting_strengthNew;
		velocity.x(vx);
		velocity.y(vy);
		velocity.z(vz);
		velocity.w(1);
		flashed = 0;
	}
	void move(float x, float y) {
		place.x(x);
		place.y(y);
	}
	
	void set(GLfloat r, GLfloat g, GLfloat b, float x, float y, float z, float thetaNew, \
					 float frequencyNew, float resetting_strengthNew, float vx, float vy, float vz) {
		c.x(r);
		c.y(g);
		c.z(b);
		place.x(x);
		place.y(y);
		place.z(z);
		theta_phase = thetaNew;
		frequency = frequencyNew;
		resetting_strength = resetting_strengthNew;
		velocity.x(vx);
		velocity.y(vy);
		velocity.z(vz);
	}
	void print() {
		//printf("c.r = %f;\nc.g = %f;\nc.b = %f;\nplace.x = %f;\nplace.y = %f;\nplace.z = %f;\nvelocity.x = %f;\nvelocity.y = %f;\nvelocity.z = %f;\n", c.x(),c.y(),c.z(),place.x(),place.y(),place.z(),velocity.x(),velocity.y(),velocity.z());
		printf("theta = %f\nfrequency = %f\nresetting strength = %f\n", theta_phase,frequency,resetting_strength);
	}
};
