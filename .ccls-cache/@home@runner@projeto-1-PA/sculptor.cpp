#include "sculptor.h"
#include <fstream> // std::ofstream
#include <iostream> // std::cout
#include <iomanip> // std::setprecision

Sculptor::Sculptor(int _nx, int _ny, int _nz){
  nx = _nx; ny = _ny; nz = _nz;
  // alocar memória
  int i, j;
  v = new Voxel**[nx];
  for(i=0; i<nx; i++){
    v[i] = new Voxel*[ny];
    for(j=0; j<ny; j++){
      v[i][j] = new Voxel[nz];
    }
  }
  
  if (v == NULL || v[0] == NULL || v[0][0] == NULL){
    std::cout << "não alocou\n";
  }
}

Sculptor::~Sculptor(){
  // liberar memória
  delete []v[0][0];
  delete []v[0];
  delete []v;
}

void Sculptor::setColor(float r, float g, float b, float a){
  // definir cor
  this->r = r; this->g = g; this->b = b; this->a = a;
}

void Sculptor::putVoxel(int x, int y, int z){
  // Ativa o voxel na posição (x,y,z) (fazendo show = true) e atribui ao mesmo a cor atual de desenho
  v[x][y][z].r = r;
  v[x][y][z].g = g;
  v[x][y][z].b = b;
  v[x][y][z].a = a;
  v[x][y][z].show = true;
}

void Sculptor::cutVoxel(int x, int y, int z){
  v[x][y][z].show = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
  int i, j, k;
  for(i=x0; i<=x1; i++){
    for(j=y0; j<=y1; j++){
      for(k=z0; k<=z1; k++){
        if(i>=0 && j>=0 && k>=0 && i<nx && j<ny && k<nz){
          v[i][j][k].r = r;
          v[i][j][k].g = g;
          v[i][j][k].b = b;
          v[i][j][k].a = a;
          v[i][j][k].show = true;
        }
      }
    }
  }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
  int i, j, k;
  for(i=x0; i<=x1; i++){
    for(j=y0; j<=y1; j++){
      for(k=z0; k<=z1; k++){
        if(i>=0 && j>=0 && k>=0 && i<nx && j<ny && k<nz){
          v[i][j][k].show = false;
        }
      }
    }
  }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
  int i, j, k;
  for(i=xcenter-radius; i<=xcenter+radius; i++){
    for(j=ycenter-radius; j<=ycenter+radius; j++){
      for(k=zcenter-radius; k<=zcenter+radius; k++){
        if(i>=0 && j>=0 && k>=0 && i<nx && j<ny && k<nz){
          if(((i-xcenter)*(i-xcenter))+((j-ycenter)*(j-ycenter))+((k-zcenter)*(k-zcenter)) <= radius*radius){
            v[i][j][k].r = r;
            v[i][j][k].g = g;
            v[i][j][k].b = b;
            v[i][j][k].a = a;
            v[i][j][k].show = true;
          }
        }
      }
    }
  }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
  int i, j, k;
  for(i=xcenter-radius; i<=xcenter+radius; i++){
    for(j=ycenter-radius; j<=ycenter+radius; j++){
      for(k=zcenter-radius; k<=zcenter+radius; k++){
        if(i>=0 && j>=0 && k>=0 && i<nx && j<ny && k<nz){
          if(((i-xcenter)*(i-xcenter))+((j-ycenter)*(j-ycenter))+((k-zcenter)*(k-zcenter)) <= radius*radius){
            v[i][j][k].show = false;
          }
        }
      }
    }
  }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
  int i, j, k;
  for(i=xcenter-rx; i<=xcenter+rx; i++){
    for(j=ycenter-ry; j<=ycenter+ry; j++){
      for(k=zcenter-rz; k<=zcenter+rz; k++){
        if(i>=0 && j>=0 && k>=0 && i<nx && j<ny && k<nz){
          if((float((i-xcenter)*(i-xcenter))/(rx*rx))+(float((j-ycenter)*(j-ycenter))/(ry*ry))+(float((k-zcenter)*(k-zcenter))/(rz*rz)) <= 1){
            v[i][j][k].r = r;
            v[i][j][k].g = g;
            v[i][j][k].b = b;
            v[i][j][k].a = a;
            v[i][j][k].show = true;
          }
        }
      }
    }
  }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
  int i, j, k;
  for(i=xcenter-rx; i<=xcenter+rx; i++){
    for(j=ycenter-ry; j<=ycenter+ry; j++){
      for(k=zcenter-rz; k<=zcenter+rz; k++){
        if(i>=0 && j>=0 && k>=0 && i<nx && j<ny && k<nz){
          if((float((i-xcenter)*(i-xcenter))/(rx*rx))+(float((j-ycenter)*(j-ycenter))/(ry*ry))+(float((k-zcenter)*(k-zcenter))/(rz*rz)) <= 1){
            v[i][j][k].show = false;
          }
        }
      }
    }
  }
}

