# TP3 Execution Checklist (Num1 + Num2)

This checklist is the operational runbook to finish and submit TP3 with minimal omissions.

## 0. Setup

- [ ] Place `Nations.txt` in `files/assets/`
- [ ] Place `coasters.txt` in `files/assets/`
- [ ] Create two independent C# projects/solutions:
  - [ ] `TP3_Num1`
  - [ ] `TP3_Num2`

## 1. Num1 - System.Array

- [ ] Task 1: Read file and fill nation array (count valid entries)
- [ ] Task 2: Display first 15 nations
- [ ] Task 3: Sequential search and required updates
- [ ] Task 4: Display nations where country == capital
- [ ] Task 5: Lowest density in Europe and Oceania
- [ ] Task 6: Highest population in America and Europe
- [ ] Task 7: Vowel-start countries and longest American capital
- [ ] Task 8: Sort by name with `Array.Sort`, show first 10
- [ ] Task 9: Search with `Array.BinarySearch` for required values
- [ ] Task 10: Generate `Europe.txt` and `Asie.txt`

Validation:
- [ ] `Nation` has usable `ToString()`
- [ ] Array sort/search behavior is deterministic
- [ ] Output sections are clearly labeled by task number

## 2. Num2 - List<T>

- [ ] Task 1: Read `coasters.txt` into `List<Coaster>`
- [ ] Task 2: Display first 6 and last 4
- [ ] Task 3: Rename first coaster and update last speed
- [ ] Task 4: Remove all from "Six Flags New Orleans"
- [ ] Task 5: Add Alpine Fury entry
- [ ] Task 6: Find shortest and fastest coaster
- [ ] Task 7: Sort by name then park
- [ ] Task 8: Display first 6 and last 4 after sort
- [ ] Task 9: Search Mantis/Cedar Point and Condor/The Great Escape
- [ ] Task 10: Display coasters with speed >= 70 mph

Validation:
- [ ] `Coaster` has usable `ToString()`
- [ ] Sorting logic matches assignment order
- [ ] Search criteria use both name and park when needed

## 3. Assignment Constraints

- [ ] No accented characters in code identifiers and string literals
- [ ] Required APIs are visibly used (`Array.IndexOf`, `Array.Sort`, `Array.BinarySearch`, `List<T>.Sort`)
- [ ] Num1 and Num2 stay in separate projects

## 4. Final Submission Readiness

- [ ] Both projects compile and run without runtime errors
- [ ] Output files (`Europe.txt`, `Asie.txt`) are generated
- [ ] Assignment PDF is present at `files/instructions/IFT1166H26TP3.pdf`
- [ ] `AUTHORS.md` is completed
- [ ] `ATTRIBUTIONS.md` is updated
- [ ] `AUTHORS.md` matricule placeholder is replaced
- [ ] All `[YYYY-MM-DD]` placeholders are replaced or marked `N/A`
- [ ] All `[ADD_URL]` placeholders are replaced or marked `N/A`
- [ ] Each solution folder is zipped for Studium submission
