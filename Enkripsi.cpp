#include<iostream>
#include<vector>
using namespace std;
int main(){
    int x,y,i,j,k,n;
    cout<<"Input Ordo Matrix\n";
    cin>>n;
    //Menginputkan ukuran dari key matrik yang akan digunakan
    
    cout<<"Input Key Matrixs\n";
    int a[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    //Menginput nilai yang akan digunakan sesuai dengan ukuran ordo matrik yang sudah di tentukan oleh n sebelumnya.
    //Diproses ini akan terbentuk sebuah matriks dengan ordo nxn
    
    cout<<"Input Plaintext yang akan di Enkripsi :\n";
    string s;
    cin>>s;									//Menginput string s yang berisi plaintext yang akan digunakan untuk menjadi sebuah cipher text
    int temp = (n-s.size()%n)%n;
    for(i=0;i<temp;i++){
        s+='x';
    }
    k=0;
    //Saat menginputkan string s, maka akan terjadi sebuah pemrosesan plaintext yang akan dikonversi menjadi sebuah angka k
    
    string ans="";
    while(k<s.size()){		//Disini angka akan disesuaikan dengan plaintext yang telah di input sebelumya
        for(i=0;i<n;i++){	//
            int sum = 0;
            int temp = k;
            for(j=0;j<n;j++){
                sum += (a[i][j]%26*(s[temp++]-'a')%26)%26;	//Key dan angka dari hasil plaintext akan dikalikan dengan atas bawah dan ditambah juga dengan perkalian yang lain
                sum = sum%26;								//saat hasil sum lebih dari 26, maka hasil akan di mod 26 sehingga hasil akhir akan kurang dari 26
            }
            ans+=(sum+'a');									//Setelah itu hasil dari perhitungan akan diubah kembali menjadi sebuah huruf
        }													//Dan huruf itu lah yang disebut dengan enkripsi
        k+=n;
    }
    cout<<ans<<'\n';	//hasil dari enkripsi akan ditampilkan

    return 0;    
}
