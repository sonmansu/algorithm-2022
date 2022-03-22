#include <iostream>
#include "../smtool.h"
#include "timebomb.h"

using namespace std;

int main() {
    int N, result, answer;
    vector<int> heap;
    int parentI;

    box_ready();
    N = box_size();
    varout(N);
    heap.reserve(N+1);
    heap[0] = 0;

    for (int i = 1; i <= N; i++) {
        heap[i] = i; //idx 집어넣음
    }

    for (int i = 1; i <= N; i++) {
        cout << heap[i] ;
    }
    ENDL;LINE;


    for (int i = N; i >= 2; i--) { //뒤에서 부터 돌림
        for (int i = 1; i <= N; i++) {
            cout << heap[i] << " " ;
        }
        ENDL;

        if (i % 2 == 1) { // if i odd, value is on the right
            parentI = (i-1)/2;
        } else { //if i even, value is on the left
            parentI = i/2;
        }
        cout << heap[i] << ", " << heap[parentI] << endl;
        result = box_comp(heap[i], heap[parentI]);
        if (result == 1) { // child is bigger, swap child's value and parent's value
            int temp = heap[parentI];
            heap[parentI] = heap[i];
            heap[i] = temp;
        }
    }

    result = box_comp(heap[2], heap[3]);
    if (result == 1) answer = heap[2];
    else if (result == -1) answer = heap[3];
    box_report(answer);
}
