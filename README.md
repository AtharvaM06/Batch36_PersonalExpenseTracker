BudgetX - Personal Expense tracker
Spend wisely. Save smartly.
Mini Hackathon

Team details
Batch: 36
Team Name : DeadHacks
Member 1: Atharva Mishra - 590040132
Member 2: Ayush Saxena - 590036856
Member 3: Naman Chauhan - 590036859
Faculty: Mrs. Arti Bahuguna

Problem statement
Build a simple expense tracker to help a student manage a monthly budget. Accept a monthly budget and multiple expenses; classify expenses into categories; calculate total spending and remaining budget; identify the highest-spending category; and warn if spending exceeds the budget.

Objectives and features
Set and update a monthly budget with positive-number validation.
Record up to 100 expenses with descriptions, amounts, categories, and unique IDs.
Categorize expenses as Food, Travel, Books, Entertainment, or Other.
View individual expenses and delete a record by ID.
Show category totals, total spending, remaining budget, budget usage %, and highest-spending category.
Show HEALTHY, MODERATE, CAUTION, CRITICAL, or EXCEEDED budget status.
Reject invalid amounts, category selections, menu options, and missing expense IDs.
C concepts demonstrated
struct / typedef, arrays, strings, fgets, sscanf, functions, loops, switch, if/else, constants, and formatted console output.

Compile and run
Requires a C11 compiler such as GCC:

gcc -std=c11 -Wall -Wextra -pedantic expense_tracker.c -lm -o expense_tracker
./expense_tracker
On Windows with GCC: gcc -std=c11 expense_tracker.c -lm -o expense_tracker.exe and then expense_tracker.exe.

Menu
1. Add expense
2. View expenses
3. Expense summary
4. Budget status
5. Delete expense
6. Change budget
7. Exit
Algorithm and flowchart
See `ALGORITHM.md` and `flowchart.png`. The program stores each expense in a structure within an array. Summary logic traverses the array and accumulates five category totals. Remaining budget = monthly budget − total spending.

Sample demonstration
Start with budget Rs. 10000 and add six expenses:

Description	Category	Amount (Rs.)
Lunch & Snacks	Food	1500
Bus / Auto	Travel	800
C Programming Book	Books	1200
Movie	Entertainment	600
Stationery	Other	400
Groceries	Food	2000
Expected: Rs. 6500 spent, Rs. 3500 remaining, 65% used, highest category Food (Rs. 3500), status MODERATE. Add an expense of Rs. 4000 to demonstrate an exceeded-budget warning of Rs. 500.

Testing
See `TEST_CASES.md` for normal, boundary, and invalid-input scenarios, and `test_run.txt` for the actual scripted run of the main demo.

Repository contents
expense_tracker.c
README.md
ALGORITHM.md
TEST_CASES.md
flowchart.png
flowchart.dot
Personal_Expense_Tracker_Presentation.pptx
test_run.txt
Known limitations and future scope
Data is not persisted after exit (in-memory array only).
Supports at most 100 expenses; one monthly budget per run.
Future improvements: file storage, date-based reports, category budgets, and graphical interface.
Presentation plan
Show the menu; add expenses; display the category summary; enter invalid input; exceed the budget; delete an expense; explain the structure, array, functions, and validation logic. Each team member should be ready to explain the entire program.





