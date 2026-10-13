#include <stdio.h>

#define MAX 10
#define INF 9999

int graph[MAX][MAX];
int dist[MAX];
int visited[MAX];
int parent[MAX];
char location[MAX][30];
int n;
int source;
int graphEntered = 0;
int algorithmDone = 0;

void enterGraph(void)
{
    int i, j;
    int weight;

    printf("\nEnter number of locations: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of locations. Please enter a value between 1 and %d.\n", MAX);
        n = 0;
        graphEntered = 0;
        return;
    }

    printf("\nEnter location names:\n");
    for (i = 0; i < n; i++)
    {
        printf("Location %d: ", i + 1);
        scanf(" %29[^\n]", location[i]);
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }

    printf("\nEnter distance between locations.\n");
    printf("Enter -1 if there is no direct road.\n\n");

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            printf("Distance between %s and %s: ", location[i], location[j]);
            scanf("%d", &weight);

            if (weight == -1)
            {
                graph[i][j] = INF;
                graph[j][i] = INF;
            }
            else if (weight >= 0)
            {
                graph[i][j] = weight;
                graph[j][i] = weight;
            }
            else
            {
                printf("Invalid distance. Using no direct road instead.\n");
                graph[i][j] = INF;
                graph[j][i] = INF;
            }
        }
    }

    graphEntered = 1;
    algorithmDone = 0;
    source = -1;

    printf("\nCampus graph entered successfully!\n");
}

void displayMatrix(void)
{
    int i, j;

    if (!graphEntered)
    {
        printf("\nPlease enter the graph first.\n");
        return;
    }

    printf("\n========== ADJACENCY MATRIX ==========\n\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
}

void selectSource(void)
{
    int i;

    if (!graphEntered)
    {
        printf("\nPlease enter the graph first.\n");
        return;
    }

    printf("\nCampus Locations:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d. %s\n", i + 1, location[i]);
    }

    printf("\nEnter source location number: ");
    scanf("%d", &source);
    source--;

    if (source < 0 || source >= n)
    {
        printf("Invalid location!\n");
        source = -1;
        return;
    }

    algorithmDone = 0;
    printf("Source selected: %s\n", location[source]);
}

void dijkstra(void)
{
    int i, j;
    int min, u;

    if (!graphEntered)
    {
        printf("\nPlease enter the graph first.\n");
        return;
    }

    if (source < 0)
    {
        printf("\nPlease select a source first.\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (i = 0; i < n; i++)
    {
        min = INF;
        u = -1;

        for (j = 0; j < n; j++)
        {
            if (visited[j] == 0 && dist[j] < min)
            {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (j = 0; j < n; j++)
        {
            if (visited[j] == 0 && graph[u][j] != INF && dist[u] + graph[u][j] < dist[j])
            {
                dist[j] = dist[u] + graph[u][j];
                parent[j] = u;
            }
        }
    }

    algorithmDone = 1;
    printf("\nDijkstra's Algorithm completed successfully!\n");
}

void displayPath(int destination)
{
    int path[MAX];
    int count = 0;
    int current = destination;
    int i;

    if (destination < 0 || destination >= n)
    {
        printf("Invalid destination");
        return;
    }

    if (dist[destination] == INF)
    {
        printf("No path");
        return;
    }

    while (current != -1 && count < MAX)
    {
        path[count] = current;
        count++;
        current = parent[current];
    }

    for (i = count - 1; i >= 0; i--)
    {
        printf("%s", location[path[i]]);
        if (i != 0)
            printf(" -> ");
    }
}

void displayShortestPaths(void)
{
    int i;

    if (!algorithmDone)
    {
        printf("\nPlease run Dijkstra's Algorithm first.\n");
        return;
    }

    printf("\n========== SHORTEST PATHS ==========" );
    printf("\nSource: %s\n\n", location[source]);

    for (i = 0; i < n; i++)
    {
        printf("Destination: %s\n", location[i]);

        if (dist[i] == INF)
        {
            printf("Distance: No path\n");
            printf("Path: No path\n");
        }
        else
        {
            printf("Distance: %d\n", dist[i]);
            printf("Path: ");
            displayPath(i);
            printf("\n");
        }

        printf("\n");
    }
}

void displayDistances(void)
{
    int i;

    if (!algorithmDone)
    {
        printf("\nPlease run Dijkstra's Algorithm first.\n");
        return;
    }

    printf("\n========== DISTANCES ==========" );
    printf("\n");
    for (i = 0; i < n; i++)
    {
        if (dist[i] == INF)
            printf("%s : No path\n", location[i]);
        else
            printf("%s : %d\n", location[i], dist[i]);
    }
}

int main(void)
{
    int choice;

    source = -1;

    do
    {
        printf("\n\n====================================\n");
        printf("   CAMPUS SHORTEST ROUTE FINDER\n");
        printf("       DIJKSTRA'S ALGORITHM\n");
        printf("====================================\n");

        printf("1. Enter Campus Graph\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Select Source Location\n");
        printf("4. Find Shortest Distance\n");
        printf("5. Display Shortest Paths\n");
        printf("6. Display Distance from Source\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterGraph();
                break;

            case 2:
                displayMatrix();
                break;

            case 3:
                selectSource();
                break;

            case 4:
                dijkstra();
                break;

            case 5:
                displayShortestPaths();
                break;

            case 6:
                displayDistances();
                break;

            case 7:
                printf("\nProgram exited successfully.\n");
                break;

            default:
                printf("\nInvalid choice! Enter 1 to 7.\n");
        }
    } while (choice != 7);

    return 0;
}
 
