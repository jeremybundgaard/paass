
#!/bin/bash


array=( "$@" )
arraylength=${#array[@]}
for (( i=1; i<${arraylength}+1; i++ ));
do
  if [[ "${array[$i-1]}" = "-c" ]]; then
		config="${array[$i]}"
		echo "config:  $config"
	fi
  if [[ "${array[$i-1]}" = "-i" ]]; then
		infile="${array[$i]}"
		echo "infile:  $infile"
	fi
done


ldf=`basename $infile .ldf`
outdir=${ldf}_date_`date +%d%b%y_%H%M.%S`
mkdir $outdir
cd $outdir

echo "~/paass/install/bin/utkscan -i $infile --frequency 250 -f R34300 -c $config -o $ldf -b"
~/paass/install/bin/utkscan -i $infile --frequency 250 -f R34300 -c $config -o $ldf -b

cd -
