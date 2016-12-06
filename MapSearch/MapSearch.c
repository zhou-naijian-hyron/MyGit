#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ST_SAMPLE_NODE_t{
	char	sub;
	ST_SAMPLE_NODE	*up;
	ST_SAMPLE_NODE	*down;
	ST_SAMPLE_NODE	*left;
	ST_SAMPLE_NODE	*right;
}ST_SAMPLE_NODE;

#define		D_SAMPLE_COLUMN_NUM 	(10)
#define		D_SAMPLE_ROM_NUM		(10)
#define		D_STRING_LENTH_MAX		(10)
#define		D_CHECK_NUM_MAX 		(10)

enum D_INPUT_STEP{
	D_INPUT_STEP_SAMPLE = 0,
	D_INPUT_STEP_CHKNUM,
	D_INPUT_STEP_CHKSTR,
	D_INPUT_STEP_END
};
int main()
{
	int rowNum, chkCnt, chkNum;
	int i;
	D_INPUT_STEP step;
	char string[D_STRING_LENTH_MAX];
	char chMap[D_SAMPLE_ROM_NUM][D_SAMPLE_COLUMN_NUM];
	char chkStr[D_CHECK_NUM_MAX][D_CHECK_NUM_MAX];
	ST_SAMPLE_NODE stMap[D_SAMPLE_ROM_NUM][D_SAMPLE_COLUMN_NUM];

	step = D_INPUT_STEP_SAMPLE;
	rowNum = 0;
	chkCnt = 0;
	chkNum = 0;
	memset( string, 0x00, sizeof(string));
	memset( chMap, 0x00, sizeof(chMap));
	memset( chkStr, 0x00, sizeof(chkStr));
	memset( stMap, 0x00, sizeof(ST_SAMPLE_NODE) * D_SAMPLE_COLUMN_NUM * D_SAMPLE_ROM_NUM);
	
	while (1) {
		scanf( "%s", string);

		switch (step) {
			case D_INPUT_STEP_SAMPLE:
				if (strlen(string) != D_STRING_LENTH_MAX) {
					printf("Size Error!!! string = %s\n", string);
					goto ERROR;
				}
				memcpy( &chMap[rowNum][0], string, D_SAMPLE_COLUMN_NUM );
				rowNum++;
				
				if (rowNum >= D_SAMPLE_ROM_NUM) {
					step = D_INPUT_STEP_CHKNUM;
				}
				break;
				
			case D_INPUT_STEP_CHKNUM:
				chkCnt = atoi(string);
				if (chkCnt == 0) {
					printf("Check Number Error!!!\n");
					goto ERROR;
				}
				step = D_INPUT_STEP_CHKSTR;
				if (chkCnt > D_CHECK_NUM_MAX) {
					goto ERROR;
				}
				break;
				
			case D_INPUT_STEP_CHKSTR:
				if (strlen(string) > D_STRING_LENTH_MAX) {
					printf("Check String Size Error!!! string = %s\n", string);
					goto ERROR;
				}
				memcpy( &chkStr[chkNum][0], string, strlen(string) );
				chkNum++;
				
				if (chkNum >= D_CHECK_NUM_MAX) {
					step = D_INPUT_STEP_END;
				}
				break;

			case D_INPUT_STEP_END:
				for ( i = 0; i < chkCnt; i++) {
					;
				}
				break;

			default:
				printf("STEP Error!!!\n");
				goto ERROR;
				break;
		}
	}
	
ERROR:
	return -1;
}