#include "btree.h"

int main(){
	Pagina *btree = CreateBTree();
	Record r;
	int opcao=1;
	char nome[15];
	char buffer[50];
	char *token;
	int idade;
	int underflow;
	FILE *fa;
	
	system("exec rm -r ./arquivos/*");//delete previous database
	InsereDatabase(&btree, r);
	
	while(opcao) {
		system("cls || clear");
		printf("1. Inserir \n2. Pesquisar \n3. Remover \n4. Testar inserir a partir de teste-inserir.txt \n5. Testar pesquisar a partir de teste-pesquisa.txt \n6. Testar remover a partir de teste-remover.txt \n7. Imprimir árvore B \n8. Sair  \n\nEscolha uma opção: ");
		scanf("%d", &opcao);
		switch (opcao) {
			case 1:
				printf("CPF: ");
				scanf("%ld", &r.key);
				printf("Nome: ");
				scanf("%s", nome);
				printf("Idade: ");
				scanf("%d", &idade);
				getchar();
				InsereAux(btree, &r, nome, idade);
				printf("\n\nPressione qualquer tecla para continuar ...");getchar();
				break;
			case 2:
				printf("CPF: ");
				scanf("%ld", &r.key);
				Pesquisa(btree, &r);
				printf("\n\nPressione qualquer tecla para continuar ...");getchar();while(getchar() != '\n');
				break;
			case 3:
				printf("CPF: ");
				scanf("%ld", &r.key);
				RemoveAux(btree, &r, &underflow);
				printf("\n\nPressione qualquer tecla para continuar ...");getchar();while(getchar() != '\n');
				break;
			case 4:
				fa = fopen("./data/teste-inserir.txt", "r");
				if(fa == NULL)
					fprintf(stderr, "Arquivo não encontrado!");
				else {
					while(fgets(buffer, BUFFER_SIZE, fa) != NULL){
						token = strtok(buffer, ",");
						r.key = atof(token);
						token = strtok(NULL, ",");
						strcpy(nome, token);
						token = strtok(NULL, ",");
						idade = atof(token);
						InsereAux(btree, &r, nome, idade);
					}
					fclose(fa);
				}
				printf("\n\nPressione qualquer tecla para continuar ...");getchar();while(getchar() != '\n');
				break;
			case 5:
				fa = fopen("./data/teste-pesquisa.txt", "r");
				if(fa == NULL)
					fprintf(stderr, "Arquivo não encontrado!");
				else {
					while(fgets(buffer, BUFFER_SIZE, fa) != NULL){
						r.key = atof(buffer);
						Pesquisa(btree, &r);
					}
					fclose(fa);
				}
				printf("\n\nPressione qualquer tecla para continuar ...");getchar();while(getchar() != '\n');
				break;
			case 6:
				fa = fopen("./data/teste-remover.txt", "r");
				if(fa == NULL)
					fprintf(stderr, "Arquivo não encontrado!");
				else {
					while(fgets(buffer, BUFFER_SIZE, fa) != NULL){
						r.key = atof(buffer);
						RemoveAux(btree, &r, &underflow);
					}
					fclose(fa);
				}
				printf("\n\nPressione qualquer tecla para continuar ...");getchar();while(getchar() != '\n');
				break;
			case 7:
				printf("\n\n");
			  	Imprime(&btree, 0);
			  	printf("\n\nPressione qualquer tecla para continuar ...");getchar();while(getchar() != '\n');
				break;
			default:
				opcao = 0;
		}
	}
	return 0;
}
