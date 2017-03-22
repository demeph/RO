### Génération des sous-ensembles

Il s'agit ici de générer les sous-ensembles des tournées réalisables, c'est à dire celles dont la quantité d'eau ne dépasse pas la capacité du drone. Le code expliqué par la suite correspond à la méthode *donnees::generer_probleme*.

Le principe utilisé ici est de générer les regroupements de taille 1 et de s'en servir pour générer ceux de taille 2 puis ceux de taille 3, et ainsi de suite.
Les regroupements de tailles n sont des préfixes des regroupements de taille n+1.
Pour créer le regroupement de taille n+1

1. Initialisation :
La première étape consiste simplement à générer les tournées ne contenant qu'un seul point de pompage.
Pour cela, nous avons créé une classe regroupement représentant un ensemble de points de pompage.

```c++
std::vector<regroupement> regroupements;
for(unsigned int i = 1; i < nblieux_; ++i)//on parcours tous les points de pompage
    if(capacite_ >= demande_[i])//on teste quand même la capacité
    {
        regroupements.emplace_back( std::vector<unsigned int>{i}, demande_[i]);
        init_distance(regroupements.back());
    }
```

La fonction init_distance sera expliquée plus tard.

2. boucle principale
Le 
