#include <iostream>
#include <fstream>
#include <utility>
#include <queue>
#include <cmath>
using namespace std;
int length,width;
int labirinth1[1000][1000];
int labirinth2[1000][1000];
int heuristic1[1000][1000];
int heuristic2[1000][1000];
int numberOfWalls;
pair<int,int> Start, End,solutionPoint;
int directionsOnVertical[]={1,-1,0,0};
int directionsOnHorizontal[]={0,0,-1,1};
bool pointsValid(int x, int y)
{
    if(x<0||x>=length||y<0||y>=width)
        return false;
    return true;
}
struct compareHeuristic1
 {
   bool operator()(const pair<int,int>& l, const pair<int,int>& r)
   {
       return heuristic1[l.first][l.second]+labirinth1[l.first][l.second] > heuristic1[r.first][r.second]+labirinth1[r.first][r.second];
   }
 };
 struct compareHeuristic2
 {
   bool operator()(const pair<int,int>& l, const pair<int,int>& r)
   {
       return heuristic2[l.first][l.second]+labirinth2[l.first][l.second] > heuristic2[r.first][r.second]+labirinth2[r.first][r.second];
   }
 };
 vector<pair<int,int>> getPath(int labirinthMatrix[1000][1000],pair<int,int> pointOfStart)
 {
     vector<pair<int,int>> path;
     path.push_back(pointOfStart);

     while(labirinthMatrix[pointOfStart.first][pointOfStart.second]>1)
     {
         for(int i=0;i<4;i++)
            {
                int dx=pointOfStart.first+directionsOnHorizontal[i];
                int dy=pointOfStart.second+directionsOnVertical[i];
                if(labirinthMatrix[dx][dy]==labirinthMatrix[pointOfStart.first][pointOfStart.second]-1)
                {
                    path.push_back(make_pair(dx,dy));
                    pointOfStart.first=dx;
                    pointOfStart.second=dy;
                }
            }
    }
    return path;
 }
int main()
{
    cin>>length>>width>>numberOfWalls;
    for(int i=0;i<numberOfWalls;i++)
    {
        int x,y;
        cin>>x>>y;
        labirinth1[x][y]=-1;
        labirinth2[x][y]=-1;
    }
    cin>>Start.first>>Start.second>>End.first>>End.second;
    for(int i=0;i<length;i++)
        for(int j=0;j<width;j++)
    {
         heuristic1[i][j]=sqrt((Start.first-i)*(Start.first-i)+(Start.second-j)*(Start.second-j));
         heuristic2[i][j]=sqrt((End.first-i)*(End.first-i)+(End.second-j)*(End.second-j));
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, compareHeuristic1 > queueForStart;
    priority_queue<pair<int,int>, vector<pair<int,int>>, compareHeuristic2 > queueForEnd;
    queueForStart.push(Start);
    queueForEnd.push(End);
    labirinth1[Start.first][Start.second]=labirinth2[End.first][End.second]=1;
    bool pathsMeet=false;
    while(!pathsMeet)
    {
        pair<int,int> frontOfQueueforStart, frontOfQueueforEnd;
        frontOfQueueforStart=queueForStart.top();
        queueForStart.pop();
        frontOfQueueforEnd=queueForEnd.top();
        queueForEnd.pop();
        if(frontOfQueueforEnd==frontOfQueueforStart)
            {pathsMeet=true;
        cout<<labirinth1[frontOfQueueforEnd.first][frontOfQueueforEnd.second]+labirinth2[frontOfQueueforEnd.first][frontOfQueueforEnd.second]-1;
        solutionPoint.first=frontOfQueueforEnd.first;
        solutionPoint.second=frontOfQueueforEnd.second;}
        else{
            for(int i=0;i<4;i++)
            {
                int dx=frontOfQueueforStart.first+directionsOnHorizontal[i];
                int dy=frontOfQueueforStart.second+directionsOnVertical[i];
                if(pointsValid(dx,dy)==true&&(labirinth1[dx][dy]==0||labirinth1[dx][dy]>labirinth1[frontOfQueueforStart.first][frontOfQueueforStart.second]+1))
                {
                    labirinth1[dx][dy]=labirinth1[frontOfQueueforStart.first][frontOfQueueforStart.second]+1;
                    queueForStart.push(make_pair(dx,dy));
                }
            }

            for(int i=0;i<4;i++)
            {
                int dx=frontOfQueueforEnd.first+directionsOnHorizontal[i];
                int dy=frontOfQueueforEnd.second+directionsOnVertical[i];
                if(pointsValid(dx,dy)==true&&(labirinth2[dx][dy]==0||labirinth2[dx][dy]>labirinth2[frontOfQueueforEnd.first][frontOfQueueforEnd.second]+1))
                {
                    labirinth2[dx][dy]=labirinth2[frontOfQueueforEnd.first][frontOfQueueforEnd.second]+1;
                    queueForEnd.push(make_pair(dx,dy));
                }
            }
        }
    }
    vector<pair<int,int>> path1,path2;
    path1=getPath(labirinth1,solutionPoint);
    path2=getPath(labirinth2,solutionPoint);
    cout<<endl;
    for(int i=path1.size()-1;i>=0;i--)
        cout<<path1[i].first<<" "<<path1[i].second<<endl;

    for(int i=1;i<path2.size();i++)
        cout<<path2[i].first<<" "<<path2[i].second<<endl;

    return 0;
}
