FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install -y make

RUN apt-get install -y cmake

RUN apt-get install -y clang

RUN apt-get install -y g++

RUN apt-get install -y libboost-all-dev

COPY ./ /irc

WORKDIR /irc/src

RUN make re

CMD ./ircserv 6667 1234
