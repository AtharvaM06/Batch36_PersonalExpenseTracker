# Sample test cases and expected outputs

Run each scenario in a fresh execution unless stated otherwise. Values below are **expected results** for the provided C program; see `test_run.txt` for an actual automated run.

| ID | Scenario / inputs | Expected result |
|---|---|---|
| TC01 | Budget 10000; Food 1500; Travel 800; Books 1200; Entertainment 600; Other 400; Food 2000 | Total Rs. 6500.00; remaining Rs. 3500.00; used 65.00%; highest Food Rs. 3500.00; MODERATE |
| TC02 | Budget 1000; Food 1200 | Immediate warning; exceeded by Rs. 200.00; EXCEEDED |
| TC03 | Budget 1000; no expenses; view summary | Total Rs. 0.00; remaining Rs. 1000.00; highest category none; HEALTHY |
| TC04 | Enter budget -500, then 1000 | Invalid amount rejected; budget accepted at Rs. 1000.00 |
| TC05 | Budget 1000; try expense amount 0, then 100 | Zero rejected; 100 accepted |
| TC06 | Budget 1000; category 9 then 1 | 9 rejected; Food accepted |
| TC07 | Budget 1000; add Food 100 (ID 1), Travel 200 (ID 2); delete ID 1 | Remaining expense ID 2; total Rs. 200.00 |
| TC08 | Budget 1000; delete ID 999 after adding an expense | `Expense ID not found.`; data unchanged |
| TC09 | Budget 1000; Food 900 | CRITICAL (90% used) |
| TC10 | Budget 1000; Food 750 | CAUTION (75% used) |
| TC11 | Budget 1000; Food 500 | MODERATE (50% used) |
| TC12 | Budget 1000; Food 1000 | CRITICAL; not EXCEEDED (exceeded means strictly greater) |

**Limitations:** Records are stored in memory only and disappear when the program exits. Maximum 100 expenses. Category ties are resolved in favor of the first category in menu order. The program is a command-line demonstration, not a banking or accounting system.
