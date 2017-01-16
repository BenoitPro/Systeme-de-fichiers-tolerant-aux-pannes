/*
Fichier : STPserveurEV.c 
Commentaire : Crée un serveur TCP/IP acceptant plusieurs clients
Execution : 
	gcc -Wall STPserveurEV.c -o STPserveurEV
	./STPserveurEV
*/

#include "utils.c"
#include "constantes.h"


/**********
* gere_commandes(), traduit puis réalise la commande du client et retourne le résultat
**********/
char*
gere_commandes(char* cmd)
{
char* reponse;
/* Le client veut voir l'espace virtuel */
	if ( (strcmp(cmd,"ls")==0) || (strcmp(cmd,"dir")==0) )
	{
		reponse = tab2string(donneEV());
	}
/* Le client veut connaitre les ip hébergeant un fichier donné en param. */
	else if (memcmp(cmd,"where",5)==0)
	{
		// Récup' du fichier donné en second paramètre
		char** fichier=strsplit(cmd,"_");
		if(fichier[1]!=NULL)
		{
		char** ips=donneIps (fichier[1]);
		if(ips[0]!=NULL)
			reponse = tab2string(ips);		
		else
			reponse = "Ce fichier n'existe pas - tapez ls ...\n" ;
		
		}
		else
			reponse ="where prend un nom de fichier en parametre (ex where_fich.txt)\n";
	}

	else if (strcmp(cmd,"exit")==0)
		reponse = "exit";

/* Le client a entré une commande qui n'existe pas*/
	else
		reponse="Cette commande n'existe pas tapez '?' pour connaitre les commandes\n";
return reponse;
		
}



/**********
* gere_client, Gère le dialog avec le client et répond à ses demandes
**********/
int
gere_client(int client_id)
{

/* Initialisation des variables */

	int debut=1;	// Pour savoir si on début le dialog
	int continu=1;	// Pour savoir si le client veut quitter
	int sz_entree;	// taille de la cmd
	char entree[MAX_RECEPT]; // chaine du client reçu par le serveur 
			
/* gestion du dialog */
	while(continu) 
	{
		 if (debut)	// Si on début le dialogue, message de bienvenu
		{	
			char bienvenu[] = "Bienvenu sur le serveur STP2K6 :)\n";
			write(client_id, bienvenu, strlen(bienvenu));
			debut=0;
		}
		else {	// Sinon on est en plein dialogue
			//char hello[] = "Bienvenu sur le serveur STP2K6 :)\n";
			if((sz_entree=read(client_id, &entree, MAX_RECEPT))<0)
			{
             			fprintf(stderr,"Impossible de lire la socket");
              			return EXIT_FAILURE;
			}
			// Reception de la commande du client
			entree[sz_entree]='\0';
			printf("STPclient%d> %s\n",client_id,entree);
	
			// Traitement de la commande
			char * rep;
			rep = gere_commandes(entree);
	
			if (strcmp(rep,"exit") != 0) {
				//printf(rep);				
				write(client_id, rep, strlen(rep));
			}	
			else
				continu=0;
			
		}		
	}
	printf("STPserveur> Fermeture de la connexion avec le client : %d\n",client_id);
	shutdown(client_id,2);
	close(client_id);

	return EXIT_SUCCESS;
}

int 
main() 
{
	int socket_id ;
	int client_id ;

	// création de la socket d'écoute sur le port 2000, pour un maxi de 10 clients
	socket_id = create_tcp_server(2000,10);

	while(1) // boucle infinie d'attente de clients
	{
		int pid;
		if(-1 == (client_id = accept(socket_id,NULL,0)))
		{
			fprintf(stderr,"Erreur sur accept()\n");
			exit(EXIT_FAILURE);
		}

		switch((pid  = fork())) 
		{
			case -1 :
				fprintf(stderr,"Problème avec fork()\n");
				exit(EXIT_FAILURE);
			case 0 : //gestion du fils
				close(socket_id);
				// gestion du dialog avec le client
				gere_client(client_id);
				
				exit(EXIT_SUCCESS);
			default:
				close(client_id);
				/* Suppression des zombies */
				while(waitpid(-1,NULL,WNOHANG) >0);

		}

	}
	exit(EXIT_SUCCESS);
}

