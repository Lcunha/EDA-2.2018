#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define size_C 25
#define img 1025
#define max_glcm 256
#define result_glcm 24
#define ILBP 512
#define VetResult 536


void separetGroup(int *, int *);
int countLine(FILE *);
int countCollumns(FILE *);
void max_Min(int *, int *, double *, int);
void normalization(double *, int, int, int num);
void glcmRight(int **, double *);
void glcmLeft(int **, double *);
void glcmUpper(int **, double *);
void glcmBottom(int **, double *);
void glcmUpperRight(int **, double *);
void glcmUpperLeft(int **, double *);
void glcmBottomLeft(int **, double *);
void glcmBottomDireito(int **, double *);
void glcmEnergia(int **, double *);
void glcmHomogeneidade(int **, double *);
void glcmContraste(int **, double *);
void glcmCompleto(int **, double *);
int comparaMedia(int **);
int lowerDecimalNumber(int);
void vetorIlbp(int **, double *);
int vetorMedia(int *, int);
void euclidianDistance(double *, double *, double **, double **);
void mediaSet(double **, double *);
int compareDistance(double, double);
void resetMetrics(double *, double *);



int main(){

	//variaveis
	int *test;
	int *training;
	int **imagem;
	int i, j, k, max, min;
	char semicollon;
	int num;
	char fileName[40];
	double *ilbp;
	double *glcm;
	double *normal;
	double *mediaGrass;
	double *mediaAsphalt;
	double **resultTestGrass;
	double **resultTestAsphalt;
	double **resultTrainingGrass;
	double **resultTrainingAsphalt;
	double **distance;
	double taxaAcerto = 0;
	double falsaAceitacao = 0;
	double falsaRejeicao = 0;

	FILE *fp;

	//alocações
	mediaGrass = (double *)calloc(VetResult, sizeof(double));
	mediaAsphalt = (double *)calloc(VetResult, sizeof(double));
	normal = (double *)calloc(VetResult, sizeof(double));
	glcm = (double *)calloc(result_glcm, sizeof(double));
	ilbp = (double *)calloc(ILBP, sizeof(double));
	test = (int *)calloc(25, sizeof(int));
	training = (int *)calloc(25, sizeof(int));
	resultTestGrass = (double **)calloc(size_C, sizeof(double *));
	distance = (double **)calloc(size_C, sizeof(double));
	resultTestAsphalt = (double **)calloc(size_C, sizeof(double *));
	resultTrainingGrass = (double **)calloc(size_C, sizeof(double *));
	resultTrainingAsphalt = (double **)calloc(size_C, sizeof(double *));

	for (i = 0; i < size_C; i++){
		resultTestGrass[i] = (double *)calloc(VetResult, sizeof(double));
		resultTestAsphalt[i] = (double *)calloc(VetResult, sizeof(double));
		resultTrainingGrass[i] = (double *)calloc(VetResult, sizeof(double));
		resultTrainingAsphalt[i] = (double *)calloc(VetResult, sizeof(double));
		distance[i] = (double *)calloc(2, sizeof(double));
	}
	imagem = (int **)calloc(img, sizeof(int *));
	for (i = 0; i < img; i++){
		imagem[i] = (int *)calloc(img, sizeof(int));
	}

	separetGroup(test, training);

	for (i = 0; i < size_C; i++){

		snprintf(fileName, 40, "DataSet/grass/grass_%.2d.txt", test[i]);
		fp = fopen(fileName, "r");

		for (j = 0; j < img; j++){
			for (k = 0; k < img; k++){
				fscanf(fp, "%d %c", &num, &semicollon);
				imagem[j][k] = num;
			}
		}

		vetorIlbp(imagem, ilbp);
		glcmCompleto(imagem, glcm);

		for (j = 0; j < ILBP; j++){
			normal[j] = ilbp[j];
		}

		for (j = ILBP, k = 0; j < VetResult; j++, k++){
			normal[j] = glcm[k];
		}

		max_Min(&min, &max, normal, VetResult);
		normalization(normal, min, max, VetResult);

		for (j = 0; j < VetResult; j++){
			resultTestGrass[i][j] = normal[j];
		}

		resetMetrics(ilbp, glcm);
	}

	for (i = 0; i < size_C; i++){

		snprintf(fileName, 40, "DataSet/asphalt/asphalt_%.2d.txt", test[i]);

		fp = fopen(fileName, "r");

		for (j = 0; j < img; j++){
			for (k = 0; k < img; k++){
				fscanf(fp, "%d %c", &num, &semicollon);
				imagem[j][k] = num;
			}
		}

		vetorIlbp(imagem, ilbp);
		glcmCompleto(imagem, glcm);

		for (j = 0; j < ILBP; j++){
			normal[j] = ilbp[j];
		}
		for (j = ILBP, k = 0; j < VetResult; j++, k++){
			normal[j] = glcm[k];
		}

		max_Min(&min, &max, normal, VetResult);
		normalization(normal, min, max, VetResult);

		for (j = 0; j < VetResult; j++){
			resultTestAsphalt[i][j] = normal[j];
		}

		resetMetrics(ilbp, glcm);
	}

	for (i = 0; i < size_C; i++){


		snprintf(fileName, 40, "DataSet/grass/grass_%.2d.txt", training[i]);
		fp = fopen(fileName, "r");

		for (j = 0; j < img; j++){
			for (k = 0; k < img; k++){
				fscanf(fp, "%d %c", &num, &semicollon);
				imagem[j][k] = num;
			}
		}

		vetorIlbp(imagem, ilbp);
		glcmCompleto(imagem, glcm);

		for (j = 0; j < ILBP; j++){
			normal[j] = ilbp[j];
		}
		for (j = ILBP, k = 0; j < VetResult; j++, k++){
			normal[j] = glcm[k];
		}

		max_Min(&min, &max, normal, VetResult);
		normalization(normal, min, max, VetResult);

		for (j = 0; j < VetResult; j++){
			resultTrainingGrass[i][j] = normal[j];
		}

		resetMetrics(ilbp, glcm);
	}

	for (i = 0; i < size_C; i++){

		snprintf(fileName, 40, "DataSet/asphalt/asphalt_%.2d.txt", training[i]);

		fp = fopen(fileName, "r");

		for (j = 0; j < img; j++){
			for (k = 0; k < img; k++){
				fscanf(fp, "%d %c", &num, &semicollon);
				imagem[j][k] = num;
			}
		}

		vetorIlbp(imagem, ilbp);
		glcmCompleto(imagem, glcm);

		for (j = 0; j < ILBP; j++){
			normal[j] = ilbp[j];
		}
		for (j = ILBP, k = 0; j < VetResult; j++, k++){
			normal[j] = glcm[k];
		}

		max_Min(&min, &max, normal, VetResult);
		normalization(normal, min, max, VetResult);

		for (j = 0; j < VetResult; j++){
			resultTrainingAsphalt[i][j] = normal[j];
		}
		resetMetrics(ilbp, glcm);
	}

	mediaSet(resultTrainingGrass, mediaGrass);
	mediaSet(resultTrainingAsphalt, mediaAsphalt);

	euclidianDistance(mediaGrass, mediaAsphalt, resultTrainingGrass, distance);

	for (i = 0; i < size_C; i++){
		if ((compareDistance(distance[i][0], distance[i][1])) == 1){
			taxaAcerto++;
		}
		else{
			falsaAceitacao++;
		}
	}

	euclidianDistance(mediaGrass, mediaAsphalt, resultTrainingAsphalt, distance);

	for (i = 0; i < size_C; i++){
		if ((compareDistance(distance[i][0], distance[i][1])) == 0){
			taxaAcerto++;
		}
		else{
			falsaRejeicao++;
		}
	}

	printf("\n Taxa de acerto: %.1lf%% \n", (taxaAcerto / 50) * 100);
	printf("\n Taxa de falsa aceitação: %.1lf%% \n", (falsaAceitacao / 50) * 100);
	printf("\n Taxa de falsa rejeição: %.1lf%% \n\n", (falsaRejeicao / 50) * 100);

	fclose(fp);

	for (i = 0; i < size_C; i++){
		free(resultTestGrass[i]);
		free(resultTestAsphalt[i]);
		free(resultTrainingGrass[i]);
		free(resultTrainingAsphalt[i]);
		free(distance[i]);
	}

	for (i = 0; i < img; i++){
		free(imagem[i]);
	}

	free(imagem);
	free(mediaGrass);
	free(mediaAsphalt);
	free(normal);
	free(glcm);
	free(ilbp);
	free(test);
	free(training);
	free(resultTestGrass);
	free(distance);
	free(resultTestAsphalt);
	free(resultTrainingGrass);
	free(resultTrainingAsphalt);

	return 0;
}

