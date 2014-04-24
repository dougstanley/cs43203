/* file_exists.c
 *
 * Using stat to determine if a file exists.
 * Need a stat stuct to pass to stat()
 * otherwise it will always return failure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    int ret = 0;
    struct stat st;

    //See if / exists (it should ALWAYS exist)
    ret = stat("/",&st);
    if( ret == 0 ){
        fprintf(stderr,"/ exists! Stat returned: %d\n",ret);
    }else{
        fprintf(stderr,"/ doesn't exist! Stat returned: %d\n",ret);
    }

    //now see what happens for something that probably doesn't exist
    ret = stat("/foo/blah/21sds2sf34",&st);
    if( ret == 0 ){
        fprintf(stderr,"/foo/blah/21sds2sf34 exists! Stat returned: %d\n",ret);
    }else{
        fprintf(stderr,"/foo/blah/21sds2sf34 doesn't exist! Stat returned: %d\n",ret);
    }

    return 0;
}
