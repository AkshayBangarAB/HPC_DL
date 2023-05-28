#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void merge(vector<int> & arr, int left, int middle, int right){
	int i, j , k;
	int n1 = middle - left + 1;
	int n2 = right - middle;
	vector<int> L(n1), R(n2);
	for(i = 0; i < n1; i++){
		L[i] = arr[left+i];
	}
	for(j = 0; j < n2; j++){
		R[j] = arr[middle + 1 + j];
	}
	
	i = 0;
	j = 0;
	k = left;
	while ( i< n1 && j < n2) {
		if (L[i] <= R[j]){
			arr[k++] = L[i++];
		}else {
			arr[k++] = R[j++];
		}
	}
	while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void merge_sort(vector<int>& arr, int left, int right){
	if ( left < right) {
		int middle = left + (right-left) / 2;
		#pragma omp task
		merge_sort(arr, left, middle); 
		#pragma omp task 
		merge_sort(arr, middle + 1, right);
		
		merge(arr, left, middle, right);
	}
}

void parallel_merge_sort(vector<int> & arr){
	#pragma omp parallel_merge_sort
	{
		#pragma omp single
		merge_sort(arr, 0, arr.size()-1);
	}
}

void display_arr(vector<int>& arr){
	cout<< "Display Array After sort"<<endl;
	for (int i =0; i< arr.size() -1; i++){
		cout<< arr[i]<< ", ";
	}
	cout<<endl;
}

int main(){
	cout<< "hi" << endl;
	vector<int> arr = {5, 2, 9, 1, 7, 6, 8, 4, 3};
	merge_sort(arr, 0, arr.size() - 1);
	cout<<"\nHI";
	display_arr(arr);
	vector<int> arr2 = {5, 2, 9, 1, 7, 6, 8, 4, 3};
	parallel_merge_sort(arr2);
	display_arr(arr2);
}