// zrobione Floydem Warshallem
#include <iostream>

using namespace std;

const int MAX = 101, MAXVAL = 1000000001;
int n, m;
int cost[MAX], prev[MAX];
int tab[MAX][MAX];

void init()
{
	for(int k = 1; k <= n; k++)
		for(int l = 1; l <= n; l++)
			tab[k][l] = MAXVAL;

	cin >> m;
	for(int k = 0; k < m; k++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		tab[a][b] = tab[b][a] = c;
	}
}

bool fordbellman()
{
	for(int k = 1; k <= n; k++)
		cost[k] = MAXVAL;
	cost[1] = 0;

	for(int i = 1; i < n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			for(int e = 1; e <= n; e++)
			{
				if(cost[e] > cost[j] + tab[j][e] && tab[j][e] != MAXVAL)
				{
					cost[e] = cost[j] + tab[j][e];
					prev[e] = j;
				}
			}
		}
	}
	for(int k = 1; k <= n; k++)
	{
		for(int e = 1; e <= n; e++)
		{
			if(cost[e] > cost[k] + tab[k][e] && tab[k][e] != MAXVAL)
				return false;
		}
	}
	return true;
}

void korekta()									// zamiana krawedzi na ujemne
{

	int cur = n;
	while(cur != 1)
	{
		int p = prev[cur];
		tab[p][cur] = MAXVAL;
		tab[cur][p] = (-1) * tab[cur][p];
		cur = p;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	while(cin >> n && n != 0)
	{
		init();
		fordbellman();
		int q = cost[n];
		korekta();
		fordbellman();
		int p = cost[n];
		if(p + q > MAXVAL)
			cout << "Back to jail\n";
		else
		cout << p + q << "\n";
	}
	return 0;
}
