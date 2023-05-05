# ZBufferToy
Codi de la Pràctica 2 de GiVD: ZBufferToy 2022-23

::

    Aquest és el model base del README.rst que haureu d'omplir com a documentació de la pràctica. De cara a la presentació d'aquests document, si us plau, esborreu les notes i aquest text. 
    
**Abstract**

Petit resum de fins on heu arribat a fer

**Features**

A continuació s'indica quines parts s'han fet i qui les ha implementat
- Fase 1
    - Lights
        - [X] Ambient Global 
            - Núria Torquet
        - [X] Puntual
            - Núria Torquet
        - [X] Direccional 
            - Esther Ruano
        - [X] Spotlight
            - Esther Ruano
    - Materials: 
       - [ ] Pas a la GPU
       - [ ] Lectura de fitxers .json
    - Shading
        - [ ] Color
        - [ ] Normal
        - [ ] Depth 
        - [ ] Phong-Gouraud 
        - [ ] Phong-Phong
        - [ ] BlinnPhong-Gouraud 
        - [ ] BlinnPhong-Phong
        - [ ] Cel-shading
    - Textures
        - [ ] Textura com material en un objecte 
        - [ ] Textura al pla base 
    - Adaptació a la lectura de fitxers de dades
        - [ ] Escenes virtuals 
        - [ ] SetUp
        - [ ] Escenes de dades 

- Fase 2 
    - [ ] Visió nocturna 
    - [ ] La Tempesta de Fornite
    - [ ] Èmfasi de siluetes 
    - [ ] Mapping indirecte de textures
    - [ ] Animacions amb dades temporals
    - [ ] Normal mapping 
    - [ ] Entorn amb textures
    - [ ] Reflexions
    - [ ] Transparències via objectes: 
    - [ ] Transparències via environmental mapping

**Preguntes**
- Pas 1.1: Pas de la llum ambient global a la GPU
    * **Decideix el moment en el que cal passar la llum ambient global a la GPU (al initializeGL? Al updateGL? En
crear un objecte?** 

        S'ha passat la llum ambient global a la GPU durant la fase d'inicialització (initializeGL) de l'aplicació, ja que la llum ambient global no canvia durant l'execució de l'aplicació.
        Així es garanteix que la GPU tingui les dades necessàries per renderitzar l'escena amb precisió des del principi. A més, si actualitzes la llum ambient global durant l'execució de l'aplicació, es pot cridar el mètode setAmbientGlobalToGPU de nou per actualitzar els valors a la GPU.

- Pas 1.2: Pas de la llum de tipus puntual a la GPU. Creació de nous tipus de llums
    * **Ara es crea una llum puntual al initializeGL() de la classe GLWidget, quan l’hauries de passar a la GPU? A l’inici de
tot? Cada vegada que es visualitza l’escena?**
    En aquest cas la llum puntual s'hauria de passar a la GPU cada vegada que es visualitza l'escena. Això és degut a que la llum puntual pot ser afectada per la posició de la càmera i dels objectes en l'escena, i per tant, la seva representació a la GPU ha de ser actualitzada en cada iteració del bucle de renderitzat.
    * **Què contindrà el "struct" de la GPU? Com l’estructurareu?**
**Extensions addicionals**
    L'struct de la GPU s'ha definit de la següent manera:
    ```
    struct Light
{
    vec3 Ia;
    vec3 Id;
    vec3 Is;

    // Directional lights
    vec3 direction;
    float intensity;

    // spot lights
    vec3 spotDirection;
    float spotCosineCutoff;
    float spotExponent;

    // point lights
    vec3 position;
    vec3 coeficients;
};
```
    S'utilitza un "struct" per a cada llum, on es guarden les seves propietats, com ara la posició, la direcció, l'atenuació... Aquestes estructures s'agrupen en un vector, que es passarà a la GPU per a ser utilitzat en la shader de il·luminació.

**Memòria**
