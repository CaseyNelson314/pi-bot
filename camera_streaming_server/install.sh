#!/bin/bash

set -e

curl -OL https://github.com/shiguredo/momo/releases/download/2024.1.2/momo-2024.1.2_raspberry-pi-os_armv8.tar.gz
tar -xvf momo-2024.1.2_raspberry-pi-os_armv8.tar.gz
rm -rf momo-2024.1.2_raspberry-pi-os_armv8.tar.gz

chmod +x ./momo/momo

