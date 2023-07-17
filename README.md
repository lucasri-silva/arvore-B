<html>
<body>
    <h1 align="center">Árvore B</h1>
      <p align="center">Implementação da árvore B em banco de dados contendo Cadastro de Pessoa Física (CPF).</p>

<h2 align="left">Compilação e Execução</h2>

| OS: Ubuntu 20.04.2 LTS | Compilador: gcc version 9.3.0 |
                
- Executar
 
        terminal:
        ./make clean
        ./make
        ./make run
        
<h2 align="left">Motivação e Aplicação</h2>

<p>Os dispositivos de memória de um computador típico consistem em dois tipos: a memória interna (ou principal, usualmente chips de silício) e a memória externa (ou secundária, usualmente disco ou fitas magnéticas). A memória interna é uma memória volátil com endereçamento direto (RAM) enquanto a memória externa, por outro lado, é uma memória não-volátil com endereçamento indireto. Considerando essas propriedades, em suma, a memória interna é mais cara (mais de uma grandeza mais cara por bit armazenado), tem alta velocidade (tempo de acesso de nano segundos) e pouca capacidade em contraste com a memória externa, que é mais barata, tem baixa velocidade (tempo de acesso de mili segundos) e grande capacidade de armazenamento (no mínimo duas ordens de grandeza maior que a quantidade de memória principal).</p>

<p>Dessa forma, a fim de superar gargalos de capacidade de armazenamento, custos e, sobretudo, tempo de acesso, a Árvore B é uma estrutura de dados desenvolvida para otimizar o acesso a dispositivos de armazenamento secundário, como discos magnéticos. É aplicada em contextos em que o volume de informação é muito grande para que as chaves possam ser armazenadas somente em memória principal. Sendo assim, somente algumas páginas da árvore são carregadas em memória principal e as demais em memória secundária.</p>

<p>Muitos sistemas de bancos de dados usam árvores B ou variações da mesma para armazenar informações. Dentre suas propriedades ela permite a inserção, remoção e busca de chaves numa complexidade de tempo logarítmica e, por esse motivo, é muito empregada em aplicações que necessitam manipular grandes quantidades de informação tais como banco de dados ou sistemas de arquivos.</p>

Exemplos da aplicação da Árvore B em sistemas de arquivos e bancos de dados:
* o sistema de arquivos NTFS do Windows,
* o sistema de arquivos HFS do Mac,
* os sistemas de arquivos ReiserFS, XFS, Ext3FS, JFS do Linux, e
* os bancos de dados ORACLE, DB2, INGRES, SQL e PostgreSQL.

<h2 align="left">Árvore B: Definição</h2>

Seja t a ordem da árvore B. Uma árvore B de ordem t é uma árvore ordenada que é vazia, ou que satisfaz as seguintes condições:
1. A raiz é uma folha ou tem no mínimo dois filhos;
2. Cada nó diferente do raiz e das folhas possui no mínimo t filhos;
3. Cada nó tem no máximo 2t filhos;
4. Todas as folhas estão no mesmo nível.

Como conseqüência da definição:
- Cada nó (página) possui entre t-1 e 2t-1 chaves, exceto o raiz que possui entre 1 e 2t-1 chaves.

| ![b-tree-m=2.png](./images/b-tree-m=2.png?width="550") | 
|:--:| 
| Exemplo de árvore B de ordem 2 |

<h2 align="left">Descrição e Implementação</h2>

<h3>Descrição do problema:</h3>

- criar uma tabela randômica de 1.000 entradas contendo CPF, nome e idade;
- inserir as 1.000 entradas na árvore B, de ordem 2, subdividindo-as em chaves, cada qual representa um arquivo contendo de 1-10 entradas;
- prover um menu que consiga Inserir, Remover e Pesquisar pessoas nesse grupo de arquivos, mantendo a integridade da estrutura e tamanho máximo do arquivo.

<h3>Implementação:</h3>

<p>Primeiramente, uma tabela de 1.000 entradas contendo CPF, nome, idade foi gerada randomicamente em um editor de planilha. A tabela consiste no banco de dados do programa e está localizada no diretório /data com o nome database.txt. Ao iniciarmos o programa, a função InsereDatabase insere a database.txt na ávore B, obedecendo a condição imposta de subdividir as 1.000 entradas em chaves (arquivos) contendo 1-10 entradas. Dessa forma, com a inserção de 1.000 entradas um total de 100 chaves são inseridas na árvore, cada qual representa um arquivo presente na memória secundária com 10 entradas cada.</p>

| ![exemplo-arquivo.png](./images/exemplo-arquivo.png?width="400") | 
|:--:| 
| Exemplo de arquivo. O cpf da 1ª entrada de todo arquivo representa a chave inserida na árvore |

<h2>Pesquisa, Inserção e Remoção</h2>

