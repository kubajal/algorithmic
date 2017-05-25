#include <iostream>
#include <vector>
#include <fstream>
#define cin tmp

using namespace std;

ifstream tmp("dane.txt");
const int MAX = 1000;
int n, l;

int Q[MAX];
int head, tail;
void Q_push(int a)
{
	Q[tail++] = a;
}
bool Q_empty()
{
	return head == tail;
}
int Q_front()
{
	return Q[head++];
}
void Q_clear()
{
	head = tail = 0;
}

struct edge
{
    int v;
    edge () {}
    edge(int _v) : v(_v) {}
};

vector <edge> graph[MAX];																//graf
vector <edge>::iterator e;

void add_edge(int u, int v)
{
    graph[u].push_back(edge(v));
}

int tab[MAX];
short int kolor[MAX] = {-1};
bool visited[MAX];

void inicjalizacjaKolejki()
{
	for(int k = 0; k<MAX; k++)
	{
		vector <edge>::iterator e;
		for(e = graph[k].begin(); e != graph[k].end(); ++e)
		{
			tab[e->v]++;
		}
	}
	for(int k = 0; k<MAX; k++)
	{
		if(tab[k] == 1)
		{
			Q_push(k);
			tab[k]--;
			cout << "k " << k << endl;
			break;
		}
	}
}

int kl;

bool dfs(int s)
{
	visited[s] = true;
	vector<edge>::iterator e;

	kolor[s] = 0;

	for(e = graph[s].begin(); e != graph[s].end(); ++e)
	{
		if(kolor[s] == 0)
		{
			if(kolor[e->v] == -1)
			{
				kolor[e->v] = 1;
			}
			else
			{
				if(kolor[e->v] == kolor[s])
					return false;
			}
		}
		if(kolor[s] == 1)
		{
			if(kolor[e->v] == -1)
			{
				kolor[e->v] = 0;
			}
			else
			{
				if(kolor[e->v] == kolor[s])
					return false;
			}
		}
		dfs(e->v);
	}
	return true;
}
void input()
{
	int a, b;
	cin >> a >> b;
	add_edge(a,b);
	add_edge(b,a);
}

void clearAll()
{
	for(int k = 0; k<MAX; k++)
	{
		graph[k].clear();
		visited[k] = false;
		kolor[k] = -1;
		tab[k] = 0;
	}
}

int main()
{
	while (cin >> n && cin >> l && n!=0)
	{
		for(int k = 0; k<l; k++)
		{
			input();
		}
		inicjalizacjaKolejki();
		bool x = dfs(1);
		for(int k = 0; k<n; k++)
		{
			cout << kolor[k] << endl;
		}
		if(x == true)
		{
			cout << "NOT BICOLORABLE." << "\n";
		}
		if(x == false)
		{
			cout << "BICOLORABLE." << "\n";
		}
		clearAll();
	}
    return 0;
}
