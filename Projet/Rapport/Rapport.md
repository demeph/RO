# Projet RO  : BladeFlyer II - conquest of water

[TOC]
## Introduction

Le projet consiste à trouver la meilleur solution pour collecter de l'eau de different point de pompage pour sauver l'humanité  en  utilisant la drone et en parcourant la distance minimal entre la base et les points de pompage. Notre travail consiste à generer tous les regroupement possible entre les points pompage en les filtrant suivant la capacité du drone. Ensuite, on calcule le plus courte chemin entre les points pompage et la base.

## Analyse du problème 
Posons tout d'abord ce problème sous la forme d'un programme linaire :

### Les  notations du sujet
- $n \in \mathbb{N}$, le nombre de lieux
- $d_i$, la quantité d'eau disponible au point $i$, avec $i \in \{1, ..., n\}$
- $Ca \in \mathbb{N}$, la capacité du drone

### Définition
Un regroupement $r$ est dit *réalisable* si $\sum_{i \in r} d_i \leq Ca$

### Paramètres
- $Re$ l'ensemble des regroupements réalisables

### Variables de décison
$$ x_i = \begin{cases}  1\space si\space on\space choisit\space le\space regroupement \space i  \\ 0 \space sinon \end{cases} $$

### Fonction objectif
Minimiser la distance parcourue par le drone 
$$ min\space \sum_{i = 1}^{Card(Re)}  l_i *x_i$$
avec $l_i$ la longueur de la plus courte tournée couvrant le regroupement $i$
ce qui donne $$ \sum_{i=1}^{27} l_i*x_i $$ sur l'exemple donné dans le sujet.

### Contraintes
- Le point de pompage $i$ doit être visité une et une seule fois, c'est-à-dire on doit avoir le nombre de regroupement dans laquelle apparait lieu de pompage i :
  $$ \sum_ {i =1}^{nbRegroupement} x_i = 1 $$

- contrainte sur l'exemple du sujet, pour le point de pompage 1 :
  $$ \sum_{i=1}^{13} x_i = 1 $$

- contrainte d'integrité :
  $ x_i \in \{0,1\},\space \forall i \in [1,nbVariable]$

Dans notre programme lineaire, on possede les paramètres qu'on ne connait pas  la valeur au debut. Ces sont  nbVariable*, *nbRegroupemet* : 

- Pour calculer *nbVariable* , nous avons besoin degenerer tous les ss-ensembles en fonction de nombre de lieux de pompage(privé de 0) en utilisant l'algorithme de la section *Explication de l'algorithme*. 
- La valeur nbRegroupement est donnée par le nombre de lieux de pompage(privé de 0).


## Description des algorithmes
### Génération des sous-ensembles

Il s'agit ici de générer les sous-ensembles des tournées réalisables, c'est à dire celles dont la quantité d'eau ne dépasse pas la capacité du drone. Le code expliqué par la suite correspond à la méthode *donnees::generer_probleme*.

Le principe utilisé ici est de générer les regroupements de taille 1 et de s'en servir pour générer ceux de taille 2 puis ceux de taille 3, et ainsi de suite.

Posons $p$ le nombre de points de pompage ( $p = n-1$ ).

#### Initialisation
La première étape consiste simplement à générer les tournées ne contenant qu'un seul point de pompage.
On se retrouve donc avec $p$ vecteurs de taille 1.


#### Hérédité
##### Genération
On remarque que les regroupements de taille $t$ sont des préfixes des regroupements de taille $t+1$.
On se sert de cette propriété pour construire l'ensemble des regroupements.

Soit $r$ un regroupement de taille $t$.
On construit $S_r$, l'ensemble des regroupements de taille $t+1$ et de préfixe $r$ comme suit :

$S_r \leftarrow \{\}$
$$\forall\space i\space \in\space [\space max(r)+1,\space ...,\space p \space],\space S_r\space \leftarrow\space S_r\space \cup\space \{\space r\space \cup\space \{i\}\}$$

On applique ce procédé à tous les regroupements de taille $t$ pour construire tous les regroupements de tailles $t+1$.
On peut ainsi construire tous les regroupements de taille allant de $1$ à $n$ à partir des regroupements de taille $1$.

