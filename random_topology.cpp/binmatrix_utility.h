//
//  binmatrix_utility.h
//  random_topology.cpp
//
//  Created by Bradley Morgan on 2/17/22.
//

#ifndef binmatrix_utility_h
#define binmatrix_utility_h

void seed() {

    // seed the rng ...
    
    timeval time;
    gettimeofday(&time, NULL);
    unsigned int s = (unsigned int)(time.tv_sec * 1000) + time.tv_usec;
                            
    srand(s);
    
}

std::string spin(int value = 0) {
    
    int delay = 0.2;
    
    char buf[sizeof(value)];
    sprintf(buf, "[%d]", value);
    
    std::string out = buf;
    
    for(std::size_t c=0; c<sizeof(buf); c++) {
        std::cout << buf[c] << std::flush;
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

#endif /* binmatrix_utility_h */
