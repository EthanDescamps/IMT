<<<<<<< HEAD
```mermaid
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
```
=======
| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C5 | ESP32-C6 | ESP32-C61 | ESP32-H2 | ESP32-H21 | ESP32-H4 | ESP32-P4 | ESP32-S2 | ESP32-S3 | Linux |
| ----------------- | ----- | -------- | -------- | -------- | -------- | --------- | -------- | --------- | -------- | -------- | -------- | -------- | ----- |

# Hello World Example

Starts a FreeRTOS task to print "Hello World".

(See the README.md file in the upper level 'examples' directory for more information about examples.)

## How to use example

Follow detailed instructions provided specifically for this example.

Select the instructions depending on Espressif chip installed on your development board:

- [ESP32 Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/stable/get-started/index.html)
- [ESP32-S2 Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/get-started/index.html)


## Example folder contents

The project **hello_world** contains one source file in C language [hello_world_main.c](main/hello_world_main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files that provide set of directives and instructions describing the project's source files and targets (executable, library, or both).

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── pytest_hello_world.py      Python script used for automated testing
├── main
│   ├── CMakeLists.txt
│   └── hello_world_main.c
└── README.md                  This is the file you are currently reading
```

For more information on structure and contents of ESP-IDF projects, please refer to Section [Build System](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html) of the ESP-IDF Programming Guide.

## Troubleshooting

* Program upload failure

    * Hardware connection is not correct: run `idf.py -p PORT monitor`, and reboot your board to see if there are any output logs.
    * The baud rate for downloading is too high: lower your baud rate in the `menuconfig` menu, and try again.

## Technical support and feedback

Please use the following feedback channels:

* For technical queries, go to the [esp32.com](https://esp32.com/) forum
* For a feature request or bug report, create a [GitHub issue](https://github.com/espressif/esp-idf/issues)

We will get back to you as soon as possible.
>>>>>>> origin/master
