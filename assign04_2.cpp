#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

vector<string> csvData;
vector<string> ip;
vector<string> dataTime;
vector<string> url;
vector<string> status;

int delimLoc[3];

void readFile(string fileName){
    string line;
    fstream fin;
    fin.open(fileName);
    getline(fin, line);
    while(!fin.eof()){
        getline(fin, line);
        csvData.push_back(line);
    }
    fin.close();
    cout<<"read file done!"<<'\n';
}
void printData(vector<string> input) {
    for(auto it = input.begin(); it!=input.end(); ++it)
        cout<<*it<<'\n';
}
void getDelimLoc(string csvDataLow){
    delimLoc[0] = csvDataLow.find(",");
    //cout<<delimLoc[0]<<'\n';
    delimLoc[1] = csvDataLow.find(",",delimLoc[0]+1);
    //cout<<delimLoc[1]<<'\n';
    delimLoc[2] = csvDataLow.find(",",delimLoc[1]+1);
    //cout<<delimLoc[2]<<'\n';
}
void splitData(){
    for(auto it=csvData.begin(); it!=csvData.end(); ++it){
        getDelimLoc(*it);
        ip.push_back(it->substr(0, delimLoc[0]));
        dataTime.push_back(it->substr(delimLoc[0]+2, delimLoc[1]-delimLoc[0]-2));
        url.push_back(it->substr(delimLoc[1]+1, delimLoc[2]-delimLoc[1]-1));
        status.push_back(it->substr(delimLoc[2]+1));
    }
}
void print(){
    for(int i=0; i<csvData.size(); i++){
        cout<<dataTime.at(i)<<'\n';
        cout<<"\tIP: "<<ip.at(i)<<'\n';
        cout<<"\tURL: "<<url.at(i)<<'\n';
        cout<<"\tStatsu: "<<status.at(i)<<'\n';
    }
}
void commandLine() {
    string input, command, argument;

    ios_base::sync_with_stdio(false);
    while(1){
        cin.clear();
        cin>>command;

        if(command == "read"){
            cout<<"read"<<'\n';
            cin>>argument;
            readFile(argument);
            //printData(csvData);
            splitData();
            //printData(ip);
            //printData(dataTime);
            //printData(url);
            //printData(status);
        }
        else if(command == "sort"){
            cout<<"sort"<<'\n';
     
        }
        else if(command == "print"){
            cout<<"print"<<'\n';
            print();
        }
        else if(command == "exit")
            return;
        else {
            cout<<"Invalid command"<<'\n';
            continue;
        }
    }
}

int main(void) {
    // string fileName = "webLog.csv";
    // readFile(fileName);
    // //printData();
    // cout<<'\n'<<csvData.at(0)<<'\n';
    // int index1 = csvData.at(0).find(",");
    // cout<<index1<<'\n';
    // int index2 = csvData.at(0).find(",",index1+1);
    // cout<<index2<<'\n';
    // int index3 = csvData.at(0).find(",", index2+1);
    // cout<<index3<<'\n';
    
    // string ip = csvData.at(0).substr(0,index1);
    // cout<<ip<<'\n';
    // string time = csvData.at(0).substr(index1+1, index2-index1-1);
    // cout<<time<<'\n';
    // string url = csvData.at(0).substr(index2+1, index3-index2-1);
    // cout<<url<<'\n';
    // string status = csvData.at(0).substr(index3+1);
    // cout<<status<<'\n';

    commandLine();

    return 0;
}
