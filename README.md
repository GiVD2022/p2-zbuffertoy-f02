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
       - [X] Pas a la GPU
            - Pau B. i Pau H.
       - [X] Lectura de fitxers .json
            - Pau B. i Pau H.
    - Shading
        - [X] Color
            - Pau B.
        - [X] Normal
            - Esther Ruano
        - [X] Depth
            - Núria Torquet
        - [X] Phong-Gouraud 
            - Pau B.
        - [X] Phong-Phong
            - Núria Torquet
        - [X] BlinnPhong-Gouraud 
            - Pau B.
        - [X] BlinnPhong-Phong
            - Núria Torquet
        - [ ] Cel-shading
    - Textures
        - [X] Textura com material en un objecte 
            - Esther Ruano
        - [ ] Textura al pla base 
    - Adaptació a la lectura de fitxers de dades
        - [ ] Escenes virtuals 
        - [ ] SetUp
        - [ ] Escenes de dades 

- Fase 2 
    - [X] Visió nocturna
        - Núria Torquet
    - [X] La Tempesta de Fornite
        - Esther Ruano
        
- Opcionals
    - [ ] Èmfasi de siluetes 
    - [X] Mapping indirecte de textures
         - Esther Ruano
    - [ ] Animacions amb dades temporals
    - [ ] Normal mapping 
    - [ ] Entorn amb textures
    - [ ] Reflexions
    - [ ] Transparències via objectes: 
    - [ ] Transparències via environmental mapping 


