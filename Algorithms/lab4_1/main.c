#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFINITY ((INT_MAX / 2) - 1)

typedef struct ListItem {
	int key;
	int weight;
	struct ListItem *next;
} ListItem, *PListItem;

typedef struct List {
	PListItem head;
	PListItem tail;
} List, *PList, *ArrayOfLists;

void PrintToTail(PListItem head) {
	for (PListItem ptr = head; ptr != NULL; ptr = ptr->next) {
		printf("(%d,%d) ", ptr->key, ptr->weight);
	}
}

void AddToTail(PList list, int key, int weight) {
	PListItem tmp = (PListItem)malloc(sizeof(ListItem));
	tmp->key = key;
	tmp->weight = weight;
	tmp->next = NULL;
	if (list->tail == NULL) {
        list->head = tmp;
    } else {
        (list->tail)->next = tmp;
    }
	list->tail = tmp;
}

void AddToHead(PList list, int key, int weight) {
	PListItem tmp = (PListItem)malloc(sizeof(ListItem));
	tmp->key = key;
	tmp->weight = weight;
	tmp->next = NULL;
	if (list->head == NULL) {
        list->tail = tmp;
    } else {
        tmp->next = list->head;
    }
	list->head = tmp;
}

int ReadVertex(FILE *file) {
	char str_vertex[6];

	if (fscanf(file, "%s", str_vertex) == EOF) {
        return EOF;
    }
	if (!strcmp(str_vertex, "x")) {
        return INFINITY;
    }
	return atoi(str_vertex);
}

ArrayOfLists MatrixToList(int **adjacency_matrix, size_t n) {
	ArrayOfLists result = (ArrayOfLists)malloc(sizeof(List) * n);
	for (int i = 0; i < n; i++) {
		result[i].head = NULL;
		result[i].tail = NULL;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjacency_matrix[i][j] != INT_MAX / 2 - 1) {
                AddToTail(&result[i], j, adjacency_matrix[i][j]);
            }
		}
	}
	return result;
}

int *DijkstrasAlgorithm(int start_vertex, ArrayOfLists adjacency_list, size_t n, int *way) {
	int *lengths = (int *)malloc(sizeof(int) * n);
	int *used = (int *)calloc(n, sizeof(int));
	int i, used_length = (int) n, min, break_flag = 1;
	PListItem iPtr;

	for (i = 0; i < n; i++) {
		lengths[i] = INFINITY;
		way[i] = -1;
	}
	lengths[start_vertex] = 0;

	i = start_vertex;
	while (used_length && break_flag) {
		iPtr = adjacency_list[i].head;
		while (iPtr != NULL) {
			if (!used[i] && lengths[iPtr->key] > lengths[i] + iPtr->weight) {
				lengths[iPtr->key] = lengths[i] + iPtr->weight;
				way[iPtr->key] = i;
			}
			iPtr = iPtr->next;
		}
		used_length--;
		used[i] = 1;

		min = INFINITY;
		break_flag = 0;
		for (int j = 0; j < n; j++) {
			if (!used[j] && (min >= lengths[j])) {
				i = j;
				min = lengths[i];
				break_flag = 1;
			}
		}
	}

	free(used);
	return lengths;
}

int *FindLongestWay(int start_vertex, ArrayOfLists adjacency_list, size_t n, int *way) {
	int *way_lengths;

	for (int i = 0; i < n; i++) {
		for (PListItem iPtr = adjacency_list[i].head; iPtr != NULL; iPtr = iPtr->next) {
			iPtr->weight *= -1;
		}
	}

	way_lengths = DijkstrasAlgorithm(start_vertex, adjacency_list, n, way);
	for (int i = 0; i < n; i++) {
		way_lengths[i] *= -1;
	}
	return way_lengths;
}

void PrintWayTo(int vertex, const int *way) {
	List list = {NULL, NULL};
 
	do {
		AddToHead(&list, vertex, 0);
		vertex = way[vertex];
	} while (vertex != -1);
	printf("%d", list.head->key);
	for (PListItem iPtr = list.head->next; iPtr != NULL; iPtr = iPtr->next) {
        printf(" -> %d", iPtr->key);
    }
}

