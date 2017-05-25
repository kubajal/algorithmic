#include <iostream>

using namespace std;

const int MAX = 400;

struct miasto
{
	int mieszkancy;
	int odlegloscDoPoprzedniego;
};

int l, x, y, minimum;

miasto linie[MAX][MAX];
int sumy[MAX];
int mieszkancyNaLinii[MAX], sumaMieszkancow;

void input()
{
	cin >> l;
	cin >> linie[0][0].mieszkancy;
	mieszkancyNaLinii[0] = linie[0][0].mieszkancy;
	for(int k = 1; k <= l; k++)
	{
		int pom;
		cin >> pom;
		for(int j = 1; j <= pom; j++)
		{
			cin >> linie[k][j].odlegloscDoPoprzedniego >> linie[k][j].mieszkancy;
		}
	}
}

void wyliczanieSum()
{
	for(int k = 1; k <= l; k++)
	{
		int j = 1;
		int odleglosc = 0;
		while(linie[k][j].odlegloscDoPoprzedniego != 0)
		{
			odleglosc += linie[k][j].odlegloscDoPoprzedniego;
			mieszkancyNaLinii[k] += linie[k][j].mieszkancy;
			sumaMieszkancow += linie[k][j].mieszkancy;
			minimum += odleglosc * linie[k][j].mieszkancy;					// obliczenie jaki jest calkowity koszt dojazdu od pierwszego miasta
			j++;
		}
	}
	sumaMieszkancow += linie[0][0].mieszkancy;
}

int wynik()												// aktualizujac wyliczone do tej pory minimum o wartosci odleglosci i liczby mieszkancow kolejnych miast znajduje ostateczne minimum
{
	int aktualny = 0, odleglosc = 0, ss;

	for(int k = 1; k <= l; k++)
	{
		aktualny = minimum;
		ss = sumaMieszkancow - mieszkancyNaLinii[k];
		odleglosc = 0;
		int j = 1;

		while(linie[k][j].odlegloscDoPoprzedniego > 0)
		{
			odleglosc = linie[k][j].odlegloscDoPoprzedniego;
\			aktualny -= odleglosc * mieszkancyNaLinii[k];
			aktualny += odleglosc * ss;

			if(aktualny < minimum)
			{
				minimum = aktualny;
				x = k;
				y = j;
			}

			mieszkancyNaLinii[k] -= linie[k][j].mieszkancy;
			ss += linie[k][j].mieszkancy;
			j++;
		}
	}

	return minimum;
}

int main()
{
	ios_base::sync_with_stdio(0);
	input();
	wyliczanieSum();

	cout << wynik() << "\n";
	cout << x << " " << y << "\n";
    return 0;
}
