#include "glpkwrapper.h"
#include "container_overload.h"

glpkwrapper::glpkwrapper(unsigned int nbContr, const probleme & prob):
    nb_contr_(nbContr-1),
    nb_var_(prob.regroupements().size()),
    droite_(1),
    nb_creux_(0),
    probleme_(prob)
{
    couts_ = new int[nb_var_+1];
	construit_couts();
	construit_taille_contr(); 

	trumpland = glp_create_prob();
    glp_set_prob_name(trumpland,"Probleme de trumpland");
    glp_set_obj_dir(trumpland,GLP_MIN);
}

glpkwrapper::~glpkwrapper()
{
    delete[] ia_;
    delete[] ja_;
    delete[] ar_;
    delete[] couts_;
    glp_delete_prob(trumpland);
}

void glpkwrapper::construit_couts()
{
	for (unsigned int i = 0; i < probleme_.regroupements().size(); ++i)
	{
		couts_[i] = probleme_.regroupements()[i].distance();
	}
}

void glpkwrapper::construit_taille_contr()
{
	int pos = 1;
	for (unsigned int i =0; i < nb_contr_;++i) nb_creux_ += probleme_.regroupements_contenant()[i].size();
	ia_ = new int[1+nb_creux_];
	ja_ = new int[1+nb_creux_];
	ar_ = new double[1+nb_creux_];
	for (unsigned int i = 0; i < nb_contr_; ++i)
	{
		for (unsigned int j = 0; j < probleme_.regroupements_contenant()[i].size(); ++j)
		{
			ia_[pos] = i+1;
			ja_[pos] = (probleme_.regroupements_contenant()[i][j]+1);
			ar_[pos] = 1.0;
			++pos;
		}
	}
}

void glpkwrapper::def_probleme()
{
	// definit contrainte
    glp_add_rows(trumpland, nb_contr_); 

	for (unsigned int i = 1; i <= nb_contr_; ++i)
	{
		
		/* partie indispensable : les bornes sur les contraintes */
		glp_set_row_bnds(trumpland, i, GLP_FX, droite_, 0.0); 
	}

	glp_add_cols(trumpland,nb_var_);

	for(unsigned int i=1;i<=nb_var_;++i)
	{
		glp_set_col_bnds(trumpland, i, GLP_DB, 0.0, 1.0);
		glp_set_col_kind(trumpland, i, GLP_BV);
	}  
	for(unsigned i = 1;i <= nb_var_;++i) glp_set_obj_coef(trumpland,i,couts_[i - 1]);  

	glp_load_matrix(trumpland,nb_creux_,ia_,ja_,ar_); 
}

void glpkwrapper::resoudre_probleme()
{
	def_probleme();
	glp_write_lp(trumpland,NULL,"trumpland.lp");
	glp_simplex(trumpland,NULL);	
	glp_intopt(trumpland,NULL);
}

void glpkwrapper::afficher()
{
    std::cout << "valeur optimale de la fonction objective :\n\tZ* = " << glp_mip_obj_val(trumpland) << std::endl;
    //std::cout << "\n\tvaleurs des variables de decision :\n";
    std::cout << std::endl << "tournees selectionnees :" << std::endl;
    for (unsigned i = 0; i< nb_var_; ++i)
    {
        //std::cout << "\tx_" << i+1 << "* = " << glp_mip_col_val(trumpland, i+1) << "\n";
        if(glp_mip_col_val(trumpland, i+1))
            std::cout << "\t" << probleme_.regroupements()[i].lieux() << std::endl;
    }
}

std::ostream & operator<<(std::ostream& os, glpkwrapper const& wrp)
{
    os << "\t" << wrp.nb_contr() << " contraintes\n\t"
       << wrp.nb_var() << " variables\n\t"
       << wrp.nb_creux() << " creux";
    return os;
}
