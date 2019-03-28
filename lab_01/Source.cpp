#include<iostream>
#include<cmath>

using namespace std;

float f(float x)
{
	float y = cos(x) - x;
	//float y = x * x;
	return y;
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
	for (int z = 0; z < n - 1; z++)
	{
		for (int i = 0; i < k - 1; i++)
		{
			res = div_diff(mtrx[i][0], mtrx[i+(z + 1)][0], mtrx[i][z + 1], mtrx[i + 1][z + 1]);
			mtrx[i][z + 2] = res;
		}
		k--;
	}
	
	cout << "\n";
	for (int i = st; i < n; i++)
	{
		for (int j = 0; j <= n-st; j++)
		{
			cout << mtrx[i][j] << " ";
		}
		cout << "\n";
	}

}

void calculation_func(float **mtrx, int n, float x)
{
	float res = 0, mid_res = 1;
	int y = mtrx[0][1];
	int i = 2;
	for (int i = 0; i < n + 1; i++)
	{
		res += mid_res * mtrx[i + 1][0];
		mid_res *= (x - mtrx[0][i]);
	}
	cout << "Result: ";
	cout << y;
	cout << "\n";
	cout << "Result (real): ";
	cout << f(x);
	cout << "\n";
}

void calculation_func2(float **mtrx, int n, float x)
{
	float res = 0, mid_res = 1;
	float y = mtrx[0][1];
	res = y;
	for (int i = 0; i < n - 1; i++)
	{
		mid_res *= (x - mtrx[i][0]);
		res += mid_res * mtrx[0][i + 2];
	}
	cout << "\nResult: ";
	cout << res;
	cout << "\n";
	cout << "Result (real): ";
	cout << f(x);
	cout << "\n";
}

int main()
{
	float x;
	cout << "Input X: ";
	cin >> x;
	int n;
	cout << "Input N: ";
	cin >> n;

	freopen("input.txt", "r", stdin);
	int cnt;
	cin >> cnt;

	float **mtrx = (float**)calloc(cnt + 1, sizeof(float*));
	for (int i = 0; i < cnt; i++)
	{
		mtrx[i] = (float*)calloc(cnt + 1, sizeof(float));
	}

	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cin >> mtrx[i][j];
		}
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
		/*int i = mid - upper + 1, j = 0;
		if (i >= 0 && mid + lower < cnt)
		{
			st = i; fn = mid + lower;
		}
		else if ( i < 0)
		{
			st = 0; fn = n;
		}
		else
		{
			fn = cnt - 1; st = fn - n + 1;
		}*/

		int space_needed;
		if (n % 2 == 0)
			space_needed = n / 2;
		else
			space_needed = (n + 1) / 2;
		if (mid + space_needed + 1 > cnt)
		{
			fn = cnt - 1;
			st = cnt - n;
		}
		else if (mid < space_needed)
		{
			st = 0;
			fn = n;
		}
		else
		{
			st = mid - space_needed + 1;
			fn = st + n;
		}

	} 

	calculation_table(mtrx, st, fn + 1);
	calculation_func2(mtrx + st, n, x);

	/*cout << "\n";
	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < cnt + 1; j++)
		{
			cout << mtrx[i][j] << " ";
		}
		cout << "\n";
	}*/
	
	return 0;
}