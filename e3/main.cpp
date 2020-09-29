#include<cstdio>
#include<vector>
#include<algorithm>
#include <cmath>

using namespace std;

int main(){
	int current_test_case = 1;  // holds the number of current test case
	int num_of_chambers;  // holds the number of chambers
	int num_of_specimen;  // holds the number of specimen
	int aux_mass;  // temporarily holds the mass of a specimen
	vector<int> masses;  // holds the masses of each specimen
	float imbalance = 0;  // holds the imbalance of each test case
	float average = 0;  // holds the average for the imbalance evaluation
	int i;

	// the problem states the program must read from a file
	while(scanf("%d", &num_of_chambers) != EOF){
		// get the number of specimens
		scanf("%d", &num_of_specimen);

		for(i = 0; i < num_of_specimen; i++){
			// temporarily get the mass of a specimen
			scanf("%d", &aux_mass);

			// for the average evaluation
			average += aux_mass;

			// put the mass in the vector with all the other specimens' masses
			masses.push_back(aux_mass);
		}

		// finish average evaluation
		average = (average / num_of_chambers);	

		// -- following a greedy strategy: load balancing
		// 2*num_of_chambers - num_of_specimen "dummy specimens" will be added to the vector 
		for(i = 0; i < (2*num_of_chambers - num_of_specimen); i++){
			// dummy specimens have zero mass
			masses.push_back(0);
		}

		// order the vector
		std::sort (masses.begin(), masses.end());

		// next, we print the mass pairs for each chamber
		printf("Set #%d\n", current_test_case);
		for(i = 0; i < num_of_chambers; i++){
			printf(" %d: ", i);

			// print the mass in a chamber only if it's not zero
			if(masses[i] != 0){
				printf("%d ", masses[i]);
			}

			if(masses[masses.size() - i - 1] != 0){
				printf("%d", masses[masses.size() - i - 1]);
			}
			printf("\n");

			// evaluate part of the imbalance:
			imbalance += std::abs(masses[i] + masses[masses.size() - i - 1] - average);			
		}

		// print the imbalance
		printf("IMBALANCE = %.5f\n", imbalance);
		printf("\n");

		// reinitialize variables for the next test case
		masses.clear();
		imbalance = 0;
		average = 0;
		current_test_case++;
	}

	// bye!
	return 0;
}