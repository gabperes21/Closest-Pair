
#include<stdio.h>
#include<stdlib.h>
#include<cstdio>
#include <time.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cfloat>


using namespace std;

struct Ponto{
 float x, y;
};

float forca_bruta(Ponto p, int tam);
void imprimir();
float euclidiana();
Ponto* mergeSort();
Ponto* merge(Ponto p[], int inicio, int meio, int fim, int coordenada);
float closest_pair(Ponto p[], int tam, Ponto &p1, Ponto &p2);
float closest_procura(Ponto px[], Ponto py[], int tam, Ponto &p1, Ponto &p2);
float strip(Ponto p_strip[], int tam, float dist, Ponto &p1, Ponto &p2);

//Distância Euclidiana
float euclidiana(float x1, float y1, float x2, float y2){
   return sqrt(pow(x2 - x1,2) + pow(y2-y1,2));
}

//Imprimir vetor
void imprimir(Ponto *p, int linha){

  int i;

  for (i = 0; i < linha; i++){
   		printf("X: %f e Y: %f", p[i].x, p[i].y);
 	printf("\n");
  }
}

//Alocar Matriz
float **alocar(int linha, int coluna){

  float **matriz;
  int i;

  //Aloca as linhas
  matriz = (float **) calloc (linha, sizeof(Ponto *));
  if (matriz == NULL) {
     printf (" Problema de Memoria Insuficiente");
     return (NULL);
  }
  //Aloca as colunas
  for ( i = 0; i < linha; i++ ) {
      matriz[i] = (float*) calloc (coluna, sizeof(Ponto *));
      if (matriz[i] == NULL) {
         printf ("Problema de Memoria Insuficiente");
         return (NULL);
      }
  }
  return (matriz);
}
/************************************************/
//Algoritmo Forca Bruta
void forca_bruta(Ponto *p, int tam){

  clock_t t2;
  t2 = clock();

  float fbx1 = 0;
	float fby1 = 0;
	float fbx2 = 0;
	float fby2 = 0;
  float fbd = 1000000000;
  float res[5];

  int i = 0, j = 0;

	for(i=0;i<tam;i++){
    	for (j = i+1; j < tam && i < tam; j++){
	  		if(euclidiana(p[i].x, p[i].y, p[j].x, p[j].y) < fbd){
	  			fbx1  = p[i].x;
	  			fby1 = p[i].y;
	  			fbx2 = p[j].x;
	  			fby2 = p[j].y;
      		fbd = euclidiana(p[i].x, p[i].y, p[j].x, p[j].y);
      		}
		}
	}
  t2 = clock() - t2;

	printf("%f %f %f %f %f %f ",((float)t2)/((CLOCKS_PER_SEC/1000)), fbd, fbx1, fby1, fbx2, fby2);

}
//Algoritmo Forca Bruta
float forca_bruta2(Ponto *p, int tam, Ponto & p1, Ponto &p2){

  float fbx1 = 0;
	float fby1 = 0;
	float fbx2 = 0;
	float fby2 = 0;
  float fbd = 1000000000;

   	int i = 0, j = 0;

	for(i=0;i<tam;i++){
    	for (j = i+1; j < tam && i < tam; j++){
	  		if(euclidiana(p[i].x, p[i].y, p[j].x, p[j].y) < fbd){
          fbd = euclidiana(p[i].x, p[i].y, p[j].x, p[j].y);
          p1.x = p[i].x, p1.y = p[i].y;
		      p2.x = p[j].x, p2.y = p[j].y;
      		}
		}
	}
	//printf(" Força Bruta:\n fbx1:%f\n fby1:%f\n fbx2:%f\n fby2:%f\n fbd:%f\n",fbx1, fby1, fbx2, fby2, fbd);
  return fbd;
}

//Algoritmo  MergeSorte para ordenar X e Y
Ponto* mergeSort(Ponto p[], int inicio, int fim, int coordenada){

  int meio;
  Ponto *ordenados;

  if(inicio<fim){
    meio = inicio + (fim - inicio)/2;
    mergeSort(p, inicio, meio, coordenada);
    mergeSort(p, meio + 1, fim, coordenada);
    ordenados = merge(p, inicio, meio, fim, coordenada);
    }
  return ordenados;

}

Ponto* merge(Ponto p[], int inicio, int meio, int fim, int coordenada){

  int i, j, k;
  int t_esq = meio - inicio + 1;
  int t_dir = fim - meio;

  Ponto esquerda[t_esq];
  Ponto direita[t_dir];

  for(i = 0; i < t_esq; i++)
    esquerda[i] = p[inicio + i];

  for(j = 0; j < t_dir; j++)
    direita[j] = p[meio + 1 + j];

  i = 0;
  j = 0;
  k = inicio;

  while (i < t_esq && j < t_dir){
    if(coordenada == 0){
      if(esquerda[i].x <= direita[j].x){
        p[k] = esquerda[i];
        i++;
      }
      else{
        p[k] = direita[j];
        j++;
      }
    }
    else if(coordenada == 1){
      if(esquerda[i].y <= direita[j].y){
        p[k] = esquerda[i];
        i++;
      }
      else{
        p[k] = direita[j];
        j++;
      }
    }
    k++;
  }
  while (i < t_esq) {
    p[k] = esquerda[i];
    i++;
    k++;
  }

  while (j < t_dir) {
    p[k] = direita[j];
    j++;
    k++;
  }

  return p;
}

