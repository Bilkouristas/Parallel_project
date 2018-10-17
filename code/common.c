//common functions
int partition(int *v, int n) {
  int pivot = v[n-1];
  int i = 0;

  for (int j = 0; j < n - 1; j++)
    if (v[j] < pivot)
      swap(v,i++,j);

  swap(v, i, n - 1);
  return (i);
}


void print(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}
