//
//  binmatrix_datatypes.h
//  random_topology.cpp
//
//  Created by Bradley Morgan on 2/18/22.
//

#ifndef binmatrix_datatypes_h
#define binmatrix_datatypes_h

struct stats {
    
    int sum = 0;
    int sum_send = 0;
    int sum_recv = 0;
    
    std::map<std::map<int,int>,int> cells;
    
};

struct metadata {

    int mu = 0;
    int dim = 0;
    int snd_max = 0;
    int rec_max = 0;
    int sum = 0;
    int range = 0;
    int mode = 0;
    int size = 0;
    
    double snd_cap = 0.0;
    double rec_cap = 0.0;
    double sparsity = 0.0;
    double mean = 0.0;
    double variance = 0.0;
    double deviation = 0.0;
    
    stats metrics;
    
    metadata(const char *argv[]) {
        
        this->mu = std::stoi(argv[1]);
        this->dim = std::stoi(argv[2]);
        this->size = this->dim * this->dim;
        
        this->snd_cap = std::stod(argv[3]);
        this->rec_cap = std::stod(argv[4]);
        this->snd_max = std::round((size * 1.0) * snd_cap);
        this->rec_max = std::round((size * 1.0) * rec_cap);
        this->sparsity = std::stod(argv[5]);
        
    }
    
};

#endif /* binmatrix_datatypes_h */
