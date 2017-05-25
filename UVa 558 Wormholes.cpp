#include <iostream>					// zadanie zrobione Dijkstra a nie FordemBellmanem
#include <vector>
#include <set>

using namespace std;

const int MAX = 1000000;
const int INF = 2000000000;

int cost[MAX+1];
int c, n, m;

struct edge
{
    int v;
    int cost;
    edge () {}
    edge(int _v, int _cost) : v(_v), cost(_cost) {}
};

vector <edge> graph[MAX+1];																		//graf

void add_edge(int u, int v, int cost)
{
    graph[u].push_back(edge(v, cost));
}

void input()
{
	cin >> n >> m;

	for(int k = 1; k<=m; k++)
	{
		int x, y, t;
		cin >> x >> y >> t;
		add_edge(x+1, y+1, t);
	}
}

struct cmp																				// komparator dla kopca
{
    bool operator() (const int &a, const int &b)
    {
    	if(cost[a]<cost[b])
			return true;
		if(cost[a]>cost[b])
			return false;
		return a>b;
    }
};

bool dijkstra(int s)
{
	set <int, cmp> kopiec;
	int cur;
	vector<edge>::iterator e;
	int edges = 0;

	cost[s] = 0;

	kopiec.insert(s);															// inicjalziacja kopca

	while(!kopiec.empty())
	{
		cur = *(kopiec.begin());
		kopiec.erase(kopiec.begin());
		for(e = graph[cur].begin(); e != graph[cur].end(); ++e)
		{
			edges++;
			if(e->cost + cost[cur] < cost[e->v])
			{
				if(kopiec.find(e->v) != kopiec.end())
					kopiec.erase(kopiec.find(e->v));

				kopiec.insert(e->v);
				cost[e->v] = e->cost + cost[cur];
				if(edges > m+5)
					return true;
			}
		}
	}
	return false;
}

void clearAll()
{
	for(int k = 1; k <= MAX; k++)
	{
		cost[k] = INF;
		graph[k].clear();
	}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin >> c;
	for(int kkk = 1; kkk<=c; kkk++)
	{
		clearAll();
		input();
		bool cycle;
		cycle = dijkstra(1);
		if(cycle == true)
			cout << "possible\n";
		else
			cout << "not possible\n";
	}
    return 0;
}
