#pragma once
#ifndef HOMOGRAPHY
#define HOMOGRAPHY
#include"homography.h"
#endif
class get_posture
{
protected:
	vector ztvl;//zero to vanishing line
	vector ctvl;//code to vanishing line
	double h[3][3];
	double h_r[3][3];
	//source
	double distance;
	double pan;//pi
	double tilt;//theta
	double roll; //roll// 코드가 천장에 있다는 가정하에 나의 자세
	//qr 코드 중심 좌표,qr코드 중심에서 vanishing line으로 벡터 
	void vector_to_degree(vector v1, double& degree);
	void homography_transform_po(vector& output, const double H[3][3], const vector& input);
public:
	get_posture();
	~get_posture();
	void input(double H[3][3], double H_R[3][3], vector Zero_To_Vanishing_Line, vector Code_To_Vanishing_Line);
	double Get_Distance();
	vector Get_pi_posture();
	double Get_theta_posture(int five_angle_to_pixel_rate);
	vector Get_roll_posture();
	void display();
};

class get_position : public get_posture
{
private:
	double theta_prime;
	double position_theta;
	double pi_prime;
	double position_pi;
public:
	double Get_theta_prime_position(int five_angle_to_pixel_rate);
	double Get_pi_prime_position(int five_angle_to_pixel_rate);
	void display();
	void write_results();
};