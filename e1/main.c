#include <stdio.h>
#include <stdlib.h>
#define NOONE -1 // indica que está solteiro   
#define DONE -2 // indica que já propôs

// checa se existe homem solteiro que não propôs para todas as mulheres
int get_man(int** men, int marriage_number){
	int i;

	for(i = 0; i < marriage_number; i++){
		if(men[i][0] == NOONE && men[i][1] != marriage_number){
			return i;  // se achou retorna a linha correspondente da matriz men
		}
	}

	return -1;  // não existe nenhum homem solteiro que não propôs para todas as mulheres
}

// obtém a primeira mulher na lista de um homem para a qual ele ainda não propôs
int get_woman(int** men, int marriage_number, int man_index){
	int j;
	int chosen_woman;

	for(j = 3; j < marriage_number + 3; j++){
		if(men[man_index][j] != DONE){
			chosen_woman = men[man_index][j] - 1;
			men[man_index][j] = DONE;
			return chosen_woman;
		}
	}

	return -1;
}

// dados dois homens, retorna qual a mulher prefere
int which_one(int** women, int manA, int manB, int woman_index, int marriage_number){
	int j;

	for(j = 3; j < marriage_number + 3; j++){
		if(women[woman_index][j] == manA + 1){
			return manA;
		}

		if(women[woman_index][j] == manB + 1){
			return manB;
		}		
	}

	return -1; 
}

int main(){
	// Para resolver o problema, vamos representar os dados em duas matrizes:
	// uma para homens e outra pra mulheres. Cada linha de uma matriz representa um
	// homem/mulher. O primeiro elemento da linha diz com quem a pessoa da linha está
	// casado atualmente (exemplo: o primeiro elemento da linha 2 da matriz men == 4,
	// então o homem 1 está casado com a mulher 3). O segundo elemento de uma linha
	// representa a quantidade de pessoas para qual a pessoa da linha propôs casamento.
	// O restante dos elementos da linha é o número da pessoa + a lista de preferências. 

	int** women;
	int** men;
	int test_case_number;  // número de casos de teste
	int marriage_number;  // número de casamentos que deve ser encontrado
	int i;
	int j;
	int k;
	int chosen_man;
	int chosen_woman;

	scanf("%d", &test_case_number);  // obtém o número de casos de teste

	for(i = 0; i < test_case_number; i++){  // executa os casos de teste um a um...
		scanf("%d", &marriage_number);  // obtém o número de casamentos

		// cria cada matriz
		// mulheres
		women = (int**) calloc(marriage_number, sizeof(int*));
		for(j = 0; j < marriage_number; j++){
			women[j] = (int*) calloc(marriage_number + 3, sizeof(int));
			women[j][0] = NOONE;  // todas as mulheres começam solteiras 
			women[j][1] = 0;  // todas as mulheres começam sem propor a ninguem (nunca propõem nesse algoritmo)
		}

		// homens
		men = (int**) calloc(marriage_number, sizeof(int*));
		for(j = 0; j < marriage_number; j++){
			men[j] = (int*) calloc(marriage_number + 3, sizeof(int));
			men[j][0] = NOONE;  // todas os homens começam solteiros 
			men[j][1] = 0;  // todas os homens começam sem ter proposto a ninguem
		}

		// inicializa cada lista de preferência
		// mulheres
		for(j = 0; j < marriage_number; j++){
			for(k = 2; k < marriage_number + 3; k++){
				scanf("%d", &women[j][k]);
			}			
		}

		// homens 
		for(j = 0; j < marriage_number; j++){
			for(k = 2; k < marriage_number + 3; k++){
				scanf("%d", &men[j][k]);
			}			
		}

		// enquanto existir homem solteiro que ainda não propôs para todas as mulheres...
		while((chosen_man = get_man(men, marriage_number)) != -1){
			// obtém a primeira mulher da lista do homem (que ele ainda não propôs)
			chosen_woman = get_woman(men, marriage_number, chosen_man);

			// homem propõe para essa mulher
			men[chosen_man][1] = men[chosen_man][1] + 1;

			if(women[chosen_woman][0] == NOONE){  // se a mulher está solteira
				// o homem e a mulher escolhida ficam noivos
				women[chosen_woman][0] = chosen_man;
				men[chosen_man][0] = chosen_woman;
			}
			else{  // se a mulher estiver comprometida

				// se a mulher preferir o homem que acabou de propor...
				if(chosen_man == which_one(women, chosen_man, women[chosen_woman][0], chosen_woman, marriage_number)){
					// o noivo da mulher fica solteiro 
					men[women[chosen_woman][0]][0] = NOONE;

					// a mulher e o homem que propôs ficam noivos
					women[chosen_woman][0] = chosen_man;
					men[chosen_man][0] = chosen_woman;					
				}
			}		
		}

		// imprime os casais e libera a memória alocada
		for(j = 0; j < marriage_number; j++){
			printf("%d %d\n", j+1, men[j][0] + 1);		
			free(men[j]);
			free(women[j]);		
		}
		free(men);
		free(women);
	}

	return 0;  // programa encerra com sucesso
}