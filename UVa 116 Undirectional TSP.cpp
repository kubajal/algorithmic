#include <iostream>

using namespace std;

const int MAXN = 102;
const long long MAXVAL = 1000000000000000000;

long long tab[MAXN][MAXN];
long long cost[MAXN][MAXN];
long long n, m;

pair<long long,long long> ojciec[MAXN][MAXN];

void input()
{
	for(int k = 0; k < MAXN; k++)
	{
		for(int l = 1; l < MAXN; l++)
		{
			cost[k][l] = MAXVAL + 1;
			tab[k][l] = MAXVAL + 1;
			ojciec[k][l].first = 0;
			ojciec[k][l].second = 0;
		}
	}
	for(int k = 1; k <= n; k++)
		for(int l = 1; l <= m; l++)
			cin >> tab[k][l];
}

void calc()
{
	for(int k = 1; k <= n; k++)
		cost[k][m] = tab[k][m];

	for(int k = m; k >= 1; k--)							// dynamicznie wylicza najkrotsza droge
											//---------------------------------------
	{										// aby dostac w latwy sposob najmniejsza leksykograficznie droge
		for(int l = 1; l<= n; l++)						// obliczam nie od lewej do prawej, a od prawej do lewej
		{									// minimalny  koszt wyjdzie ten sam, a zlikwiduje to problem porownywania drog
			int kierunki[] = {1, 0, -1};

			for(int i = 0; i < 3; i++)
			{								
				int a = l - kierunki[i];
				if(a == 0)
					a = n;
				if(a == n+1)
					a = 1;
				if(cost[a][k-1] > cost[l][k] + tab[a][k-1])
				{
					cost[a][k-1] = cost[l][k] + tab[a][k-1];
					ojciec[a][k-1] = make_pair(l, k);
				}

			}
		}
	}
}

void znajdzDroge()
{
	long long minimum = MAXVAL + 1;
	pair<int,int> p;

	for(int k = 1; k <= n; k++)
		minimum = min(minimum, cost[k][1]);

	for(int k = 1; k <= n; k++)							// jak natknie sie na pierwsze minimum, to od razu wypisuje droge z nim
	{										// zwiazana. to dziala bo to ona *musi* byc najwczesniejsza
		if(cost[k][1] == minimum)
		{
			p = ojciec[k][1];
			cout << k;
			while(p.first != 0)
			{
				cout << " " << p.first;
				p = ojciec[p.first][p.second];
			}
			break;
		}
	}
	cout << "\n" << minimum;
}

int main()
{
	ios_base::sync_with_stdio(false);
	bool pom = false;
	while(cin >> n >> m && n != 0 && m != 0)
	{
		if(pom == true)								// syf, zeby nie bylo PE w sprawdzaczce
			cout << "\n";							// -||-
		if(pom == false)							// -||-
			pom = true;							// -||-
		input();
		calc();
		znajdzDroge();
	}
	cout << "\n";
	return 0;
}
