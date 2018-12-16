#include "carregadorgl.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

#define LIMX 250
#define LIMY 114
#define TEXT2POS 660
#define OFFSETX 50
#define OFFSETY 10
#define WindowWidth 768
#define WindowHeight 1366
#define color4 GLfloat
//#define PRINTTEXT


#define sgn(x) ((x<0)?-1:((x>0)?1:0))
// gcc pong.cpp -o bot -lGL -lGLU -lglut -lm


GLfloat light0_ambient[] =
{0.2, 0.2, 0.2, 1.0};
GLfloat light0_diffuse[] =
{0.0, 0.0, 0.0, 1.0};
GLfloat light1_diffuse[] =
{0.0, 0.0, 0.0, 1.0};
GLfloat light1_position[] =
{0.0, 0.0, -10.0, 1.0};
GLfloat light2_diffuse[] =
{1.0, 1.0, 1.0, 1.0};
GLfloat light2_position[] =
{0.0, 0.0, -10.0, 1.0};
GLfloat globalAmbient[] = {1.0, 0.0, 0.0, 0.0};

Jogador* jog1;
Jogador* jog2;
Bola* bola;
Cena* cena;

void initsphere();

Cena::Cena(double escala,double perspectiva){
  this->escala=escala;
  this->perspectiva=perspectiva;
  objs=vector<Opengl_obj*>(0,0);
}

void Cena::add_obj(Opengl_obj *obj){
  objs.push_back(obj);
}

void Cena::desenha_tudo(){
  for (int i=0;i<objs.size();i++){
    objs[i]->main_rotine();
    objs[i]->desenha_gl();
  }
}

bool Opengl_obj::collision(Opengl_obj* other){

  
  return this->pos_y<other->pos_y+other->tamanho*2+5 &&
   this->pos_y>other->pos_y-5 &&
   this->pos_x  < other->pos_x +6&&
   this->pos_x  > other->pos_x ;
}

void Bola::vertical_collision(){
  if (pos_y>LIMY){
    ly=-1;
  }

  if (pos_y<-LIMY){
    ly=+1;

  }
}

void Jogador::pontuar(){
  pontuacao++;
}

void Jogador::main_rotine(){
  if(moving_state_horizontal==0){
    pos_x-=velocidade;
  } if(moving_state_horizontal==1){
    pos_x+=velocidade;
  } if(moving_state_vertical==0){
    pos_y+=velocidade;
  } if(moving_state_vertical==1){
    pos_y-=velocidade;
    
  }
}

double rand_range(double M,double N){
  return M + (rand() / ( RAND_MAX / (N-M) ) );
}

void Bola::main_rotine(){

  vertical_collision();
  horizontal_collision();
  
  if((Opengl_obj*)this->collision((Opengl_obj*)jog1)){
    dx=rand_range(3,6);
    dy=rand_range(dx-2,dx-1.0);
    lx=1;
 
  }
  if((Opengl_obj*)this->collision((Opengl_obj*)jog2)){
    dx=rand_range(3,6);
    dy=rand_range(dx-2,dx-1.0);
    lx=-1;
   
  }
  
  pos_x+=dx*lx;
  pos_y+=dy*ly;

}

void Bola::start_pos(){
 
  pos_y=0;
  if (((double)rand()/RAND_MAX)>0.5){
    lx=1;
     pos_x=-LIMX;
  }else{
    lx=-1;
    pos_x=LIMX;
  }
  if (((double)rand()/RAND_MAX)>0.5){
    ly=1;
  }else{
    ly=-1;
  }
  dx=rand_range(3,6);
  dy=rand_range(dx-2,dx-1.0);

  
}

void Bola::horizontal_collision(){
  
  if (pos_x<-LIMX){
    jog2->pontuar();
    start_pos();
    
  }

  if(pos_x>LIMX){
    jog1->pontuar();
    start_pos();
  }
}


void keyboard_up(unsigned char key, int x, int y)
{
   
     if(jog1->contains_horizontal_char(key)){
      jog1->moving_state_horizontal=-1;
    }else if(jog1->contains_vertical_char(key)){
      jog1->moving_state_vertical=-1;
    }else if(jog2->contains_horizontal_char(key)){
      jog2->moving_state_horizontal=-1;
    }else if(jog2->contains_vertical_char(key)){
      jog2->moving_state_vertical=-1;
    }
}



void Jogador::set_vel(int vel){
  velocidade=vel;
}
bool Jogador::contains_char(char c){
  return up==c||down==c||left==c||right==c;
}

bool Jogador::contains_vertical_char(char c){
  return up==c||down==c;
}

bool Jogador::contains_horizontal_char(char c){
  return left==c||right==c;
}

