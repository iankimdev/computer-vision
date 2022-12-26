#include"vanish.h"
#include<cmath>

vanish::vanish()
{
	point1_exist = false;
	point2_exist = false;
	point3_exist = false;
	count = 0;
}
void vanish::input_homography(double hmgp[3][3])//호모그래피 행렬 입력
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			homography[i][j] = hmgp[i][j];
		}
	}
}
bool vanish::get_VanishingPoints()
{
	count = 0;

	if (abs(homography[2][0]) >= 0.0000001 )
	{
		vanishing_point1.x = homography[0][0] / homography[2][0];
		vanishing_point1.y = homography[1][0] / homography[2][0];
		point1_exist = true;
		count++;
	}
	else
	{
		vanishing_point1.x = 0;
		vanishing_point1.y = 0;
		point1_exist = false;
	}

	if (abs(homography[2][1]) >= 0.0000001)
	{
		vanishing_point2.x = homography[0][1] / homography[2][1];
		vanishing_point2.y = homography[1][1] / homography[2][1];
		point2_exist = true;
		count++;
	}
	else
	{
		vanishing_point2.x = 0;
		vanishing_point2.y = 0;
		point2_exist = false;
	}

	if (abs(homography[2][0]+ homography[2][1]) >= 0.0000001)
	{
		vanishing_point3.x = (homography[0][0]+ homography[0][1]) / (homography[2][0] + homography[2][1]);
		vanishing_point3.y = (homography[1][0] + homography[1][1]) / (homography[2][0] + homography[2][1]);
		point3_exist = true;
		count++;
	}
	else
	{
		vanishing_point3.x = 0;
		vanishing_point3.y = 0;
		point3_exist = false;
	}

	if (count >= 2)
	{
		return true;
	}
	else
	{
		return false;
	}
	

}

void vanish::get_line(vector v1, vector v2, vector& unit_direct, vector& locate)
{
	double d_x;
	double d_y;
	double mag;
	d_x = v2.x - v1.x;
	d_y = v2.y - v1.y;
	mag = sqrt(d_x*d_x + d_y*d_y);
	unit_direct.x = d_x / mag;
	unit_direct.y = d_y / mag;
	locate.x = (v2.x + v1.x) / 2;
	locate.y = (v2.y + v1.y) / 2;
}
void vanish::get_VanishingLine()
{
	vector unit_direct1;
	vector locate1;
	bool line1_exist = false;
	vector unit_direct2;
	vector locate2;
	bool line2_exist = false;
	vector unit_direct3;
	vector locate3;
	bool line3_exist = false;

	if (point1_exist && point2_exist)
	{
		get_line(vanishing_point1, vanishing_point2, unit_direct1, locate1);
		line1_exist = true;
	}
	if (point2_exist && point3_exist)
	{
		get_line(vanishing_point2, vanishing_point3, unit_direct2, locate2);
		line2_exist = true;
	}
	if (point3_exist && point1_exist)
	{
		get_line(vanishing_point3, vanishing_point1, unit_direct3, locate3);
		line3_exist = true;
	}

	vanishing_line_unit_d = (unit_direct1*(double)line1_exist) + (unit_direct2*(double)line2_exist) + (unit_direct3*(double)line3_exist);
	vanishing_line_unit_d = vanishing_line_unit_d / (sqrt(vanishing_line_unit_d.x*vanishing_line_unit_d.x + vanishing_line_unit_d.y*vanishing_line_unit_d.y));

	vanishing_line_locate = ((locate1*(double)line1_exist) + (locate2*(double)line2_exist) + (locate3*(double)line3_exist)) / ((double)line1_exist + (double)line2_exist + (double)line3_exist);
}
vector vanish::Zero_to_Vanishing_Line()
{
	zero_to_vanishing_line = vanishing_line_locate - (vanishing_line_unit_d*(dot(vanishing_line_unit_d, vanishing_line_locate)));
	return zero_to_vanishing_line;
}
vector vanish::Code_to_Vanishing_Line()
{
	vector modi_center_point(homography[0][2], homography[1][2]);
	vector vanishing_line_locate_p;
	vanishing_line_locate_p = (vanishing_line_locate - modi_center_point);
	code_to_vanishing_line = vanishing_line_locate_p - (vanishing_line_unit_d*(dot(vanishing_line_unit_d, vanishing_line_locate_p)));
	return code_to_vanishing_line;
}

