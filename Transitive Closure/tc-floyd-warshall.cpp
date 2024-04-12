#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

// change this value to change the delay between loop iterations
const uint32_t
    DELAY = 1;

void transitiveClosure(vector<vector<uint8_t>>& r) {
    uint32_t
        N,
        i,j,k;

    N = r.size();

    vector<vector<uint8_t>>
        closure(N);

    cout << "\033[2J";

    for (i=0;i<N;i++) {
        closure[i].resize(N);
        for (j = 0; j < N; j++) {
            closure[i][j] = r[i][j];
            cout << "\033[" << i+1 << ';' << 2*j+1 << 'H' << (int)r[i][j];
        }
        closure[i][i] = 1;
    }

    cout << "\033[1;42Hi   j   k\033[2;41H--- --- ---";

    for (k=0;k<N;k++)
        for (i=0;i<N;i++)
            for (j=0;j<N;j++) {
                cout << "\033[3;" << (i < 10? 42 : 41) << 'H' << i;
                cout << "\033[3;" << (j < 10? 46 : 45) << 'H' << j;
                cout << "\033[3;" << (k < 10? 50 : 49) << 'H' << k;
                cout << "\033[5;41H[i][j] = [" << i << "][" << j << "]: " << (int)closure[i][j];
                cout << "\033[6;41H[i][k] = [" << i << "][" << k << "]: " << (int)closure[i][k];
                cout << "\033[7;41H[k][j] = [" << k << "][" << j << "]: " << (int)closure[k][j];
                cout << "\033[9;41HResult: " << (int)closure[i][j] << " || ("
                    << (int)closure[i][k] << " && " << (int)closure[k][j] << ") = ";
                closure[i][j] = closure[i][j] ||
                    closure[i][k] && closure[k][j];
                cout << (int)closure[i][j];
                cout << "\033[" << i+1 << ';' << 2*j+1 << 'H' << (int)closure[i][j];
                cout.flush();
                sleep(DELAY);
            }
    for (i=0;i<N;i++)
        for (j = 0; j < N; j++)
            r[i][j] = closure[i][j];

    cout << "\033[15;1H";
}

int main() {
    // if you want to see a different relation, create a 0-1 matrix
    // representation here, using a vector of vector of uint8_t
    // (aka unsigned char)
    vector<vector<uint8_t>>
        r(4);

    for (uint32_t i=0;i<4;i++)
        r[i].resize(4,0);

    r[0][1] = 1;
    r[1][2] = 1;
    r[2][3] = 1;
    r[0][3] = 1;
    
    // don't modify anything below this line

    transitiveClosure(r);

    for (uint32_t i=0;i<r.size();i++) {
        for (uint32_t j=0;j<r.size();j++)
            cout << (int)r[i][j];
        cout << endl;
    }
    return 0;
}
