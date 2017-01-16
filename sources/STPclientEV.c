/*
Fichier : client.c 
Commentaire : Crée un client TCP/IP simple
Execution : 
	gcc -Wall STPclientEV.c -o STPclientEV
	./STPclientEV
*/

/*************************************
*	Programme principal
**************************************/

#include "utils.c"
#include "constantes.h"

int 
main()
{
/* Initialisation des variables */
	int socket_id ;		// id de la socket client créée

	char entree[MAX_RECEPT];// chaine de caract. recu par le serveur
	int sz_entree ;		// nb de caract. recu par le serveur

	char sortie[MAX_SEND];	// chaine de caract. envoyez vers le serveur
	int sz_sortie ;		// nb de caract envoyer vers le serveur

	int continu=1;		// boolean pour savoir si l'utilisateur quit la session

/* Connexion au serveur */
	socket_id = create_tcp_client("127.0.0.1",2000);
	if(socket_id == -1) 
	{
		fprintf(stderr,"Impossible de se connecter au serveur\n");
		return -1;
	}

// reception du message de bienvenu
		sz_entree = read (socket_id, &entree,MAX_RECEPT);
		entree[sz_entree]='\0';
		printf("%s\n",entree);

/* Dialogue avec le serveur */
	while(continu) {	
//
		char ** reponse;	

// saisi d'une commande
      		printf(">");
      		scanf("%s", sortie); 		// Récup' de la saisie de l'utilisateur
		sz_sortie=strlen(sortie);	// Récup' de la taille de la saisie
		
/* Gestion de la commande */
		if ( (strcmp(sortie,"ls")==0) || (strcmp(sortie,"dir")==0) ) 
		{
			write(socket_id, sortie, sz_sortie);// envoie de la commande au serveur
			sz_entree = read (socket_id, &entree,MAX_RECEPT); // reception
			entree[sz_entree]='\0'; // ajout du caractere de fin
			printf("%s\n",entree); // affichage de la réponse du serveur
		}

		// S'il s'agit de la commande where
		else if (strncmp(sortie,"where",5)==0) {		
			write(socket_id, sortie, sz_sortie);// envoie de la commande au serveur
			sz_entree = read (socket_id, &entree,MAX_RECEPT); // reception
			entree[sz_entree]='\0'; // ajout du caractere de fin
			printf("%s\n",entree); // affichage de la réponse du serveur
			reponse = strsplit(entree,"\n"); // on récup' les ips ds un tableau
			printf("%s\n",tab2string(reponse)); // vérif. affichage du tableau...
		}	

		else if (strncmp(sortie,"get",3)==0) {
			
		}

		// condition d'arrêt du dialog la commande "exit"
		else if(strcmp(sortie,"exit")==0) {
			printf("Aurevoir\n");
			write(socket_id, sortie, sz_sortie);// envoie de la commande au serveur
			continu=0;
		}
		else
			printf("Cette commande n'existe pas.\n");
	}
	shutdown(socket_id,2);
	close(socket_id);
	exit(EXIT_SUCCESS);
}
