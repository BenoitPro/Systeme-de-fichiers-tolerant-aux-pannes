
//****************************************************************************/
/*			Programme Principal				     */
//****************************************************************************/
int main() {
	char *fichier;
	char **tabl;
	char *nom;
	fichier	= malloc(TAILLESTRING * sizeof *fichier);
	nom	= malloc(TAILLESTRING * sizeof *nom);
	strcpy(fichier,"fc.txt");
	


/****** Affichage de l'espace virtuel ***************/
	tabl= donneEV();
	int i=0;
	printf("Espace virtuel :\n");
	
	while(NULL!= tabl[i]) {	// pas simple d'afficher un tableau dont la taille n'est pas connu...
		printf(" %s \n",tabl[i]);
		i++;
	}	

/********* Recherche d'un fichier dans l'EV *****************/
	char *resu;	
	resu	= malloc(TAILLESTRING * sizeof *resu);
	resu=rechercheFich("bob.pdf");
	printf("Fichier trouver : %s\n",resu);

/********** Recherche des ips d'un fichier *******************/
	char **resu2;
	resu2 = donneIps("fiche.pdf");
	
	i=0;
	while(NULL!=resu2[i]) {	
		printf("ips : %s \n",resu2[i]);
		i++;
	}	


/************ Ajoute une IP a un fichier *******************/
	ajouteIp("jaky","Benoit");
	

/**************** Fin du prog principal ***************************/
	exit(0); 
}
