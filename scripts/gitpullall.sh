#!/bin/bash
for branch in `git branch -a | grep remotes | grep -v HEAD`; do
    branchaux=${branch##*refs};
    if [ ${branchaux##*/} != $branchaux ]; then
      echo "-----------------------------------------------------------------";
      echo "-- ${branchaux##*/}";
      echo "-----------------------------------------------------------------";
      git branch --track ${branchaux##*/} $branchaux;
      git pull origin ${branchaux##*/};
      echo "  ";
    fi
done

exit
