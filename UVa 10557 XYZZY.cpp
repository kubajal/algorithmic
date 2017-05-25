#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAX = 105;
const int INF = 1000000000;

int n;
int enter[MAX];
bool visited[MAX];
int reach[MAX];
int cost[MAX];
int numberOfEdges;

int Q[MAX];
int head, tail;
void Q_push(int a) { Q[tail++] = a; }
int Q_front() { return Q[head++]; }
bool Q_empty() { return head == tail; }
void Q_clear() { head = tail = 0; }

struct edge
{
    int v;
    bool dir;
    edge () {}
    edge(int _v, bool _dir) : v(_v), dir(_dir) {}
};

vector <edge> graph[MAX];																//graf

void add_edge(int u, int v, bool dir)
{
    graph[u].push_back(edge(v, dir));
}

void input()
{
	for(int k = 1; k<=n; k++)
	{
		int temp;
		cin >> enter[k] >> temp;
		enter[k] = -enter[k];
		numberOfEdges += temp;
		for(int j = 1; j<=temp; j++)
		{
			int a;
			cin >> a;
			add_edge(k, a, true);
			add_edge(a, k, false);
		}
	}
};

void bfs(int s, bool dir)
{
	vector<edge>::iterator e;
	int cur;

	Q_push(s);
	visited[s] = true;
	reach[s]++;

	while(!Q_empty())
	{
		cur = Q_front();

		for(e = graph[cur].begin(); e != graph[cur].end(); ++e)
		{
			if(!visited[e->v] && e->dir == dir)
			{
				Q_push(e->v);
				visited[e->v] = true;
				reach[e->v]++;
			}
		}
	}
	for(int k = 1; k<=n; k++)
		visited[k] = false;
	Q_clear();
}

struct cmp																	// komparator dla kopca
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

	for(int k = 1; k<=n; k++)
	{
		cost[k] = INF;
	}
	cost[s] = 0;

	kopiec.insert(s);															// inicjalziacja kopca

	while(!kopiec.empty())
	{
		cur = *(kopiec.begin());
		kopiec.erase(kopiec.begin());
		for(e = graph[cur].begin(); e != graph[cur].end(); ++e)
		{
			if(reach[e->v] == 2 && enter[e->v] + cost[cur] < 100 && enter[e->v] + cost[cur] < cost[e->v] && e->dir == true)
			{
				edges++;
				if(kopiec.find(e->v) != kopiec.end())									//
					kopiec.erase(kopiec.find(e->v));

				kopiec.insert(e->v);
				cost[e->v] = enter[e->v] + cost[cur];
				if(edges > numberOfEdges+5)
					return true;
			}
		}
	}
	return false;
}

void clearAll()
{
	for(int k = 1; k<=n; k++)
	{
		reach[k] = 0;
		cost[k] = INF;
		visited[k] = false;
		graph[k].clear();
		enter[k] = 0;
	}
	numberOfEdges = 0;
	Q_clear();
}

int main()
{
	ios_base::sync_with_stdio(0);
	while(cin >> n && n != -1)
	{
		clearAll();
		input();
		bfs(1, true);												// puszczenie BFS'a z wezla startowego i znalezenie osiaglnych wierzcholkwo
		bfs(n, false);												// puszczenie BFS'a z wezla koncowego z odwroconymi krawedziami i znaleznie osiaglnych wierzcholkow
		bool cycle = dijkstra(1);
		if(cycle == true || cost[n] < 100)
			cout << "winnable" << endl;
		else
			cout << "hopeless" << endl;
	}
	return 0;
}
