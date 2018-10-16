#include <vector>
#include <tuple>
#include <iostream>

using namespace std;

class Imagem{
public:
  Imagem(string tipo, int M, int N, int max, vector<vector <tuple <int,int,int> > >img);

  static Imagem leitor(string arquivo);
  static Imagem gerador_aleatorio (int M, int N, int max);
  static Imagem degrade(int M, int N, int max,int cor);
  static Imagem arco(int M, int N, int max);
  static Imagem leitor_labirinto(string arquivo,Imagem cerca, Imagem livre);
  static void sem_shape(vector<vector <tuple <int,int,int> > > &img,string simbol,int N);
  static void com_shape(vector<vector <tuple <int,int,int> > > &img,string simbol,int N,Imagem cerca, Imagem livre);
  void salvar_imagem(string saida);
  void inverter_cor();
  

private:
  string tipo;
  int N;
  int M;

  int max;

  vector<vector <tuple <int,int,int> > >img;


};
