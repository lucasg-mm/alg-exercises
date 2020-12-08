#include <iostream>
#include <cstdio>
#include <cmath>
#include <bitset>
#include <vector>
#include <map>


using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef map<int, int> mii;



ll tamCrivo;

bitset<10000010> bs;    //BITSET funciona como booleano (0 ou 1), ma usa 1 bit apenas... !!!
vector<ll> primos;


vi fatoresPrimos(ll n){
	vi fatores; 
	ll FP;

	ll ind = 0;
	FP = primos[ind];  // o primeiro primo eh o 2.....

	while (FP*FP <= n){    // nao precisa iterar até o fim.. apenas até a raiz quadrada..
		while ( n % FP == 0){
			fatores.push_back(FP);
			n = n / FP;
		}
		FP = primos[++ind];
	}

	if (n != 1)     // VAI QUE O N QUE FOI PASSADO É um PRIMO !!!!
		fatores.push_back(n);

	return fatores;

}


mii fatoresPrimosMAP(ll n){
	mii fatores; 
	ll FP;

	ll ind = 0;
	FP = primos[ind];  // o primeiro primo eh o 2.....

	while (FP*FP <= n){    // nao precisa iterar até o fim.. apenas até a raiz quadrada..
		while ( n % FP == 0){
			fatores[FP]++;
			n = n / FP;
		}
		FP = primos[++ind];
	}

	if (n != 1)     // VAI QUE O N QUE FOI PASSADO É um PRIMO !!!!
		fatores[n]++;

	return fatores;

}



void crivo(ll n){
	tamCrivo = n +1;

	bs.set();   //inicia o bit como TRUE....
	bs[0] = bs[1] = 0;

	for (ll i = 2; i <= tamCrivo; i++){  //PERCIREE TODO O CRIVO...
		if (bs[i])  {     //se ele é primo, elimina todos os seus multiplos e coloca no vetor primos.. 
			for (ll j = i*i; j <= tamCrivo; j+=i)
			{
				bs[j] = 0;
			}
			primos.push_back(i);
		}
	
	}

}



int main(int argc, char const *argv[])
{
	/* code */

	crivo (10000000);



	vi r = fatoresPrimos(120);


	for (vi::iterator i = r.begin(); i != r.end(); i++)
		printf("%d ", *i);
	printf("\n");

	r = fatoresPrimos(136117223861LL);
	for (vi::iterator i = r.begin(); i != r.end(); i++)
		printf("%d ", *i);
	printf("\n");

	mii m = fatoresPrimosMAP(120);
	for (mii::iterator i = m.begin(); i != m.end(); i++)
		printf("%d -> %d , ", i->first, i->second);
	printf("\n");



	return 0;
}