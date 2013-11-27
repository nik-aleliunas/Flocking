/*********
 Vector Class
 Written by Amy Gooch
 Copyright 2003
 *********/
#include "myVector.h"
#include <math.h>

MyVec4f::MyVec4f(){
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
}
MyVec4f::MyVec4f(const float& a, const float& b, const float& c, const float& d) {
	data[0] = a;
	data[1] = b;
	data[2] = c;
	data[3] = d;
}
MyVec4f::MyVec4f(const MyVec4f& copied) { 
	data[0] = copied.data[0];
	data[1] = copied.data[1];
	data[2] = copied.data[2];
	data[3] = copied.data[3];
}

MyVec4f::~MyVec4f() {
}

void MyVec4f::set(const float& a, const float& b, const float& c, const float& d){
	data[0] = a;
	data[1] = b;
	data[2] = c;
	data[3] = d;
}
float MyVec4f::norm()  //returns length of vector
{
	return sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]);
}
void MyVec4f::normalize() //makes vector unit length
{
	float length = norm();
	if (length != 0) {
		data[0] = data[0]/length;
		data[1] = data[1]/length;
		data[2] = data[2]/length;
		data[3] = 1;
	}
}
void MyVec4f::zero() //assigns zeros to all vector values
{
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
}

MyVec4f MyVec4f::operator = (const MyVec4f &other) 
{
	data[0] = other.data[0];
	data[1] = other.data[1];
	data[2] = other.data[2];
	data[3] = other.data[3];
	return *this;
}
MyVec4f MyVec4f::operator + (const MyVec4f &other)
{
	return MyVec4f(data[0]+other.data[0], 
								 data[1]+other.data[1], 
								 data[2]+other.data[2], 
								 data[3]+other.data[3]);
}
MyVec4f MyVec4f::operator - (const MyVec4f &other)
{
	return MyVec4f(data[0]-other.data[0], 
								 data[1]-other.data[1], 
								 data[2]-other.data[2], 
								 data[3]-other.data[3]);
}

MyVec4f MyVec4f::operator += (const MyVec4f &other)
{
	data[0] += other.data[0];
	data[1] += other.data[1];
	data[2] += other.data[2];
	data[3] += other.data[3];
	return *this;
}
MyVec4f MyVec4f::operator -= (const MyVec4f &other)
{
	data[0] -= other.data[0];
	data[1] -= other.data[1];
	data[2] -= other.data[2];
	data[3] -= other.data[3];
	return *this;
}
MyVec4f MyVec4f::operator *= (const float &scalar){
	data[0] *= scalar;
	data[1] *= scalar;
	data[2] *= scalar;
	data[3] *= scalar;
	return *this;
}

bool MyVec4f::operator == (const MyVec4f &other) {
	if ( data[0] == other.data[0])
		if ( data[1] == other.data[1])
			if ( data[2] == other.data[2])
				if ( data[3] == other.data[3])
					return true;
	return false;

}
bool MyVec4f::operator != (const MyVec4f &other) {
	if ( data[0] == other.data[0])
		if ( data[1] == other.data[1])
			if ( data[2] == other.data[2])
				if ( data[3] == other.data[3])
					return false;
	return true;
}

MyVec4f operator *(const float &s, const MyVec4f &v)
{
	return MyVec4f(s*v.data[0], s*v.data[1], s*v.data[2], s*v.data[3]);
}
MyVec4f operator *(const MyVec4f &v, const float &s)
{
	return MyVec4f(s*v.data[0], s*v.data[1], s*v.data[2], s*v.data[3]);
}

MyVec4f cross_product(const MyVec4f &LHV, const MyVec4f &RHV)
{
	return MyVec4f(LHV.data[2]*RHV.data[3] - LHV.data[3]*RHV.data[2],
								 LHV.data[3]*RHV.data[1] - LHV.data[1]*RHV.data[3],
								 LHV.data[1]*RHV.data[2] - LHV.data[2]*RHV.data[1],
								 1);
}
float dot_product(const MyVec4f &LHV, const MyVec4f &RHV)
{
	return (LHV.data[0]*RHV.data[0] + 
					LHV.data[1]*RHV.data[1] + 
					LHV.data[2]*RHV.data[2] +
					LHV.data[3]*RHV.data[3]); 
}
