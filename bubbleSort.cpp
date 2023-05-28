#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void bubble_sort_odd_even(vector<int>& arr) {
	bool isSorted = false;
	while(! isSorted){
		isSorted = true;
		#pragma omp parallel for 
		for (int i = 0; i < arr.size() - 1; i+=2 ){
			if (arr[i] > arr[i+1]){
			swap(arr[i], arr[i+1]);
				isSorted = false;
			}
		}
		#pragma omp parallel for 
		for(int i = 1; i < arr.size() -1 ; i+=2){
			if (arr[i] > arr[i+1]){
				swap(arr[i] , arr[i+1]);
				isSorted = false;
			}
		}
	}
}

int main() {
	vector<int> arr = {5, 2, 9, 1, 6, 7, 8,3 ,4}; 
	
	//Measure performance of parallel bubble sort using odd event
	 
	bubble_sort_odd_even(arr);
	 
	cout<< "Sorted Array" <<endl;
	for(int i =0; i< arr.size(); i++){
		cout<< arr[i]<< ", ";
	}
	
	//return 0
}
