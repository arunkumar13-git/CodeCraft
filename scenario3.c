#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

struct PatientRequest {
    char id[50];
    char name[50];
    int age;
    char condition[50];
    char department[50];
    char status[50];
    int priority_score;
};

int main() {
    struct PatientRequest patients[MAX_PATIENTS];
    int total_patients = 0;
    
    int choice;
    int base_score = 0;

    do {
        printf("\n===========================================\n");
        printf("    HOSPITAL TRIAGE CONTROL MAIN MENU      \n");
        printf("===========================================\n");
        printf("1. Register a Patient Triage Request\n");
        printf("2. View Patient Queue (Sorted by Urgency)\n");
        printf("3. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (total_patients >= MAX_PATIENTS) {
                printf("\n[ERROR] Triage Ward Full! Cannot add more patients.\n");
                continue;
            }

            struct PatientRequest *pat = &patients[total_patients];

            printf("\n--- Enter Patient Triage Details (#%d) ---\n", total_patients + 1);
            printf("Enter Patient ID: ");
            scanf("%s", pat->id);
            printf("Enter Patient Name: ");
            scanf("%s", pat->name);
            printf("Enter Patient Age: ");
            scanf("%d", &pat->age);
            printf("Enter Condition/Priority Level (Critical/Abnormal/Fever): ");
            scanf("%s", pat->condition);
            printf("Enter Assigned Department: ");
            scanf("%s", pat->department);
            printf("Enter Current Status: ");
            scanf("%s", pat->status);

            // Calculate Base Triage Priority Score based on condition
            if (strcmp(pat->condition, "Critical") == 0) {
                base_score = 300;
            } else if (strcmp(pat->condition, "Abnormal") == 0) {
                base_score = 200;
            } else if (strcmp(pat->condition, "Fever") == 0) {
                base_score = 100;
            } else {
                base_score = 50; 
            }

            // Older age slightly weights high priority within the same severity level
            pat->priority_score = base_score + (pat->age / 2);
            
            total_patients++; 
            printf("\n[SUCCESS] Patient triage profile saved into slot %d!\n", total_patients);

        } else if (choice == 2) {
            if (total_patients == 0) {
                printf("\nNo patients registered yet! Please choose option 1 first.\n");
                continue;
            }

            // Sorting entire data structures using descending bubble sort
            for (int i = 0; i < total_patients - 1; i++) {
                for (int j = 0; j < total_patients - i - 1; j++) {
                    if (patients[j].priority_score < patients[j + 1].priority_score) {
                        // Swap entire structure blocks using a temporary container variable
                        struct PatientRequest temp = patients[j];
                        patients[j] = patients[j + 1];
                        patients[j + 1] = temp;
                    }
                }
            }

            printf("\n=========================================================================================\n");
            printf("                               LIVE ER PATIENT TRIAGE QUEUE                              \n");
            printf("=========================================================================================\n");
            printf("%-10s %-15s %-6s %-12s %-15s %-10s %-8s\n", "ID", "Name", "Age", "Priority", "Department", "Status", "SCORE");
            printf("-----------------------------------------------------------------------------------------\n");
            for (int i = 0; i < total_patients; i++) {
                printf("%-10s %-15s %-6d %-12s %-15s %-10s %-8d\n", 
                       patients[i].id, patients[i].name, patients[i].age, 
                       patients[i].condition, patients[i].department, patients[i].status, patients[i].priority_score);
            }
            printf("=========================================================================================\n");
        }

    } while (choice != 3);

    printf("\nExiting Hospital Triage System. System Offline.\n");
    return 0;
}
