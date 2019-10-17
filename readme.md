Libs necessárias
apt-get install libsqlite3-dev

```shell script
./bin/import < test_file.tsv
```

Base de dados:
```sql
DROP TABLE IF EXISTS movies;
CREATE TABLE movies (
    movie_id TEXT PRIMARY KEY,
    titleType TEXT NOT NULL,
    primaryTitle TEXT NOT NULL,
    originalTitle TEXT NOT NULL,
    isAdult INTEGER NOT NULL,
    startYear INTEGER NOT NULL,
    endYear INTEGER NOT NULL,
    runtimeMinutes INTEGER NOT NULL
);

DROP TABLE IF EXISTS movies_genres;
CREATE TABLE movies_genres (
    movie_id TEXT,
    genre TEXT,
    PRIMARY KEY (movie_id , genre)
);

DROP TABLE IF EXISTS actors;
CREATE TABLE actors (
    actor_id TEXT PRIMARY KEY,
    primaryName TEXT NOT NULL,
    birthYear INTEGER NOT NULL,
    deathYear INTEGER NULL
);

DROP TABLE IF EXISTS actors_profession;
CREATE TABLE actors_profession (
    actor_id TEXT,
    profession TEXT,
    PRIMARY KEY (actor_id , profession)
);

DROP TABLE IF EXISTS actors_movies;
CREATE TABLE actors_movies (
    actor_id TEXT,
    movie_id TEXT,
    PRIMARY KEY (actor_id , movie_id )
);
```

