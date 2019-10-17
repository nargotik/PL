	#include <stdio.h>
    int nr_movies=0,nr_actors=0;


%x ACTOR MOVIE SKIPTAB

%%
^[#]{3}.+[^\n] {
    printf("\nComment Detected: %s\n", yytext);
}

[\n]nm {
    nr_actors++;
    BEGIN(ACTOR);
}
[\n]tt {
    nr_movies++;
    BEGIN(MOVIE);
}

<MOVIE>.+ {
    prepareAndInsertMovie(yytext);
    BEGIN(INITIAL);
}

<ACTOR>.+ {
    prepareAndInsertActor(yytext);
    BEGIN(INITIAL);
}

. { }

<<EOF>> {
printf("\n Movies:%d \n Actors:%d \n",nr_movies,nr_actors);
return 0;
} ;

%%

