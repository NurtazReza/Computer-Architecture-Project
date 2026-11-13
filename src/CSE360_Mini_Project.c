#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

// Color codes for better visibility
#define RED_TEXT 12
#define GREEN_TEXT 10
#define YELLOW_TEXT 14
#define WHITE_TEXT 15
#define CYAN_TEXT 11

// Structure to hold road information
typedef struct {
    char name[10];
    int vehicles;
    int direction;  // 1=North, 2=South, 3=East, 4=West
    int greenTime;
} Road;

// Function to set console text color
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Countdown timer with 1-second delay
void countdown(int sec) {
    int i;
    for(i = sec; i >= 1; i--) {
        printf("%2d ", i);
        fflush(stdout);
        Sleep(1000);  // Real 1-second delay
    }
    printf("\n");
}

// Display traffic signal status
void displaySignalStatus(int road) {
    printf("\n");
    setColor(CYAN_TEXT);
    printf("  ----- TRAFFIC SIGNAL STATUS -----\n\n");
    setColor(WHITE_TEXT);

    switch(road) {
        case 1:
            printf("  North : "); setColor(GREEN_TEXT); printf("GREEN\n"); setColor(WHITE_TEXT);
            printf("  South : "); setColor(RED_TEXT); printf("RED\n"); setColor(WHITE_TEXT);
            printf("  East  : "); setColor(RED_TEXT); printf("RED\n"); setColor(WHITE_TEXT);
            printf("  West  : "); setColor(RED_TEXT); printf("RED\n"); setColor(WHITE_TEXT);
            break;
        case 2:
            printf("  North : "); setColor(RED_TEXT); printf("RED\n"); setColor(WHITE_TEXT);
            printf("  South : "); setColor(GREEN_TEXT); printf("GREEN\n"); setColor(WHITE_TEXT);
            printf("  East  : "); setColor(RED_TEXT); printf("RED\n"); setColor(WHITE_TEXT);
            printf("  West  : "); setColor(RED_TEXT); printf("RED\n"); setColor(WHITE_TEXT);
            break;
        case 3:
            printf("  North : "); setColor(RED_TEXT); printf("RED\n"); setColor(WHITE_TEXT);
            printf("  South : "); setColor(RED_TEXT); printf("RED\n"); setColor(WHITE_TEXT);
            printf("  East  : "); setColor(GREEN_TEXT); printf("GREEN\n"); setColor(WHITE_TEXT);
            printf("  West  : "); setColor(RED_TEXT); printf("RED\n"); setColor(WHITE_TEXT);
            break;
        case 4:
            printf("  North : "); setColor(RED_TEXT); printf("RED\n"); setColor(WHITE_TEXT);
            printf("  South : "); setColor(RED_TEXT); printf("RED\n"); setColor(WHITE_TEXT);
            printf("  East  : "); setColor(RED_TEXT); printf("RED\n"); setColor(WHITE_TEXT);
            printf("  West  : "); setColor(GREEN_TEXT); printf("GREEN\n"); setColor(WHITE_TEXT);
            break;
    }
    setColor(WHITE_TEXT);
}

// Calculate adaptive green time based on traffic density
int calculateGreenTime(int vehicles) {
    // Adaptive timing based on vehicle count
    if(vehicles <= 5)
        return 5;   // Light traffic
    else if(vehicles <= 15)
        return 10;  // Medium traffic
    else
        return 15;  // Heavy traffic
}

// Calculate adaptive green time for emergency vehicles
int calculateEmergencyGreenTime(int emergencyCount) {
    // Adaptive timing based on number of emergency vehicles
    if(emergencyCount == 1)
        return 8;   // Single emergency vehicle
    else if(emergencyCount <= 3)
        return 12;  // 2-3 emergency vehicles
    else
        return 15;  // 4+ emergency vehicles (major incident)
}

// Get valid integer input with validation
int getValidInput(int min, int max, char* prompt) {
    int input;
    int valid = 0;

    while(!valid) {
        printf("%s", prompt);
        if(scanf("%d", &input) != 1) {
            // Clear input buffer
            while(getchar() != '\n');
            printf("\n  Error: Please enter a valid number!\n");
        } else if(input < min || input > max) {
            printf("\n  Error: Please enter a number between %d and %d!\n", min, max);
        } else {
            valid = 1;
        }
    }

    return input;
}

