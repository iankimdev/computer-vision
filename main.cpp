#ifndef HOMOGRAPHY
#define HOMOGRAPHY
#include"homography.h"
#endif
#include"vanish.h"
#include"get_posture.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>


using namespace std;

enum pictures{PI=0,THETA=1,ROLL=2,FIX_POSISION=3,MOVING_POSITION=4};
double Get_Distance(double h[3][3], double h_r[3][3], vector ztvl);
void homography_transform(vector& output, const double h[3][3], const vector& input);
vector Get_cardinal_point(double h[3][3], double h_r[3][3], vector ztvl);
void picture_info(vector output[4],pictures mode,int picture_num);
void picture_info2(vector output[4], pictures mode, int picture_num);
int main()
{
	ofstream out1("outputFile.txt", ios::trunc);
	out1.close();
	int FATPR = 387;
	int stop;
	vector org[4];
	vector modi[4];
	
	org[0].x = - 1000;
	org[0].y = -1000;
	org[1].x =  1000;
	org[1].y = - 1000;
	org[2].x =  1000;
	org[2].y =  1000;
	org[3].x = - 1000;
	org[3].y =  1000;
	
	homography h1;

	vanish v1;
	vector ztvl;
	vector ctvl;

	double h[3][3];
	double h_r[3][3];

	get_position My_position;
	/*
	//PI ����
	for (int i = 0; i <= 9; i++)
	{
		picture_info(modi, PI, i);

		modi[0].x = modi[0].x - 2592;//g	//1803	, 1602	, 2158	, 2408	, 2651	, 2724
		modi[0].y = modi[0].y - 1728;//g	// 521	,  993	, 2065	, 1432	, 2456	, 1415
		modi[1].x = modi[1].x - 2592;//r	//3942	, 3057	, 2180	, 2498	, 2781	, 2901
		modi[1].y = modi[1].y - 1728;//r	// 494	,  972	, 3519	, 2751	, 3740	, 2277
		modi[2].x = modi[2].x - 2592;//y	//3957	, 3003	,  507	,  872	,  943	, 1407
		modi[2].y = modi[2].y - 1728;//y	//2612	, 2535	, 3418	, 2716	, 3524	, 2410
		modi[3].x = modi[3].x - 2592;//b	//1850	, 1517	,  698	, 1000	, 1226	, 1544
		modi[3].y = modi[3].y - 1728;//b	//2670	, 2452	, 1930	, 1400	, 2270	, 1517
								
		
		h1.input(org, modi);
		h1.calc_homography();
		h1.calc_inv_homography();
		h1.Display_homography();

		//calc vanishing line
		

		h1.output_h(h);
		h1.output_h_r(h_r);

		v1.input_homography(h);
		v1.get_VanishingPoints();
		v1.get_VanishingLine();

		ztvl = v1.Zero_to_Vanishing_Line();//�� ������ ������ ��������  theta �� ����
		ctvl = v1.Code_to_Vanishing_Line();
		//calc distance,caldinal point

		
		My_position.input(h, h_r, ztvl, ctvl);// ztvl�� ctvl�� ��κ��� ��� ������ ������ �幮 ���̽��� ������ �ݴ��� �� �ִ�.
		My_position.Get_theta_posture(FATPR);
		My_position.Get_pi_posture();
		My_position.Get_roll_posture();
		My_position.Get_Distance();
		My_position.Get_pi_prime_position(FATPR);
		My_position.Get_theta_prime_position(FATPR);

		My_position.display();
		stop = 0;
		cin >> stop;
	}
	//THETA ���� 
	for (int i = 0; i <= 12; i++)
	{
		picture_info(modi, THETA, i);

		modi[0].x = modi[0].x - 2592;//g	//1803	, 1602	, 2158	, 2408	, 2651	, 2724
		modi[0].y = modi[0].y - 1728;//g	// 521	,  993	, 2065	, 1432	, 2456	, 1415
		modi[1].x = modi[1].x - 2592;//r	//3942	, 3057	, 2180	, 2498	, 2781	, 2901
		modi[1].y = modi[1].y - 1728;//r	// 494	,  972	, 3519	, 2751	, 3740	, 2277
		modi[2].x = modi[2].x - 2592;//y	//3957	, 3003	,  507	,  872	,  943	, 1407
		modi[2].y = modi[2].y - 1728;//y	//2612	, 2535	, 3418	, 2716	, 3524	, 2410
		modi[3].x = modi[3].x - 2592;//b	//1850	, 1517	,  698	, 1000	, 1226	, 1544
		modi[3].y = modi[3].y - 1728;//b	//2670	, 2452	, 1930	, 1400	, 2270	, 1517


		h1.input(org, modi);
		h1.calc_homography();
		h1.calc_inv_homography();
		h1.Display_homography();

		//calc vanishing line


		h1.output_h(h);
		h1.output_h_r(h_r);

		v1.input_homography(h);
		v1.get_VanishingPoints();
		v1.get_VanishingLine();

		ztvl = v1.Zero_to_Vanishing_Line();//�� ������ ������ ��������  theta �� ����
		ctvl = v1.Code_to_Vanishing_Line();
		//calc distance,caldinal point


		My_position.input(h, h_r, ztvl, ctvl);// ztvl�� ctvl�� ��κ��� ��� ������ ������ �幮 ���̽��� ������ �ݴ��� �� �ִ�.
		My_position.Get_theta_posture(FATPR);
		My_position.Get_pi_posture();
		My_position.Get_roll_posture();
		My_position.Get_Distance();
		My_position.Get_pi_prime_position(FATPR);
		My_position.Get_theta_prime_position(FATPR);

		My_position.display();

		cin >> stop;
	}
	*/							
	
	//phi ����
	for (int i = 0; i <= 9; i++)
	{
		picture_info2(modi, PI, i);

		modi[0].x = modi[0].x - 2592;//g	//1803	, 1602	, 2158	, 2408	, 2651	, 2724
		modi[0].y = modi[0].y - 1728;//g	// 521	,  993	, 2065	, 1432	, 2456	, 1415
		modi[1].x = modi[1].x - 2592;//r	//3942	, 3057	, 2180	, 2498	, 2781	, 2901
		modi[1].y = modi[1].y - 1728;//r	// 494	,  972	, 3519	, 2751	, 3740	, 2277
		modi[2].x = modi[2].x - 2592;//y	//3957	, 3003	,  507	,  872	,  943	, 1407
		modi[2].y = modi[2].y - 1728;//y	//2612	, 2535	, 3418	, 2716	, 3524	, 2410
		modi[3].x = modi[3].x - 2592;//b	//1850	, 1517	,  698	, 1000	, 1226	, 1544
		modi[3].y = modi[3].y - 1728;//b	//2670	, 2452	, 1930	, 1400	, 2270	, 1517


		h1.input(org, modi);
		h1.calc_homography();
		h1.calc_inv_homography();
		//h1.Display_homography();

		//calc vanishing line


		h1.output_h(h);
		h1.output_h_r(h_r);

		v1.input_homography(h);
		v1.get_VanishingPoints();
		v1.get_VanishingLine();

		ztvl = v1.Zero_to_Vanishing_Line();//�� ������ ������ ��������  theta �� ����
		ctvl = v1.Code_to_Vanishing_Line();
		//calc distance,caldinal point


		My_position.input(h, h_r, ztvl, ctvl);// ztvl�� ctvl�� ��κ��� ��� ������ ������ �幮 ���̽��� ������ �ݴ��� �� �ִ�.
		My_position.Get_theta_posture(FATPR);
		My_position.Get_pi_posture();
		My_position.Get_roll_posture();
		My_position.Get_Distance();
		My_position.Get_pi_prime_position(FATPR);
		My_position.Get_theta_prime_position(FATPR);

		My_position.write_results();
		stop = 0;
		//cin >> stop;
	}
	out1.open("outputFile.txt", ios::app);
	out1 << endl;
	out1.close();
	
	//theta ����
	for (int i = 0; i <= 12; i++)
	{
		picture_info2(modi, THETA, i);

		modi[0].x = modi[0].x - 2592;//g	//1803	, 1602	, 2158	, 2408	, 2651	, 2724
		modi[0].y = modi[0].y - 1728;//g	// 521	,  993	, 2065	, 1432	, 2456	, 1415
		modi[1].x = modi[1].x - 2592;//r	//3942	, 3057	, 2180	, 2498	, 2781	, 2901
		modi[1].y = modi[1].y - 1728;//r	// 494	,  972	, 3519	, 2751	, 3740	, 2277
		modi[2].x = modi[2].x - 2592;//y	//3957	, 3003	,  507	,  872	,  943	, 1407
		modi[2].y = modi[2].y - 1728;//y	//2612	, 2535	, 3418	, 2716	, 3524	, 2410
		modi[3].x = modi[3].x - 2592;//b	//1850	, 1517	,  698	, 1000	, 1226	, 1544
		modi[3].y = modi[3].y - 1728;//b	//2670	, 2452	, 1930	, 1400	, 2270	, 1517


		h1.input(org, modi);
		h1.calc_homography();
		h1.calc_inv_homography();
		//h1.Display_homography();

		//calc vanishing line


		h1.output_h(h);
		h1.output_h_r(h_r);

		v1.input_homography(h);
		v1.get_VanishingPoints();
		v1.get_VanishingLine();

		ztvl = v1.Zero_to_Vanishing_Line();//�� ������ ������ ��������  theta �� ����
		ctvl = v1.Code_to_Vanishing_Line();
		//calc distance,caldinal point


		My_position.input(h, h_r, ztvl, ctvl);// ztvl�� ctvl�� ��κ��� ��� ������ ������ �幮 ���̽��� ������ �ݴ��� �� �ִ�.
		My_position.Get_theta_posture(FATPR);
		My_position.Get_pi_posture();
		My_position.Get_roll_posture();
		My_position.Get_Distance();
		My_position.Get_pi_prime_position(FATPR);
		My_position.Get_theta_prime_position(FATPR);

		My_position.write_results();

		//cin >> stop;
	}
	out1.open("outputFile.txt", ios::app);
	out1 << endl;
	out1.close();
	
	//roll ����
	for (int i = 0; i <= 9; i++)
	{
		picture_info2(modi, ROLL, i);

		modi[0].x = modi[0].x - 2592;//g	//1803	, 1602	, 2158	, 2408	, 2651	, 2724
		modi[0].y = modi[0].y - 1728;//g	// 521	,  993	, 2065	, 1432	, 2456	, 1415
		modi[1].x = modi[1].x - 2592;//r	//3942	, 3057	, 2180	, 2498	, 2781	, 2901
		modi[1].y = modi[1].y - 1728;//r	// 494	,  972	, 3519	, 2751	, 3740	, 2277
		modi[2].x = modi[2].x - 2592;//y	//3957	, 3003	,  507	,  872	,  943	, 1407
		modi[2].y = modi[2].y - 1728;//y	//2612	, 2535	, 3418	, 2716	, 3524	, 2410
		modi[3].x = modi[3].x - 2592;//b	//1850	, 1517	,  698	, 1000	, 1226	, 1544
		modi[3].y = modi[3].y - 1728;//b	//2670	, 2452	, 1930	, 1400	, 2270	, 1517


		h1.input(org, modi);
		h1.calc_homography();
		h1.calc_inv_homography();
		//h1.Display_homography();

		//calc vanishing line


		h1.output_h(h);
		h1.output_h_r(h_r);

		v1.input_homography(h);
		v1.get_VanishingPoints();
		v1.get_VanishingLine();

		ztvl = v1.Zero_to_Vanishing_Line();//�� ������ ������ ��������  theta �� ����
		ctvl = v1.Code_to_Vanishing_Line();
		//calc distance,caldinal point


		My_position.input(h, h_r, ztvl, ctvl);// ztvl�� ctvl�� ��κ��� ��� ������ ������ �幮 ���̽��� ������ �ݴ��� �� �ִ�.
		My_position.Get_theta_posture(FATPR);
		My_position.Get_pi_posture();
		My_position.Get_roll_posture();
		My_position.Get_Distance();
		My_position.Get_pi_prime_position(FATPR);
		My_position.Get_theta_prime_position(FATPR);

		My_position.write_results();

		//cin >> stop;
	}
	out1.open("outputFile.txt", ios::app);
	out1 << endl;
	out1.close();
	
	//fix_position ����
	for (int i = 0; i <= 8; i++)
	{
		picture_info2(modi, FIX_POSISION, i);

		modi[0].x = modi[0].x - 2592;//g	//1803	, 1602	, 2158	, 2408	, 2651	, 2724
		modi[0].y = modi[0].y - 1728;//g	// 521	,  993	, 2065	, 1432	, 2456	, 1415
		modi[1].x = modi[1].x - 2592;//r	//3942	, 3057	, 2180	, 2498	, 2781	, 2901
		modi[1].y = modi[1].y - 1728;//r	// 494	,  972	, 3519	, 2751	, 3740	, 2277
		modi[2].x = modi[2].x - 2592;//y	//3957	, 3003	,  507	,  872	,  943	, 1407
		modi[2].y = modi[2].y - 1728;//y	//2612	, 2535	, 3418	, 2716	, 3524	, 2410
		modi[3].x = modi[3].x - 2592;//b	//1850	, 1517	,  698	, 1000	, 1226	, 1544
		modi[3].y = modi[3].y - 1728;//b	//2670	, 2452	, 1930	, 1400	, 2270	, 1517


		h1.input(org, modi);
		h1.calc_homography();
		h1.calc_inv_homography();
		//h1.Display_homography();

		//calc vanishing line


		h1.output_h(h);
		h1.output_h_r(h_r);

		v1.input_homography(h);
		v1.get_VanishingPoints();
		v1.get_VanishingLine();

		ztvl = v1.Zero_to_Vanishing_Line();//�� ������ ������ ��������  theta �� ����
		ctvl = v1.Code_to_Vanishing_Line();
		//calc distance,caldinal point


		My_position.input(h, h_r, ztvl, ctvl);// ztvl�� ctvl�� ��κ��� ��� ������ ������ �幮 ���̽��� ������ �ݴ��� �� �ִ�.
		My_position.Get_theta_posture(FATPR);
		My_position.Get_pi_posture();
		My_position.Get_roll_posture();
		My_position.Get_Distance();
		My_position.Get_pi_prime_position(FATPR);
		My_position.Get_theta_prime_position(FATPR);

		My_position.write_results();

		//cin >> stop;
	}
	out1.open("outputFile.txt", ios::app);
	out1 << endl;
	out1.close();
	
	//moving_position ����
	for (int i = 0; i <= 5; i++)
	{
		picture_info2(modi, MOVING_POSITION, i);

		modi[0].x = modi[0].x - 2592;//g	//1803	, 1602	, 2158	, 2408	, 2651	, 2724
		modi[0].y = modi[0].y - 1728;//g	// 521	,  993	, 2065	, 1432	, 2456	, 1415
		modi[1].x = modi[1].x - 2592;//r	//3942	, 3057	, 2180	, 2498	, 2781	, 2901
		modi[1].y = modi[1].y - 1728;//r	// 494	,  972	, 3519	, 2751	, 3740	, 2277
		modi[2].x = modi[2].x - 2592;//y	//3957	, 3003	,  507	,  872	,  943	, 1407
		modi[2].y = modi[2].y - 1728;//y	//2612	, 2535	, 3418	, 2716	, 3524	, 2410
		modi[3].x = modi[3].x - 2592;//b	//1850	, 1517	,  698	, 1000	, 1226	, 1544
		modi[3].y = modi[3].y - 1728;//b	//2670	, 2452	, 1930	, 1400	, 2270	, 1517


		h1.input(org, modi);
		h1.calc_homography();
		h1.calc_inv_homography();
		//h1.Display_homography();

		//calc vanishing line


		h1.output_h(h);
		h1.output_h_r(h_r);

		v1.input_homography(h);
		v1.get_VanishingPoints();
		v1.get_VanishingLine();

		ztvl = v1.Zero_to_Vanishing_Line();//�� ������ ������ ��������  theta �� ����
		ctvl = v1.Code_to_Vanishing_Line();
		//calc distance,caldinal point


		My_position.input(h, h_r, ztvl, ctvl);// ztvl�� ctvl�� ��κ��� ��� ������ ������ �幮 ���̽��� ������ �ݴ��� �� �ִ�.
		My_position.Get_theta_posture(FATPR);
		My_position.Get_pi_posture();
		My_position.Get_roll_posture();
		My_position.Get_Distance();
		My_position.Get_pi_prime_position(FATPR);
		My_position.Get_theta_prime_position(FATPR);

		My_position.write_results();

		//cin >> stop;
	}

	return 0; 
}
double Get_Distance(double h[3][3], double h_r[3][3], vector ztvl)
{
	vector modi_code_center(h[0][2], h[1][2]);
	vector distance_line_vector( (ztvl.y / mag(ztvl)) , -(ztvl.x / mag(ztvl)) );
	vector point1;
	vector point2;
	vector point1_p;
	vector point2_p;
	point1 = modi_code_center + distance_line_vector;
	point2 = modi_code_center - distance_line_vector;
	homography_transform(point1_p, h_r, point1);
	homography_transform(point2_p, h_r, point2);

	return mag(point2_p - point1_p);
}
void homography_transform(vector& output, const double h[3][3], const vector& input)
{
	double w;
		w		=  input.x*h[2][0] + input.y*h[2][1] + h[2][2]	   ;
	output.x	= (input.x*h[0][0] + input.y*h[0][1] + h[0][2]) / w;
	output.y	= (input.x*h[1][0] + input.y*h[1][1] + h[1][2]) / w;
}
vector Get_cardinal_point(double h[3][3], double h_r[3][3], vector ztvl)
{
	vector unit_ztvl;
	vector unit_ztvl_p;
	unit_ztvl = ztvl / mag(ztvl);
	homography_transform(unit_ztvl_p, h_r, unit_ztvl);
	unit_ztvl_p = unit_ztvl_p / mag(unit_ztvl_p);
	return unit_ztvl_p;
}
//���� �ʿ� (�̷к��� �ٽ� ����)
void picture_info(vector output[4], pictures mode,int picture_num)
{
	vector picture_information[2][13][4];
	// pi,0 
	picture_information[PI][0][0].x = 1894;
	picture_information[PI][0][0].y = 828;
	picture_information[PI][0][1].x = 3830;
	picture_information[PI][0][1].y = 810;
	picture_information[PI][0][2].x = 3953;
	picture_information[PI][0][2].y = 2753;
	picture_information[PI][0][3].x = 1835;
	picture_information[PI][0][3].y = 2770;
	// pi,10
	picture_information[PI][1][0].x = 1098;
	picture_information[PI][1][0].y = 469;
	picture_information[PI][1][1].x = 2945;
	picture_information[PI][1][1].y = 207;
	picture_information[PI][1][2].x = 3305;
	picture_information[PI][1][2].y = 1963;
	picture_information[PI][1][3].x = 1268;
	picture_information[PI][1][3].y = 2272;
	// pi,20
	picture_information[PI][2][0].x = 1431;
	picture_information[PI][2][0].y = 704;
	picture_information[PI][2][1].x = 3222;
	picture_information[PI][2][1].y = 214;
	picture_information[PI][2][2].x = 3929;
	picture_information[PI][2][2].y = 1880;
	picture_information[PI][2][3].x = 1984;
	picture_information[PI][2][3].y = 2495;
	// pi,30
	picture_information[PI][3][0].x = 1243;
	picture_information[PI][3][0].y = 1019;
	picture_information[PI][3][1].x = 2872;
	picture_information[PI][3][1].y = 355;
	picture_information[PI][3][2].x = 3782;
	picture_information[PI][3][2].y = 1785;
	picture_information[PI][3][3].x = 2019;
	picture_information[PI][3][3].y = 2621;
	// pi,40
	picture_information[PI][4][0].x = 1079;
	picture_information[PI][4][0].y = 1488;
	picture_information[PI][4][1].x = 2552;
	picture_information[PI][4][1].y = 574;
	picture_information[PI][4][2].x = 3775;
	picture_information[PI][4][2].y = 1736;
	picture_information[PI][4][3].x = 2242;
	picture_information[PI][4][3].y = 2901;
	// pi,50
	picture_information[PI][5][0].x = 1271;
	picture_information[PI][5][0].y = 1672;
	picture_information[PI][5][1].x = 2523;
	picture_information[PI][5][1].y = 830;
	picture_information[PI][5][2].x = 3737;
	picture_information[PI][5][2].y = 1737;
	picture_information[PI][5][3].x = 2489;
	picture_information[PI][5][3].y = 2808;
	// pi,60
	picture_information[PI][6][0].x = 1259;
	picture_information[PI][6][0].y = 1794;
	picture_information[PI][6][1].x = 2317;
	picture_information[PI][6][1].y = 805;
	picture_information[PI][6][2].x = 3614;
	picture_information[PI][6][2].y = 1549;
	picture_information[PI][6][3].x = 2618;
	picture_information[PI][6][3].y = 2739;
	// pi,70
	picture_information[PI][7][0].x = 1445;
	picture_information[PI][7][0].y = 2241;
	picture_information[PI][7][1].x = 2070;
	picture_information[PI][7][1].y = 948;
	picture_information[PI][7][2].x = 3573;
	picture_information[PI][7][2].y = 1383;
	picture_information[PI][7][3].x = 3144;
	picture_information[PI][7][3].y = 2788;
	// pi,80
	picture_information[PI][8][0].x = 1051;
	picture_information[PI][8][0].y = 1821;
	picture_information[PI][8][1].x = 1519;
	picture_information[PI][8][1].y = 492;
	picture_information[PI][8][2].x = 3071;
	picture_information[PI][8][2].y = 722;
	picture_information[PI][8][3].x = 2821;
	picture_information[PI][8][3].y = 2114;
	// pi,90
	picture_information[PI][9][0].x = 1249;
	picture_information[PI][9][0].y = 2359;
	picture_information[PI][9][1].x = 1385;
	picture_information[PI][9][1].y = 782;
	picture_information[PI][9][2].x = 3134;
	picture_information[PI][9][2].y = 800;
	picture_information[PI][9][3].x = 3305;
	picture_information[PI][9][3].y = 2343;
	
	// theta,0
	picture_information[THETA][0][0].x = 1443;
	picture_information[THETA][0][0].y = 621;
	picture_information[THETA][0][1].x = 3646;
	picture_information[THETA][0][1].y = 615;
	picture_information[THETA][0][2].x = 3663;
	picture_information[THETA][0][2].y = 2863;
	picture_information[THETA][0][3].x = 1381;
	picture_information[THETA][0][3].y = 2841;
	// theta,5
	picture_information[THETA][1][0].x = 1506;
	picture_information[THETA][1][0].y = 686;
	picture_information[THETA][1][1].x = 3559;
	picture_information[THETA][1][1].y = 687;
	picture_information[THETA][1][2].x = 3606;
	picture_information[THETA][1][2].y = 2789;
	picture_information[THETA][1][3].x = 1427;
	picture_information[THETA][1][3].y = 2778;
	// theta,10
	picture_information[THETA][2][0].x = 1537;
	picture_information[THETA][2][0].y = 759;
	picture_information[THETA][2][1].x = 3504;
	picture_information[THETA][2][1].y = 746;
	picture_information[THETA][2][2].x = 3571;
	picture_information[THETA][2][2].y = 2781;
	picture_information[THETA][2][3].x = 1431;
	picture_information[THETA][2][3].y = 2767;
	// theta,15
	picture_information[THETA][3][0].x = 1584;
	picture_information[THETA][3][0].y = 860;
	picture_information[THETA][3][1].x = 3432;
	picture_information[THETA][3][1].y = 845;
	picture_information[THETA][3][2].x = 3527;
	picture_information[THETA][3][2].y = 2753;
	picture_information[THETA][3][3].x = 1443;
	picture_information[THETA][3][3].y = 2745;
	// theta,20
	picture_information[THETA][4][0].x = 1652;
	picture_information[THETA][4][0].y = 976;
	picture_information[THETA][4][1].x = 3384;
	picture_information[THETA][4][1].y = 965;
	picture_information[THETA][4][2].x = 3512;
	picture_information[THETA][4][2].y = 2738;
	picture_information[THETA][4][3].x = 1485;
	picture_information[THETA][4][3].y = 2731;
	// theta,25
	picture_information[THETA][5][0].x = 1706;
	picture_information[THETA][5][0].y = 1085;
	picture_information[THETA][5][1].x = 3365;
	picture_information[THETA][5][1].y = 1071;
	picture_information[THETA][5][2].x = 3504;
	picture_information[THETA][5][2].y = 2751;
	picture_information[THETA][5][3].x = 1517;
	picture_information[THETA][5][3].y = 2736;
	// theta,30
	picture_information[THETA][6][0].x = 1724;
	picture_information[THETA][6][0].y = 1217;
	picture_information[THETA][6][1].x = 3305;
	picture_information[THETA][6][1].y = 1197;
	picture_information[THETA][6][2].x = 3462;
	picture_information[THETA][6][2].y = 2763;
	picture_information[THETA][6][3].x = 1522;
	picture_information[THETA][6][3].y = 2758;
	// theta,35
	picture_information[THETA][7][0].x = 1779;
	picture_information[THETA][7][0].y = 1353;
	picture_information[THETA][7][1].x = 3289;
	picture_information[THETA][7][1].y = 1336;
	picture_information[THETA][7][2].x = 3455;
	picture_information[THETA][7][2].y = 2781;
	picture_information[THETA][7][3].x = 1561;
	picture_information[THETA][7][3].y = 2772;
	// theta,40
	picture_information[THETA][8][0].x = 1819;
	picture_information[THETA][8][0].y = 1477;
	picture_information[THETA][8][1].x = 3272;
	picture_information[THETA][8][1].y = 1460;
	picture_information[THETA][8][2].x = 3448;
	picture_information[THETA][8][2].y = 2804;
	picture_information[THETA][8][3].x = 1592;
	picture_information[THETA][8][3].y = 2798;
	// theta,45
	picture_information[THETA][9][0].x = 1841;
	picture_information[THETA][9][0].y = 1625;
	picture_information[THETA][9][1].x = 3241;
	picture_information[THETA][9][1].y = 1609;
	picture_information[THETA][9][2].x = 3426;
	picture_information[THETA][9][2].y = 2839;
	picture_information[THETA][9][3].x = 1606;
	picture_information[THETA][9][3].y = 2834;
	// theta,50
	picture_information[THETA][10][0].x = 1867;
	picture_information[THETA][10][0].y = 1740;
	picture_information[THETA][10][1].x = 3229;
	picture_information[THETA][10][1].y = 1722;
	picture_information[THETA][10][2].x = 3420;
	picture_information[THETA][10][2].y = 2872;
	picture_information[THETA][10][3].x = 1629;
	picture_information[THETA][10][3].y = 2868;
	// theta,55
	picture_information[THETA][11][0].x = 1880;
	picture_information[THETA][11][0].y = 1889;
	picture_information[THETA][11][1].x = 3202;
	picture_information[THETA][11][1].y = 1870;
	picture_information[THETA][11][2].x = 3398;
	picture_information[THETA][11][2].y = 2916;
	picture_information[THETA][11][3].x = 1638;
	picture_information[THETA][11][3].y = 2914;
	// theta,60
	picture_information[THETA][12][0].x = 1881;
	picture_information[THETA][12][0].y = 2044;
	picture_information[THETA][12][1].x = 3169;
	picture_information[THETA][12][1].y = 2035;
	picture_information[THETA][12][2].x = 3367;
	picture_information[THETA][12][2].y = 2983;
	picture_information[THETA][12][3].x = 1634;
	picture_information[THETA][12][3].y = 2978;


	if (mode == PI && picture_num<=9)
	{
		for (int i = 0; i < 4; i++)
		{
			output[i] = picture_information[PI][picture_num][i];
		}
	}
	else if (mode == THETA && picture_num <= 12)
	{
		for (int i = 0; i < 4; i++)
		{
			output[i] = picture_information[THETA][picture_num][i];
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			output[i].x = 0;
			output[i].y = 0;
		}
	}
}
void picture_info2(vector output[4], pictures mode, int picture_num)
{
	vector picture_information[5][13][4];
	// pi,0 
	picture_information[PI][0][0].x = 3456;
	picture_information[PI][0][0].y = 1549;
	picture_information[PI][0][1].x = 3779;
	picture_information[PI][0][1].y = 2813;
	picture_information[PI][0][2].x = 1594;
	picture_information[PI][0][2].y = 2820;
	picture_information[PI][0][3].x = 1881;
	picture_information[PI][0][3].y = 1557;
	// pi,10
	picture_information[PI][1][0].x = 3386;
	picture_information[PI][1][0].y = 1228;
	picture_information[PI][1][1].x = 4006;
	picture_information[PI][1][1].y = 2250;
	picture_information[PI][1][2].x = 2045;
	picture_information[PI][1][2].y = 2543;
	picture_information[PI][1][3].x = 1921;
	picture_information[PI][1][3].y = 1389;
	// pi,20
	picture_information[PI][2][0].x = 3271;
	picture_information[PI][2][0].y = 1041;
	picture_information[PI][2][1].x = 4081;
	picture_information[PI][2][1].y = 1856;
	picture_information[PI][2][2].x = 2420;
	picture_information[PI][2][2].y = 2325;
	picture_information[PI][2][3].x = 1944;
	picture_information[PI][2][3].y = 1311;
	// pi,30
	picture_information[PI][3][0].x = 3118;
	picture_information[PI][3][0].y = 875;
	picture_information[PI][3][1].x = 4046;
	picture_information[PI][3][1].y = 1512;
	picture_information[PI][3][2].x = 2703;
	picture_information[PI][3][2].y = 2075;
	picture_information[PI][3][3].x = 1944;
	picture_information[PI][3][3].y = 1229;
	// pi,40
	picture_information[PI][4][0].x = 2926;
	picture_information[PI][4][0].y = 741;
	picture_information[PI][4][1].x = 3925;
	picture_information[PI][4][1].y = 1225;
	picture_information[PI][4][2].x = 2880;
	picture_information[PI][4][2].y = 1832;
	picture_information[PI][4][3].x = 1914;
	picture_information[PI][4][3].y = 1155;
	// pi,50
	picture_information[PI][5][0].x = 2711;
	picture_information[PI][5][0].y = 639;
	picture_information[PI][5][1].x = 3746;
	picture_information[PI][5][1].y = 989;
	picture_information[PI][5][2].x = 2986;
	picture_information[PI][5][2].y = 1610;
	picture_information[PI][5][3].x = 1862;
	picture_information[PI][5][3].y = 1095;
	// pi,60
	picture_information[PI][6][0].x = 2483;
	picture_information[PI][6][0].y = 554;
	picture_information[PI][6][1].x = 3540;
	picture_information[PI][6][1].y = 794;
	picture_information[PI][6][2].x = 3017;
	picture_information[PI][6][2].y = 1400;
	picture_information[PI][6][3].x = 1794;
	picture_information[PI][6][3].y = 1036;
	// pi,70
	picture_information[PI][7][0].x = 2236;
	picture_information[PI][7][0].y = 488;
	picture_information[PI][7][1].x = 3294;
	picture_information[PI][7][1].y = 632;
	picture_information[PI][7][2].x = 2986;
	picture_information[PI][7][2].y = 1207;
	picture_information[PI][7][3].x = 1710;
	picture_information[PI][7][3].y = 988;
	// pi,80
	picture_information[PI][8][0].x = 1970;
	picture_information[PI][8][0].y = 452;
	picture_information[PI][8][1].x = 3021;
	picture_information[PI][8][1].y = 511;
	picture_information[PI][8][2].x = 2903;
	picture_information[PI][8][2].y = 1044;
	picture_information[PI][8][3].x = 1609;
	picture_information[PI][8][3].y = 952;
	// pi,90
	picture_information[PI][9][0].x = 1712;
	picture_information[PI][9][0].y = 427;
	picture_information[PI][9][1].x = 2750;
	picture_information[PI][9][1].y = 412;
	picture_information[PI][9][2].x = 2785;
	picture_information[PI][9][2].y = 903;
	picture_information[PI][9][3].x = 1499;
	picture_information[PI][9][3].y = 921;

	// theta,0
	picture_information[THETA][0][0].x = 1443;
	picture_information[THETA][0][0].y = 621;
	picture_information[THETA][0][1].x = 3646;
	picture_information[THETA][0][1].y = 615;
	picture_information[THETA][0][2].x = 3663;
	picture_information[THETA][0][2].y = 2863;
	picture_information[THETA][0][3].x = 1381;
	picture_information[THETA][0][3].y = 2841;
	// theta,5
	picture_information[THETA][1][0].x = 1506;
	picture_information[THETA][1][0].y = 686;
	picture_information[THETA][1][1].x = 3559;
	picture_information[THETA][1][1].y = 687;
	picture_information[THETA][1][2].x = 3606;
	picture_information[THETA][1][2].y = 2789;
	picture_information[THETA][1][3].x = 1427;
	picture_information[THETA][1][3].y = 2778;
	// theta,10
	picture_information[THETA][2][0].x = 1537;
	picture_information[THETA][2][0].y = 759;
	picture_information[THETA][2][1].x = 3504;
	picture_information[THETA][2][1].y = 746;
	picture_information[THETA][2][2].x = 3571;
	picture_information[THETA][2][2].y = 2781;
	picture_information[THETA][2][3].x = 1431;
	picture_information[THETA][2][3].y = 2767;
	// theta,15
	picture_information[THETA][3][0].x = 1584;
	picture_information[THETA][3][0].y = 860;
	picture_information[THETA][3][1].x = 3432;
	picture_information[THETA][3][1].y = 845;
	picture_information[THETA][3][2].x = 3527;
	picture_information[THETA][3][2].y = 2753;
	picture_information[THETA][3][3].x = 1443;
	picture_information[THETA][3][3].y = 2745;
	// theta,20
	picture_information[THETA][4][0].x = 1652;
	picture_information[THETA][4][0].y = 976;
	picture_information[THETA][4][1].x = 3384;
	picture_information[THETA][4][1].y = 965;
	picture_information[THETA][4][2].x = 3512;
	picture_information[THETA][4][2].y = 2738;
	picture_information[THETA][4][3].x = 1485;
	picture_information[THETA][4][3].y = 2731;
	// theta,25
	picture_information[THETA][5][0].x = 1706;
	picture_information[THETA][5][0].y = 1085;
	picture_information[THETA][5][1].x = 3365;
	picture_information[THETA][5][1].y = 1071;
	picture_information[THETA][5][2].x = 3504;
	picture_information[THETA][5][2].y = 2751;
	picture_information[THETA][5][3].x = 1517;
	picture_information[THETA][5][3].y = 2736;
	// theta,30
	picture_information[THETA][6][0].x = 1724;
	picture_information[THETA][6][0].y = 1217;
	picture_information[THETA][6][1].x = 3305;
	picture_information[THETA][6][1].y = 1197;
	picture_information[THETA][6][2].x = 3462;
	picture_information[THETA][6][2].y = 2763;
	picture_information[THETA][6][3].x = 1522;
	picture_information[THETA][6][3].y = 2758;
	// theta,35
	picture_information[THETA][7][0].x = 1779;
	picture_information[THETA][7][0].y = 1353;
	picture_information[THETA][7][1].x = 3289;
	picture_information[THETA][7][1].y = 1336;
	picture_information[THETA][7][2].x = 3455;
	picture_information[THETA][7][2].y = 2781;
	picture_information[THETA][7][3].x = 1561;
	picture_information[THETA][7][3].y = 2772;
	// theta,40
	picture_information[THETA][8][0].x = 1819;
	picture_information[THETA][8][0].y = 1477;
	picture_information[THETA][8][1].x = 3272;
	picture_information[THETA][8][1].y = 1460;
	picture_information[THETA][8][2].x = 3448;
	picture_information[THETA][8][2].y = 2804;
	picture_information[THETA][8][3].x = 1592;
	picture_information[THETA][8][3].y = 2798;
	// theta,45
	picture_information[THETA][9][0].x = 1841;
	picture_information[THETA][9][0].y = 1625;
	picture_information[THETA][9][1].x = 3241;
	picture_information[THETA][9][1].y = 1609;
	picture_information[THETA][9][2].x = 3426;
	picture_information[THETA][9][2].y = 2839;
	picture_information[THETA][9][3].x = 1606;
	picture_information[THETA][9][3].y = 2834;
	// theta,50
	picture_information[THETA][10][0].x = 1867;
	picture_information[THETA][10][0].y = 1740;
	picture_information[THETA][10][1].x = 3229;
	picture_information[THETA][10][1].y = 1722;
	picture_information[THETA][10][2].x = 3420;
	picture_information[THETA][10][2].y = 2872;
	picture_information[THETA][10][3].x = 1629;
	picture_information[THETA][10][3].y = 2868;
	// theta,55
	picture_information[THETA][11][0].x = 1880;
	picture_information[THETA][11][0].y = 1889;
	picture_information[THETA][11][1].x = 3202;
	picture_information[THETA][11][1].y = 1870;
	picture_information[THETA][11][2].x = 3398;
	picture_information[THETA][11][2].y = 2916;
	picture_information[THETA][11][3].x = 1638;
	picture_information[THETA][11][3].y = 2914;
	// theta,60
	picture_information[THETA][12][0].x = 1881;
	picture_information[THETA][12][0].y = 2044;
	picture_information[THETA][12][1].x = 3169;
	picture_information[THETA][12][1].y = 2035;
	picture_information[THETA][12][2].x = 3367;
	picture_information[THETA][12][2].y = 2983;
	picture_information[THETA][12][3].x = 1634;
	picture_information[THETA][12][3].y = 2978;
	// roll,0
	picture_information[ROLL][0][0].x = 3585;
	picture_information[ROLL][0][0].y = 2243;
	picture_information[ROLL][0][1].x = 2437;
	picture_information[ROLL][0][1].y = 2967;
	picture_information[ROLL][0][2].x = 1733;
	picture_information[ROLL][0][2].y = 1349;
	picture_information[ROLL][0][3].x = 3021;
	picture_information[ROLL][0][3].y = 865;
	// roll,10
	picture_information[ROLL][1][0].x = 3493;
	picture_information[ROLL][1][0].y = 2412;
	picture_information[ROLL][1][1].x = 2250;
	picture_information[ROLL][1][1].y = 2933;
	picture_information[ROLL][1][2].x = 1831;
	picture_information[ROLL][1][2].y = 1217;
	picture_information[ROLL][1][3].x = 3171;
	picture_information[ROLL][1][3].y = 961;
	// roll,20
	picture_information[ROLL][2][0].x = 3352;
	picture_information[ROLL][2][0].y = 2570;
	picture_information[ROLL][2][1].x = 2050;
	picture_information[ROLL][2][1].y = 2864;
	picture_information[ROLL][2][2].x = 1937;
	picture_information[ROLL][2][2].y = 1100;
	picture_information[ROLL][2][3].x = 3291;
	picture_information[ROLL][2][3].y = 1086;
	// roll,30
	picture_information[ROLL][3][0].x = 3247;
	picture_information[ROLL][3][0].y = 2660;
	picture_information[ROLL][3][1].x = 1919;
	picture_information[ROLL][3][1].y = 2768;
	picture_information[ROLL][3][2].x = 2050;
	picture_information[ROLL][3][2].y = 1000;
	picture_information[ROLL][3][3].x = 3388;
	picture_information[ROLL][3][3].y = 1179;
	// roll,40
	picture_information[ROLL][4][0].x = 3059;
	picture_information[ROLL][4][0].y = 2766;
	picture_information[ROLL][4][1].x = 1739;
	picture_information[ROLL][4][1].y = 2641;
	picture_information[ROLL][4][2].x = 2189;
	picture_information[ROLL][4][2].y = 919;
	picture_information[ROLL][4][3].x = 3461;
	picture_information[ROLL][4][3].y = 1335;
	// roll,50
	picture_information[ROLL][5][0].x = 2822;
	picture_information[ROLL][5][0].y = 2856;
	picture_information[ROLL][5][1].x = 1563;
	picture_information[ROLL][5][1].y = 2471;
	picture_information[ROLL][5][2].x = 2350;
	picture_information[ROLL][5][2].y = 871;
	picture_information[ROLL][5][3].x = 3501;
	picture_information[ROLL][5][3].y = 1537;
	// roll,60
	picture_information[ROLL][6][0].x = 2631;
	picture_information[ROLL][6][0].y = 2879;
	picture_information[ROLL][6][1].x = 1460;
	picture_information[ROLL][6][1].y = 2286;
	picture_information[ROLL][6][2].x = 2510;
	picture_information[ROLL][6][2].y = 842;
	picture_information[ROLL][6][3].x = 3523;
	picture_information[ROLL][6][3].y = 1695;
	// roll,70
	picture_information[ROLL][7][0].x = 2413;
	picture_information[ROLL][7][0].y = 2899;
	picture_information[ROLL][7][1].x = 1389;
	picture_information[ROLL][7][1].y = 2087;
	picture_information[ROLL][7][2].x = 2704;
	picture_information[ROLL][7][2].y = 876;
	picture_information[ROLL][7][3].x = 3519;
	picture_information[ROLL][7][3].y = 1905;
	// roll,80
	picture_information[ROLL][8][0].x = 2242;
	picture_information[ROLL][8][0].y = 2850;
	picture_information[ROLL][8][1].x = 1341;
	picture_information[ROLL][8][1].y = 1903;
	picture_information[ROLL][8][2].x = 2814;
	picture_information[ROLL][8][2].y = 883;
	picture_information[ROLL][8][3].x = 3471;
	picture_information[ROLL][8][3].y = 2017;
	// roll,90
	picture_information[ROLL][9][0].x = 2025;
	picture_information[ROLL][9][0].y = 2766;
	picture_information[ROLL][9][1].x = 1322;
	picture_information[ROLL][9][1].y = 1668;
	picture_information[ROLL][9][2].x = 2960;
	picture_information[ROLL][9][2].y = 936;
	picture_information[ROLL][9][3].x = 3384;
	picture_information[ROLL][9][3].y = 2172;
	//move_position,0
	picture_information[MOVING_POSITION][0][0].x = 2559;
	picture_information[MOVING_POSITION][0][0].y = 3226;
	picture_information[MOVING_POSITION][0][1].x = 1963;
	picture_information[MOVING_POSITION][0][1].y = 2036;
	picture_information[MOVING_POSITION][0][2].x = 3051;
	picture_information[MOVING_POSITION][0][2].y = 1978;
	picture_information[MOVING_POSITION][0][3].x = 3691;
	picture_information[MOVING_POSITION][0][3].y = 3026;
	//move_position,1
	picture_information[MOVING_POSITION][1][0].x = 1623;
	picture_information[MOVING_POSITION][1][0].y = 3248;
	picture_information[MOVING_POSITION][1][1].x = 1045;
	picture_information[MOVING_POSITION][1][1].y = 2048;
	picture_information[MOVING_POSITION][1][2].x = 2185;
	picture_information[MOVING_POSITION][1][2].y = 1986;
	picture_information[MOVING_POSITION][1][3].x = 2801;
	picture_information[MOVING_POSITION][1][3].y = 3038;
	//move_position,2
	picture_information[MOVING_POSITION][2][0].x = 1489;
	picture_information[MOVING_POSITION][2][0].y = 3263;
	picture_information[MOVING_POSITION][2][1].x = 945;
	picture_information[MOVING_POSITION][2][1].y = 2061;
	picture_information[MOVING_POSITION][2][2].x = 2111;
	picture_information[MOVING_POSITION][2][2].y = 2003;
	picture_information[MOVING_POSITION][2][3].x = 2705;
	picture_information[MOVING_POSITION][2][3].y = 3055;
	//move_position,3
	picture_information[MOVING_POSITION][3][0].x = 1197;
	picture_information[MOVING_POSITION][3][0].y = 3289;
	picture_information[MOVING_POSITION][3][1].x = 691;
	picture_information[MOVING_POSITION][3][1].y = 2093;
	picture_information[MOVING_POSITION][3][2].x = 1881;
	picture_information[MOVING_POSITION][3][2].y = 2035;
	picture_information[MOVING_POSITION][3][3].x = 2443;
	picture_information[MOVING_POSITION][3][3].y = 3085;
	//move_position,4
	picture_information[MOVING_POSITION][4][0].x = 1085;
	picture_information[MOVING_POSITION][4][0].y = 3267;
	picture_information[MOVING_POSITION][4][1].x = 609;
	picture_information[MOVING_POSITION][4][1].y = 2067;
	picture_information[MOVING_POSITION][4][2].x = 1823;
	picture_information[MOVING_POSITION][4][2].y = 2011;
	picture_information[MOVING_POSITION][4][3].x = 2365;
	picture_information[MOVING_POSITION][4][3].y = 3067;
	//move_position,5
	picture_information[MOVING_POSITION][5][0].x = 717;
	picture_information[MOVING_POSITION][5][0].y = 3267;
	picture_information[MOVING_POSITION][5][1].x = 277;
	picture_information[MOVING_POSITION][5][1].y = 2073;
	picture_information[MOVING_POSITION][5][2].x = 1515;
	picture_information[MOVING_POSITION][5][2].y = 2019;
	picture_information[MOVING_POSITION][5][3].x = 2035;
	picture_information[MOVING_POSITION][5][3].y = 3073;
	//fix_position,0
	picture_information[FIX_POSISION][0][0].x = 1599;
	picture_information[FIX_POSISION][0][0].y = 2466;
	picture_information[FIX_POSISION][0][1].x = 2199;
	picture_information[FIX_POSISION][0][1].y = 1045;
	picture_information[FIX_POSISION][0][2].x = 3787;
	picture_information[FIX_POSISION][0][2].y = 1053;
	picture_information[FIX_POSISION][0][3].x = 3319;
	picture_information[FIX_POSISION][0][3].y = 2635;
	//fix_position,1
	picture_information[FIX_POSISION][1][0].x = 9;
	picture_information[FIX_POSISION][1][0].y = 2521;
	picture_information[FIX_POSISION][1][1].x = 645;
	picture_information[FIX_POSISION][1][1].y = 1053;
	picture_information[FIX_POSISION][1][2].x = 2233;
	picture_information[FIX_POSISION][1][2].y = 1061;
	picture_information[FIX_POSISION][1][3].x = 1761;
	picture_information[FIX_POSISION][1][3].y = 2645;
	//fix_position,2
	picture_information[FIX_POSISION][2][0].x = 2881;
	picture_information[FIX_POSISION][2][0].y = 2461;
	picture_information[FIX_POSISION][2][1].x = 3477;
	picture_information[FIX_POSISION][2][1].y = 1045;
	picture_information[FIX_POSISION][2][2].x = 5129;
	picture_information[FIX_POSISION][2][2].y = 1057;
	picture_information[FIX_POSISION][2][3].x = 4641;
	picture_information[FIX_POSISION][2][3].y = 2673;
	//fix_position,3
	picture_information[FIX_POSISION][3][0].x = 2253;
	picture_information[FIX_POSISION][3][0].y = 2457;
	picture_information[FIX_POSISION][3][1].x = 2845;
	picture_information[FIX_POSISION][3][1].y = 1037;
	picture_information[FIX_POSISION][3][2].x = 4457;
	picture_information[FIX_POSISION][3][2].y = 1041;
	picture_information[FIX_POSISION][3][3].x = 3985;
	picture_information[FIX_POSISION][3][3].y = 2645;
	//fix_position,4
	picture_information[FIX_POSISION][4][0].x = 1397;
	picture_information[FIX_POSISION][4][0].y = 1785;
	picture_information[FIX_POSISION][4][1].x = 2001;
	picture_information[FIX_POSISION][4][1].y = 345;
	picture_information[FIX_POSISION][4][2].x = 3605;
	picture_information[FIX_POSISION][4][2].y = 357;
	picture_information[FIX_POSISION][4][3].x = 3121;
	picture_information[FIX_POSISION][4][3].y = 1937;
	//fix_position,5
	picture_information[FIX_POSISION][5][0].x = 1317;
	picture_information[FIX_POSISION][5][0].y = 1521;
	picture_information[FIX_POSISION][5][1].x = 1905;
	picture_information[FIX_POSISION][5][1].y = 77;
	picture_information[FIX_POSISION][5][2].x = 3525;
	picture_information[FIX_POSISION][5][2].y = 69;
	picture_information[FIX_POSISION][5][3].x = 3045;
	picture_information[FIX_POSISION][5][3].y = 1669;
	//fix_position,6
	picture_information[FIX_POSISION][6][0].x = 1533;
	picture_information[FIX_POSISION][6][0].y = 2869;
	picture_information[FIX_POSISION][6][1].x = 2099;
	picture_information[FIX_POSISION][6][1].y = 1430;
	picture_information[FIX_POSISION][6][2].x = 3669;
	picture_information[FIX_POSISION][6][2].y = 1410;
	picture_information[FIX_POSISION][6][3].x = 3243;
	picture_information[FIX_POSISION][6][3].y = 3001;
	//fix_position,7
	picture_information[FIX_POSISION][7][0].x = 2745;							
	picture_information[FIX_POSISION][7][0].y = 1533;
	picture_information[FIX_POSISION][7][1].x = 3313;
	picture_information[FIX_POSISION][7][1].y = 93;
	picture_information[FIX_POSISION][7][2].x = 4985;
	picture_information[FIX_POSISION][7][2].y = 49;
	picture_information[FIX_POSISION][7][3].x = 4495;
	picture_information[FIX_POSISION][7][3].y = 1683;
	//fix_position,8
	picture_information[FIX_POSISION][8][0].x = 371;	
	picture_information[FIX_POSISION][8][0].y = 3035;
	picture_information[FIX_POSISION][8][1].x = 973;
	picture_information[FIX_POSISION][8][1].y = 1569;
	picture_information[FIX_POSISION][8][2].x = 2533;
	picture_information[FIX_POSISION][8][2].y = 1543;
	picture_information[FIX_POSISION][8][3].x = 2093;
	picture_information[FIX_POSISION][8][3].y = 3129;

	if (mode == PI && picture_num <= 9)
	{
		for (int i = 0; i < 4; i++)
		{
			output[i] = picture_information[PI][picture_num][i];
		}
	}
	else if (mode == THETA && picture_num <= 12)
	{
		for (int i = 0; i < 4; i++)
		{
			output[i] = picture_information[THETA][picture_num][i];
		}
	}
	else if (mode == ROLL&& picture_num <= 9)
	{
		for (int i = 0; i < 4; i++)
		{
			output[i] = picture_information[ROLL][picture_num][i];
		}
	}
	else if (mode == MOVING_POSITION && picture_num <= 5)
	{
		for (int i = 0; i < 4; i++)
		{
			output[i] = picture_information[MOVING_POSITION][picture_num][i];
		}
	}
	else if (mode == FIX_POSISION && picture_num <= 8)
	{
		for (int i = 0; i < 4; i++)
		{
			output[i] = picture_information[FIX_POSISION][picture_num][i];
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			output[i].x = 0;
			output[i].y = 0;
		}
	}
}