//função separetGroup
void separetGroup(int *test, int *training){

	int i, j, k = 0;
	int number;
	int repeat;

	srand(time(NULL));

	for (i = 0; i < size_C; i++){

		number = rand() % 50 + 1;
		repeat = 0;

		for (j = 0; j < i; j++){

			if (*(test + j) == number){
				repeat++;
			}
		}

		if (repeat > 0){
			i--;
			continue;
		}
		else{
			*(test + i) = number;
		}
	}

	for (i = 1; i <= 50; i++){

		repeat = 0;

		for (j = 0; j < size_C; j++){
			if (i == *(test + j)){
				repeat++;
			}
		}

		if (repeat > 0){
			continue;
		}

		*(training + k) = i;
		k++;
	}
}

//função countLine
int countLine(FILE *nome_do_arquivo){

	int contaLinhas = 0;
	char semicollon;
	int number;

	while (!feof(nome_do_arquivo)){
		fscanf(nome_do_arquivo, "%d%c", &number, &semicollon);
		if (semicollon == '\n'){
			contaLinhas++;
		}
	}
	contaLinhas--;

	rewind(nome_do_arquivo);

	printf("%d\n", contaLinhas);
	return contaLinhas;
}

//função countCollumns
int countCollumns(FILE *arquivo){

	int contaColunas = 0, number;
	char semicollon = ';';

	while (semicollon != '\n'){
		fscanf(arquivo, "%d%c", &number, &semicollon);
		contaColunas++;
	}

	printf("%d\n", contaColunas);

	rewind(arquivo);
	return contaColunas;
}

