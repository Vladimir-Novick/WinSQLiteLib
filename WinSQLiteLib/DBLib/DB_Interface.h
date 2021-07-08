#pragma once
#include "Mtype.h"
#include <string>
#include <windows.h>
#include <list>





using namespace std;


/// <summary>
///   Interface classs for all database wrapper classes
/// </summary>
class  DB_Interface
{
public:

    int virtual filexist(char* fileName) = 0;

    void virtual _unlink(char* fileName) = 0;

    int  virtual db_findfirst(const char* filespec, string* fileinfo) = 0;

    void virtual RenameTable(char* OldFile, char* NewFileName) = 0;

    int virtual DeleteTable(char * fileNamePath) = 0;

    int virtual CopyTable(char * targetFileNamePath, char * sourceFileNamepath) = 0;

    int virtual GetFileList(char* mask, list<string>* fileList) = 0;

    void virtual NewBackupProject(HWND hWndParent, const char far* Drive, const char far* PrjName, int FlagOldVersion) = 0;
    /// <summary>
    ///   rename  project
    /// </summary>
    /// <param name="oldname"></param>
    /// <param name="newname"></param>
    /// <returns></returns>
    int virtual RenameProject(char* oldname, char* newname) = 0;
     /// <summary>
    ///   get base class name
    /// </summary>
    /// <returns></returns>
    std::string  virtual   GetName() = 0;
	/// <summary>
	/// open file/Table
	/// </summary>
	/// <param name="fdes"></param>
	/// <param name="fname"></param>
	/// <param name="opn_mode"></param>
	/// <param name="owner"></param>
	/// <returns></returns>
    int  virtual   btrb_open(void** fdes, char* fname, int opn_mode, char* owner) = 0;
  /// <summary>
  /// close file/table ( 1 )
  /// </summary>
  /// <param name="fdes"></param>
  /// <returns></returns>
    int    virtual   btrb_close(void** fdes) = 0;
  /// <summary>
  /// Create file/table
  /// </summary>
  /// <param name="fdes"></param>
  /// <param name="fname"></param>
  /// <param name="rec_len"></param>
  /// <param name="owner"></param>
  /// <returns></returns>
   int virtual   btrb_create(void** fdes, char* fname, word* rec_len, char* owner)= 0 ;
  /// <summary>
  ///   drop file/table cascade
  /// </summary>
  /// <param name="fdes"></param>
  /// <param name="fname"></param>
  /// <param name="owner"></param>
  /// <returns></returns>
   int virtual   btrb_drop(void** fdes, char* fname, char* owner)= 0 ;
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
    int    virtual   btrb_nget_e(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len,  word locking)= 0 ;
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
    int    virtual   btrb_nget_ge(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len,  word locking)= 0 ;
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
    int    virtual   btrb_nget_l(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len,  word locking)= 0 ;
  /// <summary>
  /// data get current position
  /// </summary>
  /// <param name="fdes"></param>
  /// <param name="pos_num"></param>
  /// <returns></returns>
    int    virtual   btrb_dget_pos(void* fdes, long* pos_num)= 0 ;
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
    int    virtual   btrb_dget(void* fdes, void* rec_buff, void* key_buff, word* rec_len, long pos_num, int key_num, word locking)= 0 ;
  /// <summary>
  /// data get first
  /// </summary>
  /// <param name="fdes"></param>
  /// <param name="rec_buff"></param>
  /// <param name="rec_len"></param>
  /// <param name="locking"></param>
  /// <returns></returns>
    int    virtual   btrb_dgetf(void* fdes, void* rec_buff, word* rec_len, word locking)= 0 ;
  /// <summary>
  /// data get next
  /// </summary>
  /// <param name="fdes"></param>
  /// <param name="rec_buff"></param>
  /// <param name="rec_len"></param>
  /// <param name="locking"></param>
  /// <returns></returns>
    int    virtual   btrb_dgetn(void* fdes, void* rec_buff, word* rec_len, word locking)= 0 ;
  /// <summary>
  /// data get last
  /// </summary>
  /// <param name="fdes"></param>
  /// <param name="rec_buff"></param>
  /// <param name="rec_len"></param>
  /// <param name="locking"></param>
  /// <returns></returns>
    int    virtual   btrb_dgetl(void* fdes, void* rec_buff, word* rec_len, word locking)= 0 ;
  /// <summary>
  /// data get prev
  /// </summary>
  /// <param name="fdes"></param>
  /// <param name="rec_buff"></param>
  /// <param name="rec_len"></param>
  /// <param name="locking"></param>
  /// <returns></returns>
    int    virtual   btrb_dgetp(void* fdes, void* rec_buff, word* rec_len, word locking)= 0 ;
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
    int    virtual   btrb_ngetf(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len,  word locking)= 0 ;
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
    int    virtual   btrb_ngetn(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len,  word locking)= 0 ;
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
    int    virtual   btrb_ngetp(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len,  word locking)= 0 ;
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
    int    virtual   btrb_ngetl(void* fdes, int key_num, void* rec_buff, void* key_buff, word* rec_len,  word locking)= 0 ;
   /// <summary>
    /// BTRBs the insert.
    /// </summary>
    /// <param name="fdes">The fdes.</param>
    /// <param name="key_num">The key number.</param>
    /// <param name="rec_buff">The record buff.</param>
    /// <param name="key_buff">The key buff.</param>
    /// <param name="rec_len">Length of the record.</param>
    /// <param name="key_len">Length of the key.</param>
    /// <param name="locking">The locking.</param>
    /// <returns></returns>
    int    virtual   btrb_insert(void* fdes, int key_num, void* rec_buff, void* key_buff, word rec_len,  word locking)= 0 ;
  ///  /// <summary>
  /// update old record (current record)
  /// </summary>
  /// <param name="fdes"></param>
  /// <param name="key_num"></param>
  /// <param name="rec_buff"></param>
  /// <param name="key_buff"></param>
  /// <param name="rec_len"></param>
  /// <param name="locking"></param>
  /// <returns></returns>
    int    virtual   btrb_update(void* fdes, int key_num, void* rec_buff, void* key_buff, word rec_len, word locking)= 0 ;
  /// <summary>
  /// delete cur record
  /// </summary>
  /// <param name="fdes"></param>
  /// <param name="key_num"></param>
  /// <param name="rec_len"></param>
  /// <returns></returns>
    int    virtual   btrb_delete(void* fdes, int key_num, word* rec_len)= 0 ;
  /// <summary>
  ///   unlock record locking
  /// </summary>
  /// <param name="fdes"></param>
  /// <param name="locking">
  /// BTRMA_- Lock single   record , wait  if locked 
  /// BTRMA_LKSA - Lock single   record, abort if locked
  /// BTRMA_LKMW - Lock multiple record, wait  if locked
  /// BTRMA_LKMA - Lock multiple record, abort if locked
  /// </param>
  /// <returns></returns>
    int    virtual   btrb_unlock(void* fdes, word locking)= 0 ;

 
};

