#include<cstdio>
#include<vector>
#include<algorithm> 
#define MAX_NUMBER 50  // maximum number of tracks on the CD
#define INFNTY 1000  // marks if a track on the CD is already recorded on the tape

using namespace std;

// global variables
int cd_tracks[MAX_NUMBER];  // holds the duration of each track
int num_tracks;  // holds the number of tracks in the cd
vector<int> best_comb;  // holds the current best combination of tracks 
int best_solution = INFNTY;  // holds the current least remaining duration of tape 
vector<int> working_comb;  // holds the combination of tracks the backtracking alg is dealing with at the moment

// optimizes the recording, as the problem states
void optimize(int available_tape, int time_recorded){
	int i;
	int aux;

	// checks if it's not possible to keep recording
	if(*std::min_element(cd_tracks, cd_tracks + num_tracks) > available_tape){
		// checks if the solution we found is better than the one we have now 
		if(available_tape < best_solution){
			// updates our best solution 
			best_solution = available_tape;
			best_comb = working_comb;
		}
	}
	else{
		for(i = 0; i < num_tracks; i++){
			// record a track if we can record it...
			if(cd_tracks[i] != INFNTY && (cd_tracks[i] <= available_tape)){
				aux = cd_tracks[i];  // marks a track already recorded
				cd_tracks[i] = INFNTY;
				working_comb.push_back(aux);  // save recorded track
				optimize(available_tape - aux, time_recorded + aux);  // backtracking recursion!
				cd_tracks[i] = aux;  // unmarks it
				working_comb.pop_back();  // unsave recorded track
			}
		}
	}
}

int main(){
	int i;
	unsigned j;
	int available_tape;  // duration available on the tape
	int sum = 0; 

	// gets duration available on the tape
	while(scanf("%d", &available_tape) != EOF){
		// gets the number of tracks on the cd
		scanf("%d", &num_tracks);

		// gets the duration of each track
		for(i = 0; i < num_tracks; i++){
			scanf("%d", &cd_tracks[i]);
		}

		// finds the answer (optimizes the recording) using backtracking, and print it
		optimize(available_tape, 0);
		for(j = 0; j < best_comb.size(); j++){
			sum += best_comb[j];
			printf("%d ", best_comb[j]);
		}
		printf("sum:%d\n", sum);

		// reinitializes variables
		best_comb.clear(); 
		best_solution = INFNTY; 
		working_comb.clear();
		sum = 0;		
	}

	// bye!
	return 0;
}