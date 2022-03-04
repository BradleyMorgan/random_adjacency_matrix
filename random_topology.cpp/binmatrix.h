//
//  random_binary_matrix.h
//  random_topology.cpp
//
//  Created by Bradley Morgan on 2/16/22.
//

#ifndef random_binary_matrix_h
#define random_binary_matrix_h

#include<map>

#include "binmatrix_utility.h"
#include "binmatrix_datatypes.h"
#include "binmatrix_stats.h"

std::map<std::pair<int,int>,int> get_col(std::vector<std::vector<int>> &matrix, int col) {
    
    std::map<std::pair<int,int>,int> cells;
    
    for (int row=0; row<matrix.size(); row++) {
        
        std::pair<int,int> cell = { row, col };
        
        cells[cell] = matrix[row][col];
        
    }
    
    return cells;
    
}

std::map<std::pair<int,int>,int> get_row(std::vector<std::vector<int>> &matrix, int row) {
    
    std::map<std::pair<int,int>,int> cells;
    
    for (int col=0; col<matrix.size(); col++) {
        
        std::pair<int,int> cell = { row, col };
        
        cells[cell] = matrix[row][col];
        
    }
    
    return cells;
    
}

int senders(std::vector<std::vector<int>> &matrix, int node) {

    std::map<std::pair<int,int>,int> row = get_col(matrix, node);
    
    int senders = std::accumulate(matrix[node].begin(), matrix[node].end(), 0);
    
    return senders;
    
}

int receivers(std::vector<std::vector<int>> &matrix, int node) {

    std::map<std::pair<int,int>,int> col = get_row(matrix, node);
    
    int receivers = std::accumulate(matrix[node].begin(), matrix[node].end(), 0);
    
    return receivers;
    
}

// less obfuscated count of nonzero matrix elements
// leaving here as a sanity check

int channel_check(std::vector<std::vector<int>> &matrix) {
    
    int channels = 0;
    
    std::vector<std::vector<int>>::iterator row;
    
    for(row = matrix.begin(); row != matrix.end(); ++row) {
        std::vector<int>::iterator column;
        for(column = row->begin(); column != row->end(); ++column) {
            if(*column == 1) { channels++; }
        }
    }
    
    return channels;
    
}

int channels(std::vector<std::vector<int>> &matrix, bool check = false) {
    
    if(check) { return channel_check(matrix); }
    
    return std::accumulate(matrix.begin(), matrix.end(), 0, [](size_t sum, std::vector<int> const &row) {
        return sum + (std::accumulate(row.begin(), row.end(), 0));
    });
        
}

#endif /* random_binary_matrix_h */
