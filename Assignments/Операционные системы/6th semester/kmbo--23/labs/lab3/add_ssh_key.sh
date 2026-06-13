#!/usr/bin/env sh

cat | ssh -i "$1" \
          -o PasswordAuthentication=no \
          -o PubkeyAuthentication=yes \
          -o BatchMode=yes \
          "$2" "cat >> ~/.ssh/authorized_keys"
