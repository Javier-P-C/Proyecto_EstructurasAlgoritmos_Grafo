#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>
#include <sstream>
#include <queue>
#include <stack>
#include <string>

class Graph
{
  private:
    int nodes;
    std::vector<std::vector<int>> adjList;//Guarda los nodos adyacentes
    std::vector<std::vector<float>> adjListCost;//Guarda el costo de cada arco
    std::vector<std::vector<int>> adjListCostOrder;//Guarda lo nodos adyacentes ordenadas con respecto a su costo
    std::vector<std::string> names;

  public:
    Graph(); 
    ~Graph();

    //Carga
    void loadGraphList(std::string,int); //Mete los nodos a adjList
    void loadNodeNames(std::string); //Carga los nombres de cada nodo

    //Búsquedas
    std::string BFS(int,int); //El recorrido de BFS junto con el camino más corto
    //std::string Dijkstra(int,int); //Algoritmo Dijkstra para el camino de costo mínimo
    void pathBFS(int,int,std::queue<int>&,std::stringstream&); //apoya a BFS a sacar el camino más corto

    //Impresiones
    std::string printAdjList(); //Imprime AdjList
    std::string printAdjListWithCost(); //Imprime las listas adyacentes y los costos
    void showInfo(); //Imprime la candidad de nodos y arcos
    void neighborNodes(int);
    void showAllNodes();
    void neighborNodesString(std::string);

    //Auxiliares
    std::string number2string(int); //Devuelve el nombre del nodo solicitado
    int string2number(std::string); //Devuelve el número del nodo nombrado
    std::string searchByNameBFS(std::string,std::string); //Actua como intermediario de BFS() cuando se realiza una búsqueda con nombres
    template <class T> void swap(std::vector<T>&,int,int); //Apoya con intercambios de valores en arreglos
    

};

Graph::Graph() 
{
  nodes = 0;
}

Graph::~Graph() 
{
  nodes = 0;
  adjList.~vector();
}

