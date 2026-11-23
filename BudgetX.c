/*
=============================================================
              BudgetX - Personal Expense Tracker
              C Programming Mini Hackathon
=============================================================

Features:
1. Set monthly budget
2. Add multiple expenses
3. Categorize expenses
4. View all expenses
5. Category-wise expense summary
6. Calculate total spending
7. Calculate remaining budget
8. Find highest spending category
9. Budget usage percentage
10. Warning when budget is exceeded
11. Input validation
12. Delete an expense
13. Simple financial insights

Concepts Used:
- Variables and Data Types
- Conditional Statements
- Loops
- Arrays
- Strings
- Functions
- Structures
- Input Validation
=============================================================
*/

#include <stdio.h>
#include <string.h>

#define MAX_EXPENSES 100
#define CATEGORY_COUNT 5

/* Structure for storing one expense */
struct Expense
{
    int id;
    char description[50];
    float amount;
    int category;
};

/* Global data */
struct Expense expenses[MAX_EXPENSES];

int expenseCount = 0;
float monthlyBudget = 0.0;

/* Category names */
const char *categoryNames[CATEGORY_COUNT] =
{
    "Food",
    "Travel",
    "Books",
    "Entertainment",
    "Other"
};

/* Function declarations */
void printHeader(void);
void displayMenu(void);
void setBudget(void);
void addExpense(void);
void viewExpenses(void);
void showSummary(void);
void checkBudgetStatus(void);
void deleteExpense(void);
void showCategoryMenu(void);
float calculateTotalSpending(void);
void calculateCategoryTotals(float totals[]);
int findHighestCategory(float totals[]);
void clearInputBuffer(void);


/* =========================
           MAIN
   ========================= */

int main(void)
{
    int choice;

    printHeader();

    printf("\nWelcome to BudgetX your own expense tracker!\n");
    printf("Manage your money. Understand your spending.\n");

    setBudget();

    do
    {
        displayMenu();

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n[ERROR] Please enter a valid number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice)
        {
            case 1:
                addExpense();
                break;

            case 2:
                viewExpenses();
                break;

            case 3:
                showSummary();
                break;

            case 4:
                checkBudgetStatus();
                break;

            case 5:
                deleteExpense();
                break;

            case 6:
                setBudget();
                break;

            case 7:
                printf("\n========================================\n");
                printf(" Thank you for using Expense Tracker!\n");
                printf(" Spend wisely. Save smartly!\n");
                printf("========================================\n");
                break;

            default:
                printf("\n[ERROR] Please choose an option from 1 to 7.\n");
        }

    } while (choice != 7);

    return 0;
}


/* =========================
       HEADER AND MENU
   ========================= */

void printHeader(void)
{
    printf("\n");
    printf("==============================================\n");
    printf("        BUDGETX - PERSONAL EXPENSE TRACKER\n");
    printf("==============================================\n");
}

void displayMenu(void)
{
    printf("\n");
    printf("============== MAIN MENU ==============\n");
    printf("1. Add Expense\n");
    printf("2. View All Expenses\n");
    printf("3. View Expense Summary\n");
    printf("4. Check Budget Status\n");
    printf("5. Delete Expense\n");
    printf("6. Change Monthly Budget\n");
    printf("7. Exit\n");
    printf("=======================================\n");
}


/* =========================
         SET BUDGET
   ========================= */

