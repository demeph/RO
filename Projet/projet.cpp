/* NOM1 Prénom1
   NOM2 Prénom2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glpk.h> /* Nous allons utiliser la bibliothèque de fonctions de GLPK */

#include <iostream>
#include <vector>
#include <array>
#include <cmath>

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h> /* Bibliothèques utilisées pour mesurer le temps CPU */

/* structures et fonctions de mesure du temps CPU */

struct timeval start_utime, stop_utime;

void crono_start()
{
	struct rusage rusage;
	
	getrusage(RUSAGE_SELF, &rusage);
	start_utime = rusage.ru_utime;
}

void crono_stop()
{
	struct rusage rusage;
	
	getrusage(RUSAGE_SELF, &rusage);
	stop_utime = rusage.ru_utime;
}

double crono_ms()
{
	return (stop_utime.tv_sec - start_utime.tv_sec) * 1000 +
    (stop_utime.tv_usec - start_utime.tv_usec) / 1000 ;
}

/* Structure contenant les données du problème */

typedef struct {
	int nblieux; /* Nombre de lieux (incluant le dépôt) */
	int capacite; /* Capacité du véhicule de livraison */
	int *demande; /* Demande de chaque lieu (la case 0 est inutilisée car le dépôt n'a aucune demande à voir satisfaire) */
	int **C; /* distancier (les lignes et colonnes 0 correspondent au dépôt) */
} donnees;


struct regroupLong {
	std::vector<int> regroupe;
	int longuerTour;
};

void copie(std::vector<int> & v,std::vector<int> & v1)
{
	for (int i = 0; i < v1.size();++i)
	{
		v.push_back(v1[i]);
	}
}

void genereSSensemble(std::vector<regroupLong> & liste,donnees *p)
{
	int N = (p->nblieux)-1;
	int nbElt = pow(2,N)-1; 
	int nbEltSaisie = 0;
	for (int i = 0; i < N; ++i)
	{
		liste.push_back(regroupLong());
		liste.back().regroupe.push_back(i+1);
		++nbEltSaisie;
	}
	int k = 0;
	while ( nbEltSaisie < nbElt )
	{
		int p = liste[k].regroupe[liste[k].regroupe.size()-1];
		for (int i = p; i <= N;++i)
		{
			for (int j = i+1; j <= N; ++j)
			{
				liste.push_back(regroupLong());
				copie(liste.back().regroupe,liste[k].regroupe);
				liste.back().regroupe.push_back(j);
				++nbEltSaisie;
			}
			++k;
		}
	}
}

std::vector<regroupLong> filterListe(std::vector<regroupLong> & liste,donnees *p)
{
	std::vector<regroupLong> l1;
	for (int i = 0; i < liste.size(); ++i)
	{
		int capacite = 0;
		for (int m = 0; m < liste[i].regroupe.size();++m) capacite += p->demande[liste[i].regroupe[m]];
		if (capacite <= p->capacite) 
		{
			l1.push_back(regroupLong());
			copie(l1.back().regroupe,liste[i].regroupe);
		}
	}
	return l1;
}



/* lecture des donnees */

void lecture_data(char *file, donnees *p)
{
	int i,j;
	FILE *fin;
	
	int val;
	fin = fopen(file,"rt");
	
	/* Lecture du nombre de villes */
	
	fscanf(fin,"%d",&val);
	p->nblieux = val;

	/* Allocation mémoire pour la demande de chaque ville, et le distancier */
	
	p->demande = (int *) malloc (val * sizeof(int));
	p->C = (int **) malloc (val * sizeof(int *));
	for(i = 0;i < val;i++) p->C[i] = (int *) malloc (val * sizeof(int));
	
	/* Lecture de la capacité */
	
	fscanf(fin,"%d",&val);
	p->capacite = val;
	
	/* Lecture des demandes des clients */
	
	for(i = 1;i < p->nblieux;i++)
	{
		fscanf(fin,"%d",&val);
		p->demande[i] = val;
	}
	
	/* Lecture du distancier */

	for(i = 0; i < p->nblieux; i++)
		for(j = 0; j < p->nblieux; j++)
		{
			fscanf(fin,"%d",&val);
			p->C[i][j] = val;
		}
		
	fclose(fin);
}

/* Fonction de libération mémoire des données */

void free_data(donnees *p)
{
	int i;
	for(i = 0;i < p->nblieux;i++) free(p->C[i]);
	free(p->C);
	free(p->demande);	
}


int main(int argc, char *argv[])
{	
	/* Déclarations des variables (à compléter) */

	donnees p; 
	double temps;
		
	/* Chargement des données à partir d'un fichier */
	
	lecture_data(argv[1],&p);
	
	/* Lancement de la résolution... */

	crono_start(); // .. et donc du chronomètre

	/* .... */












	/* ... */



	/* Problème résolu, arrêt du chrono */
	
	crono_stop();
	temps = crono_ms()/1000,0;
	
	/* Affichage des résultats (à compléter) */
	
	printf("Temps : %f\n",temps);	
	
	/* libération mémoire (à compléter en fonction des allocations) */

	free_data(&p);
	
	/* J'adore qu'un plan se déroule sans accroc! */
	return 0;
}
