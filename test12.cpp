#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;


class MyParity {
public:
    int parity[2][2] = {{ -1, -1 }, { -1, -1 }};
    int getParity( int i, int j );
    void setParity( int i, int j, int p );
};

int MyParity::getParity( int i, int j )
{
    return parity[i & 1][j & 1];
}

void MyParity::setParity( int i, int j, int p )
{
    parity[i & 1][ j &1 ] = p;
    parity[ 1 - ( i & 1) ][ 1 - ( j & 1 )] = 1 - p;
}


void storeInMap(string str,int row,map<pair<int,int>,int>& matrix){
   string word="";
   int count=0;
   int size=str.length();
   for(int i=0;i<size;i++){
       if(str[i] == ' '){ 
           pair<int,int> pos=make_pair(row,count);
           matrix[pos]=stoi(word);
           //
           count++;
           word="";
       }else{ 
           word=word+str[i];
        }
   }
    pair<int,int> pos=make_pair(row,count);
    matrix[pos]=stoi(word);

}


int main(int argc, const char * argv[]){
    MyParity myParity;
    string line="";
    long long sum;
    int temp;
    bool invalid=false;
    map<pair<int,int>,int> matrix;

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

    if(n==1||m==1){
        invalid=false;
        sum=0;
        temp=0;
         for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                temp=matrix[make_pair(i,j)];
                if (temp == 0) {
                    temp= 1;
                    if (i > 0) {temp = matrix[make_pair(i-1,j)]+1;}
                    if (j > 0) {temp = max(temp, matrix[make_pair(i,j-1)]+1);}
                    matrix[make_pair(i,j)]=temp;
                }else{
                    if((i>0 && temp <= matrix[make_pair(i-1,j)])||(j>0 && temp <= matrix[make_pair(i,j-1)]) ){
                        invalid = true;
                    }
                }
                sum += temp;
                matrix[make_pair(i,j)]=temp;
            }
        }
    }


    // minnum = sum;
    //     if (Invalid == true) {
    //         cout << -1;
    //         return 0;
    //     }
  if(!invalid){
        // if the parity of (0,0) is not set, set it with 1.
        if( myParity.getParity(0,0) < 0) {myParity.setParity(0,0,1);}
        if( myParity.getParity(0,1) < 0){
            myParity.setParity(0,1,0);
            sum = 0;
            temp=0;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    temp=matrix[make_pair(i,j)];
                    if (temp == 0) {
                        temp = 1;
                        if (i > 0) {temp = matrix[make_pair(i-1,j)]+1; }
                        if (j > 0) {temp = max(temp, matrix[make_pair(i,j-1)] + 1);}
                        if ((temp & 1)!=myParity.getParity(i,j)) {
                            temp++;
                        }
                        matrix[i][j] = num;
                    }else{
                        if (i>0 && num <= newmatrix0[i-1][j]) {
                            Invalid = true;
                        }else if( j>0 && num <= newmatrix0[i][j-1] ){
                            Invalid = true;
                        }
                    }
                    sum += num;
                    newmatrix0[i][j] = num;
                }
            }
            long long sum0= sum;
            if (Invalid == true) {
                sum0 = -1;
            }
            
            // try the case that parity of position(0,1) is 1 and get the sum.
            myParity.setParity(0,1,1);
            int newmatrix1[n][m];
            Invalid =false;
            sum =0;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    int num = matrix[i][j];
                    if (num == 0) {
                        num = 1;
                        if (i > 0) {
                            num = newmatrix1[i-1][j]+1;
                        }
                        if (j > 0) {
                            num = max(num, newmatrix1[i][j-1] + 1);
                        }
                        if ((num&1)!=myParity.getParity(i,j)) {
                            num++;
                        }
                        newmatrix1[i][j] = num;
                    }else{
                        if (i>0 && num <= newmatrix1[i-1][j]) {
                            Invalid = true;
                        }else if( j>0 && num <= newmatrix1[i][j-1] ){
                            Invalid = true;
                        }
                    }
                    sum += num;
                    newmatrix1[i][j] = num;
                }
            }
            long long sum1 = sum;
            if (Invalid == true) {
                sum1 = -1;
            }
            if( sum0 < 0 ) {
                minnum = sum1;
            }else if(sum1 < 0){
                minnum = sum0;
            }else {
                minnum = min(sum0, sum1);
            }
        }else{ // the case that the all of parity are already set
            int newmatrix2[n][m];
            sum =0;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    int num = matrix[i][j];
                    if (num == 0) {
                        num = 1;
                        if (i > 0) {
                            num = newmatrix2[i-1][j] + 1;
                        }
                        if (j > 0) {
                            num = max(num, newmatrix2[i][j-1] + 1);
                        }
                        if ((num&1)!=myParity.getParity(i,j)) {
                            num++;
                        }
                        newmatrix2[i][j] = num;
                    }else{
                        if (i>0 && num <= newmatrix2[i-1][j]) {
                            Invalid = true;
                        }else if( j>0 && num <= newmatrix2[i][j-1] ){
                            Invalid = true;
                        }
                    }
                    sum += num;
                    newmatrix2[i][j] = num;
                }
            }
            minnum= sum;
        }
    }


    if(invalid!=true){
        cout<<sum<<endl;
    }else{
        cout<<"-1"<<endl;
    }

}