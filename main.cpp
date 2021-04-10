#include <string>
#include <iostream>
#include <cmath>
#include <set>
#include <algorithm>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int n, m, k, p, c;
    cout << "Введіть число змінних: ";
    cin >> n;
    m = pow(2, n);
    int a[n + 1][m + 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            a[i][j] = 0;
    //формуємо набори
    for (int j = 1; j <= n; j++) {
        k = m / (pow(2, j));
        p = 0;
        c = 0;
        for (int i = k + 1; i <= m; i++) {
            if (p < k) {
                a[j][i] = 1;
                p++;
            } else if (c < k - 1) {
                a[j][i] = 0;
                c++;
            } else {
                p = 0;
                c = 0;
            }

        }

    }
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            cout << a[i][j] << " ";
        }

        cout << endl;
    }
    int Cube[m + 1][n + 1];
    int Vector[m + 1];
    int choose;
    cout << "Виберіть спосіб задання функції: 1) векторно; 2) порядковим номером; 3)кубами " << endl;
    cin >> choose;
    if (choose == 1) {

        for (int i = 1; i <= m; ++i) {
            cin >> Vector[i];
            if (Vector[i] != 0 and Vector[i] != 1) {
                cout << "Ви ввели не вірне значення, тому програма завершилася";
                exit(0);
            }
        }

    }
    if (choose == 2) {
        cout<<"Введіть порядковий номер "<<endl;
        int bin, dec;
        cin >> dec;


        for (int i = m; i > 0; i--) {
            bin = dec % 2;
            dec /= 2;
            Vector[i] = bin;
        }

        for (int i = 1; i <= m; ++i) {
            cout << Vector[i] << " ";
        }
        cout << endl;

    }
    //формуємо нульовий куб
    int q = 0, w = 0;
    bool flug = false;
    for (int j = 1; j <= m; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (Vector[j] == 1) {
                Cube[q][w] = a[i][j];
                w++;
                flug = true;
            }

        }

        if (flug) {
            q++;
            w = 0;
        }
        if (j == m)
            break;

        flug = false;
    }
    if (choose == 3 ){
        int nabir;
        cout<<"Введіть кількість наборів у кубі";
        cin>>nabir;
        for (int i = 0; i < nabir; ++i) {
            for (int j = 0; j < n; ++j) {
                cin>>Cube[i][j];
                if (Cube[i][j] != 0 and Cube[i][j] != 1){
                    cout<<"Програма закінчилася, оскільки ви ввели не правильні числа";
                    exit(0);
                }

            }
            for (int j = 0; j < n; ++j) {
                cout<<Cube[i][j]<<" ";
            }
            cout<<endl;
        }
        q = nabir;
    }
    int row[q][n];
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < n; j++) {
            cout << Cube[i][j] << " ";
            row[i][j] = 0;
        }

        cout << endl;
    }

    cout << "_____________________" << endl;
    cout<<"Перший куб"<<endl;
    int index = 0;
    int count = 0;
    int num = 0;

    for (int i = 0; i < q; ++i) {

        for (int l = i + 1; l < q; ++l) {
            for (int j = 0; j < n; ++j) {
                if (Cube[i][j] != Cube[l][j]) {
                    index++;

                }
            }
            if (index == 1) {
                for (int j = 0; j < n; ++j) {

                    if (Cube[i][j] != Cube[l][j]) {
                        count++;

                        if (count == 1) {
                            for (int i1 = 0; i1 < n; ++i1) {
                                row[i][i1] = Cube[l][i1];
                            }
                            row[i][j] = Cube[l][j];
                            row[i][j] = 2;

                        } else {
                            for (int i1 = 0; i1 < n; ++i1) {
                                row[num + 1][i1] = Cube[l][i1];
                            }
                            row[num + 1][j] = Cube[l][j];
                            row[num + 1][j] = 2;
                            num++;
                        }

                    }

                }
            }
            index = 0;

        }
    }
    //сортую куб по групам
    int temp = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= num; ++j) {
            if (row[j][i] == 2) {

                for (int l = temp; l <= j; ++l) {
                    for (int i1 = 0; i1 < n; ++i1) {
                        swap(row[j][i1], row[l][i1]);
                    }
                }
                temp++;

            }
        }

    }


    for (int i = 0; i <= num; i++) {
        for (int j = 0; j < n; j++) {
            cout << row[i][j] << " ";
        }

        cout << endl;
    }

    int first, last = 50, caunt = 0;
    int check = 0, colum = 0, ind = 0;
    bool checkkub = true;
    int Cube2[num + 1][n];
    int checklist[num + 1];
    //формування куба 2
    for (int i = 0; i < n; ++i) {
        for (int l = i; l <= num; ++l) {
            //перевіряємо кожну групу
            if (row[l][i] == 2) {
                caunt++;
                if (caunt == 1)
                    first = l;
                else
                    last = l;
                if (last == -1)
                    last = first;
            }
        }
        //шукаємо тільки одну відмінність
        for (int j = first; j <= last; ++j) {
            for (int l = 0; l < n; ++l) {
                if (row[j][l] != row[j + 1][l] and row[j + 1][i] == 2) {
                    check++;

                }
            }

            if (check == 1) {

                for (int l = 0; l < n; ++l) {
                    if (row[j][l] != row[j + 1][l] and row[j + 1][i] == 2) {
                        ind++;

                        if (ind == 1) {
                            for (int i1 = 0; i1 < n; ++i1) {
                                Cube2[j][i1] = row[j][i1];
                            }
                            Cube2[j][l] = 2;
                            checklist[j + 1] = 0;
                            checkkub = false;

                        } else {
                            for (int i1 = 0; i1 < n; ++i1) {
                                Cube2[colum + 1][i1] = row[j][i1];
                            }
                            Cube2[colum + 1][l] = 2;
                            colum++;
                            checklist[j + 1] = 0;
                        }
                    }
                }
            } else if (check != 0 and check != 1 or check == 0 and j == last and checklist[j] != 0) {
                if (check != 0 and check != 1)
                    checklist[j] = 1;
                else
                    checklist[j] = 1;


            }
            check = 0;
        }
        caunt = 0;
        last = -1;
    }
    int lastarr[num + 1][n];
    int last_index = 0;

    if (checkkub) {
        //формуємо масив для покриття
        for (int i = 0; i <= num; ++i) {
            for (int j = 0; j < n; ++j) {
                lastarr[i][j] = row[i][j];
            }
        }
        last_index = num + 1;
    } else {

        cout << "___________________" << endl;
        cout << "Другий куб" << endl;
        int rowTo[colum + 1][n];
        bool one = false;
        int coin = 0;
        int two_check = 0;
        //шукаємо однакові набори щоб їх склеїти
        for (int i = 0; i <= colum; i++) {
            for (int k = i + 1; k <= colum; k++) {
                if (!one) {
                    for (int j = 0; j < n; ++j) {
                        if (Cube2[i][j] == Cube2[k][j]) {
                            coin++;

                        }
                    }
                    if (coin == n) {
                        for (int j = 0; j < n; ++j) {
                            rowTo[two_check][j] = Cube2[i][j];
                        }
                        one = true;
                        two_check++;
                    }

                    coin = 0;
                }

            }
            one = false;

        }

        for (int i = 0; i < two_check; i++) {
            for (int j = 0; j < n; j++) {

                cout << rowTo[i][j] << " ";
            }
            cout << endl;
        }


        //формуємо склеювання для всіх імплікант
        for (int i = 0; i <= num; ++i) {
            if (checklist[i] == 1) {
                for (int j = 0; j < n; ++j) {
                    lastarr[last_index][j] = row[i][j];
                }
                last_index++;
            }

        }
        for (int i = 0; i < two_check; ++i) {
            for (int j = 0; j < n; ++j) {
                lastarr[last_index][j] = rowTo[i][j];
            }
            last_index++;
        }

        cout << "-------------------" << endl;
        cout << "Імпліканти, які залишилися після склеювання" << endl;

        for (int i = 0; i < last_index; i++) {
            for (int j = 0; j < n; j++) {
                cout << lastarr[i][j] << " ";
            }
            cout << endl;
        }
    }
        int final[last_index][q];
        for (int i = 0; i < last_index; ++i) {
            for (int j = 0; j < q; ++j) {
                final[i][j] = 0;
            }
        }

    //таблиця покриття
    int score = 0, twice = 0;
    for (int i = 0; i < last_index; ++i) {
        for (int j = 0; j < n; ++j) {
            if (lastarr[i][j] == 2)
                twice++;
        }
        for (int l = 0; l < q; ++l) {

            if (twice == 1)
                for (int j = 0; j < n; ++j) {

                    if (lastarr[i][j] == Cube[l][j])
                        score++;
                    if (n - score == 1) {
                        final[i][l] = 1;
                    }
                }
            else if (twice == 2)
                for (int j = 0; j < n; ++j) {
                    if (lastarr[i][j] == Cube[l][j])
                        score++;
                    if (n - score == 2) {
                        final[i][l] = 1;
                    }
                }
            score = 0;

        }
        twice = 0;
    }
    cout << "Таблиця покриття" << endl;
    for (int i = 0; i < last_index; i++) {
        for (int j = 0; j < q; j++) {

            cout << final[i][j] << " ";
        }
        cout << endl;
    }
    set<int> vec;
    int amount = 0, l_ind;
    int ar[q];
    for (int i = 0; i < q; ++i) {
        ar[i] = 0;
    }
    //знаходження МДНФ
    for (int j = 0; j < q; ++j) {
        for (int l = 0; l < last_index; ++l) {
            if (final[l][j] == 1 && ar[j] == 0) {
                amount++;
                l_ind = l;
            }
        }
        if (amount == 1) {

            for (int l = 0; l < q; ++l) {
                if (final[l_ind][l] == 1 && ar[l] == 0) {
                    ar[l] = 1;
                    vec.insert(l_ind);

                }

            }

        }
        amount = 0;
    }
    string minimal = "";
    for (int i = 0; i < last_index; ++i) {
        if (vec.count(i)) {
            for (int j = 0; j < n; ++j) {
                if (lastarr[i][j] == 0)
                    minimal += "notX" + to_string(j + 1);
                else if (lastarr[i][j] == 1)
                    minimal += "X" + to_string(j + 1);
            }
            if (i != last_index - 1)
                minimal += " \\/ ";
        }

    }
    cout << minimal;
    return 0;
}
