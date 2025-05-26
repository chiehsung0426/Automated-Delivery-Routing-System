#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include "shipment.h"
#include "mapping.h"
#include "truck.h"
#include "integration.h"
#include <stdlib.h> 


void integrationTest() {

    printf("Integration Test - Starting\n\n");

    // Test Case 1: Check if the truck has enough space for a valid shipment
    double WeightTest1 = 50.0;
    double VolumeTest1 = 0.5;
    struct Point DestinationTest1 = { 24 - 1 , 'Y' - 'A' };
    struct Shipment shipment1 = { WeightTest1, VolumeTest1, DestinationTest1 };
    struct Truck truck1 = { 100, 1.0, { 8 - 1 , 'Y' - 'A' } };
    int isValid1 = validateShipment(shipment1.weight, shipment1.volume, shipment1.destination);
    printf("1. Test to check if the truck has enough space\n\n");
    if (isValid1) {
        int hasSpace1 = enoughSpace(truck1, shipment1);
        printf("Expected: Shipment is valid and the truck has enough space.\n");
        printf("Actual  : Shipment is %svalid and the truck %shas enough space.\n\n",
            isValid1 ? "" : "not ", hasSpace1 ? "" : "does not ");
    }
    else {
        printf("Shipment is not valid.\n\n");
    }

    // Test Case 2: Check when the truck does not have enough space for a valid shipment
    double WeightTest2 = 657.0;
    double VolumeTest2 = 5.0;
    struct Point DestinationTest2 = { 15 - 1 , 'M' - 'A' };
    struct Shipment shipment2 = { WeightTest2, VolumeTest2, DestinationTest2 };
    struct Truck truck2 = { 1200, 5, {3 - 1 , 'E' - 'A'} };
    int isValid2 = validateShipment(shipment2.weight, shipment2.volume, shipment2.destination);
    printf("2. Test to check if the truck doesn't have enough space\n\n");
    if (isValid2) {
        int hasSpace2 = enoughSpace(truck2, shipment2);
        printf("Expected: Shipment is valid, but the truck does not have enough space.\n");
        printf("Actual  : Shipment is %svalid and the truck %shas enough space.\n\n",
            isValid2 ? "" : "not ", hasSpace2 ? "does " : "does not ");
    }
    else {
        printf("Shipment is not valid.\n\n");
    }

    printf("Integration Test - Ended\n\n");
}