##### Filtrage
On remarque que cet algorithme génère tous les regroupements, même ceux non réalisables.
On peut résoudre ce problème en testant si l'instance est réalisable avant de l'ajouter à la solution partielle.
L'avantage de cette approche est que les regroupements ayant un préfixe non réalisable ne sont pas envisagés, économisant ainsi du temps de calcul.

Soit $r$ un regroupement de taille $t$.
On construit $R_r$, l'ensemble des regroupements réalisables de taille $t+1$ et de préfixe $r$ comme suit :

$S_r \leftarrow \{\}$
$$\forall\space i\space \in\space [\space max(r)+1,\space ...,\space p \space ],\space S_r\space \leftarrow\space \begin{cases} S_r\space \cup\space \{r\space \cup\space \{i\}\} \space si \space (\sum_{j \in r} d_j)  + d_i \leq Ca \\ S_r \space sinon \end{cases}$$

### Calcul du plus court chemin
La méthode utilisée pour calculer le plus court chemin d'un regroupement donné consiste simplement à parcourir toutes les permutations et calculer pour chacune la distance parcourue.

## Explication des classes utilisées
### regroupement

Cette classe représente un ensemble de points de pompage.

#### Atributs
| Attribut  | Type              | Description                              |
| --------- | ----------------- | ---------------------------------------- |
| lieux_    | vecteur d'entiers | indice des points de pompage du regroupement  |
| quantite_ | entier signé      | quantité d'eau du regroupement |
| distance_ | entier signé      | distance du plus cours chemin passant par tous les points de pompage |

#### Méthodes
``` void add(unsigned int point, unsigned int quantité) ``` :
Ajoute le point de pompage d'indice *point* et de quantité *quantite* dans le regroupement.

### donnees
Cette classe permet de lire les données présentes dans le dossier *data*.
Son constructeur et son destructeur reprennent respectivement le code des fonctions *lecture_data* et *free_data*.

#### Attributs
| Attribut  | Type              | Description                   |
| --------- | ----------------- | ------------------------------|
| nblieux_  | entier            | nombre de lieux               |
| capacite_ | entier            | capacité du drone             |
| demande_  | tableau d'entiers | capacité des lieux de pompage |
| C_        | matrice d'entiers | distancier                    |

#### Méthodes
``` std::vecteur<regroupements> generer_regroupements() const ``` :
Construit tous les regroupements réalisables, sans calculer le plus court chemin.

``` unsigned int distance( std::vector<unsigned int> lieux ) const ``` :
Calcule la distance du parcours dans l'ordre de *lieux*, en commençant et en terminant par le point 0.

``` void init_distance(regroupement& rgrp) const ```
Initialise l'attribut distance_ et réordonne les lieux_ de *rgrp* selon le plus court chemin.

### probleme
Cette classe représente l'instance du problème à résoudre.

#### Attributs
| Attribut                 | Type                             | Description                              |
| ------------------------ | -------------------------------- | ---------------------------------------- |
| regroupements_           | vecteur de regroupements         | ensemble des regroupements réalisables |
| regroupements_contenant_ | vecteur de vecteur d'entiers     | regroupements[i] = indice des regroupements contenant le point de pompage i |

#### Méthodes
``` void init_regroupements_contenant() ``` :
Parcours chaque regroupement et ajoute son indice $i$ à regroupements_contenant_$[j] , \forall j \in regroupements\_[i]$.

### chrono
Cette classe reprends le code et les fonctionnalités des fonctions *chrono_start*, *chrono_stop* et *chrono_ms*, en ajoutant cependant la possibilité d'obtenir le temps directement en secondes, grâce à la méthode *to_sec*. Elle nous permet donc de déterminer le temps de calcul des étapes cruciales de la résolution du problème.

### glpkwrapper
Cette classe est utilisée pour résoudre le problème de partitionnement.

#### Méthodes

``` void construit_couts() ``` :
Initialise les couts de chaque tournée à la valeur du plus court chemin du regroupement représentant cette tournée.

``` void construit_taille_contr() ``` :
Initialise les paramètres de la matrice creuse.

``` void def_probleme() ``` :


