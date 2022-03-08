#include <iostream>
#include "../smtool.h"
using namespace std;

deque<char> dqT;

string operation(deque<char> dqS) {
    // string to list
    deque<char>:: iterator it = dqS.begin();

    int idxS = 0, idxT = 0;


    while (true) {
        contout(dqS);
        varMout("dqS[idxS]: ",dqS[idxS]);
        varMout("dqT[idxT]: ",dqT[idxT]);

        if (dqS == dqT) {
            return("YES\n");
        }
        if (idxT >= dqT.size()) { //끝에 도달했을때
            if ( (dqS.size() - idxS) % 2 == 0) { //짝수 개 남았을 시
                return("YES\n");
            } else {
                return("NO\n");
            }
        }
        if ((dqS.size() < dqT.size()) || (dqS.size() == dqT.size() && dqS != dqT)) {
            return("NO\n");
        }
        // 비교 시작
        if (dqS[idxS] == dqT[idxT]) {
            if (it == dqS.begin() && idxS == 0) { // 첫번째 원소
                if ((dqS[idxS+1] == dqT[idxT]) && (dqS[idxS]!=dqT[idxT+1])) {   //2번에 해당, 앞 원소 날려줌
                    dqS.pop_front();
                    continue;
                }
            }
            idxS++;
            idxT++;
            /** 첫 두 개가 다를때 **/
        } else if (it == dqS.begin() && idxS == 0) { //가르키는게 첫원소라면 한개만 지움.. 두개지워줘도 되잖아 ?
            dqS.pop_front(); //한개만 지움
            int curIdxS =idxS;
            int curIdxT =idxT;

            if (operation(dqS) == "YES\n"); {
                return "YES\n";
            }
            //restore
            idxS = curIdxS;
            idxT = curIdxT;
        } else { //두개씩 지움
            dqS.erase(dqS.begin()+idxS);
            dqS.erase(dqS.begin()+idxS);
        }

    }
}
int main() {
    int N;
    cin >> N;
    string s,t;
    for (int i = 0; i < N; i++) {
        cout << i << "번째 테스트!============================" << endl;
//        cin >> s >> t;
        s = "abbabba";
        t = "aa";

        deque<char> dqS(s.begin(), s.end());
        dqT = deque<char>(t.begin(), t.end());

        cout << operation(dqS);

    }

}
