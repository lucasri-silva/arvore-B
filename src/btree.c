#include "btree.h"

static int j=0;
static char fileNameBackup[50];
static bool elementoEncontrado;

Pagina* CreateBTree(){
	return NULL;
}

void PesquisaAux(long int elemento, Record r) {
	FILE *fa;
	char fileName[50], elementoProcurado[50];
	char buffer[50], copia[50];
	char path[50] = "./arquivos/";
	sprintf(fileName, "%ld", elemento);
	strcpy(fileNameBackup, fileName);
	sprintf(elementoProcurado, "%ld", r.key);
	strcat(path, fileName);
	fa = fopen(path, "r");
	char *token;

	if(fa == NULL)
		fprintf(stderr, "\n\nArquivo não encontrado! PesquisaAux\n\n");
	else {
		while(fgets(buffer, BUFFER_SIZE, fa) != NULL){
			strcpy(copia, buffer);
			token = strtok(buffer, ",");
			if(!strcmp(token, elementoProcurado)) {
				elementoEncontrado = TRUE;
				printf("\nCPF %s encontrado! %s", elementoProcurado, copia);
				j=0;
				fclose(fa);
				return;
			}
			token = strtok(NULL, "\n");
		}
		elementoEncontrado = FALSE;
		printf("\n[ERROR]: CPF %s NÃO encontrado!", elementoProcurado);
		j=0;
		fclose(fa);
	}
	return;
}

void Pesquisa(Pagina *p, Record *r){
	short i = 1;
	
	if(p == NULL){for(int i=0; i<6; i++);PesquisaAux(maiorElemento[j-1], *r);return;}

	while(i < p->n && r->key > p->r[i-1].key){maiorElemento[j] = p->r[i-1].key;j++;i++;}
	
	if(r->key == p->r[i-1].key){for(int i=0; i<6; i++);PesquisaAux(p->r[i-1].key, *r);return;}
	
	if(r->key < p->r[i-1].key){Pesquisa(p->p[i-1], r);return;}
	if(r->key > p->r[i-1].key){maiorElemento[j] = p->r[i-1].key;j++;Pesquisa(p->p[i], r);return;}
}

void InsereNaPagina(Pagina *p, Pagina *pdir, Record r){ 
	short IsNotPosition;
	int k;

	k = p->n;  
	IsNotPosition = (k > 0);

	while (IsNotPosition){ 

	if (r.key >= p->r[k-1].key){
		IsNotPosition = FALSE;
		break;
	}

	p->r[k]   = p->r[k-1];
	p->p[k+1] = p->p[k];
	k--;
      
	if (k < 1) 
		IsNotPosition = FALSE;
	}

	p->r[k] = r;
	p->p[k+1] = pdir;
	p->n++;

} 

void InsertFixUp(Pagina **p, Pagina **pr, Record r, Record *rr, short *Overflow){ 
	long i=1, j; 
	Pagina *paux;
  
	if(*p == NULL){ 
		*Overflow = TRUE; 
		*rr = r; 
		*pr = NULL;
		return;
	}

	while(i < (*p)->n && r.key > (*p)->r[i-1].key)  i++;

	if(r.key == (*p)->r[i-1].key){ 
		*Overflow = FALSE;
		return;
	}
  
	if(r.key < (*p)->r[i-1].key) i--; 

	/* caminha nas sub-árvores a esquerda e/ou direita da B Tree*/
	InsertFixUp(&(*p)->p[i], pr, r, rr, Overflow);

	/* na chamada (linha 101) esse if valida o registro já existente*/
	if(!*Overflow) return;

	if((*p)->n < MM){ /* página com espaço */ 
		InsereNaPagina(*p, *pr, *rr);
		*Overflow = FALSE;
		return;
	}

	/* Overflow: Pagina tem que ser dividida */
	paux = (Pagina*)malloc(sizeof(Pagina));
	paux->n = 0;  
	paux->p[0] = NULL;

	if(i < M + 1){
		InsereNaPagina(paux, (*p)->p[MM], (*p)->r[MM-1]);
		(*p)->n--;
		InsereNaPagina(*p, *pr, *rr);
	} else 
		InsereNaPagina(paux, *pr, *rr);

	for(j=M+2; j<=MM; j++)
		InsereNaPagina(paux, (*p)->p[j], (*p)->r[j-1]);

	(*p)->n = M;  
	paux->p[0] = (*p)->p[M+1];
	*rr = (*p)->r[M];  
	*pr = paux;
}