//função max min
void max_Min(int *min, int *max, double *vetor, int num){

	int maximoTemporario = 0;
	int minimoTemporario = *(vetor);

	for (int i = 0; i < num; i++){
		if (*(vetor + i) >= maximoTemporario){
			maximoTemporario = vetor[i];
		}
		else if (*(vetor + i) <= minimoTemporario){
			minimoTemporario = vetor[i];
		}
	}
	*max = maximoTemporario;
	*min = minimoTemporario;
}

//função normalization
void normalization(double *vetor, int minimo, int maximo, int num){
	int i = 0;

	for (i = 0; i < num; i++){
		*(vetor + i) = ((double)(*(vetor + i) - minimo) / (maximo - minimo));
	}
}

//função glcRight
void glcmRight(int **image, double *resultado){

	int i, j, **glcm_Right;

	glcm_Right = (int **)calloc(max_glcm, sizeof(int *));

	for (i = 0; i < max_glcm; i++){
		glcm_Right[i] = (int *)calloc(max_glcm, sizeof(int));
	}

	for (i = 0; i < max_glcm; i++){
		for (j = 0; j < max_glcm; j++){
			if (j != max_glcm){
				glcm_Right[image[i][j]][image[i][j + 1]]++;
			}
		}
	}

	glcmContraste(glcm_Right, resultado);
	glcmEnergia(glcm_Right, resultado);
	glcmHomogeneidade(glcm_Right, resultado);

	for (i = 0; i < max_glcm; i++){
		free(glcm_Right[i]);
	}

	free(glcm_Right);
}

//função glcmLeft
void glcmLeft(int **image, double *resultado){

	int i, j, **glcm_Left;

	glcm_Left = (int **)calloc(max_glcm, sizeof(int *));

	for (i = 0; i < max_glcm; i++){
		glcm_Left[i] = (int *)calloc(max_glcm, sizeof(int));
	}

	for (i = 0; i < max_glcm; i++){
		for (j = 0; j < max_glcm; j++){
			if (j != 0){
				glcm_Left[image[i][j]][image[i][j - 1]]++;
			}
		}
	}

	glcmContraste(glcm_Left, resultado);
	glcmEnergia(glcm_Left, resultado);
	glcmHomogeneidade(glcm_Left, resultado);

	for (i = 0; i < max_glcm; i++){
		free(glcm_Left[i]);
	}

	free(glcm_Left);
}

