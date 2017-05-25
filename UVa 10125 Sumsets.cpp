#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int n;

struct str
{
	int q, p;
	int x;
	str(int a, int b, int c)
	{
		q = a;
		p = b;
		x = c;
	}
};

bool operator<(const str a, const str b)
{
	if(a.x >= b.x)
		return false;
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	while(cin >> n && n != 0)
	{
		vector <int> v;
		for(int k = 0; k < n; k++)
		{
			int a;
			cin >> a;
			v.push_back(a);
		}

		vector <str> ab, cd;

		for(int k = 0; k < n; k++)
		{
			for(int l = 0; l < n; l++)
			{
				if(v[k] != v[l])
				{
					ab.push_back(str(v[k], v[l], v[k] + v[l]));
					cd.push_back(str(v[k], v[l], v[k] - v[l]));
				}
			}
		}

		sort(cd.begin(), cd.end());
		int wynik = -536870913;									// najmniejsza mozliwa wartosc
		for(int k = 0; k < ab.size(); k++)
		{
			vector<str>::iterator e = lower_bound(cd.begin(), cd.end(), str(0, 0, ab[k].x));
			if(e != cd.end() && e->q != ab[k].q && e->q != ab[k].p && e->p != ab[k].q && e->p != ab[k].p && wynik < e->q && e->x == ab[k].x)
			{
				wynik = e->q;
			}
		}
		if(wynik == -536870913)
			cout << "no solution\n";
		else
			cout << wynik << "\n";
	}
    return 0;
}
