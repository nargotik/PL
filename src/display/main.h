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

int DbQuery(char* sql);
int DbConnect();
int DbDisconnect();


#endif //PL_MAIN_H
