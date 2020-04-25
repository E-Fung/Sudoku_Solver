#include <iostream>     //is required for user I/O

using namespace std;    //basically gives shortcuts to using std::cout

#define DEBUG_ENABLED             //uncomment to debug

void print(int puzzle[9][9]){
    for(int row=0;row<9;row++){
        for(int col=0;col<9;col++){
            cout<<puzzle[row][col]<<" ";
        }
        cout<<endl;
    }
}

bool check(int puzzle[9][9],int position,int value){            //checks if the number is valid in that position
    int row = position/9;
    int col = position%9;
    for(int i=0;i<9;i++){
        if(puzzle[row][i]==value || puzzle[i][col]==value){    //checks the row and column
            #ifdef DEBUG_ENABLED
            cout <<value<<" not valid for row:"<<row<<" col: "<<col<<endl;
            #endif
            return false;
        }
    }
    for(int j=0;j<3;j++){                                      //checks the 3 by 3 block
        for(int k=0;k<3;k++){
            if(puzzle[(row/3)*3+j][(col/3)*3+k]==value){
                #ifdef DEBUG_ENABLED
                cout <<value<<" not valid for row:"<<row<<" col: "<<col<<endl;
                #endif
                return false;
            }
        }
    }
    puzzle[row][col]=value;
    #ifdef DEBUG_ENABLED
    cout<<endl;
    print(puzzle);
    #endif
    return true;
}

int find_next_zero(int puzzle[9][9]){
    for(int i=0;i<81;i++){
        if(puzzle[i/9][i%9]==0){
            return i;
        }
    }
    return 100;
}

bool solve(int puzzle[9][9]){
    int position = find_next_zero(puzzle);
    if(position==100){                 //all cells are valid (1 of 2 cases)
        return true;
    }
    for(int i=1;i<10;i++){
        if(check(puzzle,position,i)){  //if we find a number that satisfies the rules for that cell, if not, try i++
            if(position==80){          //if it is the last cell, we have solved the puzzle (1 of 2 cases)
                return true;
            }
            puzzle[position/9][position%9]=i;       //set that cell to the valid number
            if(solve(puzzle)){                      //pass the updated puzzle to the function
                return true;                        //for the final case
            }                                       //if it does not lead to solution, try i++
        }
    }
    puzzle[position/9][position%9]=0;   //set tempered cells to 0 and return to the cell where we used a wrong valid input that does not lead to solution
    return false;                       //if the most recent cell has no valid inputs return false to return to the previous tampered cell
}

int main()
{

    int puzzle[9][9]={
    {9,4,8,6,0,0,3,0,1},
    {0,0,5,8,0,0,4,6,9},
    {6,0,0,5,4,0,2,0,0},
    {3,0,7,4,1,5,6,9,0},
    {0,0,0,0,6,3,8,0,0},
    {0,1,0,9,2,0,0,0,4},
    {0,0,0,3,9,0,0,0,8},
    {0,2,0,0,5,7,0,0,0},
    {1,0,0,2,0,4,0,0,0}
    };
    print(puzzle);

    if(solve(puzzle)){
        cout<<endl;
        print(puzzle);          //c++ passes array by reference, thus the original array is altered
    }
    else
        cout<<"not solvable"<<endl;
    return 0;
}

