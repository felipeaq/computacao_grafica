#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "carregadorgl.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <tuple>
#include <cmath>
#include <stack>
#include <cmath>
#include <queue>
#include <string>
#include <algorithm>

#define sgn(x) ((x<0)?-1:((x>0)?1:0))
// gcc textur.c -o bot -lGL -lGLU -lglut -lm


//Cena *cena=new Cena();



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




Cena* cena;
Cena::Cena(double escala,double perspectiva){
  this->escala=escala;
  this->perspectiva=perspectiva;
  this->pos=0;
}

void Cena::add_obj(Opengl_obj *obj){
  objs.push_back(obj);
}

Opengl_obj* Cena::get_obj(){
  return objs[pos];
}
void Cena::next_obj(){
  pos++;
  if (pos>=objs.size()){
    pos=0;
  }
}


void Cena::ant_obj(){
  pos--;

  if (pos<0){
    pos=objs.size()-1;


  }

}

void Cena::desenha_tudo(){
  for (int i=0;i<objs.size();i++){
    objs[i]->desenha_gl();
  }
}


void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(0);
      break;

    case 's':
      cena->get_obj()->rotate_ang(3.0, cena->get_obj()->theta);
      break;

    case 'w':
      cena->get_obj()->rotate_ang(-3.0, cena->get_obj()->theta);
      break;


    case 'a':
      cena->get_obj()->rotate_ang(-3.0, cena->get_obj()->phi);
      break;

    case 'd':
      cena->get_obj()->rotate_ang(3.0, cena->get_obj()->phi);
      break;




    case 'q':
      cena->get_obj()->rotate_ang(3.0, cena->get_obj()->omega);
      break;

    case 'e':
      cena->get_obj()->rotate_ang(-3.0, cena->get_obj()->omega);
      break;

    case '-':
      if (cena->escala>.25)
        cena->escala-=0.25;
      break;

    case '+':
      cena->escala+=0.25;
      break;

    case 'z':
      cena->perspectiva-=1;
      break;
    case 'x':
      cena->perspectiva+=1;
      break;

    case 'i':
      cena->get_obj()->pos_y--;
      break;
    case 'k':
      cena->get_obj()->pos_y++;
      break;

    case 'j':
      cena->get_obj()->pos_x--;
      break;
    case 'l':
      cena->get_obj()->pos_x++;
      break;

    case 'u':
      cena->get_obj()->pos_z--;
      break;
    case 'p':
      cena->get_obj()->pos_z++;
      break;

    case 'm':
      cena->next_obj();
      break;
    case 'n':
      cena->ant_obj();
      break;

    case 'v':
      string arquivo,arquivo_cor;

      double pos_x,pos_y,pos_z,theta,phi,omega,r,g,b,a;
      cout<<"digite: arquivo pos_x pos_y pos_z theta phi omega red green blue alpha arquivo_cor"<<endl;
      cin>>arquivo>>pos_x>>pos_y>>pos_z>>theta>>phi>>omega>>r>>g>>b>>a>>arquivo_cor;
      cena->add_obj(Opengl_obj::criador_obj( arquivo,pos_x,pos_y,pos_z,theta,phi,omega,r,g,b,a,arquivo_cor));




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
    //glLoadIdentity();

}

void initflat(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    //glShadeModel (GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glFrontFace(GL_CW);    //
    glCullFace(GL_FRONT);    //  Estas tres fazem o culling funcionar
    glEnable(GL_CULL_FACE); //

   glClearDepth(100.0f);  ///*******
    glEnable(GL_DEPTH_TEST);  ///*******

    glDepthFunc(GL_LEQUAL);  ///*******
    glDepthRange(50,-50);    ///*******

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT2);



    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
   /// glDepthMask(GL_TRUE);


}

void initsphere(void)
{

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glFrontFace(GL_CW);    //
    glCullFace(GL_FRONT);    //
    glEnable(GL_CULL_FACE); //

    glClearDepth(100.0f);  ///*******
    glEnable(GL_DEPTH_TEST);  ///*******

    glDepthFunc(GL_LEQUAL);  ///*******
    glDepthRange(50,-50);    ///*******


    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glEnable(GL_LIGHTING);

    ///glColorMaterial(GL_FRONT, GL_DIFFUSE);
    ///glEnable(GL_COLOR_MATERIAL);
    /*  mode	Specifies which	of several material parameters track
    	the current color.  Accepted values are	GL_EMISSION,
    	GL_AMBIENT, GL_DIFFUSE,	GL_SPECULAR, and
    	GL_AMBIENT_AND_DIFFUSE.	 The initial value is
    	GL_AMBIENT_AND_DIFFUSE. */

    glColorMaterial ( GL_FRONT, GL_AMBIENT);
    //glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);


    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

}