void setBudget(void)
{
    float budget;

    while (1)
    {
        printf("\nEnter your monthly budget (Rs.): ");

        if (scanf("%f", &budget) != 1)
        {
            printf("[ERROR] Invalid input. Enter a numeric amount.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (budget <= 0)
        {
            printf("[ERROR] Budget must be greater than zero.\n");
        }
        else
        {
            monthlyBudget = budget;

            printf("\n[SUCCESS] Monthly budget set to Rs. %.2f\n",
                   monthlyBudget);
            break;
        }
    }
}


/* =========================
       CATEGORY MENU
   ========================= */

void showCategoryMenu(void)
{
    int i;

    printf("\nSelect Expense Category:\n");

    for (i = 0; i < CATEGORY_COUNT; i++)
    {
        printf("%d. %s\n", i + 1, categoryNames[i]);
    }
}


/* =========================
        ADD EXPENSE
   ========================= */

void addExpense(void)
{
    struct Expense newExpense;
    int category;
    float amount;

    if (expenseCount >= MAX_EXPENSES)
    {
        printf("\n[ERROR] Maximum expense limit reached.\n");
        return;
    }

    printf("\n========== ADD NEW EXPENSE ==========\n");

    /*
       Expense ID is generated automatically.
       IDs start from 1.
    */
    newExpense.id = expenseCount + 1;

    printf("Enter expense description: ");

    fgets(newExpense.description,
          sizeof(newExpense.description),
          stdin);

    /* Remove newline added by fgets */
    newExpense.description[
        strcspn(newExpense.description, "\n")
    ] = '\0';

    /* Description validation */
    if (strlen(newExpense.description) == 0)
    {
        strcpy(newExpense.description, "No Description");
    }

    /* Amount validation */
    while (1)
    {
        printf("Enter expense amount (Rs.): ");

        if (scanf("%f", &amount) != 1)
        {
            printf("[ERROR] Please enter a valid amount.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (amount <= 0)
        {
            printf("[ERROR] Expense must be greater than zero.\n");
        }
        else
        {
            break;
        }
    }

    showCategoryMenu();

    /* Category validation */
    while (1)
    {
        printf("Enter category number (1-%d): ",
               CATEGORY_COUNT);

        if (scanf("%d", &category) != 1)
        {
            printf("[ERROR] Enter a valid category number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (category < 1 || category > CATEGORY_COUNT)
        {
            printf("[ERROR] Category must be between 1 and %d.\n",
                   CATEGORY_COUNT);
        }
        else
        {
            break;
        }
    }

    newExpense.amount = amount;
    newExpense.category = category - 1;

    expenses[expenseCount] = newExpense;
    expenseCount++;

    printf("\n--------------------------------------\n");
    printf("[SUCCESS] Expense added!\n");
    printf("Description : %s\n", newExpense.description);
    printf("Category    : %s\n",
           categoryNames[newExpense.category]);
    printf("Amount      : Rs. %.2f\n",
           newExpense.amount);
    printf("--------------------------------------\n");

    /*
       Immediately warn the user if the new expense
       causes the budget to be exceeded.
    */
    if (calculateTotalSpending() > monthlyBudget)
    {
        printf("\n*** WARNING: MONTHLY BUDGET EXCEEDED! ***\n");
    }
}


/* =========================
       VIEW EXPENSES
   ========================= */

void viewExpenses(void)
{
    int i;

    printf("\n================ ALL EXPENSES =================\n");

    if (expenseCount == 0)
    {
        printf("No expenses recorded yet.\n");
        return;
    }

    printf("%-5s %-22s %-17s %-12s\n",
           "ID",
           "Description",
           "Category",
           "Amount");

    printf("----------------------------------------------------------\n");

    for (i = 0; i < expenseCount; i++)
    {
        printf("%-5d %-22s %-17s Rs. %-8.2f\n",
               expenses[i].id,
               expenses[i].description,
               categoryNames[expenses[i].category],
               expenses[i].amount);
    }

    printf("----------------------------------------------------------\n");

    printf("Total number of expenses: %d\n", expenseCount);
}


/* =========================
     CALCULATE TOTAL
   ========================= */

float calculateTotalSpending(void)
{
    int i;
    float total = 0.0;

    for (i = 0; i < expenseCount; i++)
    {
        total += expenses[i].amount;
    }

    return total;
}


/* =========================
      CATEGORY TOTALS
   ========================= */

void calculateCategoryTotals(float totals[])
{
    int i;

    /* Initialize all category totals to zero */
    for (i = 0; i < CATEGORY_COUNT; i++)
    {
        totals[i] = 0.0;
    }

    /* Add each expense to its category */
    for (i = 0; i < expenseCount; i++)
    {
        totals[expenses[i].category] += expenses[i].amount;
    }
}


/* =========================
      HIGHEST CATEGORY
   ========================= */

int findHighestCategory(float totals[])
{
    int i;
    int highestIndex = 0;

    for (i = 1; i < CATEGORY_COUNT; i++)
    {
        if (totals[i] > totals[highestIndex])
        {
            highestIndex = i;
        }
    }

    return highestIndex;
}


/* =========================
       EXPENSE SUMMARY
   ========================= */

void showSummary(void)
{
    float categoryTotals[CATEGORY_COUNT];
    float total;
    float remaining;
    float percentage;
    int highestCategory;
    int i;

    printf("\n");
    printf("==============================================\n");
    printf("              EXPENSE SUMMARY\n");
    printf("==============================================\n");

    total = calculateTotalSpending();
    remaining = monthlyBudget - total;

    calculateCategoryTotals(categoryTotals);

    printf("Monthly Budget       : Rs. %.2f\n",
           monthlyBudget);

    printf("----------------------------------------------\n");

    printf("CATEGORY-WISE SPENDING\n\n");

    for (i = 0; i < CATEGORY_COUNT; i++)
    {
        printf("%-20s : Rs. %.2f\n",
               categoryNames[i],
               categoryTotals[i]);
    }

    printf("----------------------------------------------\n");

    printf("Total Spending       : Rs. %.2f\n", total);

    if (remaining >= 0)
    {
        printf("Remaining Budget     : Rs. %.2f\n",
               remaining);
    }
    else
    {
        printf("Budget Exceeded By   : Rs. %.2f\n",
               -remaining);
    }

    /*
       Avoid division by zero.
       Budget should already be positive due to validation.
    */
    percentage = (total / monthlyBudget) * 100;

    printf("Budget Used          : %.2f%%\n", percentage);

    printf("----------------------------------------------\n");

    if (expenseCount > 0)
    {
        highestCategory =
            findHighestCategory(categoryTotals);

        printf("Highest Expenditure  : %s\n",
               categoryNames[highestCategory]);

        printf("Amount               : Rs. %.2f\n",
               categoryTotals[highestCategory]);
    }
    else
    {
        printf("Highest Expenditure  : No expenses yet\n");
    }

    printf("----------------------------------------------\n");

    /*
       Give a useful status based on budget usage.
    */
    if (total > monthlyBudget)
    {
        printf("BUDGET STATUS : EXCEEDED\n");
        printf("*** WARNING: You have exceeded your budget! ***\n");
    }
    else if (percentage >= 90)
    {
        printf("BUDGET STATUS : CRITICAL\n");
        printf("Warning: More than 90%% of your budget is used.\n");
    }
    else if (percentage >= 75)
    {
        printf("BUDGET STATUS : CAUTION\n");
        printf("You have used more than 75%% of your budget.\n");
    }
    else if (percentage >= 50)
    {
        printf("BUDGET STATUS : MODERATE\n");
        printf("You have used more than half of your budget.\n");
    }
    else
    {
        printf("BUDGET STATUS : HEALTHY\n");
        printf("Great! Your spending is under control.\n");
    }

    printf("==============================================\n");
}


/* =========================
       BUDGET STATUS
   ========================= */

void checkBudgetStatus(void)
{
    float total;
    float remaining;
    float percentage;

    total = calculateTotalSpending();
    remaining = monthlyBudget - total;
    percentage = (total / monthlyBudget) * 100;

    printf("\n========== BUDGET STATUS ==========\n");

    printf("Monthly Budget : Rs. %.2f\n",
           monthlyBudget);

    printf("Total Spent    : Rs. %.2f\n",
           total);

    printf("Budget Used    : %.2f%%\n",
           percentage);

    if (total > monthlyBudget)
    {
        printf("\n*** BUDGET EXCEEDED! ***\n");

        printf("Exceeded By    : Rs. %.2f\n",
               total - monthlyBudget);

        printf("Suggestion     : Reduce unnecessary spending.\n");
    }
    else
    {
        printf("Remaining      : Rs. %.2f\n",
               remaining);

        if (percentage >= 90)
        {
            printf("\nStatus: CRITICAL\n");
            printf("Suggestion: Avoid non-essential expenses.\n");
        }
        else if (percentage >= 75)
        {
            printf("\nStatus: CAUTION\n");
            printf("Suggestion: Monitor upcoming expenses carefully.\n");
        }
        else if (percentage >= 50)
        {
            printf("\nStatus: MODERATE\n");
            printf("Suggestion: You are doing fine, but spend wisely.\n");
        }
        else
        {
            printf("\nStatus: HEALTHY\n");
            printf("Suggestion: Excellent budget management!\n");
        }
    }

    printf("===================================\n");
}


/* =========================
       DELETE EXPENSE
   ========================= */

void deleteExpense(void)
{
    int id;
    int index = -1;
    int i;

    if (expenseCount == 0)
    {
        printf("\nNo expenses available to delete.\n");
        return;
    }

    viewExpenses();

    printf("\nEnter the ID of the expense to delete: ");

    if (scanf("%d", &id) != 1)
    {
        printf("[ERROR] Invalid ID.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    /* Find expense with matching ID */
    for (i = 0; i < expenseCount; i++)
    {
        if (expenses[i].id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("[ERROR] Expense ID not found.\n");
        return;
    }

    printf("\nDeleting: %s - Rs. %.2f\n",
           expenses[index].description,
           expenses[index].amount);

    /*
       Shift all expenses after the deleted
       expense one position to the left.
    */
    for (i = index; i < expenseCount - 1; i++)
    {
        expenses[i] = expenses[i + 1];
    }

    expenseCount--;

    /*
       Reassign IDs to keep them simple:
       1, 2, 3, ...
    */
    for (i = 0; i < expenseCount; i++)
    {
        expenses[i].id = i + 1;
    }

    printf("[SUCCESS] Expense deleted successfully.\n");
}


/* =========================
       INPUT UTILITY
   ========================= */

void clearInputBuffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Discard unwanted characters */
    }
}