void Insere(Pagina **p, Record r){ 
	short Overflow;
	Record rr;
	Pagina *pr, *paux;

	//p = raiz
	//pr = ponteiro de ligação quando estoura
	//r = novo dado
	//rr = dado a ser deslocado
	//Overflow = bit para indicar estouro de páginas
	InsertFixUp(p, &pr, r, &rr, &Overflow);

	if(Overflow){ /* cresce na altura */ 
		paux = (Pagina *)malloc(sizeof(Pagina));
		paux->n = 1;  
		paux->r[0] = rr;
		paux->p[0] = *p;  
		paux->p[1] = pr;
		*p = paux;
	}

}

int InsereAux(Pagina *btree, Record *r, char *nome, int idade) {
	Pesquisa(btree, r);//verifica se cpf já existe na database; encontra arquivo que elemento deve/deveria estar
	
	if(!elementoEncontrado) {//cpf existe no banco de dados
		FILE *fa, *new;
		char path[50] = "./arquivos/";
		int numLinhas=0;
		char buffer[50];
		char copia[50];
		char *token;
		long int cpfArquivo;
		char fileName[50];
		bool arquivaRestante=FALSE;
		strcat(path, fileNameBackup);
		fa = fopen(path, "r");
		
		while(fgets(buffer, BUFFER_SIZE, fa) != NULL){numLinhas++;}
		
		if(numLinhas == 10) {//arquivo cheio; cria-se novo arquivo e o insere na arvore
			fclose(fa);
			sprintf(fileName, "%ld", r->key);
			strcpy(path, "./arquivos/");
			strcat(path, fileName);
			fa = fopen(path, "w");
			fprintf(fa, "%ld", r->key);
			fprintf(fa, "%c", ',');
			fprintf(fa, "%s", nome);
			fprintf(fa, "%c", ',');
			fprintf(fa, "%d", idade);
			fprintf(fa, "%c", '\n');
			Insere(&btree, (*r));
			printf("\nArquivo %s cheio. Novo arquivo %s criado! CPF inserido no arquivo %s", fileNameBackup, fileName, fileName);
			fclose(fa);
		} else {//há espaço no arquivo
			fclose(fa);
			fa = fopen(path, "a");			
			fprintf(fa, "%ld", r->key);
			fprintf(fa, "%c", ',');
			fprintf(fa, "%s", nome);
			fprintf(fa, "%c", ',');
			fprintf(fa, "%d", idade);
			fprintf(fa, "%c", '\n');
			fclose(fa);
			fa = fopen(path, "r");			
			new = fopen("./arquivos/new", "w");
			while(fgets(buffer, BUFFER_SIZE, fa) != NULL) {
				strcpy(copia, buffer);
				token = strtok(buffer, ",");
				cpfArquivo = atoi(token);
				
				if(!arquivaRestante) {
					if(cpfArquivo < r->key) {
						fprintf(new, "%s", copia);
						continue;
					} else {
						fprintf(new, "%ld", r->key);
						fprintf(new, "%c", ',');
						fprintf(new, "%s", nome);
						fprintf(new, "%c", ',');
						fprintf(new, "%d", idade);
						fprintf(new, "%c", '\n');
						arquivaRestante=TRUE;
					}
				} 
				if(cpfArquivo == r->key) break;
				fprintf(new, "%s", copia);
				
			}
			fclose(fa);
			fclose(new);
			remove(path);
			rename("./arquivos/new", path);
			printf("\nCPF inserido no arquivo %s", fileNameBackup);
		}
	}
	else printf("\nCPF %ld já presente no banco de dados!", r->key); 
	
	return 0;
}

