/*
Fichier : GereEV.c
Commentaire : Lit un fichier
Execution : 
	gcc -Wall GereEV.c -o GereEV
	./GereEV

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"


//****************************************************************************/
/*									     */
/*			Manipulation de String				     */
/*									     */
//****************************************************************************/
/* strsplit, permet de séparer une chaine (char *) selon un séparateur,
en renvoyant un tableau de chaine (char**) */
char** strsplit(const char * str,const char*separator)
{
	char **a = NULL;
	int a_size = 0;
	int a_len = 0;
	int i;
	int separator_len = strlen(separator);
	const char *p0;
	char *p1;

/* Initialisations */ 
	if( NULL == (a = malloc(TAILLESTRING * sizeof *a)))
		return(NULL);

	a_size = TAILLESTRING ;
	a_len = 0;
	p0 = str;

	/* Récupération des sous chaines */ 
	while(p0 && (p1 = strstr(p0, separator)))
{
	if(a_len>=(a_size+2))
	{
	/* L'espace initialement prévus est insuffisant */
	a_size +=TAILLESTRING;
	if (NULL== (a =realloc(a,a_size * sizeof *a)))
		return (NULL);
	}
	if (NULL == (a[a_len] = calloc(p1 - p0 + 1, sizeof **a)))
	{
		for(i = 0;i< a_len;i++)
			free(a[i]);
		free(a);
		return (NULL);

	}	
	memcpy(a[a_len], p0, p1  - p0);
	p0 = p1 + separator_len ;
	a_len++;
}

	/* On récupere la derniere chaine */
	if (NULL == (a[a_len] = strdup(p0)))
	{
		for( i = 0;i<a_len;i++)
			free(a[i]);
		free(a);
		return NULL;
	}
	a_len++;
	a[a_len] = NULL;
	
	return (a);

}

//****************************************************************************/
/*			Fonction pour géré L'espace virtuel		     */
//****************************************************************************/

/*****
 donneEV , renvoi un tableau de char* contenant les fichiers de l'espace virtuel 
*****/

char** donneEV() {

// déclaration des chaines de caractères
	char *fichier,*lignelu;
	char **temp;
	char **tab;
	int tab_len=0;


	// Allocation de mémoire
	fichier	= malloc(TAILLESTRING * sizeof *fichier);
	lignelu	= malloc(TAILLESTRING * sizeof *lignelu);
	tab	= malloc(TAILLESTRING * sizeof *tab);
	
	// Nom du fichier
	strcpy(fichier,FICHIERCORRES);
		
	// Déclaration du fichier
	FILE *fd;
	
	// Ouverture du fichier en mode lecture (mode "a" pour faire le '>>' du shell)
	if (NULL == (fd = fopen (fichier,"r"))) // mode lecture -> "r"
	{
		fprintf(stderr, "Impossible de lire le fichier\n");
		exit(-1);
	}
	// Parcour des lignes du fichier
	while(fgets(lignelu, TAILLESTRING, fd)) {
		temp = strsplit(lignelu,";");
		tab[tab_len]=temp[0];
		tab_len++;
	}	
	
	if(!feof(fd)) {
	fprintf(stderr, "Probleme de lecture\n");
	exit(-1);
	}	

	fclose(fd);
	printf("\n");

return (tab);

}

/**********
* Convertie un tableau de chaine de caract en une chaine de caract
***********/
char* 
tab2string(char** tab) {
	int i=0;
	char res[TAILLESTRING];
	strcpy(res,"");
	while(NULL!= tab[i]) {
		strcat(res,tab[i]);
		strcat(res,"\n");
		i++;
	}	
return (res);
}


