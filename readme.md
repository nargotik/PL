---


---

<h1 id="trabalho-prático-de-pl">Trabalho Prático de PL</h1>
<p>O presente software foi desenvolvido no contexto académico e deve ser utilizado sem qualquer garantia por conta e risco do utilizador.</p>
<p><a href="https://travis-ci.com/nargotik/PL"><img src="https://travis-ci.com/nargotik/PL.svg?token=qNfqiYyxNzmWoPqpyHnZ&amp;branch=master" alt="Build Status"></a></p>
<p><strong>Autores:</strong></p>
<ul>
<li>José Moura <a href="mailto:a13742@alunos.ipca.pt">a13742@alunos.ipca.pt</a></li>
<li>Óscar Silva <a href="mailto:a14383@alunos.ipca.pt">a14383@alunos.ipca.pt</a></li>
<li>Daniel Filipe <a href="mailto:a17442@alunos.ipca.pt">a17442@alunos.ipca.pt</a></li>
</ul>
<p><strong>Links Uteis</strong></p>
<ul>
<li>GitHub: <a href="https://github.com/nargotik/PL/">https://github.com/nargotik/PL/</a></li>
<li>Documentação: <a href="https://nargotik.github.io/PL/">https://nargotik.github.io/PL/</a></li>
</ul>
<h2 id="introdução">Introdução</h2>
<p>Para a realização deste trabalho foram utilizadas as ferramentas abaixo descritas:</p>
<ul>
<li>flex (versão 2.6.0)</li>
<li>libfl-dev</li>
<li>libsqlite3-dev</li>
<li>sqlite3 (Opcional)</li>
</ul>
<p>Utilizamos um motor de base de dados simples (sqlite) de forma a importar toda a informação contida no ficheiro de teste para a base de dados e poder efectuar consultas de qualquer informação directamente na base de dados.</p>
<h2 id="requisitos">Requisitos</h2>
<p>Libs necessárias instalação em Ubuntu (pode variar com outras distribuições)</p>
<pre class=" language-shell"><code class="prism  language-shell">apt-get install libsqlite3-dev
</code></pre>
<p>Existe a necessidade de, pelo menos, 2Gb de memoria RAM para processar o ficheiro de teste fornecido pelo professor.</p>
<h2 id="utilização--compilação">Utilização / Compilação</h2>
<p>Para compilar as aplicações necessárias simplesmente é necessário efectuar o comando:</p>
<pre class=" language-shell"><code class="prism  language-shell">$ make
</code></pre>
<p>Para efectuar a importação do ficheiro fornecido utilizamos o comando abaixo.</p>
<pre class=" language-shell"><code class="prism  language-shell">utilizador@lesi-ipca:~/PL$ ./bin/import &lt; test_file.tsv
[...]
Comment Detected: ### tconst    titleType       primaryTitle    originalTitle   isAdult startYear       endYear runtimeMinutes  genres
[...]
Inserts Movies  Actors
[...]
Comment Detected: ###  nconst   primaryName     birthYear       deathYear       primaryProfession       knownForTitles
[...]
.\N\N\N\N\N...
[...]
 Movies:6223386 
 Actors:9626431 
utilizador@lesi-ipca:~/PL$ ls -lah
[...]
-rw-r--r--  1 utilizador  utilizador       3,1G out 23 23:28 database.db
[...]
utilizador@lesi-ipca:~/PL$
</code></pre>
<p>Para efectuarmos a listagem do pedido apenas teremos de executar a aplicação display como mostrado abaixo:</p>
<pre class=" language-shell"><code class="prism  language-shell">utilizador@lesi-ipca:~/PL$ ./bin/display
Showing info from database

* Chris Bailey
* Daniel Torres
         - Walkin' the Way
* David Jewell
* Jennifer Watkins
         - Go Time!
         - Mark
* Jesús Daniel Torres
* Julia Lawson
         - Hlala Kwabafileyo
         - Triptiek II
* Oscar Silva
* Reggie Bush
         - Bad Jokes
         - Simms &amp; Lefkoe: The Show
         - Walking on Dead Fish
