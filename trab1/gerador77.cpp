#include <vector>
#include <iostream>
#include "imagem77.h"
#include <fstream>
#include <tuple>
#include <cmath>
#include <stack>
#include <cmath>
#include <queue>
#include <string>
#include <algorithm>
#define sgn(x) ((x<0)?-1:((x>0)?1:0))


#define rotate_angle(a1,b1,a2,b2,a3,b3,angle) {\
  double a1temp=b1*-sin(angle)+a1*cos(angle);\
  double b1temp=b1* cos(angle)+a1*sin(angle);\
  double a2temp=b2*-sin(angle)+a2*cos(angle);\
  double b2temp=b2* cos(angle)+a2*sin(angle);\
  double a3temp=b3*-sin(angle)+a3*cos(angle);\
  double b3temp=b3* cos(angle)+a3*sin(angle);\
  \
  a1=a1temp;\
  a2=a2temp;\
  a3=a3temp;\
  b1=b1temp;\
  b2=b2temp;\
  b3=b3temp;\
  \
}






using namespace std;

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


bool CompareDist::operator()(tuple<double,double,double,double,double,double,double,double,double> n1,
  tuple<double,double,double,double,double,double,double,double,double> n2){
    return max_z(n1)<max_z(n2);
  }




Imagem::Imagem(std::string tipo, int M, int N, int max, vector<vector <tuple <int,int,int> > >img){
  this->tipo=tipo;
  this->M=M;
  this->N=N;
  this->max=max;
  this ->img=img;
  this->meio=make_pair(N/2,M/2);
  this->height=N;
  width=M;
  //cout<<M<<" "<<N<<endl;
}

Imagem::Imagem(std::string tipo, int M, int N, int max, vector<vector <tuple <int,int,int> > >img,int posicao_objeto_x,int posicao_objeto_y){
  this->tipo=tipo;
  this->M=M;
  this->N=N;
  this->max=max;
  this ->img=img;
  this->meio=make_pair(posicao_objeto_x,posicao_objeto_y);
  this->height=M;
  width=N;
  //cout<<M<<" "<<N<<endl;
}
Imagem::Imagem(){

}

Imagem::~Imagem(){

}






void Imagem::plot_pixel(int py, int px, tuple<int, int, int> color){
  //cout<<px<<" "<<py<<endl;
  //cout<<get<0>(this->img[px][py])<<endl;
  if (get<0>(color)<0)
    get<0>(color)=0;
  if(get<0>(color)>255)
    get<0>(color)=255;

  if (get<1>(color)<0)
    get<1>(color)=0;
  if(get<1>(color)>255)
    get<1>(color)=255;

  if (get<2>(color)<0)
    get<2>(color)=0;
  if(get<2>(color)>255)
    get<2>(color)=255;





  this->img[px][py]=color;
}
void Imagem::salvar_imagem_bin(string arquivo){
  std::ofstream out(arquivo);


  out<<"P6";


  //cout<<('3'+3)<<endl;


  out<<endl;
  out<<this->N;
  out<<" ";
  out<<this->M;
  out<<endl;
  out<<this->max;

  out<<endl;
  for (int i=0;i<this->M;i++){

    for (int j=0;j<this->N;j++){

      uint8_t aux=get<0>(this->img[i][j]);
      out<<aux;
      aux=get<1>(this->img[i][j]);
      out<<aux;
      aux=get<2>(this->img[i][j]);
      out<<aux;


    }
  }



}


void Imagem::salvar_imagem(string arquivo){
  std::ofstream out(arquivo);


  out<<"P3";
  out<<endl;
  out<<this->N;
  out<<" ";
  out<<this->M;
  out<<endl;
  out<<this->max;

  out<<endl;
  for (int i=0;i<this->M;i++){

    for (int j=0;j<this->N;j++){
      out<<get<0>(this->img[i][j]);
      out<<" ";
      out<<get<1>(this->img[i][j]);
      out<<" ";
      out<<get<2>(this->img[i][j]);
      out<<endl;

    }
  }



}


