#!/bin/bash


outdir="ornl2016_`date +%d%b%y_%H%M.%S`"
mkdir $outdir
cd $outdir

~/paass/install/bin/utkscan -i /scratch3/ornl2016_vandle/micronet3/pixie16/ornl2016/ldf/rb/097rb_02.ldf --frequency 250 -f R34300 -c ~/paass/install/share/utkscan/cfgs/ornl/Vandle2016/analysis/Config-2TdelayTest.xml -o tmp 

cd -
