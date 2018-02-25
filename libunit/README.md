# libunit - Framework de test unitaire en C

* Test des retour de fonction.
* Test de fonction avec redirection de l'entrée et sortie standard.
* **(Expérimental)** Test d'un exécutable avec redirection de l'entrée et sortie standard.

## Architecture des tests

* **libunit**/
  * **tests**/
    * *Makefile*
    * *main.c*
    * **includes**/
      * *launchers.h*
    * **test_x/**
      * *test_x.h*
      * *00_launcher.c*
      * *01_basic_tests.c*
      * *02_adv_tests.c*
      * *03_crash_tests.c*
      * *...*
    * **test_y/**
      * *test_y.h*
      * *00_launcher.c*
      * *01_basic_tests.c*
      * *...*

## Getting Started

* Créer le dossier *libunit/tests/*
* Copier le Makefile du dossier *libunit/examples/* dans *libunit/tests/*
* Créer un dossier pour chaque catégorie de test dans *libunit/tests/*
* Créer un fichier par test.
* Créer un fichier *00_launcher.c* pour chaque dossier de tests
* Créer un fichier *main.c* dans *libunit/tests/*
* Modifier le Makefile pour ajouter les dossiers de tests et les fichiers du projet à tester.

##### Dans les fichiers de tests

* Mettez uniquement une fonction de test par fichier.
* La fonction doit retourner 0 en cas de succès, -1 en cas d'erreur.

##### Dans les 00_launcher.c

* Vous devez inclure le header *"libunit.h"*
* Déclarez les prototypes des tests dans *libunit/tests/{tests folder}/{tests folder}.h*
* Déclarez tout les tests dans le launcher avec **unit\_register\_[fn|fnio|exe]**

##### Dans le main.c

* Vous devez inclure le header *"libunit.h"*
* Récupérer le *t_unit_tests* via la fonction **unit\_init**
* Déclarez les prototypes des launchers dans *libunit/tests/includes/launchers.h*
* Déclarez tout les launchers dans la fonction main avec **unit\_register\_launcher**
* Lancez la série de tests avec **unit\_launch\_tests**

## Référence
>Les fonctions des test doivent renvoyer 0 en cas de succès, -1 en cas d'erreur.

### libunit.h
`t_unit_tests *unit_init(char *name)`<br/>
**Initialisation d'une série de tests**<br/>
*name*: Nom de la série de tests.<br/>
*RETURN*: Structure de tests.<br/>

`int unit_launch_tests(t_unit_tests *tests)`<br/>
**Lancement de la série de tests**<br/>
*tests*: Structure de tests.<br/>
*RETURN*: 0 si tout les tests sont validés, -1 si un ou plusieurs test(s) ont échoué(s).<br/>

`void unit_register_launcher(t_unit_tests *tests, char *name, void (*f)(t_unit_launcher *))`<br/>
**Enregistrement d'un lancher**<br/>
*tests*: Structure de tests.<br/>
*name*: Nom du launcher.<br/>
*f*: Pointeur sur fonction du launcher. (`void f(t_unit_launcher *launcher)`)<br/>

`void unit_register_fn(t_unit_launcher *launcher, char *name, int (*f)(void))`<br/>
**Enregistrement d'une fonction standard**<br/>
*launcher*: Structure du launcher.<br/>
*name*: Nom du test.<br/>
*f*: Pointeur sur fonction du test. (`int f(void)`)<br/>

`void unit_register_fn_io(t_unit_launcher *launcher, char *name, int (*f)(int, int))`<br/>
**Enregistrement d'une fonction avec redirection de l'entrée et sortie standard**<br/>
*launcher*: Structure du launcher.<br/>
*name*: Nom du test.<br/>
*f*: Pointeur sur fonction du test. (`int f(int in, int out)`)<br/>

`void unit_register_exe(t_unit_launcher *launcher, char *name, char *path, char **argv, int (*f)(int, int, pid_t))`<br/>
**Enregistrement d'un exécutable avec redirection de l'entrée et sortie standard**<br/>
*launcher*: Structure du launcher.<br/>
*name*: Nom du test.<br/>
*path*: Chemin de l'exécutable relatif au dossier *libunit/tests/*.<br/>
*argv*: Arguments à envoyer à l'exécutable terminé par un caractère NULL.<br/>
*f*: Pointeur sur fonction du test. (`int f(int in, int out, pid_t pid)`)<br/>

### libunit_utils.h
`int utils_getline(const int fd, char **line)`<br/>
**Lecture ligne par ligne d'un descripteur de fichier**<br/>
*fd*: Descripteur de fichier.<br/>
*line*: Adresse du pointeur ou la ligne sera inscrite sans le '\\n'. (Doit être initialisé à NULL)<br/>

`void utils_purgefd(const int fd)`<br/>
**Purge le buffer d'un descripteur de fichier**<br/>
*fd*: Descripteur de fichier.<br/>

`char **utils_venvinit(void)`<br/>
**Initialisation d'un environnement virtuel**<br/>
*RETURN*: Tableau des variables d'environnement.<br/>

`void utils_venvdestroy(char **venv)`<br/>
**Detruit le tableau des variables d'environnement**<br/>
*venv*: Tableau des variables d'environnement.<br/>

`void utils_venvadd(char ***venv, const char *key, const char *value)`<br/>
**Ajoute ou modifie une variable dans l'environnement virtuel**<br/>
*venv*: Adresse du tableau des variables d'environnement.<br/>
*key*: Nom de la variable. (Ne peut être NULL)<br/>
*value*: Valeur de la variable. (Ne peut être NULL)<br/>

`char *utils_venvget(char **env, const char *key)`<br/>
**Récupère la valeur d'une variable dans l'environnement virtuel**<br/>
*venv*: Tableau des variables d'environnement.<br>
*key*: Nom de la variable. (Ne peut être NULL)<br/>
*RETURN*: La valeur de la variable ou NULL si non trouvée. (Vous ne devez pas modifier directement cette variable, utiliser *utils_venvadd*)
