/*
 * (C) Copyright 2008-2014 Rockchip Electronics
 *
 * Configuation settings for the rk3xxx chip platform.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#ifndef RKIDBLOCK_H
#define RKIDBLOCK_H

#include <fastboot.h>
#include "../config.h"

extern BootInfo gBootInfo;

#ifndef __GNUC__
#define PACKED1 __packed
#define PACKED2
#else
#define PACKED1
#define PACKED2 __attribute__((packed))
#endif


/* �������صĴ����� */
#define ERR_SUCCESS			0
#define ERR_DEVICE_READY		ERR_SUCCESS
#define ERR_DEVICE_OPEN_FAILED		-1
#define ERR_DEVICE_WRITE_FAILED		-2 
#define ERR_DEVICE_READ_FAILED		-3
#define ERR_CMD_NOTMATCH		-4
#define ERR_DEVICE_UNREADY		-5
#define ERR_DEVICE_SET_FAILED		-6
#define ERR_FOUND_BAD_BLOCK		-7
#define ERR_FAILED			-8
#define ERR_CROSS_BORDER		-9
#define ERR_CSW_OPEN_FAILED		-10


#define FLASH_ID_LEN			5
#define BLOCK_STATE_BYTES		64
#define MAX_TEST_BLOCK			512		//һ�οɲ��Ե�������
#define MAX_ERASE_BLOCK			128						//һ�οɲ�����������

#define SECTOR_SIZE			512
#define MLC_SECTOR_SIZE			528
#define SLC_SECTOR_SIZE			SECTOR_SIZE
#define MAX_RW_SECTOR			20	// һ�οɶ�д�����������
#define MAX_MANUFACTURER_NAME		16
#define MAX_FLASH_NUMBER		8

#define CELL_SLC			0
#define CELL_MLC			1

#define MAX_FW_SIZE			(64 * 1024 - 1)
#define DEVICE_TRY_COUNT		5

#define IOCTL_TRANSFER_SIZE		4096
#define IDB_BLOCKS	5
#define EIB_BLOCKS	5
#define RESERVE_BLOCKS	2

#define MAX_TRY_COUNT		20	// ����20�ξ͹���
#define MAX_BLOCK_STATE		512
#define MAX_BLOCK_SEARCH 	200

#define MAX_WRITE_SECTOR	20

#define UINT    unsigned int
#define UCHAR   unsigned char
#define USHORT  unsigned short
#define BYTE   unsigned char
#define PBYTE   BYTE*
#define LPBYTE	BYTE*

PACKED1 struct _Sector0Info{			//�ܹ�512Bytes
	UINT	fwSig;
	UCHAR	reserved[8];
	USHORT	usBootCode1Offset;
	USHORT	usBootCode2Offset;
	UCHAR	reserved1[490];
	USHORT  usFlashDataSize;//����Ϊ��λ
	USHORT	ucFlashBootSize;
	UCHAR	reserved2[2];
}PACKED2;

typedef	struct _Sector0Info Sector0Info;

typedef PACKED1 struct _Sector1Info{
	USHORT  usSysReservedBlock;                  // 2 bytes
	USHORT  usDisk0Size;					// 2 bytes
	USHORT  usDisk1Size;					// 2 bytes
	USHORT  usDisk2Size;					// 2 bytes
	USHORT  usDisk3Size;					// 2 bytes
	UINT	uiChipTag;
	UINT	uiMachineId;
	USHORT	usLoaderYear;
	USHORT	usLoaderDate;
	USHORT	usLoaderVer;				// Master and slave version
	UCHAR   reserved[72];
	USHORT  usFlashDataOffset;
	USHORT  usFlashDataLen;             //��SectorΪ��λ
	UCHAR	reserved2[384];
	UINT    uiFlashChipSize; //��SectorΪ��λ
	UCHAR   reserved1;
	UCHAR   bAccessTime;
	USHORT  usPhyBlockSize;
	UCHAR   bPhyPageSize;
	UCHAR   bECCBits;

	BYTE	reserved3[8];
	USHORT  usIdBlock0;
	USHORT  usIdBlock1;
	USHORT  usIdBlock2;
	USHORT  usIdBlock3;
	USHORT  usIdBlock4;
}PACKED2 Sector1Info;

typedef PACKED1 struct _Sector2Info{
	USHORT  chipInfoSize;                        
	UCHAR   chipInfo[510];					
}PACKED2 Sector2Info;

#define TAG_MANUFACTURER	"M.F.T"
#define TAG_PRODUCT_SERIES	"PROD_SERIES"
#define TAG_PRODUCT		"PRODUCT"
#define TAG_SUB_PRODUCT		"SUB_PROD"
#define TAG_MACHINE_SN		"SN"

#define SN_MAX_SIZE		30
#define SEC3_RESERVED_SIZE 	435
#define UID_MAX_SIZE 		30
#define BT_MAX_SIZE 		6
#define MAC_MAX_SIZE 		6

typedef PACKED1 struct _Sector3Info{
	USHORT  snSize;  
	UCHAR   sn[SN_MAX_SIZE];
	UCHAR   macTag[3];
	UCHAR	macSize;
	UCHAR	macAddr[6];					
}PACKED2 Sector3Info;

typedef UCHAR Sector[512];
typedef UCHAR Spare[16];

