/* Exercice 1.4 question 1 modele implicite*/ 

#Declaration des variables utilisés

	param nbPlageHoraire; # nombre de plage d'horaires
	set indPlage := 1..nbPlageHoraire; #enseble de tranche horaire

	param nbInfirmParPlage;
	set indiceParPlage := 1..nbInfirmParPlage;

	param nbColonne;
	set indColonne := 1..nbColonne;
    
	param nbInfirmiere{indiceParPlage}; # coeff de membre droite des contraintes
	param matriceIndice{indiceParPlage,indColonne}; 

#Declaration de variables non-negatives sous la forme
#d'un tableau de variables indicées sur le nombre infirmiere qui commencent leur service à la tranche d'horaire

	var x{indPlage} >= 0;

#Fonction objectif

	minimize profit : sum{i in indPlage} x[i];

#contraintes

	s.t. contrainte{i in indPlage} : sum{j in indColonne} x[matriceIndice[i,j]] >= nbInfirmiere[i];

#Resolution
	solve;

#Affichage 
	display : x; #Affichage des variables de decision
	#display : 'Z=',sum{i in  indiceParPlage} x[i]; #affichage de la valeur optimale

data;

	param nbPlageHoraire := 12;

	param nbInfirmParPlage := 12;

	param nbColonne := 4;

	param nbInfirmiere := 1 35
						  2 40 
						  3 40 
						  4 35
						  5 30
						  6 30
						  7 35
						  8 30
						  9 20
						  10 15
						  11 15
						  12 15;

	param matriceIndice : 1 2 3 4 := 1 1 12 10 9
								   2 2 1  11 10
								   3 3 2  12 11
								   4 4 3  12  1
								   5 5 4  2   1
								   6 6 5  3   2
								   7 7 6  4   3
								   8 8 7  5   4
								   9 9 8  6   5
								   10 10 9 7 6
								   11 11 10 8 7
								   12 12 11 9 8;
end;