int InsereDatabase(Pagina **p, Record r){
	FILE *fn, *fa;
	char *fileName;
	char buffer[80];
	char copia[80];
	char path[20];
	fn = fopen("./data/database.txt", "r");
	short int i = 1;
	
	if( fn == NULL )
		fprintf(stderr, "\n\nArquivo não encontrado! InsereDatabase\n\n");
	else {
		while(fgets(buffer, BUFFER_SIZE, fn) != NULL){
			if(i == 1) {
				strcpy(copia, buffer);
				fileName = strtok(buffer, ",");
				strcpy(path, "./arquivos/");
				strcat(path, fileName);
				fa = fopen(path, "w");
				fprintf(fa, "%s", copia);
				r.key = atof(fileName);
				Insere(p, r);
				i++;
			}
			else if(i == 10) {
				fprintf(fa, "%s", buffer);
				fclose(fa);
				i = 1;
			} else { 
				fprintf(fa, "%s", buffer);
				i++;
			}
		}
		fclose(fn);		
	}
	return 0;
}

void RemoveFixUp(Pagina *p, Pagina *pai, int PosPai, int *underflow) { 
	Pagina *aux; 
	long disp, j;
  
	if(PosPai < pai->n) { 
		aux = pai->p[PosPai + 1];  
		disp = (aux->n - M + 1) / 2;
		p->r[p->n] = pai->r[PosPai];
		p->p[p->n + 1] = aux->p[0];  
		p->n++;
    
		if(disp > 0){ 
			for (j = 1; j < disp; j++)
				InsereNaPagina(p, aux->p[j], aux->r[j-1]);
	      
			pai->r[PosPai] = aux->r[disp-1];  
			aux->n -= disp;
		      
			for(j = 0; j < aux->n; j++) 
				aux->r[j] = aux->r[j + disp];
			for(j = 0; j <= aux->n; j++) 
				aux->p[j] = aux->p[j + disp];
			*underflow = FALSE;
	    
		} else { /* intercala aux em p e libera aux */ 

			for(j = 1; j <= M; j++)
				InsereNaPagina(p, aux->p[j], aux->r[j-1]);
			free(aux);
		
			for(j = PosPai + 1; j < pai->n; j++){ 
				pai->r[j-1] = pai->r[j];
				pai->p[j] = pai->p[j+1];
			}
	      
			pai->n--;
			if(pai->n >= M) 
				*underflow = FALSE;
		}

	} else { /* aux = Pagina a esquerda de p */ 
		aux = pai->p[PosPai-1]; 
		disp = (aux->n - M + 1) / 2;
    
		for (j = p->n; j >= 1; j--) 
			p->r[j] = p->r[j-1];

		p->r[0] = pai->r[PosPai-1];
    
		for (j = p->n; j >= 0; j--) 
			p->p[j+1] = p->p[j];
    
		p->n++;
		if (disp > 0){ /* Existe folga: transf. de aux para p */ 
			for (j = 1; j < disp; j++)
				InsereNaPagina(p, aux->p[aux->n - j + 1], aux->r[aux->n - j]);

			p->p[0] = aux->p[aux->n - disp + 1];
			pai->r[PosPai-1] = aux->r[aux->n - disp];
			aux->n -= disp;  
			*underflow = FALSE;

		} else { /* intercala p em aux e libera p */ 
      
			for (j = 1; j <= M; j++)
				InsereNaPagina(aux, p->p[j], p->r[j-1]);

			free(p);  
			pai->n--;

			if (pai->n >= M)  
				*underflow = FALSE;
		}
	}
}

