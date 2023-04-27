/* iaed-23 - ist1102373 - project2 */

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>

# define MAX_INPUT_LENGTH 65535
# define FALSE 0
# define TRUE 1

/* Structures */
struct Stop {
    char *name;
    double latitude;
    double longitude;
    int nRoutes;
};

struct Route {
    char *name;
    char *startingPoint;
    char *arrivalPoint;
    int *idStops;
    int nRouteStops;
    float totalPrice;
    float totalDuration;
};

struct Connection {
    int idRoute;
    int idStartingPoint, idArrivalPoint;
    float price, duration;
};

/* Functions */
void addStop(struct Stop **StopMap, char *name, double latitude, double longitude, int *nStops);
void showStop(struct Stop **StopMap, char *name, int *nStops);
void listStops(struct Stop **StopMap, int *nStops);
void createConnection(struct Stop **StopMap, struct Route **RouteMap, struct Connection **ConnectionMap, int nStops, int nRoutes, int *nConnections, char* placeholderRouteName, char* placeholderStartingPoint, char* placeholderArrivalPoint, float placeholderPrice, float placeholderDuration);
void showIntersections(struct Stop **StopMap, struct Route **RouteMap, int nStops, int nRoutes);
int checkReverse(char s[]);
void addRoute(struct Route **RouteMap, char *name, int *nRoutes);
void showRoute(struct Stop **StopMap, struct Route **RouteMap, int idRoute, char *placeholderReverse);
void listRoutes(struct Route **RouteMap, int *nRoutes);
void removeRoute(struct Route **RouteMap, struct Stop **StopMap, struct Connection **ConnectionMap, char* name, int nStops, int* nRoutes, int* nConnections);
void removeStop(struct Stop **StopMap, struct Route **RouteMap, struct Connection **ConnectionMap, char* name, int* nStops, int nRoutes, int* nConnections);

/* Exception Handlers */
void NoMemoryException();
void IncorrectSortOptionException();
void StopAlreadyExistsException(char* placeholderStopName);
void NoSuchStopException(char* placeholderStopName);
void NoSuchLineException(char* placeholderRouteName);
void NegativeCostOrDurationException();
void ConnectionNotAvailableException();


