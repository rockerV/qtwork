#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <semaphore.h>
#include "conf.h"
#include <stdarg.h>
/*****************************************************************************************/
/*****************************************************************************************/
/**********                   conf                                   *********************/
/*****************************************************************************************/
/*****************************************************************************************/

static char sprint_buf[1024*1024];
static char log_file_name[256];
void _logger(char *filename, const char* funcname, int line, int level, char* fmt, ...)
{
    FILE *fd;
    time_t timep;
    struct tm *p;
    int n = 0;

    time(&timep);
    p = localtime(&timep);

    va_list args;
    va_start(args, fmt);
    n = vsprintf(sprint_buf, fmt, args);
    va_end(args);

    fd = stdout;
    fprintf(fd,"[%d-%d-%d-%d:%d:%d][File:%s, Func:%s, Line:%d]", (1900 + p->tm_year), ( 1 + p->tm_mon), p->tm_mday,
            p->tm_hour, p->tm_min, p->tm_sec, filename, funcname, line);
    fprintf(fd,"%s\n", sprint_buf);

    return;
}

/*==============================================================================================*/
/*==============================================================================================*/
/*=====================              end of               conf          =========================*/
/*==============================================================================================*/
/*==============================================================================================*/



/*****************************************************************************************/
/*****************************************************************************************/
/**********                   comm                                   *********************/
/*****************************************************************************************/
/*****************************************************************************************/

//----------------------------------------------------------
unsigned char xCal_crc(char *ptr,int len)
{
    unsigned char crc;
    int i;
    crc = 0;
    while(len--)
    {
        crc ^= *ptr++;
        for(i = 0;i < 8;i++)
        {
            if(crc & 0x01)
            {
                crc = (crc >> 1) ^ 0x8C;
            }else crc >>= 1;
        }
    }
    return crc;
}
char  char2hex(char src)
{
    if(src >= 'a' && src <= 'f')
        return src -'a' + 10;
    else if(src >= 'A' && src <= 'F')
        return src -'A' + 10;
    else if(src >= '0' && src <= '9')
        return src - '0';
    else
    {
        //logger(LOG_DEBUG,"char2hex wrong char %c", src);
        return 0xff;
    }
}
char  hex2char(char src)
{
    char dic[] = "0123456789ABCDEF";
    if(src >=16)
    {
        //logger(LOG_DEBUG,"hex2char wrong char %c", src);
        return dic[15];
    }
    return dic[src];
}

int  hex2string(char* des, char* src, int srcLen)
{
    int i=0;
    if(src == NULL || des == NULL)
    {
        //logger(LOG_DEBUG,"hex2string fail");
        return -1;
    }

    for(i = 0; i < srcLen; i++)
    {
        des[2*i+0] = hex2char((src[i]>>4)&0x0f);
        des[2*i+1] = hex2char(src[i]&0x0f);
    }
    return 2*srcLen;
    //logger(LOG_DEBUG,"des:%s len:%d src:%s",des,srcLen,src);
}

int  hex2str(char* des, char* src, int srcLen)
{
    int i=0;
    if(src == NULL || des == NULL)
    {
        //logger(LOG_DEBUG,"hex2string fail");
        return -1;
    }

    for(i = 0; i < srcLen; i++)
    {
        des[3*i+0] = hex2char((src[i]>>4)&0x0f);
        des[3*i+1] = hex2char(src[i]&0x0f);
        des[3*i+2] = ' ';
    }
    return 3*srcLen;
}

int  string2hex(char * des, char* src)
{
    int len=0,i=0,j=0;
    if(src == NULL || des == NULL)
    {
        //logger(LOG_DEBUG,"string2hex fail");
        return -1;
    }

    len = strlen(src);
    if(len %2 != 0)
    {
        //logger(LOG_DEBUG,"string2hex fail2222");
        return -2;
    }
    for(i = 0; i < len; i+=2)
    {
        des[i/2] = (char2hex(src[i])<<4)+char2hex(src[i+1]);
        j++;
    }
    return j;
}

int  string2hexn(char * des, char* src,int srclen)
{
    int len=0,i=0, j=0;
    if(src == NULL || des == NULL)
    {
        //logger(LOG_DEBUG,"string2hex fail");
        return -1;
    }

    len = srclen;
    if(len %2 != 0)
    {
        //logger(LOG_DEBUG,"string2hex fail2222");
        return -2;
    }
    for(i = 0; i < len; i+=2)
    {
        des[i/2] = (char2hex(src[i])<<4)+char2hex(src[i+1]);
        j++;
    }
    return j;
}

int getrand(int min,int max)
{
    int num;
    srand(time(NULL));
    //rand() ï¿½ï¿½ï¿½?µï¿½ï¿½ï¿½?»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½0ï¿½ï¿½32767
    num=rand()%(max-min+1)+min;
    return num;
}

