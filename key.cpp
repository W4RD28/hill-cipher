/**
 * Nama : Windu Nursetyadi 
 * NPM  : 140810190041
 */

#include<iostream>
#include<vector>
using namespace std;

// mencari invers modulo
int modInverse(int a, int m){ 
    a=a%m; 
    for(int x=-m;x<m;x++) 
       if((a*x)%m==1) 
          return x; 
} 

// mendapatkan kofaktor matriks
void getCofactor(vector<vector<int> > &a, vector<vector<int> > &temp, int p, int q, int n){ 
    int i=0,j=0; 
    for(int row=0;row<n;row++){ 
        for(int col=0;col<n;col++){ 
            if(row!=p&&col!=q){ 
                temp[i][j++] = a[row][col]; 
                if (j==n-1){ 
                    j=0; 
                    i++; 
                } 
            } 
        } 
    } 
}

// mencari determinan matriks
int determinant(vector<vector<int> > &a, int n, int N){ 
    int D = 0;
    if(n==1) 
        return a[0][0]; 
    vector<vector<int> > temp(N, vector<int>(N));
    int sign = 1;
    for(int f=0;f<n;f++){ 
        getCofactor(a, temp, 0, f, n); 
        D += sign * a[0][f] * determinant(temp, n - 1, N); 
        sign = -sign; 
    }
    return D; 
} 

// mencari adjoin matriks
void adjoint(vector<vector<int> > &a,vector<vector<int> > &adj,int N){ 
    if(N == 1){ 
        adj[0][0] = 1; 
        return; 
    } 
    int sign = 1;
    vector<vector<int> > temp(N, vector<int>(N));
    for(int i=0;i<N;i++){ 
        for(int j=0;j<N;j++){ 
            getCofactor(a, temp, i, j, N); 
            sign = ((i+j)%2==0)? 1: -1; 
            adj[j][i] = (sign)*(determinant(temp, N-1 , N)); 
        } 
    } 
} 

// mencari invers
bool inverse(vector<vector<int> > &a, vector<vector<int> > &inv, int N){ 
    // cek invers melalui keberadaan determinan
    int det = determinant(a, N, N); 
    if(det == 0){ 
        cout << "Inversnya tidak ada"; 
        return false; 
    } 
    
    int invDet = modInverse(det,26);
    cout<<det%26<<' '<<invDet<<'\n';
    vector<vector<int> > adj(N, vector<int>(N));
    adjoint(a, adj, N);  
    for(int i=0;i<N;i++) 
        for(int j=0;j<N;j++) 
            inv[i][j] = (adj[i][j]*invDet)%26; 
    return true; 
} 

void findKey(string plaintext, string ciphertext, vector<vector<int>> &K,
             int N) {

  int i, j;

  if (plaintext.size() != ciphertext.size()) {
    cout << "Jumlah huruf plaintext dan ciphertext tidak sama\n";
  }

  if (plaintext.size() % N != 0 || N < 2) {
    cout << "Ukuran matriks kunci tidak sesuai\n";
  }

  vector<vector<int>> P(N, vector<int>(N));
  vector<vector<int>> C(N, vector<int>(N));
  vector<vector<int>> inversP(N, vector<int>(N));

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      P[i][j] = plaintext[i * N + j] - 97;
      C[i][j] = ciphertext[i * N + j] - 97;
    }
  }

  if (!inverse(P, inversP, N)) {
    cout << "Matriks kunci tidak dapat ditemukan\n";
  }

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      K[i][j] = 0;

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; j++)
        K[i][j] += C[i][k] * inversP[k][j];

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      cout << K[i][j] << " ";
    }
    cout << "\n";
  }
}

int main() {
    string s, d;
    int n;
    vector<vector<int> > key(n, vector<int>(n));

    cout << "Masukkan plaintext\n";
    cin >> s;

    cout << "Masukkan ciphertext\n";
    cin >> d;

    cout << "Masukkan ukuran matriks kunci\n";
    cin >> n;

    cout << "Matriks kuncinya\n";
    findKey(s, d, key, n);
    return 0;
}
