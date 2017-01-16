/*
Fichier : STPclientTrans.c 
Commentaire : Crée un client TCP/IP simple
Execution : 
	gcc -Wall STPclientTrans.c -o STPclientTrans
	./STPclientTrans
*/
/*****************************************/
// fgets(buffer,sizeof(buffer), stdin);
// ne pas oublié fflush(fich) apré le fclose() !!!!
/******************************************/
#include "constantes.h"
#include "utils.c"

/* Envoye d'un fichier */
int 
main()
{

/* Initialisation des variables */
	int socket_id ;// id de la socket client créée

	char entree[MAX_RECEPT];// chaine de caract. recu par le serveur
	int sz_entree ;		// nb de caract. recu par le serveur

	char sortie[MAX_SEND];	// chaine de caract. envoyez vers le 						serveur
	int sz_sortie ;		// nb de caract envoyer vers le serveur

	int continu=1;		// boolean pour savoir si l'utilisateur quit la session


// Déclaration du fichier
	FILE *fich;
	
// Ouverture du fichier en mode lecture (mode "a" pour faire le '>>' du shell)
	if (NULL == (fich = fopen ("LireFich","rb"))) // mode lecture -> "r"
	{
		fprintf(stderr, "Impossible de lire le fichier\n");
		exit(-1);
	}

/* Connexion au serveur */
	socket_id = create_tcp_client("127.0.0.1",2001);
	if(socket_id == -1) 
	{
		fprintf(stderr,"Impossible de se connecter au serveur\n");
		return -1;
	}

/* Envoi du fichier au serveur */
		printf("Transmission en cours ...\n");
/*  E	*/	while((sz_sortie=fread(sortie,1,sizeof(sortie),fich)) > 0) 
/*  N	*/	{ 	
/*  V	*/		write(socket_id,sortie,sz_sortie);
/*  O	*/		printf("octets envoyer : %d\n",sz_sortie);
/*  I	*/	}
		printf("Transmission terminée.\n");

	shutdown(socket_id,2);
	close(socket_id);
	exit(EXIT_SUCCESS);

}
