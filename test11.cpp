#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;


void storeInMap(string str,int row,map<pair<int,int>,int>& matrix){
   string word="";
   int count=0;
   int size=str.length();
   for(int i=0;i<size;i++){
       if(str[i] == ' '){ 
           pair<int,int> pos=make_pair(row,count);
           matrix[pos]=stoi(word);
           count++;
           word="";
       }else{ 
           word=word+str[i];
        }
   }
    pair<int,int> pos=make_pair(row,count);
    matrix[pos]=stoi(word);

}

long long findSum(map<pair<int,int>,int> matrix){
    int sum=0;
    for(map<pair<int,int>,int>::iterator i=matrix.begin();i!=matrix.end();i++){
        sum+= i->second;
    }
    return sum ;
}

vector<pair<int,int> > posOfZero(map<pair<int,int>,int> matrix){
       vector<pair<int,int> > v;
       for(map<pair<int,int>,int>::iterator i=matrix.begin();i!=matrix.end();i++){
        if(i->second==0){
            v.push_back(i->first);
        }
    }
    return v;
}

long long typeI(map<pair<int,int>,int>& matrix,int row,int col,bool b){
    int r=0,d=0,x=0,y=0,value,count;
       if(b==true){
           r=1; 
           d=2;
        }else{
           r=2;
           d=1;
        }
       for(map<pair<int,int>,int>::iterator i=matrix.begin();i!=matrix.end();i++){
        if(i->second==0){
            count=0;
            value=0;
            int left=-1;
            int right=-1;
            int up=-1;
            int down=-1;
            int diag=-1;
            x=(i->first).first;
            y=(i->first).second;
            if(y-1>=0){left=matrix[make_pair(x,y-1)]; count++;}//有left point
            if(y+1<col){right=matrix[make_pair(x,y+1)]; count++;}//有right point
            if(x-1>=0){up=matrix[make_pair(x-1,y)]; count++;}//有up point
            if(x+1<row){down=matrix[make_pair(x+1,y)]; count++;}//有down point
  
            if(count==4){//general case
                value=left+r;
                while(value<=up){value=value+2;}
                if((value >= right && right>0)|| (value>=down && down>0)){
                    value=-1;
                }
            }

            if(count==3){//edge case
                if(left<0){value=up+d;}else{value=left+r;}
                while(value<=up){value=value+2;}
                if((value>=right && right>0)||(value>=down && down>0)){
                     value=-1;
                }      
            }

            if(count==2){//corner case
                if(left<0 && up<0 && right>0){//up left
                    if(right>0){
                        value=right-r;
                        if(value<=0){ value=-1;}
                        while(value>=3){value=value-2;}
                    }else if(down>0){
                        value=down-d;
                        if(value<=0){ value=-1;}
                        while(value>=3){value=value-2;}
                    }else if(diag>0){
                        diag=matrix[make_pair(x+1,y+1)];
                        if(diag%2==0){value=1;}
                        if(diag%2==1){value=2;}
                    }        
                }             
                if(down<0 && left<0){//left down
                    value=up+d;
                    if(value>=right && right>0){ value=-1;}
                }
                if(up<0 && right<0){//up right
                    value=left+r;
                    if(value>=down && down>0){value=-1;}
                } 
                 if(right<0 && down<0){//down right
                    value=left+r;
                    while(value<=up){value=value+2;}
                 }

            }
            if(value==-1){
               // cout<<"-1"<<endl;
                return -1;
            }else{ 
                i->second=value;
                //cout<<x<< " "<<y<<":value"<<value<<endl;
            }
           
        } 
       }   
        return findSum(matrix);
    }   

 

int main(int argc, const char * argv[]){
    string line="";
    //long long sum;
    map<pair<int,int>,int> matrix;
    vector<pair<int,int> > zeros;

    getline(cin,line);
    int len=line.length();
    int pos=line.find(' ');
    int m=stoi(line.substr(0,pos));//row
    int n=stoi(line.substr(pos+1,len-pos-1));//col
    int row=0;
    int count=m;
    
    while(!cin.eof() && count>0){
       getline(cin,line);
       storeInMap(line,row,matrix);
       row++; 
       count--;     
   }
    
    //if 1xn or nx1,don't not need to care even/odd
     if(matrix[make_pair(0,1)]==1 || matrix[make_pair(1,0)]==1){
        cout<<"-1"<<endl;
        return 0;
    }
    
    int x,y,left,right,down,up;
    if(m==1){
        zeros=posOfZero(matrix);
        int count=zeros.size();   
        if(count==0)
            cout<<findSum(matrix)<<endl;
        for(int i=0;i<count;i++){
            x=zeros[i].first;
            y=zeros[i].second;
            if(y==0){
                matrix[make_pair(x,y)]=1;
                continue;    
            } 
            left=matrix[make_pair(0,y-1)];
            right=matrix[make_pair(0,y+1)];
            matrix[make_pair(0,y)]=left+1;
            if(y<n-1 && matrix[make_pair(0,y)]>=right && right!=0)
                cout<<"-1"<<endl;
                return 0;
        }
        cout<<findSum(matrix)<<endl;
    }

    if(n==1){
        zeros=posOfZero(matrix);
        int count=zeros.size();
        if(count==0)
            cout<<findSum(matrix)<<endl;
        for(int i=0;i<count;i++){
            x=zeros[i].first;
            y=zeros[i].second;
            if(y==0){
                matrix[make_pair(x,y)]=1;
                continue;    
            } 
            up=matrix[make_pair(x-1,0)];
            down=matrix[make_pair(x+1,0)];
            matrix[make_pair(x,0)]=up+1;
            if(x<m-1 && matrix[make_pair(x,0)]>=right && right !=0)
                cout<<"-1"<<endl;
                return 0;
        }
        cout<<findSum(matrix)<<endl;
    }
    
    int A=matrix[make_pair(0,0)];
    int B=matrix[make_pair(0,1)];
    int C=matrix[make_pair(1,0)];
    int D=matrix[make_pair(1,1)];
    int temp=0;
    //typeI
    if(A==0 && B==0 && C==0 && D==0){
        matrix[make_pair(0,0)]=1;
        matrix[make_pair(0,1)]=2;
        matrix[make_pair(1,0)]=3;
        matrix[make_pair(1,1)]=4;
        cout<<typeI(matrix,m,n,true)<<endl;
          
   }
  
    if(((A!=0 || D!=0) && C==0 && B==0)||(B-A==1||C-A==2||D-B==2||D-C==1)){
        cout<<typeI(matrix,m,n,true)<<endl;  
    }

    if((C!=0 || B!=0)&& A==0 && D==0){
        matrix[make_pair(0,0)]=1;
        if(C-A==1 || B-A==2){
            cout<<typeI(matrix,m,n,false)<<endl;;
        }
        if(C-A==2 || B-A==1){
             cout<<typeI(matrix,m,n,true)<<endl;
        }
    }

    if(B-A==2||C-A==1||D-B==1||D-C==2){
        cout<<typeI(matrix,m,n,false)<<endl;
    }
  
    return 0;
}
