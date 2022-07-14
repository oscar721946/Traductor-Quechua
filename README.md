### Traductor Quechua - Español

-Estos son los datos lingüísticos de Traductor Automático Quechua - Español basado en traducción en ambas direcciones

# Requerimientos

Previamente se requiere los siguientes programas:
- Python 
- Tesseract OCR

Posteriormente las siguientes extensiones:
- pyttsx3 
- C++
- xml
- label
- tkinter 
- html
- javascript

#### Instalacion

Una vez clonado el proyecto, se debe instaurar el acoplamiento de diccionarios por autogen.sh

Posteriormente ejecutar el programa de acuerdo a las premisas del codigo fuente:
   if __name__=="__main__":

    traductor()

```

####HTML code

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Primera section</title>
</head>

<!-- ===== Primera Section ===== -->
<section id="primera">
    <div id="primera-container">
        <div class="container">
            <h2>Uso de Condicionales Simples y Anidados</h2>
            <p>El programa a continuación es un dicionario Español -  Quechua que busca ser una
                herramienta útil y sencilla de utilizar</p>
        </div>
        <div class="container">
            <!-- Creación de un cajo de opciones y definir variables -->
            <label for>Seleciona el color a traducir</label><br><br>

            <select name="color" onchange="colores(this.value);"><br><br>
                <option value=""></option>
                <option value="1">Azul</option>
                <option value="2">Celeste</option>
                <option value="3">Amarillo</option>
                <option value="4">Verde</option>
                <option value="5">Naranja</option>
                <option value="6">Morado</option>
                <option value="7">Café</option>
                <option value="8">Rojo</option>
                <option value="9">Plomo</option>
                <option value="10">Rosado</option>
                <option value="11">Negro</option>
                <option value="12">Azul marino</option>
                <option value="13">Blanco</option>
            </select><br><br>


            <label>Traducción</label><br><br>
            <span id="traduccion"></span>

            <script src="uno.js"></script>
        </div>
        <div class="container">

        </div>
    </div>
</section>

<body>

</body>
</html>
```


####Funciones de Traduccion

