
#    __  __         _____  _     _      ____                  _       _____                _                  # 
#   |  \/  |       |  __ \(_)   | |    |  _ \                | |     |  __ \              | |                 #
#   | \  / |_   _  | |  | |_ ___| | __ | |_) | ___ _ __   ___| |__   | |__) |___  __ _  __| |_ __ ___   ___   #
#   | |\/| | | | | | |  | | / __| |/ / |  _ < / _ \ '_ \ / __| '_ \  |  _  // _ \/ _` |/ _` | '_ ` _ \ / _ \  #
#   | |  | | |_| | | |__| | \__ \   <  | |_) |  __/ | | | (__| | | | | | \ \  __/ (_| | (_| | | | | | |  __/  #
#   |_|  |_|\__, | |_____/|_|___/_|\_\ |____/ \___|_| |_|\___|_| |_| |_|  \_\___|\__,_|\__,_|_| |_| |_|\___|  #
#            __/ |                                                                                            #
#           |___/                                                                                             #



This is a tool to calculate R/W speed of a given drive HDD/SSD

Its pretty simple to use it

Pre-Requisite:
###############################################################
g++ compiler
pthread library

Steps to Run
##############################################################
execute command 
`make`  //This will clean and compile the cpp code

To run the program use following options:

./benchmark <W/WR/R/RR> <# of Threads> <RecordSize in bytes>


Example:

./benchmark W 1 1024


Note: Benchmark program will read/write 10g of data on to disk
Please use write prior to read

