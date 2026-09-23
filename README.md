# Data Structures Comparison — Electoral Roll

Coursework for *Estructuras de Datos y Algoritmos*, Universidad Nacional de San Luis, 2026.

An electoral roll implemented over three different data structures, with a
comparison of what it costs to insert, delete and look up a voter in each one.

**Authors:** Lorenzo Luna and Santino Capdevila (Group 15)

## Structures

- **LVO** — Sorted linked list terminated by content (a sentinel node holding +infinity).
- **LSOBB** — Sorted sequential list with binary search (bisection, inclusive bounds, witness kept on the left, larger segment on the left).
- **ABB** — Binary search tree. Deletion of a node with two children uses the *smallest of the larger* policy, replacing by copying the data.

Each structure supports the same four operations: insert, delete, look up and
display. Deletion is confirmed by comparing the whole tuple, not just the ID,
and string comparison is case insensitive.

## Cost model

| Operation | How it is measured |
|---|---|
| Insert / delete in LSOBB | 1 per element shifted |
| Insert / delete in LVO and ABB | 0.5 per pointer modified |
| Delete in ABB with replacement | + 1 for the data copy |
| Lookups | 1 per cell visited |

## Results

Over the 8975 operations in `Operaciones_Padron.txt`, with a peak of 2001
voters held at the same time:

| | Insert (avg / max) | Delete (avg / max) | Lookup hit (avg / max) | Lookup miss (avg / max) |
|---|---|---|---|---|
| **LSOBB** | 413.65 / 2000 | 503.36 / 2000 | 10.14 / 11 | 9.88 / 11 |
| **LVO** | 1.00 / 1.00 | 0.50 / 0.50 | 566.80 / 1994 | 463.47 / 1206 |
| **ABB** | 0.50 / 0.50 | 1.02 / 1.50 | 11.84 / 22 | 12.03 / 21 |

No structure wins across the board. The LSOBB is the best at lookups and the
worst at inserting; the LVO is exactly the other way round. The ABB is not the
best at any single operation, but it is the only one that is not bad at any of
them.

The ABB result depends on the order the IDs arrive in. Had they come in sorted,
the tree would degenerate into a list and lookups would go from O(log N) to
O(N). Even with the shuffled data in the input file the tree reached a height
of 22, where a balanced tree holding 2001 nodes would be 11.

## Build and run

With Code::Blocks, open `P1-Grupo15.cbp` and build.

From a terminal:

```
gcc -o padron main.c LVO.c LSOBB.c ABB.c Elector.c
```

`Operaciones_Padron.txt` must sit in the directory the program is run from.
Each line of that file holds an operation code (1 insert, 2 delete, 3 lookup)
followed by the voter's fields, one per line.