int main() {

    /* Command and Input Information*/
    char command, input[MAX_INPUT_LENGTH];

    /* Stop Information */
    struct Stop *StopMap = NULL;

    char placeholderStopName[MAX_INPUT_LENGTH - 5];
    double placeholderLatitude;
    double placeholderLongitude;
    int nStops = 0;

    /* Route Information */
    struct Route *RouteMap = NULL;

    char placeholderRouteName[MAX_INPUT_LENGTH - 1];
    char placeholderStartingPoint[MAX_INPUT_LENGTH - 5];
    char placeholderArrivalPoint[MAX_INPUT_LENGTH - 5];
    float placeholderPrice;
    float placeholderDuration;
    char placeholderReverse[10];
    int nRoutes = 0;

    /* Connection Information */
    struct Connection *ConnectionMap = NULL;
    int nConnections = 0;

    /* Counter Information */
    int i;


    while (1) {

        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            break;
        }
        strtok(input, "\n");

        command = input[0];
        
        switch (command)
        {
            case 'q':

                /* Free the memory allocated */
                free(StopMap);
                free(RouteMap);
                free(ConnectionMap);

                return 0;
            
            case 'c':

                if (sscanf(input, " %c %s %s", &command, placeholderRouteName, placeholderReverse) == 3)
                {
                    /* Display the Route if it exists and has stops */
                    if(checkReverse(placeholderReverse))
                    {
                        for (i = 0; i < nRoutes; i++)
                        {
                            if (strcmp(placeholderRouteName, RouteMap[i].name) == 0)
                            {
                                if (RouteMap[i].nRouteStops > 0)
                                {
                                    showRoute(&StopMap, &RouteMap, i, placeholderReverse);
                                }

                                break;
                            }
                        }

                        if (i == nRoutes)
                        {
                            NoSuchLineException(placeholderRouteName);
                        }

                    } else
                    {
                        IncorrectSortOptionException();
                    }

                } else if (sscanf(input, " %c %s", &command, placeholderRouteName) == 2)
                {
                    /* Display the Route if it exists and has stops */
                    for (i = 0; i < nRoutes; i++)
                    {
                        if (strcmp(placeholderRouteName, RouteMap[i].name) == 0)
                        {
                            if (RouteMap[i].nRouteStops > 0)
                            {
                                showRoute(&StopMap, &RouteMap, i, placeholderReverse);
                            }

                            break;
                        }
                    }
                
                    if (i == nRoutes)
                    {
                        addRoute(&RouteMap, placeholderRouteName, &nRoutes);
                    }

                } else if (sscanf(input, " %c", &command) == 1)
                {
                    listRoutes(&RouteMap, &nRoutes);
                }
                
                

                break;

            case 'p':
                if (sscanf(input, " %c %s %lf %lf", &command, placeholderStopName, &placeholderLatitude, &placeholderLongitude) == 4) {

                    addStop(&StopMap, placeholderStopName, placeholderLatitude, placeholderLongitude, &nStops);

                } else if (sscanf(input, " %c \"%[^\"]\" %lf %lf", &command, placeholderStopName, &placeholderLatitude, &placeholderLongitude) == 4) {
                    
                    addStop(&StopMap, placeholderStopName, placeholderLatitude, placeholderLongitude, &nStops);

                } else if(sscanf(input, " %c %s", &command, placeholderStopName) == 2) {

                    showStop(&StopMap, placeholderStopName, &nStops);

                } else if(sscanf(input, " %c \"%[^\"]\"", &command, placeholderStopName) == 2) {

                    showStop(&StopMap, placeholderStopName, &nStops);

                } else if (sscanf(input, " %c", &command) == 1) {

                    listStops(&StopMap, &nStops);
                
                }

                break;

            case 'l':
                if (sscanf(input, " %c %s \"%[^\"]\" \"%[^\"]\" %f %f", &command, placeholderRouteName, 
                placeholderStartingPoint, placeholderArrivalPoint, &placeholderPrice, &placeholderDuration) == 6) {
                    /* User input: When both startingPoint and arrivalPoint don't have quotes */
                    createConnection(&StopMap, &RouteMap, &ConnectionMap, nStops, nRoutes, &nConnections, placeholderRouteName, placeholderStartingPoint, placeholderArrivalPoint, placeholderPrice, placeholderDuration);

                } else if (sscanf(input, " %c %s \"%[^\"]\" %s %f %f", &command, placeholderRouteName, 
                placeholderStartingPoint, placeholderArrivalPoint, &placeholderPrice, &placeholderDuration) == 6) {
                    /* User input: When startingPoint is inside quotes */
                    createConnection(&StopMap, &RouteMap, &ConnectionMap, nStops, nRoutes, &nConnections, placeholderRouteName, placeholderStartingPoint, placeholderArrivalPoint, placeholderPrice, placeholderDuration);

                } else if (sscanf(input, " %c %s %s \"%[^\"]\" %f %f", &command, placeholderRouteName, 
                placeholderStartingPoint, placeholderArrivalPoint, &placeholderPrice, &placeholderDuration) == 6) {
                    /* User input: When arrivalPoint is inside quotes */
                    createConnection(&StopMap, &RouteMap, &ConnectionMap, nStops, nRoutes, &nConnections, placeholderRouteName, placeholderStartingPoint, placeholderArrivalPoint, placeholderPrice, placeholderDuration);

                } else if (sscanf(input, " %c %s %s %s %f %f", &command, placeholderRouteName, 
                placeholderStartingPoint, placeholderArrivalPoint, &placeholderPrice, &placeholderDuration) == 6) {
                    /* User input: When both startingPoint and arrivalPoint are inside quotes */
                    createConnection(&StopMap, &RouteMap, &ConnectionMap, nStops, nRoutes, &nConnections, placeholderRouteName, placeholderStartingPoint, placeholderArrivalPoint, placeholderPrice, placeholderDuration);
                
                }
                
                break;

            case 'i':
                /* User input: i */

                showIntersections(&StopMap, &RouteMap, nStops, nRoutes);

                break;

            case 'r':
                /* User input: r Routename */

                if (sscanf(input, " %c %s", &command, placeholderRouteName) == 2)
                {
                    removeRoute(&RouteMap, &StopMap, &ConnectionMap, placeholderRouteName, nStops, &nRoutes, &nConnections);
                }

                break;
            
            case 'e':
              /* User input: e Stopname */

                if (sscanf(input, " %c %s", &command, placeholderStopName) == 2)
                {
                    removeStop(&StopMap, &RouteMap, &ConnectionMap, placeholderStopName, &nStops, nRoutes, &nConnections);
                }
                
                break;

            case 'a':
                /* User input: a */

                /* Free the memory allocated */
                free(StopMap);
                free(RouteMap);
                free(ConnectionMap);

                break;
            
            default:
                break;
        }  
    }
    return 0;
}

