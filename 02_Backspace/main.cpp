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
            if (idxT == dqT.size()) { //���� ����������
                if (dqS.size() % 2 == 0) { //¦�� �� ������ ��
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
                if (idxS == 0) { // ù��° ����
                    if ((dqS[idxS+1] == dqT[idxT]) && (dqS[idxS]!=dqT[idxT+1])) {   //2���� �ش�, �� ���� ������
    //dq �� ������ it�� begin�̶� ������ ���ϱ�
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
//                    if (*(++dqS[idxS]) == *(++dqT[idxT])) { //�״��� ���Ұ� ������ ������ ����..
//                        varout(*dqS[idxS]);
//                        varout(*dqT[idxT]);
//                        cout("nothing to do");
//                    }
                    }
                }
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

//
//

//
//



}
