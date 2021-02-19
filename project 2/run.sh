#!/bin/bash
echo "tester start"
./enter_queue &
sleep 1
./enter_queue &
sleep 1
./enter_queue &
./clean_queue &