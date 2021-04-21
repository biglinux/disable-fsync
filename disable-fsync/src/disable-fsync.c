/*
 * 
 *  nosync - crazy preload to disable sync() function call
 *  for days when we just don't want to sync() (similar to
 *  nohup, just more sync than HUP).
 * 
 *  These libc functions are trapped in dynamically linked 
 *  executables and stripped of their sync features:
 * 
 *   sync
 *   fdatasync
 *   fsync
 * 
 *  compile with gcc, or use the attached wrapper:
 *
 *    gcc -Wall -fPIC -shared -o nosync-browser.so nosync-browser.c -lc -ldl
 * 
 *   (c) 2011 
 *   Licence: GNU Public Licence version 2 or above
 */




void sync(void)
{
    return;
}

int fsync(int fd)
{
    return 0;
}

int fdatasync(int fd)
{
    return 0;
}




