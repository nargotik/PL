#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

sqlite3 *db;
sqlite3_stmt *stmt;
int rc;
const char insert_sql_actor[]  = "INSERT INTO actors(actor_id,primaryName,birthYear,deathYear) VALUES (?, ?, ?, ?)";
const char insert_sql_actors_profession[]  = "INSERT OR IGNORE INTO actors_profession(actor_id,profession) VALUES (?, ?)";
const char insert_sql_actors_movies[]  = "INSERT OR IGNORE INTO actors_movies(actor_id,movie_id) VALUES (?, ?)";
const char insert_sql_movie[]  = "INSERT INTO movies(movie_id,titleType,primaryTitle,originalTitle,isAdult,startYear,endYear,runtimeMinutes)"
                          "                  VALUES (?, ?, ?, ?, ? ,? ,? ,?)";
const char insert_sql_movies_genres[]  = "INSERT INTO movies_genres(movie_id,genre) VALUES (?, ?)";

int nr_movies=0,nr_actors=0;

/* Variavel para controlar o numero de inserts entre COMITS*/
int sql_inserts = 0;
int sql_inserts_row = 0;
/* Numero de inserts entre COMITS*/
const int sql_inserts_by_commit = 200000;

extern int yylex();

/**
 *
 * @param _movie
 * @param Genre
 * @return
 */
int insertMovieGenre(Movie _movie, char* Genre) {

    if (strlen(Genre) == 0)
        return 1;
    insertsCommit();
    // Insere na tabela actors
    sqlite3_stmt *res;
    //movie_id,titleType,primaryTitle,originalTitle,isAdult,startYear,endYear,runtimeMinutes
    rc = sqlite3_prepare_v2(db, insert_sql_movies_genres, -1, &res, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, _movie.movie_id,strlen(_movie.movie_id), NULL);
        sqlite3_bind_text(res, 2, Genre,strlen(Genre), NULL);
    } else {
        fprintf(stderr, "Failed to execute statement: %s - %s\n", sqlite3_errmsg(db),_movie.movie_id);
    }

    rc = sqlite3_step(res);
    if(SQLITE_DONE != rc) {
        fprintf(stderr, "insert statement didn't return DONE (%i): %s -%s\n", rc, sqlite3_errmsg(db),_movie.movie_id);
    } else {
        //printf("INSERT completed\n\n");
    }
    sqlite3_finalize(res);

    return 1;

}

/**
 *
 * @param movie_id
 * @param titleType
 * @param primaryTitle
 * @param originalTitle
 * @param isAdult
 * @param startYear
 * @param endYear
 * @param runtimeMinutes
 * @param genres
 * @return
 */
int insertMovie(Movie _movie) {
    nr_movies++;

    insertsCommit();
    // Insere na tabela actors
    sqlite3_stmt *res;
    //movie_id,titleType,primaryTitle,originalTitle,isAdult,startYear,endYear,runtimeMinutes
    rc = sqlite3_prepare_v2(db, insert_sql_movie, -1, &res, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, _movie.movie_id,strlen(_movie.movie_id), NULL);
        sqlite3_bind_text(res, 2, _movie.titleType,strlen(_movie.titleType), NULL);
        sqlite3_bind_text(res, 3, _movie.primaryTitle,strlen(_movie.primaryTitle), NULL);
        sqlite3_bind_text(res, 4, _movie.originalTitle,strlen(_movie.originalTitle), NULL);
        sqlite3_bind_int(res, 5, _movie.isAdult);
        sqlite3_bind_int(res, 6, _movie.startYear);
        sqlite3_bind_int(res, 7, _movie.endYear);
        sqlite3_bind_int(res, 8, _movie.runtimeMinutes);

    } else {
        fprintf(stderr, "Failed to execute statement: %s - %s\n", sqlite3_errmsg(db),_movie.movie_id);
    }

    rc = sqlite3_step(res);
    if(SQLITE_DONE != rc) {
        fprintf(stderr, "insert statement didn't return DONE (%i): %s -%s\n", rc, sqlite3_errmsg(db),_movie.movie_id);
    }
    sqlite3_finalize(res);
    return 1;
}

int insertActorProfession(Actor _actor, char* _profession) {
    if (strlen(_profession  ) == 0)
        return 1;
    insertsCommit();
    sqlite3_stmt *res;

    rc = sqlite3_prepare_v2(db, insert_sql_actors_profession, -1, &res, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, _actor.actor_id,strlen(_actor.actor_id), NULL);
        sqlite3_bind_text(res, 2, _profession,strlen(_profession), NULL);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    rc = sqlite3_step(res);
    if(SQLITE_DONE != rc) {
        fprintf(stderr, "insert statement didn't return DONE (%i): %s\n", rc, sqlite3_errmsg(db));
    } else {
        //printf("INSERT completed\n\n");
    }
    sqlite3_finalize(res);
    return 1;
}


