#!/bin/bash -xe

echo "$WORKSPACE"
cp -r "$WORKSPACE/src" "/mnt/tmp/"

sudo /usr/sbin/chroot /mnt <<EOF
    export LANGUAGE=en_GB.UTF-8
    export LC_ALL=en_GB.UTF-8
    export LC_CTYPE=en_GB.UTF-8
    apt-get update
    apt-get install -y autotools-dev intltool libglib2.0-dev
    cd /tmp/src
    ./autogen.sh
    ./configure --sysconfdir=/etc
    /usr/bin/make -j4
    /usr/bin/strip --strip-all lxde-pt-shutdown-helper
    cp lxde-pt-shutdown-helper /tmp
EOF