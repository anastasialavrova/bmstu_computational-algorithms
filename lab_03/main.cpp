#include<iostream>
#include<cmath>

using namespace std;

float f(float x, float y)
{
	float z = x*x + y*y;
	return z;
}

float div_diff(float x1, float x2, float y1, float y2)
{
	if (x1 - x2 == 0)
		cout << "WARNING!";
	return (y1 - y2) / (x1 - x2);
}

void calculation_table(float **mtrx, int st, int n)
{
	float res;
	int k = n;
	//cout << "\nn = " << n;
	//cout << "\nk = " << k;
	for (int z = 0; z < n - 1; z++)
	{
		for (int i = 0; i < k - 1; i++)
		{
			/*cout << "\nz = " << z;
			cout << "\ni = " << i;
			cout << "\nmtrx[i][0] = " << mtrx[i][0];
			cout << "\nmtrx[i + (z + 1)][0] = " << mtrx[i + (z + 1)][0];
			cout << "\nmtrx[i][z + 1] = " << mtrx[i][z + 1];
			cout << "\nmtrx[i + 1][z + 1] = " << mtrx[i + 1][z + 1];
			cout << "\n";*/
			res = div_diff(mtrx[i][0], mtrx[i + (z + 1)][0], mtrx[i][z + 1], mtrx[i + 1][z + 1]);
			mtrx[i][z + 2] = res;
		}
		k--;
	}

	/*cout << "\n";
	for (int i = st; i < n; i++)
	{
		for (int j = 0; j <= n - st; j++)
		{
			cout << mtrx[i][j] << " ";
		}
		cout << "\n";
	}*/

}

float calculation_func(float **mtrx, int n, float x)
{
	float res = 0, mid_res = 1;
	float y = mtrx[0][1];
	res = y;
	for (int i = 0; i < n - 1; i++)
	{
		mid_res *= (x - mtrx[i][0]);
		res += mid_res * mtrx[0][i + 2];
	}
	//cout << "\nResult: ";
	//cout << res;
	return res;
}

float create_table(float x, int cnt, int n, float *x1, float *x2)
{
	float **mtrx = (float**)calloc(cnt + 1, sizeof(float*));
	for (int i = 0; i < cnt; i++)
	{
		mtrx[i] = (float*)calloc(cnt + 1, sizeof(float));
	}

	for (int i = 0; i < cnt; i++)
	{
		mtrx[i][0] = x1[i + 1];
	}

	for (int i = 0; i < cnt; i++)
	{
		mtrx[i][1] = x2[i + 1];
	}

	int st = 0;
	int fn = cnt - 1;
	if (cnt < n)
	{
		cout << "Error!\n";
	}
	else if (n < cnt)
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
		n++;
		int upper = n / 2;
		int lower = n - upper;
		if (mid + lower >= cnt)
		{
			int t = lower;
			lower = upper;
			upper = t;
		}
		int i = mid - upper + 1, j = 0;
		if (i >= 0 && mid + lower < cnt)
		{
			st = i; fn = mid + lower;
		}
		else if (i < 0)
		{
			st = 0; fn = n;
		}
		else
		{
			fn = cnt - 1; st = fn - n + 1;
		}
	}

	//cout << "\nst = " << st;
	//cout << "\nfn = " << fn;


	calculation_table(mtrx, st, fn + 1);
	float res = calculation_func(mtrx + st, n, x);

	return res;
}

int main()
{
	float x;
	cout << "Input X: ";
	cin >> x;
	int n_x;
	cout << "Input N(X): ";
	cin >> n_x;
	float y;
	cout << "Input Y: ";
	cin >> y;
	int n_y;
	cout << "Input N(Y): ";
	cin >> n_y;

	freopen("input.txt", "r", stdin);
	int cnt_x, cnt_y;
	cin >> cnt_x >> cnt_y;

	float **a = (float**)calloc(cnt_y + 1, sizeof(float*));
	for (int i = 0; i < cnt_y + 1; i++)
	{
		a[i] = (float*)calloc(cnt_x + 1, sizeof(float));
	}

	for (int i = 1; i < cnt_x + 1; i++)
	{
		cin >> a[0][i];
	}

	for (int i = 1; i < cnt_y + 1; i++)
	{
		cin >> a[i][0];
	}

	for (int i = 1; i < cnt_y + 1; i++)
	{
		for (int j = 1; j < cnt_x + 1; j++)
		{
			a[i][j] = f(a[0][j], a[i][0]);
		}
	}

	for (int i = 0; i < cnt_y + 1; i++)
	{
		for (int j = 0; j < cnt_x + 1; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << "\n";
	}

	float *res_x = (float*)calloc(cnt_y, sizeof(float));

	for (int i = 0; i < cnt_y; i++)
	{
		res_x[i] = create_table(x, cnt_x, n_x, a[0], a[i + 1]);
	}

	float *y1 = (float*)calloc(cnt_y, sizeof(float));

	for (int i = 0; i < cnt_y; i++)
	{
		y1[i] = a[i + 1][0];
	}

	float res = create_table(y, cnt_y, n_y, y1, res_x);

	cout << "\nResult = " << res << "\n";
	cout << "Result (real) = " << f(x, y) << "\n";
}