/****
 rechercheFich , recherche un fichier et renvoie sa ligne sinon renvoi NULL 
*****/
char* rechercheFich(const char * nomFich) {

// déclaration des chaines de caractères
	char *fichier,*lignelu;
	char **temp;
	int trouve=0;
	char *res;

	// Allocation de mémoire
	fichier	= malloc(TAILLESTRING * sizeof *fichier);
	lignelu	= malloc(TAILLESTRING * sizeof *lignelu);
	res	= malloc(TAILLESTRING * sizeof *res);
	
	// Nom du fichier
	strcpy(fichier,FICHIERCORRES);
		
	// Déclaration du fichier
	FILE *fd;
	
	// Ouverture du fichier en mode lecture (mode "a" pour faire le '>>' du shell)
	if (NULL == (fd = fopen (fichier,"r"))) // mode lecture -> "r"
	{
		fprintf(stderr, "Impossible de lire le fichier\n");
		exit(-1);
	}
	// Parcour des lignes du fichier
	while((fgets(lignelu, TAILLESTRING, fd)) && (trouve==0)) {
		temp = strsplit(lignelu,";");
		if (strcmp(temp[0],nomFich)==0)
		{
			trouve = 1;
			strcpy(res,lignelu);
			fclose(fd);
			return (res);
		}
	}	
	
	if(!feof(fd)) {
	fprintf(stderr, "Probleme de lecture\n");
	exit(-1);
	}	

	fclose(fd);
	printf("\n");
return NULL; // <-------- ATTENTION P-E METTRE (res) PLUTOT
}


void SupprimerLigne(char *nomFich, char *ligne)
{
        FILE *temp, *fich;
        char line[256];
        /* fichier dont on doit suprimer une ligne */
        if ((fich = fopen(nomFich,"r")) == NULL ) exit (EXIT_FAILURE);
        /* fichier temporaire */
        if ((temp = fopen("temp","w")) == NULL ) exit (EXIT_FAILURE);
        /* Tant qu'il y a des lignes on lit dans fich */
        while( fgets (line, sizeof(line), fich) )
        {
                /* Si la ligne n'est pas celle en paramètre */
                if ( strcmp(line,ligne) != 0 )
                        /* On l'ecrit dans temp */
                        fputs(line, temp);
        }
        fclose(fich);
        fclose(temp);
        /* Suppression de fich */
        unlink(nomFich);
        /* On renomme temp */
        rename("temp", nomFich);
} 
/*****
FAIT A 50% besion de supprimeLigne
 ajouteIp , insere l'ip d'un nouveau pc pour un fichier donnée, si le fichier
n'existait pas il est ajouté en meme temp que son ip
*****/

void ajouteIp(const char* nomFich,const char* ip) {

	// Recherche du 'fichier'
	char *resu;	
	resu	= malloc(TAILLESTRING * sizeof *resu);
	resu=rechercheFich(nomFich);

	// si le 'fichier' est présent
	if(resu!=NULL) 
	{
	//...A faire....
		printf("fichier trouve -> %s", resu);
	}
	// si le 'fichier' n'est pas trouver on l'ajoute
	else
	{
		printf("fichier NON trouvé ajout de la ligne \n");
	// Déclaration du fichier
		FILE *fd;
	
	// Ouverture du fichier en mode écriture (mode "a" pour faire le '>>' du shell)
		if (NULL == (fd = fopen (FICHIERCORRES,"a")))	
		{
		fprintf(stderr, "Impossible de lire le fichier\n");
		exit(-1);
		}
	// Ecriture, formater par fprintf(), dans le fichier
		fprintf(fd,"%s;%s;\n",nomFich,ip);
		fclose(fd);
	}
	
}

/************
donneIps , donne les ips sous forme d'un tableau de char* d'un fichier donné en parametre
le resultat vaut NULL si ya rien de trouvé
************/
char** donneIps (const char* nomFich) {
	
	/* Recherche la ligne */
	char *ligne;	
	char **res1 ;
	char **res2 ;
	int i=1;
	ligne= malloc(TAILLESTRING * sizeof *ligne);
	res2= malloc(TAILLESTRING * sizeof *res2);
	ligne=rechercheFich(nomFich);
	if(ligne!=NULL)
	{
		res1=strsplit(ligne,";");
		while( NULL!=res1[i] ) {
			if (strcmp("\n",res1[i])!=0) 
			{	
			res2[i-1]=res1[i];
			}
			i++;
		}
		//return res2;
	
	}
return (res2);
}

