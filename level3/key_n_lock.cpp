// 블로그 작성용 추가
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void rotate(vector< vector<int> >& key){  // 키를 회전시키기위함
    vector< vector<int> > temp(key.size(), vector<int>(key.size(), 0));
    for (int i = 0; i < key.size(); i++){
        for (int j = 0; j < key.size(); j++){
            temp[i][j] = key[j][key.size() - i - 1];
        }
    }
    key = temp;
}

void print(vector< vector<int> > mat){
    for (int i = 0; i < mat.size(); i++){
        for (int j = 0; j < mat.size(); j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

bool unlock(vector< vector<int> > mat, vector< vector<int> > key, int y, int x){
    for (int i = 0; i < key.size(); i++){  // mat xor key 하고 lock이 열릴려면 가운데에 열쇠 복사한 부분이 모두 1로 채워져있어야 함
        for (int j = 0; j < key.size(); j++){
            mat[i + y][j + x] ^= key[i][j];
        }
    }

    // print(mat);

    for (int i = key.size() - 1; i < mat.size() - (key.size() - 1); i++)  // 열쇠부분이 모두 1인지 확인
        for( int j = key.size() -1; j < mat.size() - (key.size() -1); j++)
            if (mat[i][j] == 0) {
                return false;
            }

    return true;
}

bool solution(vector< vector<int> > key, vector< vector<int> > lock) {  // main solution
    int mat_size = 2 * (key.size() - 1) + lock.size();
    vector< vector<int> > mat(mat_size, vector<int>(mat_size, 0));  // lock, key 들어갈 판떼기 만들기
    for (int i = 0; i < lock.size(); i++){  // 판떼기 정중앙에 lock 복사
        for (int j = 0; j < lock.size(); j++){
            mat[i + (mat_size - lock.size()) / 2][j + (mat_size - lock.size()) / 2] = lock[i][j];
        }
    }

    // rotate(key);
    // rotate(key);
    // unlock(mat, key, 2, 5);
    
    for (int i = 0; i < 4; i++){
        // 회전
        for (int j = 0; j < mat_size - key.size() + 1; j++){
            // 위아래 이동
            for (int k = 0; k < mat_size - key.size() + 1; k++){
                // 좌우 이동                
                if (unlock(mat, key, k, j)) return true;
            }
        }
        rotate(key);
    }
    return false;
}

int main(){
    // for test
    vector< vector<int> > key(3, vector<int>(3, 1));  // 3x3 1 initialized
    vector< vector<int> > lock(4, vector<int>(4, 1));  // 4x4 1 initialized
    key[1][2] = 0;
    /*
    { {1, 1, 1}, 
      {1, 1, 0}, 
      {1, 1, 1} };
    */
    lock[0][3] = 0;
    lock[2][3] = 0;
    /*
    { {1, 1, 1, 0},
      {1, 1, 1, 1},
      {1, 1, 1, 0},
      {1, 1, 1, 1} }   
    */

    cout << solution(key, lock) << endl;

    return 0;
}







// 정답코드
// #include <string>
// #include <vector>

// using namespace std;

// void rotate(vector< vector<int> >& key){
//     vector< vector<int> > temp(key.size(), vector<int>(key.size(), 0));
//     for (int i = 0; i < key.size(); i++){
//         for (int j = 0; j < key.size(); j++){
//             temp[i][j] = key[j][key.size() - i - 1];
//         }
//     }
//     key = temp;
// }

// bool unlock(vector< vector<int> > mat, vector< vector<int> > key, int y, int x){
//     for (int i = 0; i < key.size(); i++){  // mat xor key, lock이 열릴려면 가운데 부분이 모두 1로 채워져있어야 함.
//         for (int j = 0; j < key.size(); j++){
//             mat[i + y][j + x] ^= key[i][j];
//         }
//     }

//     for (int i = key.size() - 1; i < mat.size() - (key.size() - 1); i++)
//         for( int j = key.size() -1; j < mat.size() - (key.size() -1); j++)
//             if (mat[i][j] == 0) {
//                 return false;
//             }

//     return true;
// }

// bool solution(vector< vector<int> > key, vector< vector<int> > lock) {  // main solution
//     int mat_size = 2 * (key.size() - 1) + lock.size();
//     vector< vector<int> > mat(mat_size, vector<int>(mat_size, 0));  // lock, key 들어갈 판떼기 만들기
//     for (int i = 0; i < lock.size(); i++){  // 판떼기 정중앙에 lock 복사
//         for (int j = 0; j < lock.size(); j++){
//             mat[i + (mat_size - lock.size()) / 2][j + (mat_size - lock.size()) / 2] = lock[i][j];
//         }
//     }
    
//     for (int i = 0; i < 4; i++){
//         // 회전
//         for (int j = 0; j < mat_size - key.size() + 1; j++){
//             // 위아래 이동
//             for (int k = 0; k < mat_size - key.size() + 1; k++){
//                 // 좌우 이동                
//                 if (unlock(mat, key, k, j)) return true;
//             }
//         }
//         rotate(key);
//     }
//     return false;
// }