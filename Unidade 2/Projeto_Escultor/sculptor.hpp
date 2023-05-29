#ifndef SCULPTOR_H
#define SCULPTOR_H
#include<string>

using namespace std;

struct Voxel {
  float r,g,b;//Gama de cores "r,g,b"
  float a;//"a" representa a tranparencia da cor para o voxel
  bool isOn;//Verdadeiro ou falso, incluso ou n�o incluso do voxel
};

class Sculptor{
private:
  int nx, ny, nz;//Dimens�es da matriz
  float r, g, b, a;//Serve para manipular as cores para cada parte do desenho que desejo colorir
  Voxel ***vox;//Matriz de 3 dimens�es para cria��o dos voxels. Como se cada ponteiro representasse uma dimens�o da matriz


public:
  Sculptor(int _nx, int _ny, int _nz);//Construtor reservando um espa�o na memoria
  ~Sculptor();//Destrutor
  void setColor(float r, float g, float b, float a);
  void putVoxel(int x, int y, int z);//Adicionar um voxel na determinada posi��o x,y,z
  void cutVoxel(int x, int y, int z);//Remover um voxel na determinada posi��o x,y,z
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);//Implementa uma serie de voxels em um espa�o determinado das cordenadas
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);//retira uma serie de voxels em um espa�o determinado das cordenadas
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);//Cria uma esfera
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);//Tira uma esfera
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);//Cria uma elipsoide
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);//Retira uma elipsoide
  void writeOFF(char* filename);//Fun��o para escrever o arquivo em .off
};
#endif
