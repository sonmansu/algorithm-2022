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
        if (idxT >= dqT.size()) { //���� ����������
            if ( (dqS.size() - idxS) % 2 == 0) { //¦�� �� ������ ��
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

        /** �� ���� **/
        /** 1. ù �� ���� ���� �� **/
        if (dqS[idxS] == dqT[idxT]) {
            // 1) ù��° ������ ��� 1�� �����ϰ� ���� ����
            if (firstDeleted == 0) {
//            if (it == dqS.begin() && idxS == 0) {
                firstDeleted = 1;
                deque<char> dqTemp = dqS;
                dqTemp.pop_front();
                operation(dqTemp, idxS, idxT);
            }
            // 2) �������, ����α�
            operation(dqS, idxS+1, idxT+1);
            // 3) ������ �ΰ� �� ������
            dqS.erase(dqS.begin()+idxS);
            dqS.erase(dqS.begin()+idxS);
            operation(dqS, idxS, idxT);
        /** ù �� ���� �ٸ��� **/
        } else {
            // 2-1) ����Ű�°� ù���Ҷ�� �Ѱ��� ���� ���� ����.
            if (firstDeleted == 0) {
//            if (it == dqS.begin() && idxS == 0) {
                firstDeleted = 1;
                deque<char> dqTemp = dqS;
                dqTemp.pop_front();
                operation(dqTemp, idxS, idxT);
            }
            // 2-2) ������ �ΰ� ����
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
        cout << i << "��° �׽�Ʈ!============================" << endl;
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