void Jogador::move(char c){
 
  if(c==left){
    moving_state_horizontal=0;
  }else if(c==right){
    moving_state_horizontal=1;
  }else if(c==up){
    moving_state_vertical=0;
  }else if(c==down){
    moving_state_vertical=1;
    
  }
}

void keyboard(unsigned char key, int x, int y)
{


  if(key== 27){
      exit(0);
  }else if(jog1->contains_char(key)){
    jog1->move(key);
  }else if (jog2->contains_char(key)){
    jog2->move(key);
  }

}



vec3d::vec3d(double x, double y, double z){
  this->x=x;
  this->y=y;
  this->z=z;
}


vec3d::vec3d(tuple<double,double,double,double,double,double,double,double,double>  ttd){
  double vx=get<3>(ttd)-get<0>(ttd),
  vy=get<4>(ttd)-get<1>(ttd),
  vz=get<5>(ttd)-get<2>(ttd),
  wx=get<6>(ttd)-get<0>(ttd),
  wy=get<7>(ttd)-get<1>(ttd),
  wz=get<8>(ttd)-get<2>(ttd);

  x = (vy*wz)-(vz*wy);
  y = (vz*wx)-(vx*wz);
  z = (vx*wy)-(vy*wx);

  double a=sqrt(pow(x,2)+pow(y,2)+pow(z,2));
  x=x/a;
  y=y/a;
  z=z/a;
}


void timer(int value)
{

    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}



void Cena::printtext(int x, int y, string text)
{
  glDisable(GL_LIGHTING);
  glColor3f(0.0f, 0.5f, 1.0f);
  glPushMatrix();
   glOrtho(0, WindowWidth*.2, 0, WindowHeight*.2, -1.0f, 1.0f);
  glTranslatef(x, y, 0);
  for (auto p = text.begin(); p!=text.end(); p++)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
  glPopMatrix();
  glEnable(GL_LIGHTING);
}

string Jogador::get_pontuacao_formatada(){
  return "pontuacao: "+to_string(pontuacao);
}

void display(void)
{

    GLfloat rot_x=0.0, rot_y=0.0;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    glEnable( GL_TEXTURE_2D );
    gluLookAt (0.0, 0.0, cena->perspectiva, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScaled (cena->escala, cena->escala, cena->escala);

    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_position);
    cena->desenha_tudo();
    cena->printtext(-WindowHeight*3,WindowWidth*5,jog1->get_pontuacao_formatada());
    cena->printtext(WindowHeight*2.5,WindowWidth*5,jog2->get_pontuacao_formatada());
 
    glFlush();
    glutSwapBuffers();
    glDisable(GL_TEXTURE_2D);
}


void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    double aspect = ((double) w) / h;
    glFrustum(-10,10,-10,10,-10,10);
    gluPerspective(45,aspect,-10,10);

    glMatrixMode(GL_MODELVIEW);
}

void initsphere(void)
{

   
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glFrontFace(GL_CW);   
    glCullFace(GL_FRONT);   
    glEnable(GL_CULL_FACE); 

    glClearDepth(100.0f);  
    glEnable(GL_DEPTH_TEST); 

    glDepthFunc(GL_LEQUAL);  
    glDepthRange(50,-50);   


    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glEnable(GL_LIGHTING);



    glColorMaterial ( GL_FRONT, GL_AMBIENT);

    glEnable(GL_COLOR_MATERIAL);


    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glFrustum(-10,10,-10,10,-10,10);

}


vector <string> split_string(string str, char sep=' '){
  vector<string> result;
  uint last_pos=0;
  uint i;
  if (str==" "||str.size()==0){
    return result;
  }
  for (i=1;i<str.size();i++){

    if (str[i]==sep){
      if (str[i-1]!=sep){
        result.push_back(str.substr(last_pos,i-last_pos));
      }

      last_pos=i+1;


    }
  }
  if(i>last_pos){
    result.push_back(str.substr(last_pos,i-last_pos));
  }
  return result;
}

Jogador::Jogador(string arquivo,double pos_x,
     double pos_y, double pos_z,double theta,double phi,
     double omega,double red, double green, double blue, double alpha,string texture_file,double escala,
     char up,char down,char left,char right,int velocidade)
     :Opengl_obj( arquivo, pos_x,
      pos_y,  pos_z, theta, phi,
      omega, red,  green,  blue,  alpha, texture_file, escala){
        this->up=up;
        this->down=down;
        this->left=left;
        this->right=right;
        this->velocidade=velocidade;
        tamanho=5*escala;
        pontuacao=0;
        moving_state_horizontal=-1;
        moving_state_vertical=-1;
      }

    Bola::Bola(string arquivo,double pos_x,
     double pos_y, double pos_z,double theta,double phi,
     double omega,double red, double green, double blue, double alpha,string texture_file,double escala)
     :Opengl_obj( arquivo, pos_x,
      pos_y,  pos_z, theta, phi,
      omega, red,  green,  blue,  alpha, texture_file, escala){
        

      }

