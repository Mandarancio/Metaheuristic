<TeXmacs|1.99.4>

<style|<tuple|generic|british>>

<\body>
  <doc-data|<\doc-title>
    TP7: Genetic Programming
  </doc-title>|<doc-author|<\author-data|<author-name|Martino Ferrari>>
    \;
  </author-data>>>

  <\section>
    Expression Search
  </section>

  <with|color|red|?? Non ? che sono sicuro di avere capito l'incipit ...
  forse:<space|1em>Si puo' andare bene, a te non va ancora bene??>

  Genetic Programming is effectively used for building new mathematical
  expressions, providing solution to a problem, through evolution. Any new
  expression is built from two predefined sets, one of operators and
  functions (called <em|function set>), and a second of constants and
  variables (called <em|terminal set>). The expression length can be fixed or
  variable but, in our exercise, we will consider the fixed-length case only.

  In particular, in our TP we will study the problem of a Boolean expression
  of four variables using only the <around*|[|<math|\<wedge\>,\<vee\>,<wide|\<vee\>|\<dot\>>,\<neg\>>|]>
  operators in the function set and the variables
  <math|<around*|[|x<rsub|1>,x<rsub|2>,x<rsub|3>,x<rsub|4>|]>> in the
  terminal set. The truth table of the desired expression, that will be used
  as <em|test set>, is shown in table 1.

  <center|<small-table|<tabular|<tformat|<cwith|1|1|1|-1|cell-background|pastel
  blue>|<cwith|2|-1|1|4|cell-halign|c>|<cwith|2|-1|5|5|cell-background|pastel
  green>|<cwith|2|-1|5|5|cell-lborder|1ln>|<cwith|2|-1|4|4|cell-rborder|1ln>|<cwith|1|1|5|5|cell-lborder|1ln>|<cwith|1|1|4|4|cell-rborder|1ln>|<cwith|2|-1|5|5|cell-halign|c>|<cwith|1|1|1|-1|cell-bborder|1ln>|<cwith|2|2|1|-1|cell-tborder|1ln>|<cwith|1|1|1|-1|cell-tborder|1ln>|<cwith|17|17|1|-1|cell-bborder|1ln>|<cwith|1|-1|1|1|cell-lborder|1ln>|<cwith|1|-1|5|5|cell-rborder|1ln>|<cwith|3|3|1|4|cell-background|pastel
  grey>|<cwith|9|9|1|4|cell-background|pastel
  grey>|<cwith|11|11|1|4|cell-background|pastel
  grey>|<cwith|11|11|5|5|cell-background|#79b500>|<cwith|9|9|5|5|cell-background|#79b500>|<cwith|3|3|5|5|cell-background|#79b500>|<table|<row|<cell|<math|x<rsub|1>>>|<cell|<math|x<rsub|2>>>|<cell|<math|x<rsub|3>>>|<cell|<math|x<rsub|4>>>|<cell|<math|f<around*|(|x|)>>>>|<row|<cell|0>|<cell|0>|<cell|0>|<cell|0>|<cell|0>>|<row|<cell|0>|<cell|0>|<cell|0>|<cell|1>|<cell|1>>|<row|<cell|0>|<cell|0>|<cell|1>|<cell|0>|<cell|0>>|<row|<cell|0>|<cell|0>|<cell|1>|<cell|1>|<cell|0>>|<row|<cell|0>|<cell|1>|<cell|0>|<cell|0>|<cell|0>>|<row|<cell|0>|<cell|1>|<cell|0>|<cell|1>|<cell|0>>|<row|<cell|0>|<cell|1>|<cell|1>|<cell|0>|<cell|0>>|<row|<cell|0>|<cell|1>|<cell|1>|<cell|1>|<cell|1>>|<row|<cell|1>|<cell|0>|<cell|0>|<cell|0>|<cell|0>>|<row|<cell|1>|<cell|0>|<cell|0>|<cell|1>|<cell|1>>|<row|<cell|1>|<cell|0>|<cell|1>|<cell|0>|<cell|0>>|<row|<cell|1>|<cell|0>|<cell|1>|<cell|1>|<cell|0>>|<row|<cell|1>|<cell|1>|<cell|0>|<cell|0>|<cell|0>>|<row|<cell|1>|<cell|1>|<cell|0>|<cell|1>|<cell|0>>|<row|<cell|1>|<cell|1>|<cell|1>|<cell|0>|<cell|0>>|<row|<cell|1>|<cell|1>|<cell|1>|<cell|1>|<cell|0>>>>>|Truth
  table of <math|f<around*|(|x|)>>>>

  Searching for a minimized expression by means of a Karnaugh map brought me
  to the following possible solution:

  <\equation*>
    <around*|\<nobracket\>|f<around*|(|x<rsub|>|)>=x<rsub|4>\<wedge\>*<around*|(||\<nobracket\>><around*|(|x<rsub|1>\<wedge\>\<neg\><around*|(|x<rsub|2>\<wedge\>
    x<rsub|3>|)>|)>\<vee\> \<neg\><around*|(|x<rsub|2><wide|\<vee\>|\<dot\>>
    x<rsub|3>|)>|)>
  </equation*>

  In this case the symbol set is composed by
  <math|<around*|[|\<wedge\>,\<vee\>,<wide|\<vee\>|\<dot\>>,\<neg\>,x<rsub|1>,x<rsub|2>,x<rsub|3>,x<rsub|4>|]>>.
  The length of the solution will be set to the minimum found, i.e. 13
  symbols. Each solution <math|s\<in\>S> will be a sequence of 13 symbols
  taken from the symbol set, meaning a solution space <math|S> composed by
  13<math|<rsup|10>> (<math|\<sim\>10<rsup|12>>) possible combinations of the
  symbol set.\ 

  \;

  <section|Genetic Programming>

  The Genetic Programming (<strong|GP>) technique was first developed in the
  90's from the Genetic Algorithm (<strong|GA>) by <em|J.R. Koza et al.>. The
  logic behind the <strong|GP> is the same as in the <strong|GA>: through a
  process of selection, crossover and mutation, generation by generation, the
  research spac<strong|>e <math|S> will be efficiently explored and an
  optimal (or acceptable) solution found. The individuals in <strong|GP> are
  not just values or data but simple programs.

  In order to deal with the need of a reliable syntax capable to resist to
  crossover and mutation processes, the proposed solution are two:

  <\enumerate>
    <item><strong|S-Expression>: where the program is represented as a tree

    <item><strong|Post-Fix>: where the program is represented as a list and
    the execution is based on a stack machine
  </enumerate>

  In our case, we will use the second option that gives us the possibility to
  simplify the implementation by fixing the size of the program.\ 

  A program written in post-fix syntax will look something like <verbatim|"2
  NEG X SIN Y DIV MUL"> that represent <math|-2\<cdot\><frac|sin<around*|(|x|)>|y>>.
  The program is built taking the symbols from 2 sets:

  <\enumerate>
    <item><strong|Function-Set>: the ensemble of all operators and functions

    <item><strong|Terminal-Set>: the ensemble of all constants and variables
  </enumerate>

  All the operators and functions implemented in the function-set must be
  robust to errors, such that any randomly generated program could always be
  executed. As policy I choose to skip functions and operators that don't
  have enough operands or terms (e.g. <verbatim|"X1
  AND"><math|\<rightarrow\>><verbatim|"X1">), and to return <em|false> if at
  the end of the execution the stack is empty (e.g. <verbatim|"AND
  AND"><math|\<rightarrow\>><em|false>).\ 

  The processes of selection, crossover and mutation are very similar to the
  ones in the <strong|GA>.

  The <strong|selection> strategies are the same proposed for the
  <strong|GA>, and in our case we will use a 2-Tournament.\ 

  The <strong|crossover> will be done using the fix-point crossover
  technique.

  The <strong|mutation> will be done by exchanging each gene with a random
  symbol, with a given probability (and equal probability of being taken from
  either the function or the terminal set).

  To recap, the <strong|GP> has 4 main driving parameters:

  <\itemize>
    <item>The population size <math|p<rsub|size>>

    <item>The program length <math|p<rsub|l>>

    <item>The crossover probability <math|p<rsub|c>>

    <item>The mutation probability <math|p<rsub|m>>
  </itemize>

  \ \ The value of each of them will be discussed in the result section.

  <section|GP and Boolean Expression>

  As for any other metaheurstic we have to define few elements:

  <\itemize>
    <item>The research space <math|S>

    <item>The start solution <math|s<rsub|0>>

    <item>The fitness function <math|f<around*|(|s<rsub|i>|)>>

    <item>The neighbourhood of a solution <math|N<around*|(|s<rsub|i>|)>>

    <item>The exploration operator <math|U>

    <item>The end condition\ 
  </itemize>

  The research space <math|S> was already defined in Section 1. The start
  solutions (as the <strong|GP> is a population-based algorithm) are randomly
  generated from <math|S>.

  To compute the fitness <math|f<around*|(|s<rsub|i>|)>> of a solution
  <math|s>, I choose to take into account 3 factors:

  <\enumerate>
    <item>The number of results that differ from the expected ones taken from
    the <em|test-set> (<math|d<rsub|c><around*|(|s<rsub|i>|)>>).

    <item>The number of errors encountered in the execution (with a penalty
    of the size of the program for the programs with empty stack at the end
    of the execution) of the programs (<math|e<rsub|c><around*|(|s<rsub|i>|)>>),
    e.g. the program <verbatim|"AND AND NOT"> contains 3 errors and will have
    a penalty of 3.

    <item>The number of elements left on the stack after the execution
    (<math|p<rsub|c><around*|(|s<rsub|i>|)>>), e.g. the program <verbatim|"X1
    X2 X3"> will leave 2 elements in the stack.
  </enumerate>

  Finally the fitness is computed as follows:

  <\equation*>
    f<around*|(|s<rsub|i>|)>=d<rsub|c><around*|(|s<rsub|i>|)>\<cdot\><around*|(|1+e<rsub|c><around*|(|s<rsub|i>|)>+p<rsub|c><around*|(|s<rsub|i>|)>|)>
  </equation*>

  In this way the selection will not only favour the programs with more
  correct results but also the ones more synthetically correct. The range of
  this function is from 0 (all the results as in the test set) <math|down to
  -n<rsub|variables><rsup|2>\<cdot\><around*|(|p<rsub|l><rsup|2>+p<rsub|l><rsub|>|)>>.

  The neighbourhood <math|N<around*|(|s<rsub|i>|)>> of a solution
  <math|s<rsub|i>> is virtually the full research space <math|S>, as the
  research operator may create any solution <math|s<rsub|i+1>>.

  The research operator <math|U>, as in the <strong|GA>, is the composition
  of the <em|Selection, Crossover> and <em|Mutation> operations.

  Finally the end condition will be <math|g<rsub|max>> (a 5th driving
  parameter), the number of generations to reach.\ 

  <section|Implementation>

  The implementation is based on the Python skeleton provided, where the
  research operator was already implemented. To speed up the execution of the
  code I choose to change the program representation from a string list to a
  function list, to avoid the use of a dictionary.

  Since, however, the performance of the code was still quite poor, I choose
  to re-implement the code in C++ (maintain the same structure,
  <verbatim|main.cpp>), gaining a factor of about <math|\<sim\>25> in the
  execution time.

  A further variable-length variant will be discussed in Section 6.

  <section|Results>

  Before analyzing the performance and results of the algorithm, I tried to
  better understand the problem and its research space <math|S>.

  To do so, I generated a landscape with 1000 randomly-generated programs of
  length 13, with the results shown in Figure 1.

  <center|<small-figure|<image|landscape.png|383pt|287pt||>|1000
  random-sample landscape>>

  In Fig. 1, it's possible to see that the landscape follow a Gaussian
  distribution with some asymmetry close to the upper limit.
  <with|color|red|(non è per niente strano ... è limitata superiormente e il
  limite superiore è in linea di principio un valore osservabile ...) si ma
  e' limitata anche inferiormente.>. In particular these 1000 events have
  average -670.5, STD 357.7, best value -5 and worst -1885.

  After this first observation, I decided to study the influence of the
  parameters <math|p<rsub|m>> and <math|p<rsub|c>> on the performance of the
  <strong|GP>: I varied both and for each variation I executed 100 times,
  with <math|p<rsub|size>=30>, <math|g<rsub|max>=100> and
  <math|p<rsub|length>=13>, the algorithm. The results are shown in Figures 2
  and 3.

  <small-figure|<image|pmVsall.png|383pt|215pt||>|Fitness and Number of Best
  Solutions Vs <math|p<rsub|m>> (<math|p<rsub|c>=0.5>)<center|>>

  <small-figure|<image|pcVsall.png|383pt|215pt||>|Fitness and STD Vs
  <math|p<rsub|c>> (<math|p<rsub|m>=0.08>)>

  The plots enlighten interesting features: the <math|p<rsub|m>> factor
  strongly affects the performance of the <strong|GP>, even very small
  variations of it may radically change the results. The best performance in
  both average fitness and number of optimum solutions is found around 0.08
  and, with <math|p<rsub|m>\<gtr\>0.4>, it becomes hard or close to
  impossible to find any optimum solution. It's important to notice that it
  is not possible to find optimum solutions also with <math|p<rsub|m>=0>.

  Quite the opposite, the influence of <math|p<rsub|c>> is much less
  important, the trend of the average fitness is flat <with|color|red|?? non
  capisco ma mancano i grafici ??. Guarda il pdf per i grafici> The only
  small difference is on the fitness STD that decreases with increasing
  <math|p<rsub|c>> (from <math|\<sim\>0.7\<rightarrow\>\<sim\>0.45>).

  The best found combination of parameters is <math|p<rsub|m>=0.08> and
  <math|p<rsub|c>=0.7>.

  Finally I chose to observe the impact of the program length on the
  performance, by varying the length from 6 to 20 and observing the results
  of 100 executions. Figures 4 and 5 \ summarize the experiment.

  <center|<small-figure|<tabular|<tformat|<table|<row|<cell|<image|plVsFit.png|383pt|215pt||>>>>>><center|>|Fitness
  Vs Program Length (<math|p<rsub|m>=0.1,p<rsub|c>=0.5>)>>

  <\center>
    <small-figure|<image|plVsnbest.png|383pt|215pt||>|Number of Optimal
    Solution Vs Program Length (<math|p<rsub|m>=0.1,p<rsub|c>=0.5>) >
  </center>

  <with|color|magenta|The first notable results of this analysis is that my
  implementation of the<strong| GP> is capable to find minimal (shorter)
  solution to the problem than the classical Karnaugh map, as it finds
  solutions with length 10, 11 and 12 (while using the Karnaugh map gave me
  program of length 13).>

  <with|color|magenta|Moreover> from the figures, it's possible to see that,
  even if the research space <math|S> increases with the program length
  <math|p<rsub|l>> (the research space size is <math|8<rsup|p<rsub|l>>>, 8
  being the number of possible symbols), the result quality increases
  <with|color|red|(?? perché dici \Peven if\Q ? Se cerchi bene in uno spazio
  più grande avrai la possibilità di trovare migliori risultati ?? SI Ma
  essendo lo spazio molto piu' grande dovrebbe essere in teoria + difficile
  trovare le soluzioni, invece diventa + facile. Io forse direi: `to see
  that, having a much larger research space, ...\Q)>. In particular, Figure 3
  show a linear trend for the number of optimal solutions found (meaning
  solutions with fitness = 0). It's also noticeable the fact that the
  <strong|GP> is not capable to find any optimal solution with programs
  shorter than 10. However, for length = 9, a large number (close to 90%) of
  the executions finds solutions with fitness -1.

  The reason why the quality of solution increases with the program length is
  the fact that, with more symbols, it's easier to find combinations giving
  the correct results with redundant (e.g. <verbatim|"NOT NOT X1">) or wrong
  (e.g. <verbatim|"NOT X1 AND">) operations, that due to the fitness function
  are not taken into account if the results match the test set
  <with|color|red|??? mi pare abbastanza incomprensibile ? volevo dire che
  come ho costrutio la funzione di fitness se un programma se pure ha degli
  errori ma metcha il test-set avra' fitness 0, quindi con una lunghezza +
  grande sara' in grado trovare sequenze con qualche errore in + ma che
  comunque metchano il test-set>?. This results in a higher number of correct
  possibilities and the trend shown in figure 5. <with|color|red|??? and can
  explain the trend. guarda il plot>

  I performed, as well, tests about the impact of <math|p<rsub|size>> and
  <math|g<rsub|max>> on the performance of the <strong|GP>. As expected,
  increasing <math|p<rsub|size>> or <math|g<rsub|max>> will increase the
  quality of the results (as the overall number of fitness evaluations will
  increase as well as the research space exploration).

  Consequently, I chose as best parameters: <math|p<rsub|size>=100>,
  <math|g<rsub|max>=100>, <math|p<rsub|c>=0.5>, <math|p<rsub|m>=0.08> and I
  analyzed the algorithm performance over 100 execution and with
  <math|p<rsub|length>=6,10,15>. \ 

  <small-figure|<image|run_6.png|383pt|287pt||>|Evaluation with
  <math|p<rsub|l>=6>>

  <small-figure|<image|run_10.png|383pt|287pt||>|Evaluation with
  <math|p<rsub|l>=10>>

  <small-figure|<center|><image|run_15.png|383pt|287pt||>|Evaluation with
  <math|p<rsub|l>=15>>

  As shown in Fig. 6, 7 and 8, my <strong|GP> implementation performs pretty
  well, the overall worst result having fitness -3, and it is capable to find
  solutions with minimum program length (<math|p<rsub|l>=10>)<with|color|magenta|
  smaller than the ones obtained with classical method.> Tables 2 and 3 show
  the numerical results of the previous test and the best programs
  created<center|>.

  \ <big-table|<tabular|<tformat|<cwith|2|-1|1|-1|cell-halign|r>|<cwith|1|1|1|-1|cell-halign|r>|<cwith|1|1|1|-1|cell-background|pastel
  blue>|<cwith|2|-1|1|5|cell-background|#e6e6e6>|<cwith|1|-1|5|5|cell-lborder|0ln>|<cwith|1|-1|4|4|cell-rborder|0ln>|<cwith|1|1|1|-1|cell-bborder|1ln>|<cwith|2|2|1|-1|cell-tborder|1ln>|<cwith|1|1|1|-1|cell-tborder|1ln>|<cwith|4|4|1|-1|cell-bborder|1ln>|<cwith|1|-1|1|1|cell-lborder|1ln>|<cwith|1|1|6|8|cell-tborder|1ln>|<cwith|4|4|6|8|cell-bborder|1ln>|<cwith|1|-1|6|6|cell-lborder|1ln>|<cwith|1|-1|5|5|cell-rborder|1ln>|<cwith|1|-1|8|8|cell-rborder|1ln>|<cwith|1|1|7|7|cell-tborder|1ln>|<cwith|4|4|7|7|cell-bborder|1ln>|<cwith|1|-1|7|7|cell-lborder|1ln>|<cwith|1|-1|6|6|cell-rborder|1ln>|<cwith|1|-1|7|7|cell-rborder|1ln>|<cwith|1|-1|8|8|cell-lborder|1ln>|<table|<row|<cell|<math|p<rsub|l>>>|<cell|<math|p<rsub|c>>>|<cell|<math|p<rsub|m>>>|<cell|<math|p<rsub|size>>>|<cell|<math|g<rsub|max>>>|<cell|Average
  Fitness>|<cell|STD>|<cell|Best >>|<row|<cell|6>|<cell|0.7>|<cell|0.08>|<cell|100>|<cell|100>|<cell|-1.12>|<cell|0.44>|<cell|-1>>|<row|<cell|10>|<cell|0.7>|<cell|0.08>|<cell|100>|<cell|100>|<cell|-0.92>|<cell|0.22>|<cell|0>>|<row|<cell|15>|<cell|0.7>|<cell|0.08>|<cell|100>|<cell|100>|<cell|-0.78>|<cell|0.45>|<cell|0>>>>>|Fitness
  Table>

  <big-table|<tabular|<tformat|<cwith|1|1|1|-1|cell-background|pastel
  blue>|<cwith|1|1|1|-1|cell-tborder|1ln>|<cwith|1|1|1|-1|cell-bborder|1ln>|<cwith|2|2|1|-1|cell-tborder|1ln>|<cwith|1|1|1|1|cell-tborder|1ln>|<cwith|7|7|1|1|cell-bborder|1ln>|<cwith|1|-1|1|1|cell-lborder|1ln>|<cwith|1|1|2|-1|cell-tborder|1ln>|<cwith|7|7|2|-1|cell-bborder|1ln>|<cwith|1|-1|2|2|cell-lborder|1ln>|<cwith|1|-1|1|1|cell-rborder|1ln>|<cwith|6|6|1|-1|cell-background|pastel
  cyan>|<cwith|4|4|1|-1|cell-background|pastel
  cyan>|<cwith|2|2|1|-1|cell-background|pastel
  cyan>|<cwith|1|1|3|3|cell-tborder|1ln>|<cwith|7|7|3|3|cell-bborder|1ln>|<cwith|1|-1|3|3|cell-lborder|1ln>|<cwith|1|-1|2|2|cell-rborder|1ln>|<cwith|1|-1|3|3|cell-rborder|1ln>|<cwith|2|-1|3|3|cell-halign|r>|<table|<row|<cell|<math|p<rsub|l>>>|<cell|Program
  and Expression>|<cell|<math|f<around*|(|x|)>>>>|<row|<cell|6>|<cell|<verbatim|X2
  X3 OR NOT X4 AND>>|<cell|-1>>|<row|<cell|>|<cell|<math|\<neg\><around*|(|x<rsub|2>\<vee\>x<rsub|3>|)>\<wedge\>x<rsub|4>>>|<cell|>>|<row|<cell|10>|<cell|<verbatim|X4
  X2 X1 AND X2 X3 XOR OR NOT AND>>|<cell|0>>|<row|<cell|>|<cell|<math|\<neg\>*<around*|(|<around*|(|x<rsub|2>\<wedge\>x<rsub|1>|)>\<vee\><around*|(|x<rsub|2><wide|\<vee\>|\<dot\>>x<rsub|3>|)>|)>\<wedge\>x<rsub|4>>>|<cell|>>|<row|<cell|15>|<cell|<verbatim|X2
  X3 X2 X1 <with|color|black|AND> AND X3 X4 XOR NOT XOR
  <with|color|black|XOR> NOT X4 AND>>|<cell|0>>|<row|<cell|>|<cell|<math|\<neg\>*<around*|(|<around*|(|x<rsub|2>\<wedge\>x<rsub|3>|)><wide|\<vee\>|\<dot\>><around*|(|<around*|(|x<rsub|2>\<exterior\>x<rsub|1>|)><wide|\<vee\>|\<dot\>>\<neg\><around*|(|x<rsub|3><wide|\<vee\>|\<dot\>>x<rsub|4>|)>|)>|)>\<wedge\>x<rsub|4>>>|<cell|>>>>>|Program
  Table>

  <section|Variable Length Implementation>

  An interesting variation could be a variable program length implementation.
  In this way the algorithm should be capable of finding the minimal program
  length without a previous analysis of the problem. For that, I suggest two
  modification:

  <\itemize>
    <item>A non length-conservative crossover <with|color|red|(o \PA length
    non-conservative crossover\Q ?? bo, cosa suona meglio?)>

    <item>A fitness function modification
  </itemize>

  To be able to have different program lengths within the same population, I
  suggest that the crossover be modified by exchanging the portion of the
  code with same size, e.g.:

  fix-point : 2

  <math|p<rsub|1>:> <verbatim|"X1 X2 \| AND NOT X4 OR"> , <math|p<rsub|2>:>
  <verbatim|"X3 NOT \| X4 XOR X3 AND">

  <math|p<rsub|1><rprime|'>:> <verbatim|"X1 X2 X3 NOT">,
  <math|p<rsub|2><rprime|'>:> <verbatim|"AND NOT X4 OR X4 XOR X3 AND">

  In this way it would be possible to generate a population with variable
  length starting from a uniform population.

  Now the fitness function should take into account the program length, to
  promote the shortest programs:

  <\equation*>
    f<around*|(|s<rsub|i>|)>=d<rsub|c><around*|(|s<rsub|i>|)>\<cdot\><around*|(|1+e<rsub|c><around*|(|s<rsub|i>|)>+p<rsub|c><around*|(|s<rsub|i>|)>|)>\<cdot\>l<around*|(|s<rsub|i>|)>
  </equation*>

  being <math|l<around*|(|s<rsub|i>|)>> the length of <math|s<rsub|i>>.

  <section|Project structure>

  <tabular|<tformat|<table|<row|<cell|<math|>gp.py>|<cell|<strong|GP>
  implementation in python>>|<row|<cell|compile.sh>|<cell|is the compilation
  script>>|<row|<cell|src/>|<cell|contains all the source code (above the
  core components)>>|<row|<cell|<math|\<rightarrow\>>/main.cpp>|<cell|<strong|GP>
  implementation in C++>>|<row|<cell|<math|\<rightarrow\>>/main_plot.cpp>|<cell|main
  file with plot>>|<row|<cell|<math|\<rightarrow\>>/landscape.cpp>|<cell|random
  landscape generator>>|<row|<cell|bin/>|<cell|contains all the
  binary>>|<row|<cell|<math|\<rightarrow\>>/gp>|<cell|runs the
  <strong|GP>>>>>>\ 

  The code and the reports can also be found on my github repository:
  <hlink|Metaheuristic|https://github.com/Mandarancio/Metaheuristic>.\ 

  \;
</body>

<\initial>
  <\collection>
    <associate|prog-scripts|python>
  </collection>
</initial>

<\references>
  <\collection>
    <associate|auto-1|<tuple|1|1>>
    <associate|auto-10|<tuple|4|5>>
    <associate|auto-11|<tuple|5|5>>
    <associate|auto-12|<tuple|6|6>>
    <associate|auto-13|<tuple|7|7>>
    <associate|auto-14|<tuple|8|7>>
    <associate|auto-15|<tuple|2|8>>
    <associate|auto-16|<tuple|3|8>>
    <associate|auto-17|<tuple|6|8>>
    <associate|auto-18|<tuple|7|8>>
    <associate|auto-2|<tuple|1|1>>
    <associate|auto-3|<tuple|2|1>>
    <associate|auto-4|<tuple|3|2>>
    <associate|auto-5|<tuple|4|3>>
    <associate|auto-6|<tuple|5|3>>
    <associate|auto-7|<tuple|1|3>>
    <associate|auto-8|<tuple|2|4>>
    <associate|auto-9|<tuple|3|4>>
  </collection>
</references>

<\auxiliary>
  <\collection>
    <\associate|figure>
      <tuple|normal|1000 random-sample landscape|<pageref|auto-7>>

      <tuple|normal|Fitness and Number of Best Solutions Vs
      <with|mode|<quote|math>|p<rsub|m>> (<with|mode|<quote|math>|p<rsub|c>=0.5>)<with|par-mode|<quote|center>|>|<pageref|auto-8>>

      <tuple|normal|Fitness and STD Vs <with|mode|<quote|math>|p<rsub|c>>
      (<with|mode|<quote|math>|p<rsub|m>=0.08>)|<pageref|auto-9>>

      <tuple|normal|Fitness Vs Program Length
      (<with|mode|<quote|math>|p<rsub|m>=0.1,p<rsub|c>=0.5>)|<pageref|auto-10>>

      <tuple|normal|Number of Optimal Solution Vs Program Length
      (<with|mode|<quote|math>|p<rsub|m>=0.1,p<rsub|c>=0.5>)
      |<pageref|auto-11>>

      <tuple|normal|Evaluation with <with|mode|<quote|math>|p<rsub|l>=6>|<pageref|auto-12>>

      <tuple|normal|Evaluation with <with|mode|<quote|math>|p<rsub|l>=10>|<pageref|auto-13>>

      <tuple|normal|Evaluation with <with|mode|<quote|math>|p<rsub|l>=15>|<pageref|auto-14>>
    </associate>
    <\associate|table>
      <tuple|normal|Truth table of <with|mode|<quote|math>|f<around*|(|x|)>>|<pageref|auto-2>>

      <tuple|normal|Fitness Table|<pageref|auto-15>>

      <tuple|normal|Program Table|<pageref|auto-16>>
    </associate>
    <\associate|toc>
      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|1<space|2spc>Expression
      Search> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-1><vspace|0.5fn>

      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|2<space|2spc>Genetic
      Programming> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-3><vspace|0.5fn>

      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|3<space|2spc>GP
      and Boolean Expression> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-4><vspace|0.5fn>

      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|4<space|2spc>Implementation>
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-5><vspace|0.5fn>

      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|5<space|2spc>Results>
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-6><vspace|0.5fn>

      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|6<space|2spc>Variable
      Length Implementation> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-17><vspace|0.5fn>

      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|7<space|2spc>Project
      structure> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-18><vspace|0.5fn>
    </associate>
  </collection>
</auxiliary>