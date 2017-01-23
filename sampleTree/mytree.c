/**
 * @file		mytree.c
 * @brief		ディレクトリツリーの遍歴ツール
 * @author		Ricky
 * @date		2017.01.01
 * @copyright	(C) 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <ftw.h>

#include "mytree.h"


static void readFileList( ST_DIRECTORY *pnode, char *path);
static void dumpInfo( ST_DIRECTORY *pnode, int depth );

/**
 * @brief @b 処理概要 : ディレクトリツリーを遍歴する
 * @return  0 成功, -1 失敗
 *
 * @b 処理詳細：指定したディレクトリにあるファイルやサブディレクトリを歩きまわり、情報を出力ファイルに保存する
 */
int main(int argc,char **argv)
{
	struct stat st;
	ST_DIRECTORY *pHead = NULL;

	/** 入力パラメータのチェックを行う */
	if(argc == 2) {
		if( (strcmp( argv[1], "-h") == 0) ||
			(strcmp( argv[1], "-help") == 0) ) {
			goto USAGE;
		}
	}
	else if(argc == 4) {
		if( (strcmp( argv[2], "-t") == 0) && (atoi(argv[3]) != 0) ) {
			// nothing
		}
		else {
			goto USAGE;
		}
	}
	else {
		goto USAGE;
	}

	/** 入力したディレクトリのパスをチェックする */
	stat(argv[1],&st);
	if(!S_ISDIR(st.st_mode)) {
		fprintf(stderr,"Not directory path(%s)\n", argv[1]);
		goto USAGE;
	}

	/** 指定したディレクトリの情報を取得する */
	pHead = (ST_DIRECTORY *)malloc(sizeof(ST_DIRECTORY));
	memset( pHead, 0x00, sizeof(ST_DIRECTORY));
	memcpy( pHead->dirname, argv[1], D_DIR_NAME_LENTH);
	pHead->update = st.st_mtim.tv_sec;

	/** 指定したディレクトリをリード(read)する */
	readFileList( pHead, argv[1]);

	/** 情報をダンプする */
	dumpInfo( pHead, 0);


	return 0;
USAGE:
	printf( "Usage: SampleTree <path> [-t days] [-h|-help]\n"
			"                  path : directory path\n"
			"                  -t   : interval time. '10' means 10days\n"
			"                  -h/-help : show usage\n");
	exit(0);
}

/**
 * @brief @b 処理概要 : 指定したディレクトリツリーをリード(read)する
 *
 * @param [in/out] pnode : リストのノード(node)
 * @param [in] path : ディレクトリのパス
 *
 */
void readFileList( ST_DIRECTORY *pnode, char *path)
{
	DIR *dir;
	struct dirent *ptr;
	ST_DIRECTORY *dirinfo = NULL;
	ST_FILE *fileinfo = NULL;
	ST_DIRECTORY_LIST *dirlist = NULL;
	ST_FILE_LIST *filelist = NULL;
	char subPath[D_PATH_LENTH] = {0};
	struct stat st;
	void *p;


	/** フォルダをオープン(open)する */
	if ((dir=opendir(path)) == NULL) {
		fprintf(stderr,"Open directory error!!!\n");
		return;
	}

	/** フォルダをリード(read)する */
	while ((ptr=readdir(dir)) != NULL) {

		printf("d_name = %s\n", ptr->d_name);

		/** 該当フォルダ(.)と前フォルダ(..)の時、ジャンプする */
		if( (strcmp(ptr->d_name,".") == 0) || (strcmp(ptr->d_name,"..") == 0) ) {
			continue;
		}
		/** 該当フォルダ下にサブディレクトリの情報を取得する */
		else if(ptr->d_type == 4) {
			// フォルダ名
			dirinfo = (ST_DIRECTORY *)malloc(sizeof(ST_DIRECTORY));
			memset( dirinfo, 0x00, sizeof(ST_DIRECTORY));
			memcpy( dirinfo->dirname, ptr->d_name, D_DIR_NAME_LENTH);
			// フォルダパス
			snprintf( subPath, sizeof(subPath), "%s/%s", path, ptr->d_name);
			stat(subPath, &st);
			// フォルダ更新期日
			dirinfo->update = st.st_mtim.tv_sec;

			dirlist = (ST_DIRECTORY_LIST *)malloc(sizeof(ST_DIRECTORY_LIST));
			dirlist->dirinfo = (void *) dirinfo;
			dirlist->dirnext = NULL;

			// NULLのNODEをサーチして、NODEを投げる
			p = (void *)pnode->dirHead;
			if( p == NULL ) {
				pnode->dirHead = dirlist;
				continue;
			}

			while( ((ST_DIRECTORY_LIST *)p)->dirnext ) {
				p = ((ST_DIRECTORY_LIST *)p)->dirnext;
			}
			((ST_DIRECTORY_LIST *)p)->dirnext = dirlist;

			/** サブディレクトリをリード(read)する */
			readFileList( dirinfo, subPath);
		}
		/** 該当フォルダ下にファイルの情報を取得する */
		else {
			// ファイル名
			fileinfo = (ST_FILE *)malloc(sizeof(ST_FILE));
			memset( fileinfo, 0x00, sizeof(ST_FILE));
			memcpy( fileinfo->filename, ptr->d_name, D_FILE_NAME_LENTH);
			// ファイルパス
			snprintf( subPath, sizeof(subPath), "%s/%s", path, ptr->d_name);
			stat(subPath, &st);
			// ファイル更新期日
			fileinfo->update = st.st_mtim.tv_sec;

			filelist = (ST_FILE_LIST *)malloc(sizeof(ST_FILE_LIST));
			filelist->fileinfo = (void *) fileinfo;
			filelist->filenext = NULL;

			// NULLのNODEをサーチして、NODEを投げる
			p = (void *)pnode->fileHead;
			if( p == NULL ) {
				pnode->fileHead = filelist;
				continue;
			}

			while( ((ST_FILE_LIST *)p)->filenext ) {
				p = ((ST_FILE_LIST *)p)->filenext;
			}
			((ST_FILE_LIST *)p)->filenext = filelist;
		}
	}
}

/**
 * @brief @b 処理概要 : 指定したディレクトリ情報をダンプする
 *
 * @param [in] pnode : ヘッダのポインター
 *
 */void dumpInfo( ST_DIRECTORY *pnode, int depth )
{
	ST_DIRECTORY *dirinfo = NULL;
	ST_FILE *fileinfo = NULL;
	ST_DIRECTORY_LIST *dirlist = NULL;
	ST_FILE_LIST *filelist = NULL;
	//char space[D_SPACE_LENTH + 1] = {0};

	printf( "ディレクトリ : %s\n", pnode->dirname);
	filelist = pnode->fileHead;
	while(filelist)
	{
		fileinfo = (ST_FILE *)filelist->fileinfo;
		printf("  ファイル : %s\n", fileinfo->filename);
		filelist = (ST_FILE_LIST *)filelist->filenext;
	}

	dirlist = pnode->dirHead;
	while(dirlist)
	{
		dirinfo = (ST_DIRECTORY *)dirlist->dirinfo;
		dumpInfo( dirinfo, depth + 1);
		dirlist = (ST_DIRECTORY_LIST *)dirlist->dirnext;
	}
}


