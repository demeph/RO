## Ecriture de probleme en GLPK

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

