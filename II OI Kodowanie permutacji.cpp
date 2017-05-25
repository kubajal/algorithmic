#include <iostream>
#include <vector>

using namespace std;

const int MAX = 40000;

int B;
int wczytane[MAX];
vector<int> tab;
vector<int> wynik;

struct node
{
	int liczbaWezlowPod;
	int liczba;
};

node drzewo[200000];								// drzewo przedzialowe
int n;

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

bool input()
{
	cin >> B;
	for(int k = 1; k <= B; k++)
		cin >> wczytane[k];

	for(int k = 1; k <= B; k++){
		if(!(k > wczytane[k]))
		{
			cout << "NIE\n";
			return false;
		}
	}
	return true;
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
	if(input() == false)
		return 0;

	n = 1;
	while(n < B)														// obliczanie najblizszej, wiekszej potegi dwojki
		n = n << 1;

	for(int k = 1; k <= B; k++)
		wstawDoDrzewa(k);

	for(int k = B; k >= 1; k--, B--)
		wynik.push_back(znajdz(B - wczytane[k]));									// znajdowanie wyniku

	for(int k = wynik.size() - 1; k >= 0; k--)
		cout << wynik[k] << "\n";
    return 0;
}
