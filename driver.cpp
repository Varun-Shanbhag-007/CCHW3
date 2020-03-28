#include<stdio.h>
#include<iostream>
#include <chrono>
#include <cstring>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include<string.h>
#include<sstream>
using namespace std;
using namespace std::chrono;

void write(int files, int record);

void read(int files, int record);

struct thread_data {
   int id;
   long long int rec;
   long long int fileSize;
};


void *WriteHelper(void *threadarg) {
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    cout << "id : " << my_data->id;
    cout << "Record : " << my_data->rec ;
    cout << "fileSize : "<< my_data->fileSize;
   
    int threadid = my_data->id;
    long long int size = my_data->fileSize;
    long long int recordSize = my_data->rec;
    
    stringstream temp_str;
    temp_str<<(threadid);
    string str = temp_str.str();
    const char* cstr2 = str.c_str();
  
    char *buf1 = (char *)malloc(recordSize*sizeof(char));
    void *buffer;

    long long int i =0;

    for(i =0;i<recordSize;i++){

            buf1[i] = 'a';
    }

    buf1[i] = '\0';

    posix_memalign(&buffer,recordSize,recordSize);

    memcpy(buffer, buf1,recordSize*sizeof(char));

    long long int hops=size/recordSize; //10GB/1M for 1 thread

    int fileDescriptor = open(cstr2, O_CREAT|O_TRUNC|O_DIRECT|O_WRONLY, S_IRWXU);
    
    auto start = high_resolution_clock::now();

    for(int i = 0; i < hops ;i++){
       write(fileDescriptor, buffer, recordSize);
    }

    auto stop = high_resolution_clock::now();
    
    close(fileDescriptor);
    free(buffer);
    free(buf1);
    
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "--Time taken by function: "
         << duration.count() << " microseconds" << endl;

    pthread_exit(NULL);
}

void *ReadHelper(void *threadarg) {
  struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    cout << "id : " << my_data->id;
    cout << "Record : " << my_data->rec ;
    cout << "fileSize : "<< my_data->fileSize;

    int threadid = my_data->id;
    long long int size = my_data->fileSize;
    long long int recordSize = my_data->rec;

    stringstream temp_str;
    temp_str<<(threadid);
    string str = temp_str.str();
    const char* cstr2 = str.c_str();

    void *buffer;

    posix_memalign(&buffer,recordSize,recordSize);

    long long int hops=size/recordSize; //10GB/1M for 1 thread

    int fileDescriptor = open(cstr2,O_DIRECT|O_RDONLY, S_IRWXU);

    auto start = high_resolution_clock::now();

    for(int i = 0; i < hops ;i++){
       read(fileDescriptor, buffer, recordSize);
    }

    auto stop = high_resolution_clock::now();

    close(fileDescriptor);
    free(buffer);
    
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "--Time taken by function: "
         << duration.count() << " microseconds" << endl;
}


int main(int argc, char *argv[])
{
    char *accessPattern = argv[1];
    if (strcmp(accessPattern, "W") == 0)
    {
        cout<<"Write Method Call"<<"\n";
        write(atoi(argv[2]),atoi(argv[3]));    
    }
    else if (strcmp(accessPattern, "R") == 0)
    {
        cout<<"Read Method Call"<<"\n";
        read(atoi(argv[2]),atoi(argv[3]));
    }

     return(0);
}

void write(int files, int record) 
{   
   //put this value below prior too submission : 10485760000	
   long long tenGb = 10485760000;   
   long long fileSize = tenGb/files;   
    
   pthread_t threads[files];
    
   struct thread_data td[files];
   int rc;
   int i;   
   for( i = 0; i < files; i++ ) {
      td[i].id = i;
      td[i].rec = record;
      td[i].fileSize = fileSize;
      rc = pthread_create(&threads[i], NULL, WriteHelper, (void *)&td[i]);      
      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}

void read(int files, int record)
{
   //put this value below prior too submission : 10485760000    
   long long int tenGb = 10485760000;
   long long int fileSize = tenGb/files;

   pthread_t threads[files];

   struct thread_data td[files];
   int rc;
   int i;
   for( i = 0; i < files; i++ ) {
      td[i].id = i;
      td[i].rec = record;
      td[i].fileSize = fileSize;
      rc = pthread_create(&threads[i], NULL, ReadHelper, (void *)&td[i]);
      if (rc) {
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}