/* 
 * FUNCTION: addStop
 *
 * INPUT: The Stop Structure, a Stop Name, a Stop Latitude, a Stop Longitude, Number of existent Stops
 * 
 * OUTPUT: Creates a Stop, without printing anything
 */
void addStop(struct Stop **StopMap, char *name, double latitude, double longitude, int *nStops) {
    struct Stop *new_stop;
    int i;

    /* Check if the stop already exists */
    for (i = 0; i < *nStops; i++) {
        if (strcmp(name, (*StopMap)[i].name) == 0) {
            StopAlreadyExistsException(name);
            return;
        }
    }

    /* Allocate memory for the new stop */
    new_stop = (struct Stop*)malloc(sizeof(struct Stop));

    /* Check if memory allocation was successful */
    if (new_stop == NULL) {
        NoMemoryException();
        return;
    }

    new_stop->name = malloc(strlen(name) + 1);

    /* Check if memory allocation was successful */
    if (new_stop->name == NULL) {
        NoMemoryException();
        free(new_stop);
        return;
    }

    /* Copy the name into the new stop structure */
    strcpy(new_stop->name, name);

    /* Latitude and Longitude */
    new_stop->latitude = latitude;
    new_stop->longitude = longitude;
    new_stop->nRoutes = 0;

    /* Add the new stop to the list */
    (*nStops)++;
    *StopMap = (struct Stop*)realloc(*StopMap, (*nStops) * sizeof(struct Stop));

    /* Check if memory reallocation was successful */
    if (*StopMap == NULL) {
        NoMemoryException();
        free(new_stop->name);
        free(new_stop);
        return;
    }

    (*StopMap)[*nStops - 1] = *new_stop;

    /* Free the memory allocated for the temporary stop structure */
    free(new_stop);
}

/* 
 * FUNCTION: showStop
 *
 * INPUT: The Stop's Structure, a Stop Name, Number of existent Stops
 * 
 * OUTPUT: Prints the Stop's Coordinates
 */
void showStop(struct Stop **StopMap, char *name, int *nStops) {
    int i;

    /* Check if the stop already exists */
    for (i = 0; i < *nStops; i++) {
        if (strcmp(name, (*StopMap)[i].name) == 0) {
            printf("%16.12f %16.12f\n", (*StopMap)[i].latitude, (*StopMap)[i].longitude);
            break;
        }
    }

    if (i == *nStops)
    {
        NoSuchStopException(name);
    }
}

/* 
 * FUNCTION: listStops
 *
 * INPUT: The Stop's Structure, Number of existent Stops
 * 
 * OUTPUT: Prints all Stops
 */
void listStops(struct Stop **StopMap, int *nStops) {

    int i;

    for (i = 0; i < *nStops; i++) {

        printf("%s: %16.12f %16.12f %d\n", (*StopMap)[i].name, (*StopMap)[i].latitude, (*StopMap)[i].longitude, (*StopMap)[i].nRoutes);

    }

}

/* 
 * FUNCTION: addRoute
 *
 * INPUT: The Route Structure, a Route Name, Number of existent Routes
 * 
 * OUTPUT: Creates a Route, without printing anything 
 */
