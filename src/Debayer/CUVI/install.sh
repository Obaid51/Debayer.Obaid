#!/bin/sh

cp -a lib/. /usr/local/lib 
cp -a include/. /usr/local/include

ldconfig

echo "Cuvi Installed!"