//função glcmUpper
void glcmUpper(int **image, double *resultado){

	int i, j, **glcm_Upper;

	glcm_Upper = (int **)calloc(max_glcm, sizeof(int *));

	for (i = 0; i < max_glcm; i++){
		glcm_Upper[i] = (int *)calloc(max_glcm, sizeof(int));
	}

	for (i = 0; i < max_glcm; i++){
		for (j = 0; j < max_glcm; j++){
			if (i != 0){
			glcm_Upper[image[i - 1][j]][image[i][j]]++;
			}
		}
	}

	glcmContraste(glcm_Upper, resultado);
	glcmEnergia(glcm_Upper, resultado);
	glcmHomogeneidade(glcm_Upper, resultado);

	for (i = 0; i < max_glcm; i++){
		free(glcm_Upper[i]);
	}

	free(glcm_Upper);
}

//função glcmBottom
void glcmBottom(int **image, double *resultado){

	int i, j, **glcm_Bottom;

	glcm_Bottom = (int **)calloc(max_glcm, sizeof(int *));

	for (i = 0; i < max_glcm; i++){
		glcm_Bottom[i] = (int *)calloc(max_glcm, sizeof(int));
	}

	for (i = 0; i < max_glcm; i++){
		for (j = 0; j < max_glcm; j++){
			if (i != max_glcm){
				glcm_Bottom[image[i + 1][j]][image[i][j]]++;
			}
		}
	}

	glcmContraste(glcm_Bottom, resultado);
	glcmEnergia(glcm_Bottom, resultado);
	glcmHomogeneidade(glcm_Bottom, resultado);

	for (i = 0; i < max_glcm; i++){
		free(glcm_Bottom[i]);
	}

	free(glcm_Bottom);
}

//função glcmUpperRight
void glcmUpperRight(int **imagem, double *resultado){

	int i, j, **glcm_direito_Upper;

	glcm_direito_Upper = (int **)calloc(max_glcm, sizeof(int *));

	for (i = 0; i < max_glcm; i++){
		glcm_direito_Upper[i] = (int *)calloc(max_glcm, sizeof(int));
	}

	for (i = 0; i < max_glcm; i++){
		for (j = 0; j < max_glcm; j++){
			if ((i != 0) && (j != max_glcm)){
				glcm_direito_Upper[imagem[i - 1][j]][imagem[i][j + 1]]++;
			}
		}
	}

	glcmContraste(glcm_direito_Upper, resultado);
	glcmEnergia(glcm_direito_Upper, resultado);
	glcmHomogeneidade(glcm_direito_Upper, resultado);

	for (i = 0; i < max_glcm; i++){
		free(glcm_direito_Upper[i]);
	}

	free(glcm_direito_Upper);
}

//função glcmUpperLeft
void glcmUpperLeft(int **imagem, double *resultado){

	int i, j, **glcm_Left_Upper;

	glcm_Left_Upper = (int **)calloc(max_glcm, sizeof(int *));

	for (i = 0; i < max_glcm; i++){
		glcm_Left_Upper[i] = (int *)calloc(max_glcm, sizeof(int));
	}

	for (i = 0; i < max_glcm; i++){
		for (j = 0; j < max_glcm; j++){
			if ((i != 0) && (j != 0)){
				glcm_Left_Upper[imagem[i - 1][j]][imagem[i][j - 1]]++;
			}
		}
	}

	glcmContraste(glcm_Left_Upper, resultado);
	glcmEnergia(glcm_Left_Upper, resultado);
	glcmHomogeneidade(glcm_Left_Upper, resultado);

	for (i = 0; i < max_glcm; i++){
		free(glcm_Left_Upper[i]);
	}

	free(glcm_Left_Upper);
}


