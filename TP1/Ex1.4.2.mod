/* Exercice 1.4 question 1 modele implicite*/ 

#Declaration des variables utilisés

	# nombre de plage d'horaires
	param nbPlageHoraire; 
	
	#enseble de tranche horaire
	set indPlage := 1..nbPlageHoraire; 

	#nombre des indices necessaire pour calculer nombre minimale des infirmieres dans chaque plage d'horaire
	param nbColonne; 

	set indColonne := 1..nbColonne;
    
  	#coeff de membre droite des contraintes
	param nbInfirmiere{indPlage};

	#matrice contenant les indices de chaque plage horaire pour chaque contrainte
	param matriceIndice{indPlage,indColonne}; 

	#Des indices correspondant au plage d'horaire effectuant heure supplémentaire
	param heuresSup{indPlage};

#Declaration de variables non-negatives sous la forme
#d'un tableau de variables indicées sur le nombre infirmiere qui commencent leur service à la tranche d'horaire

	var s{indPlage} >= 0 integer;

	var x{indPlage} >= 0 integer;

#Fonction objectif

	# l'objectif ici c'est de minimiser nombre des infirmieres qui font les heures supplémentaires
	minimize profit : sum{i in indPlage} s[i];

#contraintes

	s.t. contrainte{i in indPlage} : sum{j in indColonne} x[matriceIndice[i,j]]+s[i] >= nbInfirmiere[i];

		#contrainte sur le nombre total des infirmieres
		nombreTotalInfirmiere : sum{i in indPlage} x[i] <= 80;

		#Cette contraint signifie qu'on peut pas avoir plus des infirmieres qui font heures supplémentaire que les infirmieres au total
		contrainteSurNbSup{i in indPlage} : s[i] <= x[i];

#Resolution
	solve;

#Affichage 
	display : x; #Affichage des variables de decision
	display : s; #Affichage des variables de decision
	display : 'Z= ',sum{i in  indPlage} x[i]; #affichage de nombre optimale des infirmieres
	display : 'Z= ',sum{i in  indPlage} s[i]; #affichage de nombre optimale des infirmieres

data;

	param nbPlageHoraire := 12;

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
	param heuresSup := 1 8
					   2 9
					   3 10
					   4 11
					   5 12
					   6 1
					   7 2
					   8 3
					   9 4
					   10 5
					   11 6
					   12 7;

end;