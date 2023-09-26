#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int identifiant;
    char titre[50];
    char description[50];
    int dodate[3];
    char statut[50];
}tache;

tache T[100];
int indice = 0;
int numID = 1;
void Ajoute();
int differenceJour(tache t);
void ajoutPlustache();
void afficher_tache();
void trier_alpha();
void set_start_date(struct tm date[]);
int modifier();
void modifier_Description();
void modifier_Statut();
void modifier_Dodate();
void supprimer_identifient(int identifiant);
void rechercher_par_identifiant();
void rechercher_par_titre();
int affich();
int Statistiques();
int nombreTotalTaches();
int nombreTachesCompletes();
int nombreTachesIncompletes();
int nombreJoursRestants(int index);

void affichemoin3j();
int compare_tasks(tache a,tache b);
void trier_deadline();
void nombre_jour_delai();

int main()
{
    int choix;
    int identifiant;



    while (1)
    {
        printf("\n1: Ajouter une nouvelle tache:\n");
        printf("2: Ajouter plusieurs taches:\n");
        printf("3: Afficher la liste de toutes les taches (triée par titre):\n");
        printf("4: Modifier une tache:\n");
        printf("5: Supprimer une tache par identifiant:\n");
        printf("6: Rechercher les identifiants :\n");
        printf("7: Rechercher les Taches :\n");
        printf("8: Statistiques :\n");
        printf("9: Quitter:\n");
        printf("\nEntrez votre choix: \n");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            Ajoute();
            break;
        case 2:
            ajoutPlustache();
            break;
        case 3:
            affich();
            break;
        case 4:
            modifier();
            break;
        case 5:
            printf("Entrez l'identifiant de la tâche à supprimer : ");
            scanf("%d", &identifiant);
            supprimer_identifient(identifiant);
            break;
        case 6:
           rechercher_par_identifiant();
            break;
        case 7:
             rechercher_par_titre();
            break;
        case 8:
             Statistiques();
            break;
        case 9:
            return 0;
        default:
            printf("Ce choix n'existe pas dans le menu\n");
            break;
        }
    }
}

void Ajoute()
{
    printf(" Identifiant : %d \n",numID);
    T[indice].identifiant = numID;

    printf("Enter le statut : \n");
    scanf(" %[^\n]", T[indice].statut);

    printf("Enter le titre : \n");
    scanf(" %[^\n]", T[indice].titre);
	do{
    printf("Enter dodate (JJ/MM/AAAA) : \n");
    scanf("%d/%d/%d", &T[indice].dodate[0], &T[indice].dodate[1], &T[indice].dodate[2]);
	}while((T[indice].dodate[0]<0||T[indice].dodate[0]>30)||(T[indice].dodate[1]<0||T[indice].dodate[1]>12));

    printf("Enter description : \n");
    scanf(" %[^\n]", T[indice].description);

    numID++;
    indice++;
}

int differenceJour(tache t){
	struct tm deadlineA = {0};
    deadlineA.tm_mday = t.dodate[0];
    deadlineA.tm_mon = t.dodate[1] - 1;
    deadlineA.tm_year = t.dodate[2] - 1900;
    time_t d=mktime(&deadlineA);
    time_t currentTime = time(NULL);
    double differenceInSeconds =(double)difftime(d, currentTime);
    int differenceInDays = (int)(differenceInSeconds / (60 * 60 * 24));
    return differenceInDays;
}

void ajoutPlustache()
{
    int combien;
    int i;
    printf("Combien de taches voulez-vous ajouter:\n");
    scanf("%d",&combien);
    for(i=0;i <combien;i++){
    	Ajoute();
    }

}
int affich(){
    int a;
    printf("\nComment tu veux voir les fichiers: \n");
    printf("1: Afficher par ordre alphabétique.\n");
    printf("2: Afficher par dodate.\n");
    printf("3: Afficher par dodate est dans 3 jours ou moins.\n");
    printf("4: Retour.\n");
    scanf("%d", &a);
    switch(a){
    case 1 :
        trier_alpha();
        break;
    case 2 :
        trier_deadline();
        printf("Taches triees par deadline :\n");
        afficher_tache();
        break;
    case 3 :
        affichemoin3j();
        break;
    case 4 :
        return 0;
    }
}


