#include "lab2.h"
#include <math.h>

void print_tree(float arr[], int n) {
    char space = '\t';
    char tab = ' ';
    // calculate the number of layers
    double num;
    int layer;
    num = log2(n+1);
    layer = ceil(num);
    //number of layers (3)
    int max = pow(2, layer-1); //max number to element on the last row (4)
    int numSpace = max * 4; // horizontal width of the display (16 spaces)
    int side = numSpace/2;  //end of the line is half of the middle space (8)
    int middle = 0;
    int track = 1;
    float lastEle = arr[n-1]; //is it not going to change right?
    printf("%d \n", side);
    //print the first layer
    for (int t = 0; t < side; t++){
        printf("%c", tab); //print tabs
    }
    printf("%g", arr[0]);
    printf("\n");

    for (int i = 1; i < layer; i++) {

        int element = pow(2, i); //number of element on that row
        middle = numSpace/element; //updating
        side = middle/2; //updating
        for (int s = 0; s < side; s++){
            printf("%c", tab); //print two spaces
        }

        for (int l = track; l < (track + element); l++){ //track = 1, element = 2, loop l = 1,2

            if (arr[l] == arr[track + element - 1]){ //if it is the last element of the layer
                printf("%g", arr[l]);
                break;
            }
            else if (arr[l] == lastEle && (l != (track + element - 1))) { //if it is the last element of the heap but not last element of the layer track(1) + 2 -1
                printf("%g", lastEle);
                int extra = element - l;
                for (int e = 0; e < (middle * extra); e++){
                    printf("%c", tab);
                }
                break;
            }
            else{
                printf("%g", arr[l]);
                for (int d = 0; d < middle; d++) { //print 4 spaces
                    printf("%c", tab);
                }
            }
        }
        printf("\n");
        track += element; // index of the first element on the next row
    }
}


float get_parent_value(float arr[], int n, int index) {
    if (index < n && index != 0){
        int parent;
        parent = (index-1)/2;
        return arr[parent];
    }
    else{
        return -1;
    }
}

float get_left_value(float arr[], int n, int index) {
    if (index < n){
        int left_child;
        left_child = 2 * index + 1;
        if (left_child < n){
            return arr[left_child];
        }
        else{
            return -1;
        }
    }
    else{
        return -1;
    }
}

float get_right_value(float arr[], int n, int index) {
    if (index < n){
        int right_child;
        right_child = 2 * index + 2;
        if (right_child < n){
            return arr[right_child];
        }
        else{
            return -1;
        }
    }
    else{
        return -1;
    }
}


int is_max_heap(float arr[], int n) {
    float root;
    root = arr[0];
    for (int i = 1; i < n; i++){
        float number;
        number = arr[i];
        if (number > root){
            return 0;
        }
        if (i == n-1){
            return 1;
        }
    }
}

void heapify(float arr[], int n) {
    int last = n - 1;
    int swap;
    for (int i = (n/2 - 1); i > -1; i--){
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        float max;
        while (right <= last || left <= last){
            if (right<= last){
                if (arr[left] >= arr[right]){
                    max = arr[left];
                }
                else{
                    max = arr[right];
                }
                if (max == arr[left]){
                    swap = left;
                }
                else{
                    swap = right;
                }
            }
            else{
                max = arr[left];
                swap = left;
            }
            if(arr[i] < max){
                float temp = arr[swap];
                arr[swap] = arr[i];
                arr[i] = temp;
                i = swap;
                left = 2 * i + 1;
                right = 2 * i + 2;
            }
            else{
                break;
            }
        }
    }
}

void heapsort(float arr[], int n) {
    while (n){
        float temp = arr[0];
        arr[0] = arr[n-1];
        arr[n-1] = temp;
        n--;
        int curr = 0;
        int left = 1;
        int right = 2;
        int last = n-1;
        float max;
        int swap;
        while (right <= last || left <= last){
            if (right <= last){
                if (arr[left] >= arr[right]){
                    max = arr[left];
                }
                else{
                    max = arr[right];
                }
                if (max == arr[left]){
                    swap = left;
                }
                else{
                    swap = right;
                }
            }
            else{
                max = arr[left];
                swap = left;
            }
            if (arr[curr] < max){
                float temporary = arr[curr];
                arr[curr] = arr[swap];
                arr[swap] = temporary;
                curr = swap;
                left = 2 * curr + 1;
                right = 2 * curr + 2;
            }
            else{
                break;
            }
        }
    }
}

float find_most_common_element(float arr[], int n) {
    float count[n];
    float maximum;
    maximum = count[0];
    int location;
    location = 0;

    for (int a = 0; a < n; a++){
        count[a] = 0;
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (arr[i] == arr[j]){
                count[i]++;
            }
        }
    }

    for (int c = 1; c < n; c++)
    {
        if (arr[c] > maximum)
        {
            maximum  = arr[c];
            location = c+1;
        }
    }
    return arr[location];
}
