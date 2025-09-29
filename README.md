graph LR
    Projet70["Projet 70"]:::root

    Projet70 --> LivrableSyntheseProjet
    LivrableSyntheseProjet["[Livrable] Synthèse de projet"]:::liv
    LivrableSyntheseProjet --> Plannification["Plannification"]:::task
    LivrableSyntheseProjet --> CreationDiagrammes["Création de diagrammes pieuvre / bête à cornes"]:::task
    LivrableSyntheseProjet --> RedactionSynthese["Rédaction de la synthèse de projet"]:::task

    Projet70 --> Phase0
    Phase0["[Phase 0] Gestion de projet"]:::phase
    Phase0 --> ReunionClient1["Réunion Client"]:::task
    Phase0 --> ReunionClient2["Réunion Client"]:::task
    Phase0 --> LivrableRevue["[Livrable] Revue de projet"]:::liv

    Projet70 --> Phase1
    Phase1["[Phase 1] Recherche sur le projet"]:::phase
    Phase1 --> EtatArt["Etat de l'art"]:::task
    Phase1 --> TrouverBatterie["[Matériel] Trouver la batterie"]:::task
    Phase1 --> TrouverCamera["[Matériel] Trouver la caméra"]:::task
    Phase1 --> TrouverCapteur["[Matériel] Trouver le capteur inertiel"]:::task
    Phase1 --> TrouverMicrocontroleur["[Matériel] Trouver le micro-contrôleur"]:::task

    Projet70 --> Phase2
    Phase2["[Phase 2] Appréhension des composants"]:::phase
    Phase2 --> TestMicro["Test microcontrôleur"]:::task
    Phase2 --> TestCam["Test caméra"]:::task
    Phase2 --> TestCapteur["Test capteur inertiel"]:::task
    Phase2 --> TestInt["Test interface Overview"]:::task
    Phase2 --> TestComm["Test communication avec interface Overview"]:::task
    Phase2 --> Connexion["Mise en place de la connexion avec Overview"]:::task
    Phase2 --> Compression["Mise en place de la compression d'images"]:::task

    Projet70 --> Phase3
    Phase3["[Phase 3] Réalisation du capteur"]:::phase
    Phase3 --> Boite["Dimensionnement de la boite"]:::task
    Phase3 --> Codage["Création du code / câblage du système odométrique"]:::task
    Phase3 --> AssocCapteur["Association du capteur avec Overview"]:::task
    Phase3 --> Impression["Impression boite 3D"]:::task
    Phase3 --> TestsGlobalite["Tests de la globalité du système"]:::task

    %% Styles couleurs
    classDef root fill:#f9f,stroke:#333,stroke-width:3px,color:#000,font-weight:bold;
    classDef phase fill:#bbf,stroke:#333,stroke-width:2px,color:#000,font-weight:bold;
    classDef liv fill:#bfb,stroke:#333,stroke-width:2px,color:#000;
    classDef task fill:#ffa,stroke:#333,stroke-width:1px,color:#000;