Como foi mencionado acima, cada chave representa um arquivo que contêm 1-10 entradas (CPF,nome,idade). Logo, a inserção e remoção de uma determinada entrada segue a seguinte lógica:
- se o arquivo no qual a entrada a ser inserida contêm < 10 entradas, então a nova entrada é inserida nesse arquivo;
- se o arquivo no qual a entrada a ser inserida contêm exatamente 10 entradas, então o arquivo está cheio. Uma nova chave e arquivo serão criados com o CPF da nova entrada;
- se o arquivo no qual a entrada a ser removida contêm > 1 entradas, então a entrada é simplesmente removida do arquivo;
- se o arquivo no qual a entrada a ser removida contêm exatamente 1 entrada, significa que essa entrada é a entrada a ser removida e que após sua remoção o arquivo ficará vazio. Assim, após sua remoção a chave representada por esse arquivo será removida da árvore, assim como o respectivo arquivo.

No menu principal há opções de teste que serão usadas para exemplificar Inserção, Remoção e Pesquisa.

<h3>Pesquisa</h3>

Na opção 5, Testar pesquisar a partir de teste-pesquisa.txt , os CPFs presentes no arquivo são simplesmente pesquisados na árvore. No arquivo estão presentes todos os CPFs inseridos no processo de inserção da database.txt, logo é esperado que todos os CPFs contidos no arquivo teste sejam encontrados na pesquisa (se nenhuma remoção foi realizada).

A pesquisa é feita a partir do CPF. Se encontrado, exibe a mensagem "CPF XXXXXXXXXX encontrado!" seguida do CPF, nome e idade.

| ![teste-pesquisar.png](./images/teste-pesquisar.png?width="400") | 
|:--:| 
| À esquerda o arquivo teste-pesquisa.txt. À direita o output da pesquisa exibindo CPF, nome, idade dos registros pesquisados |

<h3>Inserção</h3>

Na opção 4, Testar inserir a partir de teste-inserir.txt, as entradas presentes no arquivo são inseridas na árvore. Neste exemplo ocorre estouro de arquivo, isto é, ao inserir as entradas os arquivos correspondentes excedem a capacidade máxima de 10 entradas. Por conseguinte, novas chaves são inseridas na árvore nomeadas com o CPF da entrada que provocou o estouro.

| ![insercao.png](./images/insercao.png?width="400") | 
|:--:| 
| Exemplo de inserção. Note que o CPF 1600000000 deveria ser inserido no arquivo 1439559022, visto que 1439559022 < 1600000000 < 2070173720. No entanto, o arquivo 1439559022 está cheio. Dessa forma, uma nova chave representada pelo CPF 1600000000 é inserida na árvore e um novo arquivo com o mesmo CPF é criado. O mesmo ocorre para os CPFs 1700000000 e 1800000000 |

| ![arvore-antes-pos-insercao.png](./images/arvore-antes-pos-insercao.png?width="400") | 
|:--:| 
| Impressão da ávore pré e pós inserção de teste-inserir.txt |

Vale ressaltar também que à medida que as entradas são inseridas nos arquivos elas são arranjadas em ordem crescente, tendo o CPF como referência.

| ![teste-inserir.png](./images/teste-inserir.png?width="400") | 
|:--:| 
| À esquerda parte do arquivo utilizado para testar inserções, teste-inserir.txt. À direita o arquivo 1600000000, em /arquivos, criado após as inserções |

<h3>Remoção</h3>

Na opção 6, Testar remover a partir de teste-remover.txt, as entradas presentes no arquivo são removidas da árvore. Neste exemplo, conforme as entradas são removidas dos arquivos esses se tornam vazios e são, portanto, removidos de /arquivos, além obviamente da respectiva chave ser removida da árvore.

| ![teste-remover.png](./images/teste-remover.png?width="400") | 
|:--:| 
| Arquivo teste-remover.txt com as chaves a serem removidas |

| ![remocao.png](./images/remocao.png?width="400") | 
|:--:| 
| Note que após a remoção do último CPF 15194563598 do arquivo 14712514720 o mesmo fica vazio e, consequentemente, é removido de /arquivos e sua respectiva chave 14712514720 é removida da árvore |

| ![arvore-antes-pos-remocao](./images/arvore-antes-pos-remocao.png?width="400") | 
|:--:| 
| Impressão da ávore pré e pós remoção de teste-remover.txt |

<h2 align="left">Referências</h2>

CORMEN, T. H.; RIVEST, R. L.; LEISERSON, C. E.; STEIN, C.. Algoritmos: teoria e prática. Elsevier, 2012. \
https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/B-trees.html \
https://pt.wikipedia.org/wiki/%C3%81rvore_B \
https://ic.unicamp.br/~afalcao/mc202/aulas16a18-ArvoreB.pdf
