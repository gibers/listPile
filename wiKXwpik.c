
#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE } bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc {
  int nombre;
  struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste;

typedef struct BlocListe {
  Liste liste;
  struct BlocListe *suivant;
} BlocListe;

typedef BlocListe *ListeDeListe;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);

/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element
 * x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste *L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son
 * premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste *l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec(Liste l);
int longueur_iter(Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD(Liste *L);
void VireDernier_rec(Liste *L);
void VireDernier_iter(Liste *L);

/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/

void initVide(Liste *L) { *L = NULL; }
void initVidell(ListeDeListe *L) { *L = NULL; }

bool estVide(Liste l) { return l == NULL; }
bool estVidell(ListeDeListe l) { return l == NULL; }

int premier(Liste l) { return l->nombre; }
Liste premierll(ListeDeListe l) { return l->liste; }

Liste ajoute(int x, Liste l) {
  Liste tmp = (Liste)malloc(sizeof(Bloc));
  tmp->nombre = x;
  tmp->suivant = l;
  return tmp;
}
ListeDeListe ajoutell(Liste x, ListeDeListe l) {
  ListeDeListe tmp = (ListeDeListe)malloc(sizeof(BlocListe));
  tmp->liste = x;
  tmp->suivant = l;
  return tmp;
}

void empile(int x, Liste *L) { *L = ajoute(x, *L); }
void empilell(Liste x, ListeDeListe *L) { *L = ajoutell(x, *L); }

Liste suite(Liste l) { return l->suivant; }
ListeDeListe suitell(ListeDeListe l) { return l->suivant; }

void depile(Liste *L) {
  Liste tmp = *L;
  *L = suite(*L);
  free(tmp);
}
void depilell(ListeDeListe *L) {
  ListeDeListe tmp = *L;
  *L = suitell(*L);
  free(tmp);
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l) {
  if (estVide(l))
    printf("\n");
  else {
    printf("%d ", premier(l));
    affiche_rec(suite(l));
  }
}

void affiche_iter(Liste l) {
  Liste L2 = l;
  while (!estVide(L2)) {
    printf("%d ", premier(L2));
    L2 = suite(L2);
  }
  printf("\n");
}

void affiche_recll(ListeDeListe l) {
  if (estVidell(l)) {
    printf("\n");
  } else {
    affiche_rec(premierll(l));
    affiche_recll(suitell(l));
  }
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec(Liste l) {
  if (l == NULL)
    return 0;
  else
    return (1 + longueur_rec(l->suivant));
}

int longueur_iter(Liste l) {
  Liste P = l;
  int cpt = 0;
  while (P ISNOT NULL) {
    P = P->suivant;
    cpt++;
  }
  return cpt;
}

int longueur_recll(ListeDeListe l) {
  if (estVidell(l))
    return 0;
  else
    return (1 + longueur_recll(l->suivant));
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD(Liste *L)
// *L non NULL ie liste non vide
{
  if (((**L).suivant) == NULL)
    depile(L);  // moralement : depile(& (*L)) ;
  else
    VD(&((**L).suivant));
}

void VireDernier_rec(Liste *L) {
  if ((*L)ISNOT NULL) VD(L);  // moralement : VD(& (*L)) ;
}

void VireDernier_iter(Liste *L) {
  if ((*L)ISNOT NULL) {
    while (((**L).suivant)ISNOT NULL) L = &((**L).suivant);
    free(*L);
    *L = NULL;
  }
}

/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L) {
  if (NOT(estVide(*L))) {
    depile(L);
    VideListe(L);
  }
}
void VideListell(ListeDeListe *L) {
  if (NOT(estVidell(*L))) {
    depilell(L);
    VideListell(L);
  }
}

/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup(Liste l) {
  // printf("Double Affichage \n");
  // affiche_rec(l);
  affiche_iter(l);

  // printf("Longueur en double %d %d \n\n", longueur_rec(l), longueur_iter(l));
}

/*************************************************/
/*           DebutDeuxIdentiques                 */
/*************************************************/

bool DebutDeuxIdentiques(Liste l) {
  if (estVide(l)) return FALSE;
  if (estVide(suite(l))) return FALSE;
  return (premier(l) == premier(suite(l)));
}

/*************************************************/
/*           QueDesZero                          */
/*************************************************/

bool QueDesZero(Liste l) {
  if (estVide(l)) return TRUE;
  return (premier(l) == 0 AND QueDesZero(suite(l)));
}

/*************************************************/
/*           SousEnsemble                        */
/*************************************************/

bool SousEnsemble(Liste l1, Liste l2) {
  poup(l1);
  poup(l2);
  if (estVide(l1))
    return TRUE;
  else if (estVide(l2))
    return FALSE;
  if (premier(l1) < premier(l2))
    return FALSE;
  else if (premier(l1) == premier(l2))
    return SousEnsemble(suite(l1), suite(l2));
  else
    return SousEnsemble(l1, suite(l2));
}


/*************************************************/
/*           Permutation                         */
/*************************************************/

// Predeclarations permutation

ListeDeListe ATPTL(int n, ListeDeListe ll);
ListeDeListe concatene(ListeDeListe l1, ListeDeListe l2);
ListeDeListe ATP(int n, Liste l);
ListeDeListe AETTL(int x, ListeDeListe ll);

//implementation

ListeDeListe permutation(int n) {
  if (n == 0) {
    ListeDeListe tmpll;
    Liste tmpl;
    initVidell(&tmpll);
    initVide(&tmpl);
    empilell(tmpl, &tmpll);
    return tmpll;
  } else {
    return ATPTL(n, permutation(n - 1));
  }
}

ListeDeListe ATPTL(int n, ListeDeListe ll) {
  if (estVidell(ll)) {
    ListeDeListe tmpll;
    initVidell(&tmpll);
    return tmpll;
  } else {
    return concatene(ATP(n, premierll(ll)), ATPTL(n, suitell(ll)));
  }
}

ListeDeListe concatene(ListeDeListe l1, ListeDeListe l2) {
  if (estVidell(l1))
    return l2;
  else
    return ajoutell(premierll(l1), concatene(suitell(l1), l2));
}

ListeDeListe ATP(int n, Liste l) {
  if (estVide(l)) {
    ListeDeListe tmpll;
    Liste tmpl;
    initVidell(&tmpll);
    initVide(&tmpl);
    empile(n, &tmpl);
    empilell(tmpl, &tmpll);
    return tmpll;
  } else {
    return ajoutell(ajoute(n, l), AETTL(premier(l), ATP(n, suite(l))));
  }
}

ListeDeListe AETTL(int x, ListeDeListe ll) {
  if (estVidell(ll)) {
    ListeDeListe tmpll;
    initVidell(&tmpll);
    return tmpll;
  } else {
    return ajoutell(ajoute(x, premierll(ll)), AETTL(x, suitell(ll)));
  }
}

/*************************************************/
/*          EliminePositionsPaires               */
/*************************************************/

Liste eliminePositionsPaires(Liste L1, bool positionImpaire) {
    if (longueur_rec(L1) == 1) return L1;
    int i = L1->nombre;
    depile(&L1);
    Liste pBloc = eliminePositionsPaires(L1, NOT(positionImpaire));
    if (positionImpaire) empile(i, &pBloc);
    return pBloc;
}

Liste eliminePosisiontsPairesChap(Liste L1) {
    return eliminePositionsPaires(L1, longueur_rec(L1) % 2);
}


int main(int argc, char **argv) {

    Liste l1;
    initVide(&l1);
    empile(1, &l1);
    empile(2, &l1);
    empile(3, &l1);
    empile(4, &l1);
    empile(5, &l1);
    empile(6, &l1);
    empile(7, &l1);

    affiche_rec(l1);
    Liste pBloc = eliminePosisiontsPairesChap(l1);
    affiche_rec(pBloc);

  /*Liste l1;
  Liste l2;

  initVide(&l1);
  initVide(&l2);

  empile(1, &l1);
  empile(1, &l1);
  empile(3, &l2);
  empile(2, &l2);
  empile(1, &l2);
  empile(0, &l2);

  if (SousEnsemble(l1, l2))
    printf("vrai\n");
  else
    printf("faux\n");

  VideListe(&l1);
  VideListe(&l2);
        */

//    ListeDeListe permutationTest;
//    permutationTest = permutation(3);
//    printf("%d\n", longueur_recll(permutationTest));

//    affiche_rec(l1);

    return 0;
}
