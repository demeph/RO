#Decaration des données du problème
	
	param nbVar;
	set indVar := 1..nbVar; #ensemble qui contient les indices des variables

	param nbContr;
	set indContr := 1..nbContr;

	set indCol;

	param coeff{indVar};
	param mdroite{indContr};

	param matriceContr{indContr,indCol};

#Decaration du variable de decision 

	var x{indVar} binary;

#fonction objectif

	maximize z : sum{i in indVar} coeff[i]*x[i];

#Contrainte
	
	s.t. contrainte{i in indContr} : sum{j in indCol}  x[matriceContr[i,j]] <= mdroite[i];

#Resolution
	solve;

	display : x;
	display : sum{i in indVar} coeff[i]*x[i];

data;

	param nbVar := 9;

	param nbContr := 11;

	set indCol := 1 2;

	param mdroite default 1;

	param coeff := 1 1 2 3 3 7 4 3 5 12 6 4 7 9 8 4 9 3;

	param matriceContr : 1 2 := 
					   1 1 5
					   2 2 5
					   3 3 5
					   4 3 4
					   5 2 7
					   6 5 7
					   7 5 4
					   8 6 7
					   9 6 8
					  10 8 4
					  11 5 9;
end;						  