int **FloydsAlgorithm(int **adjacency_matrix, size_t n) {
	int **result = (int**)malloc(sizeof(int*) * n);
	int tmp;

	for (int i = 0; i < n; i++) {
		result[i] = (int*)malloc(sizeof(int) * n);
		for (int j = 0; j < n; j++) {
			if (i == j) {
                result[i][j] = 0;
            } else {
                result[i][j] = adjacency_matrix[i][j];
            }
		}
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if ((result[i][k] == INFINITY) || (result[k][j] == INFINITY)) {
                    tmp = INFINITY;
                } else {
                    tmp = result[i][k] + result[k][j];
                }
				if (result[i][j] > tmp) {
                    result[i][j] = tmp;
                }
			}
		}
	}
	return result;
}

int FindCenter(int **adjacency_matrix, int **centers, size_t n) {
	int count = 0, length = 1, min = INFINITY;
	int *max_arr = (int *)malloc(sizeof(int) * n);
	int **shortest_ways = FloydsAlgorithm(adjacency_matrix, n);

	for (int i = 0; i < n; i++) {
        max_arr[i] = INT_MIN;
    }

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
 			if (max_arr[i] <= shortest_ways[j][i]) {
                max_arr[i] = shortest_ways[j][i];
            }
		}
		if (min >= max_arr[i]) {
            min = max_arr[i];
        }
	}

	for (int i = 0; i < n; i++) {
		if (min == max_arr[i]) {
			if (length == count) {
				int *tmp = (int *)realloc(max_arr, ++length);
				if (tmp == NULL) {
                    exit(-1);
                } else {
                    max_arr = tmp;
                }
			}
			count++;
			max_arr[count - 1] = i;
		}
	}
	*centers = realloc(max_arr, sizeof(int) * count);
	return count;
}

int main() {
	FILE *file = fopen("adjacency_matrix.txt", "r");
	int state, **adjacency_matrix;
	size_t n;
	int start_vertex, finish_vertex;

	if (file == NULL) {
		printf("Failed to open file");
		return -1;
	}

	state = fscanf(file, "%d", &n);
	if (state != EOF) {
		adjacency_matrix = (int **)malloc(sizeof(int *) * n);
		for (int i = 0; i < n; i++) {
            adjacency_matrix[i] = (int *) malloc(sizeof(int) * n);
        }
	} else {
		printf("the file is empty");
		return -1;
	}

	for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjacency_matrix[i][j] = ReadVertex(file);
        }
    }

	ArrayOfLists adjacency_list = MatrixToList(adjacency_matrix, n);
	for (int i = 0; i < n; i++) {
		printf("%d: ", i);
		PrintToTail(adjacency_list[i].head);
		printf("\n");
	}
	printf("\n");

	printf("Enter the start vertex:");
	scanf_s("%d", &start_vertex);
	printf("Enter the finish vertex:");
	scanf_s("%d", &finish_vertex);
	int *way = malloc(sizeof(int) * n);
	int *lengths = DijkstrasAlgorithm(start_vertex, adjacency_list, n, way);

	if (lengths[finish_vertex] == INFINITY) {
		printf("There is no way from %d to %d\n\n", start_vertex, finish_vertex);
	} else {
		printf("\nThe shortest way: ");
		PrintWayTo(finish_vertex, way);
		printf("; length = %d\n", lengths[finish_vertex]);
		lengths = FindLongestWay(start_vertex, adjacency_list, n, way);
		printf("The longest way: ");
		PrintWayTo(finish_vertex, way);
		printf("; length = %d\n\n", lengths[finish_vertex]);
	}

	int **shortest_ways = FloydsAlgorithm(adjacency_matrix, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (shortest_ways[i][j] == INFINITY) {
                printf("   x ");
            } else {
                printf("%4d ", shortest_ways[i][j]);
            }
		}
		printf("\n");
	}
	printf("\n");

	int *centers;
	int centers_count = FindCenter(adjacency_matrix, &centers, n);

	for (int i = 0; i < centers_count; i++) {
		printf("Center %d\n", centers[i]);
	}

    adjacency_list = MatrixToList(adjacency_matrix, n);
    lengths = DijkstrasAlgorithm(start_vertex, adjacency_list, n, way);
    while (lengths[finish_vertex] != INFINITY && finish_vertex < n && way[finish_vertex] < n){
        printf("\nThe way: ");
        PrintWayTo(finish_vertex, way);
        printf("; length = %d", lengths[finish_vertex]);
        adjacency_matrix[way[finish_vertex]][finish_vertex] = INFINITY;
        adjacency_list = MatrixToList(adjacency_matrix, n);
        lengths = DijkstrasAlgorithm(start_vertex, adjacency_list, n, way);
    }

	return 0;
}