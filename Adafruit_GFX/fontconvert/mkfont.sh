#! /bin/sh

FONT=$1

for SiZ in `seq 8 12`
do
  ./fontconvert $FONT.ttf $SiZ > "$FONT$SiZ"pt7b.h
  echo "$FONT$SiZ"pt7b.h
  sleep 1.01
done

# echo "sh mkfont.sh Ubuntu"

