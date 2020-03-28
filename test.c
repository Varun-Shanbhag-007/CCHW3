#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define BLOCKSIZE 1024*1024

int main (void)
{
    // cout<<getpagesize();

    
    long long int record_size = 1024*1024;

    void *buffer;
    
    //cout<<buf1<<endl;
    
    // char *buffer = (char *)malloc(16*1024*1024*sizeof(char));

    //cout<<buffer<<endl<<sizeof(buffer)<<endl;
    
    posix_memalign(&buffer, BLOCKSIZE, BLOCKSIZE);
	
    cout<<buffer<<endl<<sizeof(buffer)<<endl;

    int a = open("0", O_DIRECT|O_RDONLY, S_IRWXU);

    auto start = high_resolution_clock::now();
    for(int i =0;i<10240;i++){

    int error = read(a, buffer, BLOCKSIZE);
    //  cout<<error;
    }

    auto stop = high_resolution_clock::now();


    close(a);
    free(buffer);

    auto duration = duration_cast<seconds>(stop - start);
     cout << "--Time taken by function: "<<duration.count();

    return 0;
}
