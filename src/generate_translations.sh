#!/bin/bash
# this file is used to auto-generate .qm file from .ts file.
# author: shibowen at linuxdeepin.com

ts_list=(`ls ../src/translations/*.ts` `ls ../startup-apps/translations/*.ts` `ls ../file-shredder/translations/*.ts` `ls ../screen-checker/translations/*.ts`)

for ts in "${ts_list[@]}"
do
    printf "\nprocess ${ts}\n"
    lrelease "${ts}"
done
