/************************************************************
 *     __/\\\_____________________/\\\\\\\\\_               *
 *      _\/\\\__________________/\\\////////__              *
 *       _\/\\\________________/\\\/___________             *
 *        _\/\\\_______________/\\\_____________            *
 *         _\/\\\______________\/\\\_____________           *
 *          _\/\\\______________\//\\\____________          *
 *           _\/\\\_______________\///\\\__________         *
 *            _\/\\\\\\\\\\\\\\\_____\////\\\\\\\\\_        *
 *             _\///////////////_________\/////////__       *
 *                                                          *
 *                                                          *
 *      Auteur : Ludovic Corcos                             *
 *                                                          *
 *      Université Clermont Auvergne | L2 Informatique      *
 *                                                          *
 *      Date : 23/02/2020                                   *   
 *                                                          *
 *      Programme : van_der_corput.c                        *
 *                                                          *
 *      Description :                                       *
 *      Générateur de la séquence de Van Der Corput 		*
 * 		avec affiche graphique de la séquence	            *
 *                                                          *
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#define ANSI_COLOR_RED "\e[31m"
#define ANSI_COLOR_GREEN "\e[92m"
#define ANSI_COLOR_YELLOW "\e[93m"
#define ANSI_COLOR_BLUE "\e[94m"
#define ANSI_COLOR_MAGENTA "\e[95m"
#define ANSI_COLOR_CYAN "\e[96m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define NB_VALEURS 32 //	Nombres de valeurs générés pour la équence de Van Der Corput
//	Au dessus de 32, il y a un problème au niveau de l'affichage dans le terminal
#define TAILLE_CHAINE_MAX 256 //  Taille de la chaine où sera stocké l'écriture en binaire des nombres

/************************************************************
 *                                                          *
 *                  Prototypes des fonctions                *
 *                                                          *
 ************************************************************/

double corput(int nombre);
void int_to_bin_entier(double int_part, char *chaine_binaire);
void int_to_bin_float(double float_part, char *chaine_binaire);
void int_to_dec(double nombre, char *chaine_binaire);
void corput_fraction(int nombre, int *numerateur, int *denominateur);

/************************************************************
 *                                                          *
 *                Fonction 'main' principale                *
 *                                                          *
 ************************************************************/

int main(int argc, char *argv[])
{

	double tab_result_corput[NB_VALEURS] = {0};
	int numerateur[NB_VALEURS] = {0};
	int denominateur[NB_VALEURS] = {0};
	char chaine_binaire_init[TAILLE_CHAINE_MAX];
	char chaine_binaire_inverse[TAILLE_CHAINE_MAX];
	int i, j, num, denom;
	int max_denom = 0;

	printf(ANSI_COLOR_RED);
	printf("■");
	printf(ANSI_COLOR_GREEN);
	printf("■");
	printf(ANSI_COLOR_YELLOW);
	printf("■");
	printf(ANSI_COLOR_BLUE);
	printf("■");
	printf(ANSI_COLOR_MAGENTA);
	printf("■");
	printf(ANSI_COLOR_CYAN);
	printf("■\n");
	printf(ANSI_COLOR_RESET);

	//	Remplissage du tableau où seront affectés les valeurs résultats de Van Der Corput
	for (i = 0; i < NB_VALEURS; i++)
	{
		tab_result_corput[i] = corput(i);
	}

	//	Remplissage des tableaux où seront affectés les valeurs résultats de Van Der Corput sous forme fractionnaire
	for (i = 0; i < NB_VALEURS; i++)
	{
		corput_fraction(i, &num, &denom);

		if (num)
		{
			numerateur[i] = num;
			denominateur[i] = denom;

			if (denom > max_denom)
			{
				max_denom = denom;
			}
		}
		else
		{
			numerateur[i] = 0;
			denominateur[i] = 0;
		}
	}

	printf("Nombre\tBinaire\t\tBinaire inverse\t\tRésultat\tFraction\tReprésentation graphique\n\n");

	for (i = 0; i < NB_VALEURS; i++)
	{
		printf("%d\t", i);

		int_to_dec(i, chaine_binaire_init);
		printf("%s\t\t", chaine_binaire_init);

		int_to_dec(tab_result_corput[i], chaine_binaire_inverse);
		printf("%s\t\t\t", chaine_binaire_inverse);

		printf("%g\t\t", corput(i));

		if ((numerateur[i] && denominateur[i]) == 0)
		{
			printf("0\t\t");
		}
		else
		{
			printf("%d/%d\t\t", numerateur[i], denominateur[i]);
		}

		if ((numerateur[i] && denominateur[i]) == 0)
		{
			for (j = 1; j <= max_denom; j++)
			{
				printf(ANSI_COLOR_BLUE);
				printf("■");
				printf(ANSI_COLOR_RESET);
			}
		}
		else
		{
			for (j = 1; j <= max_denom; j++)
			{
				int temp = (numerateur[i] * max_denom);
				if (j == ((int)temp / (int)denominateur[i]))
				{
					printf(ANSI_COLOR_YELLOW);
					printf("■");
					printf(ANSI_COLOR_RESET);
				}
				else
				{
					printf(ANSI_COLOR_BLUE);
					printf("■");
					printf(ANSI_COLOR_RESET);
				}
			}
		}

		printf("\n");
	}

	return EXIT_SUCCESS;
}

