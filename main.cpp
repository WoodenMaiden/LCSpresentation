#include <iostream> //cout, cerr 
#include <iomanip> //setw, setfill
#include <string> //string
#include <vector> //vector

#define str std::string 
#define mat std::vector<std::vector<unsigned>>

void promptMatrix (mat m) {
    const std::string DELIMITER(8*m[0].size() + 1 , '-'); 
    std::cout << DELIMITER << std::endl; 
    for(unsigned y = 0; y < m.size(); ++y) {
        std::cout << '|';
        for (unsigned x = 0; x < m[y].size(); ++x)
            std::cout << std::setw(6) << m[y][x] << '\t' << '|';
        std::cout << std::endl << DELIMITER <<std::endl; 
    }
}

mat LCSLength(str seq1, str seq2) {
    //constructing matrix
    mat C(seq1.size() + 1, std::vector<unsigned>(seq2.size() +1 , 0));

    //for each letters of seq1...
    for (unsigned y = 1; y < C.size(); ++y)
        //we look at all the letters of seq2 
        for (unsigned x = 1; x < C[0].size(); ++x)
            //if both letters are the same the current common subsequence grows            
            if (seq1[y - 1] == seq2 [x - 1])C[y][x] = C[y-1][x-1] + 1;      
            //else it gets the max length between top
            else C[y][x] = (C[y][x - 1] > C[y -1][x]) ? C[y][x - 1] : C[y -1][x]; 

    return C;

}


str backtrackRec(const mat C, const str row, const str column, unsigned y, unsigned x) {
    //stop condition : if we are on the upper edge of the matrix
    if (x == 0 || y == 0) return "";
    //if the letters are the same we go one case to the left and we concatenate the letter
    if (row[y - 1] == column[x - 1]) 
        return backtrackRec(C, row, column, y -1, x - 1) + row[x -1];
    //if the left value is higher than the upper one go left
    if (C[y][x - 1] > C[y - 1][x]) 
        return backtrackRec(C, row, column, y, x - 1);
    //go up by default
    return backtrackRec(C, row, column, y - 1, x); 
}

str backtrack(const mat C, const str row, const str column) {
    //the matrix will form a path that will go fromm the upper left to the down left
    //we will go through this path from down to up and from right to left
    return backtrackRec(C, row, column, C.size() - 1, C[0].size() - 1);
}


str LCS(str seq1, str seq2) {
    mat C = LCSLength(seq1, seq2);
    promptMatrix(C);
    return backtrack(C, seq1, seq2);
}



int main (int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "\33[0;31m Please provide only two strings to compare : row column\33[0m" << std::endl;
        return -1;
    }    

    str sequence1(argv[1]);
    str sequence2(argv[2]);

    std::cout << LCS(sequence1, sequence2) << std::endl;

    //backtrack doesn't work, i might have mixed up variables names, howerver i still understood how it works!
}