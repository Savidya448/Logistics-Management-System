#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define VEHICLE_COUNT 3
#define MAX_NAME_LENGTH 50
#define FUEL_PRICE 310.0

typedef struct {
    char name[MAX_NAME_LENGTH];
} City;

typedef struct {
    char name[10];
    int capacity;
    float ratePerKm;
    float speed;
    float efficiency;
} Vehicle;

typedef struct {
    int src, dest;
    float weight;
    int vehicleType;
    float distance;
    float baseCost, fuelUsed, fuelCost, totalCost, profit, customerCharge, time;
} Delivery;
