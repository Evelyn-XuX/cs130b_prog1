#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;


class CheckOddEven {
public:
    int bin[2][2] = {{ -1, -1 }, { -1, -1 }};
    int getBit(int i,int j );
    void setBit(int i,int j,int p );
};

int CheckOddEven::getBit(int i,int j){return bin[i & 1][j & 1];}

void CheckOddEven::setBit(int i,int j,int p )
{
    bin[i & 1][j &1] = p;
    bin[1 -(i&1)][1 - (j&1)]= 1 - p;
}

// void storeInMap(string str,int row,vector< vector<int> > matrix,bool& invalid){
//    string word="";
//    int count=0;
//    int num=0;
//    int size=str.length();
//    CheckOddEven c;
//    for(int i=0;i<size;i++){
//        if(str[i] == ' '){ 
//            //pair<int,int> pos=make_pair(row,count);
//            //matrix[pos]=stoi(word);
//            num=stoi(word);
//            matrix[row][count]=num;
//             if(num >0){
//                 int p = c.getBit(i,j);
//                 if(p == - 1) {
//                     c.setBit(i,j,num& 1);
//                 }else if( p!=(num&1) ) {
//                     invalid = true;
//                 }       
//             }
//            count++;
//            word="";
//        }else{ 
//            word=word+str[i];
//         }
//    }
//    // pair<int,int> pos=make_pair(row,count);
//     matrix[row][count]=stoi(word);

// }

// long long getSum(int n, int m,vector<vector<int> > matrix,bool& invalid){
//     CheckOddEven c;
//     //int temp[n][m];
//     vector<vector<int> > temp;
//     int sum=0;
//     int num=0;
//      for (int i = 0; i < n; i++){
//         for (int j = 0; j < m; j++){
//             num = matrix[i][j];
//         if (num == 0) {
//             num = 1;
//             if (i > 0) {num = temp[i-1][j] + 1;}
//             if (j > 0) {num = max(num,temp[i][j-1] + 1); }
//             if ((num&1)!=c.getBit(i,j)) {num++;}
//                     temp[i][j] = num;
//             }else{
//              if (i>0 && num <= temp[i-1][j]) {
//                 invalid = true;
//             }else if( j>0 && num <= temp[i][j-1] ){
//                             invalid = true;
//                         }
//                     }
//                     sum += num;
//                     temp[i][j] = num;
//                 }
//     }
//     return sum;
// }

int main(int argc, const char * argv[]) {
    CheckOddEven c;
    long long Min = 0;
    long long sum = 0;
    int num=0;
    bool invalid = false;
    string line="";
  //  vector<vector<int> > matrix;

//     getline(cin,line);
//     int len=line.length();
//     int pos=line.find(' ');
//     int m=stoi(line.substr(0,pos));//row
//     int n=stoi(line.substr(pos+1,len-pos-1));//col
//     int row=0;
//     int count=m;
    
//     while(!cin.eof() && count>0){
//        getline(cin,line);
//        storeInMap(line,row,matrix,invalid,c);
//        row++; 
//        count--;     
//    }
   
  
    int m=0,n=0;
    cin >> n >> m;
    
   int matrix[n][m];
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> matrix[i][j];
            num= matrix[i][j];
            if(num >0){
                int p = c.getBit(i,j);
                if(p == - 1) {
                    c.setBit(i,j,num& 1);
                }else if( p!=(num&1) ) {
                    invalid = true;
                }       
            }
        }
    }
    
    if( n==1 || m==1 ){
        invalid = false;
        int m1[n][m];
        sum =0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                num = matrix[i][j];
                if (num == 0) {
                    num = 1;
                    if (i > 0) {num = m1[i-1][j]+1;}
                    if (j > 0) {num = max(num, m1[i][j-1] + 1);}
                    m1[i][j] = num;
                }else{
                    if (i>0 && num <= m1[i-1][j]){
                        invalid = true;
                    }else if( j>0 && num <= m1[i][j-1] ){
                       invalid = true;
                    }
                }
                sum += num;
                m1[i][j] = num;
            }
        }
        Min= sum;
        if (invalid == true) {
            cout <<"-1"<<endl;
            return 0;
        }
    }else if(!invalid){
        if(c.getBit(0,0) < 0) {c.setBit(0,0,1);}
        if(c.getBit(0,1) < 0){    
            c.setBit(0,1,0);
           // sum=getSum(n,m,matrix,invalid,c);
            int m2[n][m];
            sum = 0;
            num=0;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    num = matrix[i][j];
                    if (num == 0) {
                        num = 1;
                        if (i > 0) {num = m2[i-1][j]+1;}
                        if (j > 0) {num = max(num, m2[i][j-1] + 1); }
                        if ((num&1)!=c.getBit(i,j)) {num++;}
                        m2[i][j] = num;
                    }else{
                        if (i>0 && num <= m2[i-1][j]) {
                            invalid = true;
                        }else if( j>0 && num <= m2[i][j-1] ){
                            invalid = true;
                        }
                    }
                    sum += num;
                    m2[i][j] = num;
                }
            }


            long long sum0=sum;
            if (invalid == true) {sum0 = -1;}
            
           c.setBit(0,1,1);
           int m3[n][m];
            invalid =false;
            sum =0;
            num=0;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    int num = matrix[i][j];
                    if (num == 0) {
                        num = 1;
                        if (i > 0) {num = m3[i-1][j]+1;}
                        if (j > 0) {num = max(num, m3[i][j-1] + 1); }
                        if ((num&1)!=c.getBit(i,j)) {num++;}
                        m3[i][j] = num;
                    }else{
                        if (i>0 && num <= m3[i-1][j]) {invalid = true;}
                        if( j>0 && num <= m3[i][j-1] ){invalid = true;}
                    }
                    sum += num;
                    m3[i][j] = num;
                }
            }
            long long s1 = sum;
            if (invalid == true) {s1 = -1;}
            if( sum0 < 0 ) {
                Min = s1;
            }else if(s1 < 0){
                Min = sum0;
            }else {
                Min = min(sum0, s1);
            }            
        }else{ 
            int m4[n][m];
            sum =0;
            num=0;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    int num = matrix[i][j];
                    if (num == 0) {
                        num = 1;
                        if (i > 0) {num = m4[i-1][j] + 1; }
                        if (j > 0) { num = max(num, m4[i][j-1] + 1);}
                        if ((num&1)!=c.getBit(i,j)) {num++;}
                        m4[i][j] = num;
                    }else{
                        if (i>0 && num <= m4[i-1][j]) {invalid = true;}
                        if( j>0 && num <= m4[i][j-1] ){invalid = true;}
                    }
                    sum += num;
                    m4[i][j] = num;
                }
            }
            Min= sum;
        }

    }
    
    if (invalid == true) {
        cout <<"-1"<<endl;
        return 0;
    }
    cout <<Min<<endl;
    return 0;
}