<sdef n="n"        c="Nombre"/>
    <sdef n="np"       c="Nombre propio"/>
    <sdef n="adj"      c="Adjetivo"/>
    <sdef n="ant"      c="Antróponimo"/>
    <sdef n="cog"      c="Apellido"/>
    <sdef n="top"      c="Topónimo"/>
    <sdef n="al"       c="NP otro"/>
    <sdef n="adv"      c="Adverbio / (Relativo) adverbial"/>
    <sdef n="cnjadv"   c="Conjunción adverbial"/>
    <sdef n="cnjcoo"   c="Conjunción coordinante"/>
    <sdef n="cnjsub"   c="Conjunción subordinante"/>
    <sdef n="det"      c="Determinante"/>
    <sdef n="detnt"    c="Determinante neutro"/>
    <sdef n="num"      c="Numeral"/>
    <sdef n="numM"     c="Numeral (Múltiplos: 10, 100 ...)"/>
    <sdef n="ord"      c="Numeral ordinal"/>
    <sdef n="pr"       c="Preposición"/>
    <sdef n="post"     c="Postposición"/>
    <sdef n="preadv"   c="Preadverbio"/>
    <sdef n="preadj"   c="Preadjetivo"/>
    <sdef n="predet"   c="Preterminante"/>
    <sdef n="prn"      c="Pronombre"/>
    <sdef n="rel"      c="Relativo"/>
    <sdef n="ij"       c="Interjeción"/>
    <sdef n="vblex"    c="Verbo"/>
    <sdef n="vbmod"    c="Verbo modal"/>
    <sdef n="vbaux"    c="Verbo auxiliar"/>
    <sdef n="vbser"    c="Verbo 'ser'"/>
    <sdef n="vbhaver"  c="Verbo 'haver'"/>
    <sdef n="vbex"     c="Verbo existencial"/>
    <sdef n="vbcop"    c="Verbo - cópula"/>
    
    <sdef n="tv"       c="Verbo transitivo"/>
    <sdef n="iv"       c="Verbo intransitivo"/>
    <sdef n="vm"       c="Verbo de movimiento"/>
    <sdef n="vcm"      c="Verbo de comunicación"/>
    <sdef n="vimp"     c="Verbo impersonal"/>
    <sdef n="pron"     c="Verbo pronominal (reflexivo)"/>
    
    <sdef n="def"      c="Definido"/>
    <sdef n="ind"      c="Indefinido"/>
    <sdef n="itg"      c="Interrogativo"/>
    <sdef n="neg"      c="Negativo"/>
    <sdef n="qnt"      c="Cuantitativo"/>
    <sdef n="dem"      c="Demostrativo"/>
    <sdef n="pos"      c="Posesivo"/>
    <sdef n="sup"      c="Superlativo"/>
    <sdef n="aa"       c="Animado"/>
    <sdef n="nn"       c="Inanimado"/>
    <sdef n="an"       c="Animado/inanimado"/>
    <sdef n="subst"    c="Substantival (adverbio)"/>
    <sdef n="temp"     c="Temporal (adverbio)"/>
    
    <sdef n="pers"     c="Personal"/>
    <sdef n="tn"       c="Tónico"/>
    <sdef n="enc"      c="Enclítico"/>
    <sdef n="pro"      c="Proclítico"/>
    <sdef n="ref"      c="Reflexivo"/>

    <sdef n="f"        c="Feminino"/>
    <sdef n="m"        c="Masculino"/>
    <sdef n="nt"       c="Neutro"/>
    <sdef n="mf"       c="Masculino/femenino"/>
    <sdef n="GD"       c="Género por determinar"/>
    
    <sdef n="sg"       c="Singular"/>
    <sdef n="pl"       c="Plural"/>
    <sdef n="sp"       c="Singular/plural"/>
    <sdef n="ND"       c="Número por determinar"/>
    
    <!-- casos -->
    <sdef n="nom"       c="Nominativo (nada)" />
    <sdef n="gen"       c="Genitivo (-q/pa)" />
    <sdef n="ben"       c="Benefactivo (-paq)" />
    <sdef n="acc"       c="Acusativo (-ta)" />
    <sdef n="dat"       c="Dativo (ilativo) (-man)" />
    <sdef n="ter"       c="Terminativo (limitativo) (-kama)" />
    <sdef n="per"       c="Perlativo (-nta)" />
    <sdef n="abl"       c="Ablativo (-manta)" />
    <sdef n="loc"       c="Locativo (-pi)" />   <!-- loc "Location" en ES - cambiado para top) -->
    <sdef n="ins"       c="Instrumental (comitativo) (-wan)" />
    <sdef n="csal"      c="Causal (causativo) (-rayku)" />
    <sdef n="dis"       c="Distributivo (-nka)" />
    <sdef n="prox"      c="Proximativo (-niq)"/>
    <sdef n="posic"     c="Posicional (-npa)" />
    <sdef n="sim"       c="Similativo (-niraq)"/>
    
    <!-- marcas de persona -->
    <sdef n="p1"       c="Primera persona"/>
    <sdef n="p2"       c="Segunda persona"/>
    <sdef n="p3"       c="Tercera persona"/>
    <sdef n="p1in"     c="Primera persona plural inclusiva"/>
    <sdef n="p1ex"     c="Primera persona plural exclusiva"/>
    
    <sdef n="po1sg"    c="Primera persona singular objeto"/>
    <sdef n="po2sg"    c="Segunda persona singular objeto"/>
    <sdef n="po3sg"    c="Tercera persona singular objeto"/>
    <sdef n="po1in"    c="Primera persona plural inclusiva objeto"/>
    <sdef n="po1ex"    c="Primera persona plural exclusiva objeto"/>
    <sdef n="po1sp"    c="Primera persona singular o plural exclusiva objeto"/>
    <sdef n="po2pl"    c="Segunda persona plural objeto"/>
    <sdef n="po2sp"    c="Segunda persona singular o plural objeto"/>
    <sdef n="po3pl"    c="Tercera persona plural objeto"/>
    <sdef n="po3sp"    c="Tercera persona singular o plural objeto"/>
    
    <sdef n="px1sg"    c="Primera persona singular posesiva"/>
    <sdef n="px2sg"    c="Segunda persona singular posesiva"/>
    <sdef n="px3sg"    c="Tercera persona singular posesiva"/>
    <sdef n="px1in"    c="Primera persona plural inclusiva posesiva"/>
    <sdef n="px1ex"    c="Primera persona plural exclusiva posesiva"/>
    <sdef n="px2pl"    c="Segunda persona plural posesiva"/>
    <sdef n="px3pl"    c="Tercera persona plural posesiva"/>
    <sdef n="pxrel"    c="Relativo (-n)"/>
    
    <!-- subordinaciones -->
    <sdef n="pp"       c="Participio pasado     -sqa (spa: /-do)    "/>
    <sdef n="pf"       c="Participio futuro     -na                 "/>
    <sdef n="ag"       c="Agentivo      -q              "/>
    <sdef n="inf"      c="Infinitivo    -y              "/>
    <sdef n="ger"      c="Gerundio      -spa (sujetos idénticos)    "/>
    <sdef n="ger2"     c="Gerundio      -qti (sujetos diferentes)   "/>
    <sdef n="cons"     c="Consecutivo   -stin   "/>
    
    <!-- tiempo/modo -->
    <sdef n="pri"      c="Presente de indicativo"/>
    <sdef n="prs"      c="Presente de subjuntivo"/>
    <sdef n="pii"      c="Pretérito imperfecto de indicativo"/>
    <sdef n="pis"      c="Pretérito imperfecto de subjuntivo"/>
    <sdef n="ifi"      c="Indefinido (pretérito perfecto)"/>
    <sdef n="fti"      c="Futuro de indicativo"/>
    <sdef n="fts"      c="Futuro de subjuntivo"/>
    <sdef n="cni"      c="Condicional"/>
    <sdef n="cni_pas"  c="Condicional pasado = condicional + AUX kar(q)an"/>
    <sdef n="imp"      c="Imperativo"/>
    <sdef n="evid"     c="Pasado evidencial -sqa"/>
    <sdef n="hab"      c="Habitual -q + AUX ka-"/>
    
    <!-- derivativos verbales -->
    <sdef n="cont"      c="Continuativo (progresivo) -sha   "/>
    <sdef n="caus"      c="Causativo        -chi    "/>
    <sdef n="refl"      c="Reflexivo        -ku     "/>
    <sdef n="rec"       c="Recíproco        -na + -ku/chi/pu    "/>
    <sdef n="bn"        c="Benefactivo      -pu     "/>
    <sdef n="inc"       c="Inceptivo        -ri     "/>
    <sdef n="rpnt"      c="Repentino        -rqu    "/>
    <sdef n="int"       c="Intensivo        -yku    "/>
    <sdef n="ctl"       c="Cis/translocativo    -mu         "/>
    <sdef n="coop"      c="Asistivo (cooperatio)    -ysi    "/>
    <sdef n="osc"       c="Oscilativo (iterativo)   -ykacha "/>
    <sdef n="frec"      c="Frecuentativo    -paya   "/>
    <sdef n="rpt"       c="Repetivo         -pa     "/>
    <sdef n="dur"       c="Durativo         -raya   "/>
    <sdef n="simul"     c="Simulativo       -tiya   "/>
    <sdef n="compl"     c="Completivo       -rpari  "/>
    <sdef n="desid"     c="Desiderativo     -naya   "/>
    <sdef n="trns"      c="Transformacional -ya     "/>
    <sdef n="fct"       c="Factitivo        -cha    "/>
    
    <!-- derivativos nominales -->
    <sdef n="poss"      c="Posesivo     -yuq    "/>
    <sdef n="pond"      c="Ponderativo  -sapa   "/>
    <sdef n="incl"      c="Inclusivo    -ntin   "/>
    
    <!-- clíticos -->
    <sdef n="af"        c="afirmativo   -mi     "/>
    <sdef n="rep"       c="reportativo  -si     "/>
    <sdef n="cnj"       c="conjetural   -chá    "/>
    <sdef n="enf"       c="enfático     -yá     "/>
    <sdef n="dub"       c="dubitativo   -chus   "/>
    <sdef n="rnd"       c="reanudador   -ri     "/>
    <sdef n="topi"      c="tópico       -qa     "/>
    <sdef n="qst"       c="interrogativo/negativo -chu"/>
    <sdef n="contr"     c="contrastivo  -taq    "/>
    <sdef n="adit"      c="aditivo      -pas    "/>
    <sdef n="cnti"      c="continuativo -raq    "/>
    <sdef n="dcnt"      c="discontinuativo -ña  "/>
    <sdef n="dfnt"      c="definitivo   -puni   "/>
    <sdef n="lim"       c="limitativo   -lla    "/>
    <sdef n="dim"       c="diminutivo   -cha    "/>


###Flujo

```flow
st=>start: Login
op=>operation: Translate operation
cond=>condition: Processing
e=>end: Process Correct

st->error->cond
cond(yes)->e
cond(no)->error
```

###Secuencia
                    
```seq
Palabra->Respuesta:Traduccion 
Variables-->Palabra:Funciones 
Conjunciones->>Respuesta: Salida de texto
```


