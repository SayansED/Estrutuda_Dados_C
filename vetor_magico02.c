#include<stdlib.h>
#include<stdio.h>
#include<time.h>

// Fun��o da vers�o 01
struct vetor_magico{
	int ocupacao, tamanho;
	int * v;
};


// Fun��o da vers�o 02
/*void inicia_vm (int t, struct vetor_magico * pvm){ //Toda vez que for modificar passa por ponteiro
	// Operador seta ->
	// A estrutura que o pvm aponta
	pvm->v = (int *) malloc (t * sizeof(int));
	pvm->ocupacao = 0;
	pvm->tamanho = t;
}*/


// Fun��o da vers�o 03
struct vetor_magico * cria_vm (int t){
	struct vetor_magico * aux;
	aux = (struct vetor_magico * ) malloc (sizeof(struct vetor_magico));
	if (aux != NULL){
		aux->v = (int *) malloc (t * sizeof(int));
		if (aux->v == NULL){
			return NULL;
		}
		aux->tamanho = t;
		aux->ocupacao = 0;
	}
	return aux; 
}

//versao 01
/*int esta_cheio (struct vetor_magico * pvm){
	if(pvm->ocupacao == pvm->tamanho)
		return 1;
	else
		return 0;
}*/

//versao 02
int esta_cheio (struct vetor_magico * pvm){
	return pvm->ocupacao == pvm->tamanho;
}


//versao 01
int aumenta_vetor (struct vetor_magico * pvm){
	int i, *temp;
	temp = (int *) malloc (2 * pvm->tamanho * sizeof(int));
	if(!temp) //ou temp == NULL, mesma coisa
		return 0;
	for(i=0; i<pvm->ocupacao; i++){
		temp[i] = pvm->v[i];
	}
	free (pvm->v);  //Liberar oq ele aponta
	pvm->v = temp;  //Apontar para outro
	pvm->tamanho = 2 * pvm->tamanho; //Atualizar tamanho
	return 1;
}


//Preencher struct
int insere_elemento (int e, struct vetor_magico * pvm){
	if(esta_cheio(pvm)){
		if(!redimensiona_vetor(pvm, pvm->tamanho * 2)){
			return 0;
		}
	}
	pvm->v[pvm->ocupacao++] = e;
	//ou
	/*
	//pvm->v[pvm->ocupacao] = e;
	//pvm->ocupacao++;
	*/
	return 1;
}

int remove_elemento(int *p, struct vetor_magico * pvm){
	//Verificar se esta ocupado
	if(esta_vazio(pvm) == 1)
		return -1;
	pvm->ocupacao--; /* Primeiro decremento ocupa��o depois tiro elemento */
	*p = pvm->v[pvm->ocupacao];
	//*p = pvm->v[--pvm->ocupacao];

	//redimensionar
	if(pvm->ocupacao <= pvm->tamanho/4)
		if(!redimensiona_vetor(pvm, pvm->tamanho/2))
			return 0;
	//Se deu tudo certo '1'
	return 1;
}


//Exercicio  **********************************************************
int ultimo_inserido(struct vetor_magico * pvm){
	if(!esta_vazio(pvm))
		return pvm->v[pvm->ocupacao-1];
	return -1;
}

int redimensiona_vetor(struct vetor_magico * pvm, int novo_tamanho){
	int i, *temp;
	temp = (int*)malloc (novo_tamanho * sizeof(int));
	if(!temp)
		return 0;
	for(i=0; i<pvm->ocupacao; i++){
		temp[i] = pvm->v[i];
	}
	free(pvm->v);
	pvm->v = temp;
	pvm->tamanho = novo_tamanho;
	return 1;
}


/*int diminui_vetor(struct vetor_magico * pvm){
	int i, *temp;
	temp = (int*)malloc (pvm->tamanho/2 * sizeof(int));
	if(!temp)
		return 0;
	for(i=0; i<pvm->ocupacao; i++){
		temp[i] = pvm->v[i];
	}
	free(pvm->v);
	pvm->v = temp;
	pvm->tamanho = pvm->tamanho/2;
	return 1;
}*/

int esta_vazio(struct vetor_magico * pvm){
	return pvm->ocupacao == 0;
}


//Versao 01

/*main(){
	printf("Tamanho de um inteiro = %d\n", sizeof(int));
	printf("Tamanho de um ponteiro de inteiro = %d\n", sizeof(int));
	printf("Tamanho da struct = %d\n", sizeof(struct vetor_magico));
	
	return 0;
}*/



//Versao 02

/*int main(){
	struct vetor_magico vm;
	int t;
	printf("Digite o tamanho do vetor: \n"); 
	scanf("%d", &t);
	//vm.v = (int *) malloc (t * sizeof(int));  //Estrutura vm no campo v, estou alocando o vetor
	//vm.ocupacao = 0; //alocando o conteudo
	//vm.tamanho = t; //alocando o tamanho
	inicia_vm (t, &vm);
		
	return 0;
}*/



//Versao 03
/*
int main(){
	struct vetor_magico * pvm;
	int t;
	printf("Digite o tamanho do vetor: \n"); 
	scanf("%d", &t);
	pvm =  cria_vm (t);
	if(pvm != NULL){
		printf("Vetor magico alocado com sucesso\n");
		for (t=1; t<=100; t++){
			if(insere_elemento(t, pvm)){
				printf("%d inserido - tamanho atual = %d\n", t, pvm->tamanho);
			}
		}
	}
	else{
		printf("Falha na aloca��o de memoria\n");
	}
	
	return 0;
}*/


// Vers�o 04
int main(){
	//Inserir e remover elementos aleatoriamente at� o vetor ficar vazio
	struct vetor_magico * pvm;
	int t;
	srand(time(0)); //Inicializa o gerador ramdomico
	printf("Digite o tamanho do vetor: \n"); 
	scanf("%d", &t);
	pvm =  cria_vm (t);
	if(pvm != NULL){
		do{
			if(rand() % 2){
				if(insere_elemento(rand() % 10, pvm)){
					printf("\nInseriu, tamanho atual = %d", pvm->tamanho);
				}
			}
			else{
				if(remove_elemento(&t, pvm) >= 0){
					printf("\nRemoveu, tamanho atual = %d", pvm->tamanho);
				}	
			}
		}while(!esta_vazio(pvm));
	}
	else{
		printf("Falha na aloca��o de memoria\n");
	}
	
	return 0;
}
