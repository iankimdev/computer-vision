#pragma once
class vector
{
public:
	vector();
	vector(double X, double Y);
	vector operator+(vector v1);
	vector operator-(vector v1);
	vector operator=(vector v1);
	vector operator*(double d1);
	vector operator/(double d1);
	double x;
	double y;

	friend double dot(vector v1, vector v2);//벡터의 내적
	friend double by(vector v1, vector v2);//벡터의 외적 (3차원좌표를 그릴게 아니므로 그냥 크기만 return)
	friend double mag(vector v1);// 벡터의 크기
};
class homography
{
private:
	double h[3][3];
	double h_r[3][3];
	vector origine[4];
	vector modified[4];
	double** mid_mat;//중간과정에 필요한 매트릭스 8by8 임
	double** cramer_mat;
	double** reverse_mid_mat;//호모그래피 h1~h8을 얻기 위해 만드는 역함수 but 사용 중지 권고 (대신 cramer공식으로 대체)
	void fill_mid_matrix();
	void fill_reverse_mid_matrix();
	void get_cramer_mat(double x[8],int n);
	int sign(int i,int j);// det을 구할 때 쓰이며 
public:
	homography();//setting order no.1
	~homography();
	
	void calc_homography();//setting order no.3
	void calc_homography(vector orig[4], vector modi[4]);
	void calc_inv_homography();

	double Det(double** A, int size);
	double Get_B(double** A,double** B,int i,int j, int size);
	double Det_i_j(double** A,int i,int j,int size);//j행 i열을 제외하고 계산한 Det 

	void input(vector orig[4], vector modi[4]);//setting order no.2
	void output_h(double h_out[3][3]);
	void output_h_r(double h_out_r[3][3]);
	
	void Display_homography();

	vector transform(vector v1);
	vector inv_transform(vector v1);
};