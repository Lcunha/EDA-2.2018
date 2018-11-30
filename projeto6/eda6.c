#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
//projeto 2
FILE *getAsphaltImage(FILE *, int id);
FILE *getGrassImage(FILE *fp, int id);

void doRandom(int *, int limite);
void linhasColunas(FILE *, int *linhas, int *colunas);
void setMatrizFile(FILE *fp, int **matrizFile, int lin, int col);
void ILBP(int **matrizFile, int lin, int col, int *ilbp);
void GLCM(int **matrizFile, int lin, int col, float *metricas);
void calculaMetricas(int **glcm, float *metricas, int initialPosition, int linhaColuna);
void euclidianDistance(int *vetorNormalizado, int *vetorA, int *vetorB, int limite);
void normalize(float *vet, float *vetNormalizado, int limite);
void concatenaIlbpGlcm(float *ilbpGlcm, int *ilbp, float *glcm);
void calculaMediaTreinamento(float **matTreinamento, float *vetMedia);
void setResultado(float **matResultado, float *vetNormalizado, int *contador);
void salvarVetorAsphalt(FILE *auxAsphalt, float *vetNormalizado, int asphaltVet);
void salvarVetorGrass(FILE *auxGrass, float *vetNormalizado, int grassVet);
void setVetorBinario(int **matrizFile, int lin, int col, char *vetorbin);

int calcMenorDecimal(char *bin);
double calculaContraste(int **matriz, int linhaColuna);
double calculaHomogeneidade(int **matriz, int linhaColuna);
double calculaEnergia(int **matriz, int linhaColuna);
//fim do projeto 2
void projeto2();

int main(int argc, char *argv[])
{
    projeto2();
    int neuronios_Camadaoculta = atoi(argv[1]);
    if (argc != 2)
    {
        printf("Parametro incorreto. Exit.\n");
        exit(1);
    }
    printf("Neuronios Camada Oculta: %d\n-----------------------------\n", neuronios_Camadaoculta);
    return 0;
}

void projeto2(){
  int grass[50], asphalt[50];
  int lin = 0, col = 0, aux = 0;
  int **matrizFile, *ilbp;
  float *glcm, *ilbpGlcm, *ilbpGlcmNormalizadoGrass, *ilbpGlcmNormalizadoAsphaut, *mediaGrama, *mediaAsfalto;
  float **resultadoGrama, **resultadoAsfalto, **treinamentoResultadoGrama, **treinamentoResultoAsfalto;

  resultadoAsfalto = (float **)malloc(50 * sizeof(float *));

  for (int i = 0; i < 50; i++)
  {
    *(resultadoAsfalto + i) = (float *)malloc(536 * sizeof(float));
  }

  doRandom(asphalt, 50);
  aux = 0;
  FILE *auxAsphalt;
  auxAsphalt = fopen("asphalt.txt", "w+");
  FILE *auxGrass;
  auxGrass = fopen("grass.txt", "w+");

  for (int i = 0; i < 50; i++)
  {
    FILE *fileAsphalt;
    fileAsphalt = getAsphaltImage(fileAsphalt, asphalt[i]);
    linhasColunas(fileAsphalt, &lin, &col);
    matrizFile = (int **)malloc(lin * sizeof(int *));
    for (int j = 0; j < lin; j++)
    {
      *(matrizFile + j) = (int *)malloc(col * sizeof(int));
    }
    setMatrizFile(fileAsphalt, matrizFile, lin, col);

    ilbp = (int *)calloc(512, sizeof(int *));
    glcm = (float *)calloc(24, sizeof(float));
    ilbpGlcm = (float *)calloc(536, sizeof(float));
    ilbpGlcmNormalizadoAsphaut = (float *)calloc(536, sizeof(float));

    ILBP(matrizFile, lin, col, ilbp);
    GLCM(matrizFile, lin, col, glcm);
    concatenaIlbpGlcm(ilbpGlcm, ilbp, glcm);
    normalize(ilbpGlcm, ilbpGlcmNormalizadoAsphaut, 536);
    salvarVetorAsphalt(auxAsphalt, ilbpGlcmNormalizadoAsphaut, asphalt[i]);

    free(ilbp);
    free(glcm);
    free(ilbpGlcm);

    for (int j = 0; j < lin; j++)
    {
      free(*(matrizFile + j));
    }
    free(matrizFile);
    fclose(fileAsphalt);
    free(ilbpGlcmNormalizadoAsphaut);
  }

  resultadoGrama = (float **)malloc(50 * sizeof(float *));
  for (int i = 0; i < 50; i++)
  {
    *(resultadoGrama + i) = (float *)malloc(536 * sizeof(float));
  }
  doRandom(grass, 50);
  aux = 0;
  for (int i = 0; i < 50; i++)
  {
    FILE *fileGrass;
    fileGrass = getGrassImage(fileGrass, grass[i]);
    linhasColunas(fileGrass, &lin, &col);
    matrizFile = (int **)malloc(lin * sizeof(int *));
    for (int j = 0; j < lin; j++)
    {
      *(matrizFile + j) = (int *)malloc(col * sizeof(int));
    }
    setMatrizFile(fileGrass, matrizFile, lin, col);

    ilbp = (int *)calloc(512, sizeof(int *));
    glcm = (float *)calloc(24, sizeof(float));
    ilbpGlcm = (float *)calloc(536, sizeof(float));
    ilbpGlcmNormalizadoGrass = (float *)calloc(536, sizeof(float));
    ILBP(matrizFile, lin, col, ilbp);
    GLCM(matrizFile, lin, col, glcm);
    concatenaIlbpGlcm(ilbpGlcm, ilbp, glcm);
    normalize(ilbpGlcm, ilbpGlcmNormalizadoGrass, 536);

    salvarVetorGrass(auxGrass, ilbpGlcmNormalizadoGrass, grass[i]);

    free(ilbp);
    free(glcm);
    free(ilbpGlcm);
    for (int j = 0; j < lin; j++)
    {
      free(*(matrizFile + j));
    }
    free(matrizFile);
    fclose(fileGrass);
    free(ilbpGlcmNormalizadoGrass);
  }

  fclose(auxAsphalt);
  fclose(auxGrass);
}//fim do projeto2

