<h1 align="center">B-Tree</h1>
<p align="center">Implementation of a B-tree in a database containing Brazilian Individual Taxpayer Registration (CPF).</p>

<h2 align="left">Compilation and Execution</h2>

| OS: Ubuntu 20.04.2 LTS | Compiler: gcc version 9.3.0 |

- Run
 
        terminal:
        ./make clean
        ./make
        ./make run
        
<h2 align="left">Motivation and Application</h2>

<p>The memory devices of a typical computer consist of two types: internal memory (or main memory, usually silicon chips) and external memory (or secondary memory, usually disks or magnetic tapes). Internal memory is volatile memory with direct addressing (RAM), while external memory, on the other hand, is non-volatile memory with indirect addressing. Considering these properties, in summary, internal memory is more expensive (more than one order of magnitude more expensive per stored bit), has high speed (nanosecond access time), and low capacity, in contrast to external memory, which is cheaper, slower (millisecond access time), and has large storage capacity (at least two orders of magnitude greater than the amount of main memory).</p>

<p>Thus, in order to overcome storage capacity bottlenecks, costs, and especially access time limitations, the B-tree is a data structure developed to optimize access to secondary storage devices such as magnetic disks. It is applied in contexts where the volume of information is too large for the keys to be stored only in main memory. Therefore, only some pages of the tree are loaded into main memory while the others remain in secondary memory.</p>

<p>Many database systems use B-trees or variations of them to store information. Among their properties, they allow insertion, removal, and key search operations with logarithmic time complexity and, for this reason, they are widely used in applications that need to manipulate large amounts of information such as databases and file systems.</p>

Examples of B-tree applications in file systems and databases:
* the Windows NTFS file system,
* the Mac HFS file system,
* the Linux ReiserFS, XFS, Ext3FS, and JFS file systems, and
* the ORACLE, DB2, INGRES, SQL, and PostgreSQL databases.

<h2 align="left">B-Tree: Definition</h2>

Let t be the order of the B-tree. A B-tree of order t is an ordered tree that is empty or satisfies the following conditions:
1. The root is a leaf or has at least two children;
2. Every node except the root and leaves has at least t children;
3. Every node has at most 2t children;
4. All leaves are at the same level.

As a consequence of the definition:
- Each node (page) has between t-1 and 2t-1 keys, except the root, which has between 1 and 2t-1 keys.

| ![b-tree-m=2.png](./images/b-tree-m=2.png?width="550") | 
|:--:| 
| Example of a B-tree of order 2 |

<h2 align="left">Description and Implementation</h2>

<h3>Problem Description:</h3>

- create a random table with 1,000 entries containing CPF, name, and age;
- insert the 1,000 entries into the B-tree of order 2, subdividing them into keys, each representing a file containing 1–10 entries;
- provide a menu capable of Inserting, Removing, and Searching people in this group of files while maintaining the integrity of the structure and maximum file size.

<h3>Implementation:</h3>

<p>First, a table with 1,000 entries containing CPF, name, and age was randomly generated in a spreadsheet editor. The table consists of the program database and is located in the /data directory under the name database.txt. When starting the program, the InsereDatabase function inserts database.txt into the B-tree, respecting the imposed condition of subdividing the 1,000 entries into keys (files) containing 1–10 entries. Thus, with the insertion of 1,000 entries, a total of 100 keys are inserted into the tree, each representing a file stored in secondary memory with 10 entries each.</p>

| ![exemplo-arquivo.png](./images/exemplo-arquivo.png?width="400") | 
|:--:| 
| Example of a file. The CPF of the first entry of every file represents the key inserted into the tree |

<h2>Search, Insertion, and Removal</h2>

As mentioned above, each key represents a file containing 1–10 entries (CPF, name, age). Therefore, insertion and removal of a given entry follow the following logic:
- if the file in which the entry is to be inserted contains < 10 entries, then the new entry is inserted into that file;
- if the file in which the entry is to be inserted contains exactly 10 entries, then the file is full. A new key and file will be created with the CPF of the new entry;
- if the file in which the entry to be removed is located contains > 1 entries, then the entry is simply removed from the file;
- if the file in which the entry to be removed is located contains exactly 1 entry, this means that after its removal the file will become empty. Therefore, after removal the key represented by this file will also be removed from the tree, along with the respective file.

The main menu contains test options that will be used to demonstrate Insertion, Removal, and Search.

<h3>Search</h3>

In option 5, Test search from teste-pesquisa.txt, the CPFs present in the file are simply searched in the tree. The file contains all CPFs inserted during the insertion process of database.txt, therefore all CPFs contained in the test file are expected to be found in the search (if no removal has been performed).

The search is performed using the CPF. If found, the message "CPF XXXXXXXXXX found!" is displayed, followed by the CPF, name, and age.

| ![teste-pesquisar.png](./images/teste-pesquisar.png?width="400") | 
|:--:| 
| On the left, the test file teste-pesquisa.txt. On the right, the search output displaying CPF, name, and age of the searched records |

<h3>Insertion</h3>

In option 4, Test insert from teste-inserir.txt, the entries present in the file are inserted into the tree. In this example, file overflow occurs, that is, when inserting the entries the corresponding files exceed the maximum capacity of 10 entries. Consequently, new keys are inserted into the tree named with the CPF of the entry that caused the overflow.

| ![insercao.png](./images/insercao.png?width="400") | 
|:--:| 
| Insertion example. Note that CPF 1600000000 should be inserted into file 1439559022, since 1439559022 < 1600000000 < 2070173720. However, file 1439559022 is full. Therefore, a new key represented by CPF 1600000000 is inserted into the tree and a new file with the same CPF is created. The same occurs for CPFs 1700000000 and 1800000000 |

| ![arvore-antes-pos-insercao.png](./images/arvore-antes-pos-insercao.png?width="400") | 
|:--:| 
| Tree print before and after insertion of teste-inserir.txt |

It is also worth mentioning that as entries are inserted into the files they are arranged in ascending order using CPF as the reference.

| ![teste-inserir.png](./images/teste-inserir.png?width="400") | 
|:--:| 
| On the left, part of the file used to test insertions, teste-inserir.txt. On the right, the file 1600000000 in /arquivos, created after insertions |

<h3>Removal</h3>

In option 6, Test remove from teste-remover.txt, the entries present in the file are removed from the tree. In this example, as entries are removed from the files they become empty and are therefore removed from /arquivos, in addition to the respective key obviously being removed from the tree.

| ![teste-remover.png](./images/teste-remover.png?width="400") | 
|:--:| 
| File teste-remover.txt containing the keys to be removed |

| ![remocao.png](./images/remocao.png?width="400") | 
|:--:| 
| Note that after removing the last CPF 15194563598 from file 14712514720, it becomes empty and consequently is removed from /arquivos and its respective key 14712514720 is removed from the tree |

| ![arvore-antes-pos-remocao](./images/arvore-antes-pos-remocao.png?width="400") | 
|:--:| 
| Tree print before and after removal of teste-remover.txt |

<h2 align="left">References</h2>

CORMEN, T. H.; RIVEST, R. L.; LEISERSON, C. E.; STEIN, C.. Algorithms: Theory and Practice. Elsevier, 2012. \
https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/B-trees.html \
https://en.wikipedia.org/wiki/B-tree \
https://ic.unicamp.br/~afalcao/mc202/aulas16a18-ArvoreB.pdf
