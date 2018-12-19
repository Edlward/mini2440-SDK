#include <common.h>
#include <s3c2410.h>

#define BUSY            1

#define NAND_SECTOR_SIZE    512
#define NAND_BLOCK_MASK     (NAND_SECTOR_SIZE - 1)

#define NAND_SECTOR_SIZE_LP    2048
#define NAND_BLOCK_MASK_LP     (NAND_SECTOR_SIZE_LP - 1)

void nand_init_ll(void);
void nand_read_ll(unsigned char *buf, unsigned long start_addr, int size);

static void nand_reset(void);
static void wait_idle(void);
static void nand_select_chip(void);
static void nand_deselect_chip(void);
static void write_cmd(int cmd);
static void write_addr(unsigned int addr);
static unsigned char read_data(void);

static void s3c2440_nand_reset(void);
static void s3c2440_wait_idle(void);
static void s3c2440_nand_select_chip(void);
static void s3c2440_nand_deselect_chip(void);
static void s3c2440_write_cmd(int cmd);
static void s3c2440_write_addr(unsigned int addr);
static unsigned char s3c2440_read_data(void);

static void s3c2440_nand_reset(void)
{
    s3c2440_nand_select_chip();
    s3c2440_write_cmd(0xff);  // 复位命令
    s3c2440_wait_idle();
    s3c2440_nand_deselect_chip();
}

static void s3c2440_wait_idle(void)
{
    int i;
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFSTAT;

    while(!(*p & BUSY))
        for(i=0; i<10; i++);
}

static void s3c2440_nand_select_chip(void)
{
    int i;
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;

    s3c2440nand->NFCONT &= ~(1<<1);
    for(i=0; i<10; i++);    
}


static void s3c2440_nand_deselect_chip(void)
{
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;

    s3c2440nand->NFCONT |= (1<<1);
}

/* 发出命令 */
static void s3c2440_write_cmd(int cmd)
{
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;

    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFCMD;
    *p = cmd;
}

/* 发出地址 */
static void s3c2440_write_addr(unsigned int addr)
{
    int i;
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFADDR;
    
    *p = addr & 0xff;
    for(i=0; i<10; i++);
    *p = (addr >> 9) & 0xff;
    for(i=0; i<10; i++);
    *p = (addr >> 17) & 0xff;
    for(i=0; i<10; i++);
    *p = (addr >> 25) & 0xff;
    for(i=0; i<10; i++);
}


/* 发出地址 */
static void s3c2440_write_addr_lp(unsigned int addr)
{
    int i;
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFADDR;
	int col, page;

	col = addr & NAND_BLOCK_MASK_LP;
	page = addr / NAND_SECTOR_SIZE_LP;
	
    *p = col & 0xff;			/* Column Address A0~A7 */
    for(i=0; i<10; i++);		
    *p = (col >> 8) & 0x0f;		/* Column Address A8~A11 */
    for(i=0; i<10; i++);
    *p = page & 0xff;			/* Row Address A12~A19 */
    for(i=0; i<10; i++);
    *p = (page >> 8) & 0xff;	/* Row Address A20~A27 */
    for(i=0; i<10; i++);
    *p = (page >> 16) & 0x03;	/* Row Address A28~A29 */
    for(i=0; i<10; i++);
}

/* 读取数据 */
static unsigned char s3c2440_read_data(void)
{
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFDATA;
    return *p;
}

static void nand_reset(void)
{
	s3c2440_nand_reset();
}

static void wait_idle(void)
{
	s3c2440_wait_idle();
}

static void nand_select_chip(void)
{
	s3c2440_nand_select_chip();
}

static void nand_deselect_chip(void)
{
	s3c2440_nand_deselect_chip();
}

static void write_cmd(int cmd)
{
	s3c2440_write_cmd(cmd);
}

static void write_addr(unsigned int addr)
{
	s3c2440_write_addr(addr);
}

static void write_addr_lp(unsigned int addr)
{
	s3c2440_write_addr_lp(addr);
}

static unsigned char read_data(void)
{
	return s3c2440_read_data();
}






void nand_read_ll_lp(unsigned char *buf, unsigned long start_addr, int size)
{
    int i, j;
    
    if ((start_addr & NAND_BLOCK_MASK_LP) || (size & NAND_BLOCK_MASK_LP)) {
        return ;    /* 地址或长度不对齐 */
    }

    /* 选中芯片 */
    nand_select_chip();

    for(i=start_addr; i < (start_addr + size);) {
      /* 发出READ0命令 */
      write_cmd(0);

      /* Write Address */
      write_addr_lp(i);
	  write_cmd(0x30);
      wait_idle();

      for(j=0; j < NAND_SECTOR_SIZE_LP; j++, i++) {
          *buf = read_data();
          buf++;
      }
    }

    /* 取消片选信号 */
    nand_deselect_chip();
    
    return ;
}

static void nand_init_ll(void)
{
	S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;

#define TACLS   0
#define TWRPH0  3
#define TWRPH1  0

		/* 设置时序 */
        s3c2440nand->NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
        /* 使能NAND Flash控制器, 初始化ECC, 禁止片选 */
        s3c2440nand->NFCONT = (1<<4)|(1<<1)|(1<<0);

	/* 复位NAND Flash */
	nand_reset();
}


static int is_boot_from_nor(void)
{
	volatile unsigned int *pdw = (volatile unsigned int *)0;
	unsigned int dwVal;

	dwVal = *pdw;       
	*pdw = 0x12345678;
	if (*pdw != 0x12345678)
	{
		return 1;
	}
	else
	{
		*pdw = dwVal;
		return 0;
	}
}

int copy_code_to_ram(unsigned long start_addr, unsigned char *buf, int size)
{
	unsigned int *pdwDest;
	unsigned int *pdwSrc;
	int i;

	if(is_boot_from_nor())
	{
		pdwDest = (unsigned int *)buf;
		pdwSrc  = (unsigned int *)start_addr;

		for (i = 0; i < size / 4; i++)
        	{
	           pdwDest[i] = pdwSrc[i];
        	}
	        return 0;
	}
	else
	{
		// from nand
		nand_init_ll();
		nand_read_ll_lp(buf, start_addr, (size + NAND_BLOCK_MASK_LP)&~(NAND_BLOCK_MASK_LP));
		return 0;
	}
}
