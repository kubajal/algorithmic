#include <iostream>
#include <string>

using namespace std;

string aktualny;
int n;

inline int konwert1(char a)					// konwersja litery na liczbe ; A->1, C->2, G->3, T->4
{
	if(a == 'A')
		return 1;
	if(a == 'C')
		return 2;
	if(a == 'G')
		return 3;
	if(a == 'T')
		return 4;
}

inline char konwert2(int a)					// konwersja z liczby na litere z alfabetu
{
	if(a == 1)
		return 'A';
	if(a == 2)
		return 'C';
	if(a == 3)
		return 'G';
	if(a == 4)
		return 'T';
}

struct node
{
	int cnt;
	node *child[5];
};

void zeruj(node *a)
{
	for(int k = 1; k<5; k++)
		a->child[k] = NULL;
	a->cnt = 0;
}

node *head;					// korzen TRIE

void init()
{
	head = new node;
	zeruj(head);
}

void trie_insert(string a)
{
	node *current = head;

	for(int k = 0; k < a.size(); k++)
	{
		int pom = konwert1(a[k]);

		if(current->child[pom] == NULL)
		{
			current->child[pom] = new node;
			zeruj(current->child[pom]);
		}
		//cout << "Z" << endl;
		current->child[pom]->cnt++;
		current = current->child[pom];
	}
}

void tworzenieSufiksow(string a)
{
	while(a.size() != 0)
	{
		trie_insert(a);
		a.erase(a.begin());
	}
}

node *m;
int aktualnaWysokosc = -1, maksymalnaWysokosc = -1, maksymalnaIloscPowtorzen;

void przegladaj(node *a)								// DFS w glab TRIE w celu ustalenia ktory wezel jest najglebiej i najwiecej razy sie powtarza, ale dla wygody bez znajdywania wyniku, bo by to pamiec zarlo
{
	aktualnaWysokosc++;
	for(int k = 1; k<5; k++)
	{
		if(a->child[k] != NULL)
		{
			if(maksymalnaWysokosc < aktualnaWysokosc && a->cnt >= 2)
			{
				m = a;
				maksymalnaIloscPowtorzen = a->cnt;
				maksymalnaWysokosc = aktualnaWysokosc;
			}
			przegladaj(a->child[k]);
			aktualnaWysokosc--;
		}
	}
}

string pom, wynik;
bool sr = false;

void znajdzWynik(node *a)								// DFS w celu odnalezenia najdluzszego slowa
{
	if(a == m)
	{
		sr = true;
		pom = wynik;
	}

	if(sr == false)
	{
		for(int k = 1; k<5; k++)
		{
			if(a->child[k] != NULL)
			{
				wynik += konwert2(k);

				znajdzWynik(a->child[k]);
				wynik.erase(wynik.size()-1);

			}
		}
	}
}

void czyscTRIE(node *a)
{
	for(int k = 1; k<5; k++)
	{
		if(a->child[k] != NULL)
		{
			czyscTRIE(a->child[k]);
		}
	}
	delete a;
}

void czyscWszystko()
{
	czyscTRIE(head);
	maksymalnaIloscPowtorzen = 0;
	wynik.clear();
	maksymalnaWysokosc = -1;
	aktualnaWysokosc = -1;
	sr = false;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin >> n;
	for(int kkk = 0; kkk < n; kkk++)
	{
		init();
		cin >> aktualny;

		tworzenieSufiksow(aktualny);

		przegladaj(head);

		znajdzWynik(head);

		if(pom.empty() == true || maksymalnaIloscPowtorzen == 0)
			cout << "No repetitions found!" << "\n";
		else
			cout << pom << " " << maksymalnaIloscPowtorzen << "\n";
		czyscWszystko();
	}
	return 0;
}
