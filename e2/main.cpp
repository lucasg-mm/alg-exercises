#include<cstdio>
#include<vector>

using namespace std;

int main(){
	int i;
	int j;
	int k;
	int num_test_cases; // number of test cases
	int num_type_coin; // different types of coin
	int coin; // temporarily holds the value of a coin
	vector<int> available_coins;  // holds the value of every type of coin of a country
	int sultan_withdraw = 0;  // holds the value to be withdrawed from the bank by the sultan
	int num_diff_coins = 0; // holds the number of different coins the sultan got from the bank (final result of a test case)

	// get the number of test cases
	scanf("%d", &num_test_cases);

	for(i = 0; i < num_test_cases; i++){
		// get the number of different types of coin
		scanf("%d", &num_type_coin);

		for(j = 0; j < num_type_coin; j++){
			// temporarily get the value of a coin
			scanf("%d", &coin);

			// insert the acquired value in the vector of every type of coin of a country
			available_coins.push_back(coin);
		}

		// let's determine if we can get the kth coin using the loop below
		for(k = 0; k < num_type_coin - 1; k++){
			sultan_withdraw += available_coins[k];

			if(sultan_withdraw < available_coins[k+1]){
				// kth coin succesfully obtained
				num_diff_coins++;
			}
			else{  // the kth coin couldn't be obtained 
				sultan_withdraw -= available_coins[k];				
			}
		}

		// one more unique coin can be obtained -- the last one can always be obtained
		num_diff_coins++;		

		// print the result for current test case
		printf("%d\n", num_diff_coins);

		// reinitialize variables
		sultan_withdraw = 0;
		num_diff_coins = 0;
		available_coins.clear();
	}

	// bye!
	return 0;
}