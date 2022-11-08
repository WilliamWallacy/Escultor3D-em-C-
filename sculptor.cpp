#include "voxel.h"
#include "sculptor.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz){
  nx = _nx;
  ny = _ny;
  nz = _nz;
  r = 1;
  g = 1;
  b = 1;
  
  int i, j;
  
  /* Alocação dinâmica da matriz 3D */
  v = new Voxel**[nx];
  for (i = 0; i < nx; i++){
    v[i] = new Voxel*[ny];
    for (j = 0; j < ny; j++){
      v[i][j]= new Voxel[nz];
    }
  }
}


Sculptor::~Sculptor(){
  for(int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      delete[] v[i][j];
    }
  }
  for (int i=0; i <nx; i++){
    delete[] v[i];
  }
  
  delete[] v;
  
  /* Resetando coordenadas */
  nx = 0; ny = 0; nz = 0;
}

void Sculptor::setColor(float r, float g, float b, float a){
  Sculptor::r = r; 
  Sculptor::g = g; 
  Sculptor::b = b; 
  Sculptor::a = a;
}

void Sculptor::putVoxel(int x, int y, int z){
  if((this -> nx > x) && (this -> ny > y) && (this -> nz > z)){
    this -> v[x][y][z].isOn = true; 
  
    /* Repassa cor e transparencia do voxel */
    this -> v[x][y][z].r = r;
    this -> v[x][y][z].g = g;
    this -> v[x][y][z].b = b;
    this -> v[x][y][z].a = a;    
  }
}
void Sculptor::cutVoxel(int x, int y, int z){
  if((this -> nx > x) && (this -> ny > y) && (this -> nz > z)){
  this -> v[x][y][z].isOn = false;
  }
}

//Desativa o voxel na posição (x,y,z) (fazendo isOn = false)

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
  /* Define uma sequencia de voxel */
	for(int x = x0; x < x1; x++){
    for(int y = y0; y < y1; y++){
      for(int z = z0; z < z1; z++){
        v[x][y][z].isOn=true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
      }
    }
  }  
}

//Ativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
  /* Desativa uma sequencia de voxel */
  for(int x = x0; x < x1; x++){
    for(int y = y0; y < y1; y++){
      for(int z = z0; z < z1; z++){
        v[x][y][z].isOn = false;
      }
    }
  }  
}

//Desativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1]

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
  /* Recebe as coordenadas e o raio da esfera */
  int i, j, k;
  
  for(i = -radius; i <= radius; i++){ /* Pecorre o diâmetro */
    for(j = -radius; j <= radius; j++){
      for(k = -radius; k <= radius; k++){ 
        if((i*i + j*j + k*k) < radius*radius){ /* condição da esfera */
          putVoxel(i+xcenter,j+ycenter,k+zcenter); /* Adiciona um voxel */
        }
      }
    }
  }
}

//Ativa todos os voxels que satisfazem à equação da esfera e atribui aos mesmos a cor atual de desenho (r,g,b,a)
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
  //Mesma lógica do putSphere, mas ao invés de ativar o voxel, ele desativa a esfera
  int i, j, k;
	
  for(i = -radius; i < radius; i++){
    for(j = -radius; j < radius; j++){
      for(k = -radius; k < radius; k++){
        if((i*i + j*j + k*k) < radius*radius){
          cutVoxel(i+xcenter,j+ycenter,k+zcenter);
        }
      }
    }
  }
}

//Desativa todos os voxels que satisfazem à equação da esfera

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
  /* Define uma elipsoide */
  /* Recebe as coordenadas das dimensões e coordenadas do centro */
  float newx, newy, newz;
  int x, y, z;

  for ( x = 0; x < nx; x++){
    for ( y = 0; y < ny; y++){
      for ( z = 0; z < nz; z++){
        newx = ((float)(x-xcenter)*(float)(x-xcenter))/(rx * rx);
        newy = ((float)(y-ycenter)*(float)(y-ycenter))/(ry * ry);
        newz = ((float)(z-zcenter)*(float)(z-zcenter))/(rz * rz);
        
  /* Cálculo da condição de existência da elipsoide */
        if ((newx + newy + newz) < 1){
        putVoxel(x,y,z);
        }
      }
    }
  }
}