float closest_pair(Ponto p[], int tam, Ponto &p1, Ponto &p2){

  float distancia;
  int i;

  Ponto px[tam];
  Ponto py[tam];
  Ponto *px_merge;
  Ponto *py_merge;

  for(i = 0; i< tam; i++){
    px[i] = p[i];
    py[i] = p[i];
  }

   px_merge = mergeSort(px, 0, tam -1, 0);
   py_merge = mergeSort(py, 0, tam -1, 1);
   distancia = closest_procura(px_merge, py_merge, tam, p1, p2);
   //printf("CP -> distancia: %f\n",distancia);
  return distancia;

}

float closest_procura(Ponto px[], Ponto py[], int tam, Ponto &p1, Ponto &p2){

  if (tam <= 3){
    return forca_bruta2(px, tam, p1, p2);

  }

  Ponto aux1, aux2, aux3, aux4;


  float dist_esq, dist_dir;

  int i;
  int meio = tam/2;
  int esq = 0;
  int dir = 0;
  int aux = 0;
  float distancia = 1000000000;
  float distancia_strip;

  Ponto p_meio = px[meio];
  Ponto p_strip[tam];


  // for(i =0; i < tam; i++){
  //   if(py[i].x <= p_meio.x){
  //     py_esq[esq++] = py[i];
  //   }
  //   else{
  //     py_dir[dir++] = py[i];
  //   }
  // }

    dist_esq = closest_procura(px, py, meio, aux1, aux2);
    dist_dir = closest_procura((px + meio), py, (tam - meio), aux3, aux4);

    if(dist_esq < dist_dir) {
      p1.x = aux1.x; p1.y = aux1.y;
      p2.x = aux2.x; p2.y = aux2.y;
    }
    else {
      p1.x = aux3.x; p1.y = aux3.y;
      p2.x = aux4.x; p2.y = aux4.y;
    }

    //printf("PX %f\n", p1.x);

    distancia = min(dist_esq, dist_dir);

    int j = 0;

    for(int i = 0; i < tam; i++){
      if(abs(px[i].x - p_meio.x) < distancia){
        py[j++] = px[i];
      }
    }
    //printf("%f\n", distancia);
    distancia_strip = strip(py, j, distancia, p1, p2);
    //printf("DS:%f, D:%f\n",distancia_strip,distancia );

    if(distancia_strip < distancia) {
		    p1.x = aux1.x; p1.y = aux1.y;
		    p2.x = aux2.x; p2.y = aux2.y;
        distancia = distancia_strip;
    }
    return distancia;
}

float strip(Ponto p_strip[], int tam, float dist, Ponto &p1, Ponto &p2){
  float min = dist;

    for(int i = 0; i < tam; i++){
      for(int j = i +1; j< tam && (p_strip[j].y - p_strip[i].y) < min; j++){
        if(euclidiana(p_strip[i].x, p_strip[i].y, p_strip[j].x, p_strip[j].y) < min){
          min = euclidiana(p_strip[i].x, p_strip[i].y, p_strip[j].x, p_strip[j].y);
          p1.x = p_strip[i].x, p1.y = p_strip[i].y;
		      p2.x = p_strip[j].x, p2.y = p_strip[j].y;
      }
    }
  }

  return min;
}

/************************************************/

int main(){

  clock_t t1;
  FILE *input;


  int linha;
  int coluna = 2;
  int i,j;
  int aux = 0;

  //Ler arquivo de entrada
  input = fopen("input.txt", "rt");

  //Verifica se há algum problema com o arquivo
  if(input == NULL){
	printf("Problemas com o arquivo\n");
	return(-1);
  }

  fscanf(input, "%d", &linha);
  Ponto p[linha];
  Ponto p1, p2;

  p1.x = 10000000;
  p1.y = 10000000;

  p2.x = 10000000;
  p2.y = 10000000;

  //Ler os elementos da matriz
  for(i = 0; i < linha; i++){

    Ponto p_aux;
    float ponto_x, ponto_y;

    fscanf(input, "%f", &ponto_x);
    fscanf(input, "%f", &ponto_y);

    p_aux.x = ponto_x;
   	p_aux.y = ponto_y;

    p[i] = p_aux;
  }

  //imprimir(p, linha);


  t1 = clock();
  float div_dist = closest_pair(p, linha, p1, p2);

  t1 = clock() - t1;

  forca_bruta(p, linha);
  printf("%f ", ((float)t1)/((CLOCKS_PER_SEC/1000)));
  printf("%f %f %f %f %f \n", div_dist, p2.x, p2.y, p1.x, p1.y);

  return 0;
}
