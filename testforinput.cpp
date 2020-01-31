#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;


int main(){
  while (!cin.eof())
{
    string line;
    getline(cin, line);

    if (cin.fail())
    {
        break;
    }

    cout << line << endl;
}
    //while()

    // ifstream in;
    // in.open("testcase1.txt");
    // string line="";
    // string sum;
    // //vector<int> v;
    // map<pair<int,int>,int> matrix;
    // vector<pair<int,int> > zeros;

    // if(in.fail()){
    //     cerr<<"Open fail"<<endl;
    // }

    // getline(in,line);
    // int len=line.length();
    // int pos=line.find(' ');
    // int m=stoi(line.substr(0,pos));//row
    // int n=stoi(line.substr(pos+1,len-pos-1));//col
    // cout<<m<<" "<<n<<endl;
    
    // int row=0;
    

//     while(!in.eof()){
//        getline(in,line);
//        storeInMap(line,row,matrix);
//        cout<<"row:"<<row<<" line:"<<line<<endl;
//        row++;      
//    }
//     in.close();
}