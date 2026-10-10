#include <stdio.h>
#include <string.h>

#define MAX_REQUESTS 100

struct RescueRequest {
    char id[50];
    char location[50];
    int people;
    char emergency[50];
    char resources[50];
    char status[50];
    int priority_score;
};

int main() {
    struct RescueRequest requests[MAX_REQUESTS];
    int total_requests = 0;
    
    int choice;
    int base_score = 0;

    do {
        printf("\n===========================================\n");
        printf("    EMERGENCY CONTROL ROOM MAIN MENU       \n");
        printf("===========================================\n");
        printf("1. Enter an Emergency Request\n");
        printf("2. View All Requests (Sorted by Priority)\n");
        printf("3. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (total_requests >= MAX_REQUESTS) {
                printf("\n[ERROR] Database full! Cannot add more requests.\n");
                continue;
            }

            struct RescueRequest *req = &requests[total_requests];

            printf("\n--- Enter Request Details (#%d) ---\n", total_requests + 1);
            printf("Enter Request ID: ");
            scanf("%s", req->id);
            printf("Enter Location: ");
            scanf("%s", req->location);
            printf("Enter Number of People Affected: ");
            scanf("%d", &req->people);
            printf("Enter Emergency Level (Critical/Severe/Moderate/Minor): ");
            scanf("%s", req->emergency);
            printf("Enter Required Resources: ");
            scanf("%s", req->resources);
            printf("Enter Current Status: ");
            scanf("%s", req->status);

            // Calculate Base Priority Score
            if (strcmp(req->emergency, "Critical") == 0) {
                base_score = 400;
            } else if (strcmp(req->emergency, "Severe") == 0) {
                base_score = 300;
            } else if (strcmp(req->emergency, "Moderate") == 0) {
                base_score = 200;
            } else {
                base_score = 100;
            }

            req->priority_score = base_score + req->people;
            
            total_requests++; // Increment counter so the next input goes into the next slot
            printf("\n[SUCCESS] Request saved into slot %d!\n", total_requests);

        } else if (choice == 2) {
            if (total_requests == 0) {
                printf("\nNo requests entered yet! Please choose option 1 first.\n");
                continue;
            }

            for (int i = 0; i < total_requests - 1; i++) {
                for (int j = 0; j < total_requests - i - 1; j++) {
                    if (requests[j].priority_score < requests[j + 1].priority_score) {
                        // Swap entire structure blocks using a temporary container variable
                        struct RescueRequest temp = requests[j];
                        requests[j] = requests[j + 1];
                        requests[j + 1] = temp;
                    }
                }
            }

            printf("\n=========================================================================\n");
            printf("                       LIVE PRIORITY RESCUE QUEUE                         \n");
            printf("=========================================================================\n");
            printf("%-10s %-15s %-8s %-12s %-12s %-10s\n", "ID", "Location", "People", "Emergency", "Resource", "SCORE");
            printf("-------------------------------------------------------------------------\n");
            for (int i = 0; i < total_requests; i++) {
                printf("%-10s %-15s %-8d %-12s %-12s %-10d\n", 
                       requests[i].id, requests[i].location, requests[i].people, 
                       requests[i].emergency, requests[i].resources, requests[i].priority_score);
            }
            printf("=========================================================================\n");
        }

    } while (choice != 3);

    printf("\nExiting Control Room Application. Goodbye!\n");
    return 0;
}
