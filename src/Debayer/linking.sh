#!/usr/bin/sh
dir_path="/Debayer/libs"
cd /etc/ld.so.conf.d/ || exit
echo "$dir_path">debayer.conf
ldconfig