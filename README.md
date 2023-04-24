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
        - [ ] Ambient Global 
        - [ ] Puntual
        - [ ] Direccional 
        - [ ] Spotlight 
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
crear un objecte? )**

- Pas 1.2: Pas de la llum de tipus puntual a la GPU. Creació de nous tipus de llums
    * **Ara es crea una llum puntual al initializeGL() de la classe GLWidget, quan l’hauries de passar a la GPU? A l’inici de
tot? Cada vegada que es visualitza l’escena?**
    * **Què contindrà el "struct" de la GPU? Com l’estructurareu?**
**Extensions addicionals**


**Memòria**