/* °???·û´®µ±?®½ø???ª»»³??ý¾?£¬'123'->123 */
int trans_string_2_int32(char *s, int *val)
{
    long lval,lbase;
    int is_negative;

    if (s == NULL)
    {
        return -1;
    }

    int len = strlen(s);
    if (len > 10 || len <= 0){
        return -2;
    }

    is_negative = (*s == '-') ? 1 : 0;

    lval = 0;
    lbase = 1;
    while(len-- > is_negative){
        lval += (s[len]-'0') * lbase;
        lbase *= 10;
    }

    if (is_negative)
    {
        lval *= -1;
    }

    if (lval > 0x7fffffff || lval < -80000000)
    {
        return -3;
    }

    *val = (int)lval;

    return 0;
}

/* °???·û´®s?ª»»³?asciiµ?%02x¸ñ?½?ä³öµ½?ý?é£¬abc->a(ascii?ë)b(ascii?ë)c(ascii?ë) */
int trans_string_2_02x(char *s, char *x, int sizex)
{
    int len = strlen(s);
    if (len*2 > sizex){
        return -1;
    }

    while (len--){
        sprintf(x, "%02x", *s++);
        x +=2;
    }
    return 0;
}
/* °?char???ý?éc?ª»»³?%02x¸ñ?½?ä³öµ½x,abc->a(ascii?ë)b(ascii?ë)c(ascii?ë) */
int trans_char_2_02x(char *c, int sizec, char *x, int sizex)
{
    if (sizec*2 > sizex){
        return -1;
    }

    while (sizec--){
        sprintf(x, "%02x", *c++);
        x +=2;
    }
    return 0;
}


/* ´???·û´®?îºóindex_end?ï?á?¡³ö?ª»»?ªuint16 */
uint16_t get_uint16_from_str_end(char *strin, int index_end)
{
    uint16_t ret;
    int len = strlen(strin);
    int y;

    if (strin == NULL)
    {
        return 0;
    }

    ret = 0;
    y = 1;
    while (index_end--)
    {
        if (--len > 0)
        {
            ret += (strin[len] - '0')*y;
            y *= 10;
        }

    }
    return ret;
}



uint16_t get_u16(uint8_t* data)
{
    return (data[0] | (data[1] << 8));
}

int16_t get_u16_r(uint8_t* data)
{
    //return (data[1] | (data[0] << 8));
    return (data[0] | (data[1] << 8));
}


uint32_t get_u32(uint8_t* data)
{
    return (data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24));
}

int u16_to_bytes(uint8_t* data, uint16_t value)
{
    data[0] = value & 0xFF;
    data[1] = (value >> 8) & 0xFF;

    return 0;
}

int u32_to_bytes(uint8_t* data, uint32_t value)
{
    data[0] = value & 0xFF;
    data[1] = (value >> 8) & 0xFF;
    data[2] = (value >> 16) & 0xFF;
    data[3] = (value >> 24) & 0xFF;

    return 0;
}

//big endian
uint32_t get_packet_bytes(uint8_t* data, uint8_t len)
{
    uint32_t ret = 0;

    switch (len) {
    case 1:
        ret = data[0];
        break;

    case 2:
        ret = (data[0] << 8) | data[1];
        break;

    case 3:
        ret = (data[0] << 16) | (data[1] << 8) | data[2];
        break;

    case 4:
        ret = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
        break;
    }

    return ret;
}

