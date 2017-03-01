/* PHALAVANDISHVILI Demetre - JAMET Félix - Groupe 601B */

#Declaration des données du problème

	param mille;
	param nbEntrepot;
	set indEntrepot := 1..nbEntrepot;

	param nbClient;
	set indClient := 1..nbClient;

	set Scout within indEntrepot cross indClient;

	param matriceCout{(i,j) in Scout}; #matrice des cout de la satistafaction

	param coutEntrepot{indEntrepot}; # ensemble contenant le cout de construction de chaque entrepot

	param capaciteEntrepot{indEntrepot}; # ensemble contenant de chaque entrepot

	param demandeClient{indClient}; # ensemble contenant de demande d un client

#Declaration d un tableau de variables binaires

	var y{indEntrepot} binary;
	var x{Scout} >= 0, <= 1;

# Fonction objectif

	minimize cout{i in indEntrepot} : coutEntrepot[i]*y[i] + sum{(i,j) in Scout} matriceCout[i,j]*x[i,j];

# Contraintes

	s.t. Contrainte{i in indEntrepot}:  sum{(i,j) in Scout} x[i,j] <= y[i];
	s.t. SatisfaireClient: sum{(i,j) in Scout}  x[i,j] = 1;
	s.t. TailleEntrepotLimite{(i,j) in Scout}: mille*demandeClient[j] * x[i,j] <= capaciteEntrepot[i]*mille;

#Resolution 
	solve;


#Affichage
	display : y;
	/*display : x;*/
	display : 'Z = ',sum{(i,j) in Scout} ( coutEntrepot[i]*y[i] +  matriceCout[i,j]*x[i,j]);

data;

	param nbEntrepot := 12;

	param nbClient := 12;

	param mille := 1000;

	set Scout :=  (1,1)(1,2)(1,3)(1,4)(1,5)(1,6)(1,7)(1,8)(1,9)(1,10)(1,11)(1,12)
					(2,1)(2,2)(2,3)(2,4)(2,5)(2,6)(2,7)(2,8)(2,9)(2,10)(2,11)(2,12)
					(3,1)(3,2)(3,3)(3,4)(3,5)(3,6)(3,7)(3,8)(3,9)(3,10)(3,11)(3,12)
					(4,1)(4,2)(4,3)(4,4)(4,5)(4,6)(4,7)(4,8)(4,9)
					(5,1)(5,2)(5,3)(5,7)(5,8)(5,9)
					(6,1)(6,2)(6,3)(6,7)(6,8)(6,9)(6,10)(6,11)(6,12)
					(7,1)(7,2)(7,3)(7,4)(7,5)(7,6)(7,7)(7,8)(7,9)(7,10)(7,11)(7,12)
					(8,1)(8,2)(8,3)(8,4)(8,5)(8,6)(8,7)(8,8)(8,9)(8,10)(8,11)(8,12)
					(9,1)(9,2)(9,3)(9,4)(9,5)(9,6)(9,7)(9,8)(9,9)(9,10)(9,11)(9,12)
					(10,1)(10,2)(10,3)(10,4)(10,5)(10,6)(10,7)(10,8)(10,9)
					(11,1)(11,2)(11,3)(11,7)(11,8)(11,9)
					(12,1)(12,2)(12,3)(12,7)(12,8)(12,9)(12,10)(12,11)(12,12);



	param matriceCout := 
					[1,1] 100 [1,2] 80 [1,3] 50 [1,4] 50 [1,5] 60 [1,6] 100 [1,7] 120 [1,8] 90 [1,9] 60 [1,10] 70 [1,11] 65 [1,12] 110
					[2,1] 120 [2,2] 90 [2,3] 60 [2,4] 70 [2,5] 65 [2,6] 110 [2,7] 140 [2,8] 110 [2,9] 80 [2,10] 80 [2,11] 75 [2,12] 130
					[3,1] 140 [3,2] 110 [3,3] 80 [3,4] 80 [3,5] 75 [3,6] 130 [3,7] 160 [3,8] 125 [3,9] 100 [3,10] 100 [3,11] 80 [3,12] 150
					[4,1] 160 [4,2] 125 [4,3] 100 [4,4] 100 [4,5] 80 [4,6] 150 [4,7] 190 [4,8] 150 [4,9] 130
					[5,1] 190 [5,2] 150 [5,3] 130 [5,7] 200 [5,8] 180 [5,9] 150
					[6,1] 200 [6,2] 180 [6,3] 150 [6,7] 100 [6,8] 80 [6,9] 50 [6,10] 50 [6,11] 60 [6,12] 100
					[7,1] 100 [7,2] 80 [7,3] 50 [7,4] 50 [7,5] 60 [7,6] 100 [7,7] 120 [7,8] 90 [7,9] 60 [7,10] 70 [7,11] 65 [7,12] 110
					[8,1] 120 [8,2] 90 [8,3] 60 [8,4] 70 [8,5] 65 [8,6] 110 [8,7] 140 [8,8] 110 [8,9] 80 [8,10] 80 [8,11] 75 [8,12] 130
					[9,1] 140 [9,2] 110 [9,3] 80 [9,4] 80 [9,5] 75 [9,6] 130 [9,7] 160 [9,8] 125 [9,9] 100 [9,10] 100 [9,11] 80 [9,12] 150
					[10,1] 160 [10,2] 125 [10,3] 100 [10,4] 100 [10,5] 80 [10,6] 150 [10,7] 190 [10,8] 150 [10,9] 130
					[11,1] 190 [11,2] 150 [11,3] 130 [11,7] 200 [11,8] 180 [11,9] 150
					[12,1] 200 [12,2] 180 [12,3] 150 [12,7] 100 [12,8] 80 [12,9] 50 [12,10] 50 [12,11] 60 [12,12] 100;

	param coutEntrepot := 1 3500 2 9000 3 10000 4 4000 5 3000 6 9000 7 9000 8 3000 9 4000 10 10000 11 9000 12 3500;

	param capaciteEntrepot := 1 300 2 250 3 100 4 180 5 275 6 300 7 200 8 220 9 270 10 250 11 230 12 180;

	param demandeClient := 1 120 2 80 3 75 4 100 5 110 6 100 7 90 8 60 9 30 10 150 11 95 12 120;


end;