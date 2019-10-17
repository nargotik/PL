#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

sqlite3 *db;
sqlite3_stmt *stmt;
int rc;
const char insert_sql_actor[]  = "INSERT INTO actors(actor_id,primaryName,birthYear,deathYear) VALUES (?, ?, ?, ?)";
const char insert_sql_actors_profession[]  = "INSERT INTO actors_profession(actor_id,profession) VALUES (?, ?)";
const char insert_sql_actors_movies[]  = "INSERT INTO actors_movies(actor_id,movie_id) VALUES (?, ?)";
const char insert_sql_movie[]  = "INSERT INTO movies(movie_id,titleType,primaryTitle,originalTitle,isAdult,startYear,endYear,runtimeMinutes)"
                          "                  VALUES (?, ?, ?, ?, ? ,? ,? ,?)";
const char insert_sql_movies_genres[]  = "INSERT INTO movies_genres(movie_id,genre) VALUES (?, ?)";

/* Variavel para controlar o numero de inserts entre COMITS*/
int sql_inserts = 0;
/* Numero de inserts entre COMITS*/
const int sql_inserts_by_commit = 10000;

extern int yylex();

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
int insertMovie(char* movie_id,char* titleType,char* primaryTitle,char* originalTitle,int isAdult,int startYear,int endYear,int runtimeMinutes,char* genres) {


    // Insere na tabela movies

    // Explode dos genres por ,

    // While para inserts na tabela dos movies_genres

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
int insertActor(char* actor_id,char* primaryName,int birthYear,int deathYear,char* professions,char* movies) {
    // Insere na tabela actors
    sqlite3_stmt *res;

    rc = sqlite3_prepare_v2(db, insert_sql_actor, -1, &res, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, actor_id,sizeof(actor_id), NULL);
        sqlite3_bind_text(res, 2, primaryName,sizeof(primaryName), NULL);
        sqlite3_bind_int(res, 3, birthYear);
        sqlite3_bind_int(res, 4, deathYear);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    rc = sqlite3_step(res);
    if(SQLITE_DONE != rc) {
        fprintf(stderr, "insert statement didn't return DONE (%i): %s\n", rc, sqlite3_errmsg(db));
    } else {
        //printf("INSERT completed\n\n");
    }

    // Explode os professions por ,
    // While para inserts na tabela dos actors_profession

    // Explode os movies por ,
    // While para inserts na tabela dos actors_movies
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
    char *sql = "BEGIN;\n"
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
 * @param text
 */
void prepareAndInsertActor(char* text) {
    insertsCommit();
    // Divide o text por tabs
    //insertActor(str,"Daniel",1982,0,"","");
}

/**
 *
 * @param text
 */
void prepareAndInsertMovie(char* text) {
    insertsCommit();
    // Divide o text por tabs
    //insertMovie(str,"Daniel",1982,0,"","");
}

/**
 *
 */
void insertsCommit() {
    if ((sql_inserts % sql_inserts_by_commit) == 0 || sql_inserts>sql_inserts_by_commit) {
        // Commit
        sql_inserts=0;
        DbQuery("COMMIT");
        DbQuery("BEGIN TRANSACTION");
    } else {
        sql_inserts++;
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

    /*DbQuery("BEGIN TRANSACTION");
    for (int i = 1;i<=1000000;i++) {
        if ((i%10000) == 0) {
            printf("%d\n",i);
            DbQuery("COMMIT");
            DbQuery("BEGIN TRANSACTION");
        }

        char str[10];
        sprintf(str, "%d", i);
        insertActor(str,"Daniel",1982,0,"","");
    }

    DbQuery("COMMIT");
*/

    while (yylex());

    DbQuery("COMMIT");

    DbDisconnect();

    return 0;
}
