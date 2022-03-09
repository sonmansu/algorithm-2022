#include <iostream>
#include "../smtool.h"
using namespace std;

deque<char> dqT;
int answer;
int firstDeleted = 0;

void operation(deque<char> dqS, int idxS, int idxT) {
//    cout<<"operation!=======================\n";
//        contMout("dqS:", dqS);
//        contMout("dqT:", dqT);
//        varMout("dqS[idxS]: ",dqS[idxS]);
//        varMout("dqT[idxT]: ",dqT[idxT]);

//    deque<char>:: iterator it = dqS.begin();

//    while (true) {


        if (answer == 1)
            return;

        if (dqS == dqT) {
            answer = 1;
            return;
        }
        if (idxT >= dqT.size()) { //끝에 도달했을때
            if ( (dqS.size() - idxS) % 2 == 0) { //짝수 개 남았을 시
                answer = 1;
                return;
            } else {
                return;
            }
        }
        if (dqS.size() < dqT.size())
            return;

        if (dqS.size() == dqT.size() && dqS != dqT)
            return;

        /** 비교 시작 **/
        /** 1. 첫 두 원소 같을 때 **/
        if (dqS[idxS] == dqT[idxT]) {
            // 1) 첫번째 원소일 경우 1개 삭제하고 진행 가능
            if (firstDeleted == 0) {
//            if (it == dqS.begin() && idxS == 0) {
                firstDeleted = 1;
                deque<char> dqTemp = dqS;
                dqTemp.pop_front();
                operation(dqTemp, idxS, idxT);
            }
            // 2) 통과가능, 살려두기
            operation(dqS, idxS+1, idxT+1);
            // 3) 같더라도 두개 다 지워줌
            dqS.erase(dqS.begin()+idxS);
            dqS.erase(dqS.begin()+idxS);
            operation(dqS, idxS, idxT);
        /** 첫 두 개가 다를때 **/
        } else {
            // 2-1) 가르키는게 첫원소라면 한개만 지울 수도 있음.
            if (firstDeleted == 0) {
//            if (it == dqS.begin() && idxS == 0) {
                firstDeleted = 1;
                deque<char> dqTemp = dqS;
                dqTemp.pop_front();
                operation(dqTemp, idxS, idxT);
            }
            // 2-2) 무조건 두개 지움
            dqS.erase(dqS.begin()+idxS);
            dqS.erase(dqS.begin()+idxS);
            operation(dqS, idxS, idxT);
        }
//    }
}
int main() {
    int N;
    cin >> N;
    string s,t;

    for (int i = 0; i < N; i++) {
        cout << i << "번째 테스트!============================" << endl;
        cin >> s >> t;
//        s = "backspace"; t = "space";

        answer = 0;
        firstDeleted = 0;

        deque<char> dqS(s.begin(), s.end());
        dqT = deque<char>(t.begin(), t.end());
        operation(dqS, 0, 0);
        if (answer == 1) cout << "YES\n";
        else cout << "NO\n";

    }

}
