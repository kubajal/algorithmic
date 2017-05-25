#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 182, MAXVAL = 1000000000;

struct klocek
{
	int x, y, z;
	klocek(int a, int b, int c)
	{
		x = a;
		y = b;
		z = c;
	}
};

vector<klocek> v;
int tab[MAX][MAX];
int n;

void init()
{
	v.clear();
	for(int k = 0 ; k < MAX; k++)
		for(int l = 0 ; l < MAX; l++)
			tab[k][l] = MAXVAL;
	for(int k = 0 ; k < n; k++)
	{
		int x, y, z;
		cin >> x >> y >> z;
		v.push_back(klocek(x, y, z));
		v.push_back(klocek(x, z, y));
		v.push_back(klocek(y, x, z));
		v.push_back(klocek(y, z, x));
		v.push_back(klocek(z, x, y));
		v.push_back(klocek(z, y, x));
	}
	for(int k = 0; k < v.size(); k++)
	{
		tab[v.size()][k] = -v[k].z;
		for(int l = 0; l < v.size(); l++)
		{
			if(v[l].x < v[k].x && v[l].y < v[k].y || v[l].x < v[k].y && v[l].y < v[k].x)
			{
				tab[k][l] = -v[l].z;
			}
		}
	}
}

int FW()										//Floyd Warshall
{
	int cost[MAX][MAX];
	for(int k = 0; k <= v.size(); k++)
	{
		for(int l = 0; l <= v.size(); l++)
		{
			cost[k][l] = tab[k][l];
		}
		cost[k][k] = 0;
	}
	for(int k = 0; k < v.size(); k++)
	{
		for(int l = 0; l <= v.size(); l++)
		{
			for(int j = 0; j <= v.size(); j++)
			{
				if(cost[l][j] > cost[l][k] + cost[k][j])
					cost[l][j] = cost[l][k] + cost[k][j];
			}
		}
	}
	int minimum = MAXVAL;
	for(int k = 0 ; k <= v.size(); k++)
	{
		for(int l = 0 ; l < v.size(); l++)
		{
			if(minimum > cost[k][l])
				minimum = cost[k][l];
		}
	}
	return (-minimum);
}

int main()
{
	ios_base::sync_with_stdio(false);
	int k = 1;
	while(cin >> n && n != 0)
	{
		init();
		cout << "Case " << k++ << ": maximum height = " << FW() << "\n";
	}
    return 0;
}