void Imagem::inverter_cor(){
  for (int i=0;i<this->M;i++)
    for (int j=0; j<this->N;j++){
      get<0>(this->img[i][j])=this->max-get<0>(this->img[i][j]);
      get<1>(this->img[i][j])=this->max-get<1>(this->img[i][j]);
      get<2>(this->img[i][j])=this->max-get<2>(this->img[i][j]);
    }
}



void Imagem::line_fast(int x1, int y1, int x2, int y2, tuple<int,int,int> color)
{
  int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

  dx=x2-x1;      /* the horizontal distance of the line */
  dy=y2-y1;      /* the vertical distance of the line */
  dxabs=abs(dx);
  dyabs=abs(dy);
  sdx=sgn(dx);
  sdy=sgn(dy);
  x=dyabs>>1;
  y=dxabs>>1;
  px=x1;
  py=y1;

  //VGA[(py<<8)+(py<<6)+px]=color;

  if (dxabs>=dyabs) /* the line is more horizontal than vertical */
  {
    for(i=0;i<dxabs;i++)
    {
      y+=dyabs;
      if (y>=dxabs)
      {
        y-=dxabs;
        py+=sdy;
      }
      px+=sdx;
      this->plot_pixel(px,py,color);
    }
  }
  else /* the line is more vertical than horizontal */
  {
    for(i=0;i<dyabs;i++)
    {
      x+=dxabs;
      if (x>=dyabs)
      {
        x-=dyabs;
        px+=sdx;
      }
      py+=sdy;
      this->plot_pixel(px,py,color);
    }
  }
}

void Imagem::drawcircle(int x0, int y0, int radius,tuple<int,int,int> color)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        this->plot_pixel(x0 + x, y0 + y,color);
        this->plot_pixel(x0 + y, y0 + x,color);
        this->plot_pixel(x0 - y, y0 + x,color);
        this->plot_pixel(x0 - x, y0 + y,color);
        this->plot_pixel(x0 - x, y0 - y,color);
        this->plot_pixel(x0 - y, y0 - x,color);
        this->plot_pixel(x0 + y, y0 - x,color);
        this->plot_pixel(x0 + x, y0 - y,color);

        y += 1;
        err += 1 + 2*y;
        if (2*(err-x) + 1 > 0)
        {
            x -= 1;
            err += 1 - 2*x;
        }
    }
}
bool Imagem::verifica_limite(int px, int py){
  return px<this->M && py<this->N &&px>=0 && py>=0;
}
bool Imagem::mesma_cor(int px, int py, tuple<int, int, int> old_color){
  return old_color==this->img[px][py];
}

void Imagem::flood_fil(int px, int py,tuple<int,int,int> new_color){
  if (this->img[px][py]==new_color){
    return;
  }

  pair <int,int> pos;
  stack <pair<int,int> > busca;

  tuple<int,int,int> old_color=this->img[px][py];

  busca.push(make_pair(px, py));

  while(!busca.empty()){
    pos=busca.top();
    busca.pop();
    this->img[pos.first][pos.second]=new_color;



    if(verifica_limite(pos.first-1,pos.second) && mesma_cor(pos.first-1,pos.second,old_color)){
      busca.push(make_pair(pos.first-1,pos.second));
    }

    if(verifica_limite(pos.first,pos.second-1) && mesma_cor(pos.first,pos.second-1,old_color)){
      busca.push(make_pair(pos.first,pos.second-1));
    }

    if(verifica_limite(pos.first,pos.second+1) && mesma_cor(pos.first,pos.second+1,old_color)){
      busca.push(make_pair(pos.first,pos.second+1));
    }

    if(verifica_limite(pos.first+1,pos.second) && mesma_cor(pos.first+1,pos.second,old_color)){
      busca.push(make_pair(pos.first+1,pos.second));
    }


  }
}

void Imagem::line_fast_3d(float x1, float y1, float z1,float x2, float y2,float z2,float z0, tuple<int,int,int> color){

float s=30.0;
  int x1p= s*x1/(z1+z0)+this->meio.first;
  int y1p= s*y1/(z1+z0)+this->meio.second;
  int x2p= s*x2/(z2+z0)+this->meio.first;
  int y2p= s*y2/(z2+z0)+this->meio.second;

  //cout<<x1p<<" "<<y1p<<" "<<x2p<<" "<<y2p<<endl;



  this->line_fast(x1p,  y1p,  x2p,  y2p, color);
}


