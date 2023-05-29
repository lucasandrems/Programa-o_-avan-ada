#include "sculptor.hpp"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

//Construtor da classe
Sculptor::Sculptor(int _nx, int _ny, int _nz){//Finção construtiora -> recebe o numero maximo de dimensoes que vou utilizar

	this -> nx = _nx;
	this -> ny = _ny;
	this -> nz = _nz;
	this -> r = 0;
	this -> g = 0;
	this -> b = 0;
	this -> a = 0;

	vox = new Voxel**[_nx];
	for (int i=0; i< _nx; i++){

        vox[i] = new Voxel*[_ny];
        for (int j=0; j< _ny; j++){

            vox[i][j] = new Voxel[_nz];
            for (int k=0; k< _ny; k++){

                this -> vox[i][j][k].r=0;
                this -> vox[i][j][k].g=0;
                this -> vox[i][j][k].b=0;
                this -> vox[i][j][k].a=0;
                this -> vox[i][j][k].isOn=false;
            }
        }
	}
}

//Destrutor da classe
Sculptor::~Sculptor(){//Função destrutora da classe para liberar a memória
    for (int i=0; i< nx; i++){
        for (int j=0; j< ny; j++){
            delete [] vox[i][j];
        }
        delete [] vox[i];
    }
    delete [] vox;
}

//Definição das Funções:

//Define a cor atual de desenho.
void Sculptor::setColor(float r, float g, float b, float alpha){
    this -> r=r;
	this -> g=g;
	this -> b=b;
	this -> a=alpha;
}

//Ativa o voxel na posicao (x,y,z) (fazendo isOn = true) e atribui ao mesmo a cor atual de desenho
void Sculptor::putVoxel(int x, int y, int z){
    this -> vox[x][y][z].r = this -> r;
    this -> vox[x][y][z].g = this -> g;
    this -> vox[x][y][z].b = this -> b;
    this -> vox[x][y][z].a = this -> a;
    this -> vox[x][y][z].isOn =false;
}

//Desativa o voxel na posicao (x,y,z) (fazendo isOn = false)
void Sculptor::cutVoxel(int x, int y, int z){//Retira o voxel nas cordenadas que se deseja
    this -> vox[x][y][z].isOn = false;
}

//Ativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){//Adicionar yna quantidade de voxels em serie
    //Faz uma rerificação se o intervalo de entrada está dentro da dimensão
    x0 = (x0 < 0) ? 0 : x0;
    x1 = (x1 > this -> nx) ? this -> nx : x1;
    y0 = (y0 < 0) ? 0 : y0;
    y1 = (y1 > this -> ny) ? this -> ny : y1;
    z0 = (z0 < 0) ? 0 : z0;
    z1 = (z1 > this -> nz) ? this -> nz : z1;


    for (int i = x0; i<x1+1; i++){
        for (int j = y0; j<y1+1; j++){
            for (int k = z0; i<z1+1; k++){
                this -> putVoxel(i,j,k);
            }
        }
    }
}

//Desativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){//Não deixa visivel os voxels construidos pela putBox
    for (int i = x0; i<x1+1; i++){
        for (int j = y0; j<y1+1; j++){
            for (int k = z0; i<z1+1; k++){
                this -> cutVoxel(i,j,k);
            }
        }
    }
}

//Ativa todos os voxels que satisfazem a equacao da esfera e atribui aos mesmos a cor atual de desenho
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){//Cria uma esfera
    putEllipsoid(xcenter, ycenter, zcenter, radius, radius, radius);
}

//Desativa todos os voxels que satisfazem a equacao da esfera
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    cutEllipsoid(xcenter, ycenter, zcenter, radius, radius, radius);
}

//Ativa todos os voxels que satisfazem à equacao do elipsoide e atribui aos mesmos a cor atual de desenho
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){//Criador de uma elipse
    //Faz uma rerificação se o intervalo de entrada está dentro da dimensão, do centro até o raio
    int x0 = (xcenter - rx < 0) ? 0 : xcenter - rx;
    int x1 = (xcenter + rx > this -> nx) ? this -> nx : xcenter + rx;
    int y0 = (ycenter - ry < 0) ? 0 : ycenter - ry;
    int y1 = (ycenter + ry > this -> ny) ? this -> ny : ycenter + ry;
    int z0 = (zcenter - rz < 0) ? 0 : zcenter - rz;
    int z1 = (zcenter + rz > this -> nz) ? this -> nz : zcenter + rz;

    //Verifica se o centro da elipse mais/menos o raio estao dentro da elipse
    for(int i=0; i< rx; i++){
        for(int j=0; j< ry; j++){
            for(int k=0; k< rz; k++){
                //Equacao da elipse
                if (pow(i - xcenter, 2) / pow(rx, 2) + pow(j - ycenter, 2) / pow(ry, 2) + pow(k - zcenter, 2) / pow(rz, 2) < 1){
                    this -> putVoxel(i,j,k);
                }
            }
        }
    }
}

