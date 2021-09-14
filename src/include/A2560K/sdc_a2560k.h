/*
 * Definitions for access to the SDC controller
 */

#ifndef __SDC_A2560K_H
#define __SDC_A2560K_H

// SDC_TRANS_TYPE_REG
#define SDC_TRANS_DIRECT      0x00   // 00 = Direct Access
#define SDC_TRANS_INIT_SD     0x01   // 01 = Init SD
#define SDC_TRANS_READ_BLK    0x02   // 10 = RW_READ_BLOCK (512 Bytes)
#define SDC_TRANS_WRITE_BLK   0x03   // 11 = RW_WRITE_SD_BLOCK

// SDC_TRANS_CONTROL_REG
#define SDC_TRANS_START       0x01
// SDC_TRANS_STATUS_REG
#define SDC_TRANS_BUSY        0x01   //  1= Transaction Busy
// SDC_TRANS_ERROR_REG
#define SDC_TRANS_INIT_NO_ERR   0x00   // Init Error Report [1:0]
#define SDC_TRANS_INIT_CMD0_ERR 0x01
#define SDC_TRANS_INIT_CMD1_ERR 0x02

#define SDC_TRANS_RD_NO_ERR     0x00   // Read Error Report [3:2]
#define SDC_TRANS_RD_CMD_ERR    0x04
#define SDC_TRANS_RD_TOKEN_ERR  0x08

#define SDC_TRANS_WR_NO_ERR     0x00   // Write Report Error  [5:4]
#define SDC_TRANS_WR_CMD_ERR    0x10
#define SDC_TRANS_WR_DATA_ERR   0x20
#define SDC_TRANS_WR_BUSY_ERR   0x30

#define SDC_VERSION_REG         ((unsigned char *)0x00C00300)
#define SDC_CONTROL_REG         ((unsigned char *)0x00C00301)
#define SDC_TRANS_TYPE_REG      ((unsigned char *)0x00C00302)

#define SDC_TRANS_CONTROL_REG   ((unsigned char *)0x00C00303)
#define SDC_TRANS_STATUS_REG    ((unsigned char *)0x00C00304)
#define SDC_TRANS_ERROR_REG     ((unsigned char *)0x00C00305)
#define SDC_DIRECT_ACCESS_REG   ((unsigned char *)0x00C00306)
#define SDC_SD_ADDR_7_0_REG     ((unsigned char *)0x00C00307)
#define SDC_SD_ADDR_15_8_REG    ((unsigned char *)0x00C00308)
#define SDC_SD_ADDR_23_16_REG   ((unsigned char *)0x00C00309)
#define SDC_SD_ADDR_31_24_REG   ((unsigned char *)0x00C0030A)

#define SDC_SPI_CLK_DEL_REG     ((unsigned char *)0x00C0030B)

#define SDC_RX_FIFO_DATA_REG    ((unsigned char *)0x00C00310)
#define SDC_RX_FIFO_DATA_CNT_HI ((unsigned char *)0x00C00312)
#define SDC_RX_FIFO_DATA_CNT_LO ((unsigned char *)0x00C00313)
#define SDC_RX_FIFO_CTRL_REG    ((unsigned char *)0x00C00314)

#define SDC_TX_FIFO_DATA_REG    ((unsigned char *)0x00C00320)
#define SDC_TX_FIFO_CTRL_REG    ((unsigned char *)0x00C00324)

#endif