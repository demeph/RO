### Génération des sous-ensembles

Il s'agit ici de générer les sous-ensembles des tournées réalisables, c'est à dire celles dont la quantité d'eau ne dépasse pas la capacité du drone. Le code expliqué par la suite correspond à la méthode *donnees::generer_probleme*.


#### Explication de l'algorithme

On utilise les notations suivantes, extraites du sujet :
$n \in \mathbb{N}$, le nombre de lieux
$d_i$, la quantité d'eau disponible au point $i$, avec $i \in \{1, ..., n\}$
$Ca \in \mathbb{N}$, la capacité du drone


Le principe utilisé ici est de générer les regroupements de taille 1 et de s'en servir pour générer ceux de taille 2 puis ceux de taille 3, et ainsi de suite.

On pose $p$ le nombre de points de pompage.


1. Initialisation :
La première étape consiste simplement à générer les tournées ne contenant qu'un seul point de pompage.
On se retrouve donc avec $p$ vecteurs de taille 1.


2. boucle principale
   1. genération
On remarque que les regroupements de tailles t sont des préfixes des regroupements de taille t+1.
On se sert de cette propriété pour construire inductivement l'ensemble des regroupements.
Soit $r$ un regroupement de taille t.

On construit $S_r$, l'ensemble des regroupements de taille $t+1$ et de préfixe $r$
    $S_r \leftarrow \{\}$
    $$
        \forall\space i\space \in\space [max(r)+1,\space ...,\space p],\space S_r\space \leftarrow\space S_r\space \cup\space \{\space r\space \cup\space \{i\}\}
    $$
    
On applique ce procédé à tous les regroupements de taille $t$ pour construire tous les regroupements de tailles $t+1$.

On peut ainsi construire tous les regroupements nous intéressant à partir des regroupements de taille 1.
    2. filtrage
On remarque que cet algorithme génère tous les regroupements, même ceux comportant une trop grande quantité d'eau.
On peut résoudre ce problème en testant si la quantité d'eau de la tournée dépasse la capacité du drone avant d'ajouter l'instance à la solution partielle.
L'avantage de cette approche est que les solutions correspondant à une trop grande quantité d'eau ne sont pas envisagées, économisant ainsi du temps de calcul.

    $S_r \leftarrow \{\}$
    $$
        \forall\space i\space \in\space [max(r)+1,\space ...,\space p],\space S_r\space \leftarrow\space
        \begin{cases} S_r\space \cup\space \{\space r\space \cup\space \{i\}\} si \sum {j \in r} d_j  + d_i \leq Ca
        \\ S_r sinon
    $$
    
#### Implantation en c++

1. Initialisation

```c++
std::vector<regroupement> regroupements;
for(unsigned int i = 1; i < nblieux_; ++i)//on parcours tous les points de pompage
    if(capacite_ >= demande_[i])//on teste quand même la capacité
    {
        regroupements.emplace_back( std::vector<unsigned int>{i}, demande_[i]);
        init_distance(regroupements.back());
    }
```

2. Boucle principale

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
            {//filtrage. seuls les regroupements dont la quantité d'eau est transportable sont ajoutés
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