//funçoes projeto 2
void salvarVetorGrass(FILE *grass, float *vetNormalizado, int grassVet)
{
  int i = 0;
  while (i < 536)
  {
    fprintf(grass, "%f", vetNormalizado[i]);
    i++;
  }
  fprintf(grass, "%f\n", vetNormalizado[i]);
}

void salvarVetorAsphalt(FILE *asphalt, float *vetNormalizado, int asphaltVet)
{

  for (int i = 0; i < 536; i++)
  {

    if (i == 535)
    {
      fprintf(asphalt, "%f\n", vetNormalizado[i]);
    }
    else
    {
      fprintf(asphalt, "%f\n", vetNormalizado[i]);
    }
  }
}

void calculaMediaTreinamento(float **matTreinamento, float *vetMedia)
{
  for (int i = 0; i < 536; i++)
  {
    for (int j = 0; j < 25; j++)
    {
      vetMedia[i] += matTreinamento[j][i];
    }
    vetMedia[i] = vetMedia[i] / 25.0;
  }
}

void setResultado(float **matResultado, float *vetNormalizado, int *contador)
{
  for (int i = 0; i < 536; i++)
  {
    *(*(matResultado + (*contador)) + i) = *(vetNormalizado + i);
  }
  contador++;
}

void concatenaIlbpGlcm(float *ilbpGlcm, int *ilbp, float *glcm)
{
  for (int j = 0; j < 512; j++)
  {
    *(ilbpGlcm + j) = *(ilbp + j);
  }
  for (int j = 512; j < 536; j++)
  {
    *(ilbpGlcm + j) = *(glcm + (j - 512));
  }
}

void ILBP(int **matrizFile, int lin, int col, int *ilbp)
{

  char vetorBinario[9];
  int menorDecimal;

  for (int i = 1; i < lin - 1; i++)
  {
    for (int j = 1; j < col - 1; j++)
    {
      setVetorBinario(matrizFile, i, j, vetorBinario);
      menorDecimal = calcMenorDecimal(vetorBinario);
      ilbp[menorDecimal]++;
    }
  }
}

int calcMenorDecimal(char *bin)
{

  int decimal, m = 0, menorNumero = 512;
  char aux;
  int dec[9];

  for (int q = 9; q > 0; q--)
  {
    decimal = 0;
    int j = 0;
    for (int i = 8; i >= 0; i--)
    {
      if (*(bin + i) == '1')
      {
        decimal += pow(2, j);
      }
      j++;
    }

    aux = bin[8];
    for (int c = 8; c > 0; c--)
    {
      bin[c] = bin[c - 1];
    }
    bin[0] = aux;

    dec[m] = decimal;
    m++;
  }

  for (int i = 0; i < 9; i++)
  {
    if (menorNumero > dec[i])
    {
      menorNumero = dec[i];
    }
  }
  return menorNumero;
}

