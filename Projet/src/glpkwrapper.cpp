#include "glpkwrapper.h"

glpkwrapper::glpkwrapper(unsigned int nbContr, const probleme & prob)
{
	nb_contr = nbContr; // nombre de contraintes depandant du nombre de point pompage
	nb_var = prob.regroupements().size(); // nombre de variable dependant de nombre de regroupement
	construit_couts(prob.regroupements());
	construit_taille_contr(prob); 
	droite_ = 1.0;

	trumpland = glp_create_prob()
    glp_set_prob_name(trumpland,"Probleme de trumpland");
    glp_set_obj_dir(prob,GLP_MIN);
}

void glpkwrapper::construit_couts(std::vector<regroupement> combinaison)
{
	for (int i = 0; i < combinaison.size; ++i)
	{
		couts[i] = combinaison[i].distance();
	}
}

void glpkwrapper::construit_taille_contr(probleme prob)
{
	int pos = 0;
	for (int i =0; i < nbContr;++i) nb_creux += prob.regroupement_contenant()[i].size();
	ia = new int(1+nb_creux);
	ja = new int(1+nb_creux);
	ar = new double(1+nb_creux);
	for (int i = 0; i < nbContr; ++i)
	{		
		for (int j = 0; j < prob.regroupement_contenant()[i].size(); ++j)
		{
			ia[pos] = i+1:
			ja[pos] = prob.regroupement_contenant()[i][j];
			ar[pos] = droite_;
			++pos;
		}
	}
}

void glpkwrapper::def_probleme()
{
	// definit contrainte
	for (int i = 0; i < nb_contr; ++i)
	{
		
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(prob, i+1, GLP_FX, droite_, 0.0); 
	}

	glp_add_cols(trumpland,nb_var);

	for(i=1;i <= nb_var;i++)
	{
		/* partie obligatoire : bornes éventuelles sur les variables, et type */
		glp_set_col_bnds(trumpland, i, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
		glp_set_col_kind(trumpland, i, GLP_BV);	/* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */	
	} 

	for(i = 1;i <= p.nbvar;i++) glp_set_obj_coef(trumpland,i,couts[i - 1]);  

	glp_load_matrix(prob,nbcreux,ia,ja,ar); 
}

void glpkwrapper::resoudre_probleme()
{
	def_probleme();
	glp_simplex(trumpland,NULL);	
	glp_intopt(trumpland,NULL);
	double z = glp_mip_obj_val(trumpland);
	cout << "Z = " << z << "\n";
}