* Shiela Martin
* Stefania Zadra
* Ursula Gehrmann
utilizador@lesi-ipca:~/PL$ 
</code></pre>
<p>Após testes feito em uma máquina virtual Ubuntu com 8Gb de RAM verificamos que o tratamento do ficheiro fornecido pelo professor e colocação desses dados em base de dados demorou:</p>
<ul>
<li>Filmes - 4 Minutos</li>
<li>Actores - 20 Minutos</li>
</ul>
<h2 id="estrutura-de-flex">Estrutura de flex</h2>
<h3 id="extração-de-filmes">Extração de Filmes</h3>
<h4 id="resumo">Resumo</h4>
<p>O reconhecimento dos dados referentes a filmes e séries do ficheiro de testes fornecido pelo professor faz-se através prefixo <strong><code>tt</code></strong> sendo este seguido por uma sequência finita de algarismos e a cada <em>tabulação</em> é encontrada uma característica referente ao filme (p.ex. título, se é para adultos, etc).</p>
<p>Inicialmente, para reconhecer no ficheiro os dados referentes a filmes e séries foi usada a expressão <strong><code>^tt</code></strong> que permite identificar, irrevogavelmente que aquela string possui dados referentes a filmes e séries.<br>
Após reconhecer-la é necessário identificar dentro da string os diversos dados que caracterizam o filme. Para tal foi definido o seguinte bloco de instruções com a finalidade ir guardando os dados referentes a um filme antes de o inserir na base de dados.</p>
<pre class=" language-c"><code class="prism  language-c">    tmp_movie<span class="token punctuation">.</span>movie_id <span class="token operator">=</span> <span class="token string">""</span><span class="token punctuation">;</span>
    tmp_movie<span class="token punctuation">.</span>titleType <span class="token operator">=</span> <span class="token string">""</span><span class="token punctuation">;</span>
    tmp_movie<span class="token punctuation">.</span>primaryTitle <span class="token operator">=</span> <span class="token string">""</span><span class="token punctuation">;</span>
    tmp_movie<span class="token punctuation">.</span>originalTitle <span class="token operator">=</span> <span class="token string">""</span><span class="token punctuation">;</span>
    tmp_movie<span class="token punctuation">.</span>isAdult <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>
    tmp_movie<span class="token punctuation">.</span>startYear <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>
    tmp_movie<span class="token punctuation">.</span>endYear <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>
    tmp_movie<span class="token punctuation">.</span>runtimeMinutes <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>
