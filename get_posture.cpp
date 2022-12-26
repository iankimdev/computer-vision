#ifndef HOMOGRAPHY
#define HOMOGRAPHY
#include"homography.h"
#endif

#include"get_posture.h"
#include<math.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#define PI_C 3.141592// phi�� ö�ڸ� �򰥷��� pi�� ���ٺ��� ������ pi�� ȥ���Ǽ� _C�� ����
void get_posture::vector_to_degree(vector v1, double& degree)
{
	
	degree = (180.0 / PI_C)*atan2(v1.y, v1.x);
	if (degree < 0)
	{
		degree = degree + 360.0;
	}

}
void get_posture::homography_transform_po(vector& output, const double H[3][3], const vector& input)
{
	double w;
	w = input.x*H[2][0] + input.y*H[2][1] + H[2][2];
	output.x = (input.x*H[0][0] + input.y*H[0][1] + H[0][2]) / w;
	output.y = (input.x*H[1][0] + input.y*H[1][1] + H[1][2]) / w;
}

get_posture::get_posture()
{
}
get_posture::~get_posture()
{}
void get_posture::input(double H[3][3], double H_R[3][3], vector Zero_To_Vanishing_Line, vector Code_To_Vanishing_Line)
{
	ztvl = Zero_To_Vanishing_Line;//qr�ڵ� �߽ɿ��� vanishing line���� ����
	ctvl = Code_To_Vanishing_Line;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			  h[i][j]	=	  H[i][j];
			h_r[i][j]	=	H_R[i][j];
		}
	}
}
double get_posture::Get_Distance()
{
	vector modi_code_center(h[0][2], h[1][2]);
	vector distance_line_vector((ctvl.y / mag(ctvl)), -(ctvl.x / mag(ctvl)));
	vector point1;
	vector point2;
	vector point1_p;
	vector point2_p;
	point1 = modi_code_center + distance_line_vector;
	point2 = modi_code_center - distance_line_vector;
	homography_transform_po(point1_p, h_r, point1);
	homography_transform_po(point2_p, h_r, point2);
	distance = mag(point2_p - point1_p);//r ȹ��
	return distance;
}
vector get_posture::Get_pi_posture()// image �� ��ǥ�� x , -y �̹Ƿ� pi �� �ð� �ݴ� �������� ȸ��
{
	vector zero_point_p;
	vector unit_ctvl;
	vector unit_ztvl;
	vector unit_ctvl_p;
	zero_point_p.x = h[0][2];
	zero_point_p.y = h[1][2];

	unit_ctvl = (ctvl / mag(ctvl));
	unit_ztvl = (ztvl / mag(ztvl));
	homography_transform_po(unit_ctvl_p, h_r, zero_point_p + unit_ctvl);
	//�����󿡼��� ���� ������ �ٶ󺸴� ���� �ҽ����� ���ϴ� ���̸�, �̸� ���ϱ����� �ڵ��߽� ��ǥ(zero_point_p)�� �ڵ��߽ɿ��� ���� ���� ������ �Ҽ��������� ���Ϳ� ���ϸ� ztvl�� ���Եȴ�.
	
	unit_ctvl_p = (unit_ctvl_p ) / mag(unit_ctvl_p );
	vector_to_degree(unit_ctvl_p, pan);//pi ȹ��
	return unit_ctvl_p;
}
double get_posture::Get_theta_posture(int five_angle_to_pixel_rate)
{
	double c = five_angle_to_pixel_rate / tan(5 * PI_C / 180);
	vector unit_coordinate_theta;

	unit_coordinate_theta = ctvl / mag(ctvl);

	tilt = (180.0 / PI_C)*atan(dot(unit_coordinate_theta, ztvl) / c);// theta ȹ��(�ȼ� �� ���� ���踦 �����Ҷ��� �߽��� �׻� 0,0. ��, �þ��߽��� �Ǿ����Ѵ�. )
	return tilt;
}
vector get_posture::Get_roll_posture()
{
	vector v_roll;
	v_roll = ctvl / mag(ctvl);
	vector_to_degree(v_roll, roll);//roll ȹ��
	roll -= 90;
	if (roll > 180)
	{
		roll -= 360;
	}
	else if (roll < -180)
	{
		roll += 360;
	}
	return v_roll;
}
void get_posture::display()
{
	std::cout << std::endl << "vanishing line vector: (" << ztvl.x << ',' << ztvl.y << ")" << std::endl << std::endl;
	
	std::cout << std::endl << "posture_tilt: (" << tilt << ")" << std::endl;
	std::cout << std::endl << "posture_pan: (" << pan << ")" << std::endl;
	std::cout << std::endl << "posture_roll: (" << roll << ")" << std::endl;
}

