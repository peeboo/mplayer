
#ifndef HAVE_NO_POSIX_SELECT

// keyboard:
static int keyb_fifo_put=-1;
static int keyb_fifo_get=-1;

static void set_nonblock_flag(int fd) {
  int oldflags;

  oldflags = fcntl(fd, F_GETFL, 0);
  if (oldflags != -1) {
    if (fcntl(keyb_fifo_put, F_SETFL, oldflags | O_NONBLOCK) != -1) {
       return;
    }
  }
  mp_msg(MSGT_INPUT,MSGL_ERR,"Cannot set nonblocking mode for fd %d!\n", fd);
}

static void make_pipe(int* pr,int* pw){
  int temp[2];
  if(pipe(temp)!=0) mp_msg(MSGT_FIXME, MSGL_FIXME, MSGTR_CannotMakePipe);
  *pr=temp[0];
  *pw=temp[1];
  set_nonblock_flag(temp[1]);
}

void mplayer_put_key(int code){

    if( write(keyb_fifo_put,&code,4) != 4 ){
        mp_msg(MSGT_INPUT,MSGL_ERR,"*** key event dropped (FIFO is full) ***\n");
    }
}

#else

#define KEY_FIFO_SIZE 1024
static int key_fifo_data[KEY_FIFO_SIZE];
static int key_fifo_read=0;
static int key_fifo_write=0;

void mplayer_put_key(int code){
//  printf("mplayer_put_key(%d)\n",code);
  if(((key_fifo_write+1)%KEY_FIFO_SIZE)==key_fifo_read) return; // FIFO FULL!!
  key_fifo_data[key_fifo_write]=code;
  key_fifo_write=(key_fifo_write+1)%KEY_FIFO_SIZE;
}

int mplayer_get_key(int fd){
  int key;
//  printf("mplayer_get_key(%d)\n",fd);
  if(key_fifo_write==key_fifo_read) return MP_INPUT_NOTHING;
  key=key_fifo_data[key_fifo_read];
  key_fifo_read=(key_fifo_read+1)%KEY_FIFO_SIZE;
//  printf("mplayer_get_key => %d\n",key);
  return key;
}

#endif

