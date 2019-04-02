#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#define T 3

using namespace std;

int N[3] = {1000, 10000, 100000};
double runningTime[9][6] = {0.0};
vector<double> randomTime(10,0);
vector<double> randomTimeOrigin(10,0);
vector<int> data;
vector<int> dataOrigin;
int heapSize;

void merge(vector<int> data, int p, int q, int r);
int partitionLastPivot(int left, int right);
int partitionMedianPivot(int left, int right);
int partitionRandomPivot(int left, int right);

void printResult() {

    cout<<"            \tRandom1000";

    cout<<"    Reverse1000";

    cout<<"    Random10000";

    cout<<"    Reverse10000";

    cout<<"    Random100000";

    cout<<"    Reverse100000"<<'\n';
    int i;
    for(i=0; i<9; i++){
        cout.flags(ios::right);
        if(i==0)
            cout<<"   Bubble sort";
        else if(i==1)
            cout<<"Selection sort";
        else if(i==2)
            cout<<"Insertion sort";
        else if(i==3)
            cout<<"\t Merge";
        else if(i==4)
            cout<<"\tQuick1";
        else if(i==5)
            cout<<"\tQuick2"; 
        else if(i==6)
            cout<<"\tQuick3";
        else if(i==7)
            cout<<"\tHeap  ";
        else if(i==8)
            cout<<"\tLibrary";
        
        for(int j=0; j<6; j++){
            cout.width(12);
            cout<<runningTime[i][j];
        }
        cout<<'\n';
    }
}
void swap(int index1, int index2){
    int temp = data.at(index1);
    data.at(index1) = data.at(index2);
    data.at(index2) = temp;
}
void bubbleSort(){
    for(int  i = data.size()-1; i>=0; i--){
        for(int j = 1; j<=i; j++){
            if(data.at(j-1)>data.at(j))
                swap(j-1, j);
        }
    }
}
void selectionSort(){
    for(int i=data.size()-1; i>=0; i--){
        int max = data.at(i);
        int maxIndex = i;
        for(int j=0; j<=i; j++){
            if(data.at(j)>max){
                max = data.at(j);
                maxIndex = j;
            }
        }
        if(maxIndex != i)
            swap(i,maxIndex);
    }
}
void insertionSort(){
    for(int i=1; i<data.size(); i++){
        int temp = data.at(i);
        int locIndex = 0;
        bool hitBig = false;
        for(int j=0; j<i; j++){
            if(data.at(j)>data.at(i)){
                locIndex = j;
                hitBig = true;
                break;
            }
        }
        if(hitBig == false){
            locIndex = i;
            continue;
        }

        for(int j=i; j>locIndex; j--){
            data.at(j) = data.at(j-1);
        }
        data.at(locIndex) = temp;
    }
}
void mergeSort(vector<int> arr, int left, int right){
//    cout<<"merge sort start!"<<'\n';
    if(left<right){
        int mid = (left+right)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge(data, left, mid, right);
    }
}
void merge(vector<int> arr, int left, int mid, int right){
//    cout<<"merge start!"<<'\n';
    vector<int> sortedData;
    int i=left;
    int j=mid+1;
    int k=left;

    while(i<=mid && j<=right){
        if(arr.at(i)<=arr.at(j)){
            sortedData.push_back(arr.at(i++));
        }
        else{
            sortedData.push_back(arr.at(j++));
        }
    }
    // front array done
    if(i>mid){
        for(int l=j; l<=right; l++)
            sortedData.push_back(arr.at(l));
    }
    // back array done
    else if(j>right){
        for(int l=i; l<=mid; l++)
            sortedData.push_back(arr.at(l));
    }
    for(int l=left; l<=right; l++){
        data[l] = sortedData.at(l-left);
    }
/*  print data 
    for(auto it=data.begin(); it!=data.end(); ++it)
        cout<<*it<<" ";
        cout<<'\n';
*/
}
void quickSortLast(int left, int right){
    if(left<right){
        int pivot = partitionLastPivot(left, right);
        quickSortLast(left, pivot-1);
        quickSortLast(pivot+1, right);
    }
}
int partitionLastPivot(int left, int right){
//    cout<<"partition start!"<<'\n';
    int i=left-1;
    //int j=left;

    int check = data.at(right);

    for(int j=left; j<right; j++){
        if(data.at(j)<check){
            i++;
            swap(i, j);
        }
    }
    swap(i+1, right);

    return i+1;
}
void quickSortMedian(int left, int right){
    if(left<right){
        int pivot = partitionMedianPivot(left, right);
        quickSortLast(left, pivot-1);
        quickSortLast(pivot+1, right);
    }
    
}
int getMedian(){
    int mediumIndex = data.size()/2;
    int lastIndex = data.size()-1;
//    cout<<"mediumIndex: "<<mediumIndex<<'\n';
    if((data.at(0)>data.at(mediumIndex) && data.at(0)<data.at(lastIndex)) || (data.at(0)<data.at(mediumIndex) && data.at(0)>data.at(lastIndex)))
        return 0;
    else if((data.at(0)<data.at(mediumIndex) && data.at(mediumIndex)<data.at(lastIndex)) || (data.at(0)>data.at(mediumIndex) && data.at(mediumIndex)>data.at(lastIndex)))
        return mediumIndex;
    else
        return lastIndex;
}
int partitionMedianPivot(int left, int right){
//    cout<<"partition start!"<<'\n';
    int i=left-1;
    //int j=left;

    int checkIndex = getMedian();
    swap(checkIndex, right);

    int check = data.at(right);

    for(int j=left; j<right; j++){
        if(data.at(j)<check){
            i++;
            swap(i, j);
        }
    }
    swap(i+1, right);

    return i+1;
}
void quickSortRandom(int left, int right){
    if(left<right){
        int pivot = partitionRandomPivot(left, right);
        quickSortLast(left, pivot-1);
        quickSortLast(pivot+1, right);
    }
    
}
int partitionRandomPivot(int left, int right){
//    cout<<"partition start!"<<'\n';
    int i=left-1;
    //int j=left;

    srand((unsigned) time(NULL));
    int checkIndex = rand()%(right-left+1);
    swap(checkIndex, right);

    int check = data.at(right);

    for(int j=left; j<right; j++){
        if(data.at(j)<check){
            i++;
            swap(i, j);
        }
    }
    swap(i+1, right);

    return i+1;
}
/*
// iterative
void maxHeapify(vector<int> arr, int i){
    int l = 2*i+1;
    int r = 2*i+2;
    int largest;
    if(l<=heapSize && data.at(l)>data.at(i))
        largest = l;
    else
        largest = i;
    if(r<=heapSize && data.at(r)>data.at(largest))
        largest = r;
    if(largest != i){
        swap(i, largest);
        maxHeapify(arr, largest);
    }
}
*/
// recursive
void maxHeapify(vector<int> arr, int i){
    int l = 2*i+1;
    int r = 2*i+2;
    int larger;
    if(l>=heapSize && r>=heapSize)
        return;
    if(r<heapSize && data.at(l)>=data.at(r))
        larger = l;
    else if(l<heapSize && r>=heapSize)
        larger = l;
    else 
        larger = r;

    if(data.at(i)>=data.at(larger))
        return;
    swap(i, larger);
    maxHeapify(arr, larger);
}

