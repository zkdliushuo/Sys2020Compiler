#!/bin/bash
for file in ./*
do
    if [ "${file##*.}"x != "sy"x ]; then
        if [ "${file##*.}"x != "in"x ]; then
            if [ "${file##*.}"x != "out"x ];then
                if [ "${file##*.}"x != "sh"x ];then
                    if [ "${file##*.}"x != "ll"x ];then
                        if [ "${file##*.}"x != "s"x ];then
                                rm $file;
                        fi
                    fi
                fi
            fi
        fi
    fi
done
