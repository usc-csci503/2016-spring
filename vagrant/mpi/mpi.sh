#!/bin/sh

echo "[i] Setting up MPI dependencies"

SETUP=/share/setup

## install dependencies
yum -q -y install mpich
yum -q -y install mpich-devel

## set profiles
install -m 644 -o root ${SETUP}/profile.d/mpich.sh /etc/profile.d/mpich.sh
