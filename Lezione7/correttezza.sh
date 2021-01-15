#!/bin/bash

for i in $(seq 0 ${2})
do
	./${1} < Test/input${i}.txt | diff - Test/output${i}.txt
done
