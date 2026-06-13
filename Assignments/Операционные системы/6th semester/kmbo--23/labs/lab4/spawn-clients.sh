#!/bin/sh

for i in {1..5}; do
    ./sockets-nb client unix ./socket.sock &
done
