# UDEM H26 IFT1166 TP3 - Workspace Guide

This repository contains the TP3 deliverable for IFT1166 (Hiver 2026): a C++23 console program for inventory management, converting the TP2 procedural solution to a full OOP architecture.

## Assignment Snapshot

- Course: IFT1166 - Programmation orientee objet en C++
- Course reference: `files/instructions/IFT1166H26TP3.pdf`
- Deliverable: Single C++23 console program (gestion d'inventaire POO)
- Due date: 2026-04-26

## Workspace Goals

1. Keep assignment instructions explicit and easy to execute.
2. Keep implementation files and evidence assets organized.
3. Reduce mistakes on required APIs and output expectations.
4. Make submission packaging straightforward.

## Repository Layout

```text
.
├── README.md
├── LICENSE
├── AUTHORS.md
├── ATTRIBUTIONS.md
├── files/
│   ├── assets/
│   │   ├── ASSETS.md
│   │   └── inventaire_tp3.txt
│   ├── instructions/
│   │   ├── INSTRUCTIONS.md
│   │   └── IFT1166H26TP3.pdf
│   ├── remise/
│   │   ├── programmes/
│   │   │   └── scr/
│   │   │       ├── main.cpp
│   │   │       ├── articles/
│   │   │       │   ├── article.h
│   │   │       │   └── article.cpp
│   │   │       ├── inventaire/
│   │   │       │   ├── inventaire.h
│   │   │       │   └── inventaire.cpp
│   │   │       └── data/
│   │   │           └── inventaire.txt
│   │   └── rapport/
│   └── resources/
│       └── RESOURCES.md
```

## OOP Class Hierarchy

```
Article  (abstract base)
├── Consommable   extra = date d'expiration (AAAA-MM-JJ)
├── Equipement    extra = garantie en mois (entier > 0)
└── Medicament    extra = dosage (texte, ex. "500mg")
```

Storage: `Article**` array in `Inventaire`; polymorphic via virtual methods and `clone()`.

## Required Command-Line Modes

| Option | Description |
|--------|-------------|
| `-i <fichier>` | Importer un inventaire CSV |
| `-o <fichier>` | Exporter l'inventaire |
| `-ajout <code> <nom> <prix> <qte> <type> <extra>` | Ajouter un article |
| `-ret <code>` | Retirer un article |
| `-maj <code> <prix> <qte>` | Mettre a jour prix/quantite |
| `-cherche <code>` | Rechercher un article |
| `-tri <champ> [asc\|desc]` | Trier (code/nom/prix/qte) |
| `-stat` | Statistiques globales et par type |
| `-aide` | Afficher l'aide |

## CSV Format

```
code;nom;prix;quantite;type;extra
```

First line is always the header. Separator is `;`.

## Constraints Checklist

Before final submission, verify:
1. Compiles with C++23 (`std::print`/`std::println` for all output).
2. No `printf`, no macros, no STL containers for data structures, no exceptions.
3. No accented characters in console output strings.
4. Sorting is hand-written (selection/insertion/bubble).
5. OOP hierarchy and polymorphism are present and coherent.
6. `-stat` output includes global and per-type sections.
7. Submission zip contains: sources, report, video, feuille de route.

## Build

Compile only `main.cpp` — it includes the `.cpp` implementation files directly:

```bash
g++ -std=c++23 -Wall -o gestion-inventaire.exe main.cpp
# or MSVC:
cl /std:c++latest /EHsc main.cpp /Fe:gestion-inventaire.exe
```

## Submission Contents (`tp3H26.zip`)

1. Source files (`.h` / `.cpp`)
2. Execution video demonstrating all required options
3. Report describing OOP design and test cases
4. Feuille de route

## Documentation Map

- `README.md`: execution and submission map
- `.claude/CLAUDE.md`: assistant behavior contract for this TP
- `files/assets/ASSETS.md`: data and output asset registry
- `files/resources/RESOURCES.md`: learning and reference sources
- `AUTHORS.md`: author and contribution ownership
- `ATTRIBUTIONS.md`: external references and AI disclosure