//função glcmBottomLeft
void glcmBottomLeft(int **imagem, double *resultado){

	int i, j, **glcm_Left_Bottom;

	glcm_Left_Bottom = (int **)calloc(max_glcm, sizeof(int *));

	for (i = 0; i < max_glcm; i++){
		glcm_Left_Bottom[i] = (int *)calloc(max_glcm, sizeof(int));
	}

	for (i = 0; i < max_glcm; i++){
		for (j = 0; j < max_glcm; j++){
			if ((i != max_glcm) && (j != 0)){
				glcm_Left_Bottom[imagem[i + 1][j]][imagem[i][j - 1]]++;
			}
		}
	}

	glcmContraste(glcm_Left_Bottom, resultado);
	glcmEnergia(glcm_Left_Bottom, resultado);
	glcmHomogeneidade(glcm_Left_Bottom, resultado);

	for (i = 0; i < max_glcm; i++){
		free(glcm_Left_Bottom[i]);
	}

	free(glcm_Left_Bottom);
}

//função glcmBottomDireito
void glcmBottomDireito(int **imagem, double *resultado){

	int i, j, **glcm_direito_Bottom;

	glcm_direito_Bottom = (int **)calloc(max_glcm, sizeof(int *));

	for (i = 0; i < max_glcm; i++){
		glcm_direito_Bottom[i] = (int *)calloc(max_glcm, sizeof(int));
	}

	for (i = 0; i < max_glcm; i++){
		for (j = 0; j < max_glcm; j++){
			if ((i != max_glcm) && (j != max_glcm)){
				glcm_direito_Bottom[imagem[i + 1][j]][imagem[i][j + 1]]++;
			}
		}

		glcmContraste(glcm_direito_Bottom, resultado);
		glcmEnergia(glcm_direito_Bottom, resultado);
		glcmHomogeneidade(glcm_direito_Bottom, resultado);

		for (i = 0; i < max_glcm; i++){
			free(glcm_direito_Bottom[i]);
		}

		free(glcm_direito_Bottom);
	}
}

//função glcmEnergia
void glcmEnergia(int **matrizglcm, double *resultado){
	int i, j;
	double energia = 0;

	for (i = 0; i < max_glcm; i++){
		for (j = 0; j < max_glcm; j++){
			energia += (matrizglcm[i][j] * matrizglcm[i][j]);
		}
	}

	for (i = 0; i < result_glcm; i++){
		if (resultado[i] == 0){
			resultado[i] = energia;
			break;
		}
	}
}

//função glcmHomogeneidade
void glcmHomogeneidade(int **matrizglcm, double *resultado){

	int i, j;
	double aux = 0, homogeneidade = 0;

	for (i = 0; i < max_glcm; i++){
		for (j = 0; j < max_glcm; j++){
			if ((i - j) != -1){
				aux = ((double)matrizglcm[i][j] / (double)(1 + (i - j)));
				homogeneidade += aux;
			}
		}
	}

	for (i = 0; i < result_glcm; i++){
		if (resultado[i] == 0){
			resultado[i] = homogeneidade;
			break;
		}
	}
}

//função glcmContraste
void glcmContraste(int **matrizglcm, double *resultado){

	int i, j;
	double contraste = 0;

	for (i = 0; i < max_glcm; i++){
		for (j = 0; j < max_glcm; j++){
			contraste += ((i - j) * (i - j)) * matrizglcm[i][j];
		}
	}

	for (i = 0; i < result_glcm; i++){
		if (resultado[i] == 0){
			resultado[i] = contraste;
			break;
		}
	}
}

//função glcmCompleto
void glcmCompleto(int **imagem, double *resultado){

	glcmRight(imagem, resultado);
	glcmLeft(imagem, resultado);
	glcmUpper(imagem, resultado);
	glcmBottom(imagem, resultado);
	glcmUpperRight(imagem, resultado);
	glcmUpperLeft(imagem, resultado);
	glcmBottomDireito(imagem, resultado);
	glcmBottomLeft(imagem, resultado);
}

//função vetorIlbp
void vetorIlbp(int **imagem, double *ilbp){

	int **matriz3x3;
	int i, j, menorDecimal;
	matriz3x3 = (int **)calloc(3, sizeof(int *));

	for (i = 0; i < 3; i++){
		matriz3x3[i] = (int *)calloc(3, sizeof(int));
	}

	for (i = 0; i < 1025; i++){
		for (j = 0; j < 1025; j++){
			if ((i != 0) && (i != 1024) && (j != 0) && (j != 1024)){
				matriz3x3[0][0] = imagem[i - 1][j - 1];
				matriz3x3[0][1] = imagem[i - 1][j];
				matriz3x3[0][2] = imagem[i - 1][j + 1];
				matriz3x3[1][0] = imagem[i][j - 1];
				matriz3x3[1][1] = imagem[i][j];
				matriz3x3[1][2] = imagem[i][j + 1];
				matriz3x3[2][0] = imagem[i + 1][j - 1];
				matriz3x3[2][1] = imagem[i + 1][j];
				matriz3x3[2][2] = imagem[i + 1][j + 1];

				menorDecimal = lowerDecimalNumber(comparaMedia(matriz3x3));

				ilbp[menorDecimal]++;
			}
		}
	}

	for (i = 0; i < 3; i++){
		free(matriz3x3[i]);
	}

	free(matriz3x3);
}

