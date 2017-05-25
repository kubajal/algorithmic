#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX = 1000000;
int T;
string s;

struct str
{
	char c;
	int l, p;
};

str drzewo[MAX];
vector<int> odpowiedz;

int stos[MAX];
int tail;
void stosPush(int a) { stos[++tail] = a; }
int stosPop() { return stos[tail--]; }

int kolejka[MAX];
int head;
void kolejkaPush(int a) {kolejka[tail++] = a; }
int kolejkaFront() { return kolejka[++head]; }
bool kolejkaEmpty() { return head == tail; }

void czysc()
{
	odpowiedz.clear();
	head = tail = 0;
}

void init()
{
	czysc();
	cin >> s;
	for(int k = 0; k < s.size(); k++)
	{
		drzewo[k].c = s[k];
		if(islower(s[k]))
		{
			drzewo[k].l = drzewo[k].p = -1;
		}
		else
		{
			drzewo[k].l = stosPop();
			drzewo[k].p = stosPop();
		}
		stosPush(k);
	}
}

void bfs()
{
	int cur;
	kolejkaPush(s.size()-1);
	while(!kolejkaEmpty())
	{
		cur = kolejkaFront();
		odpowiedz.push_back(cur);
		if(drzewo[cur].l != -1)
		{
			kolejkaPush(drzewo[cur].p);
			kolejkaPush(drzewo[cur].l);
		}
	}
}

void wypiszOdp()
{
	for(int k = odpowiedz.size() - 1; k >= 0; k--)
		cout << drzewo[odpowiedz[k]].c;
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin >> T;
	for(int z = 0; z < T; z++)
	{
		init();
		bfs();
		wypiszOdp();
	}
    return 0;
}
