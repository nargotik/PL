//
// Created by Daniel on 17/10/2019.
//

#ifndef PL_MAIN_H
#define PL_MAIN_H

#define DATABASE "database.db"

#define YYLMAX 1048576

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

#endif //PL_MAIN_H
