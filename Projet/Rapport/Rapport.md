# Projet RO  : BladeFlyer II - conquest of water

[TOC]


## Modélisation sous forme de programme linéaire

Posons tout d'abord ce problème sous la forme d'un programme linaire :
### Rappel des notations du sujet
- $n \in \mathbb{N}$, le nombre de lieux
- $d_i$, la quantité d'eau disponible au point $i$, avec $i \in \{1, ..., n\}$
- $Ca \in \mathbb{N}$, la capacité du drone

### Définition
Un regroupement r est dit *réalisable* si $\sum_{i \in r} d_i \leq Ca$

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
  ​
  $$
  \sum_ {i =1}^{nbRegroupement} x_i = 1
  $$

- contrainte sur l'exemple du sujet, pour le point de pompage 1 :
  $$
  \sum_{i=1}^{13} x_i = 1
  $$

- contraint d'ntegrité :
  $ x_i \in \{0,1\},\space \forall i \in [1,nbVariable]$

Dans notre programme lineaire, on possede les paramètres qu'on ne connait pas  la valeur au debut. Ces sont  nbVariable*, *nbRegroupemet* : 

- Pour calculer *nbVariable* , nous avons besoin degenerer tous les ss-ensembles en fonction de nombre de lieux de pompage(privé de 0) en utilisant l'algorithme de la section *Explication de l'algorithme*. 
- La valeur nbRegroupement est donnée par le nombre de lieux de pompage(prive de 0).


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
je me chargerais d'expliquer ça

## Explication des classes utilisées

### classe *donnees*

La classe permettant de lire les données present dans le dossier *data*. Cette classe possede plusieurs attributs en privé : 

| Attribut  | Type             | Description                           |
| --------- | ---------------- | ------------------------------------- |
| nblieux_  | entier           | nombre de lieu de pompage             |
| capacite_ | entier           | capacite de la drone                  |
| demenade_ | tableau d'entier | capacité de chaque lieu de pompage    |
| C_        | matrice i,j      | distancier entre les lieux de pompage |

Les methodes present dans cette classe :

### Classe *glpkwrapper*

​	Dans la classe *glpkwrapper*, on initialise le problème avec son nom et definit qu'il s'agit un probleme de minisation. 

- Couts des variables des decision :

  Pour definir les couts *couts* des variables decisions on utilise vecteur qui contient le plus court chemin pour chaque regroupement qui se trouve dans la classe *probleme*. Voir la procedure *construit_couts* de la classe *glpkwrapper*.

- Definition des variables de decision

  On defiinit les variables de decision comme les variables entiers en utilisant du mots-clés *GLP_DB* et puis on prcecise que ces sont des variables binaires en utilisant mots-clés *GLP_BV*. Puis en utilisant la fonction de *glpk*, *glp_set_obj_coef*, on attribut les couts *couts* à chaque variable de decision.

- Définition des coefficients non-nuls dans la matrice des contraintes :

  Les coefficients de la matrice creuse. Pour faire cela dans la procedure on possede trois tableaux dynamiques d'entiers:  *ia,ja,ar*.  Initialisés au nombre de creux(nb_creux_) de la matrice creux :

  - *nb_creux_* : le nombre de  variable present dans chaque contrainte. Cette infrormation est  stocké dans la classe *problème* dans l'attribut de type *vector* : *regroupement_contenant* 

  - *ia* :  numero de contrainte

  - *ja* : les indices des variables de decision stockés dans  le vecteur *regroupement_contenant* de chaque contrainte *i*

  - *ar* : les couts  de chaque variable present dans la contrainte *i*, dans notre probleme les coûts de nos variable de decision sont égale à 1.

  Puis on definit les contraintes en glpk en definissant la borne des contraintes comme fixe et la partie droite des contraintes à la valeur de attribut *droite_* de la classe *glpkwrapper*. Puis avec la procedure *glp_load_matrix* de *glpk* on charge *nb_creux_,ia,ja,ar*.


## Implémentation des algorithmes en c++

### Génération des sous-ensembles

#### Initialisation

```c++
std::vector<regroupement> regroupements;
for(unsigned int i = 1; i < nblieux_; ++i)//on parcours tous les points de pompage
    if(capacite_ >= demande_[i])//on teste quand même la capacité
    {
        regroupements.emplace_back( std::vector<unsigned int>{i}, demande_[i]);
        init_distance(regroupements.back());
    }
```

#### Hérédité

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

La fonction init_distance servant calculer le chemin le plus court d'un regroupement sera expliquée dans la section suivante

### Calcul du plus court chemin
je me chargerais d'expliquer






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

- A cet etape, il faut chosir pour qu'elle donne on veut calculer lancer notre programme:

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

    ​