template <class T>
void Graph::swap(std::vector<T> &v,int i,int j)
{
  int aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

void Graph::loadGraphList(std::string doc_name,int vert)
{
  //Se dan valores los atributos del objeto
  nodes = vert;
  for(int i=0;i<nodes;i++)
  {
    std::vector<int> lista;
    adjList.push_back(lista);
    adjListCostOrder.push_back(lista);
    std::vector<float> lista_costo;
    adjListCost.push_back(lista_costo);
  }

  //Se lee el documento y se sacan los nodos de él
  std::ifstream reader(doc_name);
  if(reader.is_open())
  {
    std::string line;
    while(reader.good())
    {
      getline(reader,line,'\n');
      //Se saca el primer entero 
      int index = 1, aux_i = index;
      int a = 0,b = 0,count = -1;
      float c=0;

      do
      {
        count ++;
        aux_i++;
      }while(line[aux_i]!=',');
      do
      {
        a+=(line[index]-'0')*pow(10,count);
        index++;
        count--;
      } while(line[index]!=',');

      //Se saca el segundo entero 
      index+=2;
      aux_i = index;
      count = -1;
      do
      {
        count ++;
        aux_i++;
      }while(line[aux_i]!=',');
      do
      {
        b+=(line[index]-'0')*pow(10,count);
        index++;
        count--;
      } while(line[index]!=',');
      
      //Se saca el flotante
      index+=2;
      std::stringstream c_aux;
      for(;index<line.size()-1;index++)
      {
        c_aux<<line[index];
      } 
      c=stof(c_aux.str());

      adjList[a].push_back(b);
      adjList[b].push_back(a);
      adjListCostOrder[a].push_back(b);
      adjListCostOrder[b].push_back(a);
      adjListCost[a].push_back(c);
      adjListCost[b].push_back(c);
    }
    reader.close();

    //Insertion Sort
    for(int x=0;x<nodes;x++)
    {
      for (int i=1;i<=adjList[x].size()-1;i++)
      {
        for (int j=i;j>0 && adjList[x][j]<adjList[x][j-1];j--)
        {
          swap(adjList[x],j,j-1);
        }
      }
    }
    //Insertion Sort
    for(int x=0;x<nodes;x++)
    {
      for (int i=1;i<=adjList[x].size()-1;i++)
      {
        for (int j=i;j>0 && adjListCost[x][j]<adjListCost[x][j-1];j--)
        {
          swap(adjListCostOrder[x],j,j-1);
          swap(adjListCost[x],j,j-1);
        }
      }
    }
    printAdjList();
    printAdjListWithCost();
  }
  else
  {
    std::cout<<"ERROR: No se pudo abrir el archivo"<<std::endl;
  }
}

void Graph::loadNodeNames(std::string doc_name)
{
  std::ifstream reader(doc_name);
  if(reader.is_open())
  {
    std::string line;
    while(reader.good())
    {
      getline(reader,line,'\n');
      names.push_back(line);
    }
    reader.close();
  }
  else
  {
    std::cout<<"ERROR: No se pudo abrir el archivo"<<std::endl;
  }
}

std::string Graph::number2string(int num)
{
  if(names.empty())
    return "No se han cargado nombres";
  return names[num];
}

std::string Graph::BFS(int start,int end) //Breadth-First Search
{
  std::queue<int> path_helper;
  bool check[nodes];
  std::stringstream visit;

  for(int i=0;i<nodes;i++)
  {
    check[i]=false;
  }

  check[start] = true;
  path_helper.push(start);
  if(start==end)
    goto next;

  for(int i=start;i<nodes;i++)
  {
    for(int j=0;j<adjList[i].size();j++)
    {
      if(check[adjList[i][j]]==false)
      {
        check[adjList[i][j]]=true;
        path_helper.push(adjList[i][j]);
        if(adjList[i][j]==end)
          goto next;
      }
    }
  }
  next: 
  
  pathBFS(start,end,path_helper,visit);
  //std::cout<<visit.str()<<std::endl;
  return visit.str();
}

void Graph::pathBFS(int start,int end,std::queue<int> &q,std::stringstream &visit)
{
  bool check[nodes];
  int prev[nodes];

  visit<<"Camino:";
  for(int i=0;i<nodes;i++)
  {
    check[i]=false;
    prev[i]=-1;
  }

  check[q.front()] = true;
  prev[q.front()] = start;  
  
  while(!q.empty())
  {
    for(int i=0;i<adjList[q.front()].size();i++)
    {
      if(check[adjList[q.front()][i]]==false)
      {
        check[adjList[q.front()][i]] = true;
        prev[adjList[q.front()][i]] = q.front();
      }      
    }
    q.pop();
  }

  int path_finder = end;
  std::vector<int> path_holder;
  while (true)
  {
    if(path_finder == prev[path_finder])
    {
      path_holder.push_back(path_finder);
      break;
    }
    path_holder.push_back(path_finder);
    path_finder=prev[path_finder];
  }
    std::cout<<"good"<<std::endl;

  for(int i=path_holder.size()-1;i>=0;i--)
  {
      visit<<"("<<path_holder[i]<<")"<<number2string(path_holder[i])<<" ";
  }
}

std::string Graph::printAdjList()
{
  std::stringstream str;
  for(int i=0;i<nodes;i++)
  {
    str<<"vertex "<<i<<" : ";
    for(int j=0;j<adjList[i].size();j++)
    {
      str<<adjList[i][j];
      str<<" ";
    }
  }
  //std::cout<<str.str()<<std::endl;
  return str.str();
}

std::string Graph::printAdjListWithCost()
{
  std::stringstream str;
  for(int i=0;i<nodes;i++)
  {
    str<<"vertex "<<i<<" : ";
    for(int j=0;j<adjList[i].size();j++)
    {
      str<<adjListCostOrder[i][j];
      str<<" = ";
      str<<adjListCost[i][j];
      str<<" | ";
    }
    str<<"\n";
  }
  //std::cout<<str.str();
  return str.str();
}

/*std::string Graph::Dijkstra(int start,int end)
{
  std::queue<int> tourist;
  bool permanent[nodes];
  bool queue_check[nodes];
  float price_path[nodes][2];//[][0]=costo del arco, [][1]=nodo del que viene;

  //Set initial values
  for(int i=0;i<nodes;i++)
  {
    permanent[i]=false;
    queue_check[i]=false;
    price_path[i][0]=999999;
    price_path[i][1]=-1;
  }

  for(int i=0;i<nodes;i++)
  {
    std::cout<<price_path[i][0]<<"-"<<price_path[i][1]<<std::endl;
  }

  //filling price_path
  int actual = start;
  tourist.push(start);
  queue_check[actual]=true;

  while(!tourist.empty())
  {
    actual=tourist.front();
    permanent[actual]=true;
    for(int i=0;i<adjListCostOrder[actual].size();i++)
    {
      if(!queue_check[adjListCostOrder[actual][i]])//If neighbor node hasn't been add to the queue
      {
        tourist.push(adjListCostOrder[actual][i]);
        queue_check[adjListCostOrder[actual][i]]=true;
      }
      if(!permanent[adjListCostOrder[actual][i]])
      {
        if(price_path[actual][0]==999999)
        {
          if(price_path[adjListCostOrder[actual][i]][0]>adjListCost[actual][i])
          {
            price_path[adjListCostOrder[actual][i]][0]=adjListCost[actual][i];
            price_path[adjListCostOrder[actual][i]][1]=actual;
          }
        }
        else
        {
          std::cout<<"entre"<<std::endl;
          if(price_path[adjListCostOrder[actual][i]][0]>(adjListCost[actual][i]+price_path[adjListCostOrder[actual][i]][0]))
          {
            std::cout<<"entre2"<<std::endl;
            price_path[adjListCostOrder[actual][i]][0]=adjListCost[actual][i]+price_path[adjListCostOrder[actual][i]][0];
            price_path[adjListCostOrder[actual][i]][1]=actual;
          }
        }
      }
    }
    tourist.pop();
  }

  std::cout<<"-----------------"<<std::endl;

  for(int i=0;i<nodes;i++)
  {
    std::cout<<price_path[i][0]<<"-"<<price_path[i][1]<<std::endl;
  }

  //getting path of minimum cost
  std::cout<<price_path[end][1]<<std::endl;
  if(price_path[end][1]==-1)
  {
    std::cout<<"No se puede llegar del punto inicial seleccionado al destino seleccionado"<<std::endl;
    return "Camino no encontrado";
  }

  std::stack<int> path_helper;
  std::stringstream min_path;
  int index_actual=end;
  while (true)
  {
    path_helper.push(index_actual);
    if(index_actual==start)
    {
      break;
    }
    index_actual=(int)price_path[index_actual][1];
  }
  while(!path_helper.empty())
  {
    min_path<<path_helper.top()<<" ";
    path_helper.pop();
  }

  return min_path.str();
}*/

std::string Graph::searchByNameBFS(std::string node1,std::string node2)
{
  int nd1= string2number(node1);
  int nd2= string2number(node2);

  if((nd1==-1)||(nd2==-1))
  {
    return "ERROR: una o ambas de las entradas no coinciden con ningún resultado. Revise los nombres de los nodos en el menú si es necesario.";
  }

  return BFS(nd1,nd2);
}

void Graph::showInfo()
{
  std::cout<<nodes<<" nodos y "<<nodes*2<<" arcos fueron cargados exitosamente\n\n";
}

int Graph::string2number(std::string str)
{
  for(int i=0;i<nodes;i++)
  {
    if(names[i]==str)
      return i;
  }
  return -1;
}

void Graph::neighborNodes(int node)
{
  std::cout<<"\n------------------------\nConectan:\n";
  for(int i=0;i<adjList[node].size();i++)
  {
    std::cout<<"("<<adjList[node][i]<<")"<<number2string(adjList[node][i])<<std::endl;
  }
  std::cout<<"\n";
}

void Graph::showAllNodes()
{
  std::cout<<"All nodes:"<<std::endl;
  for(int i=0;i<nodes;i++)
  {
    std::cout<<"("<<i<<")"<<names[i]<<std::endl;
  }
  std::cout<<"\n";
}

void Graph::neighborNodesString(std::string nameNode)
{
  neighborNodes(string2number(nameNode));
}

#endif