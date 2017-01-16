/*
Fichier : STPserveurTrans.c 
Commentaire : Crée un serveur TCP/IP acceptant plusieurs clients
Execution : 
	gcc -Wall STPserveurTrans.c -o STPserveurTrans
	./STPserveurTrans
*/

#include "constantes.h"
#include "utils.c"

/**********************************/
/* Fonction récup' de JM */
/***********************************/

int 
main() 
{
//
	int socket_id ;
	int client_id ;

// Déclaration du fichier
	FILE *fich;
	
// Ouverture du fichier en mode lecture (mode "a" pour faire le '>>' du shell)
	if (NULL == (fich = fopen ("test.pdf","wb"))) // mode lecture -> "r"
	{
		fprintf(stderr, "Impossible de lire le fichier\n");
		exit(-1);
	}

	char entree[MAX_RECEPT];
	int size;
	int continu=1 ;

// création de la socket d'écoute sur le port 2000, pour un maxi de 10 clients
	socket_id = create_tcp_server(2001,10);
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
				//close(socket_id);

	printf("Reception en cours ...\n");
	while( (size=read(socket_id,entree,sizeof(entree)) ) == 1024 )
	{   
		fwrite(entree,1,size,fich);
		printf("Octets recus : %d\n",size);
	}
	if (size==-1) {
		printf("Erreur sur read() ");
	}
	else if(size<1024)
	{
		fwrite(entree,1,size,fich);
		printf("Petit packet octets recus : %d\n",size);
	}
		printf("Reception terminée.\n");
		exit(EXIT_SUCCESS);
			default:
				close(client_id);
				/* Suppression des zombies */ 
				while(waitpid(-1,NULL,WNOHANG) >0);
		}
	}
	exit(EXIT_SUCCESS);
}

