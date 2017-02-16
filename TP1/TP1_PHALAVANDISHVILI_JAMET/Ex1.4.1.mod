/* PHALAVANDISHVILI Demetre - JAMET Félix - Groupe 601B*/
/* Exercice 1.4 question 1 modele implicite*/ 

#Declaration des variables utilisés

	# nombre de plage d'horaires
	param nbPlageHoraire; 
	
	#enseble de tranche horaire,pour réaliser le modele implicite, on commence la numérotation à 0 jusqu'a nbPlageHoraire-1
	set indPlage := 0..nbPlageHoraire; 
   
  	# coeff de membre droite des contraintes
	param nbInfirmiere{indPlage};

#Declaration de variables non-negatives sous la forme d'un tableau de variables indicées sur le nombre infirmiere qui commencent leur service à la tranche d'horaire

	var x{indPlage} >= 0 integer;

#Fonction objectif

	minimize profit : sum{i in indPlage} x[i];

#contraintes

	s.t. contrainte{i in indPlage} : x[(i mod 12)] + x[((i-1) mod 12)] + x[((i-3) mod 12)] + x[((i-4) mod 12)] >= nbInfirmiere[i];

#Resolution
	solve;

#Affichage 
	display : x; #Affichage des variables de decision
	display : 'Z= ',sum{i in  indPlage} x[i]; #affichage de nombre oprimale des infirmieres

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