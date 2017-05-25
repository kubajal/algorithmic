#include <iostream>

using namespace std;

const int INF = 1000000001;

int n, k, m;
int odleglosci[101][101];

void init()
{
	cin >> n >> k >> m;

	for(int i = 1; i <= n; i++)	{
		for(int l = 1; l <= n; l++)
			odleglosci[i][l] = INF;
		odleglosci[i][i] = 0;
	}

	for(int i = 1; i <= k; i++){
		int a, b, w;
		cin >> a >> b >> w;
		odleglosci[a][b] = odleglosci[b][a] = min(odleglosci[a][b], w);
	}
}

void FW()
{
	for(int i = 1; i <= n; i++)
		for(int l = 1; l <= n; l++)
			for(int j = 1; j <= n; j++)
				odleglosci[l][j] = min(odleglosci[l][i] + odleglosci[i][j], odleglosci[l][j]);

}

void porownaj()
{
	int a, b, w;
	for(int l = 1; l <= m; l++){
		cin >> a >> b >> w;
		if(odleglosci[1][a]+w+odleglosci[b][n] < odleglosci[1][n] || odleglosci[1][b]+w+odleglosci[a][n] < odleglosci[1][n]){		// jezeli ta propozycja jest korzystniejsza od wczesniej wyliczonego kosztu to aktualizujemy
			cout << 1 << endl;
			for(int i = 1; i <= n; i++)
			 for(int j = 1; j <= n; j++){
				if(odleglosci[i][j] > odleglosci[i][a]+w+odleglosci[b][j]) odleglosci[i][j] = odleglosci[i][a]+w+odleglosci[b][j];
				if(odleglosci[i][j] > odleglosci[i][b]+w+odleglosci[a][j]) odleglosci[i][j] = odleglosci[i][b]+w+odleglosci[a][j];
			}
		}
		else cout << 0 << endl;
	}
}

int main()
{
	init();
	FW();
	porownaj();
	return 0;
}