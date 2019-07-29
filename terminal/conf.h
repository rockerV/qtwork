#ifndef CONF_H
#define CONF_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

/*****************************************************************************************/
/*****************************************************************************************/
/**********                   conf                                   *********************/
/*****************************************************************************************/
/*****************************************************************************************/
#define LOG_DEBUG 7
#define LOG_ERR 3
#define LOG_INFO 6

void _logger(char *filename, const char* funcname, int line, int level, char* fmt, ...);

#define logger(level, format...) _logger(__FILE__,__FUNCTION__, __LINE__, level, format)

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
/*********************************************/
/* system common interface */
#define GW_MALLOC malloc
#define GW_FREE free

/*********************************************/
/* sensor devices num */
#define SENSOR_NUM_MAX 128
#define SENSOR_SN_LEN_MAX 32

/*********************************************/
/* NORMAL FUNTIONS */
#define CHAR_2_UINT16_BIG_ENDIAN(c) ((c)[0]<<8 + (c)[1])
#define CHAR_2_UINT16_LITTLE_ENDIAN(c) ((c)[1]<<8 + (c)[0])

/* 把字符串s转换成%02x格式输出到x */
int trans_string_2_02x(char *s, char *x, int sizex);
/* 把char型数组c转换成%02x格式输出到x */
int trans_char_2_02x(char *c, int sizec, char *x, int sizex);

/* 把字符串当十进制转换成数据，'123'->123 */
int trans_string_2_int32(char *s, int *val);

/* 从字符串最后index_end里提取出转换为uint16 */
uint16_t get_uint16_from_str_end(char *strin, int index_end);


uint16_t get_u16(uint8_t* data);
int16_t get_u16_r(uint8_t* data);
uint32_t get_u32(uint8_t* data);
int u16_to_bytes(uint8_t* data, uint16_t value);
int u32_to_bytes(uint8_t* data, uint32_t value);
uint32_t get_packet_bytes(uint8_t* data, uint8_t len);

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

#define GH20_RX_BUFF_MAX 1280
#define GH20_TX_BUFF_MAX 128
#define GH20_RX_FRAME_CONF_LEN_MAX 33
#define GH20_RX_FRAME_WAVE_LEN_MAX 128
#define GH20_RX_FRAME_LEN_MAX (GH20_RX_FRAME_WAVE_LEN_MAX + GH20_RX_FRAME_CONF_LEN_MAX)


#define GH20_WAVE_LEN_MAX (4000*3*6+1024)

#define GH20_CMD_RETRY_MAX 3

#define GH20_UART_TIMEOUT_MS_BASIC 500
#define GH20_UART_TIMEOUT_MS_WORK 100
#define GH20_UART_TIMEOUT_MS_GW 500

enum GH20_PROTOCOL_TIMEOUT_VAL {
    GH20_TIMEOUT_1000MS = 1000,
};


enum GH20_CHECK_GW_SUB_STEP{
    GH20_CHECK_GW_STEP_GET_CH_START = 0,
    GH20_CHECK_GW_STEP_GET_CH,
    GH20_CHECK_GW_STEP_SET_CH_START,
    GH20_CHECK_GW_STEP_SET_CH,
};


enum GH20_GET_CONF_SUB_STEP{
    GH20_GET_CONF_STEP_GET_START = 0,
    GH20_GET_CONF_STEP_GET,
    GH20_GET_CONF_STEP_SYNC_START,
    GH20_GET_CONF_STEP_SYNC,
    GH20_GET_CONF_STEP_CHANGE_CONF_START,
    GH20_GET_CONF_STEP_CHANGE_CONF,
    GH20_GET_CONF_STEP_GET_AGAIN_START,
    GH20_GET_CONF_STEP_GET_AGAIN,
};

enum GH20_SET_CHANNEL_SUB_STEP{
    GH20_SET_CH_STEP_G_BASE = 0,
    GH20_SET_CH_STEP_S_WORK_START,
    GH20_SET_CH_STEP_S_WORK,
    GH20_SET_CH_STEP_G_WORK_START,
    GH20_SET_CH_STEP_G_WORK,
    GH20_SET_CH_STEP_S_WORK_CHECK_START,
    GH20_SET_CH_STEP_S_WORK_CHECK,
};

