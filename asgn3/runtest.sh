# Usage:    sh runtest.sh "list of numbers"
# Example:  sh runtest.sh "314 76 95064"

# Check that two command-line arguments are given.
if [ "$1" = "" ] || [ "$2" = "" ]
then
    echo 'Usage:    sh runtest.sh num_players seed'
    echo 'Example:  sh runtest.sh 3 784'
else
    # Automatically determine which binaries to run.
    KERNEL=`uname -r | sed -e 's/.*-//'`
    MACHINE=`uname -m`

    if [ $KERNEL = 'azure' ]
    then
        EXEC='../../resources/asgn3/lcr_hub'
    else
        if [ $MACHINE = 'aarch64' ]
        then
            EXEC='../../resources/asgn3/lcr_arm'
        else
            EXEC='../../resources/asgn3/lcr_x86'
        fi
    fi

    # Confirm that the executable file is where we expect it to be.
    if ! [ -f $EXEC ]
    then
        echo "Can't find reference program $EXEC"
    else
        # Run the executables.
        printf "%d\n%d\n" $1 $2 | $EXEC > expected.txt
        printf "%d\n%d\n" $1 $2 | ./lcr > got.txt

        # Print any difference.
        # The diff -s option reports when the files are identical.
        diff -s expected.txt got.txt
    fi
fi

