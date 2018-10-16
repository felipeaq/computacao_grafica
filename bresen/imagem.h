#include <vector>
#include <tuple>
#include <iostream>

using namespace std;

class Imagem{
public:
  Imagem(string tipo, int M, int N, int max, vector<vector <tuple <int,int,int> > >img);
  Imagem();
  ~Imagem();
  static Imagem leitor(string arquivo);
  static Imagem gerador_aleatorio (int M, int N, int max);
  static Imagem degrade(int M, int N, int max,int cor);
  static Imagem arco(int M, int N, int max);
  void line_fast(int x1, int y1, int x2, int y2, tuple<int,int,int> color);
  static Imagem leitor_labirinto(string arquivo,Imagem cerca, Imagem livre);
  static void sem_shape(vector<vector <tuple <int,int,int> > > &img,string simbol,int N);
  static void com_shape(vector<vector <tuple <int,int,int> > > &img,string simbol,int N,Imagem cerca, Imagem livre);
  void salvar_imagem(string saida);
  void inverter_cor();
  void plot_pixel(int px, int py, tuple<int,int,int> color);
  void drawcircle(int x0, int y0, int radius,tuple<int,int,int> color);


private:
  string tipo;
  int N;
  int M;

  int max;

  vector<vector <tuple <int,int,int> > >img;


};
