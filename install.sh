#!/bin/sh

g++ ./ideaTweak.cpp -o ./ideaTweak
mv ./ideaTweak /usr/local/bin/
chown root.root /usr/local/bin/ideaTweak
chmod 4755 /usr/local/bin/ideaTweak