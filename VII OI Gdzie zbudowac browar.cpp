#include <iostream>
using namespace std;

const int MAXN = 10001;
const int MAXVAL = 1000000001;

long long z[MAXN], d[MAXN], koszt[MAXN], n, minimum = 0, miastoWLewo = -1, miastoWPrawo, zaoptrzenieWLewo, zaopatrzenieWPrawo, odlWLewo, odlWPrawo;

void input()
{
	cin >> n;
	for(int k = 0; k < n; k++)
		cin >> z[k] >> d[k];
}

void init()
{
	for(int k = 1; k < n; k++)
		koszt[k] = MAXVAL;

	long long aktualnaOdl = 0;
	for(int k = 1; k < n; k++)
	{
		aktualnaOdl += d[k-1];
		koszt[k] = min(koszt[k], aktualnaOdl * z[k]);
	}
	aktualnaOdl = 0;
	for(int k = n - 1; k >= 1; k--)
	{
		aktualnaOdl += d[k];
		if(koszt[k] > aktualnaOdl * z[k])
		{
			if(miastoWLewo = -1)
				miastoWLewo = k;
			koszt[k] = aktualnaOdl * z[k];
		}
	}
	for(int k = 0 ; k < n; k ++)										// obliczam minimum dla pierwszego miasta
		minimum += koszt[k];
	miastoWPrawo = miastoWLewo - 1;
	if(miastoWLewo == -1)
	{
		miastoWLewo = n;
		miastoWPrawo = n - 1;
	}
	for(int k = 1; k <= miastoWPrawo; k++)
	{
		zaopatrzenieWPrawo += z[k];
		odlWPrawo += d[k-1];
	}
	for(int k = n - 1; k >= miastoWLewo; k--)
	{
		zaoptrzenieWLewo += z[k];
		odlWLewo += d[k];
	}
}

void przetworz()
{
	int x = 0;
	long long temp = minimum;
	while(x < n)												// poprawiam dotychczasowo wyliczone minimum
	{
		zaoptrzenieWLewo += z[x];
		temp += zaoptrzenieWLewo * d[x] - zaopatrzenieWPrawo * d[x];
		odlWPrawo -= d[x];
		odlWLewo += d[x];
		zaopatrzenieWPrawo -= z[(x+1)%n];
		while(odlWLewo > odlWPrawo + d[miastoWPrawo])
		{
			odlWPrawo += d[miastoWPrawo];
			temp += odlWPrawo * z[miastoWLewo] - z[miastoWLewo] * odlWLewo;
			zaopatrzenieWPrawo += z[miastoWLewo];
			zaoptrzenieWLewo -= z[miastoWLewo];
			odlWLewo -= d[miastoWLewo];
			miastoWLewo++;
			miastoWPrawo++;
			if(miastoWLewo >= n)
				miastoWLewo -= n;
			if(miastoWPrawo >= n)
				miastoWPrawo -= n;
			if(minimum > temp)
				minimum = temp;
		}

		if(minimum > temp)
			minimum = temp;
		x++;
	}
}

int main()
{
	input();
	init();
	przetworz();
	cout << minimum << endl;
	return 0;
}
