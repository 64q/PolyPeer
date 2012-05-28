#!/bin/bash
valgrind -v --tool=memcheck --leak-check=yes  --show-reachable=yes --log-file="carnage.txt" ./polypeer