enum GH20_READ_STATIC_WAVE_SUB_STEP{
    GH20_READ_WAVE_STEP_GET_START = 0,
    GH20_READ_WAVE_STEP_GET,
    GH20_READ_WAVE_STEP_WAITTING,
    GH20_READ_WAVE_STEP_ACK_START,
};

enum GH20_READ_REAL_WAVE_SUB_STEP{
    GH20_READ_REAL_STEP_NULL = 0,
    GH20_READ_REAL_STEP_GET_START,
    GH20_READ_REAL_STEP_GET,
    GH20_READ_REAL_STEP_WORKING,
    GH20_READ_REAL_STEP_STOP_START,
    GH20_READ_REAL_STEP_STOP,
};


enum GH20_PROTOCOL_VAL {

    GH_PT_CMD_NULL = 0,


    /* define gh sensor protocol data */
    //head
    GH_PT_HEAD_0 = 0x55,
    GH_PT_HEAD_1 = 0xAA,

    //data direction
    //H_G means host -> 1310gataway(receiver)
    //G_S means 1310gataway(receiver) -> 1310sensor
    GH_PT_DIRT_H_G = 0x01,
    GH_PT_DIRT_G_H = 0x10,
    GH_PT_DIRT_G_S = 0x12,
    GH_PT_DIRT_S_G = 0x21,

    //data CMD
    GH_PT_CMD_SET_G_CHAN = 0x01,
    GH_PT_CMD_GET_G_CHAN = 0x02,
    GH_PT_CMD_SET_S_CHAN = 0x10,
    GH_PT_CMD_CHECK_S_CHAN = 0x11,
    GH_PT_CMD_SET_S_CONF = 0x12,
    GH_PT_CMD_GET_S_CONF = 0x13,
    GH_PT_CMD_GET_S_DAT_STATIC = 0x14,
    GH_PT_CMD_REP_S_DAT_STATIC = 0x15,
    GH_PT_CMD_GET_S_DAT_RT_START = 0x16,
    GH_PT_CMD_REP_S_DAT_RT = 0x17,
    GH_PT_CMD_GET_S_DAT_RT_STOP = 0x18,
    GH_PT_CMD_SYNC_TS = 0x19,

    //data END
    GH_PT_END_0 = 0xAB,
    GH_PT_END_1 = 0xEF,
};


enum GH20_FRAM_LEN {
    GH20_FM_HEAD     = 2,
    GH20_FM_TS      = 1,
    GH20_FM_DIRT     = 1,
    GH20_FM_CMD      = 1,
    GH20_FM_LEN   = 1,
    GH20_FM_CHECKSUM = 1,
    GH20_FM_END      = 2,
};
#define GH20_FRAM_TOTAL_LEN_MIN (GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT + GH20_FM_CMD + GH20_FM_LEN + GH20_FM_CHECKSUM + GH20_FM_END)
#define GH20_FRAM_LEN_INDEX (GH20_FM_HEAD + GH20_FM_TS + GH20_FM_DIRT + GH20_FM_CMD)
#define GH20_FRAM_CRC_STATIC_LEN (GH20_FM_TS + GH20_FM_DIRT + GH20_FM_CMD + GH20_FM_LEN)


enum GH20_WAVE_SEND_FRAME_STAT {
    WAVE_FRAME_SEND_OK     = 0,
    WAVE_FRAME_SEND_RETRY = 1,//NOT USED NOW
    WAVE_FRAME_SEND_ABORT =2,
};
enum GH20_WAVE_FRAME_STAT {
    WAVE_FRAME_END	  = 0,
    WAVE_FRAME_CONTINUE = 1,
    WAVE_FRAME_ABORT =2,
    WAVE_FRAME_NO_VIB_DATA =5,
};

enum GH20_TASK_STAT {
    GH20_TASK_NULL = 0,
    GH20_TASK_SET_CH,//not called by app
    GH20_TASK_READ_REALTIME_WAVE,
    GH20_TASK_CONN_CHECK,
    GH20_TASK_READ_STATIC_WAVE,
    GH20_TASK_CHECK_GW,
};

enum GH20_GW_CHANNEL {
    GH20_GW_CHANNEL_MIN     = 1,
    GH20_GW_CHANNEL_BASE_868M      = 26,
    GH20_GW_CHANNEL_MAX     = 51,
};

