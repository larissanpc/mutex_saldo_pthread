#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t m1;
pthread_mutex_t m2;
float saldoA;
float saldoB;
FILE* sA;
FILE* sB;
FILE* sAR;
FILE* sBR;

void *ClienteA() {
  float qtd = 10.0;
  pthread_mutex_lock(&m1);
  pthread_mutex_lock(&m2);
  printf("\n\nTransação A para B = -10\n");
  sAR = fopen("saldoA.txt", "r");
  fscanf(sAR, "%f", &saldoA);
  sA = fopen("saldoA.txt", "w+");
  printf("\nsaldoA = %f",saldoA);
  saldoA = saldoA - qtd;
  fprintf (sA, "%2f", saldoA);
  printf("\nsaldoA novo = %f",saldoA);

  sBR = fopen("saldoB.txt", "r");
  fscanf(sBR, "%f", &saldoB);
  sB = fopen("saldoB.txt", "w+");
  printf("\nsaldoB = %f",saldoB);
  saldoB = saldoB + qtd;
  fprintf (sB, "%2f", saldoB);
  printf("\nsaldoB novo = %f",saldoB);
  
  fclose (sA);
  fclose (sAR);
  fclose (sB);
  fclose (sBR);
  sleep(2);
  pthread_mutex_unlock(&m2);
  pthread_mutex_unlock(&m1);
  
}

void *ClienteB() {
  float qtd = 100.0;
  pthread_mutex_lock(&m1);
  pthread_mutex_lock(&m2);
  printf("\n\nTransação B para A = -100\n");
  sBR = fopen("saldoB.txt", "r");
  fscanf(sBR, "%f", &saldoB);
  sB = fopen("saldoB.txt", "w+");
  printf("\nsaldoB = %f",saldoB);
  saldoB = saldoB - qtd;
  fprintf (sB, "%2f", saldoB);
  printf("\nsaldoB novo = %f",saldoB);

  sAR = fopen("saldoA.txt", "r");
  fscanf(sAR, "%f", &saldoA);
  sA = fopen("saldoA.txt", "w+");
  printf("\nsaldoA = %f",saldoA);
  saldoA = saldoA + qtd;
  fprintf (sA, "%2f", saldoA);
  printf("\nsaldoA novo = %f",saldoA);
  
  fclose (sA);
  fclose (sAR);
  fclose (sB);
  fclose (sBR);
  sleep(2);
  pthread_mutex_unlock(&m1);
  pthread_mutex_unlock(&m2);
  
}

int main(void) {
  pthread_mutex_init(&m1, NULL);
  pthread_mutex_init(&m2, NULL);
  
  pthread_t t1,t2;
  pthread_create(&t1, NULL, ClienteA, NULL);
  pthread_create(&t2, NULL, ClienteB, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2,NULL);
  sleep(10);
  
  return 0;
}