</code></pre>
<p>Após a iniciação dessas variáveis, é necessário entrar num modo que permita reconhecer padrões apenas sobre a string reconhecida acima. Para tal usa-se o comando <strong>BEGIN(MOVIE_x)</strong> sendo x substituído pelo campo que pretendemos reconhecer.</p>
<p>O primeiro dado a reconhecer é o ID do filme. Para tal foi usada a expressão <strong><code>[0-9]+\t</code></strong> que permite reconhecer a cadeia de algarismos que são precedidas por tt e que terminam numa tabulação.<br>
Após esse reconhecimento, segue-se um BEGIN que permite reconhecer qual o tipo de conteúdo (p. ex. Filme, série, etc).<br>
O reconhecimento desse dado é obtido através da expressão <strong><code>[^\t]+\t</code></strong>. Essa expressão permite identificar que, entre a tabulação reconhecida pela expressão anterior até à próxima tabulação, o dado reconhecido será o que identifica o tipo de conteúdo.</p>
<p>Analogamente ao que foi definido para o campo que identifica o tipo de conteúdo, os restantes campos a reconhecer seguem a mesma expressão de reconhecimento, no entanto, a identificação do campo género carece de uma ligeira alteração na expressão.</p>
<p>De forma a separar os generos dos filmes que estão divididos por <strong>([,] - Virgulas)</strong> é efectuada a separação da seguinte forma:<br>
A expressão abaixo encontra tudo o que não tenha um &lt;[tab]&gt;, &lt;[virgula]&gt; e termine com uma &lt;[virgula]&gt;</p>
<pre class=" language-regexp"><code class="prism  language-regexp">[^\t\,])+\,
</code></pre>
<p>Por fim este ciclo é terminado ao encontrar um &lt;[enter]&gt; para o caso de ser filme.</p>
<h4 id="diagrama">Diagrama</h4>
<p><img src="https://github.com/nargotik/PL/raw/master/images/WC_Movie.png" alt="Diagrama Movie"></p>
<hr>
<h3 id="extração-de-actores">Extração de Actores</h3>
<h4 id="resumo-1">Resumo</h4>
<p>O reconhecimento dos dados referentes a actores do ficheiro de testes fornecido pelo professor faz-se através prefixo <strong><code>nm</code></strong> sendo este seguido por uma sequência finita de algarismos e a cada <em>tabulação</em> é encontrada uma característica referente ao actor (p.ex. nome, data de nascimento e falecimento, etc).</p>
<p>Inicialmente, para reconhecer no ficheiro os dados referentes a actores foi usada a expressão <strong><code>^nm</code></strong> que permite identificar, irrevogavelmente que aquela linha possui dados referentes a actores.<br>
Após reconhecer-la é necessário identificar dentro da string os diversos dados que caracterizam o actor. Para tal foi definido o seguinte bloco de instruções com a finalidade ajudar ir guardando os dados referentes a um actor antes de o interir na base de dados.</p>
<pre class=" language-c"><code class="prism  language-c">    tmp_actor<span class="token punctuation">.</span>actor_id <span class="token operator">=</span> <span class="token string">""</span><span class="token punctuation">;</span>
    tmp_actor<span class="token punctuation">.</span>primaryName <span class="token operator">=</span> <span class="token string">""</span><span class="token punctuation">;</span>
    tmp_actor<span class="token punctuation">.</span>birthYear <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>
    tmp_actor<span class="token punctuation">.</span>deathYear <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span>
</code></pre>
<p>Após a iniciação dessas variáveis, é necessário entrar num modo que permita reconhecer padrões apenas sobre a string reconhecida acima. Para tal usa-se o comando <strong>BEGIN(ACTOR_x)</strong> sendo x substituído pelo campo que pretendemos reconhecer.</p>
<p>O primeiro dado a reconhecer é o ID do actor. Para tal foi usada a expressão <strong><code>[0-9]+\t</code></strong> que permite reconhecer a cadeia de algarismos que são precedidas por nm e que terminam numa tabulação.<br>
Após esse reconhecimento, segue-se um BEGIN que permite reconhecer qual o nome do actor.<br>
O reconhecimento desse dado é obtido através da expressão <strong><code>[^\t]+\t</code></strong>. Essa expressão permite identificar que, entre a tabulação reconhecida pela expressão anterior até à próxima tabulação, o dado reconhecido será o que identifica o nome do actor.<br>
Analogamente ao que foi definido para o campo que identifica o nome do actor, os campos data de nascimento e de falecimento serão reconhecidos através da mesma expressão de reconhecimento, no entanto, a identificação do campo profissão principal e títulos pelos quais são reconhecidos carecem de uma ligeira alteração na expressão.</p>
<p>De forma a separar as profissões e os filmes que estão divididos por <strong>([,] - Virgulas)</strong> é efectuada a separação da seguinte forma:<br>
A expressão abaixo econtra tudo o que não tenha um &lt;[tab]&gt;, &lt;[virgula]&gt; e termine com uma &lt;[virgula]&gt;</p>
<pre class=" language-regexp"><code class="prism  language-regexp">[^\t\,])+\,
</code></pre>
<p>Por fim este ciclo é terminado ou ao encontrar um &lt;[tab]&gt; ou um &lt;[enter]&gt; para o caso de ser filme.</p>
<h4 id="diagrama-1">Diagrama</h4>
<p><img src="https://github.com/nargotik/PL/raw/master/images/WC_Actor.png" alt="Diagrama Actor"></p>
<hr>
<h2 id="estrutura-de-base-de-dados">Estrutura de Base de dados:</h2>
<pre class=" language-sql"><code class="prism  language-sql"><span class="token keyword">DROP</span> <span class="token keyword">TABLE</span> <span class="token keyword">IF</span> <span class="token keyword">EXISTS</span> movies<span class="token punctuation">;</span>
<span class="token keyword">CREATE</span> <span class="token keyword">TABLE</span> movies <span class="token punctuation">(</span>
    movie_id <span class="token keyword">TEXT</span> <span class="token keyword">PRIMARY</span> <span class="token keyword">KEY</span><span class="token punctuation">,</span>
    titleType <span class="token keyword">TEXT</span> <span class="token operator">NOT</span> <span class="token boolean">NULL</span><span class="token punctuation">,</span>
    primaryTitle <span class="token keyword">TEXT</span> <span class="token operator">NOT</span> <span class="token boolean">NULL</span><span class="token punctuation">,</span>
    originalTitle <span class="token keyword">TEXT</span> <span class="token operator">NOT</span> <span class="token boolean">NULL</span><span class="token punctuation">,</span>
    isAdult <span class="token keyword">INTEGER</span> <span class="token operator">NOT</span> <span class="token boolean">NULL</span><span class="token punctuation">,</span>
    startYear <span class="token keyword">INTEGER</span> <span class="token operator">NOT</span> <span class="token boolean">NULL</span><span class="token punctuation">,</span>
    endYear <span class="token keyword">INTEGER</span> <span class="token operator">NOT</span> <span class="token boolean">NULL</span><span class="token punctuation">,</span>
    runtimeMinutes <span class="token keyword">INTEGER</span> <span class="token operator">NOT</span> <span class="token boolean">NULL</span>
<span class="token punctuation">)</span><span class="token punctuation">;</span>