//Ativa todos os voxels que satisfazem à equação do elipsóide e atribui aos mesmos a cor atual de desenho

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
   /* Desativa a elipsoide */
   double newx, newy, newz;
   int x, y, z;
   
  for(x = 0; x < nx; x++){
    for(y = 0; y < ny; y++){
      for(z = 0; z < nz; z++){
        newx = ((float)(x-xcenter)*(float)(x-xcenter))/(rx * rx);
        newy = ((float)(y-ycenter)*(float)(y-ycenter))/(ry * ry);
        newz = ((float)(z-zcenter)*(float)(z-zcenter))/(rz * rz);

        if((newx + newy + newz) < 1){
          cutVoxel(x,y,z);
        }
      }
    }
  }
}

//Desativa todos os voxels que satisfazem à equação do elipsóide

void Sculptor::writeOFF(const char* filename){
  int qtd_Voxel = 0;
  int ref;
  int i, j, k, a, b, c; //auxiliares
  float fix = 0.5;
  
  std::ofstream endArq;
  
  endArq.open(filename);
  
  if(endArq.is_open()){
    endArq<<"OFF\n"; /* Define off na primeira linha */

    /* Percorre todas as dimensoes verificando os voxel em exibiçao */
    for (i = 0; i < nx; i++){
      for (j = 0; j <ny; j++){
        for (k = 0; k <nz; k++){
          if(v[i][j][k].isOn == true){
            qtd_Voxel++; /* Guarda a quantidade de voxel ativos */
          }
        }
      }
    }
    endArq<<qtd_Voxel * 8<<" "<<qtd_Voxel * 6 << " " << "0" << "\n"; 
    /* Exibe a quantidade total de vértices, faces e arestas */

    /* Pecorre as posições a, b, c e exibe as coordenadas do voxel */
    /* No primeiro voxel o fix será o valor de referência */
    for (a = 0; a < nx; a++){
      for (b = 0; b < ny; b++){
        for (c = 0; c < nz; c++){
          if(v[a][b][c].isOn == true){
            endArq << a - fix << " " << b + fix << " " << c - fix << "\n" << flush;
            endArq << a - fix << " " << b - fix << " " << c - fix << "\n" << flush;
            endArq << a + fix << " " << b - fix << " " << c - fix << "\n" << flush;
            endArq << a + fix << " " << b + fix << " " << c - fix << "\n" << flush;
            endArq << a - fix << " " << b + fix << " " << c + fix << "\n" << flush;
            endArq << a - fix << " " << b - fix << " " << c + fix << "\n" << flush;
            endArq << a + fix << " " << b - fix << " " << c + fix << "\n" << flush;
            endArq << a + fix << " " << b + fix << " " << c + fix << "\n" << flush;
          }
        }
      }
    }

    qtd_Voxel = 0; /* Reseta a quantidade de voxel */

    /* Percorre todas as dimensões */
    /* Verifica os voxel ativos e exibe as linhas com números de faces e as combinações que exibem a face */
    for(a = 0; a < nx; a++){
      for(b = 0; b < ny; b++){
        for(c = 0; c < nz; c++){
          if(v[a][b][c].isOn == true){
            ref = qtd_Voxel * 8;
            endArq << fixed;

            /* Construir linha que monta as faces a partir do vértices: */
            /* Valores exemplos do site quando ref = 0: */
            endArq << "4" << " " << 0+ref << " " << 3+ref << " " << 2+ref << " " << 1+ref << " ";
            /* Exibindo propriedades do voxel: */
            endArq << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";
            endArq << "4" << " " << 4+ref << " " << 5+ref << " " << 6+ref << " " << 7+ref << " ";
            endArq << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";
            endArq << "4" << " " << 0+ref << " " << 1+ref << " " << 5+ref << " " << 4+ref << " ";
            endArq << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";
            endArq << "4" << " " << 0+ref << " " << 4+ref << " " << 7+ref << " " << 3+ref << " ";
            endArq << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";
            endArq << "4" << " " << 3+ref << " " << 7+ref << " " << 6+ref << " " << 2+ref << " ";
            endArq << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";
            endArq << "4" << " " << 1+ref << " " << 2+ref << " " << 6+ref << " " << 5+ref << " ";
            endArq << setprecision(2)<<v[a][b][c].r << " " << setprecision(2)<<v[a][b][c].g <<" " << setprecision(2)<<v[a][b][c].b << " " << setprecision(2) << v[a][b][c].a << "\n";

            qtd_Voxel++; /* Incrementa a quantidade de voxels */
            }
          }
        }
      }
    }
  else{
    cout << "Erro ao abrir arquivo de texto."; 
  }
    
  endArq.close();
}

/* Grava a escultura no formato OFF no arquivo filename */
