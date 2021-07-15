#include <stdio.h>
#include <stdlib.h>


unsigned char IP_TABLE[64] = {
  58,50,42,34,26,18,10, 2,
  60,52,44,36,28,20,12, 4,
  62,54,46,38,30,22,14, 6,
  64,56,48,40,32,24,16, 8,
  57,49,41,33,25,17, 9, 1,
  59,51,43,35,27,19,11, 3,
  61,53,45,37,29,21,13, 5,
  63,55,47,39,31,23,15, 7
};

unsigned char EXPANSION_TABLE[48] = {
  32, 1, 2, 3, 4, 5,
   4, 5, 6, 7, 8, 9,
   8, 9,10,11,12,13,
  12,13,14,15,16,17,
  16,17,18,19,20,21,
  20,21,22,23,24,25,
  24,25,26,27,28,29,
  28,29,30,31,32, 1
};

unsigned char PC1_TABLE[56] = {
  57,49,41,33,25,17, 9,
   1,58,50,42,34,26,18,
  10, 2,59,51,43,35,27,
  19,11, 3,60,52,44,36,
  63,55,47,39,31,23,15,
   7,62,54,46,38,30,22,
  14, 6,61,53,45,37,29,
  21,13, 5,28,20,12, 4
};

unsigned int KEY_SHIFT_TABLE[16] = {
  1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

unsigned char KEY_SHIFT_1[56]={
    2,3,4,5,6,7,8,9,
    10,11,12,13,14,15,16,17,
    18,19,20,21,22,23,24,25,26,27,28,1,
    30,31,32,33,
    34,35,36,37,38,39,40,41,
    42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,29
};

unsigned char PC2_TABLE[48] = {
  14,17,11,24, 1, 5,
   3,28,15, 6,21,10,
  23,19,12, 4,26, 8,
  16, 7,27,20,13, 2,
  41,52,31,37,47,55,
  30,40,51,45,33,48,
  44,49,39,56,34,53,
  46,42,50,36,29,32
};

unsigned char S_GATES_TABLE[8][4][16] = {
  // S1
  { {14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7},
    { 0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8},
    { 4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0},
    {15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13}
  },
  // S2
  { {15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10},
    { 3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5},
    { 0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15},
    {13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9}
  },
	// S3
  { {10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8},
    {13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1},
    {13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7},
    { 1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12}
  },
	// S4
  { { 7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15},
    {13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9},
    {10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4},
    { 3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14}
  },
	// S5
  { { 2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9},
    {14,11,2 ,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6},
    { 4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14},
    {11, 8,12, 7, 1,14, 2,13, 6,15, 0 ,9,10, 4, 5, 3}
  },
	// S6
  { {12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11},
    {10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8},
    { 9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6},
    { 4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13}
  },
	// S7
  { { 4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1},
    {13, 0,11, 7, 4, 9, 1,10,14, 3, 5, 12,2,15, 8, 6},
    { 1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2},
    { 6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12}
  },
  // S8
	{ {13, 2, 8, 4, 6,15, 11,1,10, 9, 3,14, 5, 0,12, 7},
    { 1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2},
    { 7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8},
    { 2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11}
  },
};

unsigned char P_TABLE[32] = {
  16, 7,20,21,
  29,12,28,17,
   1,15,23,26,
   5,18,31,10,
   2, 8,24,14,
  32,27, 3, 9,
  19,13,30, 6,
  22,11, 4,25
};

unsigned char IP_INV_TABLE[64]={
  40, 8,48,16,56,24,64,32,
  39, 7,47,15,55,23,63,31,
  38, 6,46,14,54,22,62,30,
  37, 5,45,13,53,21,61,29,
  36, 4,44,12,52,20,60,28,
  35, 3,43,11,51,19,59,27,
  34, 2,42,10,50,18,58,26,
  33, 1,41, 9,49,17,57,25
};

void print_byte_as_bits(char val) {
    int i;
  for (i = 7; 0 <= i; i--) {
    printf("%c", (val & (1 << i)) ? '1' : '0');
  }

}

void imprimir_debug(unsigned char* text, unsigned char *datos, int len) {
  int i;
  printf("%s ", text);
  for (i=0; i<len; i++) {
    printf("%02X ", datos[i]);
  }
  printf("\n");
}

int ascii_to_hex(char c)
{
        int num = (int) c;
        if(num < 58 && num > 47)
        {
                return num - 48;
        }
        if(num < 103 && num > 96)
        {
                return num - 87;
        }
        return num;
}

int permutacion(unsigned char matriz[],char fragmento[], int size_matrix, char frase[]){

        int i,j=0,p_bit=0,bt=0,p_letra=0;

        for(i=0;i<=((size_matrix/8)-1);i++){

            for(;;j++){
                p_bit=(matriz[j]-1)%8;        //posicion del bit
                p_letra=(matriz[j]-1)/8;      //posicion de la letra
                bt=frase[p_letra]>>(7-p_bit);       //desplazamos el bit que nos interesa a la posicion del bit menos significativo
                bt=bt& 0b00000001;
                bt=bt<<(7-(j%8));
                fragmento[i]=fragmento[i]|bt;
                if(j%8==7) break;               //cada 8 iteraciones salimos del for
            }
        j++;

    }
}

int s(char R[],char foo[],unsigned char S_GATES_TABLE[][4][16]){
    int i,x,mascara=0,mascara_ant=0,fila=0,columna=0,ciclo=0;
    for(i=0;i<=7;i++){

           x=i%4;   //los bits que hay que coger en la posicion 0 son los mismos que hay que coger en la 4
           if(x==0){
                mascara=252;
                columna=(foo[i-ciclo]&mascara)>>2;
                fila=(columna& 0b00100001)%10;
                columna=(columna & 0b00011110)>>1;
                R[i/2]=R[i/2] | ((S_GATES_TABLE[i][fila][columna])<<4);
                continue;   //siguiente iteracion del ciclo
           }
           mascara=(-18)*x*x*x+36*x*x-30*x+252; //ecuacion (no le des muchas vueltas), funciona para el resto de casos
           mascara_ant=((float)(9*x*x*x)/2)-9*x*x+((float)(15*x)/2);    //otra ecuacion, lo mismo que la anterior
           columna=(foo[(i-1)-ciclo]&mascara_ant)<<(6-2*x)|(foo[i-ciclo]&mascara)>>((-4)*x*x+14*x-6);
           fila=(columna & 0b00100001)%10;
           columna=(columna & 0b00011110)>>1;
           R[i/2]=R[i/2] | ((S_GATES_TABLE[i][fila][columna])<<((1-(x%2))*4));

           if(i==3) ciclo+=1;   //cuando llegamos a la segunda mitad los datos que hay que coger estan una posicion mas atras con respecto a la posicion del resultado en la que estemos

    }
}

int main(int argc,char* argv[])
{
    char fragmento[8]={0x00}, R[4]={0x00}, L[4]={0x00}, Raux[4]={0x00},foo[7]={0x00},nkey[7]={0x00},permkey[7]={0x00},fragmento_final[8]={0x00};
    int i,iteracion,shift=0,contadoor;
    unsigned char endes='e',c1,c2;
    unsigned char key[8], frase[50];
    FILE *fp = fopen("datos.txt","r");
    FILE *fc = fopen("mensaje.txt","r+");
    if(endes=='e'){
        for(i=0;;i++){
            if(i<8){
                c1=fgetc(fp);
                fputc(c1, fc);
                c1=ascii_to_hex(c1);
                c2=fgetc(fp);
                fputc(c2, fc);
                c2=ascii_to_hex(c2);
                if((c2&0b00000001)==0x00)    c2+=1; //correcion paridad
                key[i]= c1<<4 | c2;
            }
            else if (feof(fp))  break;
            else    {
                    c1=ascii_to_hex(fgetc(fp));
                    c2=ascii_to_hex(fgetc(fp)) ;
                    frase[i-8]=c1<<4 | c2;
            }
        }
    }

    imprimir_debug("datos -->", frase, 8);
    if(endes=='d'){
        for(i=0;;i++){
            if(i<8){
                c1=ascii_to_hex(fgetc(fc));
                c2=ascii_to_hex(fgetc(fc));
                key[i]= c1<<4 | c2;
            }
            else if (feof(fc))  break;
            else    frase[i-8]=fgetc(fc);
        }
    }
    imprimir_debug("key -->", key, 8);
    permutacion(PC1_TABLE,permkey,sizeof(PC1_TABLE),key);
    permutacion(IP_TABLE,fragmento,sizeof(IP_TABLE),frase);

   for(i=0;i<=7;i++){
        if(i<=3) L[i]=fragmento[i];

        if(i>=4) R[i-4]=fragmento[i];

        if(i<=6) foo[i]=0x00;
   }
   for(iteracion=0;iteracion<=15;iteracion++){     //ciclo de 16 iteraciones
        if(endes=='e')  for(i=0;i<=iteracion;i++)    shift+=KEY_SHIFT_TABLE[i];
        else if(endes=='d') for(i=0;i<=(15-iteracion);i++)    shift+=KEY_SHIFT_TABLE[i];
        for(i=0;i<=6;i++)   nkey[i]=permkey[i];
        for(contadoor=1;contadoor<=shift;contadoor++){
            permutacion(KEY_SHIFT_1,foo,sizeof(KEY_SHIFT_1),nkey);
            for(i=0;i<=6;i++)   {
                    nkey[i]=foo[i];
                    foo[i]=0x00;
            }
        }
        permutacion(PC2_TABLE,foo,sizeof(PC2_TABLE),nkey);
        for(i=0;i<=6;i++)   {
                    nkey[i]=foo[i];
                    foo[i]=0x00;
            }
        imprimir_debug("Key perm -->", nkey, 6);
        for(i=0;i<=3;i++)   Raux[i]=R[i];   //guardamos el valor de R
        permutacion(EXPANSION_TABLE,foo,sizeof(EXPANSION_TABLE),R); //R es el dato y foo el resultado
        for(i=0;i<=5;i++)   foo[i]=foo[i]^nkey[i];  //XOR con la clave
        for(i=0;i<=3;i++)   R[i]=0x00;  //Puertas S->foo es el dato y R es la salida
        s(R,foo,S_GATES_TABLE); //datos en foo, resultado en R
        for(i=0;i<=5;i++)   foo[i]=0x00;
        permutacion(P_TABLE,foo,sizeof(P_TABLE),R); //R es el dato y foo el resultado
        for(i=0;i<=3;i++)   R[i]=L[i]^foo[i];   //segunda XOR
        for(i=0;i<=3;i++)   L[i]=Raux[i];
        if(iteracion<=14)for(i=0;i<=5;i++)   nkey[i]=0x00;  //a partir de aqui, reinicializacion de variables
        for(i=0;i<=6;i++)   foo[i]=0x00;
        shift=0;
   }

   for(i=0;i<=7;i++){

        if(i<=3) fragmento[i]=R[i]; //intercambiamos L y R de posicion

        else fragmento[i]=L[i-4];
   }
   permutacion(IP_INV_TABLE,fragmento_final,sizeof(IP_INV_TABLE),fragmento);


   printf("mensaje cifrado: ");
   for(i=0;i<=7;i++)    print_byte_as_bits(fragmento_final[i]);
   printf("\n");
   printf("clave: ");
   for(i=0;i<=5;i++)    print_byte_as_bits(nkey[i]);
   printf("\n");
   if(endes=='d'){
        printf("mensaje: %s \n",fragmento_final);   //escribe el mensaje original
        fclose(fc);
   }
   if(endes=='e')   for(i=0;i<=7;i++)   fputc(fragmento_final[i], fc);
}
