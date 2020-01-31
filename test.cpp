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
    long long sum=0;
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

int checkLR(pair<int,int> p,map<pair<int,int>,int> matrix){
    int value=0;
    int left=matrix[make_pair(p.first,p.second-1)];
    int right=matrix[make_pair(p.first,p.second+1)];
    if(right==0 || right>left+1){
       value=left+1;
      // return value;
    }
    if(left+1==right){
        return -1;
    }
    cout<<"value"<<value<<endl;
    return value;
}

int checkUD(pair<int,int> p,map<pair<int,int>,int> matrix){
    int value=0;
    int up=matrix[make_pair(p.first-1,p.second)];
    int down=matrix[make_pair(p.first+1,p.second)];
    if(down==0){
       value=up+1;
       return value;
    }
    if(up+1==down){
        return -1;
    }
     return (up+1);
}

//return true if it is valid right+1 down+2
int checkAroundI(pair<int,int> p,map<pair<int,int>,int>& matrix,int row,int col){
    int x=p.first;
    int y=p.second;
    //int left,right,up,down,diag=-1;
    int left=-1;
    int right=-1;
    int up=-1;
    int down=-1;
    int diag=-1;
    int value=0;
    if(y-1>=00){left=matrix[make_pair(x,y-1)];}//有left point
    if(y+1<col){right=matrix[make_pair(x,y+1)];}//有right point
    if(x-1>=0){up=matrix[make_pair(x-1,y)];}//有up point
    if(x+1<row){down=matrix[make_pair(x+1,y)];}//有down point

    if(left<0 && up<0){//left up
        if(right>0){
            value=right-1;
            while(value>=3){
                value=value-2;
            }
            matrix[p]=value;
            return value;
        }
        if(down>0){
            value=down-2;
            while(value>=3){
                value=value-2;
            }
            matrix[p]=value;
            return value;
        }
        if(matrix[make_pair(x+1,y+1)]>0){
            diag=matrix[make_pair(x+1,y+1)];
            if(diag%2==0){matrix[make_pair(x,y)]=1; return value;}
            if(diag%2==1){matrix[make_pair(x,y)]=2; return value;}
        }
    }

    if(up<0 && right<0){
        value=left+1;
        if(down==0||value<down){matrix[make_pair(x,y)]=value; return value;}
        if(value>=down && down!=0){return -1;}
    }

    if(left<0 && down<0){
        value=up+2;
        if(right==0||value<right){matrix[make_pair(x,y)]=value; return value;}
        if(value>=right && right!=0){return -1;}
    }

    if(right<0 && down<0){
        value=left+1;
        if(value>up){matrix[make_pair(x,y)]=value; return value;}
        while(value<=up){value=value+2;}
        matrix[make_pair(x,y)]=value;
        return value;
    }
    
    if(left<0 && up>0 && right>=0 && down >=0 ){
        value=up+2;
        if((value>=right && right!=0)||(value>=down && down!=0)){return -1;}
        if((right==0||value<right)&&(down==0||value<down)){
            matrix[make_pair(x,y)]=value;
            return value;
            }
    }
    
    if(right<0 && up>0 && left>0 && down>=0){
        value=up+2;
        while(value<=left){value=value+2;}
        if(value>=down && down!=0){return -1;}
        if(value<down ||down==0){matrix[make_pair(x,y)]=value;return value;}
    }
    //checkLR
    if(left>=0 && right>=0){
        if(left+1==right){return -1;}
        value=left+1;
            if(up>=0 && down >=0){//for general point with 4 nonde around
                if(up+2==down){return -1;}
                while (up>=value){value=value+2;}
                if(value>=down && down!=0){return -1;}
                matrix[p]=value;  
                return value;      
            }
            if(up<0 && down>=0){//for upper boundary
                if(down==0){matrix[p]=value;return value;}
                if(value>=down && down!=0){return -1;}
            }
            if(up>=0 && down<0){//for lower bounndary
               while (up>=value){value=value+2;}
               matrix[p]=value; 
               return value;      
            }

    }
    return value;
}

