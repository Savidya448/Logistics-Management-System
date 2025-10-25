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
void printDistanceTable() {
    printf("     ");
    for (int i = 0; i < cityCount; i++)
        printf("%10s", cities[i].name);
    printf("\n");

    for (int i = 0; i < cityCount; i++) {
        printf("%-5s", cities[i].name);
        for (int j = 0; j < cityCount; j++) {
            printf("%10d", distances[i][j]);
        }
        printf("\n");
    }
}
void handleDelivery() {
    listCities();
    int src, dest;
    float weight;
    int vehicleType;

    printf("Enter source index: ");
    scanf("%d", &src);
    printf("Enter destination index: ");
    scanf("%d", &dest);

    if (src == dest) {
        printf("Source and destination cannot be same!\n");
        return;
    }

    int dist = distances[src][dest];
    if (dist == 0) {
        printf("No distance recorded between these cities.\n");
        return;
    }

    printf("Enter weight (kg): ");
    scanf("%f", &weight);
printf("Select vehicle:\n");
    for (int i = 0; i < VEHICLE_COUNT; i++) {
        printf("%d. %s (Capacity: %d kg)\n", i + 1, vehicles[i].name, vehicles[i].capacity);
    }
    scanf("%d", &vehicleType);
    vehicleType--;

    if (vehicleType < 0 || vehicleType >= VEHICLE_COUNT) {
        printf("Invalid vehicle type.\n");
        return;
    }

    if (weight > vehicles[vehicleType].capacity) {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }

    Vehicle v = vehicles[vehicleType];
    float baseCost = dist * v.ratePerKm * (1 + weight / 10000.0);
    float fuelUsed = dist / v.efficiency;
    float fuelCost = fuelUsed * FUEL_PRICE;
    float totalCost = baseCost + fuelCost;
    float profit = baseCost * 0.25;
    float charge = totalCost + profit;
    float time = dist / v.speed;

    Delivery d = {src, dest, weight, vehicleType, dist,
                  baseCost, fuelUsed, fuelCost, totalCost,
                  profit, charge, time};
    deliveries[deliveryCount++] = d;
 printf("\n===== DELIVERY ESTIMATE =====\n");
    printf("From: %s\n", cities[src].name);
    printf("To: %s\n", cities[dest].name);
    printf("Vehicle: %s\n", v.name);
    printf("Distance: %.2f km\n", (float)dist);
    printf("Base Cost: %.2f LKR\n", baseCost);
    printf("Fuel Used: %.2f L\n", fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", fuelCost);
    printf("Operational Cost: %.2f LKR\n", totalCost);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", charge);
    printf("Estimated Time: %.2f hrs\n", time);
}

void showReports() {
    if (deliveryCount == 0) {
        printf("No deliveries made yet.\n");
        return;
    }

    float totalRevenue = 0, totalProfit = 0, totalTime = 0, totalDistance = 0;
    float shortest = 1e9, longest = 0;

    for (int i = 0; i < deliveryCount; i++) {
        totalRevenue += deliveries[i].customerCharge;
        totalProfit += deliveries[i].profit;
        totalTime += deliveries[i].time;
        totalDistance += deliveries[i].distance;

        if (deliveries[i].distance < shortest) shortest = deliveries[i].distance;
        if (deliveries[i].distance > longest) longest = deliveries[i].distance;
    }
printf("\n===== PERFORMANCE REPORT =====\n");
    printf("Total Deliveries: %d\n", deliveryCount);
    printf("Total Distance Covered: %.2f km\n", totalDistance);
    printf("Average Delivery Time: %.2f hours\n", totalTime / deliveryCount);
    printf("Total Revenue: %.2f LKR\n", totalRevenue);
    printf("Total Profit: %.2f LKR\n", totalProfit);
    printf("Longest Route: %.2f km\n", longest);
    printf("Shortest Route: %.2f km\n", shortest);
}
