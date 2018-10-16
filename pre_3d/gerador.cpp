#include <vector>
#include <iostream>
#include "imagem.h"
#include <fstream>
#include <tuple>
#include <cmath>
#include <stack>
#include <cmath>
#define sgn(x) ((x<0)?-1:((x>0)?1:0))


using namespace std;

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
Imagem::Imagem(){

}

Imagem::~Imagem(){

}



 Imagem Imagem::leitor  (string arquivo){
  ifstream in(arquivo);
  string tipo;
  int M,N,max;

  in >> tipo;
  in >> N;
  in >> M;
  vector <vector <tuple <int,int,int> > > img(M,vector <tuple <int,int,int>  >(N));
  in >> max;


   for (int i=0;i<M;i++){
     for (int j=0;j<N;j++){

       int r,g,b;
       in >> r;
       in >> g;
       in >>b;
       img[i][j]=make_tuple(r,g,b);
     }
   }

   return Imagem(tipo,M,N,max,img);

}



 Imagem Imagem::leitor_bin  (string arquivo){
  ifstream in(arquivo);
  string tipo;
  int M,N,max;

  in >> tipo;
  in >> N;
  in >> M;
  vector <vector <tuple <int,int,int> > > img(M,vector <tuple <int,int,int>  >(N));
  in >> max;


   for (int i=0;i<M;i++){
     for (int j=0;j<N;j++){

       uint8_t r,g,b;
       in >> r;
       in >> g;
       in >>b;
       img[i][j]=make_tuple(r,g,b);
     }
   }

   return Imagem(tipo,M,N,max,img);

}

Imagem Imagem::gerador_aleatorio (int M, int N, int max=255){
  srand (time(NULL));
  vector <vector <tuple <int,int,int> > > img(M,vector <tuple <int,int,int>  >(N));

  for (int i=0;i<M;i++){
    for (int j=0;j<N;j++){
      img[i][j]=make_tuple(rand()%max,rand()%max,rand()%max);
    }
  }

  return Imagem ("P3",M,N,max,img);

}
 Imagem Imagem::leitor_labirinto(string arquivo,Imagem cerca, Imagem livre){

  ifstream in(arquivo);
  string tipo;
  int M=0,N=0,max=255;
  string simbol="      ";

  vector<string> linhas;
  vector <vector <tuple <int,int,int> > > img;



  for (;simbol[2]==' ';getline(in,simbol)){


  }

  N=simbol.size()*cerca.N;
  while(getline(in,simbol)){
    M+=cerca.M;
    linhas.push_back(simbol);
    Imagem::com_shape(img, simbol,  N,cerca,livre);



  }

  for (int i=0;i<M;i++){
  //  cout<<"\n";
    for (int j=0;j<N;j++){
      //cout<<get<0>(img[i][j])<<" ";
    }
  }





  return Imagem ("P3",M,N,max,img);
}

void Imagem::sem_shape(vector<vector <tuple <int,int,int> > > &img,string simbol,int N){
  vector <tuple <int,int,int>  > linha_da_img(N);

  for (int i=0;i<N;i++){
    if (simbol[i]=='#'){
      linha_da_img[i]=(make_tuple(255,0,0));
    //  cout<<get<0>(linha_da_img[i]);
    }else if (simbol[i]=='.'){
      linha_da_img[i]=(make_tuple(0,255,255));
    }else if (simbol[i]==' '){
      linha_da_img[i]=(make_tuple(0,0,255));
    }
  }

  img.push_back(linha_da_img);

}



void Imagem::com_shape(vector<vector <tuple <int,int,int> > > &img,string simbol,int N,Imagem cerca, Imagem livre){
  vector< vector <tuple <int,int,int>  > > linha_da_img(cerca.M,vector <tuple <int,int,int>  >(N*cerca.N));
  //cout<<livre.M<<endl;

  for (int i=0;i<N;i++){

    for (int j=0;j<cerca.M;j++){
      for (int k=0;k<cerca.N;k++){

        if (simbol[i]=='#'){


          linha_da_img[j][k]=make_tuple(0,0,255);//cerca.img[j][k];
    //  cout<<get<0>(linha_da_img[i]);
        }else if (simbol[i]=='.'){
          linha_da_img[j][k]=make_tuple(0,0,255);//linha_da_img[j][k]=livre.img[j][k];
        }else if (simbol[i]==' '){
          linha_da_img[j][k]=(make_tuple(0,0,255));
    }
  }
}
}

  //img.push_back(linha_da_img);

}

Imagem Imagem::degrade (int M, int N, int max=255,int cor=0){
  int cores[] = {0,0,0};
  srand (time(NULL));
  vector <vector <tuple <int,int,int> > > img(M,vector <tuple <int,int,int>  >(N));

  for (int i=0;i<M;i++){
    cores[cor]=(cores[cor]+1)%max;
    //cout<<cores[cor]<<endl;
    for (int j=0;j<N;j++){
      img[i][j]=make_tuple(cores[0],cores[1],cores[2]);
    }
  }

  return Imagem ("P3",M,N,max,img);

}



Imagem Imagem::arco (int M, int N, int max=255){
  int cores[] = {255,127,0};
  srand (time(NULL));
  vector <vector <tuple <int,int,int> > > img(M,vector <tuple <int,int,int>  >(N));

  for (int i=0;i<M;i++){
    cores[1]=(cores[0]+1)%max;
    if (cores[1]%5==0)
      cores[2]=(cores[2]+1)%max;
    //cout<<cores[cor]<<endl;
    for (int j=0;j<N;j++){

      img[i][j]=make_tuple(cores[0],cores[1],cores[2]);
    }
  }

  return Imagem ("P3",M,N,max,img);

}




