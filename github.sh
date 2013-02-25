#/bin/bash

clear
echo "Github"
read -p "Push to: " target
read -p "Commit message: " commitMsg
git add .
git commit -m "${commitMsg}"
git push $target master
