#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define MAX 15		
#define MAXHAMLE 50  
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define YELLOW 6
#define WHITE 7
#define MAX_SCORES 10

int numScores = 0;
int N;
char username[20];
int i,j,matris[MAX][MAX]={{0}};
int tahtalar[MAXHAMLE][MAX][MAX]={{0}};
char fileName[20];
int tahtaNo;
int undosayi=0;
int flag=1;
void drawBoard(int matris[][MAX], int N);
void readFromFile(int matris[][MAX], char *fileName);
void mainMenu();
void gameMenu();
void manueloyna(int matris[][MAX],int N,int tahtalar[][MAX][MAX],int *tahtaNo,int *undosayi);
void hareket(int matris[][MAX],int N,int tahtalar[][MAX][MAX],int *tahtaNo,int *undosayi);
void tahtadurumu(int N,int matris[][MAX],int *tahtaNo,int tahtalar[][MAX][MAX]);
void tahtaundo(int N,int matris[][MAX],int *tahtaNo,int tahtalar[][MAX][MAX],int *undosayi);
int hesaplama(int N,int *undosayi,int *tahtaNo);

typedef struct {				//SKOR TUTMAK ICIN OLUSTURDUGUM STRUCT
    char username[20];
    int score;
} Score;
Score scores[MAX_SCORES];

int main(){
	int bas;
	char username[20];
 	printf ("\t*** SAYI ESLESTIRME OYUNU ***\n");
    while (flag==1) {
        mainMenu();
        if (flag==1){
        printf("\n\nYeniden matris olusturmak icin 1 e devam etmek icin herhangi bir sayiya basabilirsiniz:");
        scanf("%d",&bas);
    }
        if(bas==1)
        mainMenu();
        
        if(flag==1)
        gameMenu();
        
        undosayi=0;
    	tahtaNo=0;
    }
  return 0;
}

void readFromFile(int matris[][MAX], char *fileName){
	int i,j, temp;
	FILE *data = fopen(fileName,"r");
	if(!data){
        printf("Dosya Acilamadi!");
		return;
    }
    while(!feof(data)){
        fscanf(data,"%d %d %d\n",&i,&j,&temp);  
		matris[i][j]=temp; 
    }  
  	fclose(data); 
}

void rastgele(int matris[][MAX]){			//RASTGELE MATRIS OLUSTURMA FONKSIYONU
	
	srand(time(NULL)); 
    printf("N sayisini giriniz: ");
    scanf("%d",&N);
    
    for (i = 0; i < N; i++) {                 //MATRIS SIFIRLAMA
        for (j = 0; j < N; j++) {
            matris[i][j] = 0;
        }
    }

    int sayi = 1;                             // SAYILARI IKISER KEZ YERLESTIRME
    while (sayi <= N) {
        int count = 0;
        while (count < 2) {
            i = rand() % N;
            j = rand() % N;
            if (matris[i][j] == 0) {
                matris[i][j] = sayi;
                count++;
            }
        }
        sayi++;
    }
    printf("\nRastgele Matris Olusturuldu.\n");
    drawBoard(matris,N);
}