//****************************************************************************/
/*									     */
/*			Connexion et Socket				     */
/*									     */
//****************************************************************************/

#include <stdio.h> 	// entrées sorties
#include <stdlib.h> 
#include <string.h>	// chaine de caractères
#include <unistd.h>	// pour close
#include <sys/socket.h>	// pour listen, shutdown
#include <sys/types.h>	// socket, bind, accept, getsockopt
#include <netinet/in.h> 
#include <netdb.h> // en plus du prog serveur.c

#include <sys/param.h>
#include <arpa/inet.h>

#include <sys/wait.h> // pour tcp_serveur

/************
create_tcp_client ,  cré une connexion avec un serveur
************/
int 
create_tcp_client(const char* hostname, int port)
{
	struct hostent *host_address; // pour le résultat de la fonction gethostbyname();
	struct sockaddr_in sockname; // structure pour les infos du socket

	int optval;
	int socket_id;


	/* Obtention de l'adresse de la machine distante */
	if(NULL == (host_address = gethostbyname(hostname)))
	{
		//write(socket_id, cmd, strlen(cmd));
		fprintf(stderr,"Echec de gethostbyname()\n");
		return -1;
	}
	/* Création de la socket */
	if(-1 == (socket_id = socket(PF_INET,SOCK_STREAM,0)))
	{
	fprintf(stderr,"Impossible de créer une socket\n");
	exit(EXIT_FAILURE);
	}

	/* Changement d'un paramètre de la socket pour permettre une réutilisation immédiate après sa fermeture */
	optval = 1;
	setsockopt(socket_id,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(int));

	/* Connexion de la socket au serveur distant */

	sockname.sin_family = host_address->h_addrtype;
	sockname.sin_port = htons(port);
	memcpy((char *) &(sockname.sin_addr.s_addr),host_address->h_addr, host_address->h_length);

	if(-1 == (connect(socket_id, (struct sockaddr *) &sockname, sizeof(struct sockaddr_in))))
	{
		fprintf(stderr,"Impossible de connecter la socket au serveur '%s'\n",hostname);
		return -1;
	}
	
	return (socket_id);

}



/************
create_tcp_server ,  crée une écoute d'un port
************/
int
create_tcp_server(int port,int nb_max_clients)
{
	int socket_id;
	int optval=1;
	struct sockaddr_in sockname;

	/* Création de la socket */
	if(-1 == (socket_id = socket(PF_INET,SOCK_STREAM, 0)))
	{
		fprintf(stderr, "Impossible de créer une socket\n");
		exit(EXIT_FAILURE);
	}
		
	/* Changement d'un parametre de la socket pour permettre une réutilisation
	* immédiate du port après sa fermeture	
	*/
	setsockopt(socket_id,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(int));

	/* Affectation d'une adresse */
	memset((char *) &sockname, 0, sizeof(struct sockaddr_in));
	sockname.sin_family = AF_INET; // nom de famille de protocol
	sockname.sin_port = htons(port);
	sockname.sin_addr.s_addr = htonl(INADDR_ANY); // ecoute toutes les adresses dispo

	if(-1 == (bind(socket_id, (struct sockaddr *) &sockname,
		sizeof(struct sockaddr_in))))
	{
		fprintf(stderr,"Erreur sur bin() serveur probablement deja lancé\n");
		exit(EXIT_FAILURE);
	}	
	
	/* Mise en écoute de la socket */
	if(-1 == (listen (socket_id, nb_max_clients)))
	{
		fprintf(stderr,"Erreur sur listen()\n");
		exit(EXIT_FAILURE);
	}
return (socket_id);
}

