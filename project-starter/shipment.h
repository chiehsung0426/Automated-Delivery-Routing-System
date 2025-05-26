#pragma once
#ifndef SHIPMENT_H
#define SHIPMENT_H

#include "mapping.h"
#include "truck.h"

#define VALID_BOX_SIZE {0.5, 1, 5}

/**
* A package represents a delivery item with weight, volume, and destination.
*/
struct Shipment
{
    double weight;  // Weight of the package in kilograms
    double volume;  // Volume of the package in cubic meters
    struct Point destination;  // Destination of the package
};

/**
* Read shipment details from the terminal
* @returns - a configurized package if it is valid, otherwise an empty shipment
*/
struct Shipment readShipmentDetails();

/**
* Validates the package details and provides an error message if any
* @param weight -  weight of  package
* @param volume - volume of package
* @param destination -  destination of  package
* @returns - 1 if the shipment is valid, false otherwise
*/
int validateShipment(double weight, double volume, struct Point destination);

#endif
