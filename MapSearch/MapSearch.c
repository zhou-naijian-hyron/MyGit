#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ST_SAMPLE_NODE_t{
	char	sub;
	char	*up;
	char	*down;
	char	*left;
	char	*right;
}ST_SAMPLE_NODE;

#define		D_SAMPLE_COLUMN_NUM		(10)    /** < Sample Columns */
#define		D_SAMPLE_ROM_NUM		(10)    /** < Sample Rows */
#define		D_STRING_LENTH_MAX		(10)    /** < String Size */
#define		D_CHECK_NUM_MAX			(10)    /** < Check MaxTimes */

typedef enum {
	D_INPUT_STEP_SAMPLE = 0,	/** < STEP1: input Sample */
	D_INPUT_STEP_CHKNUM,		/** < STEP2: input Check Times */
	D_INPUT_STEP_CHKSTR,		/** < STEP3: input Check String */
	D_INPUT_STEP_END			/** < STEP4: get result */
}D_INPUT_STEP;


// SampleArray
char chMap[D_SAMPLE_ROM_NUM][D_SAMPLE_COLUMN_NUM];
// CheckArray
char chkStr[D_CHECK_NUM_MAX][D_STRING_LENTH_MAX + 1];
// Map
ST_SAMPLE_NODE stMap[D_SAMPLE_ROM_NUM][D_SAMPLE_COLUMN_NUM];



static void initMapping( void );
static int checkStrFromMap( char *str, int size);
int main()
{
	int rowNum, chkCnt, chkNum;
	int i, j;
	D_INPUT_STEP step;
	char string[D_STRING_LENTH_MAX];

	step = D_INPUT_STEP_SAMPLE;
	rowNum = 0;
	chkCnt = 0;
	chkNum = 0;
	memset( string, 0x00, sizeof(string));
	memset( chMap, 0x00, sizeof(chMap));
	memset( chkStr, 0x00, sizeof(chkStr));
	memset( stMap, 0x00, sizeof(ST_SAMPLE_NODE) * D_SAMPLE_COLUMN_NUM * D_SAMPLE_ROM_NUM);

	while (1) {
		switch (step) {
			/** STEP1: input Sample */
			case D_INPUT_STEP_SAMPLE:
				printf("Please input Sample [%d] > ", rowNum);
				scanf( "%s", string);

				// Size Check
				if (strlen(string) != D_STRING_LENTH_MAX) {
					printf("Size Error!!! string = %s\n", string);
					return -1;
				}

				// Set SampleArray
				memcpy( &chMap[rowNum][0], string, D_SAMPLE_COLUMN_NUM );
				rowNum++;

				if (rowNum >= D_SAMPLE_ROM_NUM) {
					step = D_INPUT_STEP_CHKNUM;
				}
				break;

			/** STEP2: input Check Times */
			case D_INPUT_STEP_CHKNUM:
				printf("Please input Check Times > ");
				scanf( "%d", &chkCnt);

				// CheckTimes Check
				step = D_INPUT_STEP_CHKSTR;
				if (chkCnt > D_CHECK_NUM_MAX) {
					return -1;
				}
				break;

			/** STEP3: input Check String */
			case D_INPUT_STEP_CHKSTR:
				printf("Please input Check String > ");
				scanf( "%s", string);

				// Size Check
				if (strlen(string) > D_STRING_LENTH_MAX) {
					printf("Check String Size Error!!! string = %s\n", string);
					return -1;
				}

				// Set CheckArray
				memcpy( &chkStr[chkNum][0], string, D_STRING_LENTH_MAX );
				chkNum++;

				if (chkNum >= chkCnt) {
					step = D_INPUT_STEP_END;
				}
				break;

			/** STEP4: get result */
			case D_INPUT_STEP_END:
				printf("Result:\n");

				// Map init
				initMapping();

				// Set Map
				for ( i = 0; i < D_SAMPLE_ROM_NUM; i++ ) {
					for ( j = 0; j < D_SAMPLE_COLUMN_NUM; j++ ) {
						stMap[i][j].sub = chMap[i][j];
					}
				}

				// In Map, Search CheckArray
				for ( i = 0; i < chkCnt; i++ ) {
					if ( checkStrFromMap( chkStr[i], strlen(chkStr[i])) == 1 ) {
						printf("Yes\n");
					}
					else {
						printf("No\n");
					}
				}
				return 0;

			default:
				printf("STEP Error!!!\n");
				return -1;
		}
	}
}

// Map init
void initMapping( void )
{
	int i, j;

	for ( i = 0; i < D_SAMPLE_ROM_NUM; i++ ) {
		for ( j = 0; j < D_SAMPLE_COLUMN_NUM; j++ ) {
			// up
			if ( i - 1 < 0 ) {
				stMap[i][j].up = NULL;
			}
			else {
				stMap[i][j].up = (char *)&(stMap[i-1][j]);
			}

			// down
			if ( i + 1 >= D_SAMPLE_ROM_NUM ) {
				stMap[i][j].down = NULL;
			}
			else {
				stMap[i][j].down = (char *)&(stMap[i+1][j]);
			}

			// left
			if ( j - 1 < 0 ) {
				stMap[i][j].left = NULL;
			}
			else {
				stMap[i][j].left = (char *)&(stMap[i][j-1]);
			}

			// right
			if ( j + 1 >= D_SAMPLE_COLUMN_NUM ) {
				stMap[i][j].right = NULL;
			}
			else {
				stMap[i][j].right = (char *)&(stMap[i][j+1]);
			}
		}
	}
}

// In Map, Search CheckArray
// [IN] *str : check string
// [IN] size : string size
// return 1 : Found
//        0 : Unfound
int checkStrFromMap( char *str, int size)
{
	int i, j, count;
	ST_SAMPLE_NODE *p;
	count = 0;
	p = NULL;
	
	printf("check string = %s\t size = %d\t result:", str, size);
	for ( i = 0; i < D_SAMPLE_ROM_NUM; i++ ) {
		for ( j = 0; j < D_SAMPLE_COLUMN_NUM; j++ ) {
			if ( stMap[i][j].sub ==  str[0] )
			{
				// when size = 1, Found
				if ( size == 1 ) {
					return 1;
				}

				// up
				p = (ST_SAMPLE_NODE *)stMap[i][j].up;
				while( p != NULL && p->sub == str[count] )
				{
					count++;
					p = (ST_SAMPLE_NODE *)p->up;
					if( count == size)
					{
						return 1;
					}
				}

				// down
				p = (ST_SAMPLE_NODE *)stMap[i][j].down;
				count = 1;
				while( p != NULL && p->sub == str[count] )
				{
					count++;
					p = (ST_SAMPLE_NODE *)p->down;
					if( count == size)
					{
						return 1;
					}
				}

				// left
				p = (ST_SAMPLE_NODE *)stMap[i][j].left;
				count = 1;
				while( p != NULL && p->sub == str[count] )
				{
					count++;
					p = (ST_SAMPLE_NODE *)p->left;
					if( count == size)
					{
						return 1;
					}
				}

				// right
				p = (ST_SAMPLE_NODE *)stMap[i][j].right;
				count = 1;
				while( p != NULL && p->sub == str[count] )
				{
					count++;
					p = (ST_SAMPLE_NODE *)p->right;
					if( count == size)
					{
						return 1;
					}
				}
			}
		}
	}

	// not found
	return 0;
}