// função lowerDecimalNumber
int lowerDecimalNumber(int decimal){
	int smaller = decimal;
	for (int i = 0; i < 9; i++){
		decimal = ((decimal >> 1) | (decimal << 8)) & 511;
		if (decimal < smaller){
			smaller = decimal;
		}
	}
	return smaller;
}

//função comparaMedia
int comparaMedia(int **matriz){

	int vetorbit[9];
	int media = 0, i, j, decimal = 0;

	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			media += matriz[i][j];
		}
	}

	media = media / 9;

	if (matriz[0][0] >= media){
		vetorbit[0] = 1;
	}
	else{
		vetorbit[0] = 0;
	}

	if (matriz[0][1] >= media){
		vetorbit[1] = 1;
	}
	else{
		vetorbit[1] = 0;
	}

	if (matriz[0][2] >= media){
		vetorbit[2] = 1;
	}
	else{
		vetorbit[2] = 0;
	}

	if (matriz[1][2] >= media){
		vetorbit[3] = 1;
	}
	else{
		vetorbit[3] = 0;
	}

	if (matriz[2][2] >= media){
		vetorbit[4] = 1;
	}
	else{
		vetorbit[4] = 0;
	}

	if (matriz[2][1] >= media){
		vetorbit[5] = 1;
	}
	else{
		vetorbit[5] = 0;
	}

	if (matriz[2][0] >= media){
		vetorbit[6] = 1;
	}
	else{
		vetorbit[6] = 0;
	}

	if (matriz[1][0] >= media){
		vetorbit[7] = 1;
	}
	else{
		vetorbit[7] = 0;
	}

	if (matriz[1][1] >= media){
		vetorbit[8] = 1;
	}
	else{
		vetorbit[8] = 0;
	}

	for (i = 0; i < 9; i++){
		decimal += vetorbit[i] * (pow((double)2, (double)i));
	}

	return decimal;
}


//função vetorMedia
int vetorMedia(int *vetor, int num){

	int media = 0, i;

	for (i = 0; i < num; i++){
		media += *(vetor + i);
	}

	media /= num;

	return media;
}


//função euclidianDistance
void euclidianDistance(double *mediaGrass, double *mediaAsphalt, double **resultados, double **listaDistancia){

	int i, j;
	double distancia = 0;

	for (i = 0; i < size_C; i++){
		for (j = 0; j < 2; j++){
			distancia += pow((resultados[i][j] - mediaGrass[i]), 2);
		}
		distancia = sqrt(distancia);
		listaDistancia[i][0] = distancia;
	}

	distancia = 0;

	for (i = 0; i < size_C; i++){
		for (j = 0; j < 2; j++){
			distancia += pow((resultados[i][j] - mediaAsphalt[i]), 2);
		}
		distancia = sqrt(distancia);
		listaDistancia[i][1] = distancia;
	}
}


//função mediaSet
void mediaSet(double **matriz, double *media){

	int i, j;
	double mediaTemp = 0;

	for (i = 0; i < VetResult; i++){
		for (j = 0; j < size_C; j++){
			mediaTemp += matriz[j][i];
		}
		media[i] = mediaTemp / 25;
	}
}

//função compareDistance
int compareDistance(double grass, double asphalt){
	if (grass < asphalt){
		return 1;
	}
	else{
		return 0;
	}
}

//função resetMetrics
void resetMetrics(double *ilbp, double *glcm){
	int i;

	for (i = 0; i < ILBP; i++){
		ilbp[i] = 0;
	}
	for (i = 0; i < result_glcm; i++){
		glcm[i] = 0;
	}
}