void Imagem::plot_pixel(int py, int px, tuple<int, int, int> color){
  //cout<<px<<" "<<py<<endl;
  //cout<<get<0>(this->img[px][py])<<endl;
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

  cout<<x1p<<" "<<y1p<<" "<<x2p<<" "<<y2p<<endl;



  this->line_fast(x1p,  y1p,  x2p,  y2p, color);
}



void Imagem::FTS(pair<int,int> P1, pair<int,int> P2, pair<int,int> P3, tuple<int,int,int> color)
{

    double x0=(double)P1.first;
    double y0=(double)P1.second;
    double x1=(double)P2.first;
    double y1=(double)P2.second;
    double x2=(double)P3.first;
    double y2=(double)P3.second;

    // sort the points vertically
    if (y1 > y2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }
    if (y0 > y1)
    {
        swap( x0, x1);
        swap( y0, y1);
    }
    if (y1 > y2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }

    double dx_far = (x2 - x0) / (y2 - y0 + 1);
    double dx_upper = (x1 - x0) / (y1 - y0 + 1);
    double dx_low = (x2 - x1) / (y2 - y1 + 1);
    double xf = x0;
    double xt = x0 + dx_upper; // if y0 == y1, special case
    for (int y = y0; y <= (y2 > height-1 ? height-1 : y2); y++)
    {



        if (y >= 0)
        {
            for (int x = (xf > 0 ? (int)xf : 0); x <= (xt < this->width ? xt : this->width-1) ; x++){
                this->plot_pixel(x, y,  color);

              }
            for (int x = (xf < this->width ? (int)xf : this->width-1); x >= (xt > 0 ? xt : 0); x--){
                this->plot_pixel(x, y,  color);
                //cout<<x<<" ";
            }

        }
        xf += dx_far;
        if (y < y1)
            xt += dx_upper;
        else
            xt += dx_low;



    }
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

void Imagem::triangle3d(tuple<double,double,double> p1,tuple<double,double,double> p2,
  tuple<double,double,double> p3 ,float z0, tuple<int,int,int> color, double s,
  double theta, double phi, double omega){

  double x1=get<0>(p1);
  double y1=get<1>(p1);
  double z1=get<2>(p1);
  double x2=get<0>(p2);
  double y2=get<1>(p2);
  double z2=get<2>(p2);
  double x3=get<0>(p3);
  double y3=get<1>(p3);
  double z3=get<2>(p3);



  double x1temp=x1*-sin(theta)+z1*cos(theta);
  double z1temp=x1*cos(theta)+z1*sin(theta);
  x1=x1temp;
  z1=z1temp;

  double x2temp=x2*-sin(theta)+z2*cos(theta);
  double z2temp=x2*cos(theta)+z2*sin(theta);
  x2=x2temp;
  z2=z2temp;


  double x3temp=x3*-sin(theta)+z3*cos(theta);
  double z3temp=x3*cos(theta)+z3*sin(theta);
  x3=x3temp;
  z3=z3temp;


  int x1p= (s*x1/(z1+z0))+meio.first;
  int y1p= (s*y1/(z1+z0))+meio.second;
  int x2p= (s*x2/(z2+z0))+meio.first;
  int y2p= (s*y2/(z2+z0))+meio.second;
  int x3p= (s*x3/(z3+z0))+meio.first;
  int y3p= (s*y3/(z3+z0))+meio.second;

  //cout<<x1<<" "<<y1<<" "<<z1<<" "<<x2<<" "<<y2<<" "<<z2<<" "<<x3<<" "<<y3<<" "<<z3<<
  //" ********** "<<x1p<<" "<<y1p<<" "<<x2p<<" "<<y2p<<" "<<x3p<<" "<<y3p<<" "<<"------------"<<
  //"y2p="<<y2p<<"="<<"("<<s<<"*"<<y2<<"/"<<"("<<z2<<"+"<<z0<<"))"<<"+"<<meio.second<<endl;




  fill_triangle(make_pair(x1p,y1p),make_pair(x2p,y2p),make_pair(x3p,y3p),color);
}

 Imagem Imagem::criador_obj  (string arquivo,int M, int N,double posicao_objeto_x,
  double posicao_objeto_y,double escala,double theta,double phi,
  double omega,double centroviewportx,
  double centroviewporty,double tam_viewport,double perspectiva){

  vector<vector<tuple<int,int,int> > > img(M,vector <tuple <int,int,int>  >(N,make_tuple(255,255,255)));

  vector<tuple<double,double,double> >  v;
  vector<tuple<uint,uint,uint> >  f;
  v.push_back(make_tuple(0,0,0));//valores comecam em 1,
  cout<<arquivo<<endl;
  ifstream in(arquivo);


  char c;


  while (in>>c){
    if (c=='v'){
      double x,y,z;
      in>>x;
      in>>y;
      in>>z;
      cout<<c;
      cout<<" "<<x<<" "<<y<<" "<<z<<endl;

      v.push_back(make_tuple(x,y,z));
    }else if(c=='f'){
      uint v1,v2,v3;

      in>>v1>>v2>>v3;
      cout<<c<<" "<<v1<<" "<<v2<<" "<<v3<<endl;
      f.push_back(make_tuple(v1,v2,v3));
    }
  }



  Imagem imagem ("P3",  M,  N, 255, img);

  for (int i=0;i<f.size();i++){
    tuple <uint,uint,uint> t=f[i];
    imagem.triangle3d(v[get<0>(t)], v[get<1>(t)],v[get<2>(t)],2.0 ,make_tuple(10,10,10),  perspectiva);
  }





  return imagem;




  }




int main(){

  Imagem d3d = Imagem::criador_obj("cara.obj",1000,1000);
  d3d.salvar_imagem_bin("nsei.ppm");

  return 0;
}
