#pragma once
#include<iostream>
#include<iostream>
#include<math.h>
#include<vector>
using namespace std;
class Matrix {
	int rows;//h
	int cols;//l
	vector<vector<double>>data;
public:
	Matrix (int r=1,int c=1):rows(r),cols(c),data(r,vector<double>(c,0)){}

	int getRows() const {
		return rows;
	}
	int getCols() const {
		return cols;
	}	
	// 修改矩阵中的某个元素
	void setElement(int r, int c, double value) {
		if (r >= 0 && r < rows && c >= 0 && c < cols) {
			data[r][c] = value;
		}
	}
	//输入矩阵
	void Matrix_Input() {
		for (int i = 0; i < this->getRows(); i++) {
			for (int j = 0; j < this->getCols(); j++) {
				double x;
				cin >> x;
				this->setElement(i, j, x);
			}
		}
	}
	//打印矩阵
	void display() const {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << data[i][j] << " ";
			}
			cout << endl;
		}
	}
	//设置单位矩阵
	void setIdentity() {
		for (int i = 0; i < this->cols; i++) {
			this->setElement(i, i, 1.0);
		}
	}

	// 获取矩阵中的某个元素
	double getElement(int r, int c) const {
		if (r >= 0 && r < rows && c >= 0 && c < cols) {
			return data[r][c];
		}
		return 0; 
	}
	//矩阵加法
	Matrix operator+(const Matrix& other) const {
		if (rows != other.rows || cols != other.cols) {
			throw invalid_argument("error!");
		}

		Matrix result(rows, cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result.data[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return result;
	}
	//矩阵减法
	Matrix operator-(const Matrix& other) const {
		if (rows != other.rows || cols != other.cols) {
			throw invalid_argument("error!");
		}

		Matrix result(rows, cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result.data[i][j] = data[i][j] - other.data[i][j];
			}
		}
		return result;
	}
	//实数与矩阵相乘
	Matrix operator*(double scalar) const {
		Matrix result(rows, cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result.data[i][j] = data[i][j] * scalar;
			}
		}
		return result;
	}
	//矩阵与矩阵相乘(重载)
	Matrix operator*(const Matrix& other) const {
		if (cols != other.rows) {
			throw invalid_argument("error!");
		}

		Matrix result(rows, other.cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < other.cols; ++j) {
				result.data[i][j] = 0;
				for (int k = 0; k < cols; ++k) {
					result.data[i][j] += data[i][k] * other.data[k][j];
				}
			}
		}
		return result;
	}
	//矩阵转置
	Matrix transpose() const {
		Matrix result(cols, rows);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result.setElement(j, i, data[i][j]);
			}
		}
		return result;
	}
	//矩阵求逆 (高斯消元法)
	Matrix inverse() const {
		if (rows != cols) {
			throw invalid_argument("只有方阵可以求逆。");
		}

		int n = rows;
		Matrix result(n, n); // 初始化单位矩阵
		Matrix copy(*this); // 创建矩阵的副本

		// 初始化单位矩阵
		for (int i = 0; i < n; i++) {
			result.setElement(i, i, 1.0);
		}

		// 高斯消元法
		for (int i = 0; i < n; i++) {
			// 寻找主元素（对角线元素）
			if (copy.data[i][i] == 0) {
				// 尝试与下方行交换
				bool swapped = false;
				for (int j = i + 1; j < n; j++) {
					if (copy.data[j][i] != 0) {
						swap(copy.data[i], copy.data[j]);
						swap(result.data[i], result.data[j]);
						swapped = true;
						break;
					}
				}
				if (!swapped) {
					throw runtime_error("error!");
				}
			}

			// 归一化主元素行
			double pivot = copy.data[i][i];
			for (int j = 0; j < n; j++) {
				copy.data[i][j] /= pivot;
				result.data[i][j] /= pivot;
			}

			// 消去其他行中的该列
			for (int j = 0; j < n; j++) {
				if (i != j) {
					double factor = copy.data[j][i];
					for (int k = 0; k < n; k++) {
						copy.data[j][k] -= factor * copy.data[i][k];
						result.data[j][k] -= factor * result.data[i][k];
					}
				}
			}
		}

		return result;
	}
	
};
//加权最小二乘
Matrix reweightedLeastSquares(Matrix B,Matrix Delta,Matrix P,Matrix X) {
	Matrix L,  X_estimated, V;
	L = B * X + Delta;
	X_estimated = (B.inverse() * P * B).transpose() * B.inverse() * P * L;//X最优估计量
	//V = B * X_estimated - L;//误差方程
	return X_estimated;
}
Matrix Identity(int row, int col) {//生成单位矩阵
	Matrix A(row, col);
	for (int i = 0; i < A.getCols(); i++) {
		A.setElement(i, i, 1.0);
	}
	return A;
}

