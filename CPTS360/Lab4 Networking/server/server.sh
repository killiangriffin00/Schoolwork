#! /bin/bash
sudo lsof -t -i:1234
gcc server.c -o server
./server