/************************************************************
 *                                                          *
 *                   Fonctions ressources                   *
 *                                                          *
 ************************************************************/

//  Permet d'obtenir le result de Van Der Corput
//  Au nombre corespondant
double corput(int nombre)
{
	double result = 0;
	double temp = (double)1 / 2;

	while (nombre > 0)
	{
		result += (nombre % 2) * temp;

		nombre /= 2;

		temp /= 2;
	}

	return result;
}

void int_to_bin_entier(double int_part, char *chaine_binaire)
{
	int compteur = 0;
	int i;
	char chaine_binaire_temp[TAILLE_CHAINE_MAX];

	while (int_part > 0)
	{
		chaine_binaire_temp[compteur++] = '0' + (int)fmod(int_part, 2);
		int_part = floor(int_part / 2);
	}

	/* Permet d'inverser la chaine binaire */
	for (i = 0; i < compteur; i++)
	{
		chaine_binaire[i] = chaine_binaire_temp[compteur - i - 1];
	}

	chaine_binaire[compteur] = 0;
}

void int_to_bin_float(double float_part, char *chaine_binaire)
{
	int compteur = 0;
	double int_part;

	while (float_part > 0)
	{
		float_part *= 2;
		float_part = modf(float_part, &int_part);
		chaine_binaire[compteur++] = '0' + (int)int_part;
	}
	chaine_binaire[compteur] = 0;
}

//  Converti un réel positif pour afficher son équivalent bianire
void int_to_dec(double nombre, char *chaine_binaire)
{
	double int_part, float_part;

	//	Sépare la partie entière et fractionnaire
	float_part = modf(nombre, &int_part);

	//	Converti la partie entière si elle n'est pas nulle
	if (int_part != 0)
	{
		int_to_bin_entier(int_part, chaine_binaire);
	}
	else
	{
		strcpy(chaine_binaire, "0");
	}

	strcat(chaine_binaire, "."); //	Concatène le '.' dans la chaine de caractère en sortie

	//	Converti la partie floatante si elle n'est pas nulle
	if (float_part != 0)
	{
		int_to_bin_float(float_part, chaine_binaire + strlen(chaine_binaire));
		//	Permet d'ajouter la parie fractionnaire à la chaine déjà présente
	}

	else
	{
		strcpy(chaine_binaire + strlen(chaine_binaire), "0");
	}
}

//	Algortihme de Van Der Corupt, mais ici, il pemet de générer un affichage
//	fractionnaire en récupérant le numérateur et le dénominateur
void corput_fraction(int nombre, int *numerateur, int *denominateur)
{
	int result = 0;
	int temp = 1;

	while (nombre)
	{
		result = result * 2 + (nombre % 2);
		temp *= 2;
		nombre /= 2;
	}

	*numerateur = result;
	*denominateur = temp;

	while (result)
	{
		nombre = result;
		result = temp % result;
		temp = nombre;
	}
	*numerateur /= temp;
	*denominateur /= temp;
}