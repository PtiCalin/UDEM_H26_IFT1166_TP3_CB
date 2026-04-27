# TP3 Assets Register

Use this file to track all assignment input/output files and validation evidence.

## Required Assignment Assets

| ID | Asset | Type | Expected Path | Mandatory | Notes |
|----|-------|------|---------------|-----------|-------|
| A-001 | Inventory dataset (provided) | Input | files/assets/inventaire_tp3.txt | Yes | Main dataset for TP3 (200 items in provided sample) |
| A-002 | Inventory dataset (runtime copy) | Input | files/remise/programmes/scr/data/inventaire.txt | Yes | Input used by local runs/tests |
| A-003 | Route sheet | Document | files/assets/IFT1166H26Tp3_feuille_de_route.odt | Yes | Mandatory file for submission zip |
| A-004 | Assignment instructions | Document | files/instructions/INSTRUCTIONS.md | Yes | Source of required options and constraints |
| A-005 | Assignment PDF | Document | files/instructions/IFT1166H26TP3.pdf | Yes | Official statement reference |

## Validation Evidence (Recommended)

Store console captures/screenshots proving each required command mode executed.

| ID | Evidence Name | Task Coverage | Path | Date | Verified By |
|----|---------------|---------------|------|------|-------------|
| E-001 | Import + display run | -i and default display | files/assets/evidence/tp3-import-display.txt | [YYYY-MM-DD] | [Name] |
| E-002 | Add/update/search/remove run | -ajout, -maj, -cherche, -ret | files/assets/evidence/tp3-crud.txt | [YYYY-MM-DD] | [Name] |
| E-003 | Sorting run | -tri code/nom/prix/qte with asc/desc | files/assets/evidence/tp3-tri.txt | [YYYY-MM-DD] | [Name] |
| E-004 | Statistics run | -stat with global and by-type sections | files/assets/evidence/tp3-stat.txt | [YYYY-MM-DD] | [Name] |
| E-005 | Export run | -o output generation | files/assets/evidence/tp3-export.txt | [YYYY-MM-DD] | [Name] |
| E-006 | Build log | C++23 build + warnings check | files/assets/evidence/tp3-build.txt | [YYYY-MM-DD] | [Name] |
| E-007 | Full command video | Complete options demo | files/assets/evidence/tp3-demo.mp4 | [YYYY-MM-DD] | [Name] |

## Naming Convention

1. Use lowercase with hyphens.
2. Include scope prefix (tp3).
3. Include version suffix only when necessary.

Examples:
- `tp3-import-display.txt`
- `tp3-tri.txt`
- `tp3-submission-checklist.pdf`

## Folder Recommendation

```text
files/assets/
├── inventaire_tp3.txt
├── IFT1166H26Tp3_feuille_de_route.odt
└── evidence/
	├── tp3-import-display.txt
	├── tp3-crud.txt
	├── tp3-tri.txt
	├── tp3-stat.txt
	├── tp3-export.txt
	├── tp3-build.txt
	└── tp3-demo.mp4
```

## Completion Checklist

- Inventory input file is present and readable.
- Report and route sheet are present.
- Build log shows C++23 compile success and warnings reviewed.
- Evidence exists for all required command options.
- Video demo covers the complete option set.
- File names are clean and consistent.
