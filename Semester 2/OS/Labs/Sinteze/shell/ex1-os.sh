if [ -z $1 ]; then
    echo no params given
fi
    
while true; do
    if [ -z $1 ]; then
        break 
    fi  
    if [ ! -d $1 ]; then
        echo not dir or not existing $1
        shift
        continue
    fi
    
    echo Director $1
    ex=0
    for f in `find $1 -type f`; do
        if [ -x $f ]; then
            $ex=`expr $ex+1`
        fi
    done
    neex=0
    for f in `find $1 -type f`; do
        if [ ! -x $f ]; then
            $neex=`expr $neex+1`
        fi
    done
    direc=0
    for d in `find $1 -type d`; do
        $direc=`expr $direc+1`
    done
    echo "    - fisiere executabile: $ex"
    echo "    - fisiere ne-executabile: $neex"
    echo "    - directoare: $direc"
    
    shift
done
