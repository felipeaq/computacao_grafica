#include <vector>
#include <tuple>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#define TESTILU 


using namespace std;



struct vec3d{
  double x;// coordenada do ponto x
  double y;// coordenada do ponto y
  double z;// coordenada do ponto z

  vec3d(double x, double y, double z); //construtor que recebe as coordenadas x, y z
  vec3d(tuple<double,double,double,double,double,double,double,double,double>  ttd);// pega todos os pontos, transforma nas normais x,y,z
};





class Opengl_obj{ // classe"abstrata"que impplementa os atributos e métodos básicos de um objeto à ser desenhado.

public:
  GLuint textura; // carrega um valor da textura.
  vector<tuple<double,double,double,double,double,double,double,double,double> > triangle_to_draw;// vetor de coordenadas da relação ponto e face.

  double escala; // escala é o multiplicador do tamanho do objeto escolhido
  tuple <float,float,float> color; // cor padrão do objeto


  double theta,phi,omega, pos_x, pos_y,pos_z,red,green,blue,alpha; //são os ângulos de roltação do objeto, são as posições x, y, z do objeto e suas respectivas coordenadas de cores.

  vector<vec3d> normais;// vetor de normais de cada face do triângulo
  vector<vec3d> cores;//vetor de cores

  void triangle3d(int i); //método que dado uma posição em um vetor de objetos dE faces desenhando-a;

  Opengl_obj(vector<tuple<double,double,double,double,double,double,double,double,double> > triangle_to_draw,
    vector<vec3d> normais,
    tuple <float,float,float> color,double theta, double phi, double omega,
    double pos_x, double pos_y,double pos_z,double red, double green, double blue, double alpha,vector<vec3d> cores);
    void desenha_gl();//chama todo os valores de "i" pra o método triangle 3D. 
    virtual void main_rotine()=0;//'uma classe virtual abstrata que imlementa a rotina de cada tipo de objeto
    void rotate_ang(double offset, double &ang);//ele incremeta o angulo selecionado.
    //ele une todas as tuplas de coordenada de pontos da face do objeto
    static tuple<double,double,double,double,double,double,double,double,double> join_tuple(tuple<double,double,double> p1, tuple<double,double,double> p2, tuple<double,double,double> p3,double theta=0, double phi=0, double omega=0);

    Opengl_obj   (string arquivo,double pos_x,
    double pos_y, double pos_z,double theta,double phi,
    double omega,double red, double green, double blue, double alpha,string texture_file,double escala);//construtor que recebe arquivo e constroi apartir destes parâmetros

    bool collision(Opengl_obj* other);// é um métoddo que detécta a colusão de um objeto com outro objeto
    
    double tamanho; //é um atributo da classe 
    GLuint LoadTexture2( string filename); // método que carrega o arquivo de texturas para o objeto desejado


};



class Cena{ // classe que descreve os componentes de uma cena Opengl
public:

  Cena(double escala, double perspectiva); // construtor que reccebe uma escala de objeto e sua respectiva perspectiva.
  vector<Opengl_obj*> objs; //vetor com objetos da classe OpenGL_obj tudo que estiver dentro dela, será carreegada para a cena à cada frame.
  
  double perspectiva; // atribudo com o valor da perspectiva
  double escala;// escala do objeto
  void printtext(int x, int y, string text);// mostra o texto do placar do jogo
  void add_obj(Opengl_obj* obj);//adiciona um Opengl_obj no vetor de objetos à serem carregados
  void desenha_tudo();//desenha tudo que está dentro do vetor de objetos mediante sua posição em um vetor

};

class Jogador:public Opengl_obj{
  private:
  int velocidade;// velocidade e quantos píxels ele se move por frame.
  char up,down,left,right;// caracteres de direção
  
  public:
  int pontuacao;//pontuação do placar
  void pontuar();// método que incrementa +1 em pontução
  void set_vel(int vel);//seta a velocidade
  int moving_state_vertical;//caso ele seja -1 esta parado.
  int moving_state_horizontal;//caso ele seja -1, o jogador está parado, caso ele seja 0, ee vai para um lado caso seja 1 ele vai para o outro lado
  void main_rotine();//rotina responsável por movimentar o jogador dado o estado do teclado

  Jogador(string arquivo,double pos_x,
     double pos_y, double pos_z,double theta,double phi,
     double omega,double red, double green, double blue, double alpha,string texture_file,double escala,
     char up,char down,char left,char right,int velocidade); // construtor do jogador que se aproveita do construtor do Opengl_obj

  void set_chars(char up,char down,char left,char right); //define os caracteres pertencentes ao movimento do jogador
  bool contains_char(char c); // verifica se "c" é igual à up ou down ou left ou right ou seja se for um desses, ele verifica se tem o "char" nos atributos
  void move(char c); //ele seta o estado de movimento do jogador dado um char
  bool contains_vertical_char(char c); //ele verifica apenas para "up" e "down", assim como no contains char
  bool contains_horizontal_char(char c); //mesma coisa que o à cima. Ele verifica se existe algo no left ou right.

  string get_pontuacao_formatada(); // ele escreve a pontuação + this->setaPontuação;
  
};

class Bola:public Opengl_obj{ //classe que define os atributos e métodos da bola
  float dx,dy;//direção da bola
  
  public:
  
  // construtor para a bola onde ele recebe a posição x y e z do objeto, seus ẫngulos para transformação, um arquivo de cores, uma textura e uma escala
  Bola(string arquivo,double pos_x,// 
     double pos_y, double pos_z,double theta,double phi,
     double omega,double red, double green, double blue, double alpha,string texture_file,double escala);
  
  int lx;// sentido no qual a bola vai se movimentar.Caso ele seja 1 ele vai para a direita, caso seja -1 ele vai para a esquerda.
  int ly;// sentido no qual a bola vai se movimentar.Caso ele seja 1 ele vai para a cima, caso seja -1 ele vai para a baixo.

  void start_pos(); //posiçao inicial da bola , setando randomicamente a posição 
  void main_rotine();//a rotina que a bola terá ao longo do jogo. Muda estado , posição, direção, detecta colizões tanto com o jogador quanto com o senário.
  void vertical_collision(); // detecta a colizão vertical com o cenário
  void horizontal_collision();// detecta colizão horizontal com o cenário e pontua um dos jogadores
};
#ifdef TESTILU
  class Rosto:public Opengl_obj{
    public:
    Rosto   (string arquivo,double pos_x,
     double pos_y, double pos_z,double theta,double phi,
     double omega,double red, double green, double blue, double alpha,string texture_file,double escala);
    void main_rotine();
  };
#endif