// Get valid yes/no input (0 or 1)
int getYesNoInput(char* prompt) {
    int input;
    int valid = 0;

    while(!valid) {
        printf("%s", prompt);
        printf("  1 = Yes | 0 = No\n");
        printf("  Enter: ");

        if(scanf("%d", &input) != 1) {
            // Clear input buffer
            while(getchar() != '\n');
            printf("\n  Error: Please enter 0 or 1!\n");
        } else if(input != 0 && input != 1) {
            printf("\n  Error: Please enter 0 (No) or 1 (Yes) only!\n");
        } else {
            valid = 1;
        }
    }

    return input;
}

// Get valid vehicle count (non-negative)
int getVehicleCount(char* direction) {
    int count;
    int valid = 0;

    while(!valid) {
        printf("  %s: ", direction);

        if(scanf("%d", &count) != 1) {
            // Clear input buffer
            while(getchar() != '\n');
            printf("\n  Error: Please enter a valid number!\n");
        } else if(count < 0) {
            printf("\n  Error: Vehicle no. cannot be negative!\n");
        } else {
            valid = 1;
        }
    }

    return count;
}

// Process traffic signal cycle for a specific road
void processTrafficCycle(int road, int greenTime, char* roadName, int vehicles) {
    displaySignalStatus(road);

    printf("\n  Direction: %s | Vehicles: %d | Green Time: %d sec\n", roadName, vehicles, greenTime);

    setColor(GREEN_TEXT);
    printf("\n   %s: GREEN Signal Active\n", roadName);
    printf("  Green Timer: ");
    countdown(greenTime);
    setColor(WHITE_TEXT);

    setColor(YELLOW_TEXT);
    printf("\n   %s: YELLOW Signal Active\n", roadName);
    printf("  Yellow Timer: ");
    countdown(3);
    setColor(WHITE_TEXT);

    setColor(RED_TEXT);
    printf("\n   %s: RED Signal Active\n", roadName);
    setColor(WHITE_TEXT);
    printf("  Vehicles cleared from %s direction.\n", roadName);
    Sleep(1000);
}

// Handle single emergency direction
void processSingleEmergency(int direction, int emergencyCount, char* dirName) {
    int emergencyGreenTime = calculateEmergencyGreenTime(emergencyCount);

    setColor(CYAN_TEXT);
    printf("\n  Emergency Details:\n\n");
    setColor(WHITE_TEXT);
    printf("  Direction          : %s\n", dirName);
    printf("  Emergency Vehicles : %d\n", emergencyCount);
    printf("  Adaptive Green Time: %d seconds\n", emergencyGreenTime);

    if(emergencyCount == 1) {
        printf("\n  Priority Level     : Standard (Single Vehicle)\n");
    } else if(emergencyCount <= 3) {
        printf("\n  Priority Level     : High (Multiple Vehicles)\n");
    } else {
        printf("\n  Priority Level     : CRITICAL (Major Incident)\n");
    }

    Sleep(1500);

    displaySignalStatus(direction);

    printf("\n  EMERGENCY LANE: %s\n", dirName);
    setColor(GREEN_TEXT);
    printf("  Emergency GREEN Signal Active\n");
    printf("  Timer: ");
    countdown(emergencyGreenTime);
    setColor(WHITE_TEXT);

    setColor(YELLOW_TEXT);
    printf("\n  Yellow Signal:\n");
    printf("  Timer: ");
    countdown(3);
    setColor(WHITE_TEXT);

    printf("\n  %d Emergency Vehicle(s) Passed Successfully on %s!\n", emergencyCount, dirName);
    Sleep(1000);
}

