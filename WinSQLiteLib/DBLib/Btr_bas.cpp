//
// btr_bas.cpp
//


#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>

#include <dscr\mtype.h>

//#include <btrieve\btrieve.h>

#include <btr_bas\btrconst.h>
#include <btr_bas\btrapi.h>
#include <btr_bas\aldbtr.h>
#include <btr_bas\btr_bas.h>

#ifdef _DEBUG
#undef DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static int BtrbCallBtr(int operation, char far* posblk, char far* databuf,
    unsigned short far* datalen, char far* keyP, int keyNumber);


//static int BtrbCallBtr(int operation,char *posblk,char *databuf,
//            unsigned *datalen,char *keyP,int keyNumber);


/// <summary>
///   open file
/// </summary>
/// <param name="fdes"></param>
/// <param name="fname"></param>
/// <param name="opn_mode"></param>
/// <param name="owner"></param>
/// <returns></returns>
int btrb_open(void **fdes,char *fname,int opn_mode,char *owner)
{
int     rc;
word    len;
 
  rc = 0;
  *fdes = malloc(BTR_FDSIZE+128); 
//  *fdes = (void *) new char[BTR_FDSIZE+128];
  if(*fdes == 0)
    {rc = BTBS_MALOC;
    }
   else
    {len = strlen(owner);
     rc = BtrbCallBtr(BTROP_OPEN,(char far *) *fdes,(char far *)owner,
               (unsigned short far *)&len,(char far *)fname,opn_mode);
     if(rc)
       *fdes = 0;
    }
  return(rc);
}
/// <summary>
///   Create file/table
/// </summary>
/// <param name="fdes"></param>
/// <param name="fname"></param>
/// <param name="rec_len"></param>
/// <param name="owner"></param>
/// <returns></returns>
int btrb_createDB(void** fdes, char* fname, word* rec_len, char* owner) {
    
    int     rc=0;
    return(rc);

};

/// <summary>
///   Drop file/table
/// </summary>
/// <param name="fdes"></param>
/// <param name="fname"></param>
/// <param name="rec_len"></param>
/// <param name="owner"></param>
/// <returns></returns>
int btrb_dropDB(void** fdes, char* fname, word* rec_len, char* owner) {

    int     rc = 0;
    return(rc);

};

/// <summary>
///   close file/Connection
/// </summary>
/// <param name="fdes"></param>
/// <returns></returns>
int  btrb_close(void **fdes)
{
int     rc;
word    len;

  rc = 0;
  len = 0;
  if(*fdes != 0)
    {rc = BtrbCallBtr(BTROP_CLOS,(char far *) *fdes,(char far *)"",
               (unsigned short far *)&len,(char far *)"",0);
     free(*fdes);
//   delete (*fdes);
    }
   else
    {rc = BTRS_FNOPEN;
    }
  *fdes = 0;
  return(rc);
}


/// <summary>
///  get by key - index get equal
/// </summary>
/// <param name="fdes"></param>
/// <param name="key_num"></param>
/// <param name="rec_buff"></param>
/// <param name="key_buff"></param>
/// <param name="rec_len"></param>
/// <param name="locking"></param>
/// <returns></returns>
int  btrb_nget_e(void *fdes,int key_num,void *rec_buff,void *key_buff,
        word *rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_KEQU+locking,(char far *) fdes,(char far *)rec_buff,
            (unsigned short far *)rec_len,(char far *)key_buff,key_num);
  return(rc);
}


/// <summary>
///   index get greater equal
/// </summary>
/// <param name="fdes"></param>
/// <param name="key_num"></param>
/// <param name="rec_buff"></param>
/// <param name="key_buff"></param>
/// <param name="rec_len"></param>
/// <param name="locking"></param>
/// <returns></returns>
int  btrb_nget_ge(void *fdes,int key_num,void *rec_buff,void *key_buff,
        word *rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_KGRE+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *)rec_len,(char far *) key_buff,key_num);
  return(rc);
}

/// <summary>
///   get by key - less
/// </summary>
/// <param name="fdes"></param>
/// <param name="key_num"></param>
/// <param name="rec_buff"></param>
/// <param name="key_buff"></param>
/// <param name="rec_len"></param>
/// <param name="locking"></param>
/// <returns></returns>
int  btrb_nget_l(void *fdes,int key_num,void *rec_buff,void *key_buff,
        word *rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_KLTH+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *) rec_len,(char far *) key_buff,key_num);
  return(rc);
}


/// <summary>
///    get current record direct position
/// </summary>
/// <param name="fdes"></param>
/// <param name="pos_num"></param>
/// <returns></returns>
int  btrb_dget_pos(void *fdes,long *pos_num)
{
int     rc;
word    rec_len;

  rec_len = 4;
  rc = BtrbCallBtr(BTROP_DPOS,(char far *) fdes,(char far *) pos_num,(unsigned short far *)&rec_len,(char far *)"",0);
  return(rc);
}

