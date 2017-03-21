#include "glpkwrapper.h"

glpkwrapper::glpkwrapper(unsigned int nbContr, const probleme & prob):
    nb_contr_(nbContr-1),
    nb_var_(prob.regroupements().size()),
    droite_(1.0),
    nb_creux_(0)
{
    couts = new int[nb_var_+1];
	construit_couts(prob.regroupements());
	construit_taille_contr(prob); 

	trumpland = glp_create_prob();
    glp_set_prob_name(trumpland,"Probleme de trumpland");
    glp_set_obj_dir(trumpland,GLP_MIN);
    
}

glpkwrapper::~glpkwrapper()
{
    delete[] ia;
    delete[] ja;
    delete[] ar;
    delete[] couts;
}

void glpkwrapper::construit_couts(const std::vector<regroupement> & combinaison)
{
	for (unsigned int i = 0; i < combinaison.size(); ++i)
	{
		couts[i] = combinaison[i].distance();
	}
}

void glpkwrapper::construit_taille_contr(probleme prob)
{
	int pos = 1;
	for (unsigned int i =0; i < nb_contr_;++i) nb_creux_ += prob.regroupements_contenant()[i].size();
	ia = new int[1+nb_creux_];
	ja = new int[1+nb_creux_];
	ar = new double[1+nb_creux_];
	for (unsigned int i = 0; i < nb_contr_; ++i)
	{		
		for (unsigned int j = 0; j < prob.regroupements_contenant()[i].size(); ++j)
		{
			ia[pos] = i+1;
			ja[pos] = prob.regroupements_contenant()[i][j];
			ar[pos] = droite_;
			++pos;
		}
	}
}

void glpkwrapper::def_probleme()
{
	// definit contrainte
    glp_add_rows(trumpland, nb_contr_); 
	for (unsigned int i = 0; i < nb_contr_; ++i)
	{
		
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(trumpland, i+1, GLP_FX, droite_, 0.0); 
	}

	glp_add_cols(trumpland,nb_var_);

	for(unsigned i=1;i <= nb_var_;++i)
	{
		/* partie obligatoire : bornes éventuelles sur les variables, et type */
		glp_set_col_bnds(trumpland, i, GLP_DB, 0.0, 1.0); /* bornes sur les variables, comme sur les contraintes */
		glp_set_col_kind(trumpland, i, GLP_BV);	/* les variables sont par défaut continues, nous précisons ici qu'elles sont binaires avec la constante GLP_BV, on utiliserait GLP_IV pour des variables entières */	
	} 

	for(unsigned i = 1;i <= nb_var_;++i) glp_set_obj_coef(trumpland,i,couts[i - 1]);  

	glp_load_matrix(trumpland,nb_creux_,ia,ja,ar); 
}

void glpkwrapper::resoudre_probleme()
{
	def_probleme();
	glp_simplex(trumpland,NULL);	
    glp_write_lp(trumpland,NULL,"trumpland.lp");
	glp_intopt(trumpland,NULL);
	double z = glp_mip_obj_val(trumpland);
	std::cout << "Z = " << z << "\n";
}

std::ostream & operator<<(std::ostream& os, glpkwrapper const& wrp)
{
    os << "\t" << wrp.nb_contr() << " contraintes\n\t"
       << wrp.nb_var() << " variables\n\t"
       << wrp.nb_creux() << " creux";
    return os;
}
