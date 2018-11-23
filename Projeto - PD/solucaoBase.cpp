#include <bits/stdc++.h>
using namespace std;
#define fastcin ios_base::sync_with_stdio(false)
#define precisecout cout << fixed << setprecision(10)
#define pb push_back
#define mk make_pair
#define mkt make_tuple
#define binary(x) bitset<8*sizeof(x)>(x)
#define zero(x) memset(x, 0, sizeof(x))
#define set(x, i) memset(x, i, sizeof(x))
#define ii pair<int, int>
#define iii tuple<int, int, int>
#define ll long long
#define ull unsigned long long
#define inf 0x3f3f3f3f

#ifdef ebug
#define dprintf printf
#else
#define dprintf if(false) printf
#endif

int r, c;
char board[16][16];
char isleMap[16][16];
char solutions[3][16][16];
ull totalSolutions = 0;
int uniqueSolutions = 0;
unordered_map<ull, ull> dp;

ull getBoardHash(){
    ull hash = 0;
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            hash |= ((ull)(board[i][j] & 0b11) << (2*j + (2*c*i)));
    return hash;
}

void restoreBoardFromHash(ull hash){
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++){
            board[i][j] = ((hash >> (2*j + (2*c*i))) & 0b11);
            if(board[i][j] == 0b11)
                board[i][j] = 3;
        }
}

// Vector of directions to open in order to avoid code duplication
int dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

// Marks all points of the isle which contains the point (i,j) in isleMap
void mapIsle(int i, int j){
    isleMap[i][j] = 1;
    for(int move = 0; move < 4; move++){
        // If I can move to respective direction and it is not an empty space, it is part of the current isle
        if(i + dir[move][0] >= 0 && i + dir[move][0] < r && j + dir[move][1] >= 0 && j + dir[move][1] < c){
            if(board[i + dir[move][0]][j + dir[move][1]] != 3 && !isleMap[i + dir[move][0]][j + dir[move][1]]){
                mapIsle(i + dir[move][0], j + dir[move][1]);
            }
        }
    }
}

char isSolvable(){
    memset(isleMap, 0, sizeof(isleMap));
    char foundOneIsle = 0;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(!isleMap[i][j] && board[i][j] != 3){
                //If board's position is a piece and is not marked as a isle, found an isle
                if(!foundOneIsle){
                    //If no isle has been found, this isle is the first and must be mapped
                    foundOneIsle = 1;
                    mapIsle(i, j);
                }
                else{
                    //Else this is the second found isle, thus there is no solution
                    return 0;
                }
            }
        }
    }

    //If one isle has been found, it may still be solvable
    //Zero isles will never happen due to the problem's nature
    return 1;
}

void solve(){
    //Uses a bfs to open all board moves in order, so the amount of times a specific board is seen can be forward-propagated
    
    dp.clear();
    queue<ull> mapsToOpen;
    ull boardHash = getBoardHash();
    ull occs;
    dp[boardHash] = 1;
    mapsToOpen.push(boardHash);
    
    while(!mapsToOpen.empty()){
        boardHash = mapsToOpen.front();
        mapsToOpen.pop();
        
        restoreBoardFromHash(boardHash);
        occs = dp[boardHash];
        
        //Check if current board is a solution
        int SolutionI;
        int SolutionJ;
        bool solved = false;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                //On non-empty piece found
                if(board[i][j] != 3){
                    //If one piece was already found, the game is not yet complete, no need to search for solution further
                    //else no piece was found, this piece may be a solution, store coordinates and continue search
                    if(solved){
                        solved = false;
                        goto nestedLoopOut;
                    }
                    else{
                        solved = true;
                        SolutionI = i;
                        SolutionJ = j;
                    }
                }
            }
        } nestedLoopOut:;

        if(solved){
            //If only one piece was found previously, this is a solution
            totalSolutions += occs;
            uniqueSolutions++;
            solutions[board[SolutionI][SolutionJ]][SolutionI][SolutionJ] = 1;
            continue;
        }
        
        if(isSolvable()){
            //If the board is solvable (there's only one isle in it)            
            
            //Enqueue next moves and count board occurences
            for(int i = 0; i < r; i++){
                for(int j = 0; j < c; j++){
                    if(board[i][j] != 3){
                        //If found piece: simulate all 4 moves of such piece and call recursion on updated map
                        for(int move = 0; move < 4; move++){
                            if(i + dir[move][0] >= 0 && i + dir[move][0] < r && j + dir[move][1] >= 0 && j + dir[move][1] < c){
                                if(board[i + dir[move][0]][j + dir[move][1]] == (board[i][j] + 1) % 3){
                                    int a = board[i + dir[move][0]][j + dir[move][1]];
                                    int b = board[i][j];

                                    //Update map
                                    board[i + dir[move][0]][j + dir[move][1]] = b;
                                    board[i][j] = 3;

                                    //Enqueue bfs
                                    ull hash = getBoardHash();
                                    if(dp.count(hash))
                                        dp[hash] += occs;
                                    else{
                                        dp[hash] = occs;
                                        mapsToOpen.push(hash);
                                    }

                                    //Reverse update
                                    board[i + dir[move][0]][j + dir[move][1]] = a;
                                    board[i][j] = b;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main(){
    scanf("%d%d", &r, &c);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            int x;
            scanf("%d", &x);

            //Pieces numbered 0..2 and 3 as invalid are easier to deal with due to the way % operation works
            board[i][j] = x - 1;
            if(board[i][j] == 3)
                board[i][j] = 3;
        }
    }

    //Open all solutions
    solve();

    //Print result
    printf("%lld\n", totalSolutions);
    printf("%d\n", uniqueSolutions);

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            for(int piece = 0; piece <= 2; piece++){
                if(solutions[piece][i][j])
                    printf("%d %d %d\n", i+1, j+1, piece+1);
            }
        }
    }
}