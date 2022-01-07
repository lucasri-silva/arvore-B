<h1 align="center">Árvore B</h1>

<p align="center">Implementação da árvore B em banco de dados contendo Cadastro de Pessoa Física (CPF)</p>

- Compilador
                
       gcc version 9.3.0
- OS
       
       Ubuntu 20.04.2 LTS

- Executar
 
        terminal:
        ./make clean
        ./make
        ./make run
        
<h2 align="left">Motivação e Aplicação</h2>

<p>Os dispositivos de memória de um computador típico consistem em dois tipos: a memória interna (ou principal, usualmente chips de silício) e a memória externa (ou secundária, usualmente disco ou fitas magnéticas). A memória interna é uma memória volátil com endereçamento direto (RAM) enquanto a memória externa, por outro lado, é uma memória não-volátil com endereçamento indireto. Considerando essas propriedades, em suma, a memória interna é mais cara (mais de uma grandeza mais cara por bit armazenado), tem alta velocidade (tempo de acesso de nano segundos) e pouca capacidade em contraste com a memória externa, que é mais barata, tem baixa velocidade (tempo de acesso de mili segundos) e grande capacidade de armazenamento (no mínimo duas ordens de grandeza maior que a quantidade de memória principal).</p>

<p>Dessa forma, a fim de contornar gargalos de capacidade de armazenamento, custos e, sobretudo, tempo de acesso, a Árvore B é uma estrutura de dados desenvolvida para otimizar o acesso a dispositivos de armazenamento secundário, como discos magnéticos. É aplicada em contextos em que o volume de informação é muito grande para que as chaves possam ser armazenadas somente em memória principal. Sendo assim, somente algumas páginas da árvore são carregadas em memória principal e as demais em memória secundária.</p>

<p>Muitos sistemas de bancos de dados usam árvores B ou variações da mesma para armazenar informações. Dentre suas propriedades ela permite a inserção, remoção e busca de chaves numa complexidade de tempo logarítmica e, por esse motivo, é muito empregada em aplicações que necessitam manipular grandes quantidades de informação tais como um banco de dados ou um sistemas de arquivos.</p>

Exemplos da aplicação da Árvore B em sistemas de arquivos e bancos de dados:
* o sistema de arquivos NTFS do Windows,
* o sistema de arquivos HFS do Mac,
* os sistemas de arquivos ReiserFS, XFS, Ext3FS, JFS do Linux, e
* os bancos de dados ORACLE, DB2, INGRES, SQL e PostgreSQL.

<h2 align="left">Árvore B: Definição</h2>

Seja t a ordem da árvore B. Uma árvore B de ordem t é uma árvore ordenada que é vazia, ou que satisfaz as seguintes condições: /
1. A raiz é uma folha ou tem no mínimo dois filhos;
2. Cada nó diferente do raiz e das folhas possui no mínimo t filhos;
3. Cada nó tem no máximo 2t filhos;
4. Todas as folhas estão no mesmo nível.

Como conseqüência da definição: /
- Cada nó (página) possui entre t-1 e 2t-1 chaves, exceto o raiz que possui entre 1 e 2t-1 chaves.

[Exemplo de árvore B de ordem 2](./b-tree-m=2#gh-light-mode-only)

<h2 align="left">Referências</h2>

CORMEN, T. H.; RIVEST, R. L.; LEISERSON, C. E.; STEIN, C.. Algoritmos: teoria e prática. Elsevier, 2012. \
https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/B-trees.html \
https://pt.wikipedia.org/wiki/%C3%81rvore_B \
https://ic.unicamp.br/~afalcao/mc202/aulas16a18-ArvoreB.pdf