// Handle emergency vehicles (can be multiple directions)
int handleEmergency(int* totalEmergencyVehicles) {
    int numEmergencyDirections;
    int emergencyCount;
    int direction;
    int cycleEmergencyCount = 0;
    int usedDirections[4] = {0}; // Track which directions already have emergency

    setColor(CYAN_TEXT);
    printf("\n  *** EMERGENCY VEHICLE DETECTED ***\n");

    setColor(WHITE_TEXT);
    printf("\n  How many directions have emergency vehicles?\n");
    numEmergencyDirections = getValidInput(1, 4, "  Enter (1-4): ");

    char* dirName[] = {"", "NORTH", "SOUTH", "EAST", "WEST"};

    setColor(CYAN_TEXT);
    printf("\n  =====================================\n");
    printf("     EMERGENCY LANE ACTIVATED!\n");
    printf("  =====================================\n");
    setColor(WHITE_TEXT);

    // Process each emergency direction
    for(int i = 0; i < numEmergencyDirections; i++) {
        printf("   Emergency Direction %d/%d\n", i+1, numEmergencyDirections);

        // Get valid direction that hasn't been used
        int validDirection = 0;
        while(!validDirection) {
            printf("\n  Select Emergency Vehicle Direction:\n");
            printf("  1. North\n");
            printf("  2. South\n");
            printf("  3. East\n");
            printf("  4. West\n");

            direction = getValidInput(1, 4, "  Enter Choice: ");

            if(usedDirections[direction - 1]) {
                printf("\n  Error: %s already has emergency vehicles! Please select a different direction.\n", dirName[direction]);
            } else {
                usedDirections[direction - 1] = 1;
                validDirection = 1;
            }
        }

        printf("\n  Enter Number of Emergency Vehicles on %s\n", dirName[direction]);
        emergencyCount = getValidInput(1, 100, "  Enter: ");

        cycleEmergencyCount += emergencyCount;

        printf("\n  Clearing EMERGENCY LANE for %s direction...\n", dirName[direction]);

        processSingleEmergency(direction, emergencyCount, dirName[direction]);
    }

    // Summary
    printf("   Emergency Processing Complete!\n");
    printf("  Total Emergency Directions: %d\n", numEmergencyDirections);
    printf("  Total Emergency Vehicles  : %d\n", cycleEmergencyCount);
    Sleep(2000);

    *totalEmergencyVehicles += cycleEmergencyCount;
    return cycleEmergencyCount;
}

// Handle pedestrian crossing
void handlePedestrian() {
    setColor(CYAN_TEXT);
    printf("\n  =====================================\n");
    printf("     PEDESTRIAN CROSSING ACTIVATED\n");
    printf("  =====================================\n");
    setColor(WHITE_TEXT);

    printf("\n  All Vehicle Signals: ");
    setColor(RED_TEXT);
    printf("RED\n");
    setColor(WHITE_TEXT);

    printf("  Pedestrian Signal  : ");
    setColor(GREEN_TEXT);
    printf("GREEN\n");

    printf("\n  Pedestrian Crossing Timer: ");
    countdown(7);
    setColor(WHITE_TEXT);

    printf("\n  Pedestrian Crossing Completed\n");
    Sleep(1000);
}

// Display traffic statistics
void displayStatistics(int north, int south, int east, int west, int cycleEmergency, int totalVehicles, int totalEmergency, int cycleCount) {
    setColor(CYAN_TEXT);
    printf("\n  =====================================\n");
    printf("        TRAFFIC STATISTICS\n");
    printf("  =====================================\n");

    printf("\n  Current Cycle Data:\n\n");
    setColor(WHITE_TEXT);
    printf("  North Direction    : %d vehicles\n", north);
    printf("  South Direction    : %d vehicles\n", south);
    printf("  East Direction     : %d vehicles\n", east);
    printf("  West Direction     : %d vehicles\n", west);
    printf("\n  Normal Vehicles    : %d\n\n", north + south + east + west);

    if(cycleEmergency > 0) {
        printf("  Emergency Vehicles : %d\n", cycleEmergency);
    } else {
        printf("  Emergency Vehicles : 0\n");
    }

    printf("\n  This Cycle Total   : %d vehicles\n",
           north + south + east + west + cycleEmergency);

    setColor(CYAN_TEXT);
    printf("\n  Cumulative Statistics:\n\n");
    setColor(WHITE_TEXT);
    printf("  Total Normal Vehicles   : %d\n", totalVehicles);

    if(totalEmergency > 0) {
        printf("  Total Emergency Vehicles: %d\n", totalEmergency);
    } else {
        printf("  Total Emergency Vehicles: 0\n");
    }

    printf("\n  Grand Total Vehicles    : %d\n", totalVehicles + totalEmergency);
    printf("  Total Cycles Completed  : %d\n", cycleCount);
}

// Main menu with validation
int displayMenu() {
    int choice;
    setColor(CYAN_TEXT);
    printf("\n  =====================================\n");
    printf("          MAIN MENU\n");
    printf("  =====================================\n");
    setColor(WHITE_TEXT);
    printf("  1. Start New Traffic Cycle\n");
    printf("  2. Exit System\n");
    setColor(CYAN_TEXT);
    printf("  =====================================\n");
    setColor(WHITE_TEXT);

    choice = getValidInput(1, 2, "  Enter Choice: ");
    return choice;
}

// Comparison function for sorting roads by vehicle density (descending order)
int compareRoads(const void* a, const void* b) {
    Road* roadA = (Road*)a;
    Road* roadB = (Road*)b;
    return roadB->vehicles - roadA->vehicles;  // Descending order (highest first)
}