//Desativa todos os voxels que satisfazem a equacao do elipsoide
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){//Remove de uma elipse
    //Faz uma rerificação se o intervalo de entrada está dentro da dimensão, do centro até o raio
    int x0 = (xcenter - rx < 0) ? 0 : xcenter - rx;
    int x1 = (xcenter + rx > this -> nx) ? this -> nx : xcenter + rx;
    int y0 = (ycenter - ry < 0) ? 0 : ycenter - ry;
    int y1 = (ycenter + ry > this -> ny) ? this -> ny : ycenter + ry;
    int z0 = (zcenter - rz < 0) ? 0 : zcenter - rz;
    int z1 = (zcenter + rz > this -> nz) ? this -> nz : zcenter + rz;

    //Verifica se o centro da elipse mais/menos o raio estao dentro da elipse
    for(int i=0; i< rx; i++){
        for(int j=0; j< ry; j++){
            for(int k=0; k< rz; k++){
                if (pow(i - xcenter, 2) / pow(rx, 2) + pow(j - ycenter, 2) / pow(ry, 2) + pow(k - zcenter, 2) / pow(rz, 2) < 1){
                    this -> cutVoxel(i,j,k);
                }
            }
        }
    }
}

//Grava a escultura no formato OFF no arquivo filename
void Sculptor::writeOFF(char *filename){
    ofstream myFile(filename);

    if (!myFile.is_open()){
        cout << "Error while open file: "<< filename << endl;
        exit(1);
    }

    int vOn = 0, i, j, k;
    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
                if (this->vox[i][j][k].isOn){
                    vOn++;
                }
            }
        }
    }
    //Escrever em OFF
    myFile << "OFF" << endl;
    myFile << 8 * vOn << " " << 6 * vOn << "0" << endl;

    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
                if (this->vox[i][j][k].isOn){
                    myFile << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    myFile << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    myFile << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    myFile << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                    myFile << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    myFile << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    myFile << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    myFile << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                }
            }
        }
    }
    int index = 0;
    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
                if (this->vox[i][j][k].isOn){
                    myFile << 4 << " " << 0 + 8*index << " " << 3 + 8*index << " " << 2 + 8*index << " " << 1 + 8*i << " " << vox[i][j][k].r << " " << vox[i][j][k].g << " " << vox[i][j][k].b << " " << vox[i][j][k].a << " " << endl;
                    myFile << 4 << " " << 4 + 8*index << " " << 5 + 8*index << " " << 6 + 8*index << " " << 7 + 8*i << " " << vox[i][j][k].r << " " << vox[i][j][k].g << " " << vox[i][j][k].b << " " << vox[i][j][k].a << " " << endl;
                    myFile << 4 << " " << 0 + 8*index << " " << 1 + 8*index << " " << 5 + 8*index << " " << 4 + 8*i << " " << vox[i][j][k].r << " " << vox[i][j][k].g << " " << vox[i][j][k].b << " " << vox[i][j][k].a << " " << endl;
                    myFile << 4 << " " << 0 + 8*index << " " << 4 + 8*index << " " << 7 + 8*index << " " << 3 + 8*i << " " << vox[i][j][k].r << " " << vox[i][j][k].g << " " << vox[i][j][k].b << " " << vox[i][j][k].a << " " << endl;
                    myFile << 4 << " " << 3 + 8*index << " " << 7 + 8*index << " " << 6 + 8*index << " " << 2 + 8*i << " " << vox[i][j][k].r << " " << vox[i][j][k].g << " " << vox[i][j][k].b << " " << vox[i][j][k].a << " " << endl;
                    myFile << 4 << " " << 1 + 8*index << " " << 2 + 8*index << " " << 6 + 8*index << " " << 5 + 8*i << " " << vox[i][j][k].r << " " << vox[i][j][k].g << " " << vox[i][j][k].b << " " << vox[i][j][k].a << " " << endl;
                    index++;
                }
            }
        }
    }

    myFile.close();
}
