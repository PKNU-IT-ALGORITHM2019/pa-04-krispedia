#include<iostream>    // 입출력
#include<fstream>     // 파일 읽기
#include<vector>      // 데이터 저장 
#include<string>      // 문자열 다루기 위해 
#include<map>         // sort할때 사용

using namespace std;

vector<string> temp;     // sort 후 split 될 map value 잠시 보관
vector<string> csvData;  // 파일에서 읽어 온 데이터 라인 단위로 저장(csv "," 열 구분자) 
vector<string> ip;       // ip
vector<string> dataTime; // time
vector<string> url;      // url
vector<string> status;   // status
vector<pair<string, string> > ipAndTime;    // 동일 ip 경우 time 으로 정렬하기 위해 pair
map<string, string> timeKeyMap;             // time 기준 sort 할때 사용
map<pair<string, string>, string> ipKeyMap; // ip 기준 sort 할때 사용

vector<int> delimLoc;    // csv "," 열 구분자 위치
// 라인 단위로 파일 읽기
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
}
// time 기준 전체 데이터 출력
void print(){
    for(int i=0; i<csvData.size(); i++){
        cout<<dataTime.at(i)<<'\n';
        cout<<"\tIP: "<<ip.at(i)<<'\n';
        cout<<"\tURL: "<<url.at(i)<<'\n';
        cout<<"\tStatus: "<<status.at(i)<<'\n';
    }
}
// ip 기준 전체 데이터 출력
void printByIp(){
    for(int i=0; i<ip.size(); i++){
        cout<<ip.at(i)<<'\n';
        cout<<"\tTime: "<<dataTime.at(i)<<'\n';
        cout<<"\tURL: "<<url.at(i)<<'\n';
        cout<<"\tStatus: "<<status.at(i)<<'\n';
    }
}
// vector 데이터 출력
void printData(vector<string> input) {
    for(auto it = input.begin(); it!=input.end(); ++it)
        cout<<*it<<'\n';
}
/*
// debug
void mapPrint(map<string, string> input){
    for(auto p : input)
        cout<<p.first<<' '<<p.second<<'\n';
}
*/
// "," 위치 파악
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
// csvData -> ip/time/url/status 나누기
void splitData(vector<string> input){
    ip.clear();
    dataTime.clear();
    url.clear();
    status.clear();
    for(auto it=input.begin(); it!=input.end(); ++it){
        getDelimLoc(*it);
        ip.push_back(it->substr(0, delimLoc.at(0)));
        dataTime.push_back(it->substr(delimLoc.at(0)+2, delimLoc.at(1)-delimLoc.at(0)-2));
        url.push_back(it->substr(delimLoc.at(1)+1, delimLoc.at(2)-delimLoc.at(1)-1));
        status.push_back(it->substr(delimLoc.at(2)+1));
    }
}
// time sort 후 temp -> ip/url/status 나누기 
void splitTempTimeKeyData(vector<string> input){
    ip.clear();
    url.clear();
    status.clear();
    for(auto it=input.begin(); it!=input.end(); ++it){
        getDelimLoc(*it);
        ip.push_back(it->substr(0, delimLoc.at(0)));
        url.push_back(it->substr(delimLoc.at(0)+1, delimLoc.at(1)-delimLoc.at(0)-1));
        status.push_back(it->substr(delimLoc.at(1)+1));
    }
}
// ip sort 후 temp -> url/status 나누기
void splitTempIpKeyData(vector<string> input){
    url.clear();
    status.clear();
    for(auto it=input.begin(); it!=input.end(); ++it){
        getDelimLoc(*it);
        url.push_back(it->substr(0, delimLoc.at(0)));
        status.push_back(it->substr(delimLoc.at(0)+1));
    }
}
// time + ip/url/status map 생성 
void makeTimeKeyMap(vector<string> timeIn, vector<string> ipIn, vector<string> urlIn, vector<string> statusIn){
    timeKeyMap.clear();
    for(int i=0; i<timeIn.size(); i++){
        string combineString ="";
        combineString.append(ipIn.at(i));
        combineString.append(",");
        combineString.append(urlIn.at(i));
        combineString.append(",");
        combineString.append(statusIn.at(i));
        timeKeyMap[timeIn.at(i)] = combineString;
    }
    //mapPrint(timeKeyMap);
}
// ip/time + url/status map 생성
void makeIpKeyMap(vector<string> ipIn, vector<string> timeIn, vector<string> urlIn, vector<string> statusIn){
    ipAndTime.clear();
    ipKeyMap.clear();
    for(int i=0; i<ipIn.size(); i++){
        string combineString = "";
        combineString.append(urlIn.at(i));
        combineString.append(",");
        combineString.append(statusIn.at(i));
        pair<string, string> key = make_pair(ipIn.at(i), timeIn.at(i));
        ipAndTime.push_back(key);
        ipKeyMap[key] = combineString;
    }
    //mapPirnt(ipKeyMap);
}
// time sort
void sortByTime(){
    temp.clear();
    makeTimeKeyMap(dataTime, ip, url, status);
    sort(dataTime.begin(), dataTime.end());
    for(auto it = dataTime.begin(); it!=dataTime.end(); ++it)
        temp.push_back(timeKeyMap[*it]);
    splitTempTimeKeyData(temp);
}
// ip+time sort
void sortByIp(){
    temp.clear();
    makeIpKeyMap(ip, dataTime, url, status);
    sort(ipAndTime.begin(), ipAndTime.end());
    dataTime.clear();
    ip.clear();
    for(auto it = ipAndTime.begin(); it!=ipAndTime.end(); ++it){
        temp.push_back(ipKeyMap[*it]);
        ip.push_back(it->first);
        dataTime.push_back(it->second);
    }   
    splitTempIpKeyData(temp);
}
void commandLine(){
    string input, command, argument;

    ios_base::sync_with_stdio(false);
    while(1){
        cin.clear();
        cin>>command;

        if(command == "read"){
            cin>>argument;
            readFile(argument);
            splitData(csvData);
        }
        else if(command == "sort"){
            cin>>argument;
            if(argument == "-t"){
                sortByTime();
            }
            else if(argument == "-ip"){
                sortByIp();
                printByIp();
            }
            else{
                cout<<"sort option need argument (-t or -ip)"<<'\n';
            }
        }
        else if(command == "print"){
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
