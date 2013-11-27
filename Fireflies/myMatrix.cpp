/*********
 Vector Class
 Written by Amy Gooch
 Copyright 2003
 *********/
#include "myMatrix.h"
#include <math.h>
/*
 00 04 08 12
 01 05 09 13
 02 06 10 14
 03 07 11 15
 
 */
#define PI 3.14159265
MyMat4f::MyMat4f()
{
	int i = 0;
	for (i = 0; i < 16; i++)
		data[i] = 0;
	data[15] = 1;
}
MyMat4f::MyMat4f(const MyMat4f &copied)
{
	int i = 0;
	for (i = 0; i < 16; i++)
		data[i] = copied.data[i];
}
MyMat4f::MyMat4f(const float &a, const float &b, const float &c, const float &d,
								 const float &e, const float &f, const float &g, const float &h,
								 const float &i, const float &j, const float &k, const float &l,
								 const float &m, const float &n, const float &o, const float &p)
{
	data[0]  = a;
	data[1]  = e;
	data[2]  = i;
	data[3]  = m;
	data[4]  = b;
	data[5]  = f;
	data[6]  = j;
	data[7]  = n;
	data[8]  = c;
	data[9]  = g;
	data[10] = k;
	data[11] = o;
	data[12] = d;
	data[13] = h;
	data[14] = l;
	data[15] = p;
}
MyMat4f::~MyMat4f()
{

}

void MyMat4f::print()
{
	int i = 0;
	for(i=0; i < 4; i++)
		printf("|%3f %3f %3f %3f| \n", data[i], data[i+4], data[i+8], data[i+12]);

}
void MyMat4f::identity()
{
	int i = 0;
	for (i = 0; i < 15; i++)
		data[i] = 0;
	data[0] = 1;
	data[5] = 1;
	data[10] = 1;
	data[15] = 1;
}
void MyMat4f::transpose()
{
	float temp;
	int i=0;
	for(i=0; i<3; i++) {
		temp = data[i*5 + 4];
		data[i*5 + 4] = data[i*5 + 1];
		data[i*5 + 1] = temp;
	}
	for(i=0; i<2; i++) {
		temp = data[i*5 + 2];
		data[i*5 + 2] = data[i*5 + 3];
		data[i*5 + 3] = temp;
	}
	temp = data[03];
	data[03] = data[12];
	data[12] = temp;
		
}
void MyMat4f::zero()
{
	int i = 0;
	for (i = 0; i < 15; i++)
		data[i] = 0;
}
/*
 Rz(θ) = 
 | cosθ -sinθ  0   0|
 | sinθ  cosθ  0   0|
 | 0     0     1   0|
 | 0     0     0   1|
 */
void MyMat4f::turnLeft(float angle)
{
	data[0] = cos(angle*PI/180);
	data[1] = sin(angle*PI/180);
	data[2] = 0;
	data[3] = 0;
	
	data[4] = -sin(angle*PI/180);
	data[5] = cos(angle*PI/180);
	data[6] = 0;
	data[7] = 0;
	
	data[8]  = 0;
	data[9]  = 0;
	data[10] = 1;
	data[11] = 0;
	
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
}
void MyMat4f::turnRight(float angle)
{
	data[0] = cos(-angle*PI/180);
	data[1] = sin(-angle*PI/180);
	data[2] = 0;
	data[3] = 0;
	
	data[4] = -sin(-angle*PI/180);
	data[5] = cos(-angle*PI/180);
	data[6] = 0;
	data[7] = 0;
	
	data[8]  = 0;
	data[9]  = 0;
	data[10] = 1;
	data[11] = 0;
	
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
}
MyVec4f MyMat4f::getTranslation()
{
	return MyVec4f(data[12], 
								 data[13],
								 data[14],
								 data[15]);
}
void MyMat4f::setTranslation(const MyVec4f &v) 
{
	data[12] = v.data[0];
	data[13] = v.data[1];
	data[14] = v.data[2];
	data[15] = v.data[3];
}
void MyMat4f::setTranslation(const float &a, const float &b,
										const float &c, const float&d)
{
	data[12] = a;
	data[13] = b;
	data[14] = c;
	data[15] = d;
}

void MyMat4f::setScale(const float &a, const float &b,
							const float &c, const float&d)
{
	int i = 0;
	for (i = 0; i < 16; i++)
		data[i] = 0;
	data[0] = a;
	data[5] = b;
	data[10] = c;
	data[15] = d;
}

// operator overloading

float MyMat4f::operator() (const unsigned char &i, const unsigned char &j)
{
	return data[i+4 * j-5];
}

MyMat4f MyMat4f::operator=(const MyMat4f &other)
{
	int i = 0;
	for( i = 0; i < 16; i++)
		this->data[i] = other.data[i];
	return *this;
}

bool MyMat4f::operator==(const MyMat4f &other) const
{
	int i = 0;
	for(i=0; i < 16; i++)
		if ( this->data[i] != other.data[i])
			return false;
	return true;
}
bool MyMat4f::operator!=(const MyMat4f &other) const
{
	int i = 0;
	int j = 0;
	for(i=0; i < 16; i++)
		if ( this->data[i] != other.data[i])
			return true;
	return false;
}

MyMat4f MyMat4f::operator*=(const float &k)
{
	int i = 0;
	for( i = 0; i < 16; i++) 
		data[i] = k*data[i];
	return *this;
}

MyMat4f operator*(const MyMat4f &M, const float &K)
{
	MyMat4f temp;
	int i = 0;
	for( i = 0; i < 16; i++) 
		temp.data[i] = K*M.data[i];
	return temp;
}
MyMat4f operator*(const float &K, const MyMat4f &M)
{
	MyMat4f temp;
	int i = 0;
	for( i = 0; i < 16; i++) 
		temp.data[i] = K*M.data[i];
	return temp;
}
MyMat4f operator*(const MyMat4f &lhm, const MyMat4f &rhm)
{
	MyMat4f temp;
	int i = 0;
	for (i = 0; i < 4; i++) {
		temp.data[i]   = lhm.data[i]*rhm.data[0]  + lhm.data[i+4]*rhm.data[1]  + lhm.data[i+8]*rhm.data[2]  + lhm.data[i+12]*rhm.data[3];
		temp.data[i+4] = lhm.data[i]*rhm.data[4]  + lhm.data[i+4]*rhm.data[5]  + lhm.data[i+8]*rhm.data[6]  + lhm.data[i+12]*rhm.data[7];
		temp.data[i+8] = lhm.data[i]*rhm.data[8]  + lhm.data[i+4]*rhm.data[9]  + lhm.data[i+8]*rhm.data[10] + lhm.data[i+12]*rhm.data[11];
		temp.data[i+12]= lhm.data[i]*rhm.data[12] + lhm.data[i+4]*rhm.data[13] + lhm.data[i+8]*rhm.data[14] + lhm.data[i+12]*rhm.data[15];
	}
	return MyMat4f(temp);

}
