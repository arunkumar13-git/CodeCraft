#include <stdio.h>
#include <string.h>

#define MAX_COMPLAINTS 100


struct CampusComplaint {
    char id[50];
    char category[50];
    char problem[100];
    char priority[50];
    char location[50];
    char status[50];
    int priority_score;
};

int main() {
    struct CampusComplaint complaints[MAX_COMPLAINTS];
    int num_inputs;
    int base_score = 0;

    printf("===========================================\n");
    printf("    CAMPUS COMPLAINT PRIORITY ENGINE       \n");
    printf("===========================================\n");
    
    printf("How many complaints do you want to enter? ");
    scanf("%d", &num_inputs);

    if (num_inputs > MAX_COMPLAINTS || num_inputs <= 0) {
        printf("Invalid number of inputs! Limiting to 1 to 100.\n");
        return 1;
    }

    for (int i = 0; i < num_inputs; i++) {
        printf("\n--- ENTER COMPLAINT #%d DETAILS ---\n", i + 1);
        printf("Enter Complaint ID (e.g., C105): "); 
        scanf("%s", complaints[i].id);
        
        printf("Enter Category: "); 
        scanf("%s", complaints[i].category);
        
        printf("Enter Problem Context (use_underscores): "); 
        scanf("%s", complaints[i].problem);
        
        printf("Enter Priority (Critical/High/Medium/Low): "); 
        scanf("%s", complaints[i].priority);
        
        printf("Enter Location: "); 
        scanf("%s", complaints[i].location);
        
        printf("Enter Status: "); 
        scanf("%s", complaints[i].status);

        if (strcmp(complaints[i].priority, "Critical") == 0) base_score = 400;
        else if (strcmp(complaints[i].priority, "High") == 0) base_score = 300;
        else if (strcmp(complaints[i].priority, "Medium") == 0) base_score = 200;
        else base_score = 100; // Low

        complaints[i].priority_score = base_score;
    }

    for (int i = 0; i < num_inputs - 1; i++) {
        for (int j = 0; j < num_inputs - i - 1; j++) {
            if (complaints[j].priority_score < complaints[j + 1].priority_score) {
                // Swap the entire complaint block records
                struct CampusComplaint temp = complaints[j];
                complaints[j] = complaints[j + 1];
                complaints[j + 1] = temp;
            }
        }
    }

    printf("\n=========================================================================\n");
    printf("                  PRIORITY DISPLAY LOG (HIGHEST FIRST)                   \n");
    printf("=========================================================================\n");
    printf("%-10s %-15s %-15s %-12s %-10s\n", "ID", "Category", "Location", "Priority", "SCORE");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < num_inputs; i++) {
        printf("%-10s %-15s %-15s %-12s %-10d\n", 
               complaints[i].id, complaints[i].category, complaints[i].location, 
               complaints[i].priority, complaints[i].priority_score);
    }
    printf("=========================================================================\n");

    return 0;
}