- Definition des variables de decision

  On defiinit les variables de decision comme les variables entiers en utilisant du mots-clés *GLP_DB* et puis on prcecise que ces sont des variables binaires en utilisant mots-clés *GLP_BV*. Puis en utilisant la fonction de *glpk*, *glp_set_obj_coef*, on attribut les couts *couts* à chaque variable de decision.

- Définition des coefficients non-nuls dans la matrice des contraintes :

  Les coefficients de la matrice creuse. Pour faire cela dans la procedure on possede trois tableaux dynamiques d'entiers:  *ia,ja,ar*.  Initialisés au nombre de creux(nb_creux_) de la matrice creux :

  - *nb_creux_* : le nombre de  variable present dans chaque contrainte. Cette infrormation est  stocké dans la classe *problème* dans l'attribut de type *vector* : *regroupement_contenant* 

  - *ia* :  numero de contrainte

  - *ja* : les indices des variables de decision stockés dans  le vecteur *regroupement_contenant* de chaque contrainte *i*

  - *ar* : les couts  de chaque variable present dans la contrainte *i*, dans notre probleme les coûts de nos variable de decision sont égale à 1.

  Puis on definit les contraintes en glpk en definissant la borne des contraintes comme fixe et la partie droite des contraintes à la valeur de attribut *droite_* de la classe *glpkwrapper*. Puis avec la procedure *glp_load_matrix* de *glpk* on charge *nb_creux_,ia,ja,ar*.

### Autres Classes
#### En-tête *Container-overload*
Cet en-tête nous permet de surcharger l'opérateur *<<* pour faciliter l'affichage sur l'ecran.

#### Implémentation des algorithmes en c++
##### Génération des sous-ensembles
###### Initialisation
```c++
std::vector<regroupement> regroupements;
for(unsigned int i = 1; i < nblieux_; ++i)//on parcours tous les points de pompage
    if(capacite_ >= demande_[i])//on teste quand même la capacité
    {
        regroupements.emplace_back( std::vector<unsigned int>{i}, demande_[i]);
        init_distance(regroupements.back());
    }
```

###### Hérédité
```c++
unsigned int start = 0;
unsigned int stop = regroupements.size();

for(unsigned int stage = 2; stage < nblieux_; ++stage)
{//génération des sous-ensembles de taille stage
    for(; start < stop; ++start)
    {//parcours de chacun des points de taille stage-1
        for(unsigned int i = regroupements[start].dernier_point() + 1; i < nblieux_; ++i)
        {//création des regroupements de préfixe regroupements[start]
            if(regroupements[start].quantite() + demande_[i] <= capacite_)
            {//filtrage. seuls les regroupements réalisables sont ajoutés
                regroupements.push_back( regroupements[start] );
                //le nouveau regroupement est une copie de regroupements[start] ...
                regroupements.back().add(i, demande_[i]);
                // ... auquel on ajoute le point i et la quantité d'eau correspondante
                init_distance(regroupements.back());
                //on calcule le chemin le plus court du regroupement créé
            }
        }
    }

    start = stop;
    stop = regroupements.size();
}
```

La fonction init_distance servant calculer le chemin le plus court d'un regroupement sera expliquée dans la section suivante.

### Calcul du plus court chemin
Comme expliqué dans la section *Description des algorithmes*, la méthode de calcul de plus court chemin consiste simplement à parcourir tous les chemins possibles et conserver le plus court.
Pour cela, nous avons utilisé la fonction std::next_permutation permettant de parcourir une à une les permutations d'un conteneur de la bibliothèque standard.

## Compilation
Pour compiler notre projet, il suffit de suvre les etapes suivantes:

- il faut se placer dans le dossier build  en utilisant la commande

  ```bash
  cd build
  ```

- Ensuite il faut taper la commande suivante:

  ```bash
  cmake ..
  ```

- Puis

  ```bash
  make 
  ```

- A cet etape, il faut chosir pour qu'elle donne on veut calculer lancer notre programeme:

  - Pour l'exemple du projet

    ````bash
    ./ro_test data/exemple.dat
    ````

  - Pour les données du dossier **A**

    ````bash
    ./ro_test data/A/nom_du_fichier.dat
    ````

  - Pour les données du dossier **B**

    ```bash
    ./ro_test data/B/nom_du_fichier.dat
    ```
## Conclusion
