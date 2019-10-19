	#include <stdio.h>
	#include <stdlib.h>
	#include "main.h"


%x ACTOR_knownForTitles ACTOR_actor_id ACTOR_primaryName ACTOR_primaryProfession  ACTOR_deathYear ACTOR_birthYear   MOVIE_movie_id MOVIE_titleType MOVIE_primaryTitle MOVIE_originalTitle MOVIE_isAdult MOVIE_startYear MOVIE_endYear MOVIE_runtimeMinutes MOVIE_genres

%%
    int nr_movies=0,nr_actors=0;
    Actor tmp_actor;
    Movie tmp_movie;
    char* tmp_str;

^[#]{3}.+$ {
    printf("\nComment Detected: %s\n", yytext);
}


^tt {
    nr_movies++;
    tmp_movie.movie_id = "";
    tmp_movie.titleType = "";
    tmp_movie.primaryTitle = "";
    tmp_movie.originalTitle = "";
    tmp_movie.isAdult = 0;
    tmp_movie.startYear = 0;
    tmp_movie.endYear = 0;
    tmp_movie.runtimeMinutes = 0;
    BEGIN(MOVIE_movie_id);
}

<MOVIE_movie_id>[0-9]+\t {
    yytext[strlen(yytext)-1] = '\0';
    tmp_movie.movie_id = strdup(yytext);
    BEGIN(MOVIE_titleType);
}
<MOVIE_titleType>[^\t]+\t {
    yytext[strlen(yytext)-1] = '\0';
    tmp_movie.titleType = strdup(yytext);
    BEGIN(MOVIE_primaryTitle);
}
<MOVIE_primaryTitle>[^\t]+\t {
    yytext[strlen(yytext)-1] = '\0';
    tmp_movie.primaryTitle = strdup(yytext);
    BEGIN(MOVIE_originalTitle);
}
<MOVIE_originalTitle>[^\t]+\t {
    yytext[strlen(yytext)-1] = '\0';
    tmp_movie.originalTitle = strdup(yytext);
    //printf("%s\n",tmp_movie.movie_id);
    BEGIN(MOVIE_isAdult);
}
<MOVIE_isAdult>[^\t]+\t {
    //@todo
    yytext[strlen(yytext)-1] = '\0';
    tmp_movie.isAdult = ((yytext-'0') > 0) ? yytext-'0' : 0;
    //printf("%s\n",tmp_movie.movie_id);
    BEGIN(MOVIE_startYear);
}
<MOVIE_startYear>[^\t]+\t {
    //@todo
    yytext[strlen(yytext)-1] = '\0';
    tmp_str = strdup(yytext);
    tmp_movie.startYear = atoi(&tmp_str);
    //printf("%s\n",tmp_movie.movie_id);
    BEGIN(MOVIE_endYear);
}
<MOVIE_endYear>[^\t]+\t {
    //@todo
    yytext[strlen(yytext)-1] = '\0';
    tmp_movie.endYear =((yytext-'0') > 0) ? yytext-'0' : 0;
    //printf("%s\n",tmp_movie.movie_id);
    BEGIN(MOVIE_runtimeMinutes);
}
<MOVIE_runtimeMinutes>[^\t]+\t {
    //@todo
    yytext[strlen(yytext)-1] = '\0';
    tmp_movie.runtimeMinutes = ((yytext-'0') > 0) ? yytext-'0' : 0;
    //printf("runtimeMinutes: %s\n",tmp_movie.runtimeMinutes);
    insertMovie(tmp_movie);
    //printf("%s\n",tmp_movie.movie_id);
    BEGIN(MOVIE_genres);
}
<MOVIE_genres>[^\t\,]+\, {

    yytext[strlen(yytext)-1] = '\0';

    insertMovieGenre(tmp_movie, yytext);
}
<MOVIE_genres>[^\t\,]*\n {
    yytext[strcspn(yytext, "\r\n")] = 0;
    insertMovieGenre(tmp_movie, yytext);
    BEGIN(INITIAL);
}


^nm {
    nr_actors++;
    tmp_actor.actor_id = "";
    tmp_actor.primaryName = "";
    tmp_actor.birthYear = "";
    tmp_actor.deathYear = "";
    BEGIN(ACTOR_actor_id);
}

<ACTOR_actor_id>[0-9]+\t {
    yytext[strlen(yytext)-1] = '\0';
    tmp_actor.actor_id = strdup(yytext);
    BEGIN(ACTOR_primaryName);
}
<ACTOR_primaryName>[^\t]+\t {
    yytext[strlen(yytext)-1] = '\0';
    tmp_actor.primaryName = strdup(yytext);
    BEGIN(ACTOR_birthYear);
}
<ACTOR_birthYear>[^\t]+\t {
    //@todo
    yytext[strlen(yytext)-1] = '\0';
    tmp_str = strdup(yytext);
    tmp_actor.birthYear = atoi(&tmp_str);
    BEGIN(ACTOR_deathYear);
}
<ACTOR_deathYear>[^\t]+\t {
    //@todo
    yytext[strlen(yytext)-1] = '\0';
    tmp_str = strdup(yytext);
    tmp_actor.deathYear = atoi(&tmp_str);
    insertActor(tmp_actor);
    BEGIN(ACTOR_primaryProfession);

}
<ACTOR_primaryProfession>([^\t\,])+\, {
    yytext[strlen(yytext)-1] = '\0';


    if (strcmp("\\N",yytext)!=0) {
        insertActorProfession(tmp_actor, yytext);
        //printf("\n@%s-%s@",yytext,tmp_actor.actor_id);
    }

}
<ACTOR_primaryProfession>([^\t\,])*\t {
    yytext[strcspn(yytext, "\t")] = 0;
    //printf("\n@%s-%s@",yytext,tmp_actor.actor_id);
    if (strcmp("\\N",yytext)!=0) {
        insertActorProfession(tmp_actor, yytext);
        //printf("\n@%s-%s@",yytext,tmp_actor.actor_id);
    }

    BEGIN(ACTOR_knownForTitles);
}
<ACTOR_knownForTitles,ACTOR_primaryProfession>\n {
    BEGIN(INITIAL);
}

<ACTOR_knownForTitles>tt([^\t\,])+\, {
    yytext[strlen(yytext)-1] = '\0';
    char *_mid = strdup(yytext);
    _mid += 2;

    if (strcmp("\\N",_mid)!=0) {
        insertActorMovie(tmp_actor, _mid);
        //printf("\n-%s-%s-",_mid,tmp_actor.actor_id);
    }

}
<ACTOR_knownForTitles>tt([^\t\,])*\n {
    yytext[strcspn(yytext, "\r\n")] = 0;
    char *_mid = strdup(yytext);
    _mid += 2;

    if (strcmp("\\N",_mid)!=0) {
        //printf("\n-%s-%s-",_mid,tmp_actor.actor_id);
        insertActorMovie(tmp_actor, _mid);
    }

    BEGIN(INITIAL);
}


. { }

<<EOF>> {
    printf("\n Movies:%d \n Actors:%d \n",nr_movies,nr_actors);
    return 0;
}

%%

