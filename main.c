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
City cities[MAX_CITIES];
int cityCount = 0;

int distances[MAX_CITIES][MAX_CITIES];

Vehicle vehicles[VEHICLE_COUNT] = {
    {"Van", 1000, 30, 60, 12},
    {"Truck", 5000, 40, 50, 6},
    {"Lorry", 10000, 45, 40, 4}
};

Delivery deliveries[MAX_DELIVERIES];
int deliveryCount = 0;
void addCity();
void listCities();
void inputDistance();
void printDistanceTable();
void handleDelivery();
void showReports();

void addCity() {
    if (cityCount >= MAX_CITIES) {
        printf("City limit reached!\n");
        return;
    }
    printf("Enter city name: ");
    scanf("%s", cities[cityCount].name);
    cityCount++;
    printf("City added successfully!\n");
}
void listCities() {
    if (cityCount == 0) {
        printf("No cities added yet.\n");
        return;
    }
    for (int i = 0; i < cityCount; i++) {
        printf("%d. %s\n", i, cities[i].name);
    }
}
void inputDistance() {
    listCities();
    int src, dest;
    printf("Enter source city index: ");
    scanf("%d", &src);
    printf("Enter destination city index: ");
    scanf("%d", &dest);

    if (src == dest) {
        printf("Distance to itself is always 0.\n");
        return;
    }

    int d;
    printf("Enter distance in km: ");
    scanf("%d", &d);
    distances[src][dest] = d;
    distances[dest][src] = d; // symmetric
    printf("Distance updated!\n");
}