int checkAroundII(pair<int,int> p,map<pair<int,int>,int>& matrix,int row,int col){
    int x=p.first;
    int y=p.second;
    int left=-1;
    int right=-1;
    int up=-1;
    int down=-1;
    int diag=-1;
    int value=0;
    if(y-1>0){left=matrix[make_pair(x,y-1)];}//有left point
    if(y+1<col){right=matrix[make_pair(x,y+1)];}//有right point
    if(x-1>0){up=matrix[make_pair(x-1,y)];}//有up point
    if(x+1<row){down=matrix[make_pair(x+1,y)];}//有down point

    if(left<0 && up<0){//left up
        if(right>0){
            value=right-2;
            while(value>=3){
                value=value-2;
            }
            matrix[p]=value;
            return value;
        }
        if(down>0){
            value=down-1;
            while(value>=3){
                value=value-2;
            }
            matrix[p]=value;
            return value;
        }
        if(matrix[make_pair(x+1,y+1)]>0){
            diag=matrix[make_pair(x+1,y+1)];
            if(diag%2==0){matrix[make_pair(x,y)]=1; return value;}
            if(diag%2==1){matrix[make_pair(x,y)]=2; return value;}
        }
    }

    if(up<0 && right<0){
        value=left+2;
        if(down==0||value<down){matrix[make_pair(x,y)]=value; return value;}
        if(value>=down && down!=0){return -1;}
    }

    if(left<0 && down<0){
        value=up+1;
        if(right==0||value<right){matrix[make_pair(x,y)]=value; return value;}
        if(value>=right && right!=0){return -1;}
    }

    if(right<0 && down<0){
        value=left+2;
        if(value>up){matrix[make_pair(x,y)]=value; return value;}
        while(value<=up){value=value+2;}
        matrix[make_pair(x,y)]=value;
        return value;
    }
    
    if(left<0){
        value=up+1;
        if((value>=right && right!=0)||(value>=down && down!=0)){return -1;}
        if((right==0||value<right)&&(down==0||value<down)){matrix[make_pair(x,y)]=value;return value;}
    }
    
    if(right<0){
        value=up+1;
        while(value<=left){value=value+2;}
        if(value>=down && down!=0){return -1;}
        if(value<down ||down==0){matrix[make_pair(x,y)]=value;return value;}
    }
    //checkLR
    if(left>=0 && right>=0){
        if(left+2==right){return -1;}
        value=left+2;
            if(up>=0 && down >=0){//for general point with 4 nonde around
                if(up+1==down){return -1;}
                while (up>=value){value=value+2;}
                if(value>=down && down!=0){return -1;}
                matrix[p]=value;  
                return value;      
            }
            if(up<0 && down>=0){//for upper boundary
                if(down==0){matrix[p]=value;return value;}
                if(value>=down && down!=0){return -1;}
            }
            if(up>=0 && down<0){//for lower bounndary
               while (up>=value){value=value+2;}
               matrix[p]=value; 
               return value;      
            }

    }
    return 1;
}

long long typeI(map<pair<int,int>,int>& matrix,int r,int c){
    vector<pair<int,int> > z;
    int temp=0;
    z=posOfZero(matrix);
    int count=z.size();
    if(count==0)
        cout<<findSum(matrix)<<endl;
    for(int i=0;i<count;i++){
     temp=checkAroundI(z[i],matrix,r,c);
     //cout<<z[i].first<<" "<<z[i].second<<": : "<<temp<<endl;
     if(temp== -1){
         return -1;
     }
    }
    return findSum(matrix);
}

long long typeII(map<pair<int,int>,int>& matrix,int r,int c){
    vector<pair<int,int> > z;
    int temp=0;
    z=posOfZero(matrix);
    int count=z.size();
    if(count==0)
        cout<<findSum(matrix)<<endl;
    for(int i=0;i<count;i++){
     temp=checkAroundII(z[i],matrix,r,c);
     if(temp== -1){
         return -1;
     }
    }
    return findSum(matrix);
}




