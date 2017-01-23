/**
 * @file		mytree.h
 * @brief		ディレクトリの遍歴ツール
 * @author		Ricky
 * @date		2017.01.01
 * @copyright	(C) 2017
 */


#ifndef _MYTREE_H_
#define _MYTREE_H_

/** フォルダ名の長さ */
#define		D_DIR_NAME_LENTH		(255)
/** ファイル名の長さ */
#define		D_FILE_NAME_LENTH		(255)
/** パスの長さ */
#define		D_PATH_LENTH			(1000)
/** スペースの長さ */
#define		D_SPACE_LENTH			(255)

/** フォルダリスト */
typedef struct ST_DIRECTORY_LIST_t{
	void*				dirinfo;							/** < フォルダ情報 */
	void*				dirnext;							/** < next */
}ST_DIRECTORY_LIST;

/** ファイルリスト */
typedef struct ST_FILE_LIST_t{
	void*				fileinfo;							/** < ファイル情報 */
	void*				filenext;							/** < next */
}ST_FILE_LIST;

/** フォルダ情報構造体 */
typedef struct ST_DIRECTORY_t{
	char				dirname[D_DIR_NAME_LENTH + 1];		/** < フォルダ名 */
	long				update;								/** < 更新期日 */
	ST_DIRECTORY_LIST*	dirHead;							/** < フォルダリスト */
	ST_FILE_LIST*		fileHead;							/** < ファイルリスト */
}ST_DIRECTORY;

/** ファイル情報構造体 */
typedef struct ST_FILE_t{
	char				filename[D_FILE_NAME_LENTH + 1];	/** < ファイル名 */
	long				update;								/** < 更新期日 */
}ST_FILE;

#endif //_MYTREE_H_