void Imagem::fill_triangle(pair<int,int> p0, pair <int,int> p1, pair<int,int> p2,tuple<int,int,int> color){
  if (p1.second>p2.second)
    swap(p1,p2);
  if(p0.second>p1.second)
    swap(p0,p1);
  if(p1.second>p2.second)
    swap(p1,p2);

  double x0=p0.first,y0=p0.second,x1=p1.first,y1=p1.second,x2=p2.first,y2=p2.second;


  double dx_f=(x2-x0)/(y2-y0+1);
  double dx_u=(x1-x0)/(y1-y0+1);
  double dx_l=(x2-x1)/(y2-y1+1);

  double xf=x0;
  double xt=x0+dx_u;

  for (int y=y0;y<= (y2>this->height-1?this->height-1:y2);y++){

    if(y>=0){

      for (int x=(xf>0?(int)xf:0); x<=(xt<this->width?xt:this->width-1);x++){
        this->plot_pixel(x, y,  color);

      }
      for (int x = (xf<this->width?(int)xf:this->width-1);x>=(xt>0?xt:0);x--){
        this->plot_pixel(x, y, color);

      }

      xf+=dx_f;
      if (y<y1){
        xt+=dx_u;
      }else{
        xt+=dx_l;
      }



    }
  }





}

tuple<double,double,double,double,double,double,double,double,double> Imagem::rotate( tuple<double,double,double> p1,
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


  rotate_angle(x1,z1,x2,z2,x3,z3,theta);
  rotate_angle(x1,y1,x2,y2,x3,y3,phi);
  rotate_angle(z1,y1,z2,y2,z3,y3,omega);




  return make_tuple(x1,y1,z1,x2,y2,z2,x3,y3,z3);
}

double Imagem::cross_product(tuple<double,double,double,double,double,double,double,double,double>  ttd,double l1, double l2, double l3){

  double vx=get<3>(ttd)-get<0>(ttd),
  vy=get<4>(ttd)-get<1>(ttd),
  vz=get<5>(ttd)-get<2>(ttd),
  wx=get<6>(ttd)-get<0>(ttd),
  wy=get<7>(ttd)-get<1>(ttd),
  wz=get<8>(ttd)-get<2>(ttd);

  double nx = (vy*wz)-(vz*wy);
  double ny = (vz*wx)-(vx*wz);
  double nz = (vx*wy)-(vy*wx);

  double a=sqrt(pow(nx,2)+pow(ny,2)+pow(nz,2));
  nx=nx/a;
  ny=ny/a;
  nz=nz/a;


  double cx=(get<0>(ttd)+get<3>(ttd)+get<6>(ttd))/3;
  double cy=(get<1>(ttd)+get<4>(ttd)+get<7>(ttd))/3;
  double cz=(get<2>(ttd)+get<5>(ttd)+get<8>(ttd))/3;


  double lx= cx-l1;
  double ly= cy-l2;
  double lz= cz-l3;

  double la  =sqrt(pow(lx,2)+pow(ly,2)+pow(lz,2));

  lx=lx/la;
  ly=ly/la;
  lz=lz/la;






  return nx*lx+ny*ly+nz*lz;
}


