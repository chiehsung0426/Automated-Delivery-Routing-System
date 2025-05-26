#include <stdio.h>
#include "truck.h"
#include "mapping.h"
#include "shipment.h"

struct Truck configureTruck(struct Route route, char color)
{
    struct Truck truck = { 0 };
    struct Point location = { 'A', 'A' };
    truck.presentVolumeInM = 0.0;
    truck.presentWeightInKg = 0.0;
    truck.route = route;
    truck.location = location;
    truck.pathColor = color;

    return truck;
}

void appropriateTruck(struct Truck trucks[], int numOfTrucks, struct Shipment shipment, const struct Map* map)
{
    int i = -1;
    int leastDistance = -1;
    int truckNumber = -1;
    struct Route BestRoute = { 0 };

    for (i = 0; i < numOfTrucks; i++)
    {
        if (enoughSpace(trucks[i], shipment))
        {

            struct Route route = findClosestPoint(map, trucks[i].route, shipment.destination);

            if (route.numPoints > 0 &&
                (route.numPoints < leastDistance ||
                    leastDistance == -1 ||
                    (leastDistance == route.numPoints && moreSpace(trucks[i], trucks[truckNumber]))))
            {
                BestRoute = route;
                truckNumber = i;
                leastDistance = BestRoute.numPoints;
            }
        }
    }
    if (truckNumber != -1) {

        loadDiversions(&trucks[truckNumber], shipment);

        printf("Ship on ");

        switch (trucks[truckNumber].pathColor) {

        case 'B':
            printf("BLUE LINE, ");
            break;
        case 'Y':
            printf("YELLOW LINE, ");
            break;
        case 'G': printf("GREEN LINE, ");
            break;
        default:
            break;
        }
        truckDiversions(&BestRoute);
    }
    else
    {
        printf("Ships tomorrow");
    }
    printf("\n");
}

/*At first we used int as our type in the enoughspace function but it caused errors due to the original struct type being double so we changed to double to make the code run properly.*/
int enoughSpace(struct Truck truck, struct Shipment shipment) {

    double availableWeight = MAX_WEIGHT - truck.presentWeightInKg;
    double availableVolume = MAX_VOLUME - truck.presentVolumeInM;

    double isWeightSufficient = availableWeight >= shipment.weight;
    double isVolumeSufficient = availableVolume >= shipment.volume;

    return isWeightSufficient && isVolumeSufficient;
}

int moreSpace(struct Truck t1, struct Truck t2)
{
    return availablePercentageLeft(t1) > availablePercentageLeft(t2);
}

double availablePercentageLeft(struct Truck truck)
{
        double volumePercentage = (truck.presentVolumeInM * 100) / MAX_VOLUME;
        double weightPercentage = (truck.presentWeightInKg * 100) / MAX_WEIGHT;

        return (volumePercentage + weightPercentage) / 2;
   
}

void truckDiversions(struct Route* route)
{
    if (route->numPoints == 2)
    {
        printf("no diversion");
    }
    else if (route->numPoints > 2)
    {
        int i = 0;
        printf("divert: ");
        for (i = 0; i < route->numPoints - 1; i++)
        {
            printf("%d%c,", route->points[i].row + 1, route->points[i].col + 'A');
        }
        printf("%d%c", route->points[i].row + 1, route->points[i].col + 'A');
    }
}

void loadDiversions(struct Truck* truck, const struct Shipment shipment)
{
    if (enoughSpace(*truck, shipment))
    {
        truck->presentVolumeInM += shipment.volume;
        truck->presentWeightInKg += shipment.weight;
        truck->location = shipment.destination;
    }
}