int main(){
    // ifstream in;
    // in.open("testcase1.txt");
    string line="";
    //string sum;
    map<pair<int,int>,int> matrix;
    vector<pair<int,int> > zeros;

    // if(in.fail()){
    //     cerr<<"Open fail"<<endl;
    // }

    getline(cin,line);
    int len=line.length();
    int pos=line.find(' ');
    int m=stoi(line.substr(0,pos));//row
    int n=stoi(line.substr(pos+1,len-pos-1));//col
    //çcout<<m<<" "<<n<<endl;
    int row=0;
    int count=m;
    

    while(!cin.eof() && count>0){
       getline(cin,line);
       storeInMap(line,row,matrix);
       //cout<<"row:"<<row<<" line:"<<line<<endl;
       row++; 
       count--;     
   }
    
   // cout<<"read end"<<endl;
   // in.close();

    //if 1xn or nx1,don't not need to care even/odd
     if(matrix[make_pair(0,1)]==1 || matrix[make_pair(1,0)]==1){
        cout<<"-1"<<endl;
        return 0;
    }

    if(m==1){
        zeros=posOfZero(matrix);
        int count=zeros.size();
        if(count==0)
            cout<<findSum(matrix)<<endl;
        for(int i=0;i<count;i++){
            if(zeros[i].second==0){
                matrix[make_pair(0,0)]=1;
                continue;
            } 
            if(zeros[i].second==n-1){
                 matrix[make_pair(0,n-1)]=matrix[make_pair(0,n-2)]+1;
                 continue;
            }
            matrix[zeros[i]]=checkLR(zeros[i],matrix);
            if(matrix[zeros[i]]==-1){
                cout<<"-1"<<endl;
                return 0;
            }
        }
        cout<<findSum(matrix)<<endl;
    }

    if(n==1){
        zeros=posOfZero(matrix);
        int count=zeros.size();
        if(count==0)
            cout<<findSum(matrix)<<endl;
        for(int i=0;i<count;i++){
            cout<<zeros[i].first<<" "<<zeros[i].second<<endl;
            if(zeros[i].first==0){
                matrix[make_pair(0,0)]=1;
                continue;
            } 
            if(zeros[i].first==m-1){
                 matrix[make_pair(m-1,0)]=matrix[make_pair(m-2,0)]+1;
                 continue;
            }
            matrix[zeros[i]]=checkUD(zeros[i],matrix);
            if(matrix[zeros[i]]==-1){
                cout<<"-1"<<endl;
                return 0;
            }
        }
    }
   
    int A=matrix[make_pair(0,0)];
    int B=matrix[make_pair(0,1)];
    int C=matrix[make_pair(1,0)];
    int D=matrix[make_pair(1,1)];
    long long result=0;
    //typeI
    if(A==0 && B==0 && C==0 && D==0){
        matrix[make_pair(0,0)]=1;
        matrix[make_pair(0,1)]=2;
        matrix[make_pair(1,0)]=3;
        matrix[make_pair(1,1)]=4;
        result=typeI(matrix,m,n);
       // cout<<"1typeI"<<endl;
        cout<<result<<endl;     
   }
  
    if((A!=0 || D!=0) && C==0 && B==0){
        //cout<<"2typeI"<<endl;
        result=typeI(matrix,m,n);
        cout<<result<<endl;    
    }

    if((C!=0 || B!=0)&& A==0 && D==0){
        matrix[make_pair(0,0)]=1;
        if(C-A==1 || B-A==2){
        //type II
          //  cout<<"1typeII"<<endl;
            result=typeII(matrix,m,n);
            cout<<result<<endl; 
        }
        if(C-A==2 || B-A==1){
            //cout<<"3typeI"<<endl;
            result=typeI(matrix,m,n);
            cout<<result<<endl; 
        }
    }

    if(B-A==1||C-A==2||D-B==2||D-C==1){
        result=typeI(matrix,m,n);
        //cout<<"4typeI"<<endl;
        cout<<result<<endl; 
    }

    if(B-A==2||C-A==1||D-B==1||D-C==2){
        //typeII
        result=typeII(matrix,m,n);
        //cout<<"2typeII"<<endl;
        cout<<result<<endl; 
    }


  
    return 0;
}