void afficher_tache()
{
	int j;
    for ( j = 0; j < indice; j++)
    {
        printf("\nIdentifiant: %d\n", T[j].identifiant);
        printf("Statut: %s\n", T[j].statut);
        printf("Titre: %s\n", T[j].titre);
        printf("Description: %s\n", T[j].description);
        printf("Dodate: %d/%d/%d\n", T[j].dodate[0], T[j].dodate[1], T[j].dodate[2]);
    }
}

void trier_alpha()
{
    tache temp;
	int i,j;
    for (i = 0; i < indice - 1; i++)
    {
        for (j = i + 1; j < indice; j++)
        {
            if (strcmp(T[i].titre, T[j].titre) > 0)
            {
				temp=T[i];
				T[i]=T[j];
				T[j]=temp;
            }
        }
    }
    for(j=0;j<indice;j++){
        printf("\nIdentifiant: %d\n", T[j].identifiant);
        printf("Statut: %s\n", T[j].statut);
        printf("Titre: %s\n", T[j].titre);
        printf("Description: %s\n", T[j].description);
        printf("Dodate: %d/%d/%d\n", T[j].dodate[0], T[j].dodate[1], T[j].dodate[2]);
    }
}

int modifier(){

    int choix;
    printf("Quelle information souhaitez-vous modifier ?\n");
    printf("1: Modifier la description\n");
    printf("2: Modifier le statut\n");
    printf("3: Modifier la date (JJ/MM/AAAA)\n");
    printf("0: Retour\n");
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        modifier_Description();
        break;
    case 2:
        modifier_Statut();
        break;
    case 3:
        modifier_Dodate();
        break;
    default:
        printf("Choix invalide.\n");
    }
}

void modifier_Description()
{
    int id;
    printf("Entrer id de tache : \n");
    scanf("%d",&id);
    int i;
    for (i = 0; i < indice; i++)
    {
        if (T[i].identifiant == id)
        {
            printf("Entrer la nouvelle modification pour la description : ");
            scanf(" %[^\n]", T[i].description);
            return;
        }
    }
    printf("%d N'est existe pas",id);
}

void modifier_Statut()
{
    int id;
    printf("Entrer id de tache : \n");
    scanf("%d",&id);
    int i;
    for (i = 0; i < indice; i++)
    {
        if (T[i].identifiant == id)
        {
            printf("Entrer la nouvelle modification pour le statut : ");
            scanf(" %[^\n]", T[i].statut);
            return;
        }
    }
    printf("%d N'est existe pas",id);
}

void modifier_Dodate()
{
    int id;
    printf("Entrer id de tache : \n");
    scanf("%d",&id);
    int i;
    for (i = 0; i < indice; i++)
    {
        if (T[i].identifiant == id)
        {
            printf("Entrer la nouvelle modification pour dodate (JJ/MM/AAAA) : ");
            scanf("%d/%d/%d", &T[i].dodate[0], &T[i].dodate[1], &T[i].dodate[2]);
            return;
        }

    }
    printf("%d N'est existe pas",id);
}

void supprimer_identifient(int identifiant)
{
    int i, trouve = 0;
	int j;
    for (i = 0; i < indice; i++)
    {
        if (T[i].identifiant == identifiant)
        {

            for (j = i; j < indice - 1; j++)
            {
                T[j] = T[j + 1];
            }


            indice--;

            trouve = 1;
            break;
        }
    }

    if (trouve)
    {
        printf("Tache avec l'identifiant %d supprimee avec succes.\n", identifiant);
    }
    else
    {
        printf("Aucune tache trouvee avec l'identifiant %d.\n", identifiant);
    }
}

void rechercher_par_identifiant()
{
    int id;
    int trouve=0;
    int j;
    printf("Entrer l_identifiant de la tache a rechercher :\n ");
    scanf("%d", &id);
    for ( j = 0; j < indice; j++)
    {
        if (T[j].identifiant == id)
        {
            printf("\nIdentifiant: %d\n", T[j].identifiant);
            printf("Statut: %s\n", T[j].statut);
            printf("Titre: %s\n", T[j].titre);
            printf("Description: %s\n", T[j].description);
            printf("Dodate: %d/%d/%d\n", T[j].dodate[0], T[j].dodate[1], T[j].dodate[2]);
            trouve=1;
        }
        if(trouve==1)
			return;
    }
    printf("%d nexiste pas \n",id);
}

