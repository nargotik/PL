	#include <stdio.h>
    int nr_movies=0,nr_actors=0;


%x ACTOR MOVIE SKIPTAB

%%
^[#]{3}.+[^\n] {
    printf("\nComment Detected: %s\n", yytext);
}

^nm {
    nr_actors++;
    BEGIN(ACTOR);
}
^tt {
    nr_movies++;
    BEGIN(MOVIE);
}

<MOVIE>.+\t[^\n] {
    yytext[sizeof(yytext - 1)] = '\0';
    printf("%s\n",yytext);

}

<MOVIE>\n {

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