void addRoute(struct Route **RouteMap, char *name, int *nRoutes) {
    struct Route *new_route;
    
    /* Allocate memory for the new route */
    new_route = (struct Route*)malloc(sizeof(struct Route));

    /* memset(new_route, 0, sizeof(struct Route)); */

    /* Check if memory allocation was successful */
    if (new_route == NULL) {
        NoMemoryException();
        free(new_route);
        return;
    }

    new_route->name = (char*)malloc(MAX_INPUT_LENGTH);
    /* Check if memory allocation was successful */
    if (new_route->name == NULL) {
        NoMemoryException();
        free(new_route->name);
        free(new_route);
        return;
    }

    new_route->startingPoint = (char*)malloc(MAX_INPUT_LENGTH - 5);
    /* Check if memory allocation was successful */
    if (new_route->startingPoint == NULL) {
        NoMemoryException();
        free(new_route->startingPoint);
        free(new_route->name);
        free(new_route);
        return;
    }

    new_route->arrivalPoint = (char*)malloc(MAX_INPUT_LENGTH - 5);
    /* Check if memory allocation was successful */
    if (new_route->arrivalPoint == NULL) {
        NoMemoryException();
        free(new_route->arrivalPoint);
        free(new_route->startingPoint);
        free(new_route->name);
        free(new_route);
        return;
    }

    new_route->idStops = (int*)malloc(sizeof(int));
    if (new_route->idStops == NULL) {
        NoMemoryException();
        free(new_route->idStops);
        free(new_route->arrivalPoint);
        free(new_route->startingPoint);
        free(new_route->name);
        free(new_route);
        return;
    }

    /* Copy the data into the new route structure */
    strcpy(new_route->name, name);
    strcpy(new_route->startingPoint, "\0");
    strcpy(new_route->arrivalPoint, "\0");
    new_route->nRouteStops = 0;
    new_route->totalPrice = 0;
    new_route->totalDuration = 0;

    /* Add the new route to the list */
    (*nRoutes)++;
    *RouteMap = (struct Route*)realloc(*RouteMap, (*nRoutes) * sizeof(struct Route));

    /* Check if memory reallocation was successful */
    if (*RouteMap == NULL) {
        NoMemoryException();
        free(new_route->name);
        free(new_route->startingPoint);
        free(new_route->arrivalPoint);
        free(new_route->idStops);
        free(new_route);
        return;
    }

    (*RouteMap)[*nRoutes - 1] = *new_route;

    /* Free the memory allocated for the temporary stop structure */
    free(new_route);    
}

/* 
 * FUNCTION: showRoute
 *
 * INPUT: The Stop's Structure, the Route's Structure, a Route's ID, a string that can represent a Reverse method
 * 
 * OUTPUT: Prints the Route's Stops, and if the Reverse String is right it prints the Route's Stops in reverse order.
 */
void showRoute(struct Stop **StopMap, struct Route **RouteMap, int idRoute, char *placeholderReverse) {
    int i;

    if (checkReverse(placeholderReverse) == 1)
    {
        for (i = ((*RouteMap)[idRoute].nRouteStops) - 1; i > 0; i--)
        {
            printf("%s, ", (*StopMap)[(*RouteMap)[idRoute].idStops[i]].name);
        }

        printf("%s\n", (*StopMap)[(*RouteMap)[idRoute].idStops[i]].name);
        
    } else {

        for (i = 0; i < ((*RouteMap)[idRoute].nRouteStops) - 1; i++)
        {
            printf("%s, ", (*StopMap)[(*RouteMap)[idRoute].idStops[i]].name);
        }

        printf("%s\n", (*StopMap)[(*RouteMap)[idRoute].idStops[i]].name);
    }
    
    placeholderReverse[0] = '\0';
}

/* 
 * FUNCTION: listRoutes
 *
 * INPUT: The Route's Structure, Number of existent Route
 * 
 * OUTPUT: Prints all Routes
 */
void listRoutes(struct Route **RouteMap, int *nRoutes) {
    
    int i;

    for (i = 0; i < (*nRoutes); i++)
    {
        if ((*RouteMap)[i].startingPoint[0] == '\0' || (*RouteMap)[i].arrivalPoint[0] == '\0')
        {
            /* If the Stop doesn't have stops */
            printf("%s %d ", (*RouteMap)[i].name, (*RouteMap)[i].nRouteStops);
            printf("%2.2f %2.2f\n", (*RouteMap)[i].totalPrice, (*RouteMap)[i].totalDuration);

        } else {
            /* If it has */
            printf("%s %s %s ", (*RouteMap)[i].name, (*RouteMap)[i].startingPoint, (*RouteMap)[i].arrivalPoint);
            printf("%d %2.2f %2.2f\n", (*RouteMap)[i].nRouteStops, (*RouteMap)[i].totalPrice, (*RouteMap)[i].totalDuration);

        } 
    }
}

