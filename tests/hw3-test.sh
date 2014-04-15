#!/bin/bash

export CFILE=$1

TMPWORKDIR=$(mktemp -d /tmp/hw3-test.XXXX)
export TMPWORKDIR
if [ ! -d $TMPWORKDIR ]; then
    echo "Temp Dir not found!"
    exit 1
fi
echo $TMPWORKDIR|grep '^/tmp/' >/dev/null
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "Something went wrong creating tmp dir!"
    exit 1
fi

export LOGFILE=$(mktemp "$TMPWORKDIR/log.XXXX")

export BINARY=$(mktemp $TMPWORKDIR"/hw3-XXXX")
export ERRORCOUNT=0

function runtest {
    TEST=$1
    if [ "$2" != "" ]; then
        MSG=$2
    else
        MSG=$1
    fi
    echo -n "[    ] $MSG"
    $TEST >/dev/null 2>&1
    STATUS=$?
    if [ ${STATUS} -ne 0 ]; then
        echo -e "\r[[31mFAIL[0m] $MSG - return status ${STATUS}"
        ERRORCOUNT=$(( $ERRORCOUNT + 1 ))
    else
        echo -e "\r[[32m OK [0m] $MSG"
    fi
}

function log {
    echo "$@" >> $LOGFILE
}

function compile {
    gcc -std=c99 -o $BINARY $CFILE  >> $LOGFILE 2>&1
    STATUS=$?
    return $STATUS
}

function mktestdir1 {
OUTDIR=$1
cat << EOF |base64 -d |tar -C $OUTDIR -zx 
H4sIACOGTVMAA+1ZbXPTRhDOV+tXLGEAKQjrxbJdYodpMgnTtCQwk9AOJUxGsU6xGumk0Z3i0JL/
3t072dhpgFJIDFPtOJbuvHe3u7p99OwlCiVrj1ZuVFyUXi+gq9fvuvNXEq/TcVc8v+N7fo8uK67n
9tzeCrg3a5aWSsiwBFiJ8ur0Y3qf+v07FWft88SANYjUnsE7ahwkWZEyKMr8tAwzkDlELMu5kCVq
gRwzUqoEgzwGMQp5TCpFWGJPyCHhRSUBlRN+2q5nhM1KjvNyHbYx5HAgQ56ytzCMMqFufzxjXLZZ
VD1RygDbuNA6eI7/2PEC6vuVlSLJOfa1XWx/njiGcTfho7SKGAyFjJK8PX4CjlPfQiJgMg4ljEOB
TidcxuhHpF0zDGxDFibctP4yWhUXySlnEYzGuMUyO7LfDoyW0dLDzNUXKQsxDOgOKyFUYQVzb8/Z
3nZevbLWYdUaGAZ56DiH4RmbquhoYegouhDnZQbTQbU2GURx/QM3t1LiVXaCQcExGPwOCIYPAKeq
1c/DMglPUiaMlnLDXL0XOeqzapvk0Zp1P5vdRbO7t+/tUy6ppZSJJ+HoDHK0oBJk6pwJtf6E6Yg9
iMiPuMwzpYT7pFx/H6Aj/iqvdHxYtA73XB+Nmn4d8VUbgwqRDcqQVslkVXJwB8alYSw7r74Xwe1z
tmT8d7u9LuE/foJ+v99V+I/qDf7fgjgKcvUuqPH3Z0INkWeYohrb2UVIV0E/IoqTsmlhYwEqK54g
RCJWXgOfV3CxSKJjCQViIXUnlLsFbNTzDlrGewD4iaVpjomu8juJTSjgzga4QLPMlH5jRw9KBpMw
kfQWabf1gFaLesz9l8+eUeuSpYLRMFzGhATXcwd4GUIXLw8f6ilnc+4ePdCINBonKaK7TNIUyopz
XGE6fUukjBVmVzUucYU5w7dzzuCewqhCuzSPTst+6HMynviPRMpvFAJU/gcf5n89n/Lf7/f8IOh2
+5j/nu81+X8r8l/43xixYYLJCnd9xIm0kki2voi7+Y7nfqvcjXq5Z3Pf5h2bBwo3FIlZ0Nh9sWnj
15YNe5sHv2ilOaa3oyhenJSCVMG8uLhoz/3VXG/Gvqr29IMU5z6ujl8+fXXoK7C0AbgmLsS94dAP
4B1wfzj0enTTGQ5/oGswMK6acFCdcCZhLxRnX8mK2t/PM0OwUY6B/4qh2Pq0DaRI7xCTAndfGW7B
xga1t2ZtC6aWbuVyDGEUlUwIJqZ0W4T0XlRRvKNfBDQtvVtmAw/HObbQt83Z4BDfT/vPDyH/0CRL
ez9IJuSy+Z/X0/gfUKOj+V+3wf9bkWvI2hwOwogq+UWo45hpptdRuWa9M5G1U7LhXaeLyWa96/UH
U3Cl/CUKxK0BzPY3fFP85/8ukjF/2ed/QeBerf+63U6T/7ch1/M/YmJ6Z9S8DhM6w/LqnEEoJcsK
iVfIsG90hhWRUqfjG55c0LjpaeD0RK8q6FQognNN7upTobhkYeTEkzKhkyiluMAer2eN/5IUOteV
oddUq8gOsSAEZYq2xLgbsTjB8u1wZ+d46+XTp8cHu7/vQOA+7s1xRLoJy9ORrQ/31tawcU7E0bh6
7ndSxfHrhbneEL9J/mRYBPMqo6VtupmUuWQIrh7+/HT32Q5V25XEDiphFZ1MEFLVqvAEPF2xao04
Lxg3yYTX3hsbVieKQ11qXjJfK9dHjqfqSSIhTRlHLnJnWtLWIE0WUDU7weKXmVMjcdG68p52bOhn
aJKLNpBLeWwueG/Zi2FELXwYXC0257LeBB+fZxYqnAG9/qIp6vHoo9GKRynyNVPF2lJh/kZL9RsR
zNabhv9P///H/8f5X9Bv8P9W5KP4/5Xgv0H17wzVFagfHG7v7h+TyfvPbdC4uuDwVQTWAIzDnr88
vDKunppOQhvQbqSRRhpppJFGGlmq/A0Wej2AACgAAA==
EOF
STATUS=$?
return $STATUS
}

