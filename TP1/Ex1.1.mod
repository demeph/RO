/* Exercice 1.1 du TD 1  modele implicite*/

#Declaration des variables utilisés

	param nbCasquette; # nombre de type de casquette
	set indCasquette := 1..nbCasquette; #ensemble des indices de type de casquette

	param nbAteliers; # nombre d'ateliers disponible
	set indAteliers := 1..nbAteliers; # ensemble des indices d'ateliers

	param profite{indCasquette}; # coeff de la fonctions objectif
	param dureeOp{indAteliers,indCasquette}; # coeff des membres de gauche des contraintes
	param heuresDispo{indAteliers}; # coeff des membres droites

#Declaration de variables non-negatives sous la forme
#d'un tableau de variables indicées sur les casquettes

	var x{indCasquette} >= 0;

#foonction objectif

	maximize profit : sum{j in  indCasquette} profite[j]*x[j];

#contraintes

	s.t. contrainte{i in indAteliers} : sum{j in indCasquette} dureeOp[i,j]*x[j] <= heuresDispo[i];

#Resolution
	solve;

#Affichage 
	display : x; #Affichage des variables de decision
	display : 'Z=',sum{j in  indCasquette} profite[j]*x[j]; #affichage de la valeur optimale

data;

	param nbCasquette := 2;

	param nbAteliers := 2;

	param profite := 1 12 2 20;

	param dureeOp : 1 2 :=
					1 0.2 0.4
					2 0.2 0.6;

	param heuresDispo := 1 400 2 800;

end;