/* 
 * FUNCTION: createConnection
 *
 * INPUT: The Stop's Structure, the Route's Structure, the Connection's Structure, Number of existent Stops, 
 * Number of existent Routes, Number of existent Connections, a Route's Name, a Route's Starting Point, 
 * a Route's Arrival Point, the Connection's Price and the Connection's Duration
 * 
 * OUTPUT: Creates a connection without printing anything
 */
void createConnection(struct Stop **StopMap, struct Route **RouteMap, struct Connection **ConnectionMap,
int nStops, int nRoutes, int *nConnections, char* placeholderRouteName, char* placeholderStartingPoint,
char* placeholderArrivalPoint, float placeholderPrice, float placeholderDuration)
{
    struct Connection *new_connection;

    int i, j;
    int foundStartingPoint = 0, foundArrivalPoint = 0;
    int startingPointIndex = -1, arrivalPointIndex = -1;

    /* Checks if both stops exist */
    for (i = 0; i < nStops; i++)
    {
        if (strcmp(placeholderStartingPoint, (*StopMap)[i].name) == 0)
        {
            foundStartingPoint = 1;
            startingPointIndex = i;
        }
        
        if (strcmp(placeholderArrivalPoint, (*StopMap)[i].name) == 0)
        {
            foundArrivalPoint = 1;
            arrivalPointIndex = i;
        }
    }
    
    /* We go through the list of Routes to find the one that user is trying to create a Connection on */
    for (i = 0; i < nRoutes; i++)
    {
    /* Here we go through some Error Handling before actually creating the connection */
        if (foundStartingPoint == 1)
        {
            if (foundArrivalPoint == 1)
            {
                if ((strcmp(placeholderRouteName, (*RouteMap)[i].name)) == 0)
                {
                    if ((*RouteMap)[i].startingPoint[0] == '\0' || 
                    strcmp(placeholderStartingPoint, (*RouteMap)[i].arrivalPoint) == 0 || 
                    strcmp(placeholderArrivalPoint, (*RouteMap)[i].startingPoint) == 0)
                    {
                        if (placeholderPrice >= 0 && placeholderDuration >= 0)
                        {
                            if ((*RouteMap)[i].startingPoint[0] == '\0')
                            {
                                /* When the Route doesn't have neither a Starting or Arrival Point yet */
                                strcpy((*RouteMap)[i].startingPoint, placeholderStartingPoint);
                                strcpy((*RouteMap)[i].arrivalPoint, placeholderArrivalPoint);
                                (*RouteMap)[i].totalPrice += placeholderPrice;
                                (*RouteMap)[i].totalDuration += placeholderDuration;

                                (*RouteMap)[i].idStops[0] = startingPointIndex;

                                (*RouteMap)[i].idStops = (int*)realloc((*RouteMap)[i].idStops, 2 * sizeof(int));
                                /* Check if memory reallocation was successful */
                                if ((*RouteMap)[i].idStops == NULL) {
                                    NoMemoryException();
                                    return;
                                }
                                (*RouteMap)[i].idStops[1] = arrivalPointIndex;

                                (*StopMap)[startingPointIndex].nRoutes++;
                                (*StopMap)[arrivalPointIndex].nRoutes++;
                                
                                (*RouteMap)[i].nRouteStops = 2;

                                new_connection = (struct Connection*)malloc(sizeof(struct Connection));
                                if (new_connection == NULL)
                                {
                                    NoMemoryException();
                                    return;
                                }

                                new_connection->idRoute = i;
                                new_connection->idStartingPoint = startingPointIndex;
                                new_connection->idArrivalPoint = arrivalPointIndex;
                                new_connection->price = placeholderPrice;
                                new_connection->duration = placeholderDuration;

                                (*nConnections)++;

                                *ConnectionMap = (struct Connection*)realloc(*ConnectionMap, (*nConnections) * sizeof(struct Connection));

                                /* Check if memory reallocation was successful */
                                if (*ConnectionMap == NULL) {
                                    NoMemoryException();
                                    free(*ConnectionMap);
                                    return;
                                }

                                (*ConnectionMap)[*nConnections - 1] = *new_connection;

                                break;

                            } else if (strcmp(placeholderStartingPoint, (*RouteMap)[i].arrivalPoint) == 0)
                            {
                                /* When the user is trying to create a new Connection and the Arrival Point is the same has the Route's Starting Point, a new Arrival Point is set */
                                strcpy((*RouteMap)[i].arrivalPoint, placeholderArrivalPoint);
                                (*RouteMap)[i].totalPrice += placeholderPrice;
                                (*RouteMap)[i].totalDuration += placeholderDuration;

                                /* Here we check if the Route's a circle */
                                if (strcmp(placeholderArrivalPoint, (*RouteMap)[i].startingPoint) != 0)
                                {
                                    (*StopMap)[arrivalPointIndex].nRoutes++;
                                }

                                (*RouteMap)[i].idStops = (int*)realloc((*RouteMap)[i].idStops, ((*RouteMap)[i].nRouteStops + 1) * sizeof(int));
                                /* Check if memory reallocation was successful */
                                if ((*RouteMap)[i].idStops == NULL) {
                                    NoMemoryException();
                                    return;
                                }

                                (*RouteMap)[i].idStops[(*RouteMap)[i].nRouteStops] = arrivalPointIndex;
                                (*RouteMap)[i].nRouteStops++;

                                new_connection = (struct Connection*)malloc(sizeof(struct Connection));
                                if (new_connection == NULL)
                                {
                                    NoMemoryException();
                                    return;
                                }

                                new_connection->idRoute = i;
                                new_connection->idStartingPoint = startingPointIndex;
                                new_connection->idArrivalPoint = arrivalPointIndex;
                                new_connection->price = placeholderPrice;
                                new_connection->duration = placeholderDuration;

                                (*nConnections)++;

                                *ConnectionMap = (struct Connection*)realloc(*ConnectionMap, (*nConnections) * sizeof(struct Connection));

                                /* Check if memory reallocation was successful */
                                if (*ConnectionMap == NULL) {
                                    NoMemoryException();
                                    return;
                                }

                                (*ConnectionMap)[*nConnections - 1] = *new_connection;

                                break;

                            } else if (strcmp(placeholderArrivalPoint, (*RouteMap)[i].startingPoint) == 0)
                            {
                                /* When the user is trying to create a new Connection and the Starting Point is the same has the Route's Arrival Point, a new Starting Point is set */
                                strcpy((*RouteMap)[i].startingPoint, placeholderStartingPoint);
                                (*RouteMap)[i].totalPrice += placeholderPrice;
                                (*RouteMap)[i].totalDuration += placeholderDuration;

                                (*RouteMap)[i].idStops = (int*)realloc((*RouteMap)[i].idStops, ((*RouteMap)[i].nRouteStops + 1) * sizeof(int));
                                /* Check if memory reallocation was successful */
                                if ((*RouteMap)[i].idStops == NULL) {
                                    NoMemoryException();
                                    return;
                                }

                                for (j = ((*RouteMap)[i].nRouteStops)-1; j >= 0; j--)
                                {
                                    (*RouteMap)[i].idStops[j+1] = (*RouteMap)[i].idStops[j];
                                }
                                
                                (*RouteMap)[i].idStops[0] = startingPointIndex;

                                (*StopMap)[startingPointIndex].nRoutes++;
                                (*RouteMap)[i].nRouteStops++;

                                new_connection = (struct Connection*)malloc(sizeof(struct Connection));
                                if (new_connection == NULL)
                                {
                                    NoMemoryException();
                                    return;
                                }

                                new_connection->idRoute = i;
                                new_connection->idStartingPoint = startingPointIndex;
                                new_connection->idArrivalPoint = arrivalPointIndex;
                                new_connection->price = placeholderPrice;
                                new_connection->duration = placeholderDuration;

                                (*nConnections)++;

                                *ConnectionMap = (struct Connection*)realloc(*ConnectionMap, (*nConnections) * sizeof(struct Connection));

                                /* Check if memory reallocation was successful */
                                if (*ConnectionMap == NULL) {
                                    NoMemoryException();
                                    return;
                                }

                                (*ConnectionMap)[*nConnections - 1] = *new_connection;

                                break;

                            }

                        } else {
                            NegativeCostOrDurationException();
                            break;
                        }

                    } else {
                        ConnectionNotAvailableException();
                        break;
                    }
                }

            } else {
                NoSuchStopException(placeholderArrivalPoint);
                break;
            }

        } else {
            NoSuchStopException(placeholderStartingPoint);
            break;
        }
    }

    if (i == nRoutes) {
        NoSuchLineException(placeholderRouteName);
    }

}

