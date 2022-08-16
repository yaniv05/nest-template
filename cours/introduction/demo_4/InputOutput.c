/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Concepts des langages de programmation - Chapitre n°1
 * Dominique Marcadet - 2022 - CC BY-SA
 *
 * InputOutput.c
 *
 * Compilation avec édition de liens :
 *     cc -o InputOutput InputOutput.c
 *
 * Exécution :
 *     ./InputOutput
 */


#include <stdio.h>

int main() {
    fprintf( stdout, "Donner un nombre : " );
    int n;
    int nb_parsed = fscanf( stdin, "%d", &n );
    if( nb_parsed == 1 ) {
        fprintf( stdout, "Le carré de %d est %d\n", n, n * n );
    }
    return 0;
}
