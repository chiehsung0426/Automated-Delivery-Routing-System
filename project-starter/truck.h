#pragma once
#ifndef TRUCK_H
#define TRUCK_H

#include "shipment.h"
#include "mapping.h"

#define MAX_VOLUME 50
#define MAX_WEIGHT 1200
#define MIN_WEIGHT 1

/**
* A truck represents a delivery vehicle with weight and volume capacity.
*/
struct Truck
{
    double presentWeightInKg;  // weight present already in the truck
    double presentVolumeInM;  // volume present already in the truck
    struct Route route;  // Route of the truck
    struct Point location; // loaction of the truck
    char pathColor;
    // the location must lie on the route
};

/**
* Configurizes a truck with the  weight, volume, and route.
* @param route - the route of the truck
* @returns - a configurized truck
*/
struct Truck configureTruck(struct Route route, char color);

/**
* Find the appropriate truck to based on  space ,volume and distance available to deliver the shipment.
* @param trucks - array of delivery trucks available
* @param numOfTrucks - the number of trucks that are in array
* @param shipment - the shipment to be delivered
* @param map - the map to refer to
* @param color - the color of the truck's route
* @returns - the index of the best truck to deliver the  shipment, or -1 if no suitable truck is found
*/
void appropriateTruck(struct Truck trucks[], int numOfTrucks, struct Shipment shipment, const struct Map* map);

/**
* checks whether the truck has enough space for the Shipment
* @param truck - truck that is being checked for space
* @param shipment - the shipment to be delivered
* @returns - 1 ithe truck has enough space for the shipment, false otherwise.
*/
int enoughSpace(struct Truck truck, struct Shipment shipment);

/**
*  checks for the truck with more space
* @param t1 - truck to compare
* @param t2 - truck to compare
* @returns - 1 if t1 has more space false otherwise
*/
int moreSpace(struct Truck t1, struct Truck t2);

/**
* Calculates the percentage space of both volume and weight left in the truck.
* @param truck - truck to be evaluated
* @returns - the value of available percentage space left
*/
double availablePercentageLeft(struct Truck truck);

/**
* print the diversion seprated by commas
* @param route - route to be printed
*/
void truckDiversions(struct Route* route);

/**
* checks if there is enough space for shipment
* if yes:
* @param truck - truck shipment is added to
* @param shipment - shipment to be added
*/
void loadDiversions(struct Truck* truck, const struct Shipment shipment);

#endif

