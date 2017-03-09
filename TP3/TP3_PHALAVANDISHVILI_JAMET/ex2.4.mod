# TP 3 - PHALAVANDISHVILI Demetre - JAMET Félix - Gr 601B
#Declaration des données du probleme

	param nbPers;
	set indPers := 1..nbPers;

	param nbMachine;
	set indMachine := 1..nbMachine;

	set Scout within indPers cross indMachine;

	param MatriceCout{(i,j) in Scout};

	param mdroite{indPers};

#Declaration
	var x{Scout} binary;

#Fonction objectif
	maximize affectaton : sum{(i,j) in Scout} MatriceCout[i,j]*x[i,j];

# Contrainte 
	s.t. PersMachine{i in  indPers} : sum{(i,j) in Scout} x[i,j] = mdroite[i];
	s.t. MachinePers{j in indMachine} : sum{(i,j) in Scout} x[i,j] = mdroite[j];

#Resolution
	solve;

#affichage
	display : affectaton;
	display : x;

data;
	param nbPers := 6;

	param nbMachine := 6;

	set Scout := (1,1)(1,2)(1,3)(1,4)(1,5)(1,6)
				 (2,1)(2,2)(2,3)(2,4)(2,5)(2,6)
				 (3,1)(3,2)(3,3)(3,4)(3,5)(3,6)
				 (4,1)(4,2)(4,3)(4,4)(4,5)(4,6)
				 (5,1)(5,2)(5,3)(5,4)(5,5)(5,6)
				 (6,1)(6,2)(6,3)(6,4)(6,5)(6,6);

	param MatriceCout := 
		[1,1] 13 [1,2] 24 [1,3] 31 [1,4] 19 [1,5] 40 [1,6] 29
		[2,1] 18 [2,2] 25 [2,3] 30 [2,4] 15 [2,5] 43 [2,6] 22
		[3,1] 20 [3,2] 20 [3,3] 27 [3,4] 25 [3,5] 34 [3,6] 33
		[4,1] 23 [4,2] 26 [4,3] 28 [4,4] 18 [4,5] 37 [4,6] 30
		[5,1] 28 [5,2] 33 [5,3] 34 [5,4] 17 [5,5] 38 [5,6] 20
		[6,1] 19 [6,2] 36 [6,3] 25 [6,4] 27 [6,5] 45 [6,6] 24;

	param mdroite default 1;