void Antecessor(Pagina *p, int i, Pagina *pai, int *underflow){ 

	if (pai->p[pai->n] != NULL){ 
		Antecessor(p, i, pai->p[pai->n], underflow);
		if (*underflow) 
			RemoveFixUp(pai->p[pai->n], pai, pai->n, underflow);
		return;
	}
  
	p->r[i-1] = pai->r[pai->n - 1]; 
	pai->n--;  
	*underflow = (pai->n < M);

}

void RemoveAux(Pagina *btree, Record *r, int *underflow) {
	Pesquisa(btree, r);//verifica se cpf já existe na database; encontra arquivo que elemento deve/deveria estar
	
	if(elementoEncontrado) {//cpf existe no banco de dados
		FILE *fa, *new;
		char faPath[50] = "./arquivos/";
		int numLinhas=0;
		char buffer[50];
		char copia[50];
		char *token;
		char fileName[50];
		char *eptr; 
		long int key = strtol(fileNameBackup, &eptr, 10);
		sprintf(fileName, "%ld", r->key);
		strcat(faPath, fileNameBackup);
		fa = fopen(faPath, "r");
		new = fopen("./arquivos/new", "w");

		if(new == NULL)
			fprintf(stderr, "\n\nArquivo não encontrado! InsereAux\n\n");
		else {
			while(fgets(buffer, BUFFER_SIZE, fa) != NULL) { 
				strcpy(copia, buffer);
				token = strtok(buffer, ",");
				if(!strcmp(token, fileName))
					continue;
				fprintf(new, "%s", copia);
				numLinhas++;
			}
			fclose(fa);
			remove(faPath);
			fclose(new);
			rename("./arquivos/new", faPath);
			if(numLinhas == 0) {
				Remove(&btree, key, underflow);
				remove(faPath);
				printf("CPF %ld removido do arquivo %s\n", r->key, fileNameBackup);
				printf("Arquivo %s vazio após remoção do CPF %ld. Arquivo removido!", fileNameBackup, r->key);
			} else
				printf("CPF %ld removido do arquivo %s\n", r->key, fileNameBackup);
		}
	}
}

void Remove(Pagina **p, long int key, int *underflow) { 
	long j, i = 1;
	Pagina *aux;

	if (*p == NULL){ 
		printf("[ERROR]: Record not found!\n"); 
		*underflow = FALSE;
		return;
	}

	aux = *p;
	while (i < aux->n && key > aux->r[i-1].key) i++;

	if(key == aux->r[i-1].key){ 
		if(aux->p[i-1] == NULL) { 
			aux->n--;
			*underflow = (aux->n < M);
			for(j = i; j <= aux->n; j++){ 
				aux->r[j-1] = aux->r[j];  
				aux->p[j] = aux->p[j+1]; 
			}
			return;
		}

		Antecessor(*p, i, aux->p[i-1], underflow);
		if (*underflow) 
			RemoveFixUp(aux->p[i-1], *p, i - 1, underflow);
		return;
	}

	if (key > aux->r[i-1].key) i++;
  
	Remove(&aux->p[i-1], key, underflow);
  
	if(*underflow) 
		RemoveFixUp(aux->p[i-1], *p, i - 1, underflow);
}

void Retira(Pagina **p, int key) { 
	int underflow;
	Pagina *aux;

	Remove(p, key, &underflow);
  
	if(underflow && (*p)->n == 0){ /* Arvore diminui na altura */
		aux = *p;   
		*p = aux->p[0]; 
		free(aux);
	}

}

void Imprime(Pagina **p, int level){ 
	long i;

	if (*p == NULL) return;

	printf("Nivel %d: ", level);
	for (i = 0; i < (*p)->n; i++)
		printf("%ld ",(*p)->r[i].key);
	putchar('\n');
	level++;

	for (i = 0; i <= (*p)->n; i++)
		Imprime(&(*p)->p[i], level);
}
