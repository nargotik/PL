/**
 * @file main.h
 * @author
 *  - José Moura <a13742|at|alunos.ipca.pt>
 *  - Óscar Silva <a14383|at|alunos.ipca.pt>
 *  - Daniel Filipe <a17442|at|alunos.ipca.pt>
 * @date 17 Out 2019
 * @brief
 * Ficheiro de header da aplicação
 * @see main.c
 */

#ifndef PL_MAIN_H
#define PL_MAIN_H

/**
 * @brief
 * Ficheiro da Base de dados
 */
#define DATABASE "database.db"

#define YYLMAX 1048576

/**
 * @brief
 * Estrutura que contem um filme
 */
typedef struct {
    /** @brief Id do Filme */
    char* movie_id;
    char* titleType;
    char* primaryTitle;
    char* originalTitle;
    int isAdult;
    int startYear;
    int endYear;
    int runtimeMinutes;
} Movie;

/**
 * @brief
 * Estrutura que contem um actor
 */
typedef struct  {
    char* actor_id;
    char* primaryName;
    int birthYear;
    int deathYear;
} Actor;

int DbQuery(char* sql);
int DbConnect();
int DbDisconnect();


#endif //PL_MAIN_H
