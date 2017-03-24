## Ecriture de probleme en GLPK

## Programme Linéaire

Posons tout d'abord cette problème sous la forme d'un  probleme linaire:

#### variables de  decison


$$
x_i = \begin{cases}  1\space si\space on\space choisit\space le\space trajer , \space i,  \\ 0 \space sinon, \end{cases}
$$

#### fonction objectif

Minimiser la distance parcourue par la drone 
$$
\sum_{i = 1}^{nbVariable}  l_i *x_i
$$

- où nbVariable = le nombre de trajet qui depassent pas la capacité du drone
- où $l_i$ :  la longeueur de la plus courte tournée
- exemple sur nombre de lieux égale à 5
  ​

$$
\sum_{i=1}^{27} l_i*x_i
$$

#### Contraintes

- Le lieu de pompage i doit etre visiter un et une seul fois, c'est-à-dire on doit avoir le nombre de regroupement dans laquelle apparait lieu de pompage i :

  ​
  $$
  \sum_ {i =1}^{nbRegroupement} x_i = 1
  $$

- contrainte sur l'exemple nombre de lieux égale à 5, pour le point de pompage 1 :
  $$
  \sum_{i=1}^{13} x_i = 1
  $$

- contraint d'ntegrité :
  $ x_i \in \{0,1\}\space \forall i \in [1,nbVariable]$  


Dans notre programme lineaire, on possede les paramètres qu'on ne connait pas  la valeur au debut. Ces sont  nbVariable*, *nbRegroupemet* : 

- Pour calculer *nbVariable* , nous avons besoin degenerer tous les ss-ensembles en fonction de nombre de lieux de pompage(privé de 0) en utilisant l'algorithme de la section *Explication de l'algorithme*. 
- La valeur nbRegroupement est donnée par le nombre de lieux de pompage(prive de 0).

## Programme Linéaire sous GLPK

​	Dans la classe *glpKWrapper*, on initialise le problème avec son nom et definit qu'il s'agit un probleme de minisation. 

- couts des variables des decision :

  Pour definir les couts *couts* des variables decisions on utilise vecteur qui contient le plus court chemin pour chaque regroupement qui se trouve dans la classe *probleme*. Voici la procedure *construit_couts* de la classe *glpkwrapper* :

- Définition des coefficients non-nuls dans la matrice des contraintes :

  Les coefficients de la matrice creuse. Pour faire cela, on possede trois tableaux dynamiques *ia,ja,ar*  de taille nombre de creux(nb_creuxç=_) de la matrice creux:

  - nb_creux_ : le nombre de  variable present dans chaque contrainte. Cette infrormation est  stocké dans la classe *problème* dans l'attribut ** 
  - ia :  numero de contrainte 
  - ja : les indices des variables present dans la contrainte *i*
  - ar : les couts  de chaque variable present dans la conteinte *i*

  ​

  ​	