	#include <stdio.h>
	#include "main.h"
    int nr_movies=0,nr_actors=0;
    Actor _actor;
    Movie _movie;
%x ACTOR MOVIE MOVIE_titleType MOVIE_primaryTitle

%%
[#]{3}.+$ {
    printf("\nComment Detected: %s\n", yytext);
}

\nnm {
    nr_actors++;
    BEGIN(ACTOR);
}
\ntt {
    nr_movies++;
    BEGIN(MOVIE);
}

<MOVIE>[0-9]+\t {
    //yytext[] = "\0";
    yytext[strlen(yytext)-1] = '\0';
    _movie.movie_id = yytext;
    //printf("-%s-\ntam-%d\n",_movie.movie_id, strlen(yytext)-1);
    BEGIN(MOVIE_titleType);
}
<MOVIE_titleType>[^\t]+\t {
    //yytext[] = "\0";
    printf("-%s-\ntam-%d\n",yytext, strlen(yytext)-1);
    BEGIN(MOVIE_primaryTitle);
}
<MOVIE_primaryTitle>[^\t]+\t {
    //yytext[] = "\0";
    printf("-%s-\ntam-%d\n",yytext, strlen(yytext)-1);

BEGIN(INITIAL);
}



<ACTOR>.+ {
    //prepareAndInsertActor(yytext);
    BEGIN(INITIAL);
}

. { }

<<EOF>> {
printf("\n Movies:%d \n Actors:%d \n",nr_movies,nr_actors);
return 0;
} ;

%%

