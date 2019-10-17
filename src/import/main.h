//
// Created by Daniel on 17/10/2019.
//

#ifndef PL_MAIN_H
#define PL_MAIN_H

#define DATABASE "database.db"

typedef struct _movie {
    char* movie_id;
    char* titleType;
    char* primaryTitle;
    char* originalTitle;
    int isAdult;
    int startYear;
    int endYear;
    int runtimeMinutes;
} Movie;

typedef struct _actor {
    char* actor_id;
    char* primaryName;
    int birthYear;
    int deathYear;
} Actor;

#endif //PL_MAIN_H