/* 
 * FUNCTION: showIntersections
 *
 * INPUT: The Stop's Structure, The Route's Structure, Number of existent Stops, Number of existent Routes
 * 
 * OUTPUT: Prints every Route with 2 or more Route's associated
 */
void showIntersections(struct Stop **StopMap, struct Route **RouteMap, int nStops, int nRoutes) {
    int i, j, k, houveTroca = TRUE;

    int* routesList = NULL;
    int nElements = 0;
    int limitElements = 10;

    for (i = 0; i < nStops; i++)
    {
        if ((*StopMap)[i].nRoutes > 1)
        {
            routesList = (int*)malloc(limitElements * sizeof(int));
            if (routesList == NULL) {
                NoMemoryException();
                free(routesList);
                return;
            }

            for (j = 0; j < nRoutes; j++)
            {
                for (k = 0; k < (*RouteMap)[j].nRouteStops; k++)
                {
                    if ((*RouteMap)[j].idStops[k] == i)
                    {
                        routesList[nElements] = j;
                        nElements++;

                        if (nElements == limitElements)
                        {
                            limitElements *= 2;
                            routesList = (int*)realloc(routesList, limitElements * sizeof(int));

                            if (routesList == NULL) {
                                NoMemoryException();
                                free(routesList);
                                return;
                            }
                        }

                        break;
                        
                    }
                }
            }
            printf("%s %d: ", (*StopMap)[i].name, (*StopMap)[i].nRoutes);

            /* Bubble Sort */

            for (j = 0; houveTroca && j < nElements-1; j++) {
                houveTroca = FALSE;
                for (k = 0; k < nElements-1-j; k++) {
                    if (strcmp((*RouteMap)[routesList[k]].name, (*RouteMap)[routesList[k+1]].name) > 0) {
                        int aux = routesList[k];
                        routesList[k] = routesList[k+1];
                        routesList[k+1] = aux;
                        houveTroca = TRUE;
                    }
                }
            }

            for (j = 0; j < nElements - 1; j++)
            {
                printf("%s ", (*RouteMap)[routesList[j]].name);
            }
            
            printf("%s\n", (*RouteMap)[routesList[j]].name);

            /* Wipe the array and nElements Counter */
            free(routesList);
            nElements = 0;
        }
    }
}

