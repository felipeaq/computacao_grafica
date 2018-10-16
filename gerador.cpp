#include <vector>
#include <iostream>
#include "imagem.h"
#include <fstream>
#include <tuple>

using namespace std;

Imagem::Imagem(std::string tipo, int M, int N, int max, vector<vector <tuple <int,int,int> > >img){
  this->tipo=tipo;
  this->M=M;
  this->N=N;
  this->max=max;
  this ->img=img;
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
  cout<<livre.M<<endl;

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





void Imagem::salvar_imagem(string arquivo){
  std::ofstream out(arquivo);


  out<<this->tipo;
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







int main(){
  /*Imagem gerador=Imagem::gerador_aleatorio(20,10);
  gerador.salvar_imagem("ex.ppm");
  Imagem ex = Imagem::leitor("ex.ppm");
  ex.inverter_cor();
  ex.salvar_imagem("saida.ppm");

  Imagem degrade=Imagem::degrade(254,  30);
  degrade.salvar_imagem("degrade.ppm");
  Imagem::arco(1024,  30).salvar_imagem("arco.ppm");*/
  Imagem bush= Imagem::leitor("bush.ppm");
  Imagem mato= Imagem::leitor("mato.ppm");

  Imagem::leitor_labirinto("maze.txt",bush,mato).salvar_imagem("maze.ppm");




  return 0;
}
