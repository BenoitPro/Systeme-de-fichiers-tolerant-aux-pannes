/*
Fichier : LireFich.c
Commentaire : Lit un fichier
Execution : 
	gcc -Wall LireFich.c -o LireFich
	./LireFich

*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLESTRING 1024

int main() {

// déclaration des chaines de caractères
	char *fichier,*lignelu,*nom,*ip;
	
	
	// Allocation de mémoire
	fichier	= malloc(TAILLESTRING * sizeof *fichier);
	lignelu	= malloc(TAILLESTRING * sizeof *lignelu);
	nom	= malloc(TAILLESTRING * sizeof *nom);
	ip	= malloc(TAILLESTRING * sizeof *ip);
	
	// Nom du fichier
	strcpy(fichier,"fc.txt");
		
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
		printf("%s", lignelu);
	}	


	if(!feof(fd)) {
	fprintf(stderr, "Probleme de lecture\n");
	exit(-1);
	}	

	fclose(fd);
	printf("\n");

	// le programme s'est déroulé correctement
	exit(0); 
}
