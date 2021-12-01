#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef vector<int> vec;
typedef vector<vector<int> > matrix;

matrix multiple_knapsack_greedy (vec& groups, int gradini, int gradinate);
int max (vec groups, int posti_disponibili);

int main()
{
    int temp[4] = {5,7,3,8};
    vec groups (temp, temp+sizeof(temp)/sizeof(int));

    matrix mat = multiple_knapsack_greedy(groups, 10, 3);

    for (int i=0; i<3; i++) {
        for (int j=0; j<10; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }

    return 0;
}

/*
 * 1) Trovare il max (groups) per capire il primo gruppo che entra nell'attuale riga (gradinata)
 * 2) Far entrare il gruppo e rimuoverlo dal vettore groups
 * 3) STOP = la dimensione di groups è 0 oppure non ci sono più gradinate disponibili
*/

matrix multiple_knapsack_greedy (vec &groups, int gradini, int gradinate) {
    matrix mat(gradinate, vec (gradini,0));

    int counter_gradinata = 0;
    bool flag = false;


    int maximum_people = 0;
    int posti_disponibili = gradini;

    while (groups.size() != 0 || !flag) {
        maximum_people = max(groups, posti_disponibili);

        if (maximum_people < 0) {
            counter_gradinata++;
            if (counter_gradinata == gradinate) { //Contando da 0, abbiamo già raggiunto la gradinata finale
                flag = true;
            }
            else {
                posti_disponibili = gradini;
            }
        }
        else {
            for (int j=gradini-posti_disponibili; j < gradini-posti_disponibili+groups[maximum_people]; j++)
                mat[counter_gradinata][j] = groups[maximum_people];

            posti_disponibili -= groups[maximum_people];
            groups.erase(groups.begin() + maximum_people);
        }
    }

    return mat;
}

int max (vec groups, int posti_disponibili) {
    if (groups.size() == 0)
        return -1;

    int maximum = -1;
    int index = -2;
    for (int i=0; i<(int)groups.size(); i++) {
        if (maximum < groups[i] && groups[i] <= posti_disponibili) {
            maximum = groups[i];
            index = i;
        }
    }

    return index;
}
