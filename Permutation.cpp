#include <iostream>

using namespace std;

struct node
{
	int liczbaWezlowPod;
	int liczba;
};

node drzewo[200000];
int n, T, K, potega;

void inicjalizujDrzewo()
{
	int pom = K;
	n = 1;

	while(n < K)
		n = n << 1;

	for(int k = 1; k <= n+K-1; k++)
		drzewo[k].liczbaWezlowPod = 0;
}

void wstawDoDrzewa(int a)
{
	int pom = (a + n - 1);

	drzewo[pom].liczba = a;
	while(pom > 0)
	{
		drzewo[pom].liczbaWezlowPod++;
		pom = pom >> 1;
	}
}

inline int znajdz(int a)
{
	int k = 1, pom;

	while(drzewo[k].liczba == 0)
	{
		if(drzewo[2*k].liczbaWezlowPod < a)
		{
			a -= drzewo[2*k].liczbaWezlowPod;
			k = 2*k + 1;
		}
		else
		{
			k = 2*k;
		}
	}

	pom = k;
	while(pom > 0)
	{
		drzewo[pom].liczbaWezlowPod--;
		pom = pom >> 1;
	}
	return drzewo[k].liczba;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin >> T;
	for(int kkk = 0; kkk < T; kkk++)
	{
		int pom;

		cin >> K;
		inicjalizujDrzewo();							//znajduje najblizsza, wieksza potege dwojki i zeruj drzewo

		for(int k = 1; k <= K; k++)
			wstawDoDrzewa(k);

		for(int k = 0; k < K - 1; k++)
		{
			cin >> pom;
			cout << znajdz(pom+1) << " ";
		}
		cin >> pom;
		cout << znajdz(pom+1) << "\n";
	}
	return 0;
}
