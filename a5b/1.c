#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int graph[1000][1000];
  memset(graph, 0, 1000 * 1000 * sizeof(int));
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    printf("%d ", i);
    for (int ii = 0; ii < n; ii++) {
      scanf("%d", &graph[i][ii]);
      if (graph[i][ii]) {
        printf("%d ", ii);
      }
    }
    printf("\n");
  }
  return 0;
}