void setVetorBinario(int **matrizFile, int lin, int col, char *vetorbin)
{
  float soma = 0, media;
  int i, j, x = 0, y = 0;
  char **bin;

  bin = (char **)malloc(3 * sizeof(char *));
  for (i = 0; i < 3; i++)
  {
    *(bin + i) = (char *)malloc(3 * sizeof(char));
  }

  for (i = lin - 1; i <= lin + 1; i++)
  {
    for (j = col - 1; j <= col + 1; j++)
    {
      soma += *(*(matrizFile + i) + j);
    }
  }

  media = soma / 9.0;

  for (i = lin - 1; i <= lin + 1; i++)
  {
    for (j = col - 1; j <= col + 1; j++)
    {
      if (*(*(matrizFile + i) + j) < media)
      {
        *(*(bin + x) + y) = '0';
      }
      else if (*(*(matrizFile + i) + j) >= media)
      {
        *(*(bin + x) + y) = '1';
      }
      y++;
    }
    y = 0;
    x++;
  }
  vetorbin[0] = *(*(bin + 0) + 0);
  vetorbin[1] = *(*(bin + 0) + 1);
  vetorbin[2] = *(*(bin + 0) + 2);
  vetorbin[3] = *(*(bin + 1) + 2);
  vetorbin[4] = *(*(bin + 2) + 2);
  vetorbin[5] = *(*(bin + 2) + 1);
  vetorbin[6] = *(*(bin + 2) + 0);
  vetorbin[7] = *(*(bin + 1) + 0);
  vetorbin[8] = *(*(bin + 1) + 1);

  for (i = 0; i < 3; i++)
  {
    free(*(bin + i));
  }
  free(bin);
}

void setMatrizFile(FILE *fp, int **matrizFile, int lin, int col)
{
  char pv;
  rewind(fp);
  for (int i = 0; i < lin; i++)
  {
    for (int j = 0; j < col; j++)
    {
      if (!feof(fp))
      {
        fscanf(fp, "%d%c", *(matrizFile + i) + j, &pv);
      }
    }
  }
}

void linhasColunas(FILE *fp, int *linhas, int *colunas)
{
  char marcador;
  *linhas = 0, *colunas = 1;
  while ((marcador = fgetc(fp)) != EOF)
  {
    if (marcador == '\n')
    {
      *linhas = *linhas + 1;
    }
    else if (*linhas == 0 && marcador == ';')
    {
      *colunas = *colunas + 1;
    }
  }
}

FILE *getAsphaltImage(FILE *fp, int id)
{
  char asphalt[40];
  if (id < 10)
    sprintf(asphalt, "DataSet/asphalt/asphalt_0%d.txt", id);
  else
    sprintf(asphalt, "DataSet/asphalt/asphalt_%d.txt", id);
    
  fp = fopen(asphalt, "r");

  if (fp == NULL)
  {
    printf("Falha leitura arquivo DataSet/...\n");
    exit(1);
  }
  return fp;
}

FILE *getGrassImage(FILE *fp, int id)
{
  char grass[40];
  if (id < 10)
    sprintf(grass, "DataSet/grass/grass_0%d.txt", id);
  else
    sprintf(grass, "DataSet/grass/grass_%d.txt", id);

  fp = fopen(grass, "r");

  if (fp == NULL)
  {
    printf("Falha leitura /DataSet/.. .\n");
    exit(1);
  }
  return fp;
}

void doRandom(int *vet, int limite)
{
  srand(time(NULL));
  for (int i = 1; i < limite + 1; i++)
  {
    vet[i - 1] = i;
  }
  for (int i = 0; i < limite; i++)
  {
    int aux = vet[i];
    int random = rand() % limite;
    if (random != 0)
    {
      vet[i] = vet[random];
      vet[random] = aux;
    }
  }
}

void normalize(float *vet, float *vetNormalizado, int limite)
{
  float menor = 9999999, maior = 0;

  for (int i = 0; i < limite; i++)
  {
    if (vet[i] < menor)
      menor = vet[i];
    if (vet[i] > maior)
      maior = vet[i];
  }

  for (int i = 0; i < limite; i++)
    vetNormalizado[i] = (vet[i] - menor) / (maior - menor);
}

void euclidianDistance(int *vetorNormalizado, int *vetorA, int *vetorB, int limite)
{
  float distanciaA, distanciaB;
  int somaA = 0, somaB = 0;

  for (int i = 0; i < limite; i++)
  {
    somaA += (pow((vetorNormalizado[i] + vetorA[i]), 2));
    somaB += (pow((vetorNormalizado[i] + vetorB[i]), 2));
  }

  distanciaA = (pow(somaA, 0.5));
  distanciaB = (pow(somaB, 0.5));
}

