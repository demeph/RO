/* PHALAVANDISHVILI Demetre - JAMET Félix - Groupe 601B*/
/* Exercice 1.4 question 1 modele implicite*/ 

#Declaration des variables utilisés

	# nombre de plage d'horaires
	param nbPlageHoraire; 
	
	#enseble de tranche horaire,pour réaliser le modele implicite, on commence la numérotation à 0 jusqu'a nbPlageHoraire-1
	set indPlage := 0..nbPlageHoraire; 
    
  	#coeff de membre droite des contraintes
	param nbInfirmiere{indPlage};

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

	s.t. contrainte{i in indPlage} : x[(i mod 12)] + x[((i-1) mod 12)] + x[((i-3) mod 12)] + x[((i-4) mod 12)] +s[(i-5)mod 12]>= nbInfirmiere[i];

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

	param nbPlageHoraire := 11;

	param nbInfirmiere := 0 35
						  1 40 
						  2 40 
						  3 35
						  4 30
						  5 30
						  6 35
						  7 30
						  8 20
						  9 15
						  10 15
						  11 15;

end;