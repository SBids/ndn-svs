#!/usr/bin/env bash
set -ex

PROJ=ndn-svs

sudo rm -fr /usr/local/include/"$PROJ"
sudo rm -f /usr/local/lib{,64}/lib"$PROJ"*
sudo rm -f /usr/local/lib{,64}/pkgconfig/{,lib}"$PROJ".pc