void calculaMetricas(int **glcm, float *metricas, int initialPosition, int linhaColuna)
{
  *(metricas + initialPosition) = calculaContraste(glcm, linhaColuna);
  *(metricas + (initialPosition + 1)) = calculaEnergia(glcm, linhaColuna);
  *(metricas + (initialPosition + 2)) = calculaHomogeneidade(glcm, linhaColuna);
}

void GLCM(int **matrizFile, int lin, int col, float *metricas)
{
  int **glcm, GLCM_LINHA_COLUNA = 512;
  for (int k = 0; k < 8; k++)
  {
    glcm = (int **)calloc(GLCM_LINHA_COLUNA, sizeof(int *));
    for (int i = 0; i < GLCM_LINHA_COLUNA; i++)
    {
      *(glcm + i) = (int *)calloc(GLCM_LINHA_COLUNA, sizeof(int));
    }
    if (k == 0)
    {
      for (int i = 0; i < lin; i++)
      {
        for (int j = 0; j < col - 1; j++)
        {
          glcm[matrizFile[i][j]][matrizFile[i][j + 1]]++;
        }
      }
      calculaMetricas(glcm, metricas, 0, GLCM_LINHA_COLUNA);
    }
    else if (k == 1)
    {
      for (int i = 0; i < lin; i++)
      {
        for (int j = 1; j < col; j++)
        {
          glcm[matrizFile[i][j]][matrizFile[i][j - 1]]++;
        }
      }
      calculaMetricas(glcm, metricas, 3, GLCM_LINHA_COLUNA);
    }
    else if (k == 2)
    {
      for (int i = 1; i < lin; i++)
      {
        for (int j = 0; j < col; j++)
        {
          glcm[matrizFile[i][j]][matrizFile[i - 1][j]]++;
        }
      }
      calculaMetricas(glcm, metricas, 6, GLCM_LINHA_COLUNA);
    }
    else if (k == 3)
    {
      for (int i = 0; i < lin - 1; i++)
      {
        for (int j = 0; j < col; j++)
        {
          glcm[matrizFile[i][j]][matrizFile[i + 1][j]]++;
        }
      }
      calculaMetricas(glcm, metricas, 9, GLCM_LINHA_COLUNA);
    }
    else if (k == 4)
    {
      for (int i = 1; i < lin; i++)
      {
        for (int j = 1; j < col; j++)
        {
          glcm[matrizFile[i][j]][matrizFile[i - 1][j - 1]]++;
        }
      }
      calculaMetricas(glcm, metricas, 12, GLCM_LINHA_COLUNA);
    }
    else if (k == 5)
    {

      for (int i = 1; i < lin; i++)
      {
        for (int j = 0; j < col - 1; j++)
        {
          glcm[matrizFile[i][j]][matrizFile[i - 1][j + 1]]++;
        }
      }
      calculaMetricas(glcm, metricas, 15, GLCM_LINHA_COLUNA);
    }
    else if (k == 6)
    {
      for (int i = 0; i < lin - 1; i++)
      {
        for (int j = 1; j < col; j++)
        {
          glcm[matrizFile[i][j]][matrizFile[i + 1][j - 1]]++;
        }
      }
      calculaMetricas(glcm, metricas, 18, GLCM_LINHA_COLUNA);
    }
    else if (k == 7)
    {
      for (int i = 0; i < lin - 1; i++)
      {
        for (int j = 0; j < col - 1; j++)
        {
          glcm[matrizFile[i][j]][matrizFile[i + 1][j + 1]]++;
        }
      }
      calculaMetricas(glcm, metricas, 21, GLCM_LINHA_COLUNA);
    }
    for (int i = 0; i < GLCM_LINHA_COLUNA; i++)
    {
      free(*(glcm + i));
    }
    free(glcm);
  }
}

double calculaContraste(int **matriz, int linhaColuna)
{
  double total = 0.0;
  for (int i = 0; i < linhaColuna; i++)
  {
    for (int j = 0; j < linhaColuna; j++)
    {
      total += matriz[i][j] * pow(i - j, 2);
    }
  }
  return total;
}

double calculaHomogeneidade(int **matriz, int linhaColuna)
{
  double total = 0.0;
  for (int i = 0; i < linhaColuna; i++)
  {
    for (int j = 0; j < linhaColuna; j++)
    {
      total += matriz[i][j] / (1 + abs(i - j));
    }
  }
  return total;
}

double calculaEnergia(int **matriz, int linhaColuna)
{
  double total = 0.0;
  for (int i = 0; i < linhaColuna; i++)
  {
    for (int j = 0; j < linhaColuna; j++)
    {
      total += pow(matriz[i][j], 2);
    }
  }
  return total;
}
//fim funções do projeto 2