#include"homography.h"
#include<cmath>
#include<iostream>
#include<iomanip>

using namespace std;



vector::vector()
{
	x = 0;
	y = 0;
}
vector::vector(double X, double Y)
{
	x = X;
	y = Y;
}
vector vector::operator+(vector v1)
{
	vector tmp;
	tmp.x = x + v1.x;
	tmp.y = y + v1.y;
	return tmp;
}
vector vector::operator-(vector v1)
{
	vector tmp;
	tmp.x = x - v1.x;
	tmp.y = y - v1.y;
	return tmp;
}
vector vector::operator=(vector v1)
{
	x = v1.x;
	y = v1.y;
	return *this;
}
vector vector::operator*(double d1)
{
	vector tmp_v;

	tmp_v.x = x * d1;
	tmp_v.y = y * d1;

	return tmp_v;
}
vector vector::operator/(double d1)
{
	vector tmp_v;
	
	tmp_v.x = x / d1;
	tmp_v.y = y / d1;

	return tmp_v;
}

double dot(vector v1, vector v2)//벡터 내적
{
	vector tmp_v;
	tmp_v.x = v1.x * v2.x;
	tmp_v.y = v1.y * v2.y;

	return tmp_v.x + tmp_v.y;
}
double by(vector v1, vector v2)//벡터 외적(크기만 출력)
{
	vector tmp_v;
	tmp_v.x = v1.x * v2.y;
	tmp_v.y = -(v1.y * v2.x);

	return tmp_v.x + tmp_v.y;
}
double mag(vector v1)//벡터 크기
{
	return sqrt(v1.x*v1.x + v1.y*v1.y);
}

homography::homography()//초기화 
{
	mid_mat = new double*[8];
	reverse_mid_mat = new double*[8];
	cramer_mat = new double*[8];

	for (int i = 0; i < 8; i++)
	{
		mid_mat[i] = new double[8];
		reverse_mid_mat[i] = new double[8];
		cramer_mat[i] = new double[8];
	}
}
homography::~homography()
{

	for (int i = 0; i < 8; i++)
	{
		delete[] mid_mat[i];
		delete[] reverse_mid_mat[i];
		delete[] cramer_mat[i];
	}
	delete[] mid_mat;
	delete[] reverse_mid_mat;
	delete[] cramer_mat;
}
void homography::fill_mid_matrix()//8*8 행렬에 value 채우기
{
	for (int k = 0; k < 4; k++)
	{
		mid_mat[2*k][0] = origine[k].x;
		mid_mat[2 * k][1] = origine[k].y;
		mid_mat[2 * k][2] = 1;
		mid_mat[2 * k][3] = 0;
		mid_mat[2 * k][4] = 0;
		mid_mat[2 * k][5] = 0;
		mid_mat[2 * k][6] = -(origine[k].x * modified[k].x);
		mid_mat[2 * k][7] = -(origine[k].y * modified[k].x);

		mid_mat[2 * k + 1][0] = 0;
		mid_mat[2 * k + 1][1] = 0;
		mid_mat[2 * k + 1][2] = 0;
		mid_mat[2 * k + 1][3] = origine[k].x;
		mid_mat[2 * k + 1][4] = origine[k].y;
		mid_mat[2 * k + 1][5] = 1;
		mid_mat[2 * k + 1][6] = -(origine[k].x * modified[k].y);
		mid_mat[2 * k + 1][7] = -(origine[k].y * modified[k].y);
	}
}
void homography::fill_reverse_mid_matrix()//안씀
{
	double det_M;
	det_M = Det(mid_mat, 8);

	if (det_M != 0)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if ((i % 2) + (j % 2) == 1)
				{
					reverse_mid_mat[i][j] = -(Det_i_j(mid_mat, j, i, 8) / det_M);// i,j -> j,i 인것이 포인트
				}
				else
				{
					reverse_mid_mat[i][j] = (Det_i_j(mid_mat, j, i, 8) / det_M);
				}
			}
		}
	}
	else
	{
		cout << "error: det is zero(rev matrix don`t exist)" << endl;
	}
}

void homography::get_cramer_mat(double x[8], int n)//cramer 공식 참고
{
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			cramer_mat[j][i] = mid_mat[j][i];
		}
	}
	for (int j = 0; j < 8; j++)
	{
		cramer_mat[j][n] = x[j];
	}
}
int homography::sign(int i, int j)//det 구할때 부호 정해주는 함수 
{
	if ((i + j) % 2 == 0)
	{
		return 1;
	}
	else             //if ((i + j) % 2 == 1)
	{
		return -1;
	}
}

void homography::input(vector orig[4], vector modi[4])//좌표 4쌍 입력
{
	for (int i = 0; i < 4; i++)
	{
		origine[i] = orig[i];
		modified[i] = modi[i];
	}
}

