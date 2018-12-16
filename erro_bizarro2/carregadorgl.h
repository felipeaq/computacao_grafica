#include <vector>
#include <tuple>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>


using namespace std;



struct vec3d{
  double x;
  double y;
  double z;

  vec3d(double x, double y, double z);
  vec3d(tuple<double,double,double,double,double,double,double,double,double>  ttd);
};





class Opengl_obj{

public:
  
  vector<tuple<double,double,double,double,double,double,double,double,double> > triangle_to_draw;

  double escala;
  tuple <float,float,float> color;


  double theta,phi,omega, pos_x, pos_y,pos_z,red,green,blue,alpha;

  vector<vec3d> normais;
  vector<vec3d> cores;

  void triangle3d(int i);

  Opengl_obj(vector<tuple<double,double,double,double,double,double,double,double,double> > triangle_to_draw,
    vector<vec3d> normais,
     tuple <float,float,float> color,double theta, double phi, double omega,
  double pos_x, double pos_y,double pos_z,double red, double green, double blue, double alpha,vector<vec3d> cores);

    void desenha_gl();

    void rotate_ang(double offset, double &ang);
    static tuple<double,double,double,double,double,double,double,double,double> join_tuple(tuple<double,double,double> p1, tuple<double,double,double> p2, tuple<double,double,double> p3,double theta=0, double phi=0, double omega=0);

    static Opengl_obj* criador_obj  (string arquivo,double pos_x,
     double pos_y, double pos_z,double theta,double phi,
     double omega,double red, double green, double blue, double alpha,string color_file,double escala);

    bool collision(Opengl_obj* other);


};



class Cena{
public:

  Cena(double escala, double perspectiva);
  vector<Opengl_obj*> objs;
  int pos;
  double perspectiva;
  double escala;

  void add_obj(Opengl_obj* obj);
  Opengl_obj* get_obj();
  void next_obj();
  void ant_obj();
  void desenha_tudo();

};

class Jogador:public Opengl_obj{
  private:
  int velocidade;
  char up,down,left,right;
  
  public:
  void set_vel(int vel);
  
  void set_chars(char up,char down,char left,char right);
  bool contains_char(char c);
  void move(char c);
 
};

class Bola:public Opengl_obj{
  float dx,dy;

  int ladox;
  int ladoy;
  public:
  void start_pos();
  void main_rotine(Cena *c);
  
};
