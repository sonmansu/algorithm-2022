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
        if (idxT >= dqT.size()) { //���� ����������
            if ( (dqS.size() - idxS) % 2 == 0) { //¦�� �� ������ ��
                return("YES\n");
            } else {
                return("NO\n");
            }
        }
        if ((dqS.size() < dqT.size()) || (dqS.size() == dqT.size() && dqS != dqT)) {
            return("NO\n");
        }
        // �� ����
        if (dqS[idxS] == dqT[idxT]) {
            if (it == dqS.begin() && idxS == 0) { // ù��° ����
                if ((dqS[idxS+1] == dqT[idxT]) && (dqS[idxS]!=dqT[idxT+1])) {   //2���� �ش�, �� ���� ������
                    dqS.pop_front();
                    continue;
                }
            }
            idxS++;
            idxT++;
            /** ù �� ���� �ٸ��� **/
        } else if (it == dqS.begin() && idxS == 0) { //����Ű�°� ù���Ҷ�� �Ѱ��� ����.. �ΰ������൵ ���ݾ� ?
            dqS.pop_front(); //�Ѱ��� ����
            int curIdxS =idxS;
            int curIdxT =idxT;

            if (operation(dqS) == "YES\n"); {
                return "YES\n";
            }
            //restore
            idxS = curIdxS;
            idxT = curIdxT;
        } else { //�ΰ��� ����
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
        cout << i << "��° �׽�Ʈ!============================" << endl;
//        cin >> s >> t;
        s = "abbabba";
        t = "aa";

        deque<char> dqS(s.begin(), s.end());
        dqT = deque<char>(t.begin(), t.end());

        cout << operation(dqS);

    }

}