void Imagem::triangle3d(tuple<double,double,double,double,double,double,double,double,double>  triangle_to_draw,
  double z0, double s,tuple <int,int,int> color,double l1, double l2, double l3){

  double x1=get<0>(triangle_to_draw);
  double y1=get<1>(triangle_to_draw);
  double z1=get<2>(triangle_to_draw);
  double x2=get<3>(triangle_to_draw);
  double y2=get<4>(triangle_to_draw);
  double z2=get<5>(triangle_to_draw);
  double x3=get<6>(triangle_to_draw);
  double y3=get<7>(triangle_to_draw);
  double z3=get<8>(triangle_to_draw);






  double color_offset=cross_product(triangle_to_draw,l1,l2,l3)/3;
  //cout<<color_offset<<" - ";


  int x1p= (s*x1/(z1+z0))+meio.first;
  int y1p= (s*y1/(z1+z0))+meio.second;
  int x2p= (s*x2/(z2+z0))+meio.first;
  int y2p= (s*y2/(z2+z0))+meio.second;
  int x3p= (s*x3/(z3+z0))+meio.first;
  int y3p= (s*y3/(z3+z0))+meio.second;

  //cout<<x1<<" "<<y1<<" "<<z1<<" "<<x2<<" "<<y2<<" "<<z2<<" "<<x3<<" "<<y3<<" "<<z3<<
  //" ********** "<<x1p<<" "<<y1p<<" "<<x2p<<" "<<y2p<<" "<<x3p<<" "<<y3p<<" "<<"------------"<<
  //"y2p="<<y2p<<"="<<"("<<s<<"*"<<y2<<"/"<<"("<<z2<<"+"<<z0<<"))"<<"+"<<meio.second<<endl;

  get<0>(color)=(int)(color_offset*get<0>(color));
  get<1>(color)=(int)(color_offset*get<1>(color));
  get<2>(color)=(int)(color_offset*get<2>(color));


  fill_triangle(make_pair(x1p,y1p),make_pair(x2p,y2p),make_pair(x3p,y3p),color);
}




 Imagem Imagem::criador_obj  (string arquivo,int M, int N,int posicao_objeto_x,
  int posicao_objeto_y,double escala,double theta,double phi,
  double omega,double perspectiva,double l1, double l2, double l3){

  vector<vector<tuple<int,int,int> > > img(M,vector <tuple <int,int,int>  >(N,make_tuple(255,255,255)));

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
    }else if(linha[0]=="f"){
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

  vector< tuple<double,double,double,double,double,double,double,double,double> > teste_v;

  Imagem imagem ("P3",  M,  N, 255, img,posicao_objeto_x,posicao_objeto_y);

  priority_queue <tuple<double,double,double,double,double,double,double,double,double>,
  vector<tuple<double,double,double,double,double,double,double,double,double> >,
  CompareDist> triangle_to_draw;

  for (uint i=0;i<f.size();i++){
    tuple <uint,uint,uint> t=f[i];

    //teste_v.push_back(imagem.rotate(v, get<0>(t),get<1>(t),get<2>(t),theta,phi,omega));

    triangle_to_draw.push(imagem.rotate(v[get<0>(t)],v[get<1>(t)],v[get<2>(t)],theta,phi,omega));
  }

  if (triangle_to_draw.empty()){
    cout<< "imagem não existe"<<endl;
    exit(1);
  }
  double perspectiva_max=perspectiva-max_z(triangle_to_draw.top());
  if (perspectiva_max<1){
    cout<< "aumente a perspectiva. valor  minimo: "<<max_z(triangle_to_draw.top())+1.125 <<endl;
    exit(1);
  }

  while(!triangle_to_draw.empty()){

    //cout<<get<2>(triangle_to_draw.top())<<" "<<" "<<get<5>(triangle_to_draw.top())<<" "<<" "<<get<8>(triangle_to_draw.top())<<endl;

    imagem.triangle3d(triangle_to_draw.top(),perspectiva,escala,make_tuple(255,255,255),l1,l2,l3);
    triangle_to_draw.pop();
  }





  return imagem;




  }




int main(int argc,char* argv[]){



  if (argc<15){
    cout<< "para executar digite entrada saida altura largura centro_x contro_y escala theta phi omega perspectiva p1_luz p2_luz p3_luz"<<endl;
    cout<<" exemplo de execução ./programa elephant.obj saida.ppm 2000 2000 500 700 600 3.14 3.14 0 30 1 1 1"<<endl;
    return 1;
  }

  Imagem d3d = Imagem::criador_obj(argv[1],stoi(argv[3]),stoi(argv[4]),stoi(argv[5])
  ,stoi(argv[6]),stod(argv[7]),stod(argv[8]),stod(argv[9]),stod(argv[10]),
  stod(argv[11]),stod(argv[12]),stod(argv[13]),stod(argv[14]));
  d3d.salvar_imagem_bin(argv[2]);

  return 0;
}
