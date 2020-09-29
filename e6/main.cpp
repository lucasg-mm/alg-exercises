#include <stdio.h>
#include <queue>
#include <cstring>
#include <stdlib.h> 

using namespace std;

struct state{
	int digit[4];
	int depth;
	int f;  // função de avaliação
    bool operator<(const state& comp) const
    {
        return f > comp.f;
    }	
};

int moves [8][4]= { {-1, 0, 0, 0 },
					 { 1, 0, 0, 0 },
					 { 0,-1, 0, 0 },
					 { 0, 1, 0, 0 },
					 { 0, 0,-1, 0 }, 
					 { 0, 0, 1, 0 },
					 { 0, 0, 0,-1 },
					 { 0, 0, 0, 1 } };

void next_states(state s, state next[8], state final){
	int i,j;
	int h;  // função heurística

	for(i=0; i<8; i++){
		h = 0;
		next[i] = s;
		next[i].depth = s.depth+1;
		for(j=0; j<4; j++){
			next[i].digit[j] += moves[i][j];
			if (next[i].digit[j]<0)
				next[i].digit[j] = 9;
			if (next[i].digit[j]>9)
				next[i].digit[j] = 0;

			// calcula função heurísitica
			if(abs(next[i].digit[j] - final.digit[j]) > 5){
				h += 10 - abs(next[i].digit[j] - final.digit[j]);
			}
			else{
				h += abs(next[i].digit[j] - final.digit[j]);
			}
		}

		// calcula a função de avaliação de cada um
		next[i].f = next[i].depth + h;
	}
}


int equal(state s, state e){
	int i;
	for (i=0; i<4; i++)
		if (s.digit[i] != e.digit[i])
			return 0;

	return 1;
}

// busca em largura
int bfs(state current, state final, int visited[10][10][10][10]){
	state next[8];
	int i;
	priority_queue<state> q;

	// o estado inicial pode ser invalido !!!!
	if (!visited[current.digit[0]][current.digit[1]][current.digit[2]][current.digit[3]]){
		visited[current.digit[0]][current.digit[1]][current.digit[2]][current.digit[3]] = 1;
		q.push(current);

		while(!q.empty()) {
			current = q.top();
			// printf("TÁ NO TOPO: %d\n", current.f);
			q.pop();
			// chegou no estado final.. basta terminar (este é o nivel minino!!!) e mostrar o nivel que saiu da árvore...!
			if (equal(current, final))
				return current.depth;
			// nao é igual.. entao, calcula todos os proximos estados e continua a busca em largura.....
			next_states(current, next, final);
			for (i=0; i<8; i++)
				if (!visited[next[i].digit[0]][next[i].digit[1]][next[i].digit[2]][next[i].digit[3]]){
					visited[next[i].digit[0]][next[i].digit[1]][next[i].digit[2]][next[i].digit[3]] = 1;
					q.push(next[i]);
				}
		}
	}
	return -1;
}


int main (){
	int nr_testes, test, forbidden, i;
	int visited[10][10][10][10];
	state initial, final, aux;

	scanf("%d", &nr_testes);
	for (test=0; test<nr_testes; test++){
		scanf("%d %d %d %d", &initial.digit[0], &initial.digit[1], &initial.digit[2], &initial.digit[3]);
		scanf("%d %d %d %d", &final.digit[0], &final.digit[1], &final.digit[2], &final.digit[3]);
		scanf("%d", &forbidden);


		memset(visited, 0, sizeof visited);

		// obtendo e marcando proibidos
		for(i=0; i<forbidden; i++) {
			scanf("%d %d %d %d", &aux.digit[0], &aux.digit[1], &aux.digit[2], &aux.digit[3]);
			visited[aux.digit[0]][aux.digit[1]][aux.digit[2]][aux.digit[3]] = 1;
		}
		initial.depth=0;
		printf("%d\n", bfs(initial, final, visited));
	}
	return 0;


}