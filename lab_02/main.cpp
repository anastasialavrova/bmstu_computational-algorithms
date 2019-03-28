#include<iostream>
#include<cmath>

using namespace std;

float f(float x)
{
	float y = x*x;
	return y;
}

void interpolate(float **mtrx, float x, int cnt)
{
	int left = 0;
	int right = cnt - 1;
	int search = -1;
	int mid = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (x == mtrx[mid][0])
		{
			search = mid;
			break;
		}
		if (x < mtrx[mid][0])
			right = mid - 1;
		else
			left = mid + 1;
	}

	float *h = (float*)calloc(cnt, sizeof(float));
	float *A = (float*)calloc(cnt, sizeof(float));
	float *B = (float*)calloc(cnt, sizeof(float));
	float *D = (float*)calloc(cnt, sizeof(float));
	float *F = (float*)calloc(cnt, sizeof(float));
	float *a = (float*)calloc(cnt, sizeof(float));
	float *b = (float*)calloc(cnt, sizeof(float));
	float *c = (float*)calloc(cnt + 1, sizeof(float));
	float *d = (float*)calloc(cnt, sizeof(float));
	float *ksi = (float*)calloc(cnt + 1, sizeof(float));
	float *eta = (float*)calloc(cnt + 1, sizeof(float));

	for (int i = 1; i < cnt; i++)
		h[i] = mtrx[i][0] - mtrx[i - 1][0];

	for (int i = 2; i < cnt; i++)
	{
		A[i] = h[i - 1];
		B[i] = -2 * (h[i - 1] + h[i]);
		D[i] = h[i];
		F[i] = -3 * ((mtrx[i][1] - mtrx[i - 1][1]) / h[i] - (mtrx[i - 1][1] - mtrx[i - 2][1]) / h[i - 1]);
	}

	for (int i = 2; i < cnt; i++)
	{
		ksi[i + 1] = D[i] / (B[i] - A[i] * ksi[i]);
		eta[i + 1] = (A[i] * eta[i] + F[i]) / (B[i] - A[i] * ksi[i]);
	}

	for (int i = cnt - 2; i > -1; i--)
		c[i] = ksi[i + 1] * c[i + 1] + eta[i + 1];

	for (int i = 1; i < cnt; i++)
	{
		a[i] = mtrx[i - 1][1];
		b[i] = (mtrx[i][1] - mtrx[i - 1][1]) / h[i] - h[i] / 3 * (c[i + 1] + 2 * c[i]);
	}

	float res = a[mid] + b[mid] * (x - mtrx[mid - 1][0]) + c[mid] * (pow((x - mtrx[mid - 1][0]), 2)) + d[mid] * (pow((x - mtrx[mid - 1][0]), 3));

	cout << "Result = " << res;
	cout << "\n";
	cout << "Result (real) = " << f(x) << "\n";
}

int main()
{
	cout << "Input X: ";
	float x;
	cin >> x;

	freopen("input.txt", "r", stdin);
	int cnt;
	cin >> cnt;

	float **mtrx = (float**)calloc(cnt, sizeof(float*));
	for (int i = 0; i < cnt; i++)
	{
		mtrx[i] = (float*)calloc(2, sizeof(float));
	}

	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cin >> mtrx[i][j];
		}
	}

	cout << "X  " << "Y\n";
	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << mtrx[i][j];
			cout << " ";
		}
		cout << "\n";
	}

	float h = abs(mtrx[0][0] - mtrx[cnt - 1][0]) / cnt;

	interpolate(mtrx, x, cnt);
}