typedef PACKED1 struct _IDBlock{
	Sector0Info sector0;
	Sector1Info sector1;
	Sector		sector2;
	Sector		sector3;
	UCHAR		SDRAM_Initial[512];
	UCHAR*		flashBoot;
}PACKED2 IDBlock;

typedef PACKED1 struct _DataInfo{
	BOOL 	bIsExist;		// 0,�����ݲ����ڣ�1,����
	int 	iOffset;
	int 	iLength;
	UINT 	uiRAMAddress;
}PACKED2 DataInfo;

typedef PACKED1 struct _ManufacturerInfo{
	UCHAR	manufacturerID;
	char	manufacturerName[MAX_MANUFACTURER_NAME];
}PACKED2 ManufacturerInfo;


typedef	PACKED1 struct _FlashID
{
	UCHAR makerCode;
	UCHAR deviceCode;
	UCHAR cellType; // 0,512 bytes ;1,2024 bytes; 2,2048 bytes
	UCHAR flashType;
	UCHAR reserved2;
}PACKED2 FlashID;

/* Flash ��Ϣ */
typedef	PACKED1 struct _FlashInfo
{
	char szManufacturerName[MAX_MANUFACTURER_NAME];
	UINT uiFlashSize;		//MB
	USHORT usBlockSize;		//KB
	UINT uiPageSize;		//KB
	UINT uiSectorPerBlock;
	//	UCHAR *BlockState;
	UCHAR   BlockState[200];
	UINT	uiBlockNum;
	BYTE	bECCBits;
	BYTE	bAccessTime;		// ���η���Flash�ļ��ʱ��
	BYTE	bFlashCS;		// FlashƬѡ(��FlashƬѡ���ڣ�����Ӧ��Bit��1��������0)
}PACKED2 FlashInfo, *PFlashInfo;

typedef PACKED1 struct _FlashInfoCmd
{
	UINT	uiFlashSize;	// Flash��С����SectorΪ��λ��
	USHORT	usBlockSize;	// ������Block��С����SectorΪ��λ��
	BYTE	bPageSize;		// ������Page��С����SectorΪ��λ��
	BYTE	bECCBits;		// 8/14
	BYTE	AccessTime;		// ���η���Flash�ļ��ʱ��
	BYTE	bManufCode;		// ����ʶ����
	BYTE	bFlashCS;		// FlashƬѡ(��FlashƬѡ���ڣ�����Ӧ��Bit��1��������0)
}PACKED2 FlashInfoCmd, *PFlashInfoCmd;


#define BOOTSIGN		"RK28@Copyright2008Rockchip"
#define BOOTSIGN_SIZE		32
#define CHECK_SIZE		16
#define HEADINFO_SIZE		512

typedef PACKED1 struct _rk_time {
	unsigned short		usYear;
	unsigned short		usMonth;
	unsigned short		usDate;
	unsigned short		usHour;
	unsigned short		usMinute;
	unsigned short		usSecond;
}PACKED2 RK_TIME;

typedef PACKED1 struct _RK28BOOT_HEAD{
	char				szSign[BOOTSIGN_SIZE];
	unsigned char		bMD5Check[CHECK_SIZE];
	RK_TIME				tmCreateTime;

	unsigned int		uiMajorVersion;
	unsigned int		uiMinorVersion;

	unsigned int		uiUsbDataOffset;
	unsigned int		uiUsbDataLen;

	unsigned int		uiUsbBootOffset;
	unsigned int		uiUsbBootLen;

	unsigned int		uiFlashDataOffset;
	unsigned int		uiFlashDataLen;

	unsigned int       	uiFlashBootOffset;
	unsigned int		uiFlashBootLen;
	unsigned char		ucRc4Flag;

	unsigned int		MergerVersion;		// ����Boot�ļ�����Merger���ߵİ汾��(��16�ֽ�Ϊ���汾�š���16�ֽ�Ϊ���汾��)
}PACKED2 RK28BOOT_HEAD, *PRK28BOOT_HEAD;

struct bootloader_message {
	char command[32];
	char status[32];
	char recovery[1024];
};


typedef struct tag_rk_boot_img_hdr {
	struct fastboot_boot_img_hdr hdr;

	unsigned char reserved[0x400-0x260];
	unsigned long signTag; //0x4E474953
	unsigned long signlen; //128
	unsigned char rsaHash[128];
} rk_boot_img_hdr;

#define SECURE_BOOT_SIGN_TAG    0x4E474953

int secureCheck(struct fastboot_boot_img_hdr *hdr, int unlocked);
int getSn(char* buf);
int setBootloaderMsg(struct bootloader_message* bmsg);
int checkMisc(void);
void fixInitrd(PBootInfo pboot_info, int ramdisk_addr, int ramdisk_sz);
int CopyMemory2Flash(uint32 src_addr, uint32 dest_offset, int sectors);
int32 CopyFlash2Memory(uint32 dest_addr, uint32 src_addr, uint32 total_sec);
void SysLowFormatCheck(void);
void Switch2MSC(void);
void setup_space(uint32 begin_addr);
int get_bootloader_ver(char *boot_ver);
int execute_cmd(PBootInfo pboot_info, char* cmdlist, bool* reboot);
const char* get_fdt_name(void);
int eraseDrmKey(void);
int update_loader(bool dataLoaded);

#endif /* RKIDBLOCK_H */
