#pragma once

#include <dscr\Mtype.h>
/*
 * btr_bas.h
 */
//#include "DB_Interface.h"
      

#define BTBS_MALOC      100     /* memory allocation error */

    /// <summary>
    /// open file
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="fname"></param>
    /// <param name="opn_mode"></param>
    /// <param name="owner"></param>
    /// <returns></returns>
      int    btrb_open(void** fdes, char* fname, int opn_mode, char* owner);
    /// <summary>
    /// close file
    /// </summary>
    /// <param name="fdes"></param>
    /// <returns></returns>
      int    btrb_close(void** fdes);
    /// <summary>
    ///    Create file/table
    /// </summary>
    /// <param name="fname"></param>
    /// <param name="rec_len"></param>
    /// <param name="owner"></param>
    /// <returns></returns>
	 int btrb_createDB(void** fdes, char* fname, word* rec_len, char* owner);
    /// <summary>
    ///   Drop file/rable
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="fname"></param>
    /// <param name="rec_len"></param>
    /// <param name="owner"></param>
    /// <returns></returns>
     int btrb_dropDB(void** fdes, char* fname, word* rec_len, char* owner);
    /// <summary>
    ///   index get equal
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="key_num"></param>
    /// <param name="rec_buff"></param>
    /// <param name="key_buff"></param>
    /// <param name="rec_len"></param>
    /// <param name="locking"></param>
    /// <returns></returns>
      int    btrb_nget_e(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len, word locking);
    /// <summary>
    ///  index get greater equal
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="key_num"></param>
    /// <param name="rec_buff"></param>
    /// <param name="key_buff"></param>
    /// <param name="rec_len"></param>
    /// <param name="locking"></param>
    /// <returns></returns>
      int    btrb_nget_ge(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len, word locking);
    /// <summary>
    /// index get less then
    /// </summary>
    /// <param name="fdes">The fdes.</param>
    /// <param name="key_num">The key number.</param>
    /// <param name="rec_buff">The record buff.</param>
    /// <param name="key_buff">The key buff.</param>
    /// <param name="rec_len">Length of the record.</param>
    /// <param name="locking">The locking.</param>
    /// <returns></returns>
      int    btrb_nget_l(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len, word locking);
    /// <summary>
    ///  get current record direct position
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="pos_num"></param>
    /// <returns></returns>
      int    btrb_dget_pos(void* fdes, long* pos_num);
    /// <summary>
    /// data get by position
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="rec_buff"></param>
    /// <param name="key_buff"></param>
    /// <param name="rec_len"></param>
    /// <param name="pos_num"></param>
    /// <param name="key_num"></param>
    /// <param name="locking"></param>
    /// <returns></returns>
      int    btrb_dget(void* fdes, void* rec_buff, void* key_buff, word* rec_len, long pos_num, int key_num, word locking);
    /// <summary>
    /// data get first
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="rec_buff"></param>
    /// <param name="rec_len"></param>
    /// <param name="locking"></param>
    /// <returns></returns>
      int    btrb_dgetf(void* fdes, void* rec_buff, word* rec_len, word locking);
    /// <summary>
    /// data get next
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="rec_buff"></param>
    /// <param name="rec_len"></param>
    /// <param name="locking"></param>
    /// <returns></returns>
      int    btrb_dgetn(void* fdes, void* rec_buff, word* rec_len, word locking);
    /// <summary>
    /// data get last
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="rec_buff"></param>
    /// <param name="rec_len"></param>
    /// <param name="locking"></param>
    /// <returns></returns>
      int    btrb_dgetl(void* fdes, void* rec_buff, word* rec_len, word locking);
    /// <summary>
    /// data get prev
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="rec_buff"></param>
    /// <param name="rec_len"></param>
    /// <param name="locking"></param>
    /// <returns></returns>
      int    btrb_dgetp(void* fdes, void* rec_buff, word* rec_len, word locking);
    /// <summary>
    /// index get first
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="key_num"></param>
    /// <param name="rec_buff"></param>
    /// <param name="key_buff"></param>
    /// <param name="rec_len"></param>
    /// <param name="locking"></param>
    /// <returns></returns>
      int    btrb_ngetf(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len, word locking);
    /// <summary>
    /// index get next
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="key_num"></param>
    /// <param name="rec_buff"></param>
    /// <param name="key_buff"></param>
    /// <param name="rec_len"></param>
    /// <param name="locking"></param>
    /// <returns></returns>
      int    btrb_ngetn(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len, word locking);
    /// <summary>
    /// index get prev
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="key_num"></param>
    /// <param name="rec_buff"></param>
    /// <param name="key_buff"></param>
    /// <param name="rec_len"></param>
    /// <param name="locking"></param>
    /// <returns></returns>
      int    btrb_ngetp(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len, word locking);
    /// <summary>
    /// index get last
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="key_num"></param>
    /// <param name="rec_buff"></param>
    /// <param name="key_buff"></param>
    /// <param name="rec_len"></param>
    /// <param name="locking"></param>
    /// <returns></returns>
      int    btrb_ngetl(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len, word locking);
    /// <summary>
    /// insert new record
    /// </summary>
    /// <param name="fdes">The fdes.</param>
    /// <param name="key_num">The key number.</param>
    /// <param name="rec_buff">The record buff.</param>
    /// <param name="key_buff">The key buff.</param>
    /// <param name="rec_len">Length of the record.</param>
    /// <param name="locking">The locking.</param>
    /// <returns></returns>
      int    btrb_insert(void* fdes, int key_num, void* rec_buff, void* key_buff, word rec_len, word locking);
    /// <summary>
    /// update old record (current record)
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="key_num"></param>
    /// <param name="rec_buff"></param>
    /// <param name="key_buff"></param>
    /// <param name="rec_len"></param>
    /// <param name="locking"></param>
    /// <returns></returns>
      int    btrb_update(void* fdes, int key_num, void* rec_buff, void* key_buff, word rec_len, word locking);
    /// <summary>
    /// delete current record
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="key_num"></param>
    /// <param name="rec_len"></param>
    /// <returns></returns>
      int    btrb_delete(void* fdes, int key_num, word* rec_len);
    /// <summary>
    ///   lock/unlock record
    /// </summary>
    /// <param name="fdes"></param>
    /// <param name="locking">
    /// BTRMA_- Lock single   record , wait  if locked 
    /// BTRMA_LKSA - Lock single   record, abort if locked
    /// BTRMA_LKMW - Lock multiple record, wait  if locked
    /// BTRMA_LKMA - Lock multiple record, abort if locked
    /// </param>
    /// <returns></returns>
      int    btrb_unlock(void* fdes, word locking);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="operation"></param>
    /// <param name="posblk"></param>
    /// <param name="databuf"></param>
    /// <param name="datalen"></param>
    /// <param name="keyP"></param>
    /// <param name="keyNumber"></param>
    /// <returns></returns>
    static int BtrbCallBtr(int operation, char far* posblk, char far* databuf,
        unsigned short far* datalen, char far* keyP, int keyNumber);



