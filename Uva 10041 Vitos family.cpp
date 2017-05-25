#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//ifstream tmp("dane.txt");

inline int wb(int lewy, int prawy)
{
	if(lewy>prawy)
		return lewy - prawy;
	return prawy - lewy;
}

int main()
{
	int N;
	cin >> N;
	for(int kkk = 0; kkk<N; kkk++)
	{
		int r;
		cin >> r;
		vector <int> a;
		for(int k = 0; k<r; k++)
		{
			int temp;
			cin >> temp;
			a.push_back(temp);
		}
		sort(a.begin(), a.end());
		int b = (a.size()-1)/2;
		int bb = a[b];
		int suma = 0;
		for(int k = 0; k<a.size(); k++)
		{
			suma += wb(bb,a[k]);
		}
		cout << suma << endl;
	}
    return 0;
}
