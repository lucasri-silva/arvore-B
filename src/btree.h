#ifndef BTREE_H 
#define BTREE_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define M 1
#define MM 3
#define BUFFER_SIZE 1024
#define TRUE 1
#define FALSE 0

typedef struct Record Record;
typedef struct Pagina Pagina;

struct Record {
	long int key;
};

struct Pagina {
	short n;
	Record r[MM];
	Pagina *p[MM + 1];
};

Pagina* CreateBTree();
double atof(const char *str);
long int maiorElemento[6];

void Pesquisa(Pagina *p, Record *r);
void PesquisaAux(long int elemento, Record r);

void InsereNaPagina(Pagina *p, Pagina *pdir, Record r);
void InsertFixUp(Pagina **p, Pagina **pr, Record r, Record *rr, short *Overflow);
void Insere(Pagina **p, Record r);
int InsereDatabase(Pagina **p, Record r);
int InsereAux(Pagina *btree, Record *r, char *nome, int idade);

void RemoveFixUp(Pagina *p, Pagina *pai, int PosPai, int *underflow);
void Antecessor(Pagina *p, int i, Pagina *pai, int *underflow);
void Remove(Pagina **p, long int key, int *underflow);
void RemoveAux(Pagina *btree, Record *r, int *underflow);

void Imprime(Pagina **p, int level);

#endif
