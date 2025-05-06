/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>
using namespace std;

void bubble(vector<int> &arr){
    int n = arr.size();
    for(int i = 0;i<n - 1;i++){
        for(int j = 0;j<n - i - 1;j++){
            if(arr[j] > arr[j+1]) swap(arr[j],arr[j+1]);
        }
    }
}

void bubblepara(vector<int> &arr){
    int n = arr.size();
    #pragma omp parallel for
    for(int i = 0;i<n - 1;i++){
        #pragma omp parallel for
        for(int j = 0;j<n - i - 1;j++){
            #pragma omp critical 
            {
            if(arr[j] > arr[j+1]) swap(arr[j],arr[j+1]);
            }
            
        }
    }
}

void mergehelp(vector<int> &arr,int start,int mid,int end){
    vector<int> temp;
    int lef = start;
    int rig = mid + 1;
    while(lef <= mid && rig <= end){
        if(arr[lef] <= arr[rig]){
            temp.push_back(arr[lef]);
            lef++;
        }
        else{
            temp.push_back(arr[rig]);
            rig++;
        }
        
    }
    while(lef <= mid){
        temp.push_back(arr[lef]);
        lef++;
    }
    while(rig <= end){
        temp.push_back(arr[rig]);
        rig++;
    }
    
    for(int i = start;i<= end;i++){
        arr[i] = temp[i - start];
        
    }
}
void merge(vector<int> &arr,int start,int end){
    if(start >= end) return;

    // while(start < end ){
        int mid = (start+end)/2;
        merge(arr,start,mid);
        merge(arr,mid + 1,end);
        
        mergehelp(arr,start,mid,end);
        
    // }
}

void mergepara(vector<int> &arr,int start,int end){
    if(start >= end) return;

    // while(start < end ){
        int mid = (start+end)/2;
        #pragma omp sections 
        {
        #pragma omp section 
        mergepara(arr,start,mid);
        #pragma omp section 
        mergepara(arr,mid + 1,end);
        }
        mergehelp(arr,start,mid,end);
        
    // }
}
int main()
{
    vector<int> arr = {1,2,3,9,0,5,4};
    mergepara(arr,0,6);
    for(auto it : arr){
        cout<<it<<endl;
    }
    return 0;
}