/**
 * @file main.h
 * @author
 *  - José Moura <a13742|at|alunos.ipca.pt>
 *  - Óscar Silva <a14383|at|alunos.ipca.pt>
 *  - Daniel Filipe <a17442|at|alunos.ipca.pt>
 * @date 17 Out 2019
 * @brief
 * Ficheiro de header da aplicação
 */

#ifndef PL_MAIN_H
#define PL_MAIN_H

/**
 * @brief
 * Ficheiro da Base de dados
 */
#define DATABASE "database.db"

/**
 * @brief
 * Utilizado de forma a não limitar o flex
 * @see https://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_node/flex_8.html
 */
#define YYLMAX 1048576

/**
 * @brief
 * Estrutura que contem um filme
 */
typedef struct {
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

int insertMovie(Movie _movie);
int DbQuery(char* sql);
void DbInitialize();
void insertsCommit();
int DbConnect();
int DbDisconnect();
int insertMovieGenre(Movie _movie, char* Genre);
int insertActorProfession(Actor _actor, char* _profession);
int insertActorMovie(Actor _actor, char* _movie);
int insertActor(Actor _actor);

#endif //PL_MAIN_H