/// <summary>
///    get record direct
/// </summary>
/// <param name="fdes"></param>
/// <param name="rec_buff"></param>
/// <param name="key_buff"></param>
/// <param name="rec_len"></param>
/// <param name="pos_num"></param>
/// <param name="key_num"></param>
/// <param name="locking"></param>
/// <returns></returns>
int  btrb_dget(void *fdes,void *rec_buff,void *key_buff,word *rec_len,
        long pos_num,int key_num,word locking)
{
int     rc;

  *((long *) rec_buff) = pos_num;
  rc = BtrbCallBtr(BTROP_DGET+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *) rec_len,(char far *) key_buff,key_num);
  return(rc);
}

/// <summary>
///   data get first
/// </summary>
/// <param name="fdes"></param>
/// <param name="rec_buff"></param>
/// <param name="rec_len"></param>
/// <param name="locking"></param>
/// <returns></returns>
int  btrb_dgetf(void *fdes,void *rec_buff,word *rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_DFRS+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *) rec_len,(char far *) "",0);
  return(rc);
}


/// <summary>
///  data get next
/// </summary>
/// <param name="fdes"></param>
/// <param name="rec_buff"></param>
/// <param name="rec_len"></param>
/// <param name="locking"></param>
/// <returns></returns>
int  btrb_dgetn(void *fdes,void *rec_buff,word *rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_DNXT+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *) rec_len,(char far *) "",0);
  return(rc);
}



/// <summary>
///   data get last
/// </summary>
/// <param name="fdes"></param>
/// <param name="rec_buff"></param>
/// <param name="rec_len"></param>
/// <param name="locking"></param>
/// <returns></returns>
int  btrb_dgetl(void *fdes,void *rec_buff,word *rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_DLST+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *) rec_len,(char far *) "",0);
  return(rc);
}

/// <summary>
///  data get prev
/// </summary>
/// <param name="fdes"></param>
/// <param name="rec_buff"></param>
/// <param name="rec_len"></param>
/// <param name="locking"></param>
/// <returns></returns>
int  btrb_dgetp(void *fdes,void *rec_buff,word *rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_DPRV+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *) rec_len,(char far *) "",0);
  return(rc);
}


//
// index get first
//
int  btrb_ngetf(void *fdes,int key_num,void *rec_buff,void *key_buff,
        word *rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_GFRS+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *) rec_len,(char far *) key_buff,key_num);
  return(rc);
}


//
// unlock record locking
//                             
int  btrb_unlock(void *fdes,word locking)
{
char    record[4];
int     keynum,rc;
word    reclen;

  if(locking == BTRMA_LKSA || locking == BTRMA_LKSW)
    {// Single record locking
     keynum = 0;
     rc = BtrbCallBtr(BTROP_UNLK,(char far *) fdes,NULL,NULL,NULL,keynum);
    }
   else
    {// Multiply record locking
     reclen = 4;
     rc = BtrbCallBtr(BTROP_DPOS,(char far *) fdes,record,&reclen,NULL,0);
     if(!rc)
       {keynum = -1;
        reclen = 4;
        rc = BtrbCallBtr(BTROP_UNLK,(char far *) fdes,record,&reclen,NULL,keynum);
       }
    }
  return(rc);
}           
           

//
// index get next
//
int  btrb_ngetn(void *fdes,int key_num,void *rec_buff,void *key_buff,
        word *rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_KNXT+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *) rec_len,(char far *) key_buff,key_num);
  return(rc);
}


//
// index get prev
//
int  btrb_ngetp(void *fdes,int key_num,void *rec_buff,void *key_buff,
        word *rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_KPRV+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *) rec_len,(char far *) key_buff,key_num);
  return(rc);
}


//
// index get last
//
int  btrb_ngetl(void *fdes,int key_num,void *rec_buff,void *key_buff,
        word *rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_GLST+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *) rec_len,(char far *) key_buff,key_num);
  return(rc);
}


//
// insert new record
//
int  btrb_insert(void *fdes,int key_num,void *rec_buff,void *key_buff,
        word rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_INSR+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *) &rec_len,(char far *) key_buff,key_num);
  return(rc);
}


//
// update old record (current record)
//
int  btrb_update(void *fdes,int key_num,void *rec_buff,void *key_buff,
        word rec_len,word locking)
{
int     rc;

  rc = BtrbCallBtr(BTROP_UPDT+locking,(char far *) fdes,(char far *) rec_buff,
            (unsigned short far *) &rec_len,(char far *) key_buff,key_num);
  return(rc);
}


//
// delete cur record
//
int  btrb_delete(void *fdes,int key_num,word *rec_len)
{
int     rc;

  rc = BtrbCallBtr(BTROP_DELE,(char far *) fdes,(char far *) 0,
            (unsigned short far *) rec_len,(char far *) 0,key_num);
  return(rc);
}


//
// Btrieve call
//      
int BtrbCallBtr(int operation,char far *posblk,char far *databuf,
    unsigned short far *datalen,char far *keyP,int keyNumber)
{
int     rc;
        
  rc = BTRV(operation,posblk,databuf,datalen,keyP,keyNumber);
  return(rc);
}