function genrandout {
    /bin/dd if=/dev/urandom bs=16 count=2 2>>/dev/null | /usr/bin/sha1sum
}

function testoutput1 {

    TMPDIR1=$(mktemp -d "$TMPWORKDIR/tar.XXXX")
    mktestdir1 $TMPDIR1

    ORIGMD5=$(find $TMPDIR1 -type f|xargs cat|md5sum|awk '{print $1}')
    TESTMD5=$($BINARY $TMPDIR1|md5sum|awk '{print $1}')
    STATUS=$?
    if [ $STATUS -ne 0 ];then
        log "Failed to get MD5 checksum of output"
        return $STATUS
    fi
    if [ "$ORIGMD5" != "$TESTMD5" ]; then
        echo "Failed test 1"
        return 1
    fi
}

function testoutput2 {
    TMPDIR1=$(mktemp -d "$TMPWORKDIR/random.XXXX")
    for i in `seq 15`; do
        genrandout > $(mktemp "$TMPDIR1/$i.XXXXXX")
    done

    ORIGMD5=$(find $TMPDIR1 -type f|xargs cat|md5sum|awk '{print $1}')
    TESTMD5=$($BINARY $TMPDIR1|md5sum|awk '{print $1}')
    STATUS=$?
    if [ $STATUS -ne 0 ];then
        log "Failed to get MD5 checksum of output"
        return $STATUS
    fi
    if [ "$ORIGMD5" != "$TESTMD5" ]; then
        echo "Failed test 1"
        return 1
    fi
}

function checkbadargs {
    ERROR=0
    $BINARY  >> $LOGFILE 2>&1
    STATUS=$?
    if [ $STATUS -eq 0 ];then
        log "Your program didn't fail when no arguments were given!"
        ERROR=1
        ERRORCOUNT=$(( $ERRORCOUNT + 1 ))
    fi
    $BINARY /tmp /tmp >> $LOGFILE 2>&1
    STATUS=$?
    if [ $STATUS -eq 0 ];then
        log "Your program didn't fail when to many arguments were given!"
        ERROR=2
        ERRORCOUNT=$(( $ERRORCOUNT + 1 ))
    fi
    return $ERROR
}

function checkbaddir {
    ERROR=0
    $BINARY  /dev/null >> $LOGFILE 2>&1
    STATUS=$?
    if [ $STATUS -eq 0 ];then
        log "Your program didn't fail when a non directory was given as an argument!"
        ERROR=1
        ERRORCOUNT=$(( $ERRORCOUNT + 1 ))
    fi
    return $ERROR
}

runtest compile "Compile source code."
runtest checkbadargs "Checking if code fails with wrong args."
runtest checkbaddir "Checking if code fails if non-dir given."
runtest testoutput1 "Testing output part 1"
runtest testoutput2 "Testing output part 2"

if [ $ERRORCOUNT -gt 0 ]; then
    echo "Errors encountered, see logfile:"
    echo "################################"
    cat $LOGFILE
fi

echo "All done, cleaning up..."
rm -rf $TMPWORKDIR
