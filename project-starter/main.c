#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "shipment.h"
#include "truck.h"
#include "integration.h"

int main(void) {

    int choice;
    struct Map map;
    struct Shipment shipment;
    struct Truck trucks[3];

    while (1) {
        // Clear the screen 
        printf("\033[2J\033[H");

        // Display menu
        printf("Choose an option:\n");
        printf("1. Perform Shipment Handling\n");
        printf("2. Integration Test\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear the incorrect input
            printf("\nInvalid input. Please enter a number: ");
        }

        printf("\033[2J\033[H");

        if (choice == 1) {
            map = populateMap();
 

            trucks[0] = configureTruck(getBlueRoute(), 'B');
            trucks[1] = configureTruck(getYellowRoute(), 'Y');
            trucks[2] = configureTruck(getGreenRoute(), 'G');

            do {
                shipment = readShipmentDetails();
                if (shipment.weight <= 0) break;

                appropriateTruck(trucks, 3, shipment, &map);
            } while (shipment.weight > 0);
        }
        else if (choice == 2) {
            integrationTest();
        }
        else if (choice == 0) {
            printf("Exiting the program.\n");
            return 0;
        }
        else {
            printf("Invalid option. Please try again.\n");
        }

        printf("Press Enter to continue...");
        while (getchar() != '\n'); // Wait for Enter key
        while (getchar() != '\n'); // Ensure the buffer is clear
    }

    return 0;
}