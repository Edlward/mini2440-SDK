/*
* s3c2440 nand api
* copy from linux-2.6.13 drivers/mtd/nand/s3c2410.c
*/

#include <common.h>

#if (CONFIG_COMMANDS & CFG_CMD_NAND) && !defined(CFG_NAND_LEGACY)
#include <s3c2410.h>
#include <nand.h>

DECLARE_GLOBAL_DATA_PTR;

#define S3C2410_NFSTAT_READY            (1 << 0)
#define S3C2410_NFCONF_nFCE             (1 << 1)

#define S3C2440_NFSTAT_READY            (1 << 0)
#define S3C2440_NFCONT_nFCE             (1 << 1)


static void s3c2440_nand_select_chip(struct mtd_info *mtd, int chip)
{
        S3C2440_NAND * const s3c2440nand = S3C2440_GetBase_NAND();

        if(chip == 1)
                s3c2440nand->NFCONT |= S3C2440_NFCONT_nFCE;
        else
                s3c2440nand->NFCONT &= ~S3C2440_NFCONT_nFCE;
}
static void s3c2440_nand_hwcontrol(struct mtd_info *mtd, int cmd)
{
        S3C2440_NAND * const s3c2440nand = S3C2440_GetBase_NAND();
        struct nand_chip *chip = mtd->priv;

        switch(cmd)
        {
                case NAND_CTL_SETNCE:
                case NAND_CTL_CLRNCE:
                        break;
                case NAND_CTL_SETCLE:
                        chip->IO_ADDR_W = (void *)&s3c2440nand->NFCMD;
                        break;
                case NAND_CTL_SETALE:
                        chip->IO_ADDR_W = (void *)&s3c2440nand->NFADDR;
                        break;
                default:
                        chip->IO_ADDR_W = (void *)&s3c2440nand->NFDATA;
                        break;
        }
}
static int s3c2440_nand_devready(struct mtd_info *mtd)
{
        S3C2440_NAND * const s3c2440nand = S3C2440_GetBase_NAND();

        return (s3c2440nand->NFSTAT & S3C2440_NFSTAT_READY);
}

static void s3c24x0_nand_inithw(void)
{
#define TACLS   0
#define TWRPH0  4
#define TWRPH1  2
        S3C2440_NAND * const s3c2440nand = S3C2440_GetBase_NAND();

        s3c2440nand->NFCONF = (TACLS << 12) | (TWRPH0 << 8) | (TWRPH1 << 4);
        s3c2440nand->NFCONT = (1 << 4 )| (0 << 1) |(1 << 0);
}

void board_nand_init(struct nand_chip *chip)
{
        S3C2440_NAND * const s3c2440nand = S3C2440_GetBase_NAND();

        s3c24x0_nand_inithw();

        chip->IO_ADDR_R = (void *) &s3c2440nand->NFDATA;
        chip->IO_ADDR_W = (void *) &s3c2440nand->NFDATA;
        chip->hwcontrol = s3c2440_nand_hwcontrol;
        chip->dev_ready = s3c2440_nand_devready;
        chip->select_chip = s3c2440_nand_select_chip;
        chip->options = 0;

        chip->eccmode = NAND_ECC_SOFT;
}

#endif