enum GH20_GW_SPEED {
    GH20_GW_SPEED_20K = 0,
    GH20_GW_SPEED_50K,
    GH20_GW_SPEED_100K,
    GH20_GW_SPEED_150K,
    GH20_GW_SPEED_200K,
    GH20_GW_SPEED_250K,
    GH20_GW_SPEED_300K,
    GH20_GW_SPEED_350K,
    GH20_GW_SPEED_400K,
    GH20_GW_SPEED_450K,
    GH20_GW_SPEED_500K,
};

enum GH20_CMD_ACK {
    GH20_CMD_ACK_OK = 0,
    GH20_CMD_ACK_BUSY = 0x11,
};

#define GH20_GW_SPEED_CONFIG GH20_GW_SPEED_200K
#define GH20_GW_SPEED_DEFAULT GH20_GW_SPEED_200K


#define GH20_SENSOR_SLEEP_TIME 3000
#define GH20_SENSOR_WAIT_CMD_TIME 100

#define GH20_GW_RESP_TIMEOUT 1000
#define GH20_GW_CHECK_S_TIMEOUT 1000


#define GH20_SEND_CMD_LEN_MAX 64


/*************************************/
#define MAX_TASK_DEEP 10

typedef struct task_status
{
    int father_task;
    int father_task_step;
    int father_timeout;
    int child_task;
    int child_task_ret;
}task_status_t;
typedef struct task_queue
{
    task_status_t cells[MAX_TASK_DEEP];
    int cnt;
}s_queue_t;
/*--------------------------------------*/


typedef struct gh20_proc_status
{
    uint32_t addr;
    uint64_t conn_ts; //if get connection ok, mark this ts, used to mark the connection last time
    uint64_t last_ts;	// when host send cmd, mark this ts, used to check if cmd timeout
    //int cmd_status;	// cmd status, like GH_PT_CMD_SET_G_CHAN, GH_PT_CMD_SET_S_CONF and so on.
    //int cmd_status_sub;//for work step in every proc
//	int proc_status; // proc status,
//	int task_status; //
    bool channel_is_set;//channel is set onece or connect is creat, not need to set channel
    bool conf_is_unequ;	//if config read from sensor is equal to the local config of gateway.
    bool is_connected;//
    int retry_cnt;
    int frame_ts;	// the frame ts, used to check if the frame received is the expected cmd
    int cmd_send;
    int cmd_expect;

    int timeout;
    int task;
    int task_step;
    int task_child_ret;
    s_queue_t father_task_queue;

    char data_send[GH20_SEND_CMD_LEN_MAX];//data send to gateway
    int data_used_len;

}gh20_proc_status_t;



typedef struct gh20_gw_para {
    uint8_t channel;
    uint8_t speed;

    //task info
    uint32_t task_realtime_addr;


}gh20_gw_para_t;


typedef struct gh20_wave {
    uint8_t data_type;//0:vib wake data  1: time out data
    uint8_t fm_status_send_now;
    uint16_t fm_idx_now;
    uint16_t fm_idx_ok;
    uint16_t fm_len;
    uint16_t fm_total;
    uint32_t pos;
    uint32_t wave_len;
    uint8_t wave_status;
    uint8_t *wave_data;
    uint64_t ts;
    uint8_t retry_times;
}gh20_wave_t;

typedef struct gh20_para {
    uint32_t addr;
    char sn[SENSOR_SN_LEN_MAX];

    //sensor web config
    int cmd_status;
    int freq;
    int period;
    int sleep_time;//sub1g gaohua  3000ms
    int wait_cmd_time;//sub1g gaohua  100ms
    int work_time;
    int collect_condition;
    int vib_wake_thr;
    int vib_wake_delay;

    //config read from sensor
    uint64_t sensor_ts_sync;
    uint32_t rd_sensor_ts;
    int rd_sleep_time;
    int rd_wait_cmd_time;
    int rd_collect_condition;
    int rd_freq;
    int rd_work_time;
    int rd_vib_wake_thr;
    int rd_vib_wake_delay;
    int rd_vib_data_exist;
    int rd_accx;//mG
    int rd_accy;
    int rd_accz;
    int rd_voltage;
    int rd_temperature;
    int rd_ack;

    //read wave info
    gh20_wave_t wave;

    //task connction ts save
    uint64_t conn_ts;

    //task sensor data
    uint64_t start_ts;
    uint64_t start_ts_bak;	// if task is ok, do : start_ts = start_ts_bak
    bool task_get_connect_status;

    bool task_set_channel;	// need change the net set
    uint8_t task_realtime_wave_control;//0:nothing 1:start 2:stop

    //used for debug
    int count_start;
    int count_ok;
} gh20_para_t;