**Decisions a destacar**

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
   
        L'struct de la GPU s'ha definit de la següent manera:
        ```glsl
        struct Light {
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
   
- Pas 2.1: Modificació de la classe Material
    * **Utilitzarem també “structs” per a estructurar la informació tant a la CPU com a la GPU, tal i com fèiem a les llums.
Des d’on es cridarà aquest mètode? (fent referència al toGPU)**
        En aquest cas, l'struct del Material és:
        ```glsl
        struct Material
        {
            vec3 Ka;
            vec3 Kd;
            vec3 Ks;
            vec3 Kt;
            float shininess;
            float opacity;
        };
        ```
        El ```toGPU()``` de ```GPUMaterial``` s'haurà de cridar a la funció draw() dels objectes. Això es deu a que volem que per cada objecte es tingui la informació del seu material. Si ho fessim tots seguits i desprès els dibuixéssim, aleshores només es tindria a la memòria de la GPU el material de l'últim objecte. Posant-ho al draw aconseguim que abans de pintar cada objecte, es passa el seu material.
    * **Si vols utilitzar diferents shaders en temps d'execució raona on s'inicialitzaran els shaders i com controlar quin
shader s'usa? Cal tornar a passar l'escena a la GPU quan es canvia de shader?**
        Hem canviat la variable program de GLWidget per un vector de GLShaders, i hem afegit un atribut program a GLShader. També hem afegit un atribut ```currentShader``` que és un enter i guarda la posició del shader actual dins del vector. Podríem guardar un shader o un program directament, però així es gasta menys memmòria. Llavors inicialitzem tots els shaders al principi, al mètode ```initShaders()``` i així ja els tenim compilats i llestos per ser usats (serà més ràpid canviar de shaders). Llavors per canviar de shader, cridem la funció ```updateShader()``` desprès de canviar el ```currentShader```. Aqudst mètode activa el shader seleccionat i envia els dades a GPU. (Tornar a enviar l'escena és necessari, ja que al carregar el nou shader sha perdut la informació que ja hi havia.
        
- Pas 3.1: Creació de diferents tipus de shadings
    * **Gouraud: Fixa't que quan es llegeix un objecte, cada vèrtex ja té la seva normal. Com serà aquest valor de la normal? Uniform o no uniform?**
        La normal no pot ser de tipus uniform, ja que cada punt de la superfície en té una de diferent. Per això la definim com 
        ```glsl
            layout (location = 1) in vec4 vNormal;
        ```
    * **En la classe Camera utilitza el mètode toGPU per a passar l'observador als shaders per a que es passi la posició de l'observador cada vegada que s'actualitza la posició de la càmera amb el ratolí. Com serà aquesta variable al shader? Uniform? O IN?**
        ```glsl
        uniform vec4 obs;
        ```
        S'ha definit de tipus uniform, perquè no varia el seu valor d'un shader a un altre en la mateixa crida de rendering. El seu valor és uniforme en totes les invocacions.
    * **Si vols utilitzar diferents shaders en temps d'execució raona on s'inicialitzaran els shaders i com controlar quin shader s'usa? Cal tornar a passar l'escena a la GPU quan es canvia de shader? I també la càmera?**
    * **Quina diferència hi ha entre el Phong-shading i el Gouraud-shading? On l'has de codificar? Necessites uns nous vertex-shader i fragment-shader? Raona on es calcula la il·luminació i modifica convenientment els fitxers de la pràctica.**
        La diferència principal és que els shaders de Gouraud es calculen al vertex shader i llavors els fragments prenen valors interpolats. En canvi, en el Phong Shader, es calcula el valor per cada fragment, i per això s'ha de fer en el fragment shader. En tots el casos, per fer noves estratègies de shader es necessiten nous fitxers vertex-shader i fragment-shader.
    * **Cel-shading: On s'implementarà el càlcul del color per a tenir més trencament entre las games de colors? Necessites uns nous vertex-shader i fragment-shader? Raona on es calcula la il·luminació** 

- Pas 4.1: Inclusió de textures
    * Per implementar les textures hem creat un nou material, MATERIALTEXTURA, inspirant-nos en la primera pràctica. Té les mateixes característiques que un lambertian però a més incorpora una Textura. Hem creat de manera simètrica GPUMaterialTextura. 
    
      Per facilitar les comprovacions, a més, desem en un atribut ```type``` (de la classe GPUMesh) el tipus de material que és segons llegim al mètode ```read()```. És en funció d'aquest atribut que s'envia o no el vector de textures, i s'assigna un valor de cert o fals a la variable uniforme ```hasTexture```; des del mètode ```toGPU()``` de GPUMesh. 
      
      Els shaders que permeten veure les textures són Gouraud (Phong i Blinn Phong), Phong i BlinnPhong
        
- FASE 2:
    - Pas 1.1: Visió Nocturna o Target amb cercle verd
        * **Detalla on es faria el càlcul? Amb quines coordenades? Amb coordenades de món? De càmera? O de viewport?**

            El càlcul es fa a nivell de viewport, passant com a variable uniform la mida horitzontal i vertical del viewport en coordenades de pixels i el seu radi. Aleshores es calcula la distància entre el píxel actual en el fragment shader i el del centre de l'escena, i es compara amb el radi.
        * **Com aconseguiries que els píxels de fons inclosos en el cercle de visió nocturna es pintessin també de color verd?** 
            S'hauria d'incloure un pla en el punt més allunyat de la capsa contenidora per a que el framgnet shader detectés els píxels de fons i poder-los així pintar de verd.
     - Pas 1.2: La tempesta de Fornite
        * **Considera quants parells de vèrtex-fragment shaders has d’usar, a on cal considerar el test amb l’esfera, etc.**

            Farem servir tres parells de vèrtex-fragment shaders: BlinnPhong pels objectes completament exteriors, una modificació de Gouraud (que posa el valor de blau de la component difusa a 1) pels objectes interiors i un de mixt que en funció de la distància de cada vèrtex al centre de l'esfera calcula Gouraud blavós o Blinn Phong. 
            
            El radi de l'esfera es decideix al mètode calculaRadi() de la classe GPUScene, i hem decidit que sigui el mínim entre 1/3 del diàmetre de l'escena i 90. 
            
            És GLWidget qui activa cada un dels shaders i envia els elements de dins, fora i interesectas amb l'esfera fent servir tres mètodes toGPU creats a GPUScene especialment per això: ```toGPUIn(), toGPUOut() i toGPUIntersect()```
        
- OPCIONALS:
    - Textures indirectes: hem fet el càlcul del mapejat a CPU, no GPU, en funció de la variable indirectMapping que llegim dels arxius JSON i de la qual en suposem un valor fals per defecte.

**Screenshots de cada part**    
- Pas 3.1: Creació de diferents tipus de shadings 

    S'ha definit una GPULight de tipus PointLight per a fer les proves de visualització. Els paràmetres per a inicialitzar-la són els següents:
    ```c++
    // Default point light
    vec3 position1 = vec3(-25,25,25);
    vec3 Ia1 = vec3(0.3,0.3,0.3);
    vec3 Id1 = vec3(1,1,1);
    vec3 Is1 = vec3(0.5,0.5,0.5);
    float a1 = 0.0;
    float b1 = 0.0;
    float c1 = 1.0;
    ```
    * Color shading 
        <img width="855" alt="Captura de pantalla 2023-05-15 a las 18 52 31" src="https://github.com/GiVD2022/p2-zbuffertoy-f02/assets/44063174/95770cd0-7453-4d91-8cdd-2c012e467e6e">


    * Depth shading 
        <img width="851" alt="Captura de pantalla 2023-05-15 a las 18 52 54" src="https://github.com/GiVD2022/p2-zbuffertoy-f02/assets/44063174/400e6c90-0e87-43be-94da-d2bd1a8849b2">


    * Normal shading 
        <img width="855" alt="Captura de pantalla 2023-05-15 a las 18 52 38" src="https://github.com/GiVD2022/p2-zbuffertoy-f02/assets/44063174/18cc537f-2b1e-4c1b-82ec-695a3e67873f">


    * Gouraud-phong shading 
        <img width="857" alt="Captura de pantalla 2023-05-15 a las 18 51 13" src="https://github.com/GiVD2022/p2-zbuffertoy-f02/assets/44063174/65613ae7-4d94-4a18-9e6a-adc9fc837a6c">


    * Phong-phong shading 
        <img width="861" alt="Captura de pantalla 2023-05-15 a las 18 51 30" src="https://github.com/GiVD2022/p2-zbuffertoy-f02/assets/44063174/d0d52c75-2232-4e62-8920-933ae9a2c3ac">

       
    * Gouraud-blinn-phong shading 
        <img width="857" alt="Captura de pantalla 2023-05-15 a las 18 51 39" src="https://github.com/GiVD2022/p2-zbuffertoy-f02/assets/44063174/e222c39d-9a09-4b64-a626-ec7c417e1219">


    * Phong-blinn-phong shading 
        <img width="854" alt="Captura de pantalla 2023-05-15 a las 18 51 49" src="https://github.com/GiVD2022/p2-zbuffertoy-f02/assets/44063174/ef3e5f41-2509-41df-8170-2bbbf428aa05">

        

**Extensions addicionals**


**Memòria**
