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

std::string spin(int value = 0) {
    
    // char spinner[] = {'/', '-', '\\', '|'};
    
    int delay = 5;
    
    char buf[sizeof(value)];
    
    sprintf(buf, "[%d]", value);
    
    std::string out = buf;
    
    for(std::size_t c=0; c<sizeof(buf); c++) {
        
        std::cout << buf[c] << std::flush;
        
        //  for(std::size_t i = 0; i < sizeof(spinner); i++) {
        //      printf("%c", spinner[i]);
        //      std::cout << spinner[i] << std::flush;
        //  }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        
    }
    
    return out;

}

void delspin(std::string &out) {

    for(std::size_t c=0; c<sizeof(out); c++) {
        
        // animation placeholder
        
    }
    
    std::cout << "\n" << std::flush;
    
}

int main(int argc, const char * argv[]) {

    int mu = std::stoi(argv[1]);
    int dim = std::stoi(argv[2]);

    double snd_cap = std::stod(argv[3]);
    double rec_cap = std::stod(argv[4]);
    double sparsity = std::stod(argv[5]);

    int snd_max = std::round((dim * 1.0) * snd_cap);
    int rec_max = std::round((dim * 1.0) * rec_cap);
    
    std::vector<int> channel_counts;
    
    for(int t=0; t<mu; t++) {

        printf("\r\n------ MATRIX %d -------\r\n", t);
        
        std::vector<std::vector<int>> matrix;
        matrix.resize(dim);

        int snd = 0;
        int rec = 0;
        int nchan = 0;
        
        int nsnd[dim];
        int nrec[dim];

        //printf("%d => ", t);
        
        for(int i=0; i<dim; i++) {
            nsnd[i] = 0;
            nrec[i] = 0;
            matrix[i].resize(dim);
        }
        
        while(nchan < (dim / 3)) {
            
            std::string out;
            
            for(int row=0; row<dim; row++) {
                         
                snd = rand()%(dim-1);

                while(nsnd[snd] >= snd_max) {
                    snd = rand()%(dim-1);
                }

                for (int col=0; col<dim; col++) {
                    
                    while (snd == rec) {

                        rec = rand()%(dim-1);

                        while(nrec[rec] >= rec_max) {
                            rec = rand()%(dim-1);
                        }

                    }

                }

                if(rand()/(RAND_MAX+1.0) < sparsity) {

                    matrix[snd][rec] = 1;
                    nsnd[snd]++;
                    nrec[rec]++;

                    nchan++;
                    
                    
                }
                
                out += spin(matrix[snd][rec]);
                
            }
            
            delspin(out);
            
        }
        
        channel_counts.push_back(nchan);
        
        printf("---- %d | %d senders | %d receivers | %d total ----\r\n", t, nsnd[snd], nrec[rec], nchan);
        
    }
    
    printf("\r\n====== RANDOM MATRICES SUMMARY ======\r\n\r\n");
    
    printf("matrix dimensions = %d", dim);
    printf("cell propability (sparsity) = %d\r\n", mu);
    printf("relative propagation (snd_cap) = %f\r\n", snd_cap);
    printf("relative saturation (rcv_cap) = %f\r\n", rec_cap);
    printf("max propagation (snd_max) = %d\r\n", snd_max);
    printf("max saturation (rcv_max) = %d\r\n", rec_max);
    printf("population size (mu) = %d\r\n\r\n", mu);
    
    printf("\r\n~~~~ STATISTICS ~~~~\r\n\r\n");
    
    int tchan = std::accumulate(channel_counts.begin(), channel_counts.end(), 0);
    
    double mean = (tchan * 1.0) / (mu * 1.0);
    double variance = 0.0;

    for(int n = 0; n<mu; n++) {
        variance += ((channel_counts[n] * 1.0) - mean) * ((channel_counts[n] * 1.0) - mean);
        
    }

    variance /= mu;

    double std_dev = sqrt(variance);

    printf("total channels = %d\r\n", tchan);
    printf("average channels (mean) = %f\r\n", mean);
    printf("variance = %f\r\n", variance);
    printf("standard deviation = %f\r\n", std_dev);

}
