#include <iostream>

using namespace std;


const int MAXN = 50001;
const int MAXVAL = 1000000001;

struct miasto
{
	int odlegloscOdNastepnego;
	int odleglosc;
};

int n;
miasto wyspa[MAXN];
int obwod = 0;

void wczytaj()
{
	cin >> n;
	for(int k = 1; k <= n; k++)
	{
		cin >> wyspa[k].odlegloscOdNastepnego;
		obwod+=wyspa[k].odlegloscOdNastepnego;
	}
}

int wyliczNajwiekszaOdleglosc()
{

	int maximum = 0, aktualnaOdl = 0;
	for(int k = 2; k <= n; k++){
		wyspa[k].odleglosc = MAXVAL;
	}

	for(int k = 2; k <= n; k++){
		aktualnaOdl += wyspa[k].odlegloscOdNastepnego;
		wyspa[k].odleglosc = min(wyspa[k].odleglosc, aktualnaOdl);
	}

	aktualnaOdl = 0;

	for(int k = n; k >= 1; k--)
	{
		aktualnaOdl += wyspa[k].odlegloscOdNastepnego;
		wyspa[k].odleglosc = min(wyspa[k].odleglosc, aktualnaOdl);
	}

	obwod /= 2;
	int x = 1, y = 1;
	int temp = 0;

	while(x <= n)										// aktualizuje dotychczasowa odleglosc przesuwajac wspolrzedna jednego koncowego miasta lub drugiego
	{
		if(temp <= obwod)
		{
			if(temp > maximum)
				maximum = temp;
			temp += wyspa[y].odlegloscOdNastepnego;
			y++;
		}
		if(temp > obwod)
		{
			temp -= wyspa[x].odlegloscOdNastepnego;
			x++;
		}
		if(y > n)
			y = y%n;
	}
	return maximum;
}

int main()
{
	wczytaj();
	cout << wyliczNajwiekszaOdleglosc() << "\n";
    	return 0;
}
