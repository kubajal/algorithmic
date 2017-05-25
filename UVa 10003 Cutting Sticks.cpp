#include <iostream>

using namespace std;

int l, n;
int c[53][53];
int cost[53][53];
int cuts[53];
int kawalki[53];


void input()
{
	cin >> n;
	for(int k = 1; k <= n; k++)
	{
		c[k][1] = 0;
		cin >> cuts[k];
	}
	cuts[0] = 0;
	cuts[n+1] = l;
	kawalki[1] = cuts[1];
	for(int k = 2; k <= n+1; k++)
		kawalki[k] = cuts[k] - cuts[k-1];
	for(int k = 1; k <= n + 1; k++)
	{
		for(int l = 1; l <= n + 1; l++)
		{
			c[k][l] = 10000000;
		}
		c[k][1] = 0;
	}
}


int main()
{
	while(cin >> l && l != 0)
	{
		input();
		for(int i = 2; i <= n + 2; i++)
		{
			for(int j = 1; j <= n - i + 2; j++)
			{
				int suma = 0;
				for(int k = j; k <= j+i-1; k++)
					suma += kawalki[k];
				for(int k = 1; k < i; k++)
				{
					int pom = suma + c[j][k] + c[k+j][i-k];
					if(c[j][i] > pom)
					{
						c[j][i] = pom;
					}
				}
			}
		}
		cout << "The minimum cutting is " << c[1][n+1] << ".\n";
	}
	return 0;
}
