#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;
struct city
{
int visited;
int index;
char name[10];
double dist;
int prev;
};
class Graph
{
private:
city *cities;
int **distmatrix;
int tcost;
 public:
int numcities;
int vcount;
 void CreateGraph();
14
 void adddistance();
 void tspnn(int start);
 void displaymatrix();
 void optimalpath(int start);
 void recprint(int v,int & dist,int s);
 //methods for dynamic programming
 void tspdp(int city);
 void clearcities();
 int least(int city);
 //methods for Backtracking
 unsigned int tspback(unsigned int **best_tour);
 void tspback_recursive(unsigned int *best_tour, unsigned int *best_tour_cost, unsigned int
*partial_tour,
 unsigned int *partial_tour_cost, unsigned int level);
 void swap(unsigned int *a, unsigned int *b);
 void displaytour(unsigned int *besttour);
 void displaycities();
};
void Graph::displaycities()
{
int i;
for(i=0;i<numcities;i++)
 cout<<"\n"<<cities[i].name;
}
void Graph::displaymatrix()
{
int i,j;
for(i=0;i<numcities;i++)
 {
 for(j=0;j<numcities;j++)
 {
 cout<<distmatrix[i][j]<<"\t";
 }
 cout<<endl;
 }
}
15
void Graph::CreateGraph()
{
int i,j,n;
char tempch[15];
int wrongcity=0;
tcost=0;
cout<<"\n Enter Number of Cities :";
cin>>n;
numcities=n;
cities=new city[n];
for(i=0;i<n;i++)
{
cities[i].visited=0;
cities[i].index=i;
cities[i].dist=9999;
cout<<"\nEnter the City Name:";
cin>>tempch;
for(j=0;j<i;j++)
{
if(strcmp(tempch,cities[j].name)==0)
{
cout<<"Wrong input\n";
cout<<"Enter the city name again\n";
wrongcity=1;
--i;
break;
}
 }
 if(wrongcity==1)
 {
 wrongcity=0;
 continue;
 }
 else
 strcpy(cities[i].name,tempch);
 
16
cities[i].prev=-1;
 wrongcity=0;
 }
 distmatrix=new int*[n];
 for(i=0;i<n;i++)
 distmatrix[i]=new int[n];
 for(i=0;i<n;i++)
 for(j=0;j<n;j++)
 distmatrix[i][j]=0;
 }
 void Graph::adddistance()
 {
 int from,to,dist,count=0;
 int i,j;
char choice;
 for(i=0;i<numcities;i++)
 {
 for(j=0;j<numcities;j++)
 {
 //if(i==j)
 distmatrix[i][j]=0;
 //else
 //distmatrix[i][j]=999999;
 }
}
 do
 {
 cout<<"\n Enter Source City Index:";
 cin>>from;
 cout<<"\n Enter Destination City Index:";
 cin>>to;
 if((from==to)||(from>=numcities)||(to>=numcities))
 {
cout<<"Wrong Input";
 choice='y';
 continue;
 }
17
 cout<<"\Enter Distance: "<<from<<" To "<<to<<":";
 cin>>dist;
 if(dist<=0)
 {
cout<<"Wrong Input";
choice='y';
 continue;
 }
 distmatrix[from][to]=dist;
 cout<<"Do you add another distance(y/n)?:";
cin>>choice;
 count++;

 }while(choice!='y');
}
void Graph::tspnn(int start)
{
int from,neighbour,i,min,count;
 cities[start].visited=1;
vcount=1;
from=start;
for(count=1;count<numcities;count++)
 {
 min=9999;
 for(i=0;i<numcities;i++)
{
if((cities[i].visited==0)&&(min>distmatrix[from][i])&&(distmatrix[from][i]!=0))
{
min=distmatrix[from][i];
 neighbour=i;
}
}
 cities[neighbour].visited=1;
 cities[neighbour].dist=min;
cities[neighbour].prev=from;
from=neighbour;

if(min!=9999)
{
 tcost+=min;
vcount++;
 }
 else
 break;
}
 if(vcount<numcities)
 {
 cout<<"\n Error: No Path Exist..No Hamiltonian Cycle exist";
 }
 else
 {
 cities[start].prev=neighbour;
 cities[start].dist=distmatrix[neighbour][start];

optimalpath(start);
tcost+=distmatrix[neighbour][start];
 }
}
void Graph::optimalpath(int start)
{
cout<<"\n Optimal Path Using Greedy Nearest Neighbour Algorithm";
cout<<"\n Opatimal Path from Starting City "<<cities[start].name<<" Index:"<<start<<"\n";
int totdist=0,i;
cout<<"\n PATH:";
recprint(cities[start].prev,totdist,start);
cout<<" ------ "<<cities[start].dist<<" ------- ";
cout<<cities[start].name<<"["<<start<<"]";
cout<<"\n Total Path Length:"<<totdist;
}
void Graph::recprint(int v,int &dist,int s)
{
if(v!=s)
{

recprint(cities[v].prev,dist,s);
cout<<" ------- "<<cities[v].dist<<" ------ ";
}
 dist=dist+cities[v].dist;
 cout<<cities[v].name<<"["<<v<<"]";
}
//Dynamic Programming
void Graph::clearcities()
{
int i;
for(i=0;i<numcities;i++)
{
cities[i].visited=0;
cities[i].prev=-1;
cities[i].dist=9999;
}
tcost=0;
}
int Graph::least(int c)
{
int i,nc=999;
int min=999,kmin;
for(i=0;i<numcities;i++)
{
if((distmatrix[c][i]!=0)&&(cities[i].visited==0))
if(distmatrix[c][i]+distmatrix[i][c] < min)
{
min=distmatrix[i][0]+distmatrix[c][i];
kmin=distmatrix[c][i];
nc=i;
}
}
if(min!=999)
 {
 tcost+=kmin;

 cout<<"-------"<<kmin<<"----------";
 }
return nc;
}
void Graph::tspdp(int city)
{
int i,ncity;
static int vcount=0;
 vcount++;
cities[city].visited=1;
cout<<cities[city].name<<"["<<city<<"]";
ncity=least(city);
if(ncity==999)
{
ncity=0;
cout<<"----"<<distmatrix[city][ncity]<<"----";
cout<<cities[ncity].name<<"["<<ncity<<"]";
tcost+=distmatrix[city][ncity];
 cout<<"\n Total Path Cost: "<<tcost;
if(vcount<numcities)
cout<<"\n****Graph Error: Invalid Path\n";
return;
}
tspdp(ncity);
}
//BackTracking Functions
void Graph::swap(unsigned int *a, unsigned int *b)
{
 unsigned int temp = *a;
 *a = *b;
 *b = temp;
}

