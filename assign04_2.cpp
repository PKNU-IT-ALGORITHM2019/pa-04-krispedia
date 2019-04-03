#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<map>

using namespace std;

vector<string> csvData;
vector<string> ip;
vector<string> dataTime;
vector<string> url;
vector<string> status;
map<string, string> timeKeyMap;
map<string, string> ipKeyMap;

vector<int> delimLoc;

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
    delimLoc.clear();
    int count=0;
    if(csvDataLow.find(",") == -1){
        cout<<"no ',' in string"<<'\n';
        return;
    }
    delimLoc.push_back(csvDataLow.find(","));
    count++;
    while(csvDataLow.find(",",delimLoc.at(count-1)+1)!=-1){
        delimLoc.push_back(csvDataLow.find(",",delimLoc.at(count-1)+1));
        count++;
    }
}
void splitData(vector<string> input){
    for(auto it=input.begin(); it!=input.end(); ++it){
        getDelimLoc(*it);
        ip.push_back(it->substr(0, delimLoc.at(0)));
        dataTime.push_back(it->substr(delimLoc.at(0)+2, delimLoc.at(1)-delimLoc.at(0)-2));
        url.push_back(it->substr(delimLoc.at(1)+1, delimLoc.at(2)-delimLoc.at(1)-1));
        status.push_back(it->substr(delimLoc.at(2)+1));
    }
    cout<<"split data done!"<<'\n';
}
void print(){
    for(int i=0; i<csvData.size(); i++){
        cout<<dataTime.at(i)<<'\n';
        cout<<"\tIP: "<<ip.at(i)<<'\n';
        cout<<"\tURL: "<<url.at(i)<<'\n';
        cout<<"\tStatus: "<<status.at(i)<<'\n';
    }
}
void mapPrint(map<string, string> input){
    for(auto p : input)
        cout<<p.first<<' '<<p.second<<'\n';
}
void makeTimeKeyMap(vector<string> timeIn, vector<string> ipIn, vector<string> urlIn, vector<string> statusIn){
    
    for(int i=0; i<timeIn.size(); i++){
        string combineString ="";
        combineString.append(ipIn.at(i));
        combineString.append(",");
        combineString.append(urlIn.at(i));
        combineString.append(",");
        combineString.append(statusIn.at(i));
        cout<<combineString<<'\n';
        timeKeyMap[timeIn.at(i)] = combineString;
    }
    mapPrint(timeKeyMap);
}

void soryByTime(){
    makeTimeKeyMap(dataTime, ip, url, status);
    sort(dataTime.begin(), dataTime.end());

}
void sortByIp(){

}
void commandLine(){
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
            splitData(csvData);
            //printData(ip);
            //printData(dataTime);
            //printData(url);
            //printData(status);
        }
        else if(command == "sort"){
            cout<<"sort"<<'\n';
            cin>>argument;
            if(argument == "-t"){
                cout<<"sortByTime"<<'\n';
                makeTimeKeyMap(dataTime, ip, url, status);
                //sortByTime();
            }
            else if(argument == "-ip"){
                cout<<"soryByIp"<<'\n';
                //sortByIp();
            }
            else
                break;
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

    commandLine();

    return 0;
}
