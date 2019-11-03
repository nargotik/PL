/**
 * @file main.c
 * @author
 *  - José Moura <a13742|at|alunos.ipca.pt>
 *  - Óscar Silva <a14383|at|alunos.ipca.pt>
 *  - Daniel Filipe <a17442|at|alunos.ipca.pt>
 * @date 30 Out 2019
 * @brief
 * Esta aplicação mostra o conteudo da base de dados [DATABASE]
 * Essa informação é proveniente de 2 queries
 */

#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

sqlite3 *db;
sqlite3_stmt *stmt;
int rc;
/**
 * @brief
 * Query que extrai os actores ordenados por nome
 */
const char select_actor[]  = "SELECT actor_id,primaryName FROM actors ORDER BY primaryName ASC";

/**
 * @brief
 * Query que extrai os filmes de um determinado actor
 */
const char select_movies_actor[]  = "SELECT movies.movie_id,originalTitle FROM "
                                    "actors_movies, movies "
                                    "WHERE actor_id = ? "
                                    "and movies.movie_id=actors_movies.movie_id  "
                                    "ORDER BY primaryTitle ASC;";

void showActorMovies(char* actor_id);
int DbConnect();
int DbDisconnect();
void showActorsAndMovies();

/**
 * @brief
 * Conecta à base de dados
 * @return 1|0
 */
int DbConnect() {

    int rc;
    rc = sqlite3_open_v2(DATABASE, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL );

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    return 1;
}

/**
 * @brief
 * Disconecta da Base de dados
 * @return 1|0
 */
int DbDisconnect() {
    sqlite3_close(db);
    return 1;
}

/**
 * @brief
 * Função main da aplicação
 * @return
 */
int main()
{
    if (!DbConnect()) {
        printf("Error connecting database\n");
        return -1;
    };

    showActorsAndMovies();

    DbDisconnect();

    return 0;
}

/**
 * @brief
 * Mostra os actores e itera cada actor
 */
void showActorsAndMovies() {
    printf("Showing info from database\n\n");
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, select_actor, -1, &stmt, NULL)) {
        printf("Error executing sql statement\n");
        sqlite3_close(db);
        exit(-1);
    }
    while (sqlite3_step(stmt) != SQLITE_DONE) {

        printf("* %s", sqlite3_column_text(stmt, 1));
        printf("\n");
        // Coluna 0 é o id do actor
        showActorMovies(sqlite3_column_text(stmt, 0));
    }
    sqlite3_finalize(stmt);
}

/**
 * @brief
 * Mostra os filmes do actor passado no parametro e itera os filmes
 * @param actor_id id do actor
 */
void showActorMovies(char* actor_id) {
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, select_movies_actor, -1, &stmt, NULL)) {
        printf("Error executing sql statement\n");
        sqlite3_close(db);
        exit(-1);
    }
    sqlite3_bind_text(stmt, 1, actor_id,strlen(actor_id), NULL);
    while (sqlite3_step(stmt) != SQLITE_DONE) {

        printf("\t - %s", sqlite3_column_text(stmt, 1));
        printf("\n");
    }

    sqlite3_finalize(stmt);
}
