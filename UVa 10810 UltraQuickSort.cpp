#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 500000;

int n;
long long wynik;
int tab[MAX];

void m(int L, int P)
{
	if(P - L > 1)
	{
		int polowa = (L + P)/2;
		m(L, polowa);
		m(polowa, P);

		vector<int> x (&tab[L], &tab[polowa]), y(&tab[polowa], &tab[P]);

		int it1 = 0, it2 = 0;
		while(it1 < x.size() && it2 < y.size())
		{
			if(x[it1] <= y[it2])
				tab[L++] = x[it1++];
			else
			{
				wynik += x.size() - it1;
				tab[L++] = y[it2++];
			}
		}
		if(it1 == x.size())
			while(it2 < y.size())
				tab[L++] = y[it2++];

		else if(it2 == y.size())
		{
			while(it1 < x.size())
				tab[L++] = x[it1++];
		}
	}
}

int main()
{
        ios_base::sync_with_stdio(false);
        while(cin >> n && n != 0)
        {
			wynik = 0;
			for(int k = 0 ; k < n; k++)
				cin >> tab[k];

			m(0, n);                  // liczenie wyniku mergesortem
			cout << wynik << "\n";
        }
    return 0;
}