// Run complete traffic cycle based on priority (highest density first)
void runPriorityBasedTrafficCycle(Road roads[]) {
    // Sort roads by vehicle density (highest to lowest)
    qsort(roads, 4, sizeof(Road), compareRoads);

    // Display priority order
    printf("\n  Traffic Priority Order:\n");

    for(int i = 0; i < 4; i++) {
        printf("  %d. %s - %d vehicles (Green: %d sec)\n",
               i+1, roads[i].name, roads[i].vehicles, roads[i].greenTime);
    }
    printf("\n");
    Sleep(2000);

    // Process each road in priority order
    for(int i = 0; i < 4; i++) {
        printf("\n  [PRIORITY %d/4] Processing %s Direction\n", i+1, roads[i].name);
        processTrafficCycle(roads[i].direction, roads[i].greenTime, roads[i].name, roads[i].vehicles);

        Sleep(1000);
    }

    Sleep(1500);
}

int main() {
    int north, south, east, west;
    int pedestrian, emergency;
    int choice;
    int totalVehicles = 0;
    int totalEmergencyVehicles = 0;
    int cycleCount = 0;

    do {
        system("cls");

        choice = displayMenu();

        if(choice == 2) {
            break;
        }

        // Get vehicle counts - Manual Input with validation
        setColor(WHITE_TEXT);
        printf("\n\n  Enter Vehicle No. for Each Direction:\n\n");

        north = getVehicleCount("North");
        south = getVehicleCount("South");
        east = getVehicleCount("East ");
        west = getVehicleCount("West ");

        totalVehicles += north + south + east + west;
        cycleCount++;

        // Initialize road data for this cycle with adaptive timing
        Road roads[4];

        strcpy(roads[0].name, "NORTH");
        roads[0].vehicles = north;
        roads[0].direction = 1;
        roads[0].greenTime = calculateGreenTime(north);

        strcpy(roads[1].name, "SOUTH");
        roads[1].vehicles = south;
        roads[1].direction = 2;
        roads[1].greenTime = calculateGreenTime(south);

        strcpy(roads[2].name, "EAST");
        roads[2].vehicles = east;
        roads[2].direction = 3;
        roads[2].greenTime = calculateGreenTime(east);

        strcpy(roads[3].name, "WEST");
        roads[3].vehicles = west;
        roads[3].direction = 4;
        roads[3].greenTime = calculateGreenTime(west);

        // Check for emergency with validation
        printf("\n\n  Emergency Vehicle Present?\n");
        emergency = getYesNoInput("");

        int cycleEmergencyVehicles = 0;

        // PHASE 1: Handle Emergency Vehicles (if present) - Can be multiple directions
        if(emergency == 1) {
            cycleEmergencyVehicles = handleEmergency(&totalEmergencyVehicles);
        }

        // PHASE 2: Normal Traffic Cycle (All 4 Directions) - Priority Based
        setColor(CYAN_TEXT);
        printf("\n  =====================================\n");
        printf("   NORMAL TRAFFIC PROCESSING\n");
        printf("  =====================================\n");
        setColor(WHITE_TEXT);

        // Run priority-based cycle for ALL 4 directions
        runPriorityBasedTrafficCycle(roads);

        // Check for pedestrian crossing after complete cycle with validation
        printf("\n\n  Pedestrian Crossing Request?\n");
        pedestrian = getYesNoInput("");

        if(pedestrian == 1) {
            handlePedestrian();
        }

        // Display statistics
        displayStatistics(north, south, east, west, cycleEmergencyVehicles,
                         totalVehicles, totalEmergencyVehicles, cycleCount);
        printf("\n\n  =====================================\n");
        printf("  Press any key to continue...");
        getch();

    } while(choice != 2);

    // Exit screen
    system("cls");
    setColor(CYAN_TEXT);
    printf("\n");
    printf("  =====================================\n");
    printf("     TRAFFIC CONTROL SYSTEM CLOSED\n");
    printf("  =====================================\n\n");
    printf("  Final Statistics:\n\n");
    setColor(WHITE_TEXT);
    printf("  Total Normal Vehicles   : %d\n", totalVehicles);
    printf("  Total Emergency Vehicles: %d\n", totalEmergencyVehicles);
    printf("\n\n  Total Vehicles          : %d\n", totalVehicles + totalEmergencyVehicles);
    printf("  Total Cycles Completed  : %d\n\n", cycleCount);

    return 0;
}

