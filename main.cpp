#include <iostream>

#include "graph.h"

int main()
{
  Graph mapa;
  mapa.loadGraphList("metroCDMX.txt", 28);
  mapa.loadNodeNames("estaciones.txt");
  
  mapa.showInfo();
  std::cout<<"BIENVENIDO \n";

  int option=-1;
  do
  {
    std::cout<<"\nEscoja una de las siguientes opciones:\n";
    std::cout<<"1:Buscar el camino con menos paradas entre dos estaciones \n";
    std::cout<<"2:Ver lo nombres de las estaciones del mapa \n";
    std::cout<<"3:Ver cuales estaciones conectan con otra \n";
    std::cout<<"0:Salir del programa\n";

    std::cin>>option;
    if(option==1)
    {
      int option2;
      std::cout<<"Escoja si quiere buscar por nombre (1) o por número de estación (2)"<<std::endl;
      std::cin>>option2;
      if(option2==1)
      {
        std::cout<<"Ingrese dos nombres de estaciones, origen y destino correspondientemente. Los nombres deben estar en MAYÚSCULAS  y SIN ACENTOS"<<std::endl;
        std::string a,b;
        std::cin.ignore();
        getline(std::cin,a,'\n');
        getline(std::cin,b,'\n');
        std::cout<<a<<" | "<<b<<std::endl;
        std::cout<<"\n"<<mapa.searchByNameBFS(a,b)<<'\n';
      }
      else if(option2==2)
      {
        std::cout<<"Ingrese dos enteros correspondientes al origen y al destino, en ese orden"<<std::endl;
        int a,b;
        std::cin>>a;
        std::cin>>b;
        std::cout<<"\n"<<mapa.BFS(a,b)<<'\n';
      }
    }
    else if(option==2)
    {
      mapa.showAllNodes();
    }
    else if(option == 3)
    {
      int option2;
      std::cout<<"Escoja si quiere buscar por nombre (1) o por número de estación (2)"<<std::endl;
      std::cin>>option2;
      if(option2==1)
      {
        std::cout<<"Ingrese el nombre de la estación requerida. Los nombres deben estar en MAYÚSCULAS  y SIN ACENTOS"<<std::endl;
        std::string a;
        std::cin.ignore();
        getline(std::cin,a,'\n');
        mapa.neighborNodesString(a);
      }
      else if(option2==2)
      {
        std::cout<<"Ingrese el número de la estación requerida."<<std::endl;
        int a;
        std::cin.ignore();
        std::cin>>a;
        mapa.neighborNodes(a);
      }
    }
  } while(option!=0);
  std::cout<<"FIN"<<std::endl;

  //std::cout<<g.printAdjListWithCost()<<std::endl;
  //std::cout<<g.Dijkstra(0, 7);
}