//little endian
uint32_t get_packet_bytes_little_endian(uint8_t* data, uint8_t len)
{
    uint32_t ret = 0;

    switch (len) {
    case 1:
        ret = data[0];
        break;

    case 2:
        ret = (data[1] << 8) | data[0];
        break;

    case 3:
        ret = (data[2] << 16) | (data[1] << 8) | data[0];
        break;

    case 4:
        ret = (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
        break;
    }

    return ret;
}

/*********************************************/
/*==============================================================================================*/
/*==============================================================================================*/
/*=====================              end of               comm          =========================*/
/*==============================================================================================*/
/*==============================================================================================*/





/*****************************************************************************************/
/*****************************************************************************************/
/**********                   sub1g                                   *********************/
/*****************************************************************************************/
/*****************************************************************************************/



//if frame valid, return data len, else return -1;
int check_frame_valid(uint8_t *dat)
{
    uint8_t checksum;

    //check frame head and end
    if (GH_PT_HEAD_0 != dat[0] || GH_PT_HEAD_1 != dat[1]
        || dat[dat[GH20_FRAM_LEN_INDEX] + GH20_FRAM_TOTAL_LEN_MIN - GH20_FM_END] != GH_PT_END_0
        || dat[dat[GH20_FRAM_LEN_INDEX] + GH20_FRAM_TOTAL_LEN_MIN - 1] != GH_PT_END_1)
    {
        logger(LOG_ERR, "data format err, end0=%x,end1=%x",
            dat[dat[GH20_FRAM_LEN_INDEX] + GH20_FRAM_TOTAL_LEN_MIN - GH20_FM_END],
            dat[dat[GH20_FRAM_LEN_INDEX] + GH20_FRAM_TOTAL_LEN_MIN - 1]);
        return -1;
    }

    //check len
    /*
    if (dat[GH20_FRAM_LEN_INDEX] > GH20_RX_FRAME_LEN_MAX || len < 0
        || dat[GH20_FRAM_LEN_INDEX] + GH20_FRAM_TOTAL_LEN_MIN > len)
    {
        return -1;
    }
    */

    //check frame dirt
    if (dat[GH20_FM_HEAD + GH20_FM_TS] != GH_PT_DIRT_G_H)
    {
        logger(LOG_ERR, "data format err");
        return -1;
    }

    //check frame cmd
    bool cmdcheck = false;
    if (dat[GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT] == GH_PT_CMD_SET_G_CHAN
        || dat[GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT] == GH_PT_CMD_GET_G_CHAN
        || dat[GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT] == GH_PT_CMD_SET_S_CHAN
        || dat[GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT] == GH_PT_CMD_CHECK_S_CHAN
        || dat[GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT] == GH_PT_CMD_SET_S_CONF
        || dat[GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT] == GH_PT_CMD_GET_S_CONF)
    {
        cmdcheck = true;
    }
    else if (dat[GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT] == GH_PT_CMD_GET_S_DAT_STATIC
        || dat[GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT] == GH_PT_CMD_REP_S_DAT_STATIC
        || dat[GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT] == GH_PT_CMD_GET_S_DAT_RT_START
        || dat[GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT] == GH_PT_CMD_REP_S_DAT_RT
        || dat[GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT] == GH_PT_CMD_GET_S_DAT_RT_STOP
        || dat[GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT] == GH_PT_CMD_SYNC_TS)
    {
        cmdcheck = true;
    }
    if (!cmdcheck)
    {
        logger(LOG_ERR, "data format err");
        return -1;
    }

    //check checksum
    checksum = 0;
    for (int i = GH20_FM_HEAD; i < dat[GH20_FRAM_LEN_INDEX] + GH20_FRAM_TOTAL_LEN_MIN - GH20_FM_END - GH20_FM_CHECKSUM; i++)
    {
        checksum += dat[i];
    }
    if (checksum != dat[dat[GH20_FRAM_LEN_INDEX] + GH20_FRAM_TOTAL_LEN_MIN - GH20_FM_END - GH20_FM_CHECKSUM])
    {
        logger(LOG_ERR, "data format err");
        return -1;
    }

    return dat[GH20_FRAM_LEN_INDEX] + GH20_FRAM_TOTAL_LEN_MIN;
}


void print_data_group(uint8_t *data_grp, uint8_t len)
{
    char *accXs, *accYs, *accZs;
    int i,num;

    for (uint8_t i = 0; i < len; i++)
    {
        printf("%02x ", data_grp[i]);
    }
    //print json
    if (len % 6 != 0)
    {
        logger(LOG_ERR, "oooooooowave div 6 err, len=%d",len);
        return;
    }
    num = len/6;

    accXs = GW_MALLOC(num * 20);
    accYs = GW_MALLOC(num * 20);
    accZs = GW_MALLOC(num * 20);

    for (i=0; i<len; i+=6) {
        if (i == 0) {
            sprintf(accXs, "%.2f", get_u16_r(&data_grp[i]) * 9.8 / 1000.0);
            sprintf(accYs, "%.2f", get_u16_r(&data_grp[i+2]) * 9.8 / 1000.0);
            sprintf(accZs, "%.2f", get_u16_r(&data_grp[i+4]) * 9.8 / 1000.0);
        } else {
            sprintf(accXs + strlen(accXs), ",%.2f", get_u16_r(&data_grp[i]) * 9.8 / 1000.0);
            sprintf(accYs + strlen(accYs), ",%.2f", get_u16_r(&data_grp[i+2]) * 9.8 / 1000.0);
            sprintf(accZs + strlen(accZs), ",%.2f", get_u16_r(&data_grp[i+4]) * 9.8 / 1000.0);
        }
    }

    printf("\r\n accX:%s,,,,,,,,,accY:%s,,,,,,,,,accZ:%s \r\n", accXs, accYs, accZs);

    accXs = GW_MALLOC(num * 20);
    accYs = GW_MALLOC(num * 20);
    accZs = GW_MALLOC(num * 20);





}

/*==============================================================================================*/
/*==============================================================================================*/
/*=====================              end of               sub1g          =========================*/
/*==============================================================================================*/
/*==============================================================================================*/