void drawBoard(int matris[][MAX], int N) {					//TAHTAYI YAZDIRMA FONKSIYONU
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i, j, k;

    for (i = 0; i < N; i++) {
        printf("\n");
        for (k = 0; k < N; k++)
            printf("-------");
        printf("\n");
        for (j = 0; j < N; j++) {
            if (matris[i][j] != 0) {																		// R
                																							// E
                SetConsoleTextAttribute(hConsole, (BLACK << 4) | WHITE);									// N
                printf("  ");																				// K
                																							// L
                SetConsoleTextAttribute(hConsole, (BLACK << 4) | getColorFromNumber(matris[i][j]));			// E
                printf("%d", matris[i][j]);																	// N
                																							// D
                SetConsoleTextAttribute(hConsole, (BLACK << 4) | WHITE);									// I
                printf("   |");																				// R
            }																								// M
            else {																							// E
                
                SetConsoleTextAttribute(hConsole, (BLACK << 4) | WHITE);
                printf("      |");
            }
        }
    }
    SetConsoleTextAttribute(hConsole, (BLACK << 4) | WHITE);
}
int getColorFromNumber(int number) {			//RENKLENDIRME FONKSIYONU
    switch (number) {
    	case 1:
    		return BLUE;
        case 2:
            return GREEN;
        case 3:
    		return CYAN;
        case 4:
            return RED;
        case 5:
    		return MAGENTA;
    	case 6:
    		return YELLOW;
    	case 7:
    		return BLUE;
        case 8:
            return RED;
        default:
            return WHITE;
    }
}
void tahtadurumu(int N,int matris[][MAX],int *tahtaNo,int tahtalar[][MAX][MAX]){		//TAHTANIN DURUMUNU TAHTALAR MATRISINE KOPYALAYAN FONKSIYON
	(*tahtaNo)++;
	int a;
	a= *tahtaNo;
for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
        tahtalar[a][i][j] = matris[i][j];
    }
}
}

void tahtaundo(int N,int matris[][MAX],int *tahtaNo,int tahtalar[][MAX][MAX],int *undosayi){	//TAHTAYI BIR ONCEKI DURUMA ALMA FONKSIYONU
	int a;
	a= *tahtaNo;
	
	if (a >= 0) {
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            matris[i][j] = tahtalar[a][i][j];
        }
    }
}
drawBoard(matris,N);
(*undosayi)++;
}
void addScore(char* username, int score) {												//SKOR EKLEME FONKSIYONU
    if (numScores < MAX_SCORES) {
        strcpy(scores[numScores].username, username);
        scores[numScores].score = score;
        numScores++;
    }
}

void showScores() {										//SKORLARI YAZDIRMA FONKSIYONU
  
    for ( i = 0; i < numScores; i++) {
        printf("%s: %d\n", scores[i].username, scores[i].score);
    }
}

int hesaplama(int N,int *undosayi,int *tahtaNo){		//SKOR HESAPLAMA FONKSIYONU
	int score;
	int hamlesayisi=0;
	hamlesayisi= (*tahtaNo) + (*undosayi);
	
	score= (N*10) - 2*hamlesayisi - 3*(*undosayi);
	return score;
}

void mainMenu() {	
    int choice;
    int tahtaNo = 0;
    char fileName[20];
    printf("\nAna Menu\n");
    printf("1- Rastgele Matris Olustur\n");
    printf("2- Dosyadan Matris Olustur\n");
    printf("3- Kullanicilarin Skorlarini Goster\n");
    printf("4- Cikis\n");
    printf("\nSeciminiz: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            rastgele(matris);
            for (i = 0; i < N; i++) {					//TAHTANIN BASLANGICINI TAHTALAR MATRISINE ATMA
    		for (j = 0; j < N; j++) {
        tahtalar[0][i][j] = matris[i][j];
    }
}
            break;
        case 2:
        	
        	for (i = 0; i < N; i++) {                 //MATRIS SIFIRLAMA
        for (j = 0; j < N; j++) {
            matris[i][j] = 0;
        }
    }
            printf("\nN sayisini giriniz: ");
    		scanf("%d",&N);
            printf("Dosya Adini Giriniz:");
  		scanf("%s",fileName);
		readFromFile(matris, fileName);
		printf("\nDosyadan Matris Olusturuldu.\n");
		
		drawBoard(matris,N);
		for (i = 0; i < N; i++) {						//TAHTANIN BASLANGICINI TAHTALAR MATRISINE ATMA
    		for (j = 0; j < N; j++) {
        tahtalar[0][i][j] = matris[i][j];
    }
}
            break;
        case 3:
            printf("\nKullanicilarin Skorlari Gosteriliyor.\n");
            showScores();
            mainMenu();
            break;
        case 4:
            printf("\nProgramdan Cikiliyor.\n");
            flag=0;
            break;
        default:
            printf("\nGecersiz secim.\n");
            mainMenu();
            break;
    }
}