double multiple_square(double x,int n)
{
	int result = 1;
	for (int i = 0; i < n; i++)
	{
		result *= x;
	}
	return result;
}
double factorial(int n)
{
	double result = 1;
	for (int i = 1; i <= n; i++)
	{
		result *= i;
	}
	return result;
}
double fast_exp(double x, int k)
{
	double result = 0;
	for (int n = 0; n <= k; n++)
	{
		result += multiple_square(x, n) / factorial(n);
	}
	return result;
}
double get_position::Get_theta_prime_position(int five_angle_to_pixel_rate)
{
	vector unit_coordinate_theta;
	vector zero_to_code;
	double c = five_angle_to_pixel_rate / tan(5 * PI_C / 180);
	double x = 0;
	zero_to_code.x = h[0][2];
	zero_to_code.y = h[1][2];// �ڵ��� �����̵� ����(�ʱ� �������ִ� �ڵ��� ����� ��ġ�� ������ ����)

	unit_coordinate_theta = ctvl / mag(ctvl);
	
	x = dot(unit_coordinate_theta, zero_to_code);
	theta_prime = (180.0 / PI_C)*atan( x / c) * (1 + (1 - fast_exp(-x,5)) * 0.1);
	position_theta = (90.0 - tilt) + theta_prime;
	return theta_prime;
}
double get_position::Get_pi_prime_position(int five_angle_to_pixel_rate)
{
	vector unit_coordinate_pi;
	vector zero_to_code;
	double c = five_angle_to_pixel_rate / tan(5 * PI_C / 180);
	double x = 0;
	zero_to_code.x = h[0][2];
	zero_to_code.y = h[1][2];

	unit_coordinate_pi.x = ctvl.y / mag(ctvl);
	unit_coordinate_pi.y = -ctvl.x / mag(ctvl);

	x = dot(unit_coordinate_pi, zero_to_code);
	pi_prime = (180.0 / PI_C)*atan(x / c) * (1 + (1 - fast_exp(-x, 5)) * 0.1);
	position_pi = pan + pi_prime;
	return pi_prime;
}
void get_position::display()
{
	std::cout << std::endl << "vanishing line vector: (" << ztvl.x << ',' << ztvl.y << ")" << std::endl << std::endl;

	std::cout << std::endl << "posture_tilt: (" << tilt << ")" << std::endl;
	std::cout << std::endl << "posture_pan: (" << pan << ")" << std::endl;
	std::cout << std::endl << "posture_roll: (" << roll << ")" << std::endl;

	std::cout << std::endl << "position_r: (" << distance << ")" << std::endl;
	std::cout << std::endl << "position_theta: (" << position_theta << ")" << std::endl;
	std::cout << std::endl << "position_pi: (" << position_pi << ")" << std::endl;
}
void get_position::write_results()
{
	std::ofstream  outputFile("outputFile.txt",std::ios::app);
	outputFile << std::setw(15) << tilt << std::setw(15) << pan << std::setw(15) << roll << std::setw(15) << distance << std::setw(15) << position_theta << std::setw(15) << position_pi << std::endl;
	outputFile.close();
}