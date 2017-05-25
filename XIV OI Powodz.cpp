#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 1002;
const int MAXVAL = 10001;
int n, m;
int pola[MAXN][MAXN];
bool pompa[MAXN][MAXN];
int wynik;

vector < pair <int, int> > kubelki[10001];

pair<int,int> ojciec[MAXN][MAXN];
int ile[MAXN][MAXN];

/*-------- Find & Union --------------*/

pair<int,int> znajdzReprezentanta(pair<int,int> a)
{
	if(ojciec[a.first][a.second] == a)
		return a;
	pair<int,int> o = znajdzReprezentanta(ojciec[a.first][a.second]);
	ojciec[a.first][a.second] = o;
	return o;
}

bool polacz(pair<int,int> a, pair<int,int> b)
{
	pair<int,int> rep1 = znajdzReprezentanta(a);
	pair<int,int> rep2 = znajdzReprezentanta(b);

	if(rep1 == rep2)
		return false;

	if(ile[rep1.first][rep1.second] >= ile[rep2.first][rep2.second])
	{
		ile[rep1.first][rep1.second] += ile[rep2.first][rep2.second];
		ojciec[rep2.first][rep2.second] = rep1;
		pompa[rep1.first][rep1.second] |= pompa[rep2.first][rep2.second];					// "trik", zeby ladnie poradzic sobie z kwestia pompy na dwoch laczonych polach
	}
	else
	{
		ile[rep2.first][rep2.second] += ile[rep1.first][rep1.second];
		ojciec[rep1.first][rep1.second] = rep2;
		pompa[rep2.first][rep2.second] |= pompa[rep1.first][rep1.second];					// "trik"
	}
	return true;
}

void inicjujFU()
{
	for(int k = 1; k <= n; k++)
	{
		for(int l = 1; l <= m; l++)
		{
			ile[k][l] = 1;
			ojciec[k][l] = make_pair(k, l);
		}
	}
}

/*^^^^^^^^^^^^^^^^^^^Find & Union^^^^^^^^^^^^^^^^^^*/

void input()
{
	for(int k = 0; k < MAXN; k++)
		for(int l = 0; l < MAXN; l++)
			pola[k][l] = MAXVAL;

	cin >> n >> m;
	for(int k = 1; k <= n; k++)
	{
		for(int l = 1; l <= m; l++)
		{
			cin >> pola[k][l];
			kubelki[abs(pola[k][l])].push_back(make_pair(k, l));						// sortowanie kubelkowe
		}
	}
	inicjujFU();
}

void licz()
{
	for(int k = 1; k <= 1000; k++)
	{
		for(vector<pair <int,int> >::iterator e = kubelki[k].begin(); e != kubelki[k].end(); ++e)		// iteracja po wszystkich polach od najmniejszego
		{
			int kierunki1[] = {0, 0, 1, -1};
			int kierunki2[] = {1, -1, 0, 0};
			for(int x = 0; x < 4; x++)
			{
				int a = e->first - kierunki1[x];
				int b = e->second - kierunki2[x];
				if(abs(pola[e->first][e->second]) >= abs(pola[a][b]))					// dane pole lacze z wszystkimi sasiadami, ktorzy sa wyzej od tego pola
					polacz(*e, make_pair(a, b));
			}
		}
		for(vector<pair <int,int> >::iterator e = kubelki[k].begin(); e != kubelki[k].end(); ++e)
		{
			pair<int,int> ojciec = znajdzReprezentanta(*e);
			if(pola[e->first][e->second] > 0 && pompa[ojciec.first][ojciec.second] == false)
			{
				pompa[ojciec.first][ojciec.second] = true;						// jezeli powstale pole nie ma ustawionej jeszcze pompy, to ja ustawiamy
				wynik++;
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	input();
	licz();
	cout << wynik << "\n";
    return 0;
}