void buildMaxHeap(vector<int> arr) {
    heapSize = arr.size()-1;
    for(int i=arr.size()/2; i>=0; i--){
        maxHeapify(arr, i);
    }
}
void heapSort(vector<int> arr){
    buildMaxHeap(arr);
    for(int i=arr.size()-1; i>=1; i--){
        swap(0, heapSize);
        heapSize -= 1;
        maxHeapify(arr, 0);
    }
}

void generateRandomData(int N){
    srand((unsigned int) time(NULL));
    dataOrigin.clear();
    for(int i=0; i<N; i++){
        // random 수 생성
        int number = rand()%N+1;
        dataOrigin.push_back(number);
    }
}
void generateReversedData(int N){
    dataOrigin.clear();
    for(int i=0; i<N; i++){
        dataOrigin.push_back(N-i);
    }
}
void printData(){
    for(auto it=data.begin(); it!=data.end(); ++it)
        cout<<*it<<" ";
    cout<<'\n';    
}
void saveRunningTime(int row, int col, double time){
    runningTime[row][col] = time;
}
void runSort(int i, int j) {

    clock_t start, end; 
    
    data.resize(dataOrigin.size());
                        
    copy(dataOrigin.begin(), dataOrigin.end(), data.begin());
    //printData();
    start = clock();
    cout<<"bubble sort"<<'\n';
    bubbleSort();
    end = clock();
    double resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        //cout<<"resultTIME: "<<resultTime<<'\n';
        resultTime += randomTime.at(0);
        randomTime.at(0) += temp;
    }
    saveRunningTime(0,(i+1)*(j+1)-1, resultTime);
    //runningTime[0][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    //printData();

    copy(dataOrigin.begin(), dataOrigin.end(), data.begin());
    //printData();
    start = clock();
    cout<<"selection sort"<<'\n';
    selectionSort();
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(1);
        randomTime.at(1) += temp;
    }
    saveRunningTime(1,(i+1)*(j+1)-1,resultTime);
    //runningTime[1][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    //printData();

    copy(dataOrigin.begin(), dataOrigin.end(), data.begin());
    //printData();           
    start = clock();
    cout<<"insertion sort"<<'\n';
    insertionSort();
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(2);
        randomTime.at(2) += temp;
    }
    saveRunningTime(2,(i+1)*(j+1)-1,resultTime);
    //runningTime[2][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    //printData();

    copy(dataOrigin.begin(), dataOrigin.end(), data.begin());
    //printData();          
    start = clock();
    cout<<"merge sort"<<'\n';
    mergeSort(data, 0, N[i]-1);
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(3);
        randomTime.at(3) += temp;
    }
    saveRunningTime(3,(i+1)*(j+1)-1,resultTime);
    //runningTime[3][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    //printData();
    // pivot 
    copy(dataOrigin.begin(), dataOrigin.end(), data.begin());
    //printData();          
    start = clock();
    cout<<"quick_sort_last"<<'\n';
    quickSortLast(0, N[i]-1);
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(4);
        randomTime.at(4) += temp;
    }
    saveRunningTime(4,(i+1)*(j+1)-1,resultTime);
    //runningTime[4][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    //printData();
            
    copy(dataOrigin.begin(), dataOrigin.end(), data.begin());
    //printData();
    start = clock();
    cout<<"quick_sort_median"<<'\n';
    quickSortMedian(0, N[i]-1);
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(5);
        randomTime.at(5) += temp;
    }
    saveRunningTime(5,(i+1)*(j+1)-1,resultTime);
    //runningTime[5][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    //printData();
            
    copy(dataOrigin.begin(), dataOrigin.end(), data.begin());
    //printData();
    start = clock();
    cout<<"quick_sort_random"<<'\n';
    quickSortRandom(0, N[i]-1);
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(6);
        randomTime.at(6) += temp;
    }
    saveRunningTime(6,(i+1)*(j+1)-1,resultTime);
    //runningTime[6][(i+1)*(j+1)-1] = (double)(end-start)/CLOCKS_PER_SEC;
    //printData();

    copy(dataOrigin.begin(), dataOrigin.end(), data.begin());
    //printData();
    start = clock();
    cout<<"heap_sort"<<'\n';
    heapSort(data);
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(6);
        randomTime.at(6) += temp;
    }
    saveRunningTime(7,(i+1)*(j+1)-1,resultTime);

    copy(dataOrigin.begin(), dataOrigin.end(), data.begin());
    //printData();
    start = clock();
    cout<<"c++_sort"<<'\n';
    sort(data.begin(), data.end());
    end = clock();
    resultTime = (double)(end-start)/CLOCKS_PER_SEC;
    if(j == 0){
        double temp = resultTime;
        resultTime += randomTime.at(6);
        randomTime.at(6) += temp;
    }
    saveRunningTime(8,(i+1)*(j+1)-1,resultTime);

}
void runningTest(){
    for(int i=0; i<2; i++) {
       for(int j=0; j<2; j++){
           clock_t start, end; 
           if(j==0){
                copy(randomTimeOrigin.begin(), randomTimeOrigin.end(), randomTime.begin());
     ;                
                for(int k=0; k<10; k++){
                    generateRandomData(N[i]);
                    //double result = (double)(end-start)/CLOCKS_PER_SEC;
                    runSort(i, j);

                }
                for(int k=0; k<7; k++){
                    runningTime[k][(i+1)*(j+1)-1] /= 10.0;
                }
            }
            else{
                generateReversedData(N[i]);
                //double result = (double)(end-start)/CLOCKS_PER_SEC;
                runSort(i, j);
            }
       }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);

    runningTest();
    printResult();

    return 0;
}
