//
//  binmatrix.cpp
//  random_binary_matrix
//
//  Created by Bradley Morgan on 2/7/22.
//
//       x
//    y [0][0][0][0]..[n]
//      [0][0][0][0]..[0]
//      [0][1][0][0]..[0]
//      [0][0][0][1]..[0]
//      ...
//      [n][0][1][0]..[0]
//


#include <iostream>
#include <random>
#include <array>
#include <cmath>
#include <numeric>
#include <thread>
#include <algorithm>
#include <sys/time.h>
#include <ctime>
#include <string.h>

#include "binmatrix.h"

// single random x,y coordinate in n*n matrix

std::pair<int, int> rnd_cell(metadata &data) {
    
    std::pair<int,int> cell = { 0, 0 };
    
    while(cell.first == cell.second) {
        
        cell = { rand()%data.dim, rand()%data.dim };
    
    }
        
    return cell;
    
}

// set of random x,y coordinates in n*n dimensional array
// map datatype ensures cell[x,y] is unique
// set of dim random x,y coordinates

std::map<std::map<int,int>,int> rnd_cells(metadata &data) {
    
    std::map<std::map<int,int>,int> cells;
    
    while(cells.size() < data.size * data.sparsity) {

        std::map<int,int> cell({ rnd_cell(data) });

        if(data.metrics.cells[cell] < data.snd_max && data.metrics.cells[cell] < data.rec_max) {
            
            cells[cell] = 0;
            
            data.metrics.cells[cell]++;
            
        }

    }

    return cells;
    
}

// set of n binary values indexed by x,y

std::vector<std::vector<int>> rnd_rows(metadata &data) {
    
    std::vector<std::vector<int>> rows(data.dim, std::vector<int>(data.dim));
    
    std::map<std::map<int,int>,int> cells = rnd_cells(data);
    
    for(std::map<std::map<int,int>,int>::iterator cell = cells.begin(); cell != cells.end(); ++cell) {
        
        std::map<int,int> keys({ cell->first });
        
        for(std::map<int,int>::iterator key = keys.begin(); key != keys.end(); ++key) {
        
            rows[key->first][key->second] = 1;
            
            printf("[%d][%d]=%d\n", key->first, key->second, rows[key->first][key->second]);
            
        }
        
    }
    
    // n*n dimensional array of x,y indexed random binary values
    
    return rows;
    
}

std::vector<std::vector<int>> rnd_matrix(metadata &data) {
    
    std::vector<std::vector<int>> matrix = rnd_rows(data);
    
    return matrix;
    
}
 
int main(int argc, const char *argv[]) {
    
    seed();
    
    metadata data(argv);
    
    std::vector<std::vector<int>> matrix = rnd_matrix(data);
    
    matrix_out(matrix);
    data_out(data);

}
