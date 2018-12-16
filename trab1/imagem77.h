#include <vector>
#include <tuple>
#include <iostream>

using namespace std;

class CompareDist
{
public:
    bool operator()(tuple<double,double,double,double,double,double,double,double,double> n1,
      tuple<double,double,double,double,double,double,double,double,double> n2);
};


class Imagem{
public:
  Imagem(string tipo, int M, int N, int max, vector<vector <tuple <int,int,int> > >img);
  Imagem(string tipo, int M, int N, int max, vector<vector <tuple <int,int,int> > >img,int posicao_objeto_x,int posicao_objeto_y);
  Imagem();
  ~Imagem();
  static Imagem leitor(string arquivo);
  static Imagem gerador_aleatorio (int M, int N, int max);
  static Imagem degrade(int M, int N, int max,int cor);
  static Imagem arco(int M, int N, int max);
  static Imagem leitor_bin  (string arquivo);
  static Imagem criador_obj  (string arquivo,int resolucao_x=1000, int resolucao_y=1000,int posicao_objeto_x=500,int posicao_objeto_y=500,double escala=600,double theta=0,double phi=0, double omega=0,double perspectiva=2.0,double l1=1, double l2=1, double l3=1);
  void line_fast(int x1, int y1, int x2, int y2, tuple<int,int,int> color);
  static Imagem leitor_labirinto(string arquivo,Imagem cerca, Imagem livre);
  static void sem_shape(vector<vector <tuple <int,int,int> > > &img,string simbol,int N);
  static void com_shape(vector<vector <tuple <int,int,int> > > &img,string simbol,int N,Imagem cerca, Imagem livre);
  void salvar_imagem(string saida);
  void salvar_imagem_bin(string saida);
  void inverter_cor();
  void plot_pixel(int px, int py, tuple<int,int,int> color);
  void drawcircle(int x0, int y0, int radius,tuple<int,int,int> color);
  void flood_fil(int px, int py,tuple<int,int,int> new_color);
  void fill_triangle(pair<int,int> p0, pair <int,int> p1, pair<int,int> p2,tuple<int,int,int> color);
  void line_fast_3d(float x1, float y1, float z1,float x2, float y2,float z2,float z0, tuple<int,int,int> color);
  bool verifica_limite(int px, int py);
  bool mesma_cor(int px,int py,tuple<int,int,int> old_color);
  static Imagem parser (string arquivo);
  void triangle3d(tuple<double,double,double,double,double,double,double,double,double>  triangle_to_draw,double z0,  double s,tuple <int,int,int> color,double l1, double l2, double l3);

  tuple<double,double,double,double,double,double,double,double,double> rotate(tuple<double,double,double> p1, tuple<double,double,double> p2, tuple<double,double,double> p3,double theta=0, double phi=0, double omega=0);

  double cross_product(tuple<double,double,double,double,double,double,double,double,double>  triangle_to_draw,double l1, double l2, double l3);


    //void Imagem::draw_triangle3d(tuple<double,double,double> p1,tuple<double,double,double> p2,
    //  tuple<double,double,double> p3 ,double z0, tuple<int,int,int> color, double s);

  void FTS(pair<int,int> P1, pair<int,int> P2, pair<int,int> P3, tuple<int,int,int> color);


private:
  string tipo;
  int N;
  int M;
  int height;
  int width;

  int max;
  pair <int,int> meio;
  vector<vector <tuple <int,int,int> > >img;


};



/*Imagem gerador=Imagem::gerador_aleatorio(20,10);
gerador.salvar_imagem("ex.ppm");
Imagem ex = Imagem::leitor("ex.ppm");
ex.inverter_cor();
ex.salvar_imagem("saida.ppm");

Imagem degrade=Imagem::degrade(254,  30);
degrade.salvar_imagem("degrade.ppm");
Imagem::arco(1024,  30).salvar_imagem("arco.ppm");*/
//Imagem bush= Imagem::leitor("bush.ppm");
//Imagem mato= Imagem::leitor("mato.ppm");

//Imagem branco;




//Imagem branco = Imagem::leitor("teste.ppm");

//cout<<endl<<endl;
//branco.fill_triangle(make_pair(10, 10),make_pair(20,10),make_pair(20,20),make_tuple(0,0,0));
//branco.salvar_imagem_bin("saida.ppm");

//Imagem binario=Imagem::leitor_bin("saida.ppm");

//binario.salvar_imagem("nao_binario.ppm");
//branco.line_fast(0, 0, 200, 200, make_tuple(0,0,0));


//branco.plot_pixel(branco.height-1, branco.this->width-1, make_tuple(0,0,0));
//branco.line_fast(100, 100, 100, 300, make_tuple(0,0,0));
//branco.line_fast(100, 100, 300, 100, make_tuple(0,0,0));
//branco.line_fast(100, 300, 300, 300, make_tuple(0,0,0));
//branco.line_fast(300, 100, 300, 300, make_tuple(0,0,0));
//branco.drawcircle(100,100,90, make_tuple(0,0,0));

//branco.flood_fil(200, 200, make_tuple(255,0,0));
//branco.flood_fil(150,150,make_tuple(0,255,0));
//branco.flood_fil(50,50,make_tuple(0,0,255));

//branco.flood_fil(150,2,make_tuple(255,255,0));
//branco.line_fast(0, 0, 200, 200, make_tuple(0,0,0));
//branco.line_fast_3d(100,-100,-100 , 100, -100, 100, 40, make_tuple(0,0,0) );
//branco.line_fast_3d(-100,-100,-100 , 100, -100, -100, 40, make_tuple(0,0,0) );
//branco.FTS(make_pair(10, 10),make_pair(10,20),make_pair(30,30),make_tuple(0,0,0));



//Imagem::leitor_labirinto("maze.txt",bush,mato).salvar_imagem("maze.ppm");
