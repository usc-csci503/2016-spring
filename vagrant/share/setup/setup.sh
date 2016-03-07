#!/bin/sh

echo "[i] Setting up system configuration"

SETUP=/share/setup

## setup keys
install -m 600 -o vagrant ${SETUP}/ssh/id_rsa ~vagrant/.ssh/id_rsa
install -m 600 -o vagrant ${SETUP}/ssh/config ~vagrant/.ssh/config
cat ${SETUP}/ssh/id_rsa.pub >> ~vagrant/.ssh/authorized_keys

## update etc
install -m 644 -o root ${SETUP}/etc/hosts /etc/hosts