class KalmanFilter
{
public:
	int stateSize; //状态量个数
	int measSize; //测量变量维度
	int uSize; //输入矩阵维度
	Matrix x;  //状态量
	Matrix z;  //观测量
	Matrix A;  //状态转移矩阵
	Matrix B;  //控制矩阵
	Matrix u;  //输入矩阵
	Matrix P;  //先验估计协方差
	Matrix H;  //观测矩阵
	Matrix R;  //测量噪声协方差
	Matrix Q;  //过程噪声协方差

	KalmanFilter(int stateSize_, int measSize_, int uSize_);
	~KalmanFilter() {}

	void init(Matrix& x_, Matrix& P_, Matrix& R_, Matrix& Q_);
	Matrix predict(Matrix& A_);
	Matrix predict(Matrix& A_, Matrix& B_, Matrix& u_);
	void update(Matrix& H_, Matrix z_meas);
};

KalmanFilter::KalmanFilter(int stateSize_ = 0, int measSize_ = 0, int uSize_ = 0) :stateSize(stateSize_), measSize(measSize_), uSize(uSize_)// sateSize状态量个数  uSize输入的维度
{
	if (stateSize == 0 || measSize == 0)
	{
		std::cerr << "error!\n";
	}

	Matrix x(stateSize, stateSize);

	Matrix A(stateSize, stateSize);
	A.setIdentity();

	Matrix u(uSize,uSize);
	u.transpose();

	Matrix B(stateSize, uSize);

	Matrix P(stateSize, stateSize);
	P.setIdentity();

	Matrix H(measSize, stateSize);

	Matrix z(measSize, measSize);
	
	Matrix Q(stateSize, stateSize);
	
	Matrix R(measSize, measSize);
}

//初始化，卡尔曼滤波初始化只需要初始化初始状态，初始协方差矩阵，初始过程噪声协方差，初始化观测噪声协方差
void KalmanFilter::init(Matrix& x_, Matrix& P_, Matrix& R_, Matrix& Q_)
{
	x = x_;
	P = P_;
	R = R_;
	Q = Q_;
}

//有输入矩阵和控制矩阵的卡尔曼滤波预测过程
Matrix KalmanFilter::predict(Matrix& A_, Matrix& B_, Matrix& u_)
{
	A = A_;
	B = B_;
	u = u_;
	x = A * x + B * u;//根据时刻t-1的状态由状态转换举着预测时刻t的先验估计值，
	
	Matrix A_T = A.transpose();
	P = A * P * A_T + Q;//时刻t先验估计值的的协方差,Q为过程噪声的协方差
	return x;
}

//没有输入矩阵和控制矩阵的卡尔曼滤波预测过程
Matrix KalmanFilter::predict(Matrix& A_)
{
	A = A_;
	x = A * x;
	Matrix A_T = A.transpose();
	P = A * P * A_T + Q;

	return x;
}

void KalmanFilter::update(Matrix& H_, Matrix z_meas)//更新过程
// H_   观测矩阵
//z_means 观测量，由系统真实观测输入
{
	H = H_;
	Matrix temp1, temp2, Ht;
	Ht = H.transpose();
	temp1 = H * P * Ht + R;
	temp2 = temp1.inverse();//(H*P*H'+R)^(-1)
	Matrix K = P * Ht * temp2;
	z = H * x;
	x = x + K * (z_meas - z);
	Matrix I = Identity(stateSize, stateSize);//Identity()单位阵
	P = (I - K * H) * P;
	P.display();
}
//没有输入矩阵和控制矩阵的卡尔曼滤波
void Kalmanfliter_Static(int stateSize_, int measSize_, int uSize_, Matrix& x_, Matrix& P_, Matrix& R_, Matrix& Q_) {
	KalmanFilter kal(stateSize_, measSize_, uSize_);
	kal.init(x_, P_, R_, Q_);
	kal.x = kal.predict(kal.A);
	kal.update(kal.H, kal.z);
}
//有输入矩阵和控制矩阵的卡尔曼滤波
void Kalmanfliter_Dynamic(int stateSize_, int measSize_, int uSize_, Matrix& x_, Matrix& P_, Matrix& R_, Matrix& Q_) {
	KalmanFilter kal( stateSize_, measSize_, uSize_);
	kal.init(x_, P_, R_, Q_);
	kal.x=kal.predict(kal.A, kal.B, kal.u);
	kal.update(kal.H,kal.z);
}




