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
	// �޸ľ����е�ĳ��Ԫ��
	void setElement(int r, int c, double value) {
		if (r >= 0 && r < rows && c >= 0 && c < cols) {
			data[r][c] = value;
		}
	}
	//�������
	void Matrix_Input() {
		for (int i = 0; i < this->getRows(); i++) {
			for (int j = 0; j < this->getCols(); j++) {
				double x;
				cin >> x;
				this->setElement(i, j, x);
			}
		}
	}
	//��ӡ����
	void display() const {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << data[i][j] << " ";
			}
			cout << endl;
		}
	}
	//���õ�λ����
	void setIdentity() {
		for (int i = 0; i < this->cols; i++) {
			this->setElement(i, i, 1.0);
		}
	}

	// ��ȡ�����е�ĳ��Ԫ��
	double getElement(int r, int c) const {
		if (r >= 0 && r < rows && c >= 0 && c < cols) {
			return data[r][c];
		}
		return 0; 
	}
	//����ӷ�
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
	//�������
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
	//ʵ����������
	Matrix operator*(double scalar) const {
		Matrix result(rows, cols);
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result.data[i][j] = data[i][j] * scalar;
			}
		}
		return result;
	}
	//������������(����)
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
	//����ת��
	Matrix transpose() const {
		Matrix result(cols, rows);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				result.setElement(j, i, data[i][j]);
			}
		}
		return result;
	}
	//�������� (��˹��Ԫ��)
	Matrix inverse() const {
		if (rows != cols) {
			throw invalid_argument("ֻ�з���������档");
		}

		int n = rows;
		Matrix result(n, n); // ��ʼ����λ����
		Matrix copy(*this); // ��������ĸ���

		// ��ʼ����λ����
		for (int i = 0; i < n; i++) {
			result.setElement(i, i, 1.0);
		}

		// ��˹��Ԫ��
		for (int i = 0; i < n; i++) {
			// Ѱ����Ԫ�أ��Խ���Ԫ�أ�
			if (copy.data[i][i] == 0) {
				// �������·��н���
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

			// ��һ����Ԫ����
			double pivot = copy.data[i][i];
			for (int j = 0; j < n; j++) {
				copy.data[i][j] /= pivot;
				result.data[i][j] /= pivot;
			}

			// ��ȥ�������еĸ���
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
//��Ȩ��С����
Matrix reweightedLeastSquares(Matrix B,Matrix Delta,Matrix P,Matrix X) {
	Matrix L,  X_estimated, V;
	L = B * X + Delta;
	X_estimated = (B.inverse() * P * B).transpose() * B.inverse() * P * L;//X���Ź�����
	//V = B * X_estimated - L;//����
	return X_estimated;
}
Matrix Identity(int row, int col) {//���ɵ�λ����
	Matrix A(row, col);
	for (int i = 0; i < A.getCols(); i++) {
		A.setElement(i, i, 1.0);
	}
	return A;
}

class KalmanFilter
{
public:
	int stateSize; //״̬������
	int measSize; //��������ά��
	int uSize; //�������ά��
	Matrix x;  //״̬��
	Matrix z;  //�۲���
	Matrix A;  //״̬ת�ƾ���
	Matrix B;  //���ƾ���
	Matrix u;  //�������
	Matrix P;  //�������Э����
	Matrix H;  //�۲����
	Matrix R;  //��������Э����
	Matrix Q;  //��������Э����

	KalmanFilter(int stateSize_, int measSize_, int uSize_);
	~KalmanFilter() {}

	void init(Matrix& x_, Matrix& P_, Matrix& R_, Matrix& Q_);
	Matrix predict(Matrix& A_);
	Matrix predict(Matrix& A_, Matrix& B_, Matrix& u_);
	void update(Matrix& H_, Matrix z_meas);
};

KalmanFilter::KalmanFilter(int stateSize_ = 0, int measSize_ = 0, int uSize_ = 0) :stateSize(stateSize_), measSize(measSize_), uSize(uSize_)// sateSize״̬������  uSize�����ά��
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

//��ʼ�����������˲���ʼ��ֻ��Ҫ��ʼ����ʼ״̬����ʼЭ������󣬳�ʼ��������Э�����ʼ���۲�����Э����
void KalmanFilter::init(Matrix& x_, Matrix& P_, Matrix& R_, Matrix& Q_)
{
	x = x_;
	P = P_;
	R = R_;
	Q = Q_;
}

//���������Ϳ��ƾ���Ŀ������˲�Ԥ�����
Matrix KalmanFilter::predict(Matrix& A_, Matrix& B_, Matrix& u_)
{
	A = A_;
	B = B_;
	u = u_;
	x = A * x + B * u;//����ʱ��t-1��״̬��״̬ת������Ԥ��ʱ��t���������ֵ��
	
	Matrix A_T = A.transpose();
	P = A * P * A_T + Q;//ʱ��t�������ֵ�ĵ�Э����,QΪ����������Э����
	return x;
}

//û���������Ϳ��ƾ���Ŀ������˲�Ԥ�����
Matrix KalmanFilter::predict(Matrix& A_)
{
	A = A_;
	x = A * x;
	Matrix A_T = A.transpose();
	P = A * P * A_T + Q;

	return x;
}

void KalmanFilter::update(Matrix& H_, Matrix z_meas)//���¹���
// H_   �۲����
//z_means �۲�������ϵͳ��ʵ�۲�����
{
	H = H_;
	Matrix temp1, temp2, Ht;
	Ht = H.transpose();
	temp1 = H * P * Ht + R;
	temp2 = temp1.inverse();//(H*P*H'+R)^(-1)
	Matrix K = P * Ht * temp2;
	z = H * x;
	x = x + K * (z_meas - z);
	Matrix I = Identity(stateSize, stateSize);//Identity()��λ��
	P = (I - K * H) * P;
	P.display();
}
//û���������Ϳ��ƾ���Ŀ������˲�
void Kalmanfliter_Static(int stateSize_, int measSize_, int uSize_, Matrix& x_, Matrix& P_, Matrix& R_, Matrix& Q_) {
	KalmanFilter kal(stateSize_, measSize_, uSize_);
	kal.init(x_, P_, R_, Q_);
	kal.x = kal.predict(kal.A);
	kal.update(kal.H, kal.z);
}
//���������Ϳ��ƾ���Ŀ������˲�
void Kalmanfliter_Dynamic(int stateSize_, int measSize_, int uSize_, Matrix& x_, Matrix& P_, Matrix& R_, Matrix& Q_) {
	KalmanFilter kal( stateSize_, measSize_, uSize_);
	kal.init(x_, P_, R_, Q_);
	kal.x=kal.predict(kal.A, kal.B, kal.u);
	kal.update(kal.H,kal.z);
}