void rechercher_par_titre()
{
    char tar_get_titre[20];
    int trouve=0;
    printf("entrer le nom rechercher : ");
    scanf(" %[^\n]",tar_get_titre);
    int j;
    for (j = 0; j < indice; j++)
    {
        if (strcmp (T[j].titre, tar_get_titre) == 0)
        {
            printf("\nIdentifiant: %d\n", T[j].identifiant);
            printf("Statut: %s\n", T[j].statut);
            printf("Titre: %s\n", T[j].titre);
            printf("Description: %s\n", T[j].description);
            printf("Dodate: %d/%d/%d\n", T[j].dodate[0], T[j].dodate[1], T[j].dodate[2]);
            trouve=1;
        }
        if(trouve==1)
        	return;

    }
    if(trouve==0){
    	printf("%s nexiste pas \n",tar_get_titre);
	}
}


void affichemoin3j(){
	int i;
	for(i=0;i<indice;i++){
		if(differenceJour(T[i])<=3){
			printf("\nIdentifiant: %d\n", T[i].identifiant);
	        printf("Statut: %s\n", T[i].statut);
	        printf("Titre: %s\n", T[i].titre);
	        printf("Description: %s\n", T[i].description);
	        printf("Dodate: %d/%d/%d\n", T[i].dodate[0], T[i].dodate[1], T[i].dodate[2]);
		}
	}
}

int compare_tasks(tache a, tache b)
{
    struct tm deadlineA = {0};
    struct tm deadlineB = {0};

    deadlineA.tm_mday = a.dodate[0];
    deadlineA.tm_mon = a.dodate[1] - 1;
    deadlineA.tm_year = a.dodate[2] - 1900;

    deadlineB.tm_mday = b.dodate[0];
    deadlineB.tm_mon = b.dodate[1] - 1;
    deadlineB.tm_year = b.dodate[2] - 1900;

    time_t timeA = mktime(&deadlineA);
    time_t timeB = mktime(&deadlineB);

    if (timeA < timeB)
        return -1;
    else if (timeA > timeB)
        return 1;
    else
        return 0;
}

void trier_deadline()
{
	int i,j;
    for ( i = 0; i < indice - 1; i++)
    {
        for (j = i + 1; j < indice; j++)
        {
            if (compare_tasks(T[i], T[j]) > 0)
            {
                tache temp = T[i];
                T[i] = T[j];
                T[j] = temp;
            }
        }
    }
}
int Statistiques() {
    int choix;

    printf("1: Afficher le nombre total de taches\n");
    printf("2: Afficher le nombre de taches completes\n");
    printf("3: Afficher le nombre de taches incompletes\n");
    printf("4: Afficher le nombre de jours restants jusqu'au delai de chaque tache\n");
    printf("5: Retour\n");

    printf("Entrez votre choix : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            {
                int nbr_tache = nombreTotalTaches();

    printf("Le nombre total de taches : %d\n", nbr_tache);
                break;
            }
        case 2:
            {
                int nbr_complet = nombreTachesCompletes();
                    printf("Le nombre de taches completes : %d\n", nbr_complet);
                break;
            }
        case 3:
            {
                int nbr_incomplet = nombreTachesIncompletes();
                    printf("Le nombre de taches incompletes : %d\n", nbr_incomplet);
                break;
            }
        case 4:
                nombre_jour_delai();
            break;
        case 5:
            return 0;
        default:
            printf("Option invalide.\n");
    }
    return 1;
}

int nombreTotalTaches() {
    return indice;
}

int nombreTachesCompletes() {
    int count = 0;
    int i;
    for (i = 0; i < indice; i++) {
        if (strcmp(T[i].statut, "done") == 0) {
            count++;
        }
    }
    return count;
}

int nombreTachesIncompletes() {
    return indice - nombreTachesCompletes();
}

void nombre_jour_delai(){
	int i;
	for(i=0;i<indice;i++){
		printf("\nle nombre de jours restant au delai de tache %d est %d\n",T[i].identifiant,differenceJour(T[i]));
	}
}
