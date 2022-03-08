#include <iostream>
#include "../smtool.h"
using namespace std;


int main() {
    int N;
    string s,t;
    deque<char> dqS, dqT;

//    cin >> N;
    for (int i = 0; i < N; i++) {
        // get string
//        cin >> s >> t;
        s = "aababa";
        t = "ababa";
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
            if (idxT >= dqT.size()) { //끝에 도달했을때
                if ( (dqS.size() - idxS) % 2 == 0) { //짝수 개 남았을 시
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
                if (it == dqS.begin()) { // 첫번째 원소
                    if ((dqS[idxS+1] == dqT[idxT]) && (dqS[idxS]!=dqT[idxT+1])) {   //2번에 해당, 앞 원소 날려줌
                        dqS.pop_front();
                        continue;
                    }
                }
                idxS++;
                idxT++;
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

}