void homography::calc_homography()//input() function 다음에 사용할 것
{
	fill_mid_matrix();
	//fill_reverse_mid_matrix(); // 사용 중지 권고
	
	double x[8] = { modified[0].x,modified[0].y,modified[1].x,modified[1].y, modified[2].x,modified[2].y, modified[3].x,modified[3].y };
	double H_8[8] = { 0, };

	for (int n = 0; n < 8; n++)
	{
		
			get_cramer_mat(x, n);
			H_8[n] = Det(cramer_mat,8)/Det(mid_mat,8);
		
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			h[i][j] = H_8[3 * i + j];
		}
	}
	h[2][2] = 1;
}
void homography::calc_homography(vector orig[4], vector modi[4])//input(vector orig[4], vector modi[4])+calc_homography()
{
	for (int i = 0; i < 4; i++)
	{
		origine[i] = orig[i];
		modified[i] = modi[i];
	}
	calc_homography();
}
void homography::calc_inv_homography()// 역 호모그래피 구하는거
{
	vector tmp_orig[4];
	vector tmp_modi[4];

	for (int i = 0; i < 4; i++)
	{
		tmp_orig[i] = origine[i];
		tmp_modi[i] = modified[i];
	}
	for (int i = 0; i < 4; i++)
	{
		origine[i] = tmp_modi[i];
		modified[i] = tmp_orig[i];
	}

	////
	fill_mid_matrix();

	double x[8] = { modified[0].x,modified[0].y,modified[1].x,modified[1].y, modified[2].x,modified[2].y, modified[3].x,modified[3].y };
	double H_8[8] = { 0, };

	for (int n = 0; n < 8; n++)
	{

		get_cramer_mat(x, n);
		H_8[n] = Det(cramer_mat, 8) / Det(mid_mat, 8);

	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			h_r[i][j] = H_8[3 * i + j];
		}
	}
	h_r[2][2] = 1;
	////

	for (int i = 0; i < 4; i++)
	{
		origine[i] = tmp_orig[i];
		modified[i] = tmp_modi[i];
	}
	fill_mid_matrix();
}

double homography::Det(double** A, int size)// 선형대수의 determinant 참고
{
	double result = 0;
	if (size == 2)
	{
		result = A[0][0]*A[1][1] - A[0][1]*A[1][0];
		return result;
	}
	else if (size < 2)
	{
		cout << "size_error"<<endl;
		return 0;
	}
	double** B = new double*[size-1];
	for (int i = 0; i < size - 1; i++)
	{ 
		B[i] = new double[size - 1];
	}

	for (int i = 0; i < size; i++)
	{
		Get_B(A, B, i,0,size);// B란? 행렬A에서 i열 j=0 행 을 제외하여 새로 만들어진 행렬이다.
		result += sign(0,i) * A[0][i] * Det(B, size - 1);// i 와 j의 순서가 바뀌어 헷갈릴수 있지만 알아서 이해해주길 바람
	}

	for (int i = 0; i < size - 1; i++)
	{
		delete[] B[i];
	}
	delete[] B;

	return result;
}
double homography::Get_B(double** A, double** B,int i,int j, int size)//A는 큰행렬(n * n 행렬) B는 작은행렬(n-1 * n-1 행렬)
{
	int num_x = 0;
	int num_y = 0;
	for (int y = 0; y < size - 1; y++)
	{
		for (int x = 0; x < size - 1; x++)
		{
			if (x >= i)
			{
				num_x = x + 1;
				
			}
			else
			{
				num_x = x;
				
			}
			if (y >= j)
			{
				num_y = y + 1;
			}
			else
			{
				num_y = y;
			}
			B[y][x] = A[num_y][num_x];
		}
	}
	return 0;
}
double homography::Det_i_j(double** A, int i, int j, int size)//Get_B + Det
{
	double tmp_det = 0;

	int fst_num_x = (i + 1) % size;
	int num_x = 0;
	int fst_num_y = (j + 1) % size;
	int num_y = 0;
	for (int y = 0; y < size - 1; y++)
	{
		for (int x = 0; x < size - 1; x++)
		{
			if (size == 2)
			{
				int test = 1;
			}
			num_x = (fst_num_x + x) % size;
			num_y = (fst_num_y + y) % size;
		}
	}
	if (size == 2)
	{
		if (num_x == 0 && num_y == 0)
		{
			return A[1][1];
		}
		else if (num_x == 0 && num_y == 1)
		{
			return -A[1][0];
		}
		else if (num_x == 1 && num_y == 0)
		{
			return -A[0][1];
		}
		else if (num_x == 1 && num_y == 1)
		{
			return A[0][0];
		}
	}
	double** B = new double*[size - 1];
	for (int i = 0; i < size - 1; i++)
	{
		B[i] = new double[size - 1];
	}
	Get_B(A, B, i, j, size);
	tmp_det=Det(B,size-1);
	for (int i = 0; i < size - 1; i++)
	{
		delete[] B[i];
	}
	delete[] B;

	return tmp_det;
}

void homography::output_h(double h_out[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			h_out[i][j] = h[i][j];
		}
	}
}
void homography::output_h_r(double h_out_r[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			h_out_r[i][j] = h_r[i][j];
		}
	}
}

void homography::Display_homography()
{
	for (int i = 0; i < 3; i++)
	{
		cout << setw(15) << h[i][0] << setw(15) << h[i][1] << setw(15) << h[i][2] << endl;
	}
}

vector homography::transform(vector v1)// 호모그래피 변환 (projective transform)-> 네이버에 다크프로그래머를 검색하세요
{
	double w = h[2][0] * v1.x + h[2][1] * v1.y + 1.0;
	vector v2;
	if (w != 0)
	{
		v2.x = (h[0][0] * v1.x + h[0][1] * v1.y + h[0][2]) / w;
		v2.y = (h[1][0] * v1.x + h[1][1] * v1.y + h[1][2]) / w;
		return v2;
	}
	else
	{
		v2.x = 0;
		v2.y = 0;
		cout << "x,y 값은 무한대로 발산" << endl;
		return v2;
	}
}
vector homography::inv_transform(vector v1)
{
	double w = h_r[2][0] * v1.x + h_r[2][1] * v1.y + 1.0;
	vector v2;
	if (w != 0)
	{
		v2.x = (h_r[0][0] * v1.x + h_r[0][1] * v1.y + h_r[0][2]) / w;
		v2.y = (h_r[1][0] * v1.x + h_r[1][1] * v1.y + h_r[1][2]) / w;
		return v2;
	}
	else
	{
		v2.x = 0;
		v2.y = 0;
		cout << "x,y 값은 무한대로 발산" << endl;
		return v2;
	}

}