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
            if (idxT >= dqT.size()) { //���� ����������
                if ( (dqS.size() - idxS) % 2 == 0) { //¦�� �� ������ ��
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
            // �� ����
            if (dqS[idxS] == dqT[idxT]) {
                if (it == dqS.begin()) { // ù��° ����
                    if ((dqS[idxS+1] == dqT[idxT]) && (dqS[idxS]!=dqT[idxT+1])) {   //2���� �ش�, �� ���� ������
                        dqS.pop_front();
                        continue;
                    }
                }
                idxS++;
                idxT++;
                /** ù �� ���� �ٸ��� **/
            } else if (it == dqS.begin()) { //����Ű�°� ù���Ҷ�� �Ѱ��� ����
                dqS.pop_front();

                contout(dqS);
            } else { //�ΰ��� ����
                dqS.pop_front();
                dqS.pop_front();
                contout(dqS);
            }
        }
    }

}