typedef struct{
    uint8_t ack;
}gh20_set_g_ch_ack_t;
typedef struct{
    uint8_t channel;
    uint8_t speed;
}gh20_get_g_ch_t;
typedef struct{
    uint32_t addr;
    uint8_t ack;
}gh20_set_s_ch_ack_t;
typedef struct{
    uint32_t addr;
    uint8_t channel;
    uint8_t speed;
    uint8_t ack;
}gh20_check_s_ch_ack_t;
typedef struct{
    uint32_t addr;
    uint8_t ack;
}gh20_set_s_conf_ack_t;
typedef struct{
    uint32_t addr;
    uint8_t ack;
}gh20_sync_s_ack_t;
typedef struct{
    uint32_t addr;
    uint32_t ts;
    uint16_t sleep_time;
    uint16_t wait_cmd_time;
    uint8_t collect_condition;
    uint8_t freq;
    uint16_t work_time;
    uint16_t vib_wake_thr;
    uint16_t vib_wake_delay;
    uint8_t vib_data_exist;
    uint16_t accx;
    uint16_t accy;
    uint16_t accz;
    uint16_t voltage;
    uint16_t temperature;
    uint8_t ack;
}gh20_get_s_conf_t;
typedef struct{
    uint32_t addr;
    uint8_t ack;
}gh20_get_s_wave_ack_t;
typedef struct{
    uint32_t addr;
    uint16_t frame_No;
    uint8_t data_type;
    uint32_t ts;
    uint16_t frame_total_cnt;
    uint8_t frame_status;
    uint8_t wave_dat[GH20_RX_FRAME_LEN_MAX];
    uint8_t wave_len_this;//not in the frame, calc by self
}gh20_get_s_wave_t;
typedef struct{
    uint32_t addr;
    uint8_t ack;
}gh20_get_s_wave_realtime_ack_t;
typedef struct{
    uint32_t addr;
    uint8_t frame_No;
    uint8_t frame_status;
    uint8_t wave_dat[GH20_RX_FRAME_LEN_MAX];
    uint8_t wave_len_this;//not in the frame, calc by self
}gh20_get_s_wave_realtime_t;
typedef struct{
    uint32_t addr;
    uint8_t ack;
}gh20_stop_s_wave_realtime_ack_t;


typedef struct gh20_frame {
    uint8_t frame_ts;
    uint8_t dirt;
    uint8_t cmd;
    uint8_t dat_len;
    //uint8_t* dat;
    uint8_t checksum;

    union{
        gh20_set_g_ch_ack_t set_g_ch_ack;
        gh20_get_g_ch_t get_g_ch;
        gh20_set_s_ch_ack_t set_s_ch_ack;
        gh20_check_s_ch_ack_t check_s_ch_ack;
        gh20_set_s_conf_ack_t set_s_conf_ack;
        gh20_sync_s_ack_t sync_s_ack;
        gh20_get_s_conf_t get_s_conf;
        gh20_get_s_wave_ack_t get_s_wave_ack;
        gh20_get_s_wave_t get_s_wave;
        gh20_get_s_wave_realtime_ack_t get_s_wave_realtime_ack;
        gh20_get_s_wave_realtime_t get_s_wave_realtime;
        gh20_stop_s_wave_realtime_ack_t stop_s_wave_realtime;
    } data_paket;

} gh20_frame_t;



int check_frame_valid(uint8_t *dat);
void print_data_group(uint8_t *data_grp, uint8_t len);
/*==============================================================================================*/
/*==============================================================================================*/
/*=====================              end of               sub1g          =========================*/
/*==============================================================================================*/
/*==============================================================================================*/



#ifdef __cplusplus
}
#endif

#endif
