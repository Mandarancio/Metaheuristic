<TeXmacs|1.99.2>

<style|<tuple|generic|italian>>

<\body>
  <section|Simulate Annealing>

  <subsection|Convergenza>

  La convergenza descrive le condizioni sotto le quali una metaeuristica
  trova l'ottimo globale (e non solamente locale).

  Per la ricotta possiamo fare una analisi matematica precisa di questa
  condizione.

  Si può calcolare la probabilità di convergenza. La soluzione trovata sarà
  albitrariamente vicina all'ottimo. con una probabilità ... vicina di 1.

  Questo e' vero se:

  <\itemize>
    <item>Le trasformazioni o movimenti sono reversibili se <math|s
    \<in\>V<around*|(|r|)>> e <math|r \<in\>V<around*|(|s|)>>

    <item>Tutti i punti di <math|S> sono raggiungibili da qualsiasi soluzione
    con un numero finito di trasformazioni

    <item>La temperatura iniziale deve essere elevata

    <item>La temperatura deve scendere lentamente:
    <math|T<around*|(|t|)>\<sim\><frac|C|log<around*|(|t|)>>> dove <math|t>
    e' l'indice dell'iterazione e <math|C> e' una costante che dipende dal
    landscape dell'energia (l'ampiezza delle variazioni di <math|E> tra i
    vicini)

    In pratica <math|C> è sconosciuta, e la diminuzione di temperatura è
    troppo lenta per essere accettabile. Per le applicazioni pratiche ci si
    accontenterà di un ottimo accettabile con tempi molto più rapidi.
  </itemize>

  Illustriamo ora le ipotesi del teorema di convergenza tramite un esempio,
  che ci permetterà di comprendere le nozioni di probabilità di trovare una
  soluzione.

  <with|gr-mode|<tuple|edit|text-at>|gr-frame|<tuple|scale|1cm|<tuple|0.0600638gw|0.110034gh>>|gr-geometry|<tuple|geometry|0.600003par|0.466668par|center>|gr-grid|<tuple|cartesian|<point|0|0>|2>|gr-grid-old|<tuple|cartesian|<point|0|0>|2>|gr-edit-grid-aspect|<tuple|<tuple|axes|none>|<tuple|1|none>|<tuple|10|none>>|gr-edit-grid|<tuple|cartesian|<point|0|0>|2>|gr-edit-grid-old|<tuple|cartesian|<point|0|0>|2>|gr-arrow-end|\<gtr\>|<graphics||<point|1|1>|<with|arrow-end|\<gtr\>|<line|<point|1|1>|<point|0.2|1.0>>>|<text-at|x|<point|1|-0.4>>|<text-at|y|<point|-0.4|1>>|<text-at|0,0|<point|-0.2|-0.3>>|<with|arrow-end|\<gtr\>|<line|<point|1|1>|<point|1.8|1.0>>>|<with|arrow-end|\<gtr\>|<line|<point|1|1>|<point|1.0|1.8>>>|<with|arrow-end|\<gtr\>|<line|<point|1|1>|<point|1.0|0.2>>>|<text-at||<point|1|2>>>>

  <math|<around*|\||S|\|>=n<rsub|x>\<cdot\>*n<rsub|y>>

  <\math>
    S\<subset\>\<bbb-Z\><rsup|2>

    mvt=<around*|{|N,S,W,E|}>
  </math>

  Supponiamo di darci una funzione di energia <math|E<around*|(|x,y|)>>

  Possiamo assegnare ad ogni punto in <math|S> una indice
  <math|i=n<rsub|y><around*|(|y-1|)>+x>

  Nell'esempio <math|y> a 100 valori possibili per <math|i>.

  Ci piacerebbe calcolare la probabiltà di <math|P<around*|(|t,i|)>>, ovvero
  la probabilità che alla <math|t>-sima iterazione la ricotta sia al punto
  <math|i\<in\>S> (con <math|i> l'ottimo globale)

  (per <math|t\<rightarrow\>\<infty\>> ci piacerebbe avere
  <math|P<around*|(|t,i|)>=1>)

  \;

  Possiamo calcolare <math|P<around*|(|t,i|)>> come:

  <math|P<around*|(|t+1,j|)>=<big|sum>P<around*|(|t,i|)>W<rsub|ij><around*|(|t|)>>

  \;

  Dato che la ricotta è un processo Markoviano.

  Qui, <math|W<rsub|ij><around*|(|t|)>> è la probabilità che all'iterazione
  <math|t> si passa da <math|i> a <math|j.>

  <math|W<rsub|ij>> è una matrice di taglia
  <math|n<rsub|x>n<rsub|y>\<times\>n<rsub|x>n<rsub|y>>. (quindi infattibili
  per spazi grandi). E si calcola:

  <\equation*>
    W<rsub|ij><around*|(|t|)>\<nocomma\>\<nocomma\>\<nocomma\>=<around*|{|<tabular|<tformat|<cwith|1|1|1|1|cell-halign|l>|<table|<row|<cell|0>|<cell|
    se j non è un vicino>>|<row|<cell|<frac|1|<around*|\||V|\|>>\<cdot\>P
    <around*|(|E<rsub|i>,E<rsub|j>,T<around*|(|t|)>|)>>|<cell| se j è
    vicino>>>>>|\<nobracket\>>
  </equation*>

  <math|W<rsub|ij>>=<math|1-<big|sum>W<rsub|ij><around*|(|t|)>> (probabilità
  di rigetto)

  \;

  Vogliamo ora calcolare <math|P<around*|(|t,k|)>> in funzione di
  <math|P<around*|(|0,l|)>> che è la probabiltà di scegliere <math|l> come
  punto iniziale della ricotta.

  <\eqnarray*>
    <tformat|<table|<row|<cell|P<around*|(|t,k|)>=<big|sum><rsub|j>P<around*|(|t-1,j|)>W<rsub|jk><around*|(|t-1|)>>|<cell|>|<cell|>>|<row|<cell|=<big|sum><rsub|j><around*|[|<big|sum><rsub|i>P<around*|(|t-2,i|)>W<rsub|ij><around*|(|t-2|)>|]>W<rsub|jk><around*|(|t-1|)>>|<cell|>|<cell|>>|<row|<cell|=<big|sum><rsub|i>P<around*|(|t-2,i|)><big|sum><rsub|j>W<rsub|ij><around*|(|t-2|)>W<rsub|jk><around*|(|t-1|)>>|<cell|>|<cell|Prodotto
    matriciale>>|<row|<cell|=<big|sum><rsub|i>P<around*|(|t-2,i|)><around*|[|W<around*|(|t-2|)>\<times\>W<around*|(|t-1|)>|]><rsub|ik>>|<cell|>|<cell|>>>>
  </eqnarray*>

  \ Iterando questa relazione si trova che:

  <\equation*>
    P<around*|(|t,k|)>=<big|sum><rsub|l>P<around*|(|0,l|)>*\<cdot\>W<around*|(|0,t-1|)><rsub|lk>
  </equation*>

  Dove <math|W<around*|(|0,t-1|)>> è definita come il prodotto delle matrici
  <math|W<around*|(|t<rprime|'>|)>> per <math|t<rprime|'>\<in\><around*|{|0\<ldots\>t-1|}>>.

  Un caso particolare se <math|W<around*|(|0,t-1|)> > tutte le linee sono
  uguali:

  <\equation*>
    W<rsub|lk><around*|(|0,t-1|)>=W<rsub|1k><around*|(|0,t-1|)>=W<rsub|2k><around*|(|0,t-1|)>\<ldots\>
  </equation*>

  In questo caso allora:

  <\equation*>
    P<around*|(|t,k|)>=W<rsub|1k><around*|(|0,t-1|)><big|sum><rsub|l>P<around*|(|0,l|)>=W<rsub|1k><around*|(|0,t-1|)>
  </equation*>

  Questo significa che il punto di partenza è irrilevante.\ 

  <subsection|Guida pratica alla Ricotta>

  Ci resta di precisare:

  <\itemize-dot>
    <item>Come definire la temperatura iniziale

    <item>Quando decidere di abbassare la temperatura (in pratica, non
    abbasseremo la temperatura ad ogni iterazione, ma al contrario faremo
    come illustrato precedentemente)

    <item>Come abbassare la temperatura (di quanto?)

    <item>Quale è la condizione di stop
  </itemize-dot>

  Non c'è una risposta unica a questi problemi, ma ci sono delle
  raccomandazioni generali.

  Per specificare un problema di ricotta, bisogna:

  <\itemize>
    <item>Codificare lo spazio di ricerca <math|S>

    <item>Definire le <underline|trasformazioni> (movimenti) possibili

    <item>Scegliere una soluzione <math|s<rsub|0>> iniziale
  </itemize>

  \;

  <with|font-series|bold|La temperatura iniziale> <math|T<rsub|0>> si
  determina impiricamente attraverso la seguente procedura (partire con
  temperature troppo alte genererà un tempo di ricerca troppo lungo):

  <\enumerate>
    <item>A partire dalla soluzione iniziale <math|s<rsub|0>>, si fanno 100
    trasformazioni casuali.

    <item>Si calcolano la variazioni di energia <math|\<Delta\>E> di questi
    100 campioni casuali

    <item>Si sceglie un tasso di accettazione <math|\<Gamma\><rsub|0>>
    secondo la qualità ipotetica della soluzione iniziale:

    <math|\<Gamma\><rsub|0>>=0.5 se la soluzione iniziale è considerata
    mediocre

    <math|\<Gamma\><rsub|0>>=0.2 se invece è considerata buona

    <item>Si risolve dunque che la temperatura è:\ 

    <\eqnarray*>
      <tformat|<table|<row|<cell|e<rsup|-<frac|\<Lambda\>E|\<Gamma\><rsub|0>>>=\<Gamma\><rsub|0>>|<cell|>|<cell|>>|<row|<cell|\<Rightarrow\>
      <frac|\<Delta\>E|\<Gamma\><rsub|0>>=ln<around*|(|\<Gamma\><rsub|0>|)>>|<cell|>|<cell|>>|<row|<cell|\<Rightarrow\>T<rsub|0>=<frac|\<Delta\>E|ln<around*|(|\<Gamma\><rsub|0>|)>>
      >|<cell|>|<cell|>>>>
    </eqnarray*>
  </enumerate>

  Intuitivamente questo vuole dire che possiamo poter fare dei salti di
  dimensione <math|\<Delta\>E> con una buona probabilità.

  \;

  <with|font-series|bold|I cambiamenti di temperatura>

  In particolare si utilizza la stessa temperatura per diverse iterazioni.

  Si cambia la temperatura nelle seguenti condizioni:

  <\itemize>
    <item>abbiamo accettato 12<math|n> candidati

    <item>abbiamo analizzato 100<math|n> candidati
  </itemize>

  Dove <math|n> è il numero di gradi di libertà del sistema.

  <with|gr-mode|<tuple|edit|text-at>|gr-frame|<tuple|scale|1cm|<tuple|0.0800134gw|0.199999gh>>|gr-geometry|<tuple|geometry|0.46667par|0.266669par|center>|gr-line-width|2ln|gr-arrow-end|\<gtr\>|<graphics||<line|<point|0|1.6>|<point|1.0|1.6>|<point|1.0|1.3>|<point|2.0|1.3>|<point|2.0|1.0>|<point|3.0|1.0>|<point|3.0|0.7>>|<line|<point|3|0.7>|<point|4.0|0.7>|<point|4.0|0.4>|<point|5.0|0.4>|<point|5.0|0.0>>|<text-at|t|<point|5.5|-0.4>>|<text-at|T|<point|-0.4|2.6>>|<with|arrow-end|\<gtr\>|line-width|2ln|<line|<point|0|0>|<point|6.0|0.0>>>|<with|arrow-end|\<gtr\>|line-width|2ln|<line|<point|0|0>|<point|0.0|3.0>>>|<text-at|<math|T<rsub|0>>|<point|0.4|1.2>>|<text-at|<math|T<rsub|1>>|<point|1.4|0.7>>|<text-at|<math|T<rsub|n>>|<point|4.4|0.7>>|<text-at||<point|5|0>>>>

  \;

  La <with|font-series|bold|progressione> della temperatura è:
  <math|T<rsub|k\<space\>+1 >=0.9T<rsub|k>>

  \;

  <with|font-series|bold|La condizione di stop>

  Se dopo almeno 3 gradini di temperatura successivi, la soluzione trovata
  non si trova un miglioramento della soluzione, ci si ferma.

  \;

  <with|font-series|bold|Validazione del risultato>

  Si ripete più volte l'esperienza con condizioni iniziali diverse, se ogni
  volta si trova lo stesso <with|font-series|bold|valore ottimale> (di
  energia, <with|font-series|bold|nb> ci possono essere più soluzioni
  ottimali con la stessa energia) allora probabilmente si tratterà di una
  buona soluzione.

  <subsection|Temperamento parallelo >

  E' una variante della ricotta che permette la parellizzazione, originato da
  <with|font-series|bold|Geyes> nel 1991 per le simulazioni Monte-Carlo sulle
  proteine, dove più ricotte simultanee interagiscono.

  L'idea principale è quella di fare passare le soluzioni possibili tra le
  ricotte di temperature vicine (in modo da esplorare meglio lo spazio).

  <with|font-series|bold|Temperaggio (tempering)> significa un ciclo
  caldo-freddo in un processo (per esempio nel processo di fabbricazione del
  cioccolato).

  Nelle ricotte tradizionali si può solo scendere di temperatura, invece in
  questo caso no.

  Si può rappresentare l'algoritmo del ``temperamento parallelo'' come:

  <with|gr-mode|<tuple|edit|line>|gr-frame|<tuple|scale|1cm|<tuple|0.490001gw|-0.539908gh>>|gr-geometry|<tuple|geometry|1par|0.200003par|center>|gr-arrow-end|\<gtr\>|gr-arrow-begin|\<less\>|gr-dash-style|10|<graphics|<text-at|<math|T<rsub|1>>|<point|-6.51837|3.19867>>|<text-at|<math|T<rsub|3>>|<point|-1.69234|3.32567>>|<text-at|<math|T<rsub|n>>|<point|0.932349|3.241>>|<with|arrow-end|\<gtr\>|arrow-begin|\<less\>|<line|<point|-3.57618|3.19854>|<point|-2.03100771632544|3.15451741496694>>>|<with|arrow-end|\<gtr\>|dash-style|10|arrow-begin|\<less\>|<line|<point|-0.485828|3.22316>|<point|0.417248537704657|3.2245173824431>>>|<cline|<point|-7.0|4.0>|<point|-5.6|4.0>|<point|-5.6|2.7>|<point|-7.0|2.7>>|<with|arrow-end|\<gtr\>|arrow-begin|\<less\>|<line|<point|-5.6|3.4>|<point|-5.03549256816261|3.39211529550945>>>|<cline|<point|-5.0|4.0>|<point|-3.6|4.0>|<point|-3.59553181637783|2.61995634343167>|<point|-5.03669466860696|2.66949993385368>>|<text-at|<math|T<rsub|2>>|<point|-4.5|3.3>>|<cline|<point|-2.03101|3.83368>|<point|-2.03100608546104|2.66949993385368>|<point|-0.5|2.6>|<point|-0.485828151871941|3.83367508929753>>|<cline|<point|0.4|3.8>|<point|0.466678793491203|2.69066675486175>|<point|2.0|2.7>|<point|2.0|3.8>>>><math|>

  Abbiamo dunque <math|n> ricotte, ciascuna con la sua propria temperatura
  <math|T<rsub|i>>, che non cambia, a parte per aggiustamenti spiegati in
  seguito.

  Si scelgono delle temperature tali che:

  <\equation*>
    T<rsub|1>\<less\>T<rsub|2>\<less\>T<rsub|3>\<ldots\>\<less\>T<rsub|n>
  </equation*>

  \ L'evoluzione nel tempo de la temperatura della ricotta standard è qui
  rimpiazzata per una variazione attraverso le <math|n> repliche.

  La replica <math|m>-esima avrà una alta temperatura e esplorerà lo spazio,
  mentre la replica 1 permetterà la ricerca di un risultato ottimizzato.

  In ciascuna dell <math|n> repliche abbiamo una configurazione che evolve
  secondo le regole di una ricotta a temperatura fissa. Ma andiamo anche ad
  aggiungere la possibilità di cambiare le soluzioni tra le ricotte vicine.

  Le configurazioni <math|C<rsub|i>> e <math|C<rsub|j>> sono scambiate se
  <math|i=j\<pm\>1> con una probabilità

  <\equation*>
    p=min<around*|(|1,e<rsup|-\<Delta\><rsub|ij>>|)>
  </equation*>

  Dove <math|\<Delta\><rsub|ij>> è calcolato cosi:

  <\equation*>
    \<Delta\><rsub|ij>=<around*|(|E<rsub|i>-E<rsub|j>|)><around*|(|<frac|1|T<rsub|j>>-<frac|1|T<rsub|i>>|)>
  </equation*>

  Dove <math|E<rsub|i>> e <math|E<rsub|j>> sono le fitness della
  configurazione <math|C<rsub|i>> e <math|C<rsub|j>>, mentre <math|T<rsub|i>>
  e <math|T<rsub|j>> sono le temperature delle repliche <math|i> e <math|j>.
  (<with|font-series|bold|nb: configurazione=soluzione>)

  Questa regola di scambia indica che una configurazione a bassa energia e
  alta temperatura sarà sempre scambiata con una configurazione ad alta
  energia e bassa temperatura.

  <with|gr-mode|<tuple|edit|text-at>|gr-frame|<tuple|scale|1cm|<tuple|0.579992gw|0.5gh>>|gr-geometry|<tuple|geometry|1par|0.133337par|center>|gr-arrow-end|\<gtr\>|gr-arrow-begin|\<less\>|gr-grid|<tuple|empty>|gr-grid-old|<tuple|cartesian|<point|0|0>|1>|gr-edit-grid-aspect|<tuple|<tuple|axes|none>|<tuple|1|none>|<tuple|10|none>>|gr-edit-grid|<tuple|empty>|gr-edit-grid-old|<tuple|cartesian|<point|0|0>|1>|<graphics||<text-at|<math|T<rsub|i>>|<point|-6.58187|0.361308>>|<text-at|<math|E<rsub|i>>
  grande|<point|-6.70887|-0.379531>>|<text-at|<math|T<rsub|i+1>\<gtr\>T<rsub|i>>|<point|-2.81418|0.318974>>|<text-at|<math|E<rsub|i+1>
  piccola>|<point|-2.81418|-0.316031>>|<cline|<point|-7.0|0.8>|<point|-5.0|0.8>|<point|-5.0|-0.8>|<point|-7.0|-0.8>>|<cline|<point|-3.4|0.7>|<point|-3.34334898796137|-0.760533800767297>|<point|-0.775549014419897|-0.739366979759227>|<point|-0.8|0.7>>|<with|arrow-end|\<gtr\>|arrow-begin|\<less\>|<line|<point|-5.0|0.0>|<point|-3.4|0.0>>>|<text-at|p=1|<point|-4.50090951184019|0.276640428628125>>>>

  Le buone soluzioni dunque vanno verso le basse temperature
  (intensificazione) e quelle cattive verso le temperature più alte
  (diversificazione).

  Ma c'è sempre una possibilità di fare il contrario.

  Questa possibilità diminuisce più la differenza di temperatura e di energia
  sono grandi.

  <\with|font-series|bold>
    \;

    Parametri di configurazione
  </with>

  Questo metodo richiede di specificare più elementi:

  <\itemize>
    <item>Il numero <math|m> di repliche, spesso <math|m=<sqrt|n>>, con
    <math|n> uguale al numero di gradi di libertà

    <item>le condizioni di scambio, ex quando due ricotte arrivano
    all'equilibrio

    <item>la distribuzione delle temperature delle repliche: la replica di
    temperatura <math|T<rsub|max>> deve avere una temperatura uguale a quella
    iniziale di una ricotta standard <math|T<rsub|0>>, mentre la replica con
    temperatura <math|T<rsub|min>> dovrà avere una temperatura abbastanza
    piccola per cercare i minimi di energia

    Possiamo decidere di ridistribuire le temperature se il tasso di scambio
    è troppo grande o piccolo.

    Se questo tasso è inferiore al 0.5% allora diminuiremo le \ temperature
    di <math|\<Delta\>T>:

    <\equation*>
      \<Delta\>T=0.1<around*|(|T<rsub|i+1>-T<rsub|i>|)>
    </equation*>

    Altrimenti se il tasso è maggiore del 2% si aumenteranno la temperature
    di <math|\<Delta\>T>

    \ \ 
  </itemize>

  \;

  \ 

  <section|Ant System>

  In questo caso l'intelligenza collettiva e la sua percezione è molto
  migliore di quella del singolo individuo.

  I problemi di questi tipo sono chiamati dai fisici <underline|problemi
  complessi>, dove il tutto (il problema) è di più della somma delle sue
  parti.

  Il risultato delle interazioni tra individui dona luogo a delle strutture
  organizzate nel tempo e nello spazio. Questa si chiama
  <underline|auto-organizzazione>

  In etologia si parla di <underline|eterarchia> che si oppone alla
  <underline|gerarchia>. Non ci sono livelli di conoscenza o di intelligenza
  diversi tra gli individui e nessuno fra di loro ha una conoscenza globale
  del problema. Dunque non c'è bisogno di capi.

  I sistemi auto-organizzati sono interessanti per la semplicità degli
  individui presenti. In più questi sistemi sono robusti ai disfunzionamenti
  o agli errori (addirittura a volta benefici, per esplorare delle soluzioni
  migliori).

  <\itemize>
    <item>Adattamento ai cambiamenti di condizione/configurazione\ 
  </itemize>

  Inoltre questi algoritmi dal punto di vista informatico sono molto
  interessanti in quanto si paralizzano facilmente.

  <with|font-series|bold|La storia>

  Nel 1992 \ Colani, Dorigo e Marizzo propongono l'algoritmo
  <with|font-series|bold|Ant-System> (AS) che permette di risolvere problemi
  di tipo combinatorio (tipo TSP, QAP...)

  L'ingrediente principale dell'AS è l'esistenza del <underline|ferormone>,
  una sostanza chimica che le formiche lasciano sulla loro strada \ per
  guidare le altre.

  Dopo questo primo algoritmo, altri ricercatori hanno studiato e replicato
  il comportamento animale per creare nuovi metaeuristiche, per esempio (si
  veda capitolo successivo):

  <\itemize>
    <item>Bee colony

    <item>PSO

    <item>Lucciole
  </itemize>

  <subsection|La pista dei ferormoni: una ottimizzazione naturale>

  Inizieremo descrivendo il ruolo dei ferormoni delle formiche per mostrare
  come questo meccanismo può dare luogo a una ottimizzazione.

  Per effettuare un lavoro collettivo, le formiche devono comunicare. Per
  farlo depositano dei ferormoni, una sostanza chimica odorante, che attira
  le altre formiche.

  Dunque, le formiche possono marcare un punto nello spazio che ritengono
  interessante.

  Tra i biologi, questo meccanismo si chiama <underline|Stignergia o
  chemotaxia>: orientare gli spostamenti in funzione di una sostanza chimica
  depositata nello spazio.

  La durata dei ferormoni è limitata nel tempo. Questi evaporano, e se non ci
  sono altre formiche a mantenere la pista, questa si cancella.

  L'evaporazione permette di eliminare delle soluzioni sotto-ottimali o
  sbagliate.

  <\with|font-series|bold>
    <subsubsection|Esperienza di Goss (1989)>
  </with>

  \;

  <with|gr-mode|<tuple|edit|point>|gr-frame|<tuple|scale|1cm|<tuple|0.599991gw|0.440006gh>>|gr-geometry|<tuple|geometry|0.953324par|0.333336par|center>|gr-line-width|2ln|gr-transformation|<tuple|<tuple|1.0|0.0|6.93889390390723e-17|0.0>|<tuple|0.0|1.0|0.0|0.0>|<tuple|-6.93889390390723e-17|0.0|1.0|0.0>|<tuple|0.0|0.0|0.0|1.0>>|gr-dash-style|11100|gr-color|blue|gr-opacity|40%|<graphics||<with|line-width|5ln|<cline|<point|0|0>|<point|1.0|2.0>|<point|2.0|0.0>|<point|1.0|-1.0>>>|<with|line-width|5ln|<line|<point|-6|0.3>|<point|-3.7|0.3>|<point|-2.0|1.5>|<point|-1.0|0.2>|<point|-0.4|0.2>|<point|1.0|2.7>|<point|2.3|0.5>|<point|3.3|0.5>>>|<with|arrow-end|\<gtr\>|line-width|5ln|<line|<point|3.4|0.3>|<point|4.4|0.3>>>|<with|arrow-end|\<gtr\>|line-width|5ln|<line|<point|-7|0>|<point|-6.0|0.0>>>|<text-at|Nido|<point|-7.8|0.8>>|<text-at|Cibo|<point|4.5|0.7>>|<with|line-width|5ln|<cline|<point|-3.5|0>|<point|-2.0|1.0>|<point|-1.09994708294748|-0.212495039026326>|<point|-2.54093612150881|-0.8>>>|<with|line-width|5ln|<line|<point|-6|-0.4>|<point|-3.6|-0.4>|<point|-2.5|-1.3>|<point|-1.0|-0.5>|<point|0.0|-0.6>|<point|1.0|-1.7>|<point|2.6|0.0>|<point|3.3|0.0>>>|<with|color|red|dash-style|10|line-width|2ln|<line|<point|-5.6|0>|<point|-3.7|0.0>|<point|-2.5|-1.0>|<point|-0.740111125810292|-0.191328218018256>|<point|-0.083939674560127|-0.254828681042466>|<point|1.0|-1.4>|<point|2.5|0.3>|<point|3.0|0.3>>>>>

  Disponendo di un sistemi di tubi con percorsi di diversa lunghezza che
  portano dal nido di formiche al cibo, Goss ha osservato che le formiche,
  che inizialmente percorrevano tutti i percorsi in modo equivalente, con il
  tempo utilizzarono solo quello corto (con qualche eccezione statistica).

  Il risultato e' stato analizzato in modo statistico nel seguente modo:

  <with|gr-mode|<tuple|edit|text-at>|gr-frame|<tuple|scale|1cm|<tuple|0.0900389gw|0.160031gh>>|gr-geometry|<tuple|geometry|1par|0.6par>|gr-line-width|2ln|gr-fill-color|pastel
  magenta|<graphics||<with|arrow-end|\<gtr\>|line-width|2ln|<line|<point|0|0>|<point|12.0|0.0>>>|<with|line-width|2ln|<line|<point|0.3|5>|<point|-0.3|5.0>>>|<with|line-width|2ln|<line|<point|-0.3|1>|<point|0.3|1.0>>>|<text-at|0.1|<point|-1|0.7>>|<text-at|1.0|<point|-1|5>>|<text-at|Frazione
  di formiche che scelgono il percorso + corto|<point|5|-0.7>>|<with|line-width|2ln|<line|<point|10|0.2>|<point|10.0|-0.3>>>|<with|line-width|2ln|<line|<point|11|0.3>|<point|11.0|-0.2>>>|<with|fill-color|pastel
  red|line-width|2ln|<cline|<point|9|0>|<point|9.0|1.0>|<point|10.0|1.0>|<point|10.0|0.0>>>|<with|fill-color|pastel
  magenta|line-width|2ln|<cline|<point|10|4>|<point|11.0|4.0>|<point|11.0|0.0>|<point|10.0|0.0>>>|<text-at|nel
  10% delle|<point|6.5|2.2>>|<text-at|osservazioni le
  |<point|6.4|1.8>>|<text-at|tra il 60-80%|<point|6.4|1.4>>|<text-at|scelgono
  il path|<point|6.4|1>>|<text-at|+ corto|<point|6.7|0.6>>|<text-at|nel 90%
  delle|<point|10.8|6.2>>|<text-at|osservazioni
  tra|<point|10.7|5.8>>|<text-at|l' 80-100%
  sceglie|<point|10.8|5.3>>|<text-at|il percorso +
  |<point|10.8|4.8>>|<text-at|corto|<point|11|4.3>>|<text-at|100%|<point|11.4|0.3>>|<text-at|60%|<point|8.3|0.2>>|<text-at|Frequenza
  di osservazioni|<point|-1.0|7.2>>|<with|arrow-end|\<gtr\>|line-width|2ln|<line|<point|0|0>|<point|0.0|5.6>>>>>

  Questo si spiega per la seguente ipotesi: la formica che casualmente
  sceglie il miglior percorso sarà la prima a ritornare e quindi rimarcare il
  percorso.

  Le formiche successive, rientrando da cammini più lunghi riprenderanno il
  cammino corto trattandosi del più marcato.\ 

  \;

  <\subsubsection>
    <\with|font-series|bold>
      Esperienza di Goss e Dereborg (1990)
    </with>
  </subsubsection>

  <with|gr-mode|<tuple|edit|line>|gr-frame|<tuple|scale|1cm|<tuple|0.509999gw|0.5gh>>|gr-geometry|<tuple|geometry|1par|0.233348par|center>|gr-color|blue|<graphics||<line|<point|-1|0>|<point|0.0|1.0>|<point|1.0|0.0>|<point|0.0|-1.0>|<point|-1.0|0.0>>|<line|<point|-3|0.3>|<point|-1.3|0.3>|<point|0.0|1.5>|<point|1.3|0.3>|<point|3.0|0.3>>|<line|<point|3|-0.3>|<point|1.3|-0.3>|<point|0.0|-1.5>>|<line|<point|-3|-0.3>|<point|-1.4|-0.3>|<point|0.0|-1.5>>|<with|color|red|<line|<point|-3|0>|<point|-1.5|0.0>|<point|0.0|1.2>|<point|1.4|0.0>|<point|3.0|0.0>>>|<with|color|blue|<line|<point|-2.99592|0.183043>|<point|-1.4189872999074|-0.0815418706178066>|<point|0.0838569916655642|-1.25630043656568>|<point|1.30094919962958|-0.113292102129911>|<point|3.01546170128324|0.151293160470962>>>>>

  Questa volta la configurazione è simmetrica.

  Si osserva dunque le seguenti varianti

  <with|gr-mode|<tuple|edit|text-at>|gr-frame|<tuple|scale|1cm|<tuple|0.5gw|0.5gh>>|gr-geometry|<tuple|geometry|1par|0.6par>|gr-line-width|2ln|<graphics||<with|arrow-end|\<gtr\>|line-width|2ln|<line|<point|-6|-3>|<point|6.0|-3.0>>>|<with|color|blue|<text-at|0.5|<point|-7|0>>>|<with|color|blue|line-width|2ln|<spline|<point|-6|0>|<point|-4.6|-0.8>|<point|-2.5|-2.2>|<point|1.6|2.0>|<point|6.0|3.0>>>|<with|color|red|line-width|2ln|<spline|<point|-6|0>|<point|-4.3|0.7>|<point|-2.7|2.0>|<point|-0.5|-1.0>|<point|2.5|-2.6>|<point|6.05678319937396|-2.8>>>|<with|color|blue|<text-at|t|<point|6|-3.7>>>|<with|arrow-end|\<gtr\>|line-width|2ln|<line|<point|-6|-3>|<point|-6.0|0.2>|<point|-6.0|3.7>>>|<with|color|blue|<text-at|occupazione|<point|-6.5|4.0>>>>>

  Si osserva che all'inizio i due cammini sono occupati in modo equivalente
  (50/50). Dopo una certa fase di oscillazione (+/- lunghi) uno dei due
  cammini prende il ``potere'' e l'occupazione diventa (0-100).

  \;

  <subsubsection|Modello matematico>

  Grass e Deneborg hanno proposto questa definizione:

  <\definition>
    \;

    <with|font-series|bold|<math|P<rsub|L><around*|(|m+1|)>>> la probabiltà
    che la (m+1)sima formica scelga il cammino L (lower).

    <with|font-series|bold|<math|P<rsub|U><around*|(|m+1|)>>> la probabiltà
    che la (m+1)sima formica scelga il cammino U (upper).

    Sia <math|<with|font-series|bold|U<rsub|m>>> il numero di formiche tra le
    m formiche già passate che sono passate sul cammino U.

    <math|<with|font-series|bold|L<rsub|m>>> ugualmente è il numero tra le m
    formiche di quelle che sono passate per il cammino L.

    Quindi: \ m=<math|U<rsub|m><rsup|>+L<rsub|m>> e
    \ <math|P<rsub|U><around*|(|m+1|)>+P<rsub|L><around*|(|m+1|)>=1>

    A questo punto la probabilità è calcolata:

    <\math>
      <with|font-series|bold|P<rsub|u><around*|(|m<rsup|>+1|)>=
      <frac|<around*|(|U<rsub|m>\<noplus\>+k|)><rsup|h>|<around*|(|U<rsub|m>+k|)><rsup|h>+<around*|(|L<rsub|m>+k|)><rsup|h>>>
    </math>

    Dove h e k sono dei parametri.

    <with|font-series|bold|k=20, h=2>

    <\with|color|dark red>
      k quantifica la differenza minima di formiche necessaria per influire
      nella scelta.

      h quantifica il modo in cui le formiche percepiscono i ferormoni.
    </with>
  </definition>

  \;

  <subsection|Algoritmo informatico di ottimizzazione>

  Dorigo nel 1992 introduce l'ant-system con l'obbiettivo di interpretare le
  piste di ferormone in un contesto di ottimizzazione combinatoria.

  In seguito, delle variate sono state presentata, per esempio
  l'<with|font-series|bold|Ant Colony System> (ACS). Più performanti in
  alcuni problemi.

  Noi presenteremo la metaeuristica AS per analizzare il problma del commesso
  viaggiatore.\ 

  Ci si dona una lista di <math|n> città e una amtrice di distanze
  <math|d<rsub|ij>> che rappresenta la distnza tra la città <math|i> e
  <math|j>.

  <with|gr-mode|<tuple|edit|text-at>|gr-frame|<tuple|scale|1cm|<tuple|0.599999gw|0.5gh>>|gr-geometry|<tuple|geometry|0.400004par|0.333336par|center>|gr-dash-style|1111010|<graphics||<point|-2.89354|1.77246>|<point|1.17049|-0.831062>|<point|-0.205351|-1.40257>|<point|-2.30087|-1.0004>|<point|-3.14753935705781|0.587114697711337>|<with|color|red|dash-style|1111010|<line|<point|-3.14754|0.587115>|<point|-2.30087|-1.0004>|<point|-0.205351|-1.40257>|<point|1.17049|-0.831062>|<point|0.154484720201085|1.77245667416325>|<point|-2.89354|1.77246>|<point|-3.14753935705781|0.587114697711337>>>|<point|0.154484720201085|1.77245667416325>|<text-at|V1|<point|-2.19503|-0.598227>>|<text-at|V2|<point|-0.268852|-1.08506>>|<text-at|V3|<point|1.55149|-0.598227>>|<text-at|V4|<point|0.747156|1.94179>>|<text-at|V5|<point|-2.63954|2.06879>>|<text-at|V6|<point|-2.63954|0.41778>>>>\ 

  Bisogna trovare il percorso più corto tra le <math|n> città, senza passare
  due volte per la stessa. Inoltre spesso si impone che il punto di partenza
  sia anche quello di arrivo (come nel caso di esempio), in questo modo il
  punto di partenza non conta.

  Per l'algoritmo AS definiamo la visibilità <math|\<eta\><rsub|ij>>:

  <\equation*>
    \<eta\><rsub|ij>=<frac|1|d<rsub|ij>>
  </equation*>

  Si individua cosi <math|\<tau\><rsub|ij>> come l'intenstità del percorso
  tra la città <math|i> e <math|j>.\ 

  Si definisce <math|m> il numero di formiche che esploreranno i percorsi
  possibili. Questi percorsi saranno influenzati dalla quantità di ormoni
  depostati tra le città (<math|\<tau\>>) e la prossimità tra queste due
  (<math|\<eta\>>).

  Bisognerà specificare inoltre il tasso di evaporazione dei ferormoni e la
  quantità di ferormoni depositati dalle formiche.

  <subsubsection|Algoritmo>

  A ogni iterazione <math|t>, lanciamo <math|m> formiche attraverso le
  <math|n> città, ciascuna attreverà in modo indipendente i percorsi del
  problema TSP secondo i valori di <math|\<tau\>> e <math|\<eta\>>.

  <underline|Durante una iterazione le <math|m> formiche determinano il loro
  percorso in modo indipendente l'una dall'altra. A l'iterazione <math|t> le
  <math|m> formiche sono influnzate solo dalle piste dei ferormoni lasciate
  dalle <math|m> formiche lasciate nell'iterazione <math|t-1>.>

  Nell'iterazione <math|t> possiamo definire <math|P<rsub|ij>> la
  probabilita' che una formica vada dalla citta' <math|i> a quella <math|j>.\ 

  <\equation*>
    P<rsub|ij>=<around*|{|<tabular|<tformat|<cwith|1|-1|1|-1|cell-valign|c>|<table|<row|<cell|0>|<cell|se
    j\<nin\>J>>|<row|<cell|<frac|<around*|[|\<tau\><rsub|ij><around*|(|t-1|)>|]><rsup|\<alpha\>><around*|[|\<eta\><rsub|ij>|]><rsup|\<beta\>>|<big|sum><rsub|l\<in\>J><around*|{|<around*|[|\<tau\><rsub|il><around*|(|t-1|)>|]><rsup|\<alpha\>><around*|[|\<eta\><rsub|il>|]><rsup|\<beta\>>|}>>>|<cell|se
    j \<in\> J>>>>>|\<nobracket\>>
  </equation*>

  Dove <math|J> è l'insieme di città ancora da visitare .

  Il fattore <math|<big|sum><rsub|l\<in\>J><around*|{|<around*|[|\<tau\><rsub|il><around*|(|t-1|)>|]><rsup|\<alpha\>><around*|[|\<eta\><rsub|il>|]><rsup|\<beta\>>|}>>
  è un fattore di normalizzazione che assume che
  <math|<big|sum><rsub|l\<in\>J>P<rsub|il>=1>.

  <math|\<alpha\>> e <math|\<beta\>> sono parametri specificati.

  In particolare i parametri <math|\<alpha\>> e <math|\<beta\>> sono i
  parametri di guida della metaeursitica. Se <math|\<alpha\>> e' grande
  mettiamo più di importanza alla traccia di ferormoni (quindi
  <underline|intensificheremo> il risultato) mentre se <math|\<beta\>> è
  grande si darà più importanza alla distanza tra le città (favorendo quindi
  la <underline|diversificazione>).

  Una volta che tutte le <math|m> formiche hanno seguito il loro percorso si
  può mettere a giorno il tasso di ferormoni in ciascun percorso in questo
  modo:

  <\equation*>
    \<tau\><rsub|ij><around*|(|t|)>=<around*|(|1-\<rho\>|)>\<tau\><rsub|ij><around*|(|t-1|)>
    \<noplus\>+\<Delta\>\<tau\><rsub|ij><around*|(|t|)>
  </equation*>

  Dove <math|\<rho\>> è il tasso di evaporazione e
  <math|\<Delta\>\<tau\><rsub|ij>=<big|sum><rsub|k=1><rsup|m>\<Delta\>\<tau\><rsub|ij><rsup|m>>
  e quindi

  <\equation*>
    \<Delta\>\<tau\><rsub|ij><rsup|k>=<around*|{|<tabular|<tformat|<cwith|2|2|1|-1|cell-valign|c>|<cwith|1|-1|1|-1|cell-halign|c>|<table|<row|<cell|0>|<cell|se
    <around*|(|i,j|)>\<nin\>T<rsub|k>>>|<row|<cell|<frac|Q|L<rsub|k>>>|<cell|se
    <around*|(|i,j|)> \<in\> T<rsub|k>>>>>>|\<nobracket\>>
  </equation*>

  Dove <math|Q> e' un parametro e <math|L<rsub|k>> è la lunghezza del tour
  <math|T<rsub|k>>.

  Concludendo ci sono 5 parametri da definire per l'algoritmo
  <with|font-series|bold|AS>:

  <\itemize>
    <item><math|m> è il numero di formiche; in generale si sceglie
    <math|m=n>, dove <math|n> è il numero di città e ogni formica partirà da
    una città diversa

    <item>In modo emprico si scelgono:

    <\itemize>
      <item><math|\<alpha\>=1>

      <item><math|\<beta\>=5>

      <item><math|\<rho\>=0.5>

      <item><math|Q=1>
    </itemize>
  </itemize>

  L'algoritmo <with|font-series|bold|AS> ha avuto un grande successo su dei
  problemi di benchmarking, trovando soluzioni migliori di quelle mai
  trovate.\ 

  Invece non su tutti i problemi ha perfomato correttamente e per questo
  motivo una nuova variante dell'<with|font-series|bold|AS> è stata proposta:
  <with|font-series|bold|Ant Colony System (ACS)>.

  <subsection|Ant Colony System>

  Con la probabilità <math|q> la prossima città visitata è quella che
  massimizza: <math|\<tau\><rsub|ij><around*|(|t-1|)><around*|[|\<eta\><rsub|ij>|]><rsup|\<beta\>>>
  per tutte le <math|j\<in\>J>. Qundi con la probabilità <math|q > scegliamo
  il <with|font-shape|italic|miglior> cammino. Con una probabilità di
  <math|1-q>, si estrare la città successiva a \ caso come prima:

  <\equation*>
    <tabular|<tformat|<table|<row|<cell|p<rsub|ij>=<frac|\<tau\><rsub|ij><around*|[|\<eta\><rsub|ij>|]><rsup|\<beta\>>|<big|sum><rsub|l\<in\>J>\<tau\><rsub|il><around*|[|\<eta\><rsub|il>|]><rsup|\<beta\>>>>|<cell|>|<cell|per
    j\<in\>J>>>>>
  </equation*>

  <subsubsection|Calcolo di <math|\<tau\><rsub|ij><around*|(|t+1|)>> nel
  <with|font-series|bold|ACS> >

  <\equation*>
    \<tau\><rsub|ij><around*|(|t+1|)>=<around*|(|1-\<phi\>|)>\<tau\><rsub|ij><around*|(|t|)>+\<phi\>\<tau\><rsub|0>
  </equation*>

  Dove <math|\<phi\>\<tau\><rsub|0>> è una quantità costante di ferormoni
  aggiunta a ciascun percorso <math|<around*|(|i,j|)>> percorsa da una
  formica.\ 

  <math|\<phi\>> è invece il fattore di evaporazione.

  Sul miglior percorso trovato si agginge una quantità di ferormoni
  <math|\<Delta\>\<tau\>=<frac|1|L<rsub|min>>>

  <subsubsection|Performance dell'ACS>

  <with|gr-mode|<tuple|edit|text-at>|gr-frame|<tuple|scale|1cm|<tuple|0.579992gw|0.539996gh>>|gr-geometry|<tuple|geometry|1par|0.540003par|center>|gr-grid|<tuple|empty>|gr-grid-old|<tuple|cartesian|<point|0|0>|5>|gr-edit-grid-aspect|<tuple|<tuple|axes|none>|<tuple|1|none>|<tuple|10|none>>|gr-edit-grid|<tuple|empty>|gr-edit-grid-old|<tuple|cartesian|<point|0|0>|5>|gr-opacity|60%|gr-line-width|2ln|<graphics||<line|<point|-7|-4>|<point|-6.5|-2.5>|<point|-6.0|-4.0>>|<line|<point|-5.5|-4>|<point|-5.0|-2.5>>|<line|<point|-5|-2.5>|<point|-4.5|-4.0>>|<line|<point|-4|-4>|<point|-3.5|-2.5>|<point|-3.0|-4.0>>|<line|<point|-2.5|-4>|<point|-2.0|-2.5>|<point|-1.5|-4.0>>|<line|<point|-1|-4>|<point|-0.5|-2.5>|<point|0.0|-4.0>>|<line|<point|0.5|-4>|<point|1.0|-2.5>>|<line|<point|1|-2.5>|<point|1.5|-4.0>>|<line|<point|2|-4>|<point|2.5|-2.5>|<point|3.0|-4.0>>|<line|<point|3.5|-4>|<point|4.0|-2.5>|<point|4.5|-4.0>>|<line|<point|-6.5|-2.5>|<point|-5.83202870896735|-0.5>|<point|-5.0|-2.5>>|<line|<point|-3.5|-2.5>|<point|-2.77459698244443|-0.5>|<point|-2.0|-2.5>>|<line|<point|-5.83203|-0.5>|<point|-4.21979967378541|1.5>>|<line|<point|-2.7746|-0.5>|<point|-4.21979967378541|1.5>>|<line|<point|-0.5|-2.5>|<point|0.218190855711201|-0.5>|<point|1.0|-2.5>>|<line|<point|2.5|-2.5>|<point|3.25810835062403|-0.5>|<point|4.0|-2.5>>|<line|<point|0.218191|-0.5>|<point|1.72137177795197|1.5>|<point|3.25810835062403|-0.5>>|<line|<point|-4.2198|1.5>|<point|-1.22862803302866|3.5>|<point|1.72137177795197|1.5>>|<with|fill-color|white|<point|-5.83203|-0.5>>|<with|fill-color|white|<point|-4.2198|1.5>>|<with|fill-color|white|<point|-2.7746|-0.5>>|<with|fill-color|white|<point|-6.5|-2.5>>|<with|fill-color|white|<point|-5|-2.5>>|<with|fill-color|white|<point|-7|-4>>|<with|fill-color|white|<point|-6|-4>>|<with|fill-color|white|<point|-5.5|-4>>|<with|fill-color|white|<point|-4.5|-4>>|<with|fill-color|white|<point|-4|-4>>|<with|fill-color|white|<point|-3|-4>>|<with|fill-color|white|<point|-3.5|-2.5>>|<with|fill-color|white|<point|-2.5|-4>>|<with|fill-color|white|<point|-2|-2.5>>|<with|fill-color|white|<point|-1.5|-4>>|<with|fill-color|white|<point|-1.22863|3.5>>|<with|fill-color|white|<point|1.72137|1.5>>|<with|fill-color|white|<point|0.218191|-0.5>>|<with|fill-color|white|<point|-1|-4>>|<with|fill-color|white|<point|-0.5|-2.5>>|<with|fill-color|white|<point|0|-4>>|<with|fill-color|white|<point|0.5|-4>>|<with|fill-color|white|<point|1|-2.5>>|<with|fill-color|white|<point|1.5|-4>>|<with|fill-color|white|<point|2|-4>>|<with|fill-color|white|<point|2.5|-2.5>>|<with|fill-color|white|<point|3.25811|-0.5>>|<with|fill-color|white|<point|4|-2.5>>|<with|fill-color|white|<point|3.5|-4>>|<with|fill-color|white|<point|3|-4>>|<with|fill-color|white|<point|4.5|-4>>|<with|color|magenta|opacity|60%|line-width|2ln|<line|<point|-1.22863|3.5>|<point|-4.2198|1.5>|<point|-5.83203|-0.5>|<point|-5.0|-2.5>|<point|-5.5|-4.0>>>|<with|color|magenta|opacity|60%|line-width|2ln|<line|<point|-4.2198|1.5>|<point|-2.7746|-0.5>|<point|-2.0|-2.5>|<point|-1.5|-4.0>>>|<with|color|magenta|opacity|60%|line-width|2ln|<line|<point|-1.22863|3.5>|<point|1.72137|1.5>|<point|3.25811|-0.5>|<point|2.5|-2.5>|<point|3.0|-4.0>>>|<with|color|magenta|opacity|60%|line-width|2ln|<line|<point|1.72137|1.5>|<point|0.218190855711201|-0.5>|<point|-0.5|-2.5>|<point|-1.0|-4.0>>>|<with|color|red|opacity|60%|line-width|2ln|<line|<point|-1.22863|3.5>|<point|-4.2198|1.5>|<point|-2.7746|-0.5>|<point|-2.0|-2.5>|<point|-2.5|-4.0>>>|<with|color|red|opacity|60%|line-width|2ln|<line|<point|-1.22863|3.5>|<point|1.72137|1.5>|<point|0.218191|-0.5>|<point|1.0|-2.5>|<point|0.5|-4.0>>>|<with|color|red|opacity|60%|line-width|2ln|<line|<point|1.72137|1.5>|<point|3.25811|-0.5>|<point|4.0|-2.5>|<point|3.5|-4.0>>>|<with|color|red|opacity|60%|line-width|2ln|<line|<point|4.5|-4>|<point|4.0|-2.5>>>|<with|opacity|60%|<text-at|2<degreesign>
  iterazione|<point|4.0|3.0>>>|<with|color|red|opacity|60%|line-width|2ln|<line|<point|3.0|3.0>|<point|3.5|3.0>>>|<with|color|magenta|opacity|60%|line-width|2ln|<line|<point|3.0|2.0>|<point|3.5|2.0>>>|<with|opacity|60%|<text-at|1<degreesign>
  iterazione|<point|4|2>>>>>\ 

  <with|prog-scripts|gnuplot|<image|<tuple|<#252150532D41646F62652D322E3020455053462D322E300A25255469746C653A2074656D702E6570730A252543726561746F723A20676E75706C6F7420352E302070617463686C6576656C20330A25254372656174696F6E446174653A204D6F6E204F63742033312031303A35313A323720323031360A2525446F63756D656E74466F6E74733A20286174656E64290A2525426F756E64696E67426F783A20353020353020343130203330320A2525456E64436F6D6D656E74730A2525426567696E50726F6C6F670A2F676E7564696374203235362064696374206465660A676E756469637420626567696E0A250A252054686520666F6C6C6F77696E6720747275652F66616C736520666C616773206D6179206265206564697465642062792068616E6420696620646573697265642E0A252054686520756E6974206C696E6520776964746820616E6420677261797363616C6520696D6167652067616D6D6120636F7272656374696F6E206D617920616C736F206265206368616E6765642E0A250A2F436F6C6F722066616C7365206465660A2F426C61636B746578742066616C7365206465660A2F536F6C69642066616C7365206465660A2F446173686C656E6774682031206465660A2F4C616E6473636170652066616C7365206465660A2F4C6576656C312066616C7365206465660A2F4C6576656C332066616C7365206465660A2F526F756E6465642066616C7365206465660A2F436C6970546F426F756E64696E67426F782066616C7365206465660A2F53757070726573735044464D61726B2066616C7365206465660A2F5472616E73706172656E745061747465726E732066616C7365206465660A2F676E756C696E65776964746820352E303030206465660A2F757365726C696E65776964746820676E756C696E657769647468206465660A2F47616D6D6120312E30206465660A2F4261636B67726F756E64436F6C6F72207B2D312E303030202D312E303030202D312E3030307D206465660A250A2F767368696674202D3436206465660A2F646C31207B0A202031302E3020446173686C656E67746820757365726C696E65776964746820676E756C696E65776964746820646976206D756C206D756C206D756C0A2020526F756E646564207B2063757272656E746C696E65776964746820302E3735206D756C20737562206475702030206C65207B20706F7020302E3031207D206966207D2069660A7D206465660A2F646C32207B0A202031302E3020446173686C656E67746820757365726C696E65776964746820676E756C696E65776964746820646976206D756C206D756C206D756C0A2020526F756E646564207B2063757272656E746C696E65776964746820302E3735206D756C20616464207D2069660A7D206465660A2F6870745F2033312E35206465660A2F7670745F2033312E35206465660A2F687074206870745F206465660A2F767074207670745F206465660A2F646F636C6970207B0A2020436C6970546F426F756E64696E67426F78207B0A202020206E657770617468203530203530206D6F7665746F20343130203530206C696E65746F2034313020333032206C696E65746F20353020333032206C696E65746F20636C6F7365706174680A20202020636C69700A20207D2069660A7D206465660A250A2520476E75706C6F742050726F6C6F672056657273696F6E20352E3120284F63742032303135290A250A252F53757070726573735044464D61726B2074727565206465660A250A2F4D207B6D6F7665746F7D2062696E64206465660A2F4C207B6C696E65746F7D2062696E64206465660A2F52207B726D6F7665746F7D2062696E64206465660A2F56207B726C696E65746F7D2062696E64206465660A2F4E207B6E657770617468206D6F7665746F7D2062696E64206465660A2F5A207B636C6F7365706174687D2062696E64206465660A2F43207B736574726762636F6C6F727D2062696E64206465660A2F66207B726C696E65746F2066696C6C7D2062696E64206465660A2F67207B736574677261797D2062696E64206465660A2F4773686F77207B73686F777D2064656620202025204D6179206265207265646566696E6564206C6174657220696E207468652066696C6520746F20737570706F7274205554462D380A2F76707432207670742032206D756C206465660A2F68707432206870742032206D756C206465660A2F4C73686F77207B63757272656E74706F696E74207374726F6B65204D2030207673686966742052200A09426C61636B74657874207B677361766520302073657467726179207465787473686F772067726573746F72657D207B7465787473686F777D206966656C73657D206465660A2F5273686F77207B63757272656E74706F696E74207374726F6B65204D2064757020737472696E67776964746820706F70206E65672076736869667420520A09426C61636B74657874207B677361766520302073657467726179207465787473686F772067726573746F72657D207B7465787473686F777D206966656C73657D206465660A2F4373686F77207B63757272656E74706F696E74207374726F6B65204D2064757020737472696E67776964746820706F70202D3220646976207673686966742052200A09426C61636B74657874207B677361766520302073657467726179207465787473686F772067726573746F72657D207B7465787473686F777D206966656C73657D206465660A2F5550207B647570207670745F206D756C202F767074206578636820646566206870745F206D756C202F6870742065786368206465660A20202F68707432206870742032206D756C20646566202F76707432207670742032206D756C206465667D206465660A2F444C207B436F6C6F72207B736574726762636F6C6F7220536F6C6964207B706F70205B5D7D206966203020736574646173687D0A207B706F7020706F7020706F702030207365746772617920536F6C6964207B706F70205B5D7D206966203020736574646173687D206966656C73657D206465660A2F424C207B7374726F6B6520757365726C696E6577696474682032206D756C207365746C696E6577696474680A09526F756E646564207B31207365746C696E656A6F696E2031207365746C696E656361707D2069667D206465660A2F414C207B7374726F6B6520757365726C696E657769647468203220646976207365746C696E6577696474680A09526F756E646564207B31207365746C696E656A6F696E2031207365746C696E656361707D2069667D206465660A2F554C207B64757020676E756C696E657769647468206D756C202F757365726C696E6577696474682065786368206465660A096475702031206C74207B706F7020317D206966203130206D756C202F75646C2065786368206465667D206465660A2F504C207B7374726F6B6520757365726C696E657769647468207365746C696E6577696474680A09526F756E646564207B31207365746C696E656A6F696E2031207365746C696E656361707D2069667D206465660A332E38207365746D697465726C696D69740A2520436C6173736963204C696E6520636F6C6F7273202876657273696F6E20352E30290A2F4C4377207B31203120317D206465660A2F4C4362207B30203020307D206465660A2F4C4361207B30203020307D206465660A2F4C4330207B31203020307D206465660A2F4C4331207B30203120307D206465660A2F4C4332207B30203020317D206465660A2F4C4333207B31203020317D206465660A2F4C4334207B30203120317D206465660A2F4C4335207B31203120307D206465660A2F4C4336207B30203020307D206465660A2F4C4337207B3120302E3320307D206465660A2F4C4338207B302E3520302E3520302E357D206465660A252044656661756C742064617368207061747465726E73202876657273696F6E20352E30290A2F4C5442207B424C205B5D204C436220444C7D206465660A2F4C5477207B504C205B5D203120736574677261797D206465660A2F4C5462207B504C205B5D204C436220444C7D206465660A2F4C5461207B414C205B312075646C206D756C20322075646C206D756C5D20302073657464617368204C436120736574726762636F6C6F727D206465660A2F4C5430207B504C205B5D204C433020444C7D206465660A2F4C5431207B504C205B3220646C31203320646C325D204C433120444C7D206465660A2F4C5432207B504C205B3120646C3120312E3520646C325D204C433220444C7D206465660A2F4C5433207B504C205B3620646C31203220646C32203120646C31203220646C325D204C433320444C7D206465660A2F4C5434207B504C205B3120646C31203220646C32203620646C31203220646C32203120646C31203220646C325D204C433420444C7D206465660A2F4C5435207B504C205B3420646C31203220646C325D204C433520444C7D206465660A2F4C5436207B504C205B312E3520646C3120312E3520646C3220312E3520646C3120312E3520646C3220312E3520646C31203620646C325D204C433620444C7D206465660A2F4C5437207B504C205B3320646C31203320646C32203120646C31203320646C325D204C433720444C7D206465660A2F4C5438207B504C205B3220646C31203220646C32203220646C31203620646C325D204C433820444C7D206465660A2F534C207B5B5D203020736574646173687D206465660A2F506E74207B7374726F6B65205B5D203020736574646173682067736176652031207365746C696E65636170204D203020302056207374726F6B652067726573746F72657D206465660A2F446961207B7374726F6B65205B5D20302073657464617368203220636F70792076707420616464204D0A2020687074206E656720767074206E656720562068707420767074206E656720560A202068707420767074205620687074206E656720767074205620636C6F736570617468207374726F6B650A2020506E747D206465660A2F506C73207B7374726F6B65205B5D203020736574646173682076707420737562204D2030207670743220560A202063757272656E74706F696E74207374726F6B65204D0A2020687074206E656720767074206E65672052206870743220302056207374726F6B650A207D206465660A2F426F78207B7374726F6B65205B5D20302073657464617368203220636F70792065786368206870742073756220657863682076707420616464204D0A2020302076707432206E656720562068707432203020562030207670743220560A202068707432206E65672030205620636C6F736570617468207374726F6B650A2020506E747D206465660A2F437273207B7374726F6B65205B5D203020736574646173682065786368206870742073756220657863682076707420616464204D0A2020687074322076707432206E656720562063757272656E74706F696E74207374726F6B65204D0A202068707432206E656720302052206870743220767074322056207374726F6B657D206465660A2F54726955207B7374726F6B65205B5D20302073657464617368203220636F70792076707420312E3132206D756C20616464204D0A2020687074206E656720767074202D312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E65672076707420312E3632206D756C205620636C6F736570617468207374726F6B650A2020506E747D206465660A2F53746172207B3220636F707920506C73204372737D206465660A2F426F7846207B7374726F6B65205B5D203020736574646173682065786368206870742073756220657863682076707420616464204D0A2020302076707432206E656720562068707432203020562030207670743220560A202068707432206E65672030205620636C6F7365706174682066696C6C7D206465660A2F5472695546207B7374726F6B65205B5D203020736574646173682076707420312E3132206D756C20616464204D0A2020687074206E656720767074202D312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E65672076707420312E3632206D756C205620636C6F7365706174682066696C6C7D206465660A2F54726944207B7374726F6B65205B5D20302073657464617368203220636F70792076707420312E3132206D756C20737562204D0A2020687074206E65672076707420312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E656720767074202D312E3632206D756C205620636C6F736570617468207374726F6B650A2020506E747D206465660A2F5472694446207B7374726F6B65205B5D203020736574646173682076707420312E3132206D756C20737562204D0A2020687074206E65672076707420312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E656720767074202D312E3632206D756C205620636C6F7365706174682066696C6C7D206465660A2F44696146207B7374726F6B65205B5D203020736574646173682076707420616464204D0A2020687074206E656720767074206E656720562068707420767074206E656720560A202068707420767074205620687074206E656720767074205620636C6F7365706174682066696C6C7D206465660A2F50656E74207B7374726F6B65205B5D20302073657464617368203220636F70792067736176650A20207472616E736C617465203020687074204D2034207B373220726F74617465203020687074204C7D207265706561740A2020636C6F736570617468207374726F6B652067726573746F726520506E747D206465660A2F50656E7446207B7374726F6B65205B5D203020736574646173682067736176650A20207472616E736C617465203020687074204D2034207B373220726F74617465203020687074204C7D207265706561740A2020636C6F7365706174682066696C6C2067726573746F72657D206465660A2F436972636C65207B7374726F6B65205B5D20302073657464617368203220636F70790A202068707420302033363020617263207374726F6B6520506E747D206465660A2F436972636C6546207B7374726F6B65205B5D2030207365746461736820687074203020333630206172632066696C6C7D206465660A2F4330207B424C205B5D20302073657464617368203220636F7079206D6F7665746F2076707420393020343530206172637D2062696E64206465660A2F4331207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F70792076707420302039302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4332207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F707920767074203930203138302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4333207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F7079207670742030203138302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4334207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F70792076707420313830203237302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4335207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F7079207670742030203930206172630A093220636F7079206D6F7665746F0A093220636F70792076707420313830203237302061726320636C6F7365706174682066696C6C0A09767074203020333630206172637D2062696E64206465660A2F4336207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F707920767074203930203237302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4337207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F7079207670742030203237302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4338207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F70792076707420323730203336302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4339207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F70792076707420323730203435302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F433130207B424C205B5D20302073657464617368203220636F7079203220636F7079206D6F7665746F2076707420323730203336302061726320636C6F7365706174682066696C6C0A093220636F7079206D6F7665746F0A093220636F707920767074203930203138302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F433131207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F7079207670742030203138302061726320636C6F7365706174682066696C6C0A093220636F7079206D6F7665746F0A093220636F70792076707420323730203336302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F433132207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F70792076707420313830203336302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F433133207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F70792076707420302039302061726320636C6F7365706174682066696C6C0A093220636F7079206D6F7665746F0A093220636F70792076707420313830203336302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F433134207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F707920767074203930203336302061726320636C6F7365706174682066696C6C0A09767074203020333630206172637D2062696E64206465660A2F433135207B424C205B5D20302073657464617368203220636F7079207670742030203336302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F526563207B6E6577706174682034203220726F6C6C206D6F7665746F203120696E646578203020726C696E65746F2030206578636820726C696E65746F0A096E6567203020726C696E65746F20636C6F7365706174687D2062696E64206465660A2F537175617265207B647570205265637D2062696E64206465660A2F42737175617265207B767074207375622065786368207670742073756220657863682076707432205371756172657D2062696E64206465660A2F5330207B424C205B5D20302073657464617368203220636F7079206D6F7665746F20302076707420726C696E65746F20424C20427371756172657D2062696E64206465660A2F5331207B424C205B5D20302073657464617368203220636F707920767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F5332207B424C205B5D20302073657464617368203220636F707920657863682076707420737562206578636820767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F5333207B424C205B5D20302073657464617368203220636F7079206578636820767074207375622065786368207670743220767074205265632066696C6C20427371756172657D2062696E64206465660A2F5334207B424C205B5D20302073657464617368203220636F7079206578636820767074207375622065786368207670742073756220767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F5335207B424C205B5D20302073657464617368203220636F7079203220636F707920767074205371756172652066696C6C0A096578636820767074207375622065786368207670742073756220767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F5336207B424C205B5D20302073657464617368203220636F70792065786368207670742073756220657863682076707420737562207670742076707432205265632066696C6C20427371756172657D2062696E64206465660A2F5337207B424C205B5D20302073657464617368203220636F70792065786368207670742073756220657863682076707420737562207670742076707432205265632066696C6C0A093220636F707920767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F5338207B424C205B5D20302073657464617368203220636F7079207670742073756220767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F5339207B424C205B5D20302073657464617368203220636F70792076707420737562207670742076707432205265632066696C6C20427371756172657D2062696E64206465660A2F533130207B424C205B5D20302073657464617368203220636F7079207670742073756220767074205371756172652066696C6C203220636F707920657863682076707420737562206578636820767074205371756172652066696C6C0A09427371756172657D2062696E64206465660A2F533131207B424C205B5D20302073657464617368203220636F7079207670742073756220767074205371756172652066696C6C203220636F7079206578636820767074207375622065786368207670743220767074205265632066696C6C0A09427371756172657D2062696E64206465660A2F533132207B424C205B5D20302073657464617368203220636F70792065786368207670742073756220657863682076707420737562207670743220767074205265632066696C6C20427371756172657D2062696E64206465660A2F533133207B424C205B5D20302073657464617368203220636F70792065786368207670742073756220657863682076707420737562207670743220767074205265632066696C6C0A093220636F707920767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F533134207B424C205B5D20302073657464617368203220636F70792065786368207670742073756220657863682076707420737562207670743220767074205265632066696C6C0A093220636F707920657863682076707420737562206578636820767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F533135207B424C205B5D20302073657464617368203220636F707920427371756172652066696C6C20427371756172657D2062696E64206465660A2F4430207B6773617665207472616E736C61746520343520726F7461746520302030205330207374726F6B652067726573746F72657D2062696E64206465660A2F4431207B6773617665207472616E736C61746520343520726F7461746520302030205331207374726F6B652067726573746F72657D2062696E64206465660A2F4432207B6773617665207472616E736C61746520343520726F7461746520302030205332207374726F6B652067726573746F72657D2062696E64206465660A2F4433207B6773617665207472616E736C61746520343520726F7461746520302030205333207374726F6B652067726573746F72657D2062696E64206465660A2F4434207B6773617665207472616E736C61746520343520726F7461746520302030205334207374726F6B652067726573746F72657D2062696E64206465660A2F4435207B6773617665207472616E736C61746520343520726F7461746520302030205335207374726F6B652067726573746F72657D2062696E64206465660A2F4436207B6773617665207472616E736C61746520343520726F7461746520302030205336207374726F6B652067726573746F72657D2062696E64206465660A2F4437207B6773617665207472616E736C61746520343520726F7461746520302030205337207374726F6B652067726573746F72657D2062696E64206465660A2F4438207B6773617665207472616E736C61746520343520726F7461746520302030205338207374726F6B652067726573746F72657D2062696E64206465660A2F4439207B6773617665207472616E736C61746520343520726F7461746520302030205339207374726F6B652067726573746F72657D2062696E64206465660A2F443130207B6773617665207472616E736C61746520343520726F746174652030203020533130207374726F6B652067726573746F72657D2062696E64206465660A2F443131207B6773617665207472616E736C61746520343520726F746174652030203020533131207374726F6B652067726573746F72657D2062696E64206465660A2F443132207B6773617665207472616E736C61746520343520726F746174652030203020533132207374726F6B652067726573746F72657D2062696E64206465660A2F443133207B6773617665207472616E736C61746520343520726F746174652030203020533133207374726F6B652067726573746F72657D2062696E64206465660A2F443134207B6773617665207472616E736C61746520343520726F746174652030203020533134207374726F6B652067726573746F72657D2062696E64206465660A2F443135207B6773617665207472616E736C61746520343520726F746174652030203020533135207374726F6B652067726573746F72657D2062696E64206465660A2F44696145207B7374726F6B65205B5D203020736574646173682076707420616464204D0A2020687074206E656720767074206E656720562068707420767074206E656720560A202068707420767074205620687074206E656720767074205620636C6F736570617468207374726F6B657D206465660A2F426F7845207B7374726F6B65205B5D203020736574646173682065786368206870742073756220657863682076707420616464204D0A2020302076707432206E656720562068707432203020562030207670743220560A202068707432206E65672030205620636C6F736570617468207374726F6B657D206465660A2F5472695545207B7374726F6B65205B5D203020736574646173682076707420312E3132206D756C20616464204D0A2020687074206E656720767074202D312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E65672076707420312E3632206D756C205620636C6F736570617468207374726F6B657D206465660A2F5472694445207B7374726F6B65205B5D203020736574646173682076707420312E3132206D756C20737562204D0A2020687074206E65672076707420312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E656720767074202D312E3632206D756C205620636C6F736570617468207374726F6B657D206465660A2F50656E7445207B7374726F6B65205B5D203020736574646173682067736176650A20207472616E736C617465203020687074204D2034207B373220726F74617465203020687074204C7D207265706561740A2020636C6F736570617468207374726F6B652067726573746F72657D206465660A2F4369726345207B7374726F6B65205B5D20302073657464617368200A202068707420302033363020617263207374726F6B657D206465660A2F4F7061717565207B677361766520636C6F736570617468203120736574677261792066696C6C2067726573746F72652030207365746772617920636C6F7365706174687D206465660A2F44696157207B7374726F6B65205B5D203020736574646173682076707420616464204D0A2020687074206E656720767074206E656720562068707420767074206E656720560A202068707420767074205620687074206E6567207670742056204F7061717565207374726F6B657D206465660A2F426F7857207B7374726F6B65205B5D203020736574646173682065786368206870742073756220657863682076707420616464204D0A2020302076707432206E656720562068707432203020562030207670743220560A202068707432206E656720302056204F7061717565207374726F6B657D206465660A2F5472695557207B7374726F6B65205B5D203020736574646173682076707420312E3132206D756C20616464204D0A2020687074206E656720767074202D312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E65672076707420312E3632206D756C2056204F7061717565207374726F6B657D206465660A2F5472694457207B7374726F6B65205B5D203020736574646173682076707420312E3132206D756C20737562204D0A2020687074206E65672076707420312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E656720767074202D312E3632206D756C2056204F7061717565207374726F6B657D206465660A2F50656E7457207B7374726F6B65205B5D203020736574646173682067736176650A20207472616E736C617465203020687074204D2034207B373220726F74617465203020687074204C7D207265706561740A20204F7061717565207374726F6B652067726573746F72657D206465660A2F4369726357207B7374726F6B65205B5D20302073657464617368200A202068707420302033363020617263204F7061717565207374726F6B657D206465660A2F426F7846696C6C207B677361766520526563203120736574677261792066696C6C2067726573746F72657D206465660A2F44656E73697479207B0A20202F46696C6C64656E2065786368206465660A202063757272656E74726762636F6C6F720A20202F436F6C42206578636820646566202F436F6C47206578636820646566202F436F6C522065786368206465660A20202F436F6C5220436F6C522046696C6C64656E206D756C2046696C6C64656E20737562203120616464206465660A20202F436F6C4720436F6C472046696C6C64656E206D756C2046696C6C64656E20737562203120616464206465660A20202F436F6C4220436F6C422046696C6C64656E206D756C2046696C6C64656E20737562203120616464206465660A2020436F6C5220436F6C4720436F6C4220736574726762636F6C6F727D206465660A2F426F78436F6C46696C6C207B67736176652052656320506F6C7946696C6C7D206465660A2F506F6C7946696C6C207B67736176652044656E736974792066696C6C2067726573746F72652067726573746F72657D206465660A2F68207B726C696E65746F20726C696E65746F20726C696E65746F20677361766520636C6F7365706174682066696C6C2067726573746F72657D2062696E64206465660A250A2520506F7374536372697074204C6576656C2031205061747465726E2046696C6C20726F7574696E6520666F722072656374616E676C65730A252055736167653A207820792077206820732061205858205061747465726E46696C6C0A2509782C79203D206C6F776572206C65667420636F726E6572206F6620626F7820746F2062652066696C6C65640A2509772C68203D20776964746820616E6420686569676874206F6620626F780A2509202061203D20616E676C6520696E2064656772656573206265747765656E206C696E657320616E6420782D617869730A2509205858203D20302F3120666F72206E6F2F7965732063726F73732D68617463680A250A2F5061747465726E46696C6C207B6773617665202F504661205B2039203220726F6C6C205D206465660A20205046612030206765742050466120322067657420322064697620616464205046612031206765742050466120332067657420322064697620616464207472616E736C6174650A2020504661203220676574202D322064697620504661203320676574202D32206469762050466120322067657420504661203320676574205265630A20205472616E73706172656E745061747465726E73207B7D207B6773617665203120736574677261792066696C6C2067726573746F72657D206966656C73650A2020636C69700A202063757272656E746C696E65776964746820302E35206D756C207365746C696E6577696474680A20202F5046732050466120322067657420647570206D756C2050466120332067657420647570206D756C206164642073717274206465660A2020302030204D2050466120352067657420726F7461746520504673202D322064697620647570207472616E736C6174650A202030203120504673205046612034206765742064697620312061646420666C6F6F72206376690A097B504661203420676574206D756C2030204D20302050467320567D20666F720A20203020504661203620676574206E65207B0A0930203120504673205046612034206765742064697620312061646420666C6F6F72206376690A097B504661203420676574206D756C20302032203120726F6C6C204D20504673203020567D20666F720A207D2069660A20207374726F6B652067726573746F72657D206465660A250A2F6C616E67756167656C6576656C2077686572650A207B706F70206C616E67756167656C6576656C7D207B317D206966656C73650A6475702032206C740A097B2F496E746572707265744C6576656C312074727565206465660A09202F496E746572707265744C6576656C332066616C7365206465667D0A097B2F496E746572707265744C6576656C31204C6576656C31206465660A0920322067740A09202020207B2F496E746572707265744C6576656C33204C6576656C33206465667D0A09202020207B2F496E746572707265744C6576656C332066616C7365206465667D0A09206966656C7365207D0A206966656C73650A250A2520506F7374536372697074206C6576656C2032207061747465726E2066696C6C20646566696E6974696F6E730A250A2F4C6576656C325061747465726E46696C6C207B0A2F54696C65387838207B2F5061696E74547970652032202F5061747465726E547970652031202F54696C696E67547970652031202F42426F78205B302030203820385D202F58537465702038202F595374657020387D0A0962696E64206465660A2F4B656570436F6C6F72207B63757272656E74726762636F6C6F72205B2F5061747465726E202F4465766963655247425D20736574636F6C6F7273706163657D2062696E64206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F7020302030204D20382038204C20302038204D20382030204C207374726F6B657D200A3E3E206D6174726978206D616B657061747465726E0A2F506174312065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F7020302030204D20382038204C20302038204D20382030204C207374726F6B650A09302034204D20342038204C20382034204C20342030204C20302034204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174322065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F7020302030204D20302038204C0A09382038204C20382030204C20302030204C2066696C6C7D0A3E3E206D6174726978206D616B657061747465726E0A2F506174332065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F70202D342038204D2038202D34204C0A0930203132204D2031322030204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174342065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F70202D342030204D2038203132204C0A0930202D34204D2031322038204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174352065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F70202D322038204D2034202D34204C0A0930203132204D2038202D34204C2034203132204D2031302030204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174362065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F70202D322030204D2034203132204C0A0930202D34204D2038203132204C2034202D34204D2031302038204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174372065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F702038202D32204D202D342034204C0A0931322030204D202D342038204C2031322034204D2030203130204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174382065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F702030202D32204D2031322034204C0A092D342030204D2031322038204C202D342034204D2038203130204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174392065786368206465660A2F5061747465726E31207B5061747465726E42676E64204B656570436F6C6F722050617431207365747061747465726E7D2062696E64206465660A2F5061747465726E32207B5061747465726E42676E64204B656570436F6C6F722050617432207365747061747465726E7D2062696E64206465660A2F5061747465726E33207B5061747465726E42676E64204B656570436F6C6F722050617433207365747061747465726E7D2062696E64206465660A2F5061747465726E34207B5061747465726E42676E64204B656570436F6C6F72204C616E647363617065207B506174357D207B506174347D206966656C7365207365747061747465726E7D2062696E64206465660A2F5061747465726E35207B5061747465726E42676E64204B656570436F6C6F72204C616E647363617065207B506174347D207B506174357D206966656C7365207365747061747465726E7D2062696E64206465660A2F5061747465726E36207B5061747465726E42676E64204B656570436F6C6F72204C616E647363617065207B506174397D207B506174367D206966656C7365207365747061747465726E7D2062696E64206465660A2F5061747465726E37207B5061747465726E42676E64204B656570436F6C6F72204C616E647363617065207B506174387D207B506174377D206966656C7365207365747061747465726E7D2062696E64206465660A7D206465660A250A250A25456E64206F6620506F7374536372697074204C6576656C203220636F64650A250A2F5061747465726E42676E64207B0A20205472616E73706172656E745061747465726E73207B7D207B6773617665203120736574677261792066696C6C2067726573746F72657D206966656C73650A7D206465660A250A25205375627374697475746520666F72204C6576656C2032207061747465726E2066696C6C20636F64657320776974680A2520677261797363616C65206966204C6576656C203220737570706F7274206973206E6F742073656C65637465642E0A250A2F4C6576656C315061747465726E46696C6C207B0A2F5061747465726E31207B302E3235302044656E736974797D2062696E64206465660A2F5061747465726E32207B302E3530302044656E736974797D2062696E64206465660A2F5061747465726E33207B302E3735302044656E736974797D2062696E64206465660A2F5061747465726E34207B302E3132352044656E736974797D2062696E64206465660A2F5061747465726E35207B302E3337352044656E736974797D2062696E64206465660A2F5061747465726E36207B302E3632352044656E736974797D2062696E64206465660A2F5061747465726E37207B302E3837352044656E736974797D2062696E64206465660A7D206465660A250A25204E6F77207465737420666F7220737570706F7274206F66204C6576656C203220636F64650A250A4C6576656C31207B4C6576656C315061747465726E46696C6C7D207B4C6576656C325061747465726E46696C6C7D206966656C73650A250A2F53796D626F6C2D4F626C69717565202F53796D626F6C2066696E64666F6E74205B312030202E3136372031203020305D206D616B65666F6E740A647570206C656E677468206469637420626567696E207B3120696E646578202F464944206571207B706F7020706F707D207B6465667D206966656C73657D20666F72616C6C0A63757272656E746469637420656E6420646566696E65666F6E7420706F700A250A2F4D4673686F77207B0A2020207B2064757020352067657420332067650A20202020207B2035206765742033206571207B67736176657D207B67726573746F72657D206966656C7365207D0A20202020207B647570206475702030206765742066696E64666F6E742065786368203120676574207363616C65666F6E7420736574666F6E740A20202020205B2063757272656E74706F696E74205D206578636820647570203220676574203020657863682052206475702035206765742032206E65207B6475702064757020360A20202020206765742065786368203420676574207B7465787473686F777D207B737472696E67776964746820706F70203020527D206966656C7365207D69662064757020352067657420302065710A20202020207B647570203320676574207B3220676574206E656720302065786368205220706F707D207B706F7020616C6F616420706F70204D7D206966656C73657D207B64757020350A20202020206765742031206571207B647570203220676574206578636820647570203320676574206578636820362067657420737472696E67776964746820706F70202D32206469760A2020202020647570203020527D207B64757020362067657420737472696E67776964746820706F70202D3220646976203020522036206765740A20202020207465787473686F77203220696E646578207B616C6F616420706F70204D206E65672033202D3120726F6C6C206E6567205220706F7020706F707D207B706F7020706F7020706F700A2020202020706F7020616C6F616420706F70204D7D206966656C7365207D6966656C7365207D6966656C7365207D0A20202020206966656C7365207D0A202020666F72616C6C7D206465660A2F47737769647468207B6475702074797065202F737472696E6774797065206571207B737472696E6777696474687D207B706F7020286E2920737472696E6777696474687D206966656C73657D206465660A2F4D467769647468207B302065786368207B206475702035206765742033206765207B2035206765742033206571207B2030207D207B20706F70207D206966656C7365207D0A207B6475702033206765747B647570206475702030206765742066696E64666F6E742065786368203120676574207363616C65666F6E7420736574666F6E740A20202020203620676574204773776964746820706F70206164647D207B706F707D206966656C73657D206966656C73657D20666F72616C6C7D206465660A2F4D4C73686F77207B2063757272656E74706F696E74207374726F6B65204D0A202030206578636820520A2020426C61636B74657874207B677361766520302073657467726179204D4673686F772067726573746F72657D207B4D4673686F777D206966656C7365207D2062696E64206465660A2F4D5273686F77207B2063757272656E74706F696E74207374726F6B65204D0A20206578636820647570204D467769647468206E65672033202D3120726F6C6C20520A2020426C61636B74657874207B677361766520302073657467726179204D4673686F772067726573746F72657D207B4D4673686F777D206966656C7365207D2062696E64206465660A2F4D4373686F77207B2063757272656E74706F696E74207374726F6B65204D0A20206578636820647570204D467769647468202D32206469762033202D3120726F6C6C20520A2020426C61636B74657874207B677361766520302073657467726179204D4673686F772067726573746F72657D207B4D4673686F777D206966656C7365207D2062696E64206465660A2F585973617665202020207B205B2820292031203220747275652066616C736520332028295D207D2062696E64206465660A2F5859726573746F7265207B205B2820292031203220747275652066616C736520342028295D207D2062696E64206465660A4C6576656C312053757070726573735044464D61726B206F72200A7B7D207B0A2F53446963742031302064696374206465660A73797374656D64696374202F7064666D61726B206B6E6F776E206E6F74207B0A20207573657264696374202F7064666D61726B2073797374656D64696374202F636C656172746F6D61726B20676574207075740A7D2069660A534469637420626567696E205B0A20202F5469746C65202874656D702E657073290A20202F5375626A6563742028676E75706C6F7420706C6F74290A20202F43726561746F722028676E75706C6F7420352E302070617463686C6576656C2033290A20202F417574686F7220286D617274696E6F290A2520202F50726F64756365722028676E75706C6F74290A2520202F4B6579776F7264732028290A20202F4372656174696F6E4461746520284D6F6E204F63742033312031303A35313A32372032303136290A20202F444F43494E464F207064666D61726B0A656E640A7D206966656C73650A250A2520537570706F727420666F7220626F7865642074657874202D20457468616E2041204D657272697474204D617920323030350A250A2F496E697454657874426F78207B207573657264696374202F544279322033202D3120726F6C6C20707574207573657264696374202F544278322033202D3120726F6C6C207075740A20202020202020202020207573657264696374202F544279312033202D3120726F6C6C20707574207573657264696374202F544278312033202D3120726F6C6C207075740A092020202F426F78696E67207472756520646566207D206465660A2F457874656E6454657874426F78207B20426F78696E670A202020207B206773617665206475702066616C7365206368617270617468207061746862626F780A2020202020206475702054427932206774207B7573657264696374202F544279322033202D3120726F6C6C207075747D207B706F707D206966656C73650A2020202020206475702054427832206774207B7573657264696374202F544278322033202D3120726F6C6C207075747D207B706F707D206966656C73650A2020202020206475702054427931206C74207B7573657264696374202F544279312033202D3120726F6C6C207075747D207B706F707D206966656C73650A2020202020206475702054427831206C74207B7573657264696374202F544278312033202D3120726F6C6C207075747D207B706F707D206966656C73650A20202020202067726573746F7265207D206966207D206465660A2F506F7054657874426F78207B206E6577706174682054427831205442786D617267696E207375622054427931205442796D617267696E20737562204D0A20202020202020202020202020202054427831205442786D617267696E207375622054427932205442796D617267696E20616464204C0A092020202020202054427832205442786D617267696E206164642054427932205442796D617267696E20616464204C0A092020202020202054427832205442786D617267696E206164642054427931205442796D617267696E20737562204C20636C6F736570617468207D206465660A2F4472617754657874426F78207B20506F7054657874426F78207374726F6B65202F426F78696E672066616C7365206465667D206465660A2F46696C6C54657874426F78207B20677361766520506F7054657874426F7820312031203120736574726762636F6C6F722066696C6C2067726573746F7265202F426F78696E672066616C7365206465667D206465660A3020302030203020496E697454657874426F780A2F5442786D617267696E203230206465660A2F5442796D617267696E203230206465660A2F426F78696E672066616C7365206465660A2F7465787473686F77207B20457874656E6454657874426F78204773686F77207D206465660A250A2520726564756E64616E7420646566696E6974696F6E7320666F7220636F6D7061746962696C69747920776974682070726F6C6F6775652E7073206F6C646572207468616E20352E302E320A2F4C5442207B424C205B5D204C436220444C7D206465660A2F4C5462207B504C205B5D204C436220444C7D206465660A656E640A2525456E6450726F6C6F670A2525506167653A203120310A676E756469637420626567696E0A67736176650A646F636C69700A3530203530207472616E736C6174650A302E30353020302E303530207363616C650A3020736574677261790A6E6577706174680A2848656C766574696361292066696E64666F6E7420313430207363616C65666F6E7420736574666F6E740A4261636B67726F756E64436F6C6F722030206C742033203120726F6C6C2030206C7420657863682030206C74206F72206F72206E6F74207B4261636B67726F756E64436F6C6F72204320312E3030302030203020373230302E303020353034302E303020426F78436F6C46696C6C7D2069660A2F48656C7665746963612066696E64666F6E7420313430207363616C65666F6E7420736574666F6E740A2F767368696674202D3436206465660A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A35343620323830204D0A3633203020560A36333338203020520A2D3633203020560A7374726F6B650A34363220323830204D0A5B205B2848656C76657469636129203134302E3020302E3020747275652074727565203020282030295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A35343620383932204D0A3633203020560A36333338203020520A2D3633203020560A7374726F6B650A34363220383932204D0A5B205B2848656C76657469636129203134302E3020302E30207472756520747275652030202820302E32295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3534362031353034204D0A3633203020560A36333338203020520A2D3633203020560A7374726F6B650A3436322031353034204D0A5B205B2848656C76657469636129203134302E3020302E30207472756520747275652030202820302E34295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3534362032313136204D0A3633203020560A36333338203020520A2D3633203020560A7374726F6B650A3436322032313136204D0A5B205B2848656C76657469636129203134302E3020302E30207472756520747275652030202820302E36295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3534362032373239204D0A3633203020560A36333338203020520A2D3633203020560A7374726F6B650A3436322032373239204D0A5B205B2848656C76657469636129203134302E3020302E30207472756520747275652030202820302E38295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3534362033333431204D0A3633203020560A36333338203020520A2D3633203020560A7374726F6B650A3436322033333431204D0A5B205B2848656C76657469636129203134302E3020302E3020747275652074727565203020282031295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3534362033393533204D0A3633203020560A36333338203020520A2D3633203020560A7374726F6B650A3436322033393533204D0A5B205B2848656C76657469636129203134302E3020302E30207472756520747275652030202820312E32295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3534362034353635204D0A3633203020560A36333338203020520A2D3633203020560A7374726F6B650A3436322034353635204D0A5B205B2848656C76657469636129203134302E3020302E30207472756520747275652030202820312E34295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A35343620323830204D0A3020363320560A30203435323820520A30202D363320560A7374726F6B650A35343620313430204D0A5B205B2848656C76657469636129203134302E3020302E3020747275652074727565203020282030295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3133343620323830204D0A3020363320560A30203435323820520A30202D363320560A7374726F6B650A3133343620313430204D0A5B205B2848656C76657469636129203134302E3020302E3020747275652074727565203020282032295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3231343620323830204D0A3020363320560A30203435323820520A30202D363320560A7374726F6B650A3231343620313430204D0A5B205B2848656C76657469636129203134302E3020302E3020747275652074727565203020282034295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3239343620323830204D0A3020363320560A30203435323820520A30202D363320560A7374726F6B650A3239343620313430204D0A5B205B2848656C76657469636129203134302E3020302E3020747275652074727565203020282036295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3337343720323830204D0A3020363320560A30203435323820520A30202D363320560A7374726F6B650A3337343720313430204D0A5B205B2848656C76657469636129203134302E3020302E3020747275652074727565203020282038295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3435343720323830204D0A3020363320560A30203435323820520A30202D363320560A7374726F6B650A3435343720313430204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028203130295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3533343720323830204D0A3020363320560A30203435323820520A30202D363320560A7374726F6B650A3533343720313430204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028203132295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3631343720323830204D0A3020363320560A30203435323820520A30202D363320560A7374726F6B650A3631343720313430204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028203134295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3639343720323830204D0A3020363320560A30203435323820520A30202D363320560A7374726F6B650A3639343720313430204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028203136295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A312E30303020554C0A4C54420A4C436220736574726762636F6C6F720A3534362034383731204E0A35343620323830204C0A36343031203020560A30203435393120560A2D36343031203020560A5A207374726F6B650A312E3030302055500A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A2520426567696E20706C6F742023310A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A2F48656C7665746963612066696E64666F6E7420313430207363616C65666F6E7420736574666F6E740A4C436220736574726762636F6C6F720A363239362034373338204D0A2873696E5C28782D31365C292F5C28782D31365C292B302E3529205273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A363338302034373338204D0A333939203020560A3534362031373535204D0A363520333020560A363420333120560A363520333220560A363520333220560A363420333020560A363520323820560A363520323620560A363420323220560A363520313720560A363520313420560A3634203820560A3635203220560A3635202D3320560A3634202D3820560A3635202D313520560A3635202D323020560A3634202D323420560A3635202D333020560A3634202D333320560A3635202D333620560A3635202D333820560A3634202D343020560A3635202D333920560A3635202D333920560A3634202D333820560A3635202D333420560A3635202D333120560A3634202D323520560A3635202D323120560A3635202D313420560A3634202D3720560A3635203020560A3635203720560A363420313420560A363520323220560A363520323920560A363420333520560A363520343120560A363520343520560A363420353020560A363520353220560A363520353320560A363420353420560A363520353220560A363520353020560A363420343520560A363520343020560A363520333320560A363420323520560A363520313720560A3634203720560A3635202D3320560A3635202D313420560A3634202D323420560A3635202D333520560A3635202D343420560A3634202D353520560A3635202D363220560A3635202D373020560A3634202D373620560A3635202D383020560A3635202D383320560A3634202D383320560A3635202D383120560A3635202D373820560A3634202D373120560A3635202D363420560A3635202D353420560A3634202D343120560A3635202D323720560A3635202D313220560A3634203520560A363520323420560A363520343320560A363420363220560A363520383220560A36352031303220560A36342031323120560A36352031343020560A36352031353620560A36342031373220560A36352031383520560A36342031393720560A36352032303520560A36352032313220560A36342032313520560A36352032313520560A36352032313320560A36342032303720560A36352031393820560A36352031383720560A36342031373220560A36352031353420560A36352031333620560A36342031313320560A363520393020560A363520363620560A363420343020560A2520456E6420706C6F742023310A7374726F6B650A322E30303020554C0A4C54620A4C436220736574726762636F6C6F720A312E30303020554C0A4C54420A4C436220736574726762636F6C6F720A3534362034383731204E0A35343620323830204C0A36343031203020560A30203435393120560A2D36343031203020560A5A207374726F6B650A312E3030302055500A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A7374726F6B650A67726573746F72650A656E640A73686F77706167650A2525547261696C65720A2525446F63756D656E74466F6E74733A2048656C7665746963610A>|ps>|700px|200px||>>

  Con uno sforzo computazionale di soli 4 formiche e 4 iterazione di dunque
  36 iterazione, abbiamo un tasso di successo del 70% e con un errore del 3%
  dal massimo un successo del 90%, quando casualmente la probabilità di
  trovare il massimo sarebbe di solo 40%.

  <section|Particle Swarm Optimization >

  <subsection|Introduzione>

  Il Particle Swarm Optimization (<with|font-series|bold|PSO>) proposto nel
  1995 da Eberhart e Kenredy, e ispirato dal metodo delle formiche
  <with|font-series|bold|AS>.\ 

  In questo caso abbiamo un insieme di particelle che esplorano lo spazio di
  ricerca. Ed è un metodo adatto alla ottimiziazione di una funzione con uno
  spazio di ricerca <math|S\<subset\>\<bbb-R\><rsup|n>>, dove <math|S> è
  limitato e continuo.

  Nella metafora del comportamento animale la <with|font-series|bold|PSO>
  suppone che le particelle seguano il migliore individuo del gruppo (quello
  che conosce la migliore sorgente di cibo) ma allo stesso gli individui
  seguono anche il loro istinto e la loro esperienza personale passata.\ 

  Combinando le conoscenze personali e di gruppo (quindi quella del migliore
  individuo) si spera di trovare una soluzione ottimale (o quasi-ottimale) di
  <math|S>.

  <subsection|Algoritmo>

  Ogni particella è caratterizzata dalla sua posizione nello spazio di
  ricerca <math|S>, quindi si definisce

  <\equation*>
    x<rsub|i><around*|(|t|)>\<in\>S
  </equation*>

  La posizione della particella <math|i> al tempo <math|t>. Cascusna delle
  particelle rappresenta una soluzione possibile del problema.

  La <with|font-series|bold|PSO> è una metaeuristica a
  <underline|popolazione>, come quella delle formiche, ciò signifca che ad
  ogni iterazione avremo un numero di soluzioni uguale al numero di
  particelle, e non una sola: <math|x<rsub|i><around*|(|t|)>\<nocomma\>>,
  <math|i=1,\<ldots\>,n>.

  Il punto chiave di questa metaeuristica è che le particelle si muovono
  nello spazio <math|S> tra 2 iterazioni consecutive. Inoltre si spostano in
  funzione dalla loro velocità <math|V<rsub|i><around*|(|t|)>>.

  Per caclolare la velocità, bisogna fare capo ai principi della
  <with|font-series|bold|PSO>: ovvero seguire il migliore individuo ma allo
  stesso tempo il proprio istinto e passate esperienze.

  Si introduce <math|x<rsub|i><rsup|best><around*|(|t|)>> come il punto di
  migliore fitness osservata dalla particella <math|i> dall'inizio della sua
  tragettoria fino al tempo <math|t>.

  <\equation*>
    x<rsub|i><rsup|best><around*|(|t|)>=<around*|{|<tabular|<tformat|<table|<row|<cell|x<rsub|i><around*|(|t|)>>|<cell|>|<cell|se
    la f<around*|(|x<rsub|i><around*|(|t|)>|)> è migliore di
    f<around*|(|x<rsub|i><rsup|best><around*|(|t-1|)>|)>>>|<row|<cell|x<rsub|i><rsup|best><around*|(|t-1|)>>|<cell|>|<cell|altrimenti>>>>>|\<nobracket\>>
  </equation*>

  Questo <math|x<rsub|i><rsup|best>> è anche chiamato
  <with|font-shape|italic|local-best>.\ 

  Abbiamo bisogno di introdurre anche il concetto di
  <with|font-shape|italic|global-best>, <math|B<around*|(|t|)>>, ovvero la
  migliore soluzione trovata dal gruppo.

  <math|B<around*|(|t|)>> è dunque il migiore dei
  <with|font-shape|italic|local-best>, per tutte le <math|i=1,\<ldots\>,n>,
  per un problema di massimizzazione:

  <\equation*>
    <tabular|<tformat|<table|<row|<cell|B<around*|(|t|)>=<below|arg
    max|x<rsub|i><rsup|best>><around*|(|f<around*|(|x<rsub|i><rsup|best><around*|(|t|)>|)>|)>>|<cell|>|<cell|i=1,\<ldots\>,n>>>>>
  </equation*>

  In pratica questo implica che <math|B<around*|(|t|)>> può essere messo a
  giorno allo stesso tempo che si calcoa <math|x<rsub|i><rsup|best><around*|(|t|)>>.

  Si la tragettoria della particella <math|i>

  <center|<tabular|<tformat|<table|<row|<cell|<with|gr-mode|<tuple|edit|text-at>|gr-frame|<tuple|scale|1cm|<tuple|0.829969gw|0.470003gh>>|gr-geometry|<tuple|geometry|0.600016par|0.333344par|center>|gr-grid|<tuple|cartesian|<point|0|0>|5>|gr-grid-old|<tuple|cartesian|<point|0|0>|5>|gr-edit-grid-aspect|<tuple|<tuple|axes|none>|<tuple|1|none>|<tuple|10|none>>|gr-edit-grid|<tuple|cartesian|<point|0|0>|5>|gr-edit-grid-old|<tuple|cartesian|<point|0|0>|5>|gr-arrow-end|\<gtr\>|gr-point-style|round|gr-color|dark
  green|gr-dash-style|11100|<graphics||<point|-6.5|-2>|<point|-2|2>|<point|-2|2>|<arc|<point|-6.5|-2>|<point|-2.0|2.0>|<point|-1.71341953622354|2.0>>|<with|color|blue|arrow-end|\<gtr\>|<line|<point|-2|2>|<point|-1.0|2.0>>>|<text-at|<math|x<rsub|i><around*|(|0|)>>|<point|-6.24277|-2>>|<text-at|<math|x<rsub|i><around*|(|t|)>>|<point|-2|1.5>>|<with|color|blue|<text-at|<math|V<rsub|i><around*|(|t|)>>|<point|-1.5|2.27473724537489>>>|<with|color|red|point-style|square|<point|-2.5|-1>>|<with|color|dark
  cyan|point-style|round|<point|-5.19303|0.610366>>|<with|color|red|arrow-end|\<gtr\>|dash-style|11100|<line|<point|-2|2>|<point|-2.5|-1.0>>>|<with|color|dark
  green|arrow-end|\<gtr\>|dash-style|11100|<line|<point|-2|2>|<point|-5.19303|0.610366>>>|<with|color|red|<text-at|<math|B<around*|(|t|)>>|<point|-2|-1>>>|<with|color|dark
  green|<text-at|<math|x<rsub|i><rsup|best><around*|(|t|)>>|<point|-6|1>>>>>>>>>>>

  La particella sarà quindi attratta da:

  <\itemize>
    <item>Continuare per la direzione attuale secondo la velocità attuale
    <math|V<rsub|i><around*|(|t|)>>

    <item>Andare verso la migliore soluzione globale <math|B<around*|(|t|)>>

    <item>Andare verso la propria soluzione migliore
    <math|x<rsub|i><rsup|best><around*|(|t|)>>
  </itemize>

  Dunque andremo a calcolare <math|V<rsub|i><around*|(|t+1|)>> ponderando
  questi fattori in questo modo

  <\equation*>
    <around*|{|<tabular|<tformat|<table|<row|<cell|V<rsub|i><around*|(|t+1|)>=w
    V<rsub|i><around*|(|t|)>+C<rsub|1>r<rsub|1><around*|(|t+1|)><around*|[|x<rsub|i><rsup|best><around*|(|t|)>-x<rsub|i><around*|(|t|)>|]>+C<rsub|2>r<rsub|2><around*|(|t+1|)><around*|[|B<around*|(|t|)>-x<rsub|i><around*|(|t|)>|]>>>|<row|<cell|>>|<row|<cell|x<rsub|i><around*|(|t+1|)>=x<rsub|i><around*|(|t|)>+V<rsub|i><around*|(|t+1|)>>>>>>|\<nobracket\>>
  </equation*>

  Dove <math|w\<in\><around*|[|0,1|]>> è un coefficente di attenuzaione (una
  sorta di attrito), <math|C<rsub|1>> e <math|C<rsub|2>> sono dei coeffienti
  mentre <math|r<rsub|1>> e <math|r<rsub|2>> sono dei numeri estratti da una
  distribuzione uniforme in <math|<around*|[|0,1|]>>.\ 

  Di fatto, <math|x<rsub|i>> e <math|V<rsub|i>> sono in generale dei vettori
  nello spazio <math|\<bbb-R\><rsup|d>> e si scelgono dei fattori
  <math|r<rsub|1>> e <math|r<rsub|2>> diversi per ogni componente del vettore
  <math|V<rsub|i>>.

  Inizialmente le particelle sono distribuite a caso dentro a <math|S> e la
  velocità iniziale è nulla.

  Se una particella raggiunge un bordo di <math|S> rimbalza in dientro.\ 

  Inoltre si definisce una velocità limite <math|V<rsub|max>> per avere delle
  velocità ragionevoli.

  Il coefficente <math|C<rsub|1>> si chiama il coefficente
  <underline|cognitivo>.

  Il coefficente <math|C<rsub|2>> si chiama coefficente <underline|sociale>.

  Si suggerisce di prendere come valori <math|C<rsub|1>=C<rsub|2>=2>, mentre
  per <math|w> si prende un valore leggermente inferiore a 1, per esempio
  <math|w=0.9>.

  <subsection|Osservazioni>

  Si può dare ad ogni particella un orizzonte di visione finità in modo tale
  che il <with|font-shape|italic|global-best> sia determinato tra gli
  individui visibili (e non dall'insieme completo) dunque
  <math|B<around*|(|t|)>\<rightarrow\> B<rsub|i><around*|(|t|)>>.

  Questa conoscenza parziale può essere definita invece che per distanza per
  legami sociali tra gli individui. Quindi ogni indiviuo conosce un sotto
  insieme finito di particelle.

  La <with|font-series|bold|PSO> funziona bene in uno spazio
  <math|S\<subset\>R<rsup|d>> ma non funziona molto bene in puno spazio
  discreto di permutazioni.

  <\itemize>
    <item>Quale è la velocità in questo tipo di spazi?

    <item>L'operatore + non è definito in questo tipo di spazi:
    <math|x<around*|(|t+1|)>=x<rsub|i><around*|(|t|)>+V<rsub|i><around*|(|t+1|)>>
    come si calcola?
  </itemize>

  Esistono dunque delle varianti della <with|font-series|bold|PSO> per questo
  tipo di spazi.

  Per dei problemi di ottimizzazione continua la <with|font-series|bold|PSO>
  converge rapidamente e la qualità del risultato è comparabile con gli
  algoritmi forniti o agli algoritmi genetici (che si presenteranno in
  seguito).

  <subsection|Firefly algorithm>

  Questo è un algoritmo ispirato dalla <with|font-series|bold|PSO> e espresso
  nel caso delle lucciole che emettono della lucia per attirare le lore prede
  o dei loro simil.\ 

  Xin-Shen Yang ha introdotto questo algoritmo nel 2010 e conosce una
  popolarità crescente.

  Anche questo algoritmo è adattatato ai probelmi continui ma esistono
  varianti per i problemi combinatori.

  <subsubsection|Algoritmo>

  Ciascuna lucciola <math|i> occupa una posizione nello spazio
  <math|x<rsub|i><around*|(|t|)>\<in\>S> al tempo <math|t>. Si spera che le
  lucciole si muvano in direzione del ottimo globale di <math|S.>

  Anche in questo caso <math|S\<subset\>\<bbb-R\><rsup|d>>.

  Ciascuna lucciola <math|i> emette una luce di intensità
  <math|I<rsub|i><around*|(|t|)>> proporzionale alla fitness della posizione
  della lucciola. Per un problema di massimizzazione si potrebbe scegliere:

  <\equation*>
    I<rsub|t><around*|(|t|)>=f<around*|(|x<rsub|i><around*|(|t|)>|)>
  </equation*>

  Dove <math|f<around*|(||)> > è la fitness.

  Ad ogni iterazione si considerano tutte le coppie di lucciole (<math|i,j>),
  con <math|i\<neq\>j>. Tra le due lucciole <math|i> e <math|j> quella con la
  intensità più debole si sposterà in direzione di quella con l'intesità più
  forte.

  La lungezza dello spostamento della lucciola <math|i> verso la lucciola
  <math|j>, dove <math|I<rsub|i><around*|(|t|)>\<less\>I<rsub|j><around*|(|*t|)>>,
  dipenderà dalla attrattività <math|\<beta\>> di <math|j> percepità da
  <math|i>.

  Questa attrattività è definità come:

  <\equation*>
    \<beta\>=\<beta\><rsub|0>\<cdot\>e<rsup|-<around*|(|<frac|r<rsub|ij>|\<gamma\>>|)><rsup|2>>
  </equation*>

  Dove <math|r<rsub|ij>> è la distanza tra la lucciola <math|i> e <math|j>
  mentre <math|\<beta\><rsub|0>> è la attrittività a distanza 0 ed è
  normalmente impostata a <math|\<beta\><rsub|0>=1>. Invece <math|\<gamma\>>
  è una costante che dipende dalla sceltà delle unità per misurare la
  distanza <math|r<rsub|ij>.>

  Allora si può calcolare lo spostamente della lucciola <math|i> verso la
  lucciola <math|j> (<math|I<rsub|i><around*|(|t|)>\<less\>I<rsub|j><around*|(|t|)>>):

  <\equation*>
    x<rsub|i><around*|(|t+1|)>=x<rsub|i><around*|(|t|)>+\<beta\><rsub|0>\<cdot\>e<rsup|-<around*|(|<frac|r<rsub|ij>|\<gamma\>>|)><rsup|2>><around*|(|x<rsub|j><around*|(|t|)>-x<rsub|i><around*|(|t|)>|)>+\<alpha\><around*|(|rand<rsub|d><around*|(||)>-0.5|)>
  </equation*>

  Dove <math|rand<rsub|d><around*|(||)>> è un vettore di <math|d> componenti
  aleatori di valore compreso tra [0,1[. Il coefficente <math|\<alpha\>> è
  scelto tra 0 e 1.

  \;

  <subsection|Pseudo Code>

  <\cpp-code>
    iteration = 0

    //initialization of n firefly

    xi = rand, i=1 to n, xi in S

    //compute the initial intensity for each firefly\ 

    Ii=f(xi)

    while(not end-condition)

    {

    \ \ for i=1 to n

    \ \ {

    \ \ \ \ for j=1 to n

    \ \ \ \ {

    \ \ \ \ \ \ \ if Ii\<less\>Ij\ 

    \ \ \ \ \ \ \ {

    \ \ \ \ \ \ \ \ \ //The firefly move in direction of xj

    \ \ \ \ \ \ \ \ \ //Compute new Ii

    \ \ \ \ \ \ \ }

    \ \ \ \ }

    \ \ }

    }
  </cpp-code>

  \;

  <section|Algoritimi evolutivi>

  <subsection|Introduzione>

  E' un insieme di metaeuristiche ispirate alla evoluzione darwiniana:

  <\quote-env>
    ``Survival of the fittest.'' Darwin
  </quote-env>

  Sono delle metaeuristiche a popolazione che utilizzano dei processi di
  <underline|mutazione>, <underline|incroci> e di <underline|selezione> per
  esplorare lo spazio di ricerca <math|S>.

  Sono dei metodi apparsi negli anni 70, in particolare:

  <\itemize>
    <item>Algoritmi genetici (Holland, John)

    <item>Strategie d'evuluzione (Rechrnberg)

    <item>Programmazione genetica (Fogel e Koza)
  </itemize>

  L'idea centrale di questi metodi e' di fare emergere dei buoni individui
  copiando quello che la natura fa per creare delle specie meglio adattate al
  loro ambiente.

  <subsection|Algoritmi genetici>

  Si avra' una popolazione di individui <math|x<rsub|i>>, ciascuno
  rapressenta una soluzione possibile del problema, dunque una punto di
  <math|x<rsub|i>\<in\>S>.

  Il codaggio degli individui dentro a <math|S> e' interpretato come del
  codice genetico (DNA) dell'individuo. Per questa analogia si parla spesso
  di cromosomi per descrivere il codaggio.

  Questa specifica si chiama <underline|genotipo>. Si definisce anche il
  <underline|phenotipo> come il valore di fitness di questo individuo.

  La fitness indica inoltre il grado di adattazione di ciascun individuo,
  dunque gli individui con buon fitness sopravviveranno e evolveranno per
  trovare fitness ancora migliori.

  In seguito consideremo dei porblemi di massimizzazione della fitness. (e'
  sempre possibile considerare un problema di minimizzazione di <math|f> come
  un problema di massimizzazione di <math|-f>)

  In biologia la fitness si misura come il numero di discendenti di ogni
  individuo.

  Nel nostro contesto si parlera' dunque di <underline|generazioni> invece di
  iterazioni.

  Si avra' una popolazione al tempo <math|t>, <math|P<around*|(|t|)>>, che
  evolvera' verso una nuova popolazione al tempo <math|t+1>,
  <math|P<around*|(|t+1|)>>, la generazione seguente.

  <with|font-series|bold|NB:> In generale la dimensione della popolazione e'
  costante durante l'evoluzione.

  <subsection|Pseudo codice>

  <\cpp-code>
    generation = 0

    //inizializzazione della popolazione

    P(0)

    while (not end-condtion)

    {

    \ \ generation ++

    \ \ //compute individual fitness

    \ \ f(x[1..n]);

    \ \ //select individual

    \ \ x = select(x[1..n]);

    \ \ //crossover

    \ \ x = crossover(x);

    \ \ //mutation\ 

    \ \ x = mutation(x)

    }

    return best_individual
  </cpp-code>

  In generale il migliore individuo della generazione <math|t> e' inserito
  anche nella generazione seguente <math|t+1>, spesso sostituendo l'individuo
  peggiore.

  Infatti le operazioni di select e crossover non garantiscono che la
  generazione seguente sia <math|\<geqslant\>> di quella presente.

  Una altro modo di rapresentare l'algoritmo genetico e' il seguente:

  <\equation*>
    P<around*|(|t|)><below|\<longminus\>\<rightarrow\>|select>P<rprime|'><around*|(|t|)><below|\<longminus\>\<rightarrow\>|crossover>P<rprime|''><around*|(|t|)><below|\<longminus\>\<rightarrow\>|mutation>P<rprime|'''><around*|(|t|)>=P<around*|(|t+1|)>
  </equation*>

  Dove <math|P<around*|(|t|)>\<nocomma\>,P<rprime|'><around*|(|t|)>\<ldots\>>
  hanno tutti lo stesso numero di elementi.

  In generale la dimensione della popolazione <math|n> e' scelta tra qualche
  decina a qualche centinaia.

  La dimensione constatne della popolazione durante la evoluzione implica
  delle particolarita' per il select e crossover.

  In generale la popolazione <math|P<around*|(|0|)>> iniziale e' aleatoria.\ 

  La condizione di arresto puo' essere un numero massimo di generazioni, o un
  tempo di stagnazione della fitness.

  <subsubsection|Selezione>

  L'obbiettivo della selezione e' di scegliere in <math|P<around*|(|t|)>>
  degli individui che seranno presenti nella fase di crossover.

  Si costruice <math|P<rprime|'><around*|(|t|)>> con un estrazione con
  rimessa (ovvero gli elementi vengo conservati nell'array originale) di
  <math|n> individui da <math|P<around*|(|t|)>>.

  Tra gli <math|n > elementi di <math|P<rprime|'><around*|(|t|)>> sara'
  dunque possibile che ci siano piu' individui uguali (copie).

  Altrettanto possibile che degli individui di <math|P<around*|(|t|)>> non
  siano presenti in <math|P<rprime|'><around*|(|t|)>>, quindi si estinguino.

  La distribuzione della estrazione non e' uniforme ma dipendera' alla
  fitness degli individui.

  Possibili modi di selezione sono:

  <\itemize>
    <item>La probabilita' proporzionale alla fitness, la probabilita'
    dell'individuo <math|i> sara'\ 

    <\equation*>
      p<rsub|i>=<frac|f<rsub|i>|<big|sum><rsup|n><rsub|j=1>f<rsub|j>>
    </equation*>

    dove <math|f> e' la fitness dell'individuo.

    <item>Selezione per tornei\ 

    <item>Selezione per rang
  </itemize>

  Quest'ultimi saranno discussi in seguito.

  <subsubsection|Crossover>

  In questa fase si prendono gli <math|n >individui (genitor) di
  <math|P<rprime|'><around*|(|t|)>> per creare gli <math|n> individui
  (discendenti) di <math|P<rprime|''><around*|(|t|)>>.

  Per fare cio' si prendereanno gli individui a coppie e ogni 2 genitori
  creara' 2 discendenti.

  Per fare cio' le coppie saranno create cosi:

  <\equation*>
    <around*|(|s<rsub|1>,s<rsub|2>|)>,<around*|(|s<rsub|3>,s<rsub|4>|)>\<ldots\><around*|(|s<rsub|i>,s<rsub|i+1>|)>\<ldots\><around*|(|s<rsub|n-1>,s<rsub|n>|)>
  </equation*>

  Dove <math|s<rsub|j>> e' un individuo di <math|P<rprime|'><around*|(|t|)>>.

  Cosi si avranno <math|<frac|n|2>> coppie di genitori uniche.

  Si difinisce una probabilita' \ di crossover <math|p<rsub|cr>> per ogni
  coppia:

  <\equation*>
    <tabular|<tformat|<cwith|1|-1|1|-1|cell-halign|c>|<table|<row|<cell|<around*|(|s<rsub|1>,s<rsub|2>|)>>|<cell|\<ldots\>>|<cell|<around*|(|s<rsub|n-1>,s<rsub|n>|)>>>|<row|<cell|\<downarrow\>p<rsub|cr>>|<cell|\<ldots\>>|<cell|\<downarrow\>p<rsub|cr>>>|<row|<cell|<around*|(|s<rprime|'><rsub|1>,s<rsub|2><rprime|'>|)>>|<cell|\<ldots\>>|<cell|<around*|(|s<rprime|'><rsub|n-1>,s<rprime|'><rsub|n>|)>>>>>>
  </equation*>

  Con probabilita' 1-<math|p<rsub|cr>> per la coppia
  <math|<around*|(|s<rsub|i>,s<rsub|i+1>|)>> la coppia non produrra
  discendenti ma verra' trasferita uguale in
  <math|P<rprime|''><around*|(|t|)>>.

  I discendenti sono prodotti a partire dei genotipi dei genitori
  mescolandoli tra loro:

  <\eqnarray*>
    <tformat|<table|<row|<cell|s<rsub|i>>|<cell|>|<cell|<around*|[|A<rsub|i>,B<rsub|i>|]>>>|<row|<cell|s<rsub|i+1>>|<cell|>|<cell|<around*|[|A<rsub|i+1>,B<rsub|i+1>|]>>>|<row|<cell|>|<cell|>|<cell|Allora
    i discendenti saranno>>|<row|<cell|s<rprime|'><rsub|i>>|<cell|>|<cell|<around*|[|A<rsub|i>,B<rsub|i+1>|]>>>|<row|<cell|s<rprime|'><rsub|i+1>>|<cell|>|<cell|<around*|[|A<rsub|i+1>,B<rsub|i>|]>>>>>
  </eqnarray*>

  Secondo il tipo di problema il crossover puo' essere creato in modi diversi
  (per esempio per il TSP).

  <subsubsection|Mutazione>

  Su ciascun degli <math|n> individui di <math|P<rprime|''><around*|(|t|)>>
  si applicano delle trasformazioni casuali al codice genetico con
  probabilita' <math|p<rsub|mt>>.

  Per esempio si potrebbero invertire ciascun bit con probabilita'
  <math|p<rsub|mt>>.

  \ 

  <subsubsection|Diversificazione VS Intensificazione>

  La Selezione favorisce l'intenficazione mentre la mutazione favorisce alla
  diversificazione. Infine il crossover contribuisce ad entrambi i fattori.

  Gl <with|font-series|bold|AG> hanno piu' parametri di guida:

  <\itemize>
    <item><math|n> la dimensione della popolazione

    <item><math|p<rsub|cr>> la probabilita' di crossover

    <item><math|p<rsub|mt>> la probabilita' di mutazione
  </itemize>

  <subsection|Esempio>

  Vogliamo un <with|font-series|bold|AG> per risolvere il problema
  <with|font-series|bold|MaxOne>, ovvero trovare la seguenza di bit
  <math|x<rsub|1>,\<ldots\>,x<rsub|l>> che massimizza;

  <\equation*>
    f<around*|(|x|)>=<big|sum><rsup|l><rsub|i=1>x<rsub|i>
  </equation*>

  Ovviamente l'ottimo e' <math|x=1111\<ldots\>1>.

  Studieremo in dettaglio un <with|font-series|bold|AG> con <math|n=6>
  individui e per un problema <with|font-series|bold|MaxOne> di dimensione
  <math|l=10> bits.

  Si supponga la seguente popolazione iniziale:

  <\eqnarray*>
    <tformat|<table|<row|<cell|P<around*|(|0|)>>|<cell|fitness>|<cell|Probabilita<rprime|'>>>|<row|<cell|s<rsub|1>=1111010101>|<cell|f<around*|(|s<rsub|1>|)>=7>|<cell|p<rsub|1>=0.206>>|<row|<cell|s<rsub|2>=0111000101>|<cell|f<around*|(|s<rsub|2>|)>=5>|<cell|\<vdots\>>>|<row|<cell|s<rsub|3>=1110110101>|<cell|f<around*|(|s<rsub|3>|)>=7>|<cell|\<vdots\>>>|<row|<cell|s<rsub|4>=0100010011>|<cell|f<around*|(|s<rsub|4>|)>=4>|<cell|\<vdots\>>>|<row|<cell|s<rsub|5>=1110111101>|<cell|f<around*|(|s<rsub|5>|)>=8>|<cell|\<vdots\>>>|<row|<cell|s<rsub|6>=0100110000>|<cell|f<around*|(|s<rsub|6>|)>=3>|<cell|p<rsub|6>=0.09>>|<row|<cell|>|<cell|f<around*|(|P<around*|(|0|)>|)>=34>|<cell|>>>>
  </eqnarray*>

  Per la <with|font-series|bold|selezione> usiamo la probabilita'
  proporzionale al fitness:\ 

  <\equation*>
    p<rsub|i>=<frac|f<around*|(|s<rsub|i>|)>|f<around*|(|P<around*|(|0|)>|)>>=<frac|f<around*|(|s<rsub|i>|)>|34>
  </equation*>

  Si estrae dunque <math|P<rprime|'><around*|(|0|)>>

  <\equation*>
    P<rprime|'><around*|(|0|)>=<around*|[|s<rprime|'><rsub|1>=s<rsub|1>,s<rprime|'><rsub|2>=s<rsub|3>,s<rprime|'><rsub|3>=s<rsub|5>,s<rprime|'><rsub|4>=s<rsub|2>,s<rprime|'><rsub|5>=s<rsub|4>,s<rsub|6><rprime|'>=s<rsub|5>|]>
  </equation*>

  Si noti che <math|s<rsub|5>> e' stato selezionato 2 volte mentre
  <math|s<rsub|6>> 0.

  Per la fase di <with|font-series|bold|crossing> per ogni coppia
  <math|<around*|(|s<rsub|i>,s<rsub|i+1>|)>> si scegliera' di di fare un
  crossing con probabilita' <math|p<rsub|cr>> e dunque generare una coppia di
  figli, altrimenti questi verranno trasferiti in
  <math|P<rprime|''><around*|(|0|)>>.

  Prenderemo in questo caso una <math|p<rsub|cr>=0.6> e supponiamo che solo
  le coppie <math|<around*|(|s<rprime|'><rsub|1>,s<rprime|'><rsub|2>|)>> e
  <math|<around*|(|s<rprime|'><rsub|5>,s<rsub|6><rprime|'>|)>> generaranno
  degli ibridi.\ 

  Per la prima coppia avremo un punto di incrocio <math|k=2>:

  <\equation*>
    <tabular|<tformat|<table|<row|<cell|s<rprime|'><rsub|1>=11\<cdot\>11010101>>|<row|<cell|s<rprime|'><rsub|2>=11\<cdot\>10110101>>>>>
  </equation*>

  Dunque dopo il crossing otteneremo

  <\equation*>
    <tabular|<tformat|<table|<row|<cell|s<rprime|''><rsub|1>=11\<cdot\>10110101=s<rsub|2><rprime|'>>>|<row|<cell|s<rsub|2><rprime|''>=11\<cdot\>11010101=s<rsub|1><rprime|'>>>>>>
  </equation*>

  Non ci sara' duqneu nessun ammiglioramente in quanto la sequenza di bit
  prima del punto di incrocio e' uguale per tute e due gli individui.

  Per la seconda coppia di il punto di incrocio <math|k=5>

  <\equation*>
    <tabular|<tformat|<table|<row|<cell|s<rprime|'><rsub|5>=01000\<cdot\>10011>>|<row|<cell|s<rprime|'><rsub|6>=11101\<cdot\>11101>>>>>
  </equation*>

  Dopo il crossing

  <\equation*>
    <tabular|<tformat|<table|<row|<cell|s<rsub|5><rprime|''>=01000\<cdot\>11101>>|<row|<cell|s<rsub|6><rprime|''>=11101\<cdot\>10011>>>>>
  </equation*>

  Questa volta i due individui generati sono davvero differenti.

  Ricapitolando la popolazione <math|P<rprime|''><around*|(|0|)>> sara
  dunque:

  <\eqnarray*>
    <tformat|<table|<row|<cell|P<rprime|''><around*|(|0|)>>|<cell|>|<cell|P<rprime|'''><around*|(|0|)>=P<around*|(|1|)>>>|<row|<cell|s<rsub|1><rprime|''>=1111010101>|<cell|\<rightarrow\>>|<cell|s<rsub|1><rprime|'''>=1111<with|font-series|medium|<with|color|red|1>>10101\<rightarrow\>f<rsub|1>=8>>|<row|<cell|s<rsub|2><rprime|''>=1110110101>|<cell|\<rightarrow\>>|<cell|s<rsub|2><rprime|'''>=11101<with|color|red|<with|font-series|bold|<with|font-series|medium|0>>>0101\<rightarrow\>f<rsub|2>=6>>|<row|<cell|s<rsub|3><rprime|''>=1110111101>|<cell|\<rightarrow\>>|<cell|s<rsub|3><rprime|'''>=11101<with|color|red|<with|font-series|medium|0>>11<with|font-series|medium|<with|color|red|1>>1\<rightarrow\>f<rsub|3>=8>>|<row|<cell|s<rsub|4><rprime|''>=0111000101>|<cell|\<rightarrow\>>|<cell|s<rsub|4><rprime|'''>=0111000101\<rightarrow\>f<rsub|4>=5>>|<row|<cell|s<rsub|5><rprime|''>=0100011101>|<cell|\<rightarrow\>>|<cell|s<rsub|5><rprime|'''>=0100011101\<rightarrow\>f<rsub|5>=5>>|<row|<cell|s<rsub|6><rprime|''>=1110110011>|<cell|\<rightarrow\>>|<cell|s<rsub|6><rprime|'''>=11101100<with|font-series|bold|<with|font-series|medium|<with|color|red|1>>>1\<rightarrow\>f<rsub|6>=6>>>>
  </eqnarray*>

  Per la <with|font-series|bold|mutazione> ogni bit della catena avra' una
  probabilita' di essere invertito di <math|<frac|1|10>>.

  Questo significa che in media saranno invertiti 6 bit sui 60 totatli della
  popolazione.

  Dunque la fitness totale di <math|P<around*|(|1|)>> = 36 mentre quella di
  <math|P<around*|(|0|)>=34>, ovvero <math|\<backsim\>10%> di
  ammigliorazione.

  <subsubsection|Esempio piu' realistico>

  Un esempio piu' realistico puo' essere uno con la seguente configurazioni:

  <math|n=100>, <math|l=128>, <with|font-series|bold|MaxOne>,
  <math|p<rsub|cr>=0.8> e <math|p<rsub|mt>=0.05>

  <with|prog-scripts|gnuplot|<center|<image|<tuple|<#252150532D41646F62652D322E3020455053462D322E300A25255469746C653A2074656D702E6570730A252543726561746F723A20676E75706C6F7420352E302070617463686C6576656C20330A25254372656174696F6E446174653A204D6F6E204E6F762020372031333A33373A353220323031360A2525446F63756D656E74466F6E74733A20286174656E64290A2525426F756E64696E67426F783A20353020353020343130203330320A2525456E64436F6D6D656E74730A2525426567696E50726F6C6F670A2F676E7564696374203235362064696374206465660A676E756469637420626567696E0A250A252054686520666F6C6C6F77696E6720747275652F66616C736520666C616773206D6179206265206564697465642062792068616E6420696620646573697265642E0A252054686520756E6974206C696E6520776964746820616E6420677261797363616C6520696D6167652067616D6D6120636F7272656374696F6E206D617920616C736F206265206368616E6765642E0A250A2F436F6C6F722066616C7365206465660A2F426C61636B746578742066616C7365206465660A2F536F6C69642066616C7365206465660A2F446173686C656E6774682031206465660A2F4C616E6473636170652066616C7365206465660A2F4C6576656C312066616C7365206465660A2F4C6576656C332066616C7365206465660A2F526F756E6465642066616C7365206465660A2F436C6970546F426F756E64696E67426F782066616C7365206465660A2F53757070726573735044464D61726B2066616C7365206465660A2F5472616E73706172656E745061747465726E732066616C7365206465660A2F676E756C696E65776964746820352E303030206465660A2F757365726C696E65776964746820676E756C696E657769647468206465660A2F47616D6D6120312E30206465660A2F4261636B67726F756E64436F6C6F72207B2D312E303030202D312E303030202D312E3030307D206465660A250A2F767368696674202D3436206465660A2F646C31207B0A202031302E3020446173686C656E67746820757365726C696E65776964746820676E756C696E65776964746820646976206D756C206D756C206D756C0A2020526F756E646564207B2063757272656E746C696E65776964746820302E3735206D756C20737562206475702030206C65207B20706F7020302E3031207D206966207D2069660A7D206465660A2F646C32207B0A202031302E3020446173686C656E67746820757365726C696E65776964746820676E756C696E65776964746820646976206D756C206D756C206D756C0A2020526F756E646564207B2063757272656E746C696E65776964746820302E3735206D756C20616464207D2069660A7D206465660A2F6870745F2033312E35206465660A2F7670745F2033312E35206465660A2F687074206870745F206465660A2F767074207670745F206465660A2F646F636C6970207B0A2020436C6970546F426F756E64696E67426F78207B0A202020206E657770617468203530203530206D6F7665746F20343130203530206C696E65746F2034313020333032206C696E65746F20353020333032206C696E65746F20636C6F7365706174680A20202020636C69700A20207D2069660A7D206465660A250A2520476E75706C6F742050726F6C6F672056657273696F6E20352E3120284F63742032303135290A250A252F53757070726573735044464D61726B2074727565206465660A250A2F4D207B6D6F7665746F7D2062696E64206465660A2F4C207B6C696E65746F7D2062696E64206465660A2F52207B726D6F7665746F7D2062696E64206465660A2F56207B726C696E65746F7D2062696E64206465660A2F4E207B6E657770617468206D6F7665746F7D2062696E64206465660A2F5A207B636C6F7365706174687D2062696E64206465660A2F43207B736574726762636F6C6F727D2062696E64206465660A2F66207B726C696E65746F2066696C6C7D2062696E64206465660A2F67207B736574677261797D2062696E64206465660A2F4773686F77207B73686F777D2064656620202025204D6179206265207265646566696E6564206C6174657220696E207468652066696C6520746F20737570706F7274205554462D380A2F76707432207670742032206D756C206465660A2F68707432206870742032206D756C206465660A2F4C73686F77207B63757272656E74706F696E74207374726F6B65204D2030207673686966742052200A09426C61636B74657874207B677361766520302073657467726179207465787473686F772067726573746F72657D207B7465787473686F777D206966656C73657D206465660A2F5273686F77207B63757272656E74706F696E74207374726F6B65204D2064757020737472696E67776964746820706F70206E65672076736869667420520A09426C61636B74657874207B677361766520302073657467726179207465787473686F772067726573746F72657D207B7465787473686F777D206966656C73657D206465660A2F4373686F77207B63757272656E74706F696E74207374726F6B65204D2064757020737472696E67776964746820706F70202D3220646976207673686966742052200A09426C61636B74657874207B677361766520302073657467726179207465787473686F772067726573746F72657D207B7465787473686F777D206966656C73657D206465660A2F5550207B647570207670745F206D756C202F767074206578636820646566206870745F206D756C202F6870742065786368206465660A20202F68707432206870742032206D756C20646566202F76707432207670742032206D756C206465667D206465660A2F444C207B436F6C6F72207B736574726762636F6C6F7220536F6C6964207B706F70205B5D7D206966203020736574646173687D0A207B706F7020706F7020706F702030207365746772617920536F6C6964207B706F70205B5D7D206966203020736574646173687D206966656C73657D206465660A2F424C207B7374726F6B6520757365726C696E6577696474682032206D756C207365746C696E6577696474680A09526F756E646564207B31207365746C696E656A6F696E2031207365746C696E656361707D2069667D206465660A2F414C207B7374726F6B6520757365726C696E657769647468203220646976207365746C696E6577696474680A09526F756E646564207B31207365746C696E656A6F696E2031207365746C696E656361707D2069667D206465660A2F554C207B64757020676E756C696E657769647468206D756C202F757365726C696E6577696474682065786368206465660A096475702031206C74207B706F7020317D206966203130206D756C202F75646C2065786368206465667D206465660A2F504C207B7374726F6B6520757365726C696E657769647468207365746C696E6577696474680A09526F756E646564207B31207365746C696E656A6F696E2031207365746C696E656361707D2069667D206465660A332E38207365746D697465726C696D69740A2520436C6173736963204C696E6520636F6C6F7273202876657273696F6E20352E30290A2F4C4377207B31203120317D206465660A2F4C4362207B30203020307D206465660A2F4C4361207B30203020307D206465660A2F4C4330207B31203020307D206465660A2F4C4331207B30203120307D206465660A2F4C4332207B30203020317D206465660A2F4C4333207B31203020317D206465660A2F4C4334207B30203120317D206465660A2F4C4335207B31203120307D206465660A2F4C4336207B30203020307D206465660A2F4C4337207B3120302E3320307D206465660A2F4C4338207B302E3520302E3520302E357D206465660A252044656661756C742064617368207061747465726E73202876657273696F6E20352E30290A2F4C5442207B424C205B5D204C436220444C7D206465660A2F4C5477207B504C205B5D203120736574677261797D206465660A2F4C5462207B504C205B5D204C436220444C7D206465660A2F4C5461207B414C205B312075646C206D756C20322075646C206D756C5D20302073657464617368204C436120736574726762636F6C6F727D206465660A2F4C5430207B504C205B5D204C433020444C7D206465660A2F4C5431207B504C205B3220646C31203320646C325D204C433120444C7D206465660A2F4C5432207B504C205B3120646C3120312E3520646C325D204C433220444C7D206465660A2F4C5433207B504C205B3620646C31203220646C32203120646C31203220646C325D204C433320444C7D206465660A2F4C5434207B504C205B3120646C31203220646C32203620646C31203220646C32203120646C31203220646C325D204C433420444C7D206465660A2F4C5435207B504C205B3420646C31203220646C325D204C433520444C7D206465660A2F4C5436207B504C205B312E3520646C3120312E3520646C3220312E3520646C3120312E3520646C3220312E3520646C31203620646C325D204C433620444C7D206465660A2F4C5437207B504C205B3320646C31203320646C32203120646C31203320646C325D204C433720444C7D206465660A2F4C5438207B504C205B3220646C31203220646C32203220646C31203620646C325D204C433820444C7D206465660A2F534C207B5B5D203020736574646173687D206465660A2F506E74207B7374726F6B65205B5D203020736574646173682067736176652031207365746C696E65636170204D203020302056207374726F6B652067726573746F72657D206465660A2F446961207B7374726F6B65205B5D20302073657464617368203220636F70792076707420616464204D0A2020687074206E656720767074206E656720562068707420767074206E656720560A202068707420767074205620687074206E656720767074205620636C6F736570617468207374726F6B650A2020506E747D206465660A2F506C73207B7374726F6B65205B5D203020736574646173682076707420737562204D2030207670743220560A202063757272656E74706F696E74207374726F6B65204D0A2020687074206E656720767074206E65672052206870743220302056207374726F6B650A207D206465660A2F426F78207B7374726F6B65205B5D20302073657464617368203220636F70792065786368206870742073756220657863682076707420616464204D0A2020302076707432206E656720562068707432203020562030207670743220560A202068707432206E65672030205620636C6F736570617468207374726F6B650A2020506E747D206465660A2F437273207B7374726F6B65205B5D203020736574646173682065786368206870742073756220657863682076707420616464204D0A2020687074322076707432206E656720562063757272656E74706F696E74207374726F6B65204D0A202068707432206E656720302052206870743220767074322056207374726F6B657D206465660A2F54726955207B7374726F6B65205B5D20302073657464617368203220636F70792076707420312E3132206D756C20616464204D0A2020687074206E656720767074202D312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E65672076707420312E3632206D756C205620636C6F736570617468207374726F6B650A2020506E747D206465660A2F53746172207B3220636F707920506C73204372737D206465660A2F426F7846207B7374726F6B65205B5D203020736574646173682065786368206870742073756220657863682076707420616464204D0A2020302076707432206E656720562068707432203020562030207670743220560A202068707432206E65672030205620636C6F7365706174682066696C6C7D206465660A2F5472695546207B7374726F6B65205B5D203020736574646173682076707420312E3132206D756C20616464204D0A2020687074206E656720767074202D312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E65672076707420312E3632206D756C205620636C6F7365706174682066696C6C7D206465660A2F54726944207B7374726F6B65205B5D20302073657464617368203220636F70792076707420312E3132206D756C20737562204D0A2020687074206E65672076707420312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E656720767074202D312E3632206D756C205620636C6F736570617468207374726F6B650A2020506E747D206465660A2F5472694446207B7374726F6B65205B5D203020736574646173682076707420312E3132206D756C20737562204D0A2020687074206E65672076707420312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E656720767074202D312E3632206D756C205620636C6F7365706174682066696C6C7D206465660A2F44696146207B7374726F6B65205B5D203020736574646173682076707420616464204D0A2020687074206E656720767074206E656720562068707420767074206E656720560A202068707420767074205620687074206E656720767074205620636C6F7365706174682066696C6C7D206465660A2F50656E74207B7374726F6B65205B5D20302073657464617368203220636F70792067736176650A20207472616E736C617465203020687074204D2034207B373220726F74617465203020687074204C7D207265706561740A2020636C6F736570617468207374726F6B652067726573746F726520506E747D206465660A2F50656E7446207B7374726F6B65205B5D203020736574646173682067736176650A20207472616E736C617465203020687074204D2034207B373220726F74617465203020687074204C7D207265706561740A2020636C6F7365706174682066696C6C2067726573746F72657D206465660A2F436972636C65207B7374726F6B65205B5D20302073657464617368203220636F70790A202068707420302033363020617263207374726F6B6520506E747D206465660A2F436972636C6546207B7374726F6B65205B5D2030207365746461736820687074203020333630206172632066696C6C7D206465660A2F4330207B424C205B5D20302073657464617368203220636F7079206D6F7665746F2076707420393020343530206172637D2062696E64206465660A2F4331207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F70792076707420302039302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4332207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F707920767074203930203138302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4333207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F7079207670742030203138302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4334207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F70792076707420313830203237302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4335207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F7079207670742030203930206172630A093220636F7079206D6F7665746F0A093220636F70792076707420313830203237302061726320636C6F7365706174682066696C6C0A09767074203020333630206172637D2062696E64206465660A2F4336207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F707920767074203930203237302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4337207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F7079207670742030203237302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4338207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F70792076707420323730203336302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F4339207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F70792076707420323730203435302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F433130207B424C205B5D20302073657464617368203220636F7079203220636F7079206D6F7665746F2076707420323730203336302061726320636C6F7365706174682066696C6C0A093220636F7079206D6F7665746F0A093220636F707920767074203930203138302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F433131207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F7079207670742030203138302061726320636C6F7365706174682066696C6C0A093220636F7079206D6F7665746F0A093220636F70792076707420323730203336302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F433132207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F70792076707420313830203336302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F433133207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F70792076707420302039302061726320636C6F7365706174682066696C6C0A093220636F7079206D6F7665746F0A093220636F70792076707420313830203336302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F433134207B424C205B5D20302073657464617368203220636F7079206D6F7665746F0A093220636F707920767074203930203336302061726320636C6F7365706174682066696C6C0A09767074203020333630206172637D2062696E64206465660A2F433135207B424C205B5D20302073657464617368203220636F7079207670742030203336302061726320636C6F7365706174682066696C6C0A097670742030203336302061726320636C6F7365706174687D2062696E64206465660A2F526563207B6E6577706174682034203220726F6C6C206D6F7665746F203120696E646578203020726C696E65746F2030206578636820726C696E65746F0A096E6567203020726C696E65746F20636C6F7365706174687D2062696E64206465660A2F537175617265207B647570205265637D2062696E64206465660A2F42737175617265207B767074207375622065786368207670742073756220657863682076707432205371756172657D2062696E64206465660A2F5330207B424C205B5D20302073657464617368203220636F7079206D6F7665746F20302076707420726C696E65746F20424C20427371756172657D2062696E64206465660A2F5331207B424C205B5D20302073657464617368203220636F707920767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F5332207B424C205B5D20302073657464617368203220636F707920657863682076707420737562206578636820767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F5333207B424C205B5D20302073657464617368203220636F7079206578636820767074207375622065786368207670743220767074205265632066696C6C20427371756172657D2062696E64206465660A2F5334207B424C205B5D20302073657464617368203220636F7079206578636820767074207375622065786368207670742073756220767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F5335207B424C205B5D20302073657464617368203220636F7079203220636F707920767074205371756172652066696C6C0A096578636820767074207375622065786368207670742073756220767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F5336207B424C205B5D20302073657464617368203220636F70792065786368207670742073756220657863682076707420737562207670742076707432205265632066696C6C20427371756172657D2062696E64206465660A2F5337207B424C205B5D20302073657464617368203220636F70792065786368207670742073756220657863682076707420737562207670742076707432205265632066696C6C0A093220636F707920767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F5338207B424C205B5D20302073657464617368203220636F7079207670742073756220767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F5339207B424C205B5D20302073657464617368203220636F70792076707420737562207670742076707432205265632066696C6C20427371756172657D2062696E64206465660A2F533130207B424C205B5D20302073657464617368203220636F7079207670742073756220767074205371756172652066696C6C203220636F707920657863682076707420737562206578636820767074205371756172652066696C6C0A09427371756172657D2062696E64206465660A2F533131207B424C205B5D20302073657464617368203220636F7079207670742073756220767074205371756172652066696C6C203220636F7079206578636820767074207375622065786368207670743220767074205265632066696C6C0A09427371756172657D2062696E64206465660A2F533132207B424C205B5D20302073657464617368203220636F70792065786368207670742073756220657863682076707420737562207670743220767074205265632066696C6C20427371756172657D2062696E64206465660A2F533133207B424C205B5D20302073657464617368203220636F70792065786368207670742073756220657863682076707420737562207670743220767074205265632066696C6C0A093220636F707920767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F533134207B424C205B5D20302073657464617368203220636F70792065786368207670742073756220657863682076707420737562207670743220767074205265632066696C6C0A093220636F707920657863682076707420737562206578636820767074205371756172652066696C6C20427371756172657D2062696E64206465660A2F533135207B424C205B5D20302073657464617368203220636F707920427371756172652066696C6C20427371756172657D2062696E64206465660A2F4430207B6773617665207472616E736C61746520343520726F7461746520302030205330207374726F6B652067726573746F72657D2062696E64206465660A2F4431207B6773617665207472616E736C61746520343520726F7461746520302030205331207374726F6B652067726573746F72657D2062696E64206465660A2F4432207B6773617665207472616E736C61746520343520726F7461746520302030205332207374726F6B652067726573746F72657D2062696E64206465660A2F4433207B6773617665207472616E736C61746520343520726F7461746520302030205333207374726F6B652067726573746F72657D2062696E64206465660A2F4434207B6773617665207472616E736C61746520343520726F7461746520302030205334207374726F6B652067726573746F72657D2062696E64206465660A2F4435207B6773617665207472616E736C61746520343520726F7461746520302030205335207374726F6B652067726573746F72657D2062696E64206465660A2F4436207B6773617665207472616E736C61746520343520726F7461746520302030205336207374726F6B652067726573746F72657D2062696E64206465660A2F4437207B6773617665207472616E736C61746520343520726F7461746520302030205337207374726F6B652067726573746F72657D2062696E64206465660A2F4438207B6773617665207472616E736C61746520343520726F7461746520302030205338207374726F6B652067726573746F72657D2062696E64206465660A2F4439207B6773617665207472616E736C61746520343520726F7461746520302030205339207374726F6B652067726573746F72657D2062696E64206465660A2F443130207B6773617665207472616E736C61746520343520726F746174652030203020533130207374726F6B652067726573746F72657D2062696E64206465660A2F443131207B6773617665207472616E736C61746520343520726F746174652030203020533131207374726F6B652067726573746F72657D2062696E64206465660A2F443132207B6773617665207472616E736C61746520343520726F746174652030203020533132207374726F6B652067726573746F72657D2062696E64206465660A2F443133207B6773617665207472616E736C61746520343520726F746174652030203020533133207374726F6B652067726573746F72657D2062696E64206465660A2F443134207B6773617665207472616E736C61746520343520726F746174652030203020533134207374726F6B652067726573746F72657D2062696E64206465660A2F443135207B6773617665207472616E736C61746520343520726F746174652030203020533135207374726F6B652067726573746F72657D2062696E64206465660A2F44696145207B7374726F6B65205B5D203020736574646173682076707420616464204D0A2020687074206E656720767074206E656720562068707420767074206E656720560A202068707420767074205620687074206E656720767074205620636C6F736570617468207374726F6B657D206465660A2F426F7845207B7374726F6B65205B5D203020736574646173682065786368206870742073756220657863682076707420616464204D0A2020302076707432206E656720562068707432203020562030207670743220560A202068707432206E65672030205620636C6F736570617468207374726F6B657D206465660A2F5472695545207B7374726F6B65205B5D203020736574646173682076707420312E3132206D756C20616464204D0A2020687074206E656720767074202D312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E65672076707420312E3632206D756C205620636C6F736570617468207374726F6B657D206465660A2F5472694445207B7374726F6B65205B5D203020736574646173682076707420312E3132206D756C20737562204D0A2020687074206E65672076707420312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E656720767074202D312E3632206D756C205620636C6F736570617468207374726F6B657D206465660A2F50656E7445207B7374726F6B65205B5D203020736574646173682067736176650A20207472616E736C617465203020687074204D2034207B373220726F74617465203020687074204C7D207265706561740A2020636C6F736570617468207374726F6B652067726573746F72657D206465660A2F4369726345207B7374726F6B65205B5D20302073657464617368200A202068707420302033363020617263207374726F6B657D206465660A2F4F7061717565207B677361766520636C6F736570617468203120736574677261792066696C6C2067726573746F72652030207365746772617920636C6F7365706174687D206465660A2F44696157207B7374726F6B65205B5D203020736574646173682076707420616464204D0A2020687074206E656720767074206E656720562068707420767074206E656720560A202068707420767074205620687074206E6567207670742056204F7061717565207374726F6B657D206465660A2F426F7857207B7374726F6B65205B5D203020736574646173682065786368206870742073756220657863682076707420616464204D0A2020302076707432206E656720562068707432203020562030207670743220560A202068707432206E656720302056204F7061717565207374726F6B657D206465660A2F5472695557207B7374726F6B65205B5D203020736574646173682076707420312E3132206D756C20616464204D0A2020687074206E656720767074202D312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E65672076707420312E3632206D756C2056204F7061717565207374726F6B657D206465660A2F5472694457207B7374726F6B65205B5D203020736574646173682076707420312E3132206D756C20737562204D0A2020687074206E65672076707420312E3632206D756C20560A20206870742032206D756C203020560A2020687074206E656720767074202D312E3632206D756C2056204F7061717565207374726F6B657D206465660A2F50656E7457207B7374726F6B65205B5D203020736574646173682067736176650A20207472616E736C617465203020687074204D2034207B373220726F74617465203020687074204C7D207265706561740A20204F7061717565207374726F6B652067726573746F72657D206465660A2F4369726357207B7374726F6B65205B5D20302073657464617368200A202068707420302033363020617263204F7061717565207374726F6B657D206465660A2F426F7846696C6C207B677361766520526563203120736574677261792066696C6C2067726573746F72657D206465660A2F44656E73697479207B0A20202F46696C6C64656E2065786368206465660A202063757272656E74726762636F6C6F720A20202F436F6C42206578636820646566202F436F6C47206578636820646566202F436F6C522065786368206465660A20202F436F6C5220436F6C522046696C6C64656E206D756C2046696C6C64656E20737562203120616464206465660A20202F436F6C4720436F6C472046696C6C64656E206D756C2046696C6C64656E20737562203120616464206465660A20202F436F6C4220436F6C422046696C6C64656E206D756C2046696C6C64656E20737562203120616464206465660A2020436F6C5220436F6C4720436F6C4220736574726762636F6C6F727D206465660A2F426F78436F6C46696C6C207B67736176652052656320506F6C7946696C6C7D206465660A2F506F6C7946696C6C207B67736176652044656E736974792066696C6C2067726573746F72652067726573746F72657D206465660A2F68207B726C696E65746F20726C696E65746F20726C696E65746F20677361766520636C6F7365706174682066696C6C2067726573746F72657D2062696E64206465660A250A2520506F7374536372697074204C6576656C2031205061747465726E2046696C6C20726F7574696E6520666F722072656374616E676C65730A252055736167653A207820792077206820732061205858205061747465726E46696C6C0A2509782C79203D206C6F776572206C65667420636F726E6572206F6620626F7820746F2062652066696C6C65640A2509772C68203D20776964746820616E6420686569676874206F6620626F780A2509202061203D20616E676C6520696E2064656772656573206265747765656E206C696E657320616E6420782D617869730A2509205858203D20302F3120666F72206E6F2F7965732063726F73732D68617463680A250A2F5061747465726E46696C6C207B6773617665202F504661205B2039203220726F6C6C205D206465660A20205046612030206765742050466120322067657420322064697620616464205046612031206765742050466120332067657420322064697620616464207472616E736C6174650A2020504661203220676574202D322064697620504661203320676574202D32206469762050466120322067657420504661203320676574205265630A20205472616E73706172656E745061747465726E73207B7D207B6773617665203120736574677261792066696C6C2067726573746F72657D206966656C73650A2020636C69700A202063757272656E746C696E65776964746820302E35206D756C207365746C696E6577696474680A20202F5046732050466120322067657420647570206D756C2050466120332067657420647570206D756C206164642073717274206465660A2020302030204D2050466120352067657420726F7461746520504673202D322064697620647570207472616E736C6174650A202030203120504673205046612034206765742064697620312061646420666C6F6F72206376690A097B504661203420676574206D756C2030204D20302050467320567D20666F720A20203020504661203620676574206E65207B0A0930203120504673205046612034206765742064697620312061646420666C6F6F72206376690A097B504661203420676574206D756C20302032203120726F6C6C204D20504673203020567D20666F720A207D2069660A20207374726F6B652067726573746F72657D206465660A250A2F6C616E67756167656C6576656C2077686572650A207B706F70206C616E67756167656C6576656C7D207B317D206966656C73650A6475702032206C740A097B2F496E746572707265744C6576656C312074727565206465660A09202F496E746572707265744C6576656C332066616C7365206465667D0A097B2F496E746572707265744C6576656C31204C6576656C31206465660A0920322067740A09202020207B2F496E746572707265744C6576656C33204C6576656C33206465667D0A09202020207B2F496E746572707265744C6576656C332066616C7365206465667D0A09206966656C7365207D0A206966656C73650A250A2520506F7374536372697074206C6576656C2032207061747465726E2066696C6C20646566696E6974696F6E730A250A2F4C6576656C325061747465726E46696C6C207B0A2F54696C65387838207B2F5061696E74547970652032202F5061747465726E547970652031202F54696C696E67547970652031202F42426F78205B302030203820385D202F58537465702038202F595374657020387D0A0962696E64206465660A2F4B656570436F6C6F72207B63757272656E74726762636F6C6F72205B2F5061747465726E202F4465766963655247425D20736574636F6C6F7273706163657D2062696E64206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F7020302030204D20382038204C20302038204D20382030204C207374726F6B657D200A3E3E206D6174726978206D616B657061747465726E0A2F506174312065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F7020302030204D20382038204C20302038204D20382030204C207374726F6B650A09302034204D20342038204C20382034204C20342030204C20302034204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174322065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F7020302030204D20302038204C0A09382038204C20382030204C20302030204C2066696C6C7D0A3E3E206D6174726978206D616B657061747465726E0A2F506174332065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F70202D342038204D2038202D34204C0A0930203132204D2031322030204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174342065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F70202D342030204D2038203132204C0A0930202D34204D2031322038204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174352065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F70202D322038204D2034202D34204C0A0930203132204D2038202D34204C2034203132204D2031302030204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174362065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F70202D322030204D2034203132204C0A0930202D34204D2038203132204C2034202D34204D2031302038204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174372065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F702038202D32204D202D342034204C0A0931322030204D202D342038204C2031322034204D2030203130204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174382065786368206465660A3C3C2054696C653878380A202F5061696E7450726F63207B302E35207365746C696E65776964746820706F702030202D32204D2031322034204C0A092D342030204D2031322038204C202D342034204D2038203130204C207374726F6B657D0A3E3E206D6174726978206D616B657061747465726E0A2F506174392065786368206465660A2F5061747465726E31207B5061747465726E42676E64204B656570436F6C6F722050617431207365747061747465726E7D2062696E64206465660A2F5061747465726E32207B5061747465726E42676E64204B656570436F6C6F722050617432207365747061747465726E7D2062696E64206465660A2F5061747465726E33207B5061747465726E42676E64204B656570436F6C6F722050617433207365747061747465726E7D2062696E64206465660A2F5061747465726E34207B5061747465726E42676E64204B656570436F6C6F72204C616E647363617065207B506174357D207B506174347D206966656C7365207365747061747465726E7D2062696E64206465660A2F5061747465726E35207B5061747465726E42676E64204B656570436F6C6F72204C616E647363617065207B506174347D207B506174357D206966656C7365207365747061747465726E7D2062696E64206465660A2F5061747465726E36207B5061747465726E42676E64204B656570436F6C6F72204C616E647363617065207B506174397D207B506174367D206966656C7365207365747061747465726E7D2062696E64206465660A2F5061747465726E37207B5061747465726E42676E64204B656570436F6C6F72204C616E647363617065207B506174387D207B506174377D206966656C7365207365747061747465726E7D2062696E64206465660A7D206465660A250A250A25456E64206F6620506F7374536372697074204C6576656C203220636F64650A250A2F5061747465726E42676E64207B0A20205472616E73706172656E745061747465726E73207B7D207B6773617665203120736574677261792066696C6C2067726573746F72657D206966656C73650A7D206465660A250A25205375627374697475746520666F72204C6576656C2032207061747465726E2066696C6C20636F64657320776974680A2520677261797363616C65206966204C6576656C203220737570706F7274206973206E6F742073656C65637465642E0A250A2F4C6576656C315061747465726E46696C6C207B0A2F5061747465726E31207B302E3235302044656E736974797D2062696E64206465660A2F5061747465726E32207B302E3530302044656E736974797D2062696E64206465660A2F5061747465726E33207B302E3735302044656E736974797D2062696E64206465660A2F5061747465726E34207B302E3132352044656E736974797D2062696E64206465660A2F5061747465726E35207B302E3337352044656E736974797D2062696E64206465660A2F5061747465726E36207B302E3632352044656E736974797D2062696E64206465660A2F5061747465726E37207B302E3837352044656E736974797D2062696E64206465660A7D206465660A250A25204E6F77207465737420666F7220737570706F7274206F66204C6576656C203220636F64650A250A4C6576656C31207B4C6576656C315061747465726E46696C6C7D207B4C6576656C325061747465726E46696C6C7D206966656C73650A250A2F53796D626F6C2D4F626C69717565202F53796D626F6C2066696E64666F6E74205B312030202E3136372031203020305D206D616B65666F6E740A647570206C656E677468206469637420626567696E207B3120696E646578202F464944206571207B706F7020706F707D207B6465667D206966656C73657D20666F72616C6C0A63757272656E746469637420656E6420646566696E65666F6E7420706F700A250A2F4D4673686F77207B0A2020207B2064757020352067657420332067650A20202020207B2035206765742033206571207B67736176657D207B67726573746F72657D206966656C7365207D0A20202020207B647570206475702030206765742066696E64666F6E742065786368203120676574207363616C65666F6E7420736574666F6E740A20202020205B2063757272656E74706F696E74205D206578636820647570203220676574203020657863682052206475702035206765742032206E65207B6475702064757020360A20202020206765742065786368203420676574207B7465787473686F777D207B737472696E67776964746820706F70203020527D206966656C7365207D69662064757020352067657420302065710A20202020207B647570203320676574207B3220676574206E656720302065786368205220706F707D207B706F7020616C6F616420706F70204D7D206966656C73657D207B64757020350A20202020206765742031206571207B647570203220676574206578636820647570203320676574206578636820362067657420737472696E67776964746820706F70202D32206469760A2020202020647570203020527D207B64757020362067657420737472696E67776964746820706F70202D3220646976203020522036206765740A20202020207465787473686F77203220696E646578207B616C6F616420706F70204D206E65672033202D3120726F6C6C206E6567205220706F7020706F707D207B706F7020706F7020706F700A2020202020706F7020616C6F616420706F70204D7D206966656C7365207D6966656C7365207D6966656C7365207D0A20202020206966656C7365207D0A202020666F72616C6C7D206465660A2F47737769647468207B6475702074797065202F737472696E6774797065206571207B737472696E6777696474687D207B706F7020286E2920737472696E6777696474687D206966656C73657D206465660A2F4D467769647468207B302065786368207B206475702035206765742033206765207B2035206765742033206571207B2030207D207B20706F70207D206966656C7365207D0A207B6475702033206765747B647570206475702030206765742066696E64666F6E742065786368203120676574207363616C65666F6E7420736574666F6E740A20202020203620676574204773776964746820706F70206164647D207B706F707D206966656C73657D206966656C73657D20666F72616C6C7D206465660A2F4D4C73686F77207B2063757272656E74706F696E74207374726F6B65204D0A202030206578636820520A2020426C61636B74657874207B677361766520302073657467726179204D4673686F772067726573746F72657D207B4D4673686F777D206966656C7365207D2062696E64206465660A2F4D5273686F77207B2063757272656E74706F696E74207374726F6B65204D0A20206578636820647570204D467769647468206E65672033202D3120726F6C6C20520A2020426C61636B74657874207B677361766520302073657467726179204D4673686F772067726573746F72657D207B4D4673686F777D206966656C7365207D2062696E64206465660A2F4D4373686F77207B2063757272656E74706F696E74207374726F6B65204D0A20206578636820647570204D467769647468202D32206469762033202D3120726F6C6C20520A2020426C61636B74657874207B677361766520302073657467726179204D4673686F772067726573746F72657D207B4D4673686F777D206966656C7365207D2062696E64206465660A2F585973617665202020207B205B2820292031203220747275652066616C736520332028295D207D2062696E64206465660A2F5859726573746F7265207B205B2820292031203220747275652066616C736520342028295D207D2062696E64206465660A4C6576656C312053757070726573735044464D61726B206F72200A7B7D207B0A2F53446963742031302064696374206465660A73797374656D64696374202F7064666D61726B206B6E6F776E206E6F74207B0A20207573657264696374202F7064666D61726B2073797374656D64696374202F636C656172746F6D61726B20676574207075740A7D2069660A534469637420626567696E205B0A20202F5469746C65202874656D702E657073290A20202F5375626A6563742028676E75706C6F7420706C6F74290A20202F43726561746F722028676E75706C6F7420352E302070617463686C6576656C2033290A20202F417574686F7220286D617274696E6F290A2520202F50726F64756365722028676E75706C6F74290A2520202F4B6579776F7264732028290A20202F4372656174696F6E4461746520284D6F6E204E6F762020372031333A33373A35322032303136290A20202F444F43494E464F207064666D61726B0A656E640A7D206966656C73650A250A2520537570706F727420666F7220626F7865642074657874202D20457468616E2041204D657272697474204D617920323030350A250A2F496E697454657874426F78207B207573657264696374202F544279322033202D3120726F6C6C20707574207573657264696374202F544278322033202D3120726F6C6C207075740A20202020202020202020207573657264696374202F544279312033202D3120726F6C6C20707574207573657264696374202F544278312033202D3120726F6C6C207075740A092020202F426F78696E67207472756520646566207D206465660A2F457874656E6454657874426F78207B20426F78696E670A202020207B206773617665206475702066616C7365206368617270617468207061746862626F780A2020202020206475702054427932206774207B7573657264696374202F544279322033202D3120726F6C6C207075747D207B706F707D206966656C73650A2020202020206475702054427832206774207B7573657264696374202F544278322033202D3120726F6C6C207075747D207B706F707D206966656C73650A2020202020206475702054427931206C74207B7573657264696374202F544279312033202D3120726F6C6C207075747D207B706F707D206966656C73650A2020202020206475702054427831206C74207B7573657264696374202F544278312033202D3120726F6C6C207075747D207B706F707D206966656C73650A20202020202067726573746F7265207D206966207D206465660A2F506F7054657874426F78207B206E6577706174682054427831205442786D617267696E207375622054427931205442796D617267696E20737562204D0A20202020202020202020202020202054427831205442786D617267696E207375622054427932205442796D617267696E20616464204C0A092020202020202054427832205442786D617267696E206164642054427932205442796D617267696E20616464204C0A092020202020202054427832205442786D617267696E206164642054427931205442796D617267696E20737562204C20636C6F736570617468207D206465660A2F4472617754657874426F78207B20506F7054657874426F78207374726F6B65202F426F78696E672066616C7365206465667D206465660A2F46696C6C54657874426F78207B20677361766520506F7054657874426F7820312031203120736574726762636F6C6F722066696C6C2067726573746F7265202F426F78696E672066616C7365206465667D206465660A3020302030203020496E697454657874426F780A2F5442786D617267696E203230206465660A2F5442796D617267696E203230206465660A2F426F78696E672066616C7365206465660A2F7465787473686F77207B20457874656E6454657874426F78204773686F77207D206465660A250A2520726564756E64616E7420646566696E6974696F6E7320666F7220636F6D7061746962696C69747920776974682070726F6C6F6775652E7073206F6C646572207468616E20352E302E320A2F4C5442207B424C205B5D204C436220444C7D206465660A2F4C5462207B504C205B5D204C436220444C7D206465660A656E640A2525456E6450726F6C6F670A2525506167653A203120310A676E756469637420626567696E0A67736176650A646F636C69700A3530203530207472616E736C6174650A302E30353020302E303530207363616C650A3020736574677261790A6E6577706174680A2848656C766574696361292066696E64666F6E7420313430207363616C65666F6E7420736574666F6E740A4261636B67726F756E64436F6C6F722030206C742033203120726F6C6C2030206C7420657863682030206C74206F72206F72206E6F74207B4261636B67726F756E64436F6C6F72204320312E3030302030203020373230302E303020353034302E303020426F78436F6C46696C6C7D2069660A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A36383620343438204D0A3633203020560A36313938203020520A2D3633203020560A7374726F6B650A36303220343438204D0A5B205B2848656C76657469636129203134302E3020302E3020747275652074727565203020282030295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3638362031313339204D0A3633203020560A36313938203020520A2D3633203020560A7374726F6B650A3630322031313339204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028203230295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3638362031383330204D0A3633203020560A36313938203020520A2D3633203020560A7374726F6B650A3630322031383330204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028203430295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3638362032353231204D0A3633203020560A36313938203020520A2D3633203020560A7374726F6B650A3630322032353231204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028203630295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3638362033323132204D0A3633203020560A36313938203020520A2D3633203020560A7374726F6B650A3630322033323132204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028203830295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3638362033393033204D0A3633203020560A36313938203020520A2D3633203020560A7374726F6B650A3630322033393033204D0A5B205B2848656C76657469636129203134302E3020302E30207472756520747275652030202820313030295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3638362034353935204D0A3633203020560A36313938203020520A2D3633203020560A7374726F6B650A3630322034353935204D0A5B205B2848656C76657469636129203134302E3020302E30207472756520747275652030202820313230295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A36383620343438204D0A3020363320560A30203433363020520A30202D363320560A7374726F6B650A36383620333038204D0A5B205B2848656C76657469636129203134302E3020302E3020747275652074727565203020282030295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3139333820343438204D0A3020363320560A30203433363020520A30202D363320560A7374726F6B650A3139333820333038204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028203230295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3331393020343438204D0A3020363320560A30203433363020520A30202D363320560A7374726F6B650A3331393020333038204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028203430295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3434343320343438204D0A3020363320560A30203433363020520A30202D363320560A7374726F6B650A3434343320333038204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028203630295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3536393520343438204D0A3020363320560A30203433363020520A30202D363320560A7374726F6B650A3536393520333038204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028203830295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A3639343720343438204D0A3020363320560A30203433363020520A30202D363320560A7374726F6B650A3639343720333038204D0A5B205B2848656C76657469636129203134302E3020302E30207472756520747275652030202820313030295D0A5D202D34362E37204D4373686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A312E30303020554C0A4C54420A4C436220736574726762636F6C6F720A3638362034383731204E0A36383620343438204C0A36323631203020560A30203434323320560A2D36323631203020560A5A207374726F6B650A312E3030302055500A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A4C436220736574726762636F6C6F720A3131322032363539204D0A63757272656E74706F696E74206773617665207472616E736C617465202D32373020726F7461746520302030206D6F7665746F0A5B205B2848656C76657469636129203134302E3020302E3020747275652074727565203020286669746E657373295D0A5D202D34362E37204D4373686F770A67726573746F72650A4C54620A4C436220736574726762636F6C6F720A33383136203938204D0A5B205B2848656C76657469636129203134302E3020302E30207472756520747275652030202867656E65726174696F6E295D0A5D202D34362E37204D4373686F770A4C54620A2520426567696E20706C6F742023310A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A4C436220736574726762636F6C6F720A363239362034373338204D0A5B205B2848656C76657469636129203134302E3020302E302074727565207472756520302028665C28505C28745C295C29295D0A5D202D34362E37204D5273686F770A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A363338302034373338204D0A333939203020560A3638362032353231204D0A36332033363220560A36332032313120560A36342031353020560A36332031313620560A363320393420560A363320383020560A363420373020560A363320363120560A363320353420560A363320353020560A363420343520560A363320343220560A363320333820560A363320333620560A363420333320560A363320333220560A363320323920560A363320323820560A363420323720560A363320323520560A363320323420560A363320323320560A363420323320560A363320323120560A363320323020560A363320323020560A363420313820560A363320313920560A363320313720560A363320313720560A363420313720560A363320313620560A363320313520560A363320313520560A363320313520560A363420313420560A363320313420560A363320313320560A363320313320560A363420313320560A363320313320560A363320313220560A363320313220560A363420313120560A363320313220560A363320313120560A363320313120560A363420313120560A363320313020560A363320313020560A363320313020560A363420313020560A363320313020560A3633203920560A363320313020560A3634203920560A3633203920560A3633203920560A3633203920560A3634203820560A3633203920560A3633203820560A3633203820560A3634203820560A3633203820560A3633203820560A3633203720560A3633203820560A3634203720560A3633203820560A3633203720560A3633203720560A3634203720560A3633203720560A3633203720560A3633203720560A3634203720560A3633203620560A3633203720560A3633203620560A3634203720560A3633203620560A3633203620560A3633203620560A3634203620560A3633203620560A3633203620560A3633203620560A3634203620560A3633203620560A3633203520560A39203120560A2520456E6420706C6F742023310A7374726F6B650A322E30303020554C0A4C54620A4C436220736574726762636F6C6F720A312E30303020554C0A4C54420A4C436220736574726762636F6C6F720A3638362034383731204E0A36383620343438204C0A36323631203020560A30203434323320560A2D36323631203020560A5A207374726F6B650A312E3030302055500A312E30303020554C0A4C54620A4C436220736574726762636F6C6F720A7374726F6B650A67726573746F72650A656E640A73686F77706167650A2525547261696C65720A2525446F63756D656E74466F6E74733A2048656C7665746963610A>|ps>||||>>>

  In circa 60 generazioni l'algoritmo converge e trova la soluzione migliore.

  \;
</body>

<\references>
  <\collection>
    <associate|auto-1|<tuple|1|1>>
    <associate|auto-10|<tuple|2.2|9>>
    <associate|auto-11|<tuple|2.2.1|9>>
    <associate|auto-12|<tuple|2.3|10>>
    <associate|auto-13|<tuple|2.3.1|10>>
    <associate|auto-14|<tuple|2.3.2|11>>
    <associate|auto-15|<tuple|3|11>>
    <associate|auto-16|<tuple|3.1|11>>
    <associate|auto-17|<tuple|3.2|12>>
    <associate|auto-18|<tuple|3.3|13>>
    <associate|auto-19|<tuple|3.4|13>>
    <associate|auto-2|<tuple|1.1|1>>
    <associate|auto-20|<tuple|3.4.1|13>>
    <associate|auto-21|<tuple|3.5|?>>
    <associate|auto-22|<tuple|4|?>>
    <associate|auto-23|<tuple|4.1|?>>
    <associate|auto-24|<tuple|4.2|?>>
    <associate|auto-25|<tuple|4.3|?>>
    <associate|auto-26|<tuple|4.3.1|?>>
    <associate|auto-27|<tuple|4.3.2|?>>
    <associate|auto-28|<tuple|4.3.3|?>>
    <associate|auto-29|<tuple|4.3.4|?>>
    <associate|auto-3|<tuple|1.2|3>>
    <associate|auto-30|<tuple|4.4|?>>
    <associate|auto-31|<tuple|4.4.1|?>>
    <associate|auto-4|<tuple|1.3|4>>
    <associate|auto-5|<tuple|2|6>>
    <associate|auto-6|<tuple|2.1|6>>
    <associate|auto-7|<tuple|2.1.1|6>>
    <associate|auto-8|<tuple|2.1.2|7>>
    <associate|auto-9|<tuple|2.1.3|8>>
  </collection>
</references>

<\auxiliary>
  <\collection>
    <\associate|toc>
      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|1<space|2spc>Simulated
      Annealing> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-1><vspace|0.5fn>

      <with|par-left|<quote|1tab>|1.1<space|2spc>Convergenza
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-2>>

      <with|par-left|<quote|1tab>|1.2<space|2spc>Guida pratica alla Ricotta
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-3>>

      <with|par-left|<quote|1tab>|1.3<space|2spc>Temperamento parallelo
      \ <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-4>>

      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|2<space|2spc>Ant
      System> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-5><vspace|0.5fn>

      <with|par-left|<quote|1tab>|2.1<space|2spc>La pista dei ferormoni: una
      ottimizazione naturale <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-6>>

      <with|par-left|<quote|2tab>|2.1.1<space|2spc>Esperienza di Goss (1989)
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-7>>

      <with|par-left|<quote|2tab>|2.1.2<space|2spc><\with|font-series|<quote|bold>>
        Esperienza di Goss e Dereborg (1990)
      </with> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-8>>

      <with|par-left|<quote|2tab>|2.1.3<space|2spc>Modello matematico
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-9>>

      <with|par-left|<quote|1tab>|2.2<space|2spc>Algoritmo informatico di
      ottimazione <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-10>>

      <with|par-left|<quote|2tab>|2.2.1<space|2spc>Algoritmo
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-11>>

      <with|par-left|<quote|1tab>|2.3<space|2spc>Ant Colony System
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-12>>

      <with|par-left|<quote|2tab>|2.3.1<space|2spc>Calcolo di
      <with|mode|<quote|math>|\<tau\><rsub|ij><around*|(|t+1|)>> nel
      <with|font-series|<quote|bold>|ACS>
      \ <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-13>>

      <with|par-left|<quote|2tab>|2.3.2<space|2spc>Performance dell'ACS
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-14>>

      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|3<space|2spc>Particle
      Swarm Optimization > <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-15><vspace|0.5fn>

      <with|par-left|<quote|1tab>|3.1<space|2spc>Introduzione
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-16>>

      <with|par-left|<quote|1tab>|3.2<space|2spc>Algoritmo
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-17>>

      <with|par-left|<quote|1tab>|3.3<space|2spc>Osservazioni
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-18>>

      <with|par-left|<quote|1tab>|3.4<space|2spc>Firefly algorithm
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-19>>

      <with|par-left|<quote|2tab>|3.4.1<space|2spc>Algoritmo
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-20>>

      <with|par-left|<quote|1tab>|3.5<space|2spc>Pseudo Code
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-21>>

      <vspace*|1fn><with|font-series|<quote|bold>|math-font-series|<quote|bold>|4<space|2spc>Algoritimi
      evolutivi> <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-22><vspace|0.5fn>

      <with|par-left|<quote|1tab>|4.1<space|2spc>Introduzione
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-23>>

      <with|par-left|<quote|1tab>|4.2<space|2spc>Algoritmi genetici
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-24>>

      <with|par-left|<quote|1tab>|4.3<space|2spc>Pseudo codice
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-25>>

      <with|par-left|<quote|2tab>|4.3.1<space|2spc>Selezione
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-26>>

      <with|par-left|<quote|2tab>|4.3.2<space|2spc>Crossover
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-27>>

      <with|par-left|<quote|2tab>|4.3.3<space|2spc>Mutazione
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-28>>

      <with|par-left|<quote|2tab>|4.3.4<space|2spc>Diversificazione VS
      Intensificazione <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-29>>

      <with|par-left|<quote|1tab>|4.4<space|2spc>Esempio
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-30>>

      <with|par-left|<quote|2tab>|4.4.1<space|2spc>Esempio piu' realistico
      <datoms|<macro|x|<repeat|<arg|x>|<with|font-series|medium|<with|font-size|1|<space|0.2fn>.<space|0.2fn>>>>>|<htab|5mm>>
      <no-break><pageref|auto-31>>
    </associate>
  </collection>
</auxiliary>