void Graph::tspback_recursive(unsigned int *best_tour, unsigned int *best_tour_cost, unsigned
int *partial_tour,
 unsigned int *partial_tour_cost, unsigned int level)
{
int **adjmat=distmatrix;
unsigned int order=numcities;
 if (level == order - 1) {
 /* Add last two edges to complete the tour */
 unsigned int tour_cost = *partial_tour_cost
 + adjmat[partial_tour[order - 2]][partial_tour[order - 1]]
 + adjmat[partial_tour[order - 1]][0];
 if (*best_tour_cost == 0 || tour_cost < *best_tour_cost) {
 /* Best tour so far */
 memcpy(best_tour, partial_tour, order * sizeof(unsigned int));
 *best_tour_cost = tour_cost;
 }
 }
 else {
 unsigned int i;
 for (i = level; i < order; i++) {
 if (*best_tour_cost == 0
 || *partial_tour_cost + adjmat[partial_tour[level - 1]][partial_tour[i]]
 < *best_tour_cost)
 {
 /* Next permutation */
 swap(&partial_tour[level], &partial_tour[i]);
 unsigned int cost = adjmat[partial_tour[level - 1]][partial_tour[level]];
 *partial_tour_cost += cost;
 tspback_recursive(best_tour, best_tour_cost,partial_tour, partial_tour_cost, level +
1);
 *partial_tour_cost -= cost;
 swap(&partial_tour[level], &partial_tour[i]);
 }
 }
 }
}
unsigned int Graph::tspback(unsigned int **best_tour)

{
int **adjmat=distmatrix;
unsigned int order=numcities;
 unsigned int i;
 unsigned int best_tour_cost = 0;
 unsigned int partial_tour_cost = 0;
 unsigned int *partial_tour = (unsigned int *)malloc(order * sizeof(unsigned int));
 *best_tour = (unsigned int *)malloc(order * sizeof(unsigned int));
 if (partial_tour == NULL || *best_tour == NULL) {
 free(partial_tour);
 free(*best_tour);
 *best_tour = NULL;
 return 0;
 }
 for (i = 0; i < order; i++) {
 partial_tour[i] = i;
 }
 tspback_recursive(*best_tour, &best_tour_cost, partial_tour,&partial_tour_cost, 1);
 free(partial_tour);
 return best_tour_cost;
}
void Graph::displaytour( unsigned int *besttour)
{
int i;
for(i=0;i<numcities;i++)
{
 cout<<cities[besttour[i]].name<<"["<<besttour[i]<<"]";
 if(i<numcities-1)
 cout<<"------"<<distmatrix[besttour[i]][besttour[i+1]]<<"------";
}
cout<<"------"<<distmatrix[besttour[numcities-1]][besttour[0]]<<"------";
 cout<<cities[besttour[0]].name<<"["<<besttour[0]<<"]";
}
int main()
{ Graph g1;
g1.CreateGraph();
23
g1.adddistance();
g1.displaymatrix();
 g1.displaycities();
//Greedy Technique
g1.tspnn(0);
 if(g1.vcount==g1.numcities)
{
//Dynamic Programming
cout<<"\n\n OPTIMAL PATH USING DYNAMIC PROGRAMMING \n\n ";
g1.clearcities();
g1.tspdp(0);
//Backtracking Technique
unsigned int *best_tour;
unsigned int cost = g1.tspback(&best_tour);
 cout<<"\n\n OPTIMAL PATH USING BACKTRACING PROGRAMMING: \n";
 cout<<"\n Best Path: \n";
g1.displaytour(best_tour);
cout<<"\nPath Length:"<<cost;
 free(best_tour);
}
} 
