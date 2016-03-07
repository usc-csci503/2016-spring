#!/bin/sh

SETUP=/share/setup
HADOOP=hadoop-1.2.1
MODE=$1

echo "[i] Setting up hadoop dependencies"

if [ -z "$MODE" ]; then
  echo "usage: $0 <one-node|cluster>"
  exit
fi

## install dependencies
yum -q -y install openssl-devel
yum -q -y install java-1.7.0-openjdk-devel

## install hadoop
export LIB=-lcrypto
curl --silent --output /tmp/hadoop.tar.gz \
  https://archive.apache.org/dist/hadoop/common/${HADOOP}/${HADOOP}.tar.gz
tar -zxf /tmp/hadoop.tar.gz -C /opt
( cd /opt/${HADOOP}/src/c++/utils ; sh configure ; make install )
( cd /opt/${HADOOP}/src/c++/pipes ; sh configure ; make install )
chown -R vagrant /opt/${HADOOP}

mkdir -p /app/hadoop/tmp
chown -R vagrant /app/hadoop/tmp
chmod 750 /app/hadoop/tmp

cp /vagrant/${MODE}/* /opt/${HADOOP}/conf/

## set profiles
install -m 644 -o root ${SETUP}/profile.d/hadoop.sh /etc/profile.d/hadoop.sh
install -m 644 -o root ${SETUP}/profile.d/java.sh /etc/profile.d/java.sh
