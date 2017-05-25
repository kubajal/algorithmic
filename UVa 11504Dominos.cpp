#include <iostream>
#include <vector>

using namespace std;

const int MAX = 100001;

vector<int> graph[MAX], transGraph[MAX];
vector<int> S;
int tab[MAX];
int t, n, m, cur;
bool visited[MAX], visited_components[MAX];
int components, tab_components[MAX];

void init()
{
	cin >> n >> m;
	S.clear();
	components = 0;
	for(int k = 1; k <= n; k++)
	{
		graph[k].clear();
		transGraph[k].clear();
		tab_components[k] = 0;
		visited[k] = false;
		tab[k] = 0;
	}
	for(int k = 0; k < m; k++)
	{
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		transGraph[b].push_back(a);
	}
}

void dfs1(int v)
{
	visited[v] = true;
	for(vector<int>::iterator e = graph[v].begin(); e != graph[v].end(); e++)
		if(!visited[*e])
		{
			dfs1(*e);
		}
	S.push_back(v);
}

void dfs2(int v)
{
	tab_components[v] = components;
	visited[v] = true;
	for(vector<int>::iterator f = transGraph[v].begin(); f != transGraph[v].end(); f++)
	{
		if(visited[*f] == false)
			dfs2(*f);
	}
}

void dfs3(int v)
{
	visited[v] = true;
	if(cur != tab_components[v] && visited_components[v] == false && components >= 2)
	{
		visited_components[v] = true;
		components--;
	}
	for(vector<int>::iterator e = graph[v].begin(); e != graph[v].end(); e++)
	{
		if(visited[*e] == false)
		{
			dfs3(*e);
		}
	}
}

void calc_components()
{
	for(int k = 1; k <= n; k++)\
	{
		if(!visited[k])
			dfs1(k);
	}
	for(int k = 1; k <= n; k++)	visited[k] = false;
	for(int k = n - 1; k >= 0; k--)
	{
		if(tab_components[S[k]] == 0)
		{
			components++;
			dfs2(S[k]);
		}
	}
}

int ans()
{
	int w = 0;
	for(int k = 1; k <= n; k++)
		tab[k] = 0;
	for(int k = 1; k <= n; k++)
	{
		for(vector<int>::iterator e = graph[k].begin(); e != graph[k].end(); e++)
		{
			if(tab_components[k] != tab_components[*e])
				tab[tab_components[*e]]++;
		}
	}

	for(int k = 1; k <= components; k++)
	{
		if(!tab[k])
			w++;
	}

	return w;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin >> t;
	while(t--)
	{
		init();
		calc_components();
		cout << ans() << "\n";
	}
	return 0;
}