<span class="token keyword">DROP</span> <span class="token keyword">TABLE</span> <span class="token keyword">IF</span> <span class="token keyword">EXISTS</span> movies_genres<span class="token punctuation">;</span>
<span class="token keyword">CREATE</span> <span class="token keyword">TABLE</span> movies_genres <span class="token punctuation">(</span>
    movie_id <span class="token keyword">TEXT</span><span class="token punctuation">,</span>
    genre <span class="token keyword">TEXT</span><span class="token punctuation">,</span>
    <span class="token keyword">PRIMARY</span> <span class="token keyword">KEY</span> <span class="token punctuation">(</span>movie_id <span class="token punctuation">,</span> genre<span class="token punctuation">)</span>
<span class="token punctuation">)</span><span class="token punctuation">;</span>

<span class="token keyword">DROP</span> <span class="token keyword">TABLE</span> <span class="token keyword">IF</span> <span class="token keyword">EXISTS</span> actors<span class="token punctuation">;</span>
<span class="token keyword">CREATE</span> <span class="token keyword">TABLE</span> actors <span class="token punctuation">(</span>
    actor_id <span class="token keyword">TEXT</span> <span class="token keyword">PRIMARY</span> <span class="token keyword">KEY</span><span class="token punctuation">,</span>
    primaryName <span class="token keyword">TEXT</span> <span class="token operator">NOT</span> <span class="token boolean">NULL</span><span class="token punctuation">,</span>
    birthYear <span class="token keyword">INTEGER</span> <span class="token operator">NOT</span> <span class="token boolean">NULL</span><span class="token punctuation">,</span>
    deathYear <span class="token keyword">INTEGER</span> <span class="token boolean">NULL</span>
<span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token keyword">CREATE</span> <span class="token keyword">INDEX</span> idx_name <span class="token keyword">ON</span> actors <span class="token punctuation">(</span>primaryName<span class="token punctuation">)</span><span class="token punctuation">;</span>

<span class="token keyword">DROP</span> <span class="token keyword">TABLE</span> <span class="token keyword">IF</span> <span class="token keyword">EXISTS</span> actors_profession<span class="token punctuation">;</span>
<span class="token keyword">CREATE</span> <span class="token keyword">TABLE</span> actors_profession <span class="token punctuation">(</span>
    actor_id <span class="token keyword">TEXT</span><span class="token punctuation">,</span>
    profession <span class="token keyword">TEXT</span><span class="token punctuation">,</span>
    <span class="token keyword">PRIMARY</span> <span class="token keyword">KEY</span> <span class="token punctuation">(</span>actor_id <span class="token punctuation">,</span> profession<span class="token punctuation">)</span>
<span class="token punctuation">)</span><span class="token punctuation">;</span>

<span class="token keyword">DROP</span> <span class="token keyword">TABLE</span> <span class="token keyword">IF</span> <span class="token keyword">EXISTS</span> actors_movies<span class="token punctuation">;</span>
<span class="token keyword">CREATE</span> <span class="token keyword">TABLE</span> actors_movies <span class="token punctuation">(</span>
    actor_id <span class="token keyword">TEXT</span><span class="token punctuation">,</span>
    movie_id <span class="token keyword">TEXT</span><span class="token punctuation">,</span>
    <span class="token keyword">PRIMARY</span> <span class="token keyword">KEY</span> <span class="token punctuation">(</span>actor_id <span class="token punctuation">,</span> movie_id <span class="token punctuation">)</span>
<span class="token punctuation">)</span><span class="token punctuation">;</span>
</code></pre>
<h2 id="conclusão">Conclusão</h2>
<p>Podemos mostrar desta forma a importância das expressões regulares e aplicações do género do flex pois conseguimos tratar de um enorme ficheiro com 18 milhões de registos e colocar numa base de dados para tratamento posterior e armazenamento dos dados.</p>
<p>Hoje em dia cada vez mais há necessidades de migração de sistemas antigos ou de dados para sistemas organizados do género de bases de dados e podemos utilizar esta ferramenta flex como outras ferramentas que utilizem expressões regulares.</p>
<p>Assim sendo tarefas como data minning podem ser muito utilizadas com o uso de expressões regulares.</p>
<p>Abaixo mostramos alguns exemplo de dados complexos que podemos retirar depois de ter a informação normalizada.</p>
<h4 id="exemplos-de-extração-de-dados">Exemplos de extração de dados:</h4>
<p>Se quisermos saber o número de actores que participaram em filmes de drama realizados em 2012<br>
Bastará correr esta Query SQL.</p>
<pre class=" language-sql"><code class="prism  language-sql"><span class="token keyword">SELECT</span> <span class="token function">Sum</span><span class="token punctuation">(</span>filmes<span class="token punctuation">)</span> 
<span class="token keyword">FROM</span>   <span class="token punctuation">(</span> 
                <span class="token keyword">SELECT</span>   <span class="token function">Count</span><span class="token punctuation">(</span><span class="token operator">*</span><span class="token punctuation">)</span> <span class="token keyword">AS</span> filmes 
                <span class="token keyword">FROM</span>     movies<span class="token punctuation">,</span> 
                         movies_genres<span class="token punctuation">,</span> 
                         actors<span class="token punctuation">,</span> 
                         actors_movies 
                <span class="token keyword">WHERE</span>    actors_movies<span class="token punctuation">.</span>movie_id <span class="token operator">=</span> movies<span class="token punctuation">.</span>movie_id 
                <span class="token operator">AND</span>      actors<span class="token punctuation">.</span>actor_id <span class="token operator">=</span> actors_movies<span class="token punctuation">.</span>actor_id 
                <span class="token operator">AND</span>      movies<span class="token punctuation">.</span>movie_id <span class="token operator">=</span> movies_genres<span class="token punctuation">.</span>movie_id 
                <span class="token operator">AND</span>      movies_genres<span class="token punctuation">.</span>genre <span class="token operator">=</span> <span class="token string">"drama"</span> 
                <span class="token operator">AND</span>      movies<span class="token punctuation">.</span>startyear <span class="token operator">=</span> <span class="token number">2012</span> 
                <span class="token keyword">GROUP</span> <span class="token keyword">BY</span> actors<span class="token punctuation">.</span>actor_id<span class="token punctuation">)</span> <span class="token number">a</span><span class="token punctuation">;</span>
</code></pre>
<h2 id="bibliografia">Bibliografia</h2>
<ul>
<li><a href="https://github.com/westes/flex">GitHub Flex</a></li>
</ul>