tuple<double,double,double,double,double,double,double,double,double> Opengl_obj::join_tuple( tuple<double,double,double> p1,
  tuple<double,double,double> p2, tuple<double,double,double> p3,double theta, double phi, double omega){


  double x1=get<0>(p1);
  double y1=get<1>(p1);
  double z1=get<2>(p1);
  double x2=get<0>(p2);
  double y2=get<1>(p2);
  double z2=get<2>(p2);
  double x3=get<0>(p3);
  double y3=get<1>(p3);
  double z3=get<2>(p3);

  return make_tuple(x1,y1,z1,x2,y2,z2,x3,y3,z3);
}



void Opengl_obj::triangle3d(int i){

  tuple<double,double,double,double,double,double,double,double,double> triangle_to_draw=
  this->triangle_to_draw[i];

  vec3d normal = this->normais[i];

  double x1=get<0>(triangle_to_draw);
  double y1=get<1>(triangle_to_draw);
  double z1=get<2>(triangle_to_draw);
  double x2=get<3>(triangle_to_draw);
  double y2=get<4>(triangle_to_draw);
  double z2=get<5>(triangle_to_draw);
  double x3=get<6>(triangle_to_draw);
  double y3=get<7>(triangle_to_draw);
  double z3=get<8>(triangle_to_draw);

  glNormal3d(normal.x,normal.y,normal.z);
  if (cores.size()>i){
    glColor4d (cores[i].x,cores[i].y, cores[i].z,this->alpha);

  }else{
    glColor4d (this->red,this->green, this->blue,this->alpha);
  }
  
  glBegin (GL_POLYGON);

  #ifdef TESTILU
  glVertex3d(x1, y1, z1);
  glVertex3d(x2, y2, z2);
  glVertex3d(x3, y3, z3);
 
  #else
   glVertex3d(x1, y1, z1);
  glTexCoord2f(0.0, 0.0);
  glVertex3d(x2, y2, z2);
  glTexCoord2f(0.0, 1.0);
  glVertex3d(x3, y3, z3);
  glTexCoord2f(1.0, 1.0);
  

  #endif
  glEnd();





  }



Opengl_obj::Opengl_obj(vector<tuple<double,double,double,double,double,double,double,double,double> > triangle_to_draw,
  vector<vec3d> normais,
   tuple <float,float,float> color,double theta, double phi, double omega,
double pos_x, double pos_y, double pos_z,double red, double green, double blue, double alpha,vector<vec3d> cores){
    this->triangle_to_draw=triangle_to_draw;
    this->normais=normais;


    this->color=color;
    this->theta=theta;
    this->phi=phi;
    this->omega=omega;
    this->pos_x=pos_x;
    this->pos_y=pos_y;
    this->pos_z=pos_z;
    this->red=red;
    this->green=green;
    this->blue=blue;
    this->alpha=alpha;
    this->cores=cores;
  }

  GLuint Opengl_obj::LoadTexture2( string arquivo)
{

    ifstream in(arquivo);
    string tipo;
    int height,width,max;

    in >> tipo;
    in >> width;
    in >> height;
    in >> max;
    
    
    GLuint texture;
    unsigned char * data;
    data = (unsigned char *)malloc( sizeof(char)*width * height * 3 );
    
    
    int r,g,b;




    for (int i=0; i<(width*height*3); i+=3)
    {
        in >> r;
        in >> g;
        in >> b;
        
        data[i]=(unsigned char)r;
        data[i+1]=(unsigned char)g;
        data[i+2]=(unsigned char)b;
    }
    in.close();

    glGenTextures( 1, &texture ); //gera a textura
    glBindTexture( GL_TEXTURE_2D, texture ); // faz o binding da texture com o array

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE , GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);



    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);

    
    return texture;
}




 Opengl_obj::Opengl_obj  (string arquivo,double pos_x,
  double pos_y, double pos_z,double theta,double phi,
  double omega,double red, double green, double blue, double alpha,string texture_file,double escala){
    
  vector<tuple<double,double,double> >  v;
  vector<tuple<uint,uint,uint> >  f;
  v.push_back(make_tuple(0,0,0));//valores comecam em 1,
  ifstream in(arquivo);



  string entrada;

  while (getline(in,entrada)){

    vector<string> linha=split_string(entrada);


    if (linha.size()==0){
      continue;
    }
    if (linha[0]=="#"){
      continue;
    }

    if (linha[0]=="v"){
      double x,y,z;
      x=stod (linha[1])*escala;
      y=stod (linha[2])*escala;
      z=stod (linha[3])*escala;

      v.push_back(make_tuple(x,y,z));
    }else if(linha[0][0]=='f'){
      vector<uint> v_f(3);

      v_f[0]=stoul (linha[1]);
      v_f[1]=stoul (linha[2]);
      v_f[2]=stoul (linha[3]);
      
      f.push_back(make_tuple(v_f[0],v_f[1],v_f[2]));

      for (uint i=4;i<linha.size();i++){
        if(linha[i]=="#")
          break;

        v_f.push_back(stoul (linha[i]));
        f.push_back(make_tuple(v_f[i-3],v_f[i-2],v_f[i-1]));
      }
    }
  }

  in.close();
  

  vector<tuple<double,double,double,double,double,double,double,double,double> > triangle_to_draw;
  vector<vec3d> normais;

  for (uint i=0;i<f.size();i++){
    tuple <uint,uint,uint> t=f[i];
    tuple<double,double,double,double,double,double,double,double,double> face
    =Opengl_obj::join_tuple(v[get<0>(t)],v[get<1>(t)],v[get<2>(t)],theta,phi,omega);

    triangle_to_draw.push_back(face);
    vec3d normal= vec3d(face);
    normais.push_back(normal);
  }



 
  textura =LoadTexture2(texture_file);
 
  this->triangle_to_draw=triangle_to_draw;
    this->normais=normais;
    this->color=color;
    this->theta=theta;
    this->phi=phi;
    this->omega=omega;
    this->pos_x=pos_x;
    this->pos_y=pos_y;
    this->pos_z=pos_z;
    this->red=red;
    this->green=green;
    this->blue=blue;
    this->alpha=alpha;
    

  }


