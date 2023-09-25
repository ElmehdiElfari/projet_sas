#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct tache
{
    int identifiant;
    char titre[50];
    char description[50];
    int dodate[10];
    char statut[50];
};

struct tache T[100];
int indice = 0;
int numID = 1;
void Ajoute();
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
void swap( int i, int j);
int Statistiques();
int nombreTotalTaches();
int nombreTachesCompletes();
int nombreTachesIncompletes();
int nombreJoursRestants(int index);

int compare_tasks(struct tache a, struct tache b);
void trier_deadline();

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

    printf("Enter dodate (JJ/MM/AAAA) : \n");
    scanf("%d/%d/%d", &T[indice].dodate[0], &T[indice].dodate[1], &T[indice].dodate[2]);

    printf("Enter description : \n");
    scanf(" %[^\n]", T[indice].description);

    numID++;
    indice++;
}

void ajoutPlustache()
{
    int combien;
    printf("Combien de taches voulez-vous ajouter:\n");
    scanf("%d",&combien);

    for(int i=indice;i < indice + combien;i++){
        T[i].identifiant = numID;
        printf("Identifiant %d\n",numID);
        printf("Enter le statut : \n");
        scanf(" %[^\n]", T[indice].statut);

        printf("Enter le titre : \n");
        scanf(" %[^\n]", T[indice].titre);

        printf("Enter dodate (JJ/MM/AAAA) : \n");
        scanf("%d/%d/%d", &T[indice].dodate[0], &T[indice].dodate[1], &T[indice].dodate[2]);

        printf("Enter description : \n");
        scanf(" %[^\n]", T[indice].description);
        numID++;
    }

    indice += combien;
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
        printf("Tri 3 jrs \n");
        break;
    case 4 :
        return 0;
    }
}
void afficher_tache()
{
    for (int j = 0; j < indice; j++)
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
    struct tache temp;

    for (int i = 0; i < indice - 1; i++)
    {
        for (int j = i + 1; j < indice; j++)
        {
            if (strcmp(T[i].titre, T[j].titre) > 0)
            {
                swap(i,j);
            }
        }
    }
    for(int j=0;j<indice;j++){
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
    printf("3: Retour\n");
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
            break;
        }else{
            printf("%d N'est existe pas",id);
        }
    }
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
            break;
        }else{
            printf("%d N'est existe pas",id);
        }
    }
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
            break;
        }else{
            printf("%d N'est existe pas",id);
        }
    }
}

void supprimer_identifient(int identifiant)
{
    int i, trouve = 0;

    for (i = 0; i < indice; i++)
    {
        if (T[i].identifiant == identifiant)
        {

            for (int j = i; j < indice - 1; j++)
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
        printf("Aucune tâche trouvée avec l'identifiant %d.\n", identifiant);
    }
}

void rechercher_par_identifiant()
{
    int id;
    printf("Entrer l_identifiant de la tache a rechercher :\n ");
            scanf("%d", &id);
    for (int j = 0; j < indice; j++)
    {
        if (T[j].identifiant == id)
        {
            printf("\nIdentifiant: %d\n", T[j].identifiant);
            printf("Statut: %s\n", T[j].statut);
            printf("Titre: %s\n", T[j].titre);
            printf("Description: %s\n", T[j].description);
            printf("Dodate: %d/%d/%d\n", T[j].dodate[0], T[j].dodate[1], T[j].dodate[2]);
        }else{
            printf("%d nexiste pas \n",id);
        }
    }
}

void rechercher_par_titre()
{
    char tar_get_titre[20];
    printf("entrer le nom rechercher : ");
    scanf(" %[^\n]",tar_get_titre);
    for (int j = 0; j < indice; j++)
    {
        if (strcmp (T[j].titre, tar_get_titre) == 0)
        {
            printf("\nIdentifiant: %d\n", T[j].identifiant);
            printf("Statut: %s\n", T[j].statut);
            printf("Titre: %s\n", T[j].titre);
            printf("Description: %s\n", T[j].description);
            printf("Dodate: %d/%d/%d\n", T[j].dodate[0], T[j].dodate[1], T[j].dodate[2]);
        }
        else{
            printf("%s nexiste pas \n",tar_get_titre);
        }
    }
}

void swap( int i, int j){
    struct tache temp;
    temp.identifiant = T[i].identifiant;
    T[i].identifiant = T[j].identifiant;
    T[j].identifiant = temp.identifiant;

    temp.dodate[0] = T[i].dodate[0];
    T[i].dodate[0] = T[j].dodate[0];
    T[j].dodate[0] = temp.dodate[0];

    temp.dodate[1] = T[i].dodate[1];
    T[i].dodate[1] = T[j].dodate[1];
    T[j].dodate[1] = temp.dodate[1];

    temp.dodate[2] = T[i].dodate[2];
    T[i].dodate[2] = T[j].dodate[2];
    T[j].dodate[2] = temp.dodate[2];

    strcpy(temp.titre,T[i].titre);
    strcpy(T[i].titre,T[j].titre);
    strcpy(T[j].titre,temp.titre);

    strcpy(temp.description,T[i].description);
    strcpy(T[i].description,T[j].description);
    strcpy(T[j].description,temp.description);

    strcpy(temp.statut,T[i].statut);
    strcpy(T[i].statut,T[j].statut);
    strcpy(T[j].statut,temp.statut);
}

int compare_tasks(struct tache a, struct tache b)
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
    for (int i = 0; i < indice - 1; i++)
    {
        for (int j = i + 1; j < indice; j++)
        {
            if (compare_tasks(T[i], T[j]) > 0)
            {
                struct tache temp = T[i];
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
                printf("Afficher le nombre de jours restants jusqu'au delai de chaque tache\n");
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
    for (int i = 0; i < indice; i++) {
        if (strcmp(T[i].statut, "Complet") == 0) {
            count++;
        }
    }
    return count;
}

int nombreTachesIncompletes() {
    return indice - nombreTachesCompletes();
}
