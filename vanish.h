#pragma once
#ifndef HOMOGRAPHY
#define HOMOGRAPHY
#include"homography.h"
#endif
class vanish
{
private:
	double homography[3][3];
	vector vanishing_point1;
	vector vanishing_point2;
	vector vanishing_point3;
	vector vanishing_line_unit_d;
	vector vanishing_line_locate;
	vector zero_to_vanishing_line;
	vector code_to_vanishing_line;
	bool point1_exist;
	bool point2_exist;
	bool point3_exist;
	int count;
	void get_line(vector v1, vector v2, vector& unit_direct,vector& locate );
public:
	vanish();//setting order no.1
	void input_homography(double hmgp[3][3]);//setting order no.2
	bool get_VanishingPoints();//setting order no.3
	void get_VanishingLine(); //setting order no.4
	vector Zero_to_Vanishing_Line();//setting order no.5
	vector Code_to_Vanishing_Line();
};