double max_z(tuple<double,double,double,double,double,double,double,double,double> t){
  double x=get<2>(t)>get<5>(t)?get<2>(t):get<5>(t);
  x= get<8>(t)>x?get<8>(t):x;

  return x;
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
  //cout<<cores.size()<<">"<<i<<endl;
  if (cores.size()>i){
    glColor4d (cores[i].x,cores[i].y, cores[i].z,this->alpha);

  }else{
    glColor4d (this->red,this->green, this->blue,this->alpha);
  }

  glBegin (GL_POLYGON);

  cout<<x1<<" "<<y1<<" "<<z1<<endl<<x2<<" "<<y2<<" "<<z2<<endl<<x3<<" "<<y3<<" "<<z3<<endl<<"******************"<<endl;


  glVertex3d(x1, y1, z1);

  glVertex3d(x2, y2, z2);

  glVertex3d(x3, y3, z3);


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


 Opengl_obj* Opengl_obj::criador_obj  (string arquivo,double pos_x,
  double pos_y, double pos_z,double theta,double phi,
  double omega,double red, double green, double blue, double alpha,string color_file){

  //vector<vector<tuple<int,int,int> > > img(M,vector <tuple <int,int,int>  >(N,make_tuple(255,255,255)));

  vector<tuple<double,double,double> >  v;
  vector<tuple<uint,uint,uint> >  f;
  v.push_back(make_tuple(0,0,0));//valores comecam em 1,
  //cout<<arquivo<<endl;
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
    //cout<<entrada<<endl;

    if (linha[0]=="v"){
      double x,y,z;
      x=stod (linha[1]);
      y=stod (linha[2]);
      z=stod (linha[3]);

      //cout<<" "<<linha[0]<<" "<<x<<" "<<y<<" "<<z<<endl;

      v.push_back(make_tuple(x,y,z));
    }else if(linha[0][0]=='f'){
      vector<uint> v_f(3);

      v_f[0]=stoul (linha[1]);
      v_f[1]=stoul (linha[2]);
      v_f[2]=stoul (linha[3]);
      //cout<<" "<<linha[0]<<" "<<v1<<" "<<v2<<" "<<v3<<endl;
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
  vector<vec3d> cores;

  ifstream in2(color_file);

  while (getline(in2,entrada)){


    vector<string> linha=split_string(entrada);


    if (linha.size()<3){
      continue;
    }
    if (linha[0]=="#"){
      continue;
    }
    //cout<<entrada<<endl;


      double x,y,z;
      x=stod (linha[0]);
      y=stod (linha[1]);
      z=stod (linha[2]);
      //cout<<x<<" "<<" "<<y<<" "<<z<<endl;

      //cout<<" "<<linha[0]<<" "<<x<<" "<<y<<" "<<z<<endl;

      cores.push_back(vec3d(x,y,z));
  }





  vector<tuple<double,double,double,double,double,double,double,double,double> > triangle_to_draw;
  vector<vec3d> normais;

  for (uint i=0;i<f.size();i++){
    tuple <uint,uint,uint> t=f[i];

    //teste_v.push_back(imagem.rotate(v, get<0>(t),get<1>(t),get<2>(t),theta,phi,omega));

    tuple<double,double,double,double,double,double,double,double,double> face
    =Opengl_obj::join_tuple(v[get<0>(t)],v[get<1>(t)],v[get<2>(t)],theta,phi,omega);

    triangle_to_draw.push_back(face);
    vec3d normal= vec3d(face);
    normais.push_back(normal);
  }









  return new Opengl_obj(triangle_to_draw,normais,make_tuple(1.0,1.0,1.0), theta,phi,omega,pos_x,pos_y,pos_z,red,blue,green,alpha,cores);




  }


void Opengl_obj::desenha_gl(){



  //cout <<omega<<endl;

  glPushMatrix();
  glTranslated(pos_x,pos_y,pos_z);
  //glLoadIdentity();
  glRotated(theta,4.0,0,0);
  glRotated(phi,0.0,1.0,0.0);
  glRotated(omega,0.0,0.0,1.0);



  //



  for (uint i=0;i<triangle_to_draw.size();i++){


    this->triangle3d(i);

  }
  cout<<endl<<"#################"<<endl;
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


int main(int argc, char **argv)
{

  if (argc<17){
    cout<< "para executar digite entrada largura altura centro_x contro_y centro_z escala theta phi omega perspectiva vermelho verde azul alpha"<<endl;
    cout<<" exemplo de execução ./programa objs/knoxs.obj  1366 768 600 700 3 1 0 0 0 600 0.5 0.0 0.0 0.5"<<endl;
    return 1;
  }




    cena=new Cena(stod(argv[7]),stod(argv[11]));

    cena->add_obj(Opengl_obj::criador_obj(argv[1],stod(argv[4]),stod(argv[5]),stod(argv[6]),
    stod(argv[8]),stod(argv[9]),stod(argv[10]),stod(argv[12]),stod(argv[13]),stod(argv[14]),stod(argv[15]),argv[16]));

    //stod(argv[12]),stod(argv[13]),stod(argv[14]) l1,l2,l3
    //escala -> stod(argv[7])
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (stoi(argv[2]),stoi(argv[3]));
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    glEnable (GL_BLEND | GL_DEPTH_TEST);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //initflat();

    initsphere();

    glutDisplayFunc(display);

    glutReshapeFunc(myReshape);

    glutTimerFunc(10, timer, 0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;


}
