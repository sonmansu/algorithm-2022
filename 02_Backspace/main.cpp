#include <iostream>
#include "../smtool.h"
using namespace std;


int main() {
//    list<char> l = {'a','b'};
//    contout(l);
//
//    list<char>::iterator it;
//    it = l.begin();
//    cout << *it;
//    it++;
//        cout << *it;
//
//        if(it == l.end()) cout("1yes");
//
//        it++;
//            cout << *it;
//        if(it == l.end()) cout("2yes");
    //=================

    int N;
    string s,t;
    deque<char> dqS, dqT;

    cin >> N;
    for (int i = 0; i < N; i++) {
        // get string
        cin >> s >> t;
//        s = "aab";
//        t = "ab";
        // string to list
        deque<char> dqS(s.begin(), s.end());
        deque<char> dqT(t.begin(), t.end());
        deque<char>:: iterator it = dqS.begin();

        int idxS = 0, idxT = 0;

        while (true) {
            if (dqS == dqT) {
                cout<<"YES\n";
                break;
            }
            if (idxT == dqT.size()) { //끝에 도달했을때
                if (dqS.size() % 2 == 0) { //짝수 개 남았을 시
                    cout<<"YES\n";
                    break;
                } else {
                    cout<<"NO\n";
                    break;
                }
            }
            if ((dqS.size() < dqT.size()) || (dqS.size() == dqT.size() && dqS != dqT)) {
                cout<<"NO\n";
                break;
            }
            // 비교 시작
            if (dqS[idxS] == dqT[idxT]) {
                if (idxS == 0) { // 첫번째 원소
                    if ((dqS[idxS+1] == dqT[idxT]) && (dqS[idxS]!=dqT[idxT+1])) {   //2번에 해당, 앞 원소 날려줌
    //dq 앞 날리고서 it이 begin이랑 같은지 비교하기
//                        if (it == dqS.begin()) {
//                            cout("yes");
//                        } else {
//                            cout("no");
//                        }
//                        dqS.pop_front();
//
//                        if (it == dqS.begin()) {
//                            cout("yes");
//                        } else {
//                            cout("no");
//                        }
                        continue;
//                    if (*(++dqS[idxS]) == *(++dqT[idxT])) { //그다음 원소가 같으면 없애지 않음..
//                        varout(*dqS[idxS]);
//                        varout(*dqT[idxT]);
//                        cout("nothing to do");
//                    }
                    }
                }
            /** 첫 두 개가 다를때 **/
            } else if (it == dqS.begin()) { //가르키는게 첫원소라면 한개만 지움
                dqS.pop_front();

                contout(dqS);
            } else { //두개씩 지움
                dqS.pop_front();
                dqS.pop_front();

                contout(dqS);
            }


        }

        }

//
//

//
//



}