void Opengl_obj::desenha_gl(){


  glPushMatrix();
  glTranslated(pos_x,pos_y,pos_z);
  glRotated(theta,4.0,0,0);
  glRotated(phi,0.0,1.0,0.0);
  glRotated(omega,0.0,0.0,1.0);
  #ifndef TESTILU
  glBindTexture( GL_TEXTURE_2D, textura );
  #endif
  for (uint i=0;i<triangle_to_draw.size();i++){
    this->triangle3d(i);
  }

  glPopMatrix();
}




void Opengl_obj::rotate_ang(double offset, double &ang){
  ang+=offset;

  if (ang>360){
    ang = ang-360;
  }else if(ang<0){
    ang=360+ang;

  }

}


void init_players(){

    jog1= new Jogador("objs/quadrado.obj" ,-(float)LIMX +OFFSETX,0,-200,0,
    0,0,0.5,1.0,0.0,0.5,"texturas/parede.ppm",3,'w','s','a','d',3);
     
    jog2=new Jogador("objs/quadrado.obj" ,(float)LIMX -OFFSETX,0,-200,0,
    0,0,0.5,1.0,0.0,0.5,"texturas/coisa.ppm",3,'i','k','j','l',3);
   
    bola=(Bola*) new Bola("objs/esfera.obj" ,0,0,-200,0,
    0,0,0.5,1.0,0.0,0.5,"texturas/madeira.ppm",4);
    bola->start_pos();
    cena->add_obj((Opengl_obj*)bola);
    cena->add_obj((Opengl_obj*)jog1);
    cena->add_obj((Opengl_obj*)jog2);

    #ifdef TESTILU
      Rosto *rosto= new Rosto("objs/cara.obj" ,0,0,-200,0,
    0,0,0.5,1.0,0.0,0.5,"texturas/unipampa.ppm",40);
      cena->add_obj(rosto);

    #endif
    
    
}



int main(int argc, char **argv)
{
    srand(time(NULL));
  
    double escala =5,perspectiva=400;

    cena=new Cena(escala,perspectiva);
    
         

    
    
    glutInit(&argc, argv);

    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize ( WindowHeight,WindowWidth);
    
    glutInitWindowPosition (100, 100);
    
    glutCreateWindow (argv[0]);
    
    glEnable (GL_BLEND | GL_DEPTH_TEST);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
    glutKeyboardUpFunc( keyboard_up );
    glutFullScreen();

    initsphere();

    glutDisplayFunc(display);

    glutReshapeFunc(myReshape);
    

    glutTimerFunc(10, timer, 0);
    
    glutKeyboardFunc(keyboard);

    init_players();

   
    glutMainLoop();
    return 0;


}


#ifdef TESTILU
      Rosto::Rosto(string arquivo,double pos_x,
     double pos_y, double pos_z,double theta,double phi,
     double omega,double red, double green, double blue, double alpha,string texture_file,double escala)
     :Opengl_obj( arquivo, pos_x,
      pos_y,  pos_z, theta, phi,
      omega, red,  green,  blue,  alpha, texture_file, escala){
        

      }

      void Rosto::main_rotine(){
        this->rotate_ang(3,theta);
      }

#endif