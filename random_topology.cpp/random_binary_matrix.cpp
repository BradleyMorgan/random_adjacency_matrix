//
//  main.cpp
//  random_topology.cpp
//
//  Created by Bradley Morgan on 2/7/22.
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

#include "random_binary_matrix.h"

// single random x,y coordinate in n*n matrix

std::pair<int, int> rnd_cell(metadata &data) {
    
    std::pair<int,int> cell = { rand()%data.dim, rand()%data.dim };
        
    return cell;
    
}

// set of random x,y coordinates in n*n dimensional array

std::vector<std::map<int,int>> rnd_cells(metadata &data) {
    
    std::vector<std::map<int,int>> cells;
    
    for(int x=0; x<(data.dim*data.dim); x++) {
    
        std::map<int,int> cell = { rnd_cell(data) };
        
        if(rand()/(RAND_MAX+1.0) < data.sparsity) {
        
            if(data.counts.channels[cell] < data.snd_max && data.counts.channels[cell] < data.rec_max) {
            
                cells.push_back(cell);
                
                data.counts.channels[cell]++;

            }
            
        }
        
    }
    
    // set of dim random x,y coordinates
    
    return cells;
    
}

// set of n binary values indexed by x,y

std::vector<std::vector<int>> rnd_rows(metadata &data) {
    
    std::vector<std::vector<int>> rows(data.dim, std::vector<int>(data.dim));
    std::vector<std::map<int,int>> cells = rnd_cells(data);
    
    for(std::vector<std::map<int,int>>::iterator x = cells.begin(); x != cells.end(); ++x) {
    
        for(std::map<int,int>::iterator y = x->begin(); y != x->end(); ++y) {
            
            rows[y->first][y->second] = 1;
            
        }
        
    }
    
    // n*n dimensional array of x,y indexed random binary values
    
    return rows;
    
}

/*-----------------------------------------------------------
     x
  y [0][0][0][0]..[n]
    [0][0][0][0]..[0]
    [0][1][0][0]..[0]
    [0][0][0][1]..[0]
     .
    [n][0][1][0]..[0]
 
-----------------------------------------------------------*/
 
std::vector<std::vector<int>> rnd_matrix(metadata &data) {
    
    std::vector<std::vector<int>> matrix = rnd_rows(data);
    
    return matrix;
    
}
 
int main(int argc, const char *argv[]) {
    
    metadata data(argv);
    
    std::vector<std::vector<int>> matrix = rnd_matrix(data);
    
    matrix_out(matrix);
    data_out(data);

}