/* 
 * FUNCTION: checkReverse
 *
 * INPUT: A string of characters
 * 
 * OUTPUT: Prints every Route with 2 or more Route's associated
 */
int checkReverse(char s[]) {
    char inv[] = "inverso";
    int size = strlen(s), i;

    if (size < 3 || size > 7)
        return FALSE;
    for (i = 0; i < size; i++)
        if (inv[i] != s[i])
            return FALSE;
    return TRUE;
}

/* 
 * FUNCTION: removeRoute
 *
 * INPUT: The Route's Structure, the Stop's Structure, the Connection's Structure, a Route's Name, Number of existent Stops, 
 * Number of existent Routes, Number of existent Connections
 * 
 * OUTPUT: Removes a Route
 */
void removeRoute(struct Route **RouteMap, struct Stop **StopMap, struct Connection **ConnectionMap, char* name, int nStops, int* nRoutes, int* nConnections) {
    int i, j, k, foundRoute = 0;

    for (i = 0; i < *nRoutes; i++)
    {
        if (strcmp((*RouteMap)[i].name, name) == 0)
        {

            for (j = 0; j < nStops; j++)
            {
                for (k = 0; k < (*RouteMap)[i].nRouteStops; k++)
                {
                    if ( strcmp((*StopMap)[j].name, (*StopMap)[(*RouteMap)[i].idStops[k]].name) == 0)
                    {
                        (*StopMap)[j].nRoutes--;
                    }
                }
            }

            for (j = 0; j < *nConnections; j++)
            {
                if ((*ConnectionMap)[j].idRoute == i)
                {
                    for (k = i+1; k < *nConnections; k++) {
                        (*ConnectionMap)[k-1] = (*ConnectionMap)[k];
                    }

                    (*nConnections)--;
                    j--;
                }
            }
            
            
            for (j = i+1; j < *nRoutes; j++) {
                (*RouteMap)[j-1] = (*RouteMap)[j];
            }

            (*nRoutes)--;
            i--;
            foundRoute = 1;
            break;
        }
    }

    if (foundRoute == 0)
    {
        NoSuchLineException(name);
    }
}