int insertActorMovie(Actor _actor, char* _movie) {
    if (strlen(_movie) == 0)
        return 1;
    insertsCommit();
    sqlite3_stmt *res;

    rc = sqlite3_prepare_v2(db, insert_sql_actors_movies, -1, &res, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, _actor.actor_id,strlen(_actor.actor_id), NULL);
        sqlite3_bind_text(res, 2, _movie,strlen(_movie), NULL);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    rc = sqlite3_step(res);
    if(SQLITE_DONE != rc) {
        fprintf(stderr, "insert statement didn't return DONE (%i): %s\n", rc, sqlite3_errmsg(db));
    } else {
        //printf("INSERT completed\n\n");
    }
    sqlite3_finalize(res);
    return 1;
}

/**
 *
 * @param actor_id
 * @param primaryName
 * @param birthYear
 * @param deathYear
 * @param professions
 * @param movies
 * @return
 */
int insertActor(Actor _actor) {
    nr_actors++;
    // nm0000001	Fred Astaire	1899	1987	soundtrack,actor,miscellaneous	tt0072308,tt0043044,tt0050419,tt0053137
    insertsCommit();
    // Insere na tabela actors
    sqlite3_stmt *res;

    rc = sqlite3_prepare_v2(db, insert_sql_actor, -1, &res, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, _actor.actor_id,strlen(_actor.actor_id), NULL);
        sqlite3_bind_text(res, 2, _actor.primaryName,strlen(_actor.primaryName), NULL);
        sqlite3_bind_int(res, 3, _actor.birthYear);
        sqlite3_bind_int(res, 4, _actor.deathYear);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    rc = sqlite3_step(res);
    if(SQLITE_DONE != rc) {
        fprintf(stderr, "insert statement didn't return DONE (%i): %s\n", rc, sqlite3_errmsg(db));
    }
    sqlite3_finalize(res);
    return 1;
}

/**
 *
 * @param sql
 * @return
 */
int DbQuery(char* sql) {
    char *err_msg = 0;
    rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        exit(1);
    }
    return 1;
}

/**
 * Inicializa a base de dados
 */
void DbInitialize() {
    char *sql = "PRAGMA main.page_size = 4096;\n"
                "PRAGMA main.cache_size=10000;\n"
                "PRAGMA main.locking_mode=EXCLUSIVE;\n"
                "PRAGMA main.synchronous=NORMAL;\n"
                "PRAGMA main.journal_mode=WAL;\n"
                "PRAGMA main.cache_size=5000;\n"
                "BEGIN;\n"
                "DROP TABLE IF EXISTS movies;\n"
                "CREATE TABLE movies (\n"
                "    movie_id TEXT PRIMARY KEY,\n"
                "    titleType TEXT NOT NULL,\n"
                "    primaryTitle TEXT NOT NULL,\n"
                "    originalTitle TEXT NOT NULL,\n"
                "    isAdult INTEGER NOT NULL,\n"
                "    startYear INTEGER NOT NULL,\n"
                "    endYear INTEGER NOT NULL,\n"
                "    runtimeMinutes INTEGER NOT NULL\n"
                ");\n"
                "\n"
                "DROP TABLE IF EXISTS movies_genres;\n"
                "CREATE TABLE movies_genres (\n"
                "    movie_id TEXT,\n"
                "    genre TEXT,\n"
                "    PRIMARY KEY (movie_id , genre)\n"
                ");\n"
                "\n"
                "DROP TABLE IF EXISTS actors;\n"
                "CREATE TABLE actors (\n"
                "    actor_id TEXT PRIMARY KEY,\n"
                "    primaryName TEXT NOT NULL,\n"
                "    birthYear INTEGER NOT NULL,\n"
                "    deathYear INTEGER NULL\n"
                ");\n"
                "CREATE INDEX idx_name ON actors (primaryName);\n"
                "\n"
                "DROP TABLE IF EXISTS actors_profession;\n"
                "CREATE TABLE actors_profession (\n"
                "    actor_id TEXT,\n"
                "    profession TEXT,\n"
                "    PRIMARY KEY (actor_id , profession)\n"
                ");\n"
                "\n"
                "DROP TABLE IF EXISTS actors_movies;\n"
                "CREATE TABLE actors_movies (\n"
                "    actor_id TEXT,\n"
                "    movie_id TEXT,\n"
                "    PRIMARY KEY (actor_id , movie_id )\n"
                ");\n"
                "COMMIT;";



    DbQuery(sql);

}

/**
 *
 */
void insertsCommit() {
    sql_inserts++;
    if (sql_inserts==1)
        printf("Inserts\tMovies\tActors\n");
    if ((sql_inserts % sql_inserts_by_commit) == 0  ) {
        // Commit
        printf("%d\t%d\t%d\n",sql_inserts,nr_movies,nr_actors);
        sql_inserts_row=0;
        DbQuery("COMMIT");
        DbQuery("BEGIN TRANSACTION");
    } else {

        sql_inserts_row++;
    }
}

/**
 *
 * @return
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
 *
 * @return
 */
int DbDisconnect() {
    sqlite3_close(db);
    return 1;
}

int yywrap()
{
    // Chamado quando termina
    //printf("\n\n\nOlá fim\n\n\n");
    return(1);
}


int main()
{
    if (!DbConnect()) {
        printf("Error connecting database\n");
        return 1;
    };

    DbInitialize();

    DbQuery("BEGIN TRANSACTION");

    while (yylex());

    DbQuery("COMMIT");

    DbDisconnect();

    return 0;
}
