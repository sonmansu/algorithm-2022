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
    list<char> lS, lT;

//    cin >> N;
    for (int i = 0; i < N; i++) {
        // get string
//        cin >> s >> t;
        s = "ababa";
        t = "ba";
        // string to list
        list<char> lS(s.begin(), s.end());
        list<char> lT(t.begin(), t.end());
        // make iterator of both of them
        list<char>::iterator itS,itT;
        itS = lS.begin();
        itT = lT.begin();


        while (true) {
            if (lS == lT) {
                cout<<"YES\n";
                break;
            }
            if (itT == lT.end()) { //끝에 도달했을때
                if (lS.size() % 2 == 0) { //짝수 개 남았을 시
                    cout<<"YES\n";
                    break;
                } else {
                    cout<<"NO\n";
                    break;
                }

            }
            if ((lS.size() < lT.size()) || (lS.size() == lT.size() && lS != lT)) {
                cout<<"NO\n";
                break;
            }

            if (*itS++ == *itT++) { //이땐 증가시키기전 itS랑 itT를 비교해주는듯
//                itS++;
//                itT++;
                if (itS == lS.begin()) {
                    if (*(++itS) == *(++itT)) { //그다음 원소가 같으면 없애지 않음..
                        varout(*itS);
                        varout(*itT);
                        cout("nothing to do");
                    } else { //다를 때만 원소 한개 날려줌
                        itS = lS.erase(--itS);
                        itT--;
                    }
                }
//                itS++;
//                itT++;
            /** 첫 두 개가 다를때 **/
            } else if (itS == lS.begin()) {
                itS = lS.erase(itS);

                contout(lS);
                varout(*itS);

            } else {
                itS = lS.erase(itS);
                contout(lS);
                varout(*itS);

                itS = lS.erase(itS); //두번 삭제함..
                contout(lS);
                varout(*itS);

            }




        }



    }





}