/* 
 * FUNCTION: removeStop
 *
 * INPUT: The Stop's Structure, the Route's Structure, the Connection's Structure, a Stop's Name, Number of existent Stops, 
 * Number of existent Routes, Number of existent Connections
 * 
 * OUTPUT: Removes a Stop
 */
void removeStop(struct Stop **StopMap, struct Route **RouteMap, struct Connection **ConnectionMap, char* name, int* nStops, int nRoutes, int* nConnections) {
    
    int i, j, k, l, foundStop = 0;

    for (i = 0; i < *nStops; i++)
    {
        if (strcmp((*StopMap)[i].name, name) == 0)
        {
            for (j = 0; j < nRoutes; j++)
            {
                for (k = 0; k < (*RouteMap)[j].nRouteStops; k++)
                {
                    if (i == (*RouteMap)[j].idStops[k])
                    {

                        for (l = k+1; l < (*RouteMap)[j].nRouteStops; l++)
                        {
                            (*RouteMap)[j].idStops[l] = (*RouteMap)[j].idStops[l+1];
                        }


                        ((*RouteMap)[j].nRouteStops)--;
                        l--;
                        foundStop += 1;                     
                    }
                }
            }
            
            for (j = 0; j < *nConnections; j++)
            {   
                if ((*ConnectionMap)[j].idStartingPoint == i || (*ConnectionMap)[j].idArrivalPoint == i)
                {
                    for (k = i+1; k < *nConnections; k++) {
                        (*ConnectionMap)[k-1] = (*ConnectionMap)[k];
                    }

                    (*nConnections)--;
                    j--;
                }
            }

            for (j = 0; j < nRoutes; j++)
            {
                strcpy((*RouteMap)[j].startingPoint, (*StopMap)[((*RouteMap)[j].nRouteStops) - ((*RouteMap)[j].nRouteStops) + 1].name);
                strcpy((*RouteMap)[j].arrivalPoint, (*StopMap)[((*RouteMap)[j].nRouteStops)].name);

                for (k = 0; k < *nConnections; k++)
                {
                    (*RouteMap)[j].totalPrice = 0;
                    (*RouteMap)[j].totalDuration = 0;

                    if ((*ConnectionMap)[k].idRoute == j)
                    {
                        (*RouteMap)[j].totalPrice += (*ConnectionMap)[k].price;
                        (*RouteMap)[j].totalDuration += (*ConnectionMap)[k].duration;
                    } 
                } 
            }

            for (j = i+1; j < *nStops; j++) {
                (*StopMap)[j-1] = (*StopMap)[j];
            }

            (*nStops)--;
            i--;
            foundStop = 1;
            break;
        }
    }

    if (foundStop == 0)
    {
        NoSuchStopException(name);
    }
}


/* Exception Functions */

void NoMemoryException() {
    printf("No memory.\n");
}

void IncorrectSortOptionException(){
    printf("incorrect sort option.\n");
}

void StopAlreadyExistsException(char* placeholderStopName) {
    printf("%s: stop already exists.\n", placeholderStopName);
}

void NoSuchStopException(char* placeholderStopName) {
    printf("%s: no such stop.\n", placeholderStopName);
}

void NoSuchLineException(char* placeholderRouteName) {
    printf("%s: no such line.\n", placeholderRouteName);
}

void NegativeCostOrDurationException() {
    printf("negative cost or duration.\n");
}

void ConnectionNotAvailableException() {
    printf("link cannot be associated with bus line.\n");
}