void Sculptor::writeOFF(const char* filename){
  // grava a escultura no formato OFF no arquivo filename

  // abre o arquivo de saida
  std::ofstream fout;
  fout.open(filename);
  if (!fout.is_open()){
    exit(0);
  }
  fout << "OFF\n";

  // contador de voxels
  int i, j, k, cont = 0;
  for(i=0; i<nx; i++){
    for(j=0; j<ny; j++){
      for(k=0; k<nz; k++){
        if(v[i][j][k].show == true){
          cont++;
        }
      }
    }
  }

  // voxels inuteis
  int *vx = new int[cont];
  int *vy = new int[cont];
  int *vz = new int[cont];

  for(i=0; i<cont; i++){
    vx[i] = 0;
    vy[i] = 0;
    vz[i] = 0;
  }
  
  int p = 0;
  for(i=0; i<nx; i++){
    for(j=0; j<ny; j++){
      for(k=0; k<nz; k++){
        if(i>0 && j>0 && k>0 && i<nx-1 && j<ny-1 && k<nz-1){
          if(v[i][j][k+1].show == true && v[i][j][k-1].show == true && v[i][j+1][k].show == true && v[i][j-1][k].show == true && v[i+1][j][k].show == true && v[i-1][j][k].show == true){
            vx[p] = i;
            vy[p] = j;
            vz[p] = k;
            p++;
          }
        }
      }
    }
  }

  // removendo os voxels inúteis
  for(i=0; i<cont; i++){
    if(vx[i] || vy[i] || vz[i]){
      v[vx[i]][vy[i]][vz[i]].show = false;
    }
  }
  delete []vx;
  delete []vy;
  delete []vz;

  // contador de voxels
  cont = 0;
  for(i=0; i<nx; i++){
    for(j=0; j<ny; j++){
      for(k=0; k<nz; k++){
        if(v[i][j][k].show == true){
          cont++;
        }
      }
    }
  }
  fout << cont*8 << " " << cont*6 << " " << 0 << std::endl;

  // escrever vertices
  float vertices[8][3] = {{-0.5, 0.5, -0.5},
                          {-0.5, -0.5, -0.5},
                          {0.5, -0.5, -0.5},
                          {0.5, 0.5, -0.5},
                          {-0.5, 0.5, 0.5},
                          {-0.5, -0.5, 0.5},
                          {0.5, -0.5, 0.5},
                          {0.5, 0.5, 0.5}};

  int z;
  for(i=0; i<nx; i++){
    for(j=0; j<ny; j++){
      for(k=0; k<nz; k++){
        if(v[i][j][k].show == true){
          for(z = 0; z < 8; z++){
            fout << vertices[z][0] + i << " " << vertices[z][1] + j << " " << vertices[z][2] + k << std::endl;
          }
        }
      }
    }
  }

  // escrever faces
  cont = 0;
  int c;
  for(i=0; i<nx; i++){
    for(j=0; j<ny; j++){
      for(k=0; k<nz; k++){
        if(v[i][j][k].show == true){
          r = v[i][j][k].r;
          g = v[i][j][k].g;
          b = v[i][j][k].b;
          a = v[i][j][k].a;
          c = 8*cont;
          cont++;
          fout << std::setprecision(1) << std::fixed;
          fout << "4 " << 0+c << " " << 3+c << " " << 2+c << " " << 1+c                  << " " << r << " " << g << " " << b << " " << a << "\n";
          fout << "4 " << 4+c << " " << 5+c << " " << 6+c << " " << 7+c                  << " " << r << " " << g << " " << b << " " << a << "\n";
          fout << "4 " << 0+c << " " << 1+c << " " << 5+c << " " << 4+c                  << " " << r << " " << g << " " << b << " " << a << "\n";
          fout << "4 " << 0+c << " " << 4+c << " " << 7+c << " " << 3+c                  << " " << r << " " << g << " " << b << " " << a << "\n";
          fout << "4 " << 3+c << " " << 7+c << " " << 6+c << " " << 2+c                  << " " << r << " " << g << " " << b << " " << a << "\n";
          fout << "4 " << 1+c << " " << 2+c << " " << 6+c << " " << 5+c                  << " " << r << " " << g << " " << b << " " << a << "\n";
        }
      }
    }
  }
}