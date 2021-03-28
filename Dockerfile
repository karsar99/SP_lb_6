FROM amazonlinux:latest
RUN yum update -y && yum install gcc-c++ -y
COPY ./nosynch.cpp ./nosynch.cpp
COPY ./synch.cpp ./synch.cpp
RUN g++ -pthread nosynch.cpp -o nosynch
RUN g++ -pthread synch.cpp -o synch

