#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include "shipment.h"
#include "mapping.h"
#include "truck.h"
#include <stdlib.h> 

// Read shipment details from the user input
struct Shipment readShipmentDetails() {

    struct Shipment shipment = { 0, 0, {0, 0} };
    int validInput, check = 0;
    char temp[4]; // Using a string to capture the column character

    while (1) {

        printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
        validInput = scanf("%lf %lf %s", &shipment.weight, &shipment.volume, temp);

        if (shipment.weight == 0 && shipment.volume == 0 && toupper(temp[0]) == 'X' && temp[1] == '\0') {
            printf("Thanks for shipping with Seneca!\n");
            break;  
        }

        if (validInput == 3) {  // Check if the input is in the correct format
            // Process the destination
            int num;
            char col;
            if (sscanf(temp, "%d%c", &num, &col) == 2) {
                shipment.destination.row = num - 1;
                shipment.destination.col = toupper(col) - 'A';

                if (validateShipment(shipment.weight, shipment.volume, shipment.destination)) {
                    break;  // Exit the loop if the shipment is valid
                }
            }

        }

        while (getchar() != '\n');
    }

    return shipment;

} 
/*
The bugs of the original readShipmentDetails function:
1. **Limited Validation**: It directly assumes the user inputs the data in the correct format without additional validation or error handling if the format is not as expected.  Ex.A space in destination '100 0.5 10 A'
2. **Buffer Overflow Vulnerability**: Since it reads a character directly for the column, it doesn’t account for accidental extra character input, potentially leading to buffer overflow or unexpected behavior if more than one character is entered for the column. Ex. '100 0.5 10AA'
3. **User Error Handling**: It lacks a clear mechanism for handling common user input errors, such as entering extra characters or spaces. Ex. enter 'exit', 'stop' or '0' instead of the specified '0 0 x' format
Overall improvement:
1.Robustness: The new approach is more robust against varied user inputs, reducing the likelihood of crashes or undefined behavior due to unexpected input formats.
2.User Experience: It improves the user experience by handling edge cases more gracefully, such as additional characters in the input or spaces that might have caused issues in the original version.
3.Security: By using a buffer (temp) and parsing it with sscanf, it potentially mitigates risks associated with directly reading values into variables, especially in terms of buffer overflow or unexpected input.
*/


// Validates the details of the shipment
int validateShipment(double weight, double volume, struct Point destination)
{
    double validSize[3] = VALID_BOX_SIZE;
   
    int isValid = 1; // Assume the shipment is valid initially
    struct Map map = populateMap(); // Assume this function populates a map of valid destinations

    // Weight validation
    if (weight > MAX_WEIGHT || weight < MIN_WEIGHT)
    {
        printf("Invalid weight (must be %.lf-%.lf Kg.)\n", (double)(MIN_WEIGHT), (double)(MAX_WEIGHT));
        isValid = 0;
    }

    // Volume validation
    int volumeIsValid = 0;
    for (int i = 0; i < sizeof(validSize) / sizeof(validSize[0]); i++) {
        if (volume == validSize[i]) {
            volumeIsValid = 1;
            break;
        }
    }
    if (!volumeIsValid) {
        printf("Invalid  size\n");
        isValid = 0;
    }

    // Destination validation
    if (!BuildingBlock(destination, map)) {
        printf("Invalid destination\n");
        isValid = 0;
    }

    return isValid;
}