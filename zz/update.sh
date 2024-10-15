#!/bin/sh

   #******************************************
   # echo "# pid_controller" >> README.md
   git init
   git status
   git add .
   git commit -m "$(date "+%Y-%m-%d")"
   git remote add origin git@github.com:Alex2269/pid_controller.git
   git push -u origin main
   git pull
   #******************************************

   #******************************************
   видалення останніх комітів:
   # git reset HEAD^    --hard
   #
   git reset  origin    --hard
   git reset  HEAD~1    --hard
   git reset  HEAD~1    --hard
   git reset  HEAD~1    --hard
   git push origin HEAD --force
   #******************************************

   #******************************************
   оновлення та полсилання файлів на сховищє:
   #
   git status
   git add .
   git commit -m "$(date "+%Y-%m-%d")"
   git push -u origin main
   git pull
   #******************************************

