//
//  binmatrix_stats.h
//  random_topology.cpp
//
//  Created by Bradley Morgan on 2/18/22.
//

#ifndef binmatrix_stats_h
#define binmatrix_stats_h

void matrix_out(std::vector<std::vector<int>> &matrix) {

    std::vector<std::vector<int>>::iterator row;
    
    std::string out;
    
    for(row = matrix.begin(); row != matrix.end(); row++) {
    
        std::vector<int>::iterator col;
    
        for(col = row->begin(); col != row->end(); ++col) {
            
            out += spin(*col);
            
        }
        
        delspin(out);
        
    }
    
}

void data_out(metadata &data) {
    
    data.mean = (data.sum * 1.0) / (data.size * 1.0);
    //data.variance += ((xy*1.0)-data.mean)*((xy*1.0)-data.mean);
    data.deviation = sqrt(data.variance);
    
    printf("\r\n====== RANDOM MATRICES SUMMARY ======\r\n\r\n");
    printf("matrix dimensions = %d\r\n", data.dim);
    printf("cell propability (sparsity) = %f\r\n", data.sparsity);
    printf("relative propagation (snd_cap) = %f\r\n", data.snd_cap);
    printf("relative saturation (rcv_cap) = %f\r\n", data.rec_cap);
    printf("max propagation (snd_max) = %d\r\n", data.snd_max);
    printf("max saturation (rcv_max) = %d\r\n", data.rec_max);
    printf("population size (mu) = %d\r\n\r\n", data.mu);
    printf("\r\n~~~~ STATISTICS ~~~~\r\n\r\n");
    printf("total channels = %d\r\n", data.sum);
    printf("mean = %f\r\n", data.mean);
    printf("variance = %f\r\n", data.variance);
    printf("deviation = %f\r\n", data.deviation);
    
}


#endif /* binmatrix_stats_h */
