#include <vector>
#include <iostream>
#include "imagem.h"
#include <fstream>
#include <tuple>
#include <cmath>
#include <stack>
#define sgn(x) ((x<0)?-1:((x>0)?1:0))


using namespace std;

Imagem::Imagem(std::string tipo, int M, int N, int max, vector<vector <tuple <int,int,int> > >img){
  this->tipo=tipo;
  this->M=M;
  this->N=N;
  this->max=max;
  this ->img=img;

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




void Imagem::plot_pixel(int px, int py, tuple<int, int, int> color){
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

int main(){
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




  Imagem branco = Imagem::leitor("teste.ppm");
  //branco.line_fast(0, 0, 200, 200, make_tuple(0,0,0));



  branco.line_fast(100, 100, 100, 300, make_tuple(0,0,0));
  branco.line_fast(100, 100, 300, 100, make_tuple(0,0,0));
  branco.line_fast(100, 300, 300, 300, make_tuple(0,0,0));
  branco.line_fast(300, 100, 300, 300, make_tuple(0,0,0));
  branco.drawcircle(100,100,90, make_tuple(0,0,0));

  branco.flood_fil(200, 200, make_tuple(255,0,0));
  branco.flood_fil(150,150,make_tuple(0,255,0));
  branco.flood_fil(50,50,make_tuple(0,0,255));

  branco.flood_fil(150,2,make_tuple(255,255,0));
  //branco.line_fast(0, 0, 200, 200, make_tuple(0,0,0));
  branco.salvar_imagem_bin("saida.ppm");

  Imagem binario=Imagem::leitor_bin("saida.ppm");

  binario.salvar_imagem("nao_binario.ppm");

  //Imagem::leitor_labirinto("maze.txt",bush,mato).salvar_imagem("maze.ppm");





  return 0;
}
