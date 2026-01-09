#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "stdkey.h"
#include <stdlib.h>
#include <time.h>

int main(){
 srand(time(0));
 //variables de configuracion
 int th=13;//tamaño, horizontal
 int tv=23;//tamaño, verticl
 int tp=10000;//en microsegundos
 int cfd=1;//cantidad de freames para una detecion
 int cfb=100;//cantidad de freames para acion de la gravetat
 int cn=20;//cantidad de niveles
 char chr[2]={' ','T'};//caracteres de representacion
 
  //variables de configuracion de efectos
 int arcm=0;//0:sin arc; 1:arc en cada blocke; 2:arc en cada linea;
 bool term=0;//modo de ter activado o no
 bool termh=0;//modo de ter con el plus hard
 int terb=9;//numero base de ter
 int arcl=10;//cantidad de canvios
 int arca=1;//arc actual
 char arcb[arcl];//biblioteca para arc
 arcb[0]='X';
 arcb[1]='@';
 arcb[2]='#';
 arcb[3]='.';
 arcb[4]=',';
 arcb[5]='A';
 arcb[6]='B';
 arcb[7]='C';
 arcb[8]='+';
 arcb[9]='-';

 //variables de almacenamiento
 int cb=7, btv=4, bth=4;//cantidad de blockes i tama�o
 int cfbm=100;//cantidad de freames para acio de la gravetat, version modificable
 bool map[tv][th];//mapa que ve el usuario 0:vacio;1:blocke;
 bool mapr[tv][th];//mapa real 0:vacio;1:blocke;
 bool block[cb][btv][bth];//blockes disponibles

 //inicializacion de variables
 for(int a=0;a<tv;a++){
  for(int b=0;b<th;b++){
   mapr[a][b]=0;
   map[a][b]=0;
  }
 }
 for(int a=0;a<tv;a++){
  mapr[a][0]=1;
  mapr[a][th-1]=1;
 }
 for(int b=0;b<th;b++){
  mapr[tv-1][b]=1;
 }

 for(int a=0;a<cb;a++){
  for(int b=0;b<btv;b++){
   for(int c=0;c<bth;c++){
    block[a][b][c]=0;
   }
  }
 }
 //XX
 //XX
 block[0][1][1]=1;
 block[0][1][2]=1;
 block[0][2][1]=1;
 block[0][2][2]=1;
 //XXXX
 block[1][1][0]=1;
 block[1][1][1]=1;
 block[1][1][2]=1;
 block[1][1][3]=1;
 //X
 //XX
 // X
 block[2][0][0]=1;
 block[2][1][0]=1;
 block[2][1][1]=1;
 block[2][2][1]=1;
 // X
 //XX
 //X
 block[3][0][1]=1;
 block[3][1][0]=1;
 block[3][1][1]=1;
 block[3][2][0]=1;
 //X
 //XX
 //X
 block[4][0][0]=1;
 block[4][1][0]=1;
 block[4][1][1]=1;
 block[4][2][0]=1;
 //XXX
 //X
 block[5][0][0]=1;
 block[5][0][1]=1;
 block[5][0][2]=1;
 block[5][1][0]=1;
 //XXX
 //  X
 block[6][0][0]=1;
 block[6][0][1]=1;
 block[6][0][2]=1;
 block[6][1][2]=1;



 //ejecucion del juego
 int rot=0;//rotacion
 int fp[2]={0,0};//frames que faltan para una detecion //frames que faltan para acio de la gravetat
 int ubb[2]={0,1};//ubicacion del blocke en movimiento
 int bsa=rand()%cb;//blocke selecionado ahora
 bool blocku[btv][bth];//blocke en uso actual
 int ubba[2]={ubb[0],ubb[1]};//ubicacion del blocke en movimiento, ubicacion antigua

 int line=0;//lineas echas
 bool go=0;//game over


 if(term){
  for(int a=1;a<th-1;a++){
   int c=rand()%terb;
   for(int b=tv-2;b>tv-2-c;b--){
    if(((bool)(rand()%2))||(!(termh))){
     mapr[b][a]=1;
    }
   }
  }
 }
 while(true){
  //print tabla
   //volcar el map real a map
  for(int a=0;a<tv;a++){
   for(int b=0;b<th;b++){
    map[a][b]=mapr[a][b];
   }
  }
   //aplicando efectos a los otjetos en movimento
  for(int a=0;a<btv;a++){
   for(int b=0;b<bth;b++){
    blocku[a][b]=0;
   }
  }
  for(int a=0;a<btv;a++){
   for(int b=0;b<bth;b++){
    if(rot==0){blocku[a][b]=block[bsa][a][b];}
    if(rot==1){blocku[b][bth-a-1]=block[bsa][a][b];}
    if(rot==2){blocku[btv-a-1][bth-b-1]=block[bsa][a][b];}
    if(rot==3){blocku[btv-b-1][a]=block[bsa][a][b];}
   } 
  }
   //volcado de la figura en movimiento
  bool veri=1;
  for(int a=ubb[0];a<ubb[0]+btv;a++){
   for(int b=ubb[1];b<ubb[1]+bth;b++){
    if((!(((a>0)&&(a<tv))&&((b>0)&&(b<th))))&&(blocku[a-ubb[0]][b-ubb[1]])){
     veri=0;
    }
   }
  }
  if(veri){
   ubba[0]=ubb[0];
   ubba[1]=ubb[1];
  }else{
   ubb[0]=ubba[0];
   ubb[1]=ubba[1];
  }
  for(int a=ubb[0];a<ubb[0]+btv;a++){
   for(int b=ubb[1];b<ubb[1]+bth;b++){
    if(blocku[a-ubb[0]][b-ubb[1]]){
     if((map[a][b])&&(blocku[a-ubb[0]][b-ubb[1]])){go=1;}
     map[a][b]=(blocku[a-ubb[0]][b-ubb[1]])||(map[a][b]);
    }
   }
  }
   //print real
  printf("\e[1;1H\e[2J");
  for(int a=0;a<tv;a++){
   printf("\n");
   for(int b=0;b<th;b++){
    if(map[a][b]==0){printf("%c",chr[0]);}
    if(map[a][b]==1){printf("%c",chr[1]);}
   }
  }
  printf("%d\n",line);
  if(arcm==1){printf("ARC-B");}
  if(arcm==2){printf("ARC-L");}
  if(term){if(termh){printf(" TER-H");}else{printf("TER");}}
  printf("\n");
  if((kbhit())&&(fp[0]==0)){
   switch(getch()){
    case 'q':{
     printf("\e[1;1H\e[2J");
     exit(0);
    }break;
    case 'w':{
     rot++;
     rot=rot%4;
     bool blocku2[btv][bth];
     for(int a=0;a<btv;a++){
      for(int b=0;b<bth;b++){
       blocku2[a][b]=0;
      }
     }
     for(int a=0;a<btv;a++){
      for(int b=0;b<bth;b++){
       if(rot==0){blocku2[a][b]=block[bsa][a][b];}
       if(rot==1){blocku2[b][bth-a-1]=block[bsa][a][b];}
       if(rot==2){blocku2[btv-a-1][bth-b-1]=block[bsa][a][b];}
       if(rot==3){blocku2[btv-b-1][a]=block[bsa][a][b];}
      } 
     }
     int ver=0;//verificacion de no choque
     for(int a=ubb[0];a<ubb[0]+btv;a++){
      for(int b=ubb[1];b<ubb[1]+bth;b++){
       if(blocku2[a-ubb[0]][b-ubb[1]]){
        if(a>=tv){ver++;continue;}
        if(b>=th){ver++;continue;}
        if(a<0){ver++;continue;}
        if(b<0){ver++;continue;}
        if(mapr[a][b]){ver++;continue;}
       }
      }
     }
     if(ver!=0){
      rot--;
      if(rot<0){rot=3;}
     }
    }break;
    case 'a':{
     ubb[1]--;
     int ver=0;//verificacion de no choque
     for(int a=ubb[0];a<ubb[0]+btv;a++){
      for(int b=ubb[1];b<ubb[1]+bth;b++){
       if(blocku[a-ubb[0]][b-ubb[1]]){
        if(a>=tv){ver++;continue;}
        if(b>=th){ver++;continue;}
        if(a<0){ver++;continue;}
        if(b<0){ver++;continue;}
        if(mapr[a][b]){ver++;continue;}
       }
      }
     }
     if(ver!=0){
      ubb[1]++;
     }
    }break;
    case 'd':{
     ubb[1]++;
     int ver=0;//verificacion de no choque
     for(int a=ubb[0];a<ubb[0]+btv;a++){
      for(int b=ubb[1];b<ubb[1]+bth;b++){
       if(blocku[a-ubb[0]][b-ubb[1]]){
        if(a>=tv){ver++;continue;}
        if(b>=th){ver++;continue;}
        if(a<0){ver++;continue;}
        if(b<0){ver++;continue;}
        if(mapr[a][b]){ver++;continue;}
       }
      }
     }
     if(ver!=0){
      ubb[1]--;
     }
    }break;
    case 's':{
     cfbm=1;
    }break;
    case 'p':{
     printf("\n>PAUSA<\n");
     while(1){
      if((kbhit())&&(getch()=='p')){
       break;
      }
      if((kbhit())&&(getch()=='q')){
       printf("\e[1;1H\e[2J");
       exit(0);
      }
     }
    }break;
   };
  }
  if(fp[1]==0){
   ubb[0]++;
   //ssitema de detecion de actuacion de la gravedad
   int ver=0;//verificacion de no choque
   for(int a=ubb[0];a<ubb[0]+btv;a++){
    for(int b=ubb[1];b<ubb[1]+bth;b++){
     if(blocku[a-ubb[0]][b-ubb[1]]){
      if(a>=tv){ver++;continue;}
      if(b>=th){ver++;continue;}
      if(a<0){ver++;continue;}
      if(b<0){ver++;continue;}
      if(mapr[a][b]){ver++;continue;}
     }
    }
   }
   if(ver!=0){
    //ejecucion de la gravedad
    ubb[0]--;
    for(int a=ubb[0];a<ubb[0]+btv;a++){
     for(int b=ubb[1];b<ubb[1]+bth;b++){
      /*if(blocku[a-ubb[0]][b-ubb[1]]){
       mapr[a][b]=blocku[a-ubb[0]][b-ubb[1]];
      }*/
      mapr[a][b]=(blocku[a-ubb[0]][b-ubb[1]])||(mapr[a][b]);
     }
    }
    rot=0;
    ubb[0]=1;
    ubb[1]=1;
    cfbm=cfb;
    bsa=rand()%cb;
    if(arcm==1){
     chr[1]=arcb[arca];
     arca++;
     if(arca>=arcl){
      arca=0;
     }
    }
    //detecion de linea
    for(int a=0;a<tv-1;a++){
     int ver=0;
     for(int b=1;b<th-1;b++){
      if(mapr[a][b]){ver++;}
     }
     if(ver==th-2){
      line++;
      if(arcm==2){
       chr[1]=arcb[arca];
       arca++;
       arca=arca%arcl;
      }
      for(int b=1;b<th-1;b++){
       mapr[a][b]=0;
      }
      for(int c=a-1;c>=0;c--){
       for(int d=0;d<th;d++){
        if(!(mapr[c+1][d])){
         mapr[c+1][d]=mapr[c][d];
         mapr[c][d]=0;
        }
       }
      }
     }
    }
   }
  }
  //sistema de los tiempos
  fp[0]++;
  fp[1]++;
  if(fp[0]>=cfd){fp[0]=0;}
  if(fp[1]>=cfbm){fp[1]=0;}

  int ver=0;
  for(int b=1;b<th-1;b++){
   if(mapr[0][b]){ver++;}
  }
  if(ver>0){
   go=1;
  }
  if(go){
   printf("GAME OVER!\n");
   exit(0); 
  }
  usleep((tp/cn)*(cn-(line%cn)));
 }
 return 0;
}
