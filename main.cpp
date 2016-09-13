#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
class sudoku{
    unsigned short table[9][9][9];
    unsigned short solve[9][9];
public:
    void ini(){
        for(auto y=0; y<9; y++)
            for(auto x=0; x<9; x++)
                for(auto z=0; z<9; z++)
                    table[y][x][z]=z+1;
    }
    void loadsolve(char *file){
        register int y=0;
        ifstream file2(file);
        while(!file2.eof()){
            for(auto x=0;x<9;x++)file2>>solve[y][x];
            y++;
        }
        file2.close();
    }
    bool soluciono(){
     for(auto y=0; y<9; y++)
        for(auto x=0; x<9; x++)
            if(table[y][x][0]==0)return 0;
     return 1;
    }
    void showfile(){
        cout<<"\nSudoku :\n\n";
        for(auto y=0; y<9; y++){
           if(y%3==0)cout<<"\n";
            for(auto x=0; x<9; x++){
                if(x%3==0) cout<<"   ";
                if(solve[y][x]==0)cout<<"\4";
                else cout<<solve[y][x];
                cout<<" ";
            }
            cout<<"\n";
        }
    }
    void show(){
        cout<<"\nSudoku solucionado:\n\n";
        for(auto y=0; y<9; y++){
         if(y%3==0)cout<<"\n";
            for(auto x=0; x<9; x++){
                if(x%3==0) cout<<"   ";
                cout<<table[y][x][0]<<" ";
            }
            cout<<"\n";
        }
    }
    void re(int x,int y){
        register int aux[9],t=0;
        for(auto z=0; z<9; z++)
            if(table[y][x][z]!=0)
                aux[t++]=table[y][x][z];
        clean(x,y,0);
        for(auto z=0; z<t; z++) table[y][x][z]=aux[z];
    }
    void solvefull(){
        for(auto y=0; y<9; y++)
            for(auto x=0; x<9; x++){
                if(solve[y][x]!=0){
                    centerdel(x,y,solve[y][x]);
                    dc(x,y,solve[y][x]);
                    clean(x,y,solve[y][x]);
                }
            }
        solveaux();
    }
    void solveaux(){
        for(auto y=0; y<9; y++)
            for(auto x=0; x<9; x++)
                if(solve[y][x]==0){
                   register int v=select_V(x,y);
                    centerdel(x,y,v);
                    dc(x,y,v);
                    clean(x,y,v);
                }
    }
    void dc(int x,int y,int v){
        for(auto y1=0; y1<9; y1++)del(x,y1,v);
        for(auto x1=0; x1<9; x1++)del(x1,y,v);
    }
    void del(int x,int y, int va){
        for(auto i=0; i<9; i++)
            if(table[y][x][i]==va){table[y][x][i]=0;
            break;}
        re(x,y);
    }
    void clean(int x,int y,int val){
        for(auto z=0; z<9; z++)
            table[y][x][z]=0;
        table[y][x][0]=val;
    }
    int select_V(int x,int y){
        register short tam=size(x,y);
        if(tam==0)
            return table[y][x][0];
        return table[y][x][rand()%(tam)];
    }
    int size(int x,int y){
        register int t=0;
        for(auto z=0; z<9; z++)
            if(table[y][x][z]!=0) t++;
            else return t;
    }
    void centerdel(int x,int y,int v){
       register short wy=0,wye=0,wx=0,wxe=0;
        if(x>=0&&x<=2){wx=2;wxe=0;}
        else if(x>=3&&x<=5){wx=5;wxe=3;}
        else return;
        if(y>=0&&y<=2){wy=2;wye=0;}
        else if(y>=3&&y<=5){wy=5;wye=3;}
        else {wy=8;wye=6;}
        for(auto w=wy;w>=wye;w--)
            for(auto w1=wx;w1>=wxe;w1--) del(w1,w,v);
    }
};
main(){
    srand(time(NULL));
    register char *file=new char[20];
    cout<<"Nombre del archivo:";
    cin>>file;
    static sudoku *open=new sudoku;
    open->loadsolve(file);
    open->showfile();
    while(open->soluciono()==0){
        open->ini();
        open->solvefull();
    }
    open->show();
    delete open;
    system("pause");
}