// Oyun men�s� fonksiyonu
void gameMenu() {
    int choice;
    int score;
    printf("\nOyun Menusu\n");
    printf("1- Manuel Modda Oyna\n");
    printf("2- Otomatik Modda Oyna\n");
    printf("3- Ana Menuye Don\n");
    printf("\nSeciminiz: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            printf("\nManuel Modda Oynuyorsunuz.\n");
            drawBoard(matris,N);
            manueloyna(matris,N,tahtalar, &tahtaNo, &undosayi);
            score=hesaplama(N,&undosayi,&tahtaNo);
            addScore(username,score);
            printf("\n");
            break;
        case 2:
            printf("\nOtomatik Mod Calismamaktadir.\n");
            gameMenu();
            break;
        case 3:
            printf("\nAna Menuye Donuluyor.\n");
            break;
        default:
            printf("\nGecersiz secim.\n");
            gameMenu();
            break;
    }
}

void manueloyna(int matris[][MAX],int N,int tahtalar[][MAX][MAX],int *tahtaNo,int *undosayi){
	int sayac=1;
	int cikis=0;
    printf("\n\nKullanici Adini Girin: ");
    scanf("%s", username);
	while(sayac!=0 && cikis==0){
		hareket(matris,N,tahtalar,tahtaNo,undosayi);
		sayac=0;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(matris[i][j]==0){
			sayac++;
		}
		}
	}
		
}
}

void hareket(int matris[][MAX],int N,int tahtalar[][MAX][MAX],int *tahtaNo,int *undosayi){
	int s1,s2,d1,d2;
	int ch,sayac,cikis;
	sayac=0;
	
	printf("\n\n1-Hamle yapmak icin 1 e basiniz\n2-Geri almak icin 2 ye basiniz\n\nSeciminiz: ");
	scanf("%d",&ch);
switch (ch) {

	case 1:
	do{ 
	printf("\n");
	printf("SADECE TEK SATIRDA VEYA TEK SUTUNDA HAREKET EDEBILIRSINIZ!!!");
	printf("\n\n");
	printf("Baslangic noktasinin satir degerini giriniz:");
	scanf("%d",&s1);
	printf("Baslangic noktasinin sutun degerini giriniz:");
	scanf("%d",&s2);
	
	printf("Varis noktasinin satir degerini giriniz:");
	scanf("%d",&d1);
	printf("Varis noktasinin sutun degerini giriniz:");
	scanf("%d",&d2);
	}while(s1-d1!=0 && s2-d2!=0);

	printf("Source:[%d][%d] Destination:[%d][%d]",s1,s2,d1,d2);

	if (s1==d1){ 
		if(s2<d2){ //saga
		i=s2+1;
	while(matris[s1][i]==matris[d1][d2]){
	if (matris[s1][i]==matris[d1][i-1]){
}
	else
	matris[s1][i]=matris[s1][i-1];
	i++;
	}
	}
	else  if (d2<s2){// sola
	i=s2-1;
	while(matris[s1][i]==matris[d1][d2]){
	if (matris[s1][i]==matris[d1][i+1]){
	}
	else
	matris[s1][i]=matris[s1][i+1];
	i--;
}
}
}
	else
	if(s1<d1){ //asagi
		i=s1+1;
	while(matris[i][s2]==matris[d1][d2]){
	if (matris[i][s2]==matris[i-1][d2]){
	}
	else
	matris[i][s2]=matris[i-1][d2];
	
	i++;
	}
}
	else if(d1<s1){ //yukari
			i=s1-1;
	while(matris[i][s2]==matris[d1][d2]){
	if (matris[i][s2]==matris[i+1][d2]){
	}
	else
	matris[i][s2]=matris[i+1][d2];
	
	i--;
	}
}

tahtadurumu(N,matris, tahtaNo ,tahtalar);
drawBoard(matris,N);
	break;
	
case 2:
	printf("UNDO ISLEMI YAPILIYOR");
	(*tahtaNo)--; 
tahtaundo(N,matris,tahtaNo,tahtalar,undosayi);
	break;
	
default:
            printf("\nGecersiz secim.\n");
            
            break;
    
}
}



