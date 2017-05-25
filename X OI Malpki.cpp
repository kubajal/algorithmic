#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 200001;
const int ZIEMIA = -2;
const int NIGDY = -1;

struct stos
{
	int malpka;
	int lapka;
	stos(int a, int b)
	{
		malpka = a;
		lapka = b;
	}
};

vector <stos> S;						// potrzebne do odtworzenia od tylu kolejnosci odczepiania lapek

int n, m;
int lewa[MAXN];
int prawa[MAXN];
bool lewaPuszczona[MAXN];
bool prawaPuszczona[MAXN];

void wczytaj()
{
	int a, b;

	cin >> n >> m;
	for(int k = 1; k <= n; k++)	{
		cin >> a >> b;
		if(a != -1)
			lewa[k] = a;
		if(b != -1)
			prawa[k] = b;
	}
	for(int k = 1; k <= m; k++){
		cin >> a >> b;

		S.push_back(stos(a, b));

		if(b == 1)
			lewaPuszczona[a] = true;
		if(b == 2)
			prawaPuszczona[a] = true;
	}
}

int ojciec[MAXN];
int ile[MAXN];
int czas[MAXN];

int znajdzReprezentanta(int a)
{
	if(a != ojciec[a]){
		int o = znajdzReprezentanta(ojciec[a]);
		if(czas[a] == ZIEMIA)
			czas[a] = czas[ojciec[a]];
		ojciec[a] = o;
	}
	return ojciec[a];
}

void polacz(int a, int b)
{
	if(ile[a] >= ile[b]){
		ile[a] += ile[b];
		ojciec[b] = a;
	}
	else{
		ile[b] += ile[a];
		ojciec[a] = b;
	}
}

void preprocessing()
{
	for(int k = 1; k <= n; k++)
	{
		ojciec[k] = k;
		ile[k] = 1;
		czas[k] = ZIEMIA;
	}
	for(int k = 1; k <= n; k++)
	{
		if(prawa[k] != 0 && prawaPuszczona[k] == false)
			polacz(znajdzReprezentanta(k), znajdzReprezentanta(prawa[k]));

		if(lewa[k] != 0 && lewaPuszczona[k] == false)
			polacz(znajdzReprezentanta(k), znajdzReprezentanta(lewa[k]));
	}
	czas[znajdzReprezentanta(1)] = NIGDY;
}

void przetworz()											// aktualizowanie struktury find & union
{
	for(int k = m - 1; k >= 0; k--)
	{
		int pom1 = znajdzReprezentanta(S[k].malpka), pom2, rdzen = znajdzReprezentanta(1);

		if(S[k].lapka == 1)
			pom2 = znajdzReprezentanta(lewa[S[k].malpka]);
		if(S[k].lapka == 2)
			pom2 = znajdzReprezentanta(prawa[S[k].malpka]);

		if(pom1 == rdzen && pom2 != rdzen)
			czas[pom2] = k;
		if(pom1 != rdzen && pom2 == rdzen)
			czas[pom1] = k;
		polacz(pom1, pom2);
	}
}

void wypisz()
{
	for(int k = 1; k <= n; k++)
	{
		znajdzReprezentanta(k);
		cout << czas[k] << "\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	wczytaj();
	preprocessing();
	przetworz();
	wypisz();
	return 0;
}
