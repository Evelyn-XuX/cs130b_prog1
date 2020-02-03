#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

// void storeInMap(string str,int row,int matrix[][n]){
//    string word="";
//    int count=0;
//    int size=str.length();
//    for(int i=0;i<size;i++){
//        if(str[i] == ' '){ 
//            matrix[row][count]=stoi(word);
//            count++;
//            word="";
//        }else{ 
//            word=word+str[i];
//         }
//    }
//     matrix[row][count]=stoi(word);

// }

class BitCheck{
public:
    int bin[2][2] = {{-1, -1 }, {-1, -1 }};
    int getRelation( int i, int j );
    void setRelation( int i, int j, int p );
};

int BitCheck::getRelation(int i, int j ){return bin[i & 1][j & 1];}
    
void BitCheck::setRelation( int i, int j, int p ){
    bin[i & 1][ j &1 ] = p;
    bin[ 1 - ( i & 1) ][ 1 - ( j & 1 )] = 1 - p;
}




int main() {
    
    string line="";
    BitCheck check;
    bool invalid = false;
    long long sum = 0;
    long long mini=0;
    int num=0;

    getline(cin,line);
    int len=line.length();
    int pos=line.find(' ');
    int m=stoi(line.substr(0,pos));//row
    int n=stoi(line.substr(pos+1,len-pos-1));//col
    int matrix[m][n];
    int row=0;
    int count=m;
    
    while(!cin.eof() && count>0){
       getline(cin,line);
       //storeInMap(line,row,matrix);
       string word="";
       int c=0;
       int size=line.length();
       for(int i=0;i<size;i++){
       if(line[i] == ' '){ 
           matrix[row][count]=stoi(word);
           count++;
           word="";
       }else{ 
           word=word+line[i];
        }
   }
    matrix[row][count]=stoi(word);
       row++; 
       count--;     
   }
    
    //1xn or mx1
    if( n==1 || m==1 ){
        invalid = false;
        int matrix1[m][n];
        sum =0;
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                num = matrix[i][j];
                if (num == 0) {
                    num = 1;
                    if (i > 0) {num = matrix1[i-1][j]+1;}
                    if (j > 0) {num = max(num, matrix1[i][j-1] + 1);
                }
                    matrix1[i][j] = num;
                }else{
                    if ((i>0 && num <= matrix1[i-1][j])&&( j>0 && num <= matrix1[i][j-1] )) {
                        invalid = true;
                    }
                }
                sum += num;
                matrix1[i][j] = num;
            }
        }
        
        mini = sum;
        if (invalid == true) {
            cout<<"-1"<<endl;
            return 0;
        }
    }
    
    


    if(!invalid){
        if(check.getRelation(0,0) < 0) {check.setRelation(0,0,1); }
        if( check.getRelation(0,1) < 0){
            check.setRelation(0,1,0);
            int matrix2[m][n];
            sum = 0;
            num=0;
            for (int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    num = matrix[m][n];
                    if (num == 0) {
                        num = 1;
                        if (i > 0) {num = matrix2[i-1][j]+1;}
                        if (j > 0) {num = max(num, matrix2[i][j-1] + 1);}
                        if ((num&1)!=check.getRelation(i,j)) {
                            num++;
                        }
                        matrix2[i][j] = num;
                    }else{
                        if((i>0 && num <= matrix2[i-1][j])&&(j>0 && num <= matrix2[i][j-1])) {
                            invalid = true;
                        }
                    }
                    sum += num;
                    matrix2[i][j] = num;
                }
            }
            long long s= sum;
            if (invalid == true) {
                s = -1;
            }
            
          
            check.setRelation(0,1,1);
            int matrix3[m][n];
            invalid =false;
            sum =0;
            num=0;
            for (int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    num = matrix[m][n];
                    if (num == 0) {
                        num = 1;
                        if (i > 0) {num = matrix2[i-1][j]+1;}
                        if (j > 0) {num = max(num, matrix3[i][j-1] + 1);}
                        if ((num&1)!=check.getRelation(i,j)) {
                            num++;
                        }
                        matrix3[i][j] = num;
                    }else{
                        if((i>0 && num <= matrix3[i-1][j])&&(j>0 && num <= matrix3[i][j-1])) {
                            invalid = true;
                        }
                    }
                    sum += num;
                    matrix3[i][j] = num;
                }
            }
            long long sum1 = sum;
            if (invalid == true) {
                sum1 = -1;
            }
            if( s < 0 ) {
                mini = sum1;
            }else if(sum1 < 0){
                mini= s;
            }else {
                mini = min(s, sum1);
            }            
        }else{ 
            int matrix4[m][n];
            sum =0;
            num=0;
            for (int i = 0; i < m; i++){
                for (int j = 0; j < n; j++){
                    num = matrix[i][j];
                    if (num == 0) {
                        num = 1;
                        if (i > 0) {num = matrix4[i-1][j] + 1; }
                        if (j > 0) {num = max(num, matrix4[i][j-1] + 1);}
                        if ((num&1)!=check.getRelation(i,j)) {num++;}
                        matrix4[i][j] = num;
                    }else{
                        if (i>0 && num <= matrix4[i-1][j]) {
                            invalid = true;
                        }else if( j>0 && num <= matrix4[i][j-1] ){
                            invalid = true;
                        }
                    }
                    sum += num;
                    matrix4[i][j] = num;
                }
            }
            mini= sum;
        }

    }
    
   
    if (invalid == true) {
        cout << -1;
        return 0;
    }
    cout << mini;
    return 0;
}
