// See LICENSE for license details.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "platform.h"
#include "picojpeg.h"

#define TEST_BASE 0x10041000
#define TRAIN_BASE 0x10041100
#define RESULT_REG 0x10041ff8
#define STATUS_REG 0x10041ffc

#define GIE 0x100507f8
#define TX_PING_LEN 0x100507f4
#define TX_PING_CON 0x100507fc
#define TX_BASE 0x10050000
#define RX_BASE 0x10051000
#define RX_PING_CON 0x100517fc
#define MDIO_ADDR 0x100507e4
#define MDIO_WR 0x100507e8
#define MDIO_RD 0x100507ec
#define MDIO_CTRL 0x100507f0


uint32_t train_set[11][37] = {{4194303,4194303,4194303,4194303,4186367,4161599,4063263,4071183,3948423,3702663,3735491,3735491,3211203,3211235,3211235,3276771,3276771,3276771,3276771,3276771,3276771,3276771,3276771,3211235,3211235,3211203,3735495,3702663,3948431,3940111,4063263,4128831,4178431,4194303,4194303,4194303,4194303},
		{4194303,4194303,4194303,4194303,4193535,4192511,4190463,4178175,4129023,3938559,3963135,4061439,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4192511,4194303,4194303,4194303,4194303},
		{4194303,4194303,4194303,4194303,4178431,4063295,3932191,3964431,3997575,4194183,4194247,4194247,4194247,4194247,4194247,4194183,4194063,4193807,4193311,4192319,4190335,4178431,4162559,4130815,4071423,3948543,3702783,3735551,3735551,3211263,3145731,3145731,3145731,4194303,4194303,4194303,4194303},
		{4194303,4194303,4194303,4194303,4178431,4063295,3932191,3997215,4062991,4194063,4194191,4194191,4194191,4194191,4194063,4193823,4193343,4129023,4129279,4128831,4193807,4194063,4194183,4194247,4194247,4194247,4194247,4194183,3931919,3800591,3670047,3932287,4162559,4194303,4194303,4194303,4194303},
		{4194303,4194303,4194303,4194303,4193823,4193823,4193311,4193311,4192287,4192287,4190495,4186911,4186911,4179743,4165407,4165407,4136735,4079391,3948319,3964703,3735327,3276575,2227999,2097153,2097153,2097153,4194079,4194079,4194079,4194079,4194079,4194079,4194079,4194303,4194303,4194303,4194303},
		{4194303,4194303,4194303,4194303,4063247,4063247,4063247,4079615,3948543,3964927,3964927,3964927,3964927,3964927,3964927,3932671,3932223,3932191,4193295,4194063,4194183,4194247,4194247,4194247,4194247,4194247,4194183,4194183,4194063,3800095,3670047,3670143,4064255,4194303,4194303,4194303,4194303},
		{4194303,4194303,4194303,4194303,4192287,4186119,4161543,4130807,4132863,4071423,3948543,3964927,3702783,3735551,3735551,3731583,3719199,3178511,3153671,3162051,3178435,3211235,3211235,3735523,3735523,3735523,3702755,3964867,3948423,4071175,4128783,4161567,4186367,4194303,4194303,4194303,4194303},
		{4194303,4194303,4194303,4194303,3145731,3145731,3145731,4194247,4194247,4194191,4194191,4194079,4194079,4193855,4193855,4193407,4193407,4192511,4192511,4190463,4190719,4190719,4187135,4187135,4178943,4179967,4179967,4163583,4163583,4165631,4165631,4165631,4132863,4194303,4194303,4194303,4194303},
		{4194303,4194303,4194303,4194303,4186367,4128831,4063263,3940111,3964807,3702727,3735495,3735495,3735495,3964871,3964815,4071199,4128831,4161599,4063263,3948303,3702663,3735491,3211235,3276771,3276771,3276771,3211235,3211203,3702663,3686151,3932175,4128799,4178175,4194303,4194303,4194303,4194303},
		{4194303,4194303,4194303,4194303,4186367,4128831,4063263,3948047,3702671,3735431,3211207,3211203,3276771,3276771,3211235,3211203,3211203,3702659,3686147,3932195,4063331,4178403,4194243,4194247,4194247,4194247,4194191,4194063,4193823,4062271,3932287,3932415,4130815,4194303,4194303,4194303,4194303},
		{4194303,4194303,4194303,4194303,3211256,3211256,3702768,3948529,3948513,4071363,4071363,4132743,4165519,4163343,4178463,4178495,4186175,4190335,4190335,4186239,4186175,4178463,4179487,4163343,4132751,4136839,4071363,3948483,3948513,3702768,3211248,3211256,2228216,4194303,4194303,4194303,4194303}};
uint16_t offset;
uint8_t char_list[11] = {'0','1','2','3','4','5','6','7','8','9','X'};
uint8_t result_list[10][19];
uint8_t dest_mac_rx[6];
uint8_t source_mac_rx[6];
uint8_t eth_type_rx[2];
uint8_t dest_ip_rx[4];
uint8_t receive_buf[550];
uint8_t image_buf[39000];
uint8_t send_buf[200];
uint32_t ip_head[14];
uint16_t tx_index;
uint16_t dest_port;
uint16_t g_nInFileSize;
uint16_t g_nInFileOfs;
uint8_t * pImage;
pjpeg_image_info_t image_info;
int mcu_x;
int mcu_y;
uint32_t row_pitch;
uint8_t status;
uint32_t decoded_width,decoded_height;
uint32_t row_blocks_per_mcu, col_blocks_per_mcu;
uint32_t k;
uint8_t * char_block;
uint8_t temp;
uint32_t sum;
uint32_t test_set[37];
uint32_t min;
uint8_t minindex;
uint8_t jpgindex;
volatile uint16_t receive_len;

void eth_ini();
int receive_udp(uint8_t * buf);
void send_udp(uint16_t data_len,uint8_t * buf);

unsigned char pjpeg_need_bytes_callback(unsigned char* pBuf, unsigned char buf_size, unsigned char *pBytes_actually_read, void *pCallback_data)
{
   uint n;
   pCallback_data;
   if ((g_nInFileSize - g_nInFileOfs) < buf_size)
	   n = g_nInFileSize - g_nInFileOfs;
   else
	   n = buf_size;
//   if (n && (fread(pBuf, 1, n, g_pInFile) != n))
 //     return PJPG_STREAM_READ_ERROR;
   memcpy(pBuf, image_buf + g_nInFileOfs, n);
   *pBytes_actually_read = (unsigned char)(n);
   g_nInFileOfs += n;
   return 0;
}

int main(void)
{
	tx_index = 0;
	for (jpgindex=0;jpgindex<10;jpgindex++){
		mcu_x = 0;
		mcu_y = 0;
		receive_len=1024;
		pImage = (uint8_t *)0xa0000000;
		int reduce = 0;
		eth_ini();
		dest_port = 0x4500;
		g_nInFileSize = 0;
		g_nInFileOfs = 0;
//		printf("udp is running\n");
		send_buf[0] = 0;
		send_buf[1] = 1;
		send_buf[2] = '0'+jpgindex;
		send_buf[3] = '.';
		send_buf[4] = 'j';
		send_buf[5] = 'p';
		send_buf[6] = 'g';
		send_buf[7] = 0;
		send_buf[8] = 'o';
		send_buf[9] = 'c';
		send_buf[10] = 't';
		send_buf[11] = 'e';
		send_buf[12] = 't';
		send_buf[13] = 0;
		send_udp(14,send_buf);
		while (receive_len>=516){
			receive_len=0;
			while (receive_len==0){
				receive_len = receive_udp(receive_buf);
			}
//			printf("receive a pkt %d\n",receive_len);
			memcpy(image_buf+g_nInFileOfs,receive_buf+4,receive_len-4);
			g_nInFileOfs+=(receive_len-4);
			if (receive_buf[1]==3){
				send_buf[0]=0;
				send_buf[1]=4;
				send_buf[2]=receive_buf[2];
				send_buf[3]=receive_buf[3];
				send_udp(4,send_buf);
			}
		}
		g_nInFileSize = g_nInFileOfs;
		g_nInFileOfs = 0;
		receive_len=0;
		status = pjpeg_decode_init(&image_info, pjpeg_need_bytes_callback, NULL, (unsigned char)reduce);
		if (status)
		{
		   printf("pjpeg_decode_init() failed with status %u\n", status);
		   if (status == PJPG_UNSUPPORTED_MODE)
		   {
		      printf("Progressive JPEG files are not supported.\n");
		   }

		   return 1;
		}
		decoded_width = reduce ? (image_info.m_MCUSPerRow * image_info.m_MCUWidth) / 8 : image_info.m_width;
		decoded_height = reduce ? (image_info.m_MCUSPerCol * image_info.m_MCUHeight) / 8 : image_info.m_height;
		row_pitch = decoded_width * image_info.m_comps;
		row_blocks_per_mcu = image_info.m_MCUWidth >> 3;
		col_blocks_per_mcu = image_info.m_MCUHeight >> 3;
		for ( ; ; )
		{
		   int y, x;
		   uint8_t *pDst_row;

		   status = pjpeg_decode_mcu();

		   if (status)
		   {
		      if (status != PJPG_NO_MORE_BLOCKS)
		      {
		         printf("pjpeg_decode_mcu() failed with status %u\n", status);
		         return 1;
		      }
		         break;
		   }
		   if (mcu_y >= image_info.m_MCUSPerCol)
		   {
		         return 1;
		   }
		   pDst_row = pImage + (mcu_y * image_info.m_MCUHeight) * row_pitch + (mcu_x * image_info.m_MCUWidth * image_info.m_comps);

		   for (y = 0; y < image_info.m_MCUHeight; y += 8)
		   {
		      int by_limit;
		      if (8<(image_info.m_height - (mcu_y * image_info.m_MCUHeight + y)))
		    	  by_limit = 8;
		      else
		    	  by_limit = image_info.m_height - (mcu_y * image_info.m_MCUHeight + y);

		      for (x = 0; x < image_info.m_MCUWidth; x += 8)
		      {
		          uint8_t *pDst_block = pDst_row + x * image_info.m_comps;

		                  // Compute source byte offset of the block in the decoder's MCU buffer.
		          uint32_t src_ofs = (x * 8U) + (y * 16U);
		          uint8_t *pSrcR = image_info.m_pMCUBufR + src_ofs;
		          uint8_t *pSrcG = image_info.m_pMCUBufG + src_ofs;
		          uint8_t *pSrcB = image_info.m_pMCUBufB + src_ofs;

		          int bx_limit;
		          if (8<(image_info.m_width - (mcu_x * image_info.m_MCUWidth + x)))
		        	  bx_limit = 8;
		          else
		        	  bx_limit = image_info.m_width - (mcu_x * image_info.m_MCUWidth + x);

		          if (image_info.m_scanType == PJPG_GRAYSCALE)
		          {
		              int bx, by;
		              for (by = 0; by < by_limit; by++)
		              {
		                   uint8_t *pDst = pDst_block;

		                   for (bx = 0; bx < bx_limit; bx++)
		                       *pDst++ = *pSrcR++;

		                   pSrcR += (8 - bx_limit);

		                   pDst_block += row_pitch;
		               }
		           }
		           else
		           {
		              int bx, by;
		              for (by = 0; by < by_limit; by++)
		              {
		                  uint8_t *pDst = pDst_block;

		                  for (bx = 0; bx < bx_limit; bx++)
		                  {
		                      pDst[0] = *pSrcR++;
		                      pDst[1] = *pSrcG++;
		                      pDst[2] = *pSrcB++;
		                      pDst += 3;
		                  }

		                  pSrcR += (8 - bx_limit);
		                  pSrcG += (8 - bx_limit);
		                  pSrcB += (8 - bx_limit);

		                  pDst_block += row_pitch;
		               }
		            }
		        }

		        pDst_row += (row_pitch * 8);
		   }
		   mcu_x++;
		   if (mcu_x == image_info.m_MCUSPerRow){
			   mcu_x = 0;
			   mcu_y++;
		   }
		}
		uint32_t kk=0;
		k=0; min = 32767;
		for (int i=0;i<319;i++){
			temp=0;
			for (int j=0;j<506;j++){
				*(pImage+k) = *(pImage+kk);
				if ((*(pImage+k)<200) && (temp==0)){
					temp=1;
					if (j<min){
						min = j;
						minindex = i;
					}
				}

				k++;
				kk+=3;
			}
		}
		offset = min-2;
//		write_hex(STDERR_FILENO, offset);
//		write(STDERR_FILENO, "\n", 1);
		for (int i=0;i<484242;i++){
			*(pImage+k) = *(pImage+i);
//			write_hex(STDERR_FILENO, k);
//			write(STDERR_FILENO, "\n", 1);
			i+=2;
			k++;
		}
		for (k=0;k<18;k++){
			if (result_list[jpgindex][0]=='4')
				char_block = pImage + 67804 + offset+2;
			else
				if (result_list[jpgindex][0]=='1')
					char_block = pImage + 67804 + offset-2;
				else
					char_block = pImage + 67804 + offset;
			offset += 22;
			for (int i=0;i<37;i++){
				sum = 0;
				for (int j=0;j<22;j++){
					if (*(char_block+j)<200)
						temp=0;
					else temp=1;
					sum = sum*2 + temp;
				}
				char_block+=506;
				test_set[i] = sum;
//				write_hex(STDERR_FILENO, sum);
//				write(STDERR_FILENO, "\n", 1);
			}
			min = 32767;
			volatile uint32_t *ptr;
			volatile uint32_t data;
			ptr = (uint32_t *)TEST_BASE;
			for (int i=0;i<37;i++){
				*(ptr+i) = test_set[i];
			}

			for (int i=0;i<11;i++){
				ptr = (uint32_t *)TRAIN_BASE;
				for (int j=0;j<37;j++){
					*(ptr+j) = train_set[i][j];
				}
				ptr = (uint32_t *)STATUS_REG;
				*ptr = 0x00000001;
				data = *ptr;
				while ((data & 0x01)==0x01){
					data = *ptr;
				}
				ptr = (uint32_t *)RESULT_REG;
				data = *ptr;
//				write_hex(STDERR_FILENO, data);
//				write(STDERR_FILENO, "\n", 1);
				if (data<min){
					min = data;
					minindex = i;
				}
			}
			result_list[jpgindex][k]=char_list[minindex];
		}
		result_list[jpgindex][18] = '\n';
	}
	dest_port = 0x4500;
	send_buf[0] = 0;
	send_buf[1] = 2;
	send_buf[2] = 't';
	send_buf[3] = 'e';
	send_buf[4] = 's';
	send_buf[5] = 't';
	send_buf[6] = '.';
	send_buf[7] = 't';
	send_buf[8] = 'x';
	send_buf[9] = 't';
	send_buf[10] = 0;
	send_buf[11] = 'n';
	send_buf[12] = 'e';
	send_buf[13] = 't';
	send_buf[14] = 'a';
	send_buf[15] = 's';
	send_buf[16] = 'c';
	send_buf[17] = 'i';
	send_buf[18] = 'i';
	send_buf[19] = 0;
	send_udp(20,send_buf);
	receive_len=0;
	while (receive_len==0){
		receive_len = receive_udp(receive_buf);
	}
	send_buf[0] = 0;
	send_buf[1] = 3;
	send_buf[2] = 0;
	send_buf[3] = 1;
	k=4;
	for (int i=0; i<10;i++)
		for (int j=0;j<19;j++){
			send_buf[k] = result_list[i][j];
			k++;
		}
	send_udp(194,send_buf);
	receive_len=0;
	while (receive_len==0){
		receive_len = receive_udp(receive_buf);
	}
	uint32_t * vga_ptr;
	vga_ptr = (uint32_t*)0x10010000;
	k=0;
	for (int i=0; i<10;i++)
		for (int j=0;j<18;j++){
			if (result_list[i][j]=='X')
				*(vga_ptr+k) = 10;
			else
				*(vga_ptr+k) = result_list[i][j];
			k++;
		}
	vga_ptr = (uint32_t*)0x10010ffc;
	*vga_ptr = 1;
	while(1){

	}
	return 0;

}

void eth_ini(){
	volatile uint32_t *p;
	volatile uint32_t pan;
	uint8_t * data_p;
	p = (uint32_t*)MDIO_RD;
	p = (uint32_t*)MDIO_CTRL;
	*p |= 0x08;
	pan = *p;
	while ((pan & 0x01)==0x01){
		pan = *p;
	}
	p = (uint32_t*)MDIO_ADDR;
	*p = 0x0020;
	p =(uint32_t*) MDIO_WR;
	*p = 0x0100;
	p = (uint32_t*)MDIO_CTRL;
	*p = 9;
	pan = *p;
	while ((pan & 0x01) == 0x01){
		pan = *p;
	}
	p = (uint32_t*)MDIO_ADDR;
	*p = 0x0420;
	p = (uint32_t*)MDIO_CTRL;
	*p = 9;
	pan = *p;
	while ((pan & 0x01) == 0x01){
		pan = *p;
	}
	p = (uint32_t*)MDIO_RD;
//	printf("%x\n", *p);

//	printf("MDIO INIT DONE 10Mb" "\n");

	p=(uint32_t*)GIE;
	*p=0x00000000;

	p=(uint32_t*)RX_PING_CON;
	*p=0x08;
	// ����mac��ַ
	p=(uint32_t*)TX_PING_CON;
	pan=*p;
	while (((pan & 0x01)==0x01) || ((pan & 0x02)==0x02)){
		pan=*p;
	}

	p=(uint32_t*)TX_BASE;

	*p = 0x33221100;
	*(p+1) = 0x5544;

	data_p=(uint8_t*)TX_BASE;
//	printf("%x ",*data_p); data_p++;
//	printf("%x ",*data_p); data_p++;
//	printf("%x ",*data_p); data_p++;
//	printf("%x ",*data_p); data_p++;
//	printf("%x ",*data_p); data_p++;
	p=(uint32_t*)TX_PING_CON;
	*p=0x03;
	pan=*p;
	while (((pan & 0x01)==0x01) || ((pan & 0x02)==0x02)){
		pan=*p;
	}
//	printf("change mac as 00-11-22-33-44-55\n");
}

int receive_udp(uint8_t * buf){
	volatile uint32_t *p;
	volatile uint32_t pan;
	volatile uint8_t * data_p;
	volatile uint16_t * udp_port_base;
	int i;
	uint16_t udp_len;
	uint8_t ip_head_len;
	p=(uint32_t*)RX_PING_CON;
	pan = *p;
	while ((pan & 0x01) == 0x00){
		pan=*p;
	};
	data_p=(uint8_t*)RX_BASE;
	dest_mac_rx[0] = *data_p;
	data_p++;
	dest_mac_rx[1] = *data_p;
	data_p++;
	dest_mac_rx[2] = *data_p;
	data_p++;
	dest_mac_rx[3] = *data_p;
	data_p++;
	dest_mac_rx[4] = *data_p;
	data_p++;
	dest_mac_rx[5] = *data_p;
	data_p++;
	source_mac_rx[0] = *data_p;
	data_p++;
	source_mac_rx[1] = *data_p;
	data_p++;
	source_mac_rx[2] = *data_p;
	data_p++;
	source_mac_rx[3] = *data_p;
	data_p++;
	source_mac_rx[4] = *data_p;
	data_p++;
	source_mac_rx[5] = *data_p;
	data_p++;
	eth_type_rx[0] = *data_p;
	data_p++;
	eth_type_rx[1] = *data_p;
	data_p++;
	if ((eth_type_rx[0]!=0x08) || (eth_type_rx[1]!=0x00)){
		p=(uint32_t*)RX_PING_CON;
		*p=0;
		return 0;
	}
	ip_head_len = ((*data_p)& 0x0f)<<2;
	data_p+=16;
	dest_ip_rx[0] = *data_p;
	data_p++;
	dest_ip_rx[1] = *data_p;
	data_p++;
	dest_ip_rx[2] = *data_p;
	data_p++;
	dest_ip_rx[3] = *data_p;
	data_p++;
	if ((dest_ip_rx[0] != 192) || (dest_ip_rx[1] != 168) || (dest_ip_rx[2]!=1) || (dest_ip_rx[3]!=123)){
		p=(uint32_t*)RX_PING_CON;
		*p=0;
		return 0;
	}
	data_p+=(ip_head_len - 20);
	udp_port_base = (uint16_t*)data_p;
	dest_port = *udp_port_base;
	data_p+=4;
	udp_len =  (*data_p)<<8;
	data_p++;
	udp_len = udp_len | (*data_p);
	udp_len = udp_len - 8;
	data_p++;
	data_p+=2;
	for (i=0;i<udp_len;i++){
		*(buf+i) = *(data_p+i);
	}
	p=(uint32_t*)RX_PING_CON;
	*p=0;
	return udp_len;
}

void send_udp(uint16_t data_len,uint8_t * buf){
	volatile uint32_t *p;
	volatile uint32_t pan;
	volatile uint8_t * data_p;
	uint16_t total_num;
	uint16_t udp_num;
	uint32_t sum;
	uint32_t sum2;
	uint16_t check_sum;
	int i;
	total_num = data_len + 28;
	udp_num = data_len + 8;
	ip_head[0] = 0x4500;
	ip_head[1] = total_num;
	tx_index++;
	ip_head[2] = tx_index;
	ip_head[3] = 0x4000;
	ip_head[4] = 0x4011;
	ip_head[5] = 0x0000;
	ip_head[6] = 0xc0a8;
	ip_head[7] = 0x017b;
	ip_head[8] = 0xc0a8;
	ip_head[9] = 0x0166;
	ip_head[10] = 69;
	ip_head[11] = ((dest_port & 0xff00)>>8)|((dest_port & 0x00ff)<<8);
	ip_head[12] = udp_num;
	ip_head[13] = 0x0000;
	sum = ip_head[0]+ip_head[1]+ip_head[2]+ip_head[3]+ip_head[4]+ip_head[5]+
		  ip_head[6]+ip_head[7]+ip_head[8]+ip_head[9];
	sum2 = ((sum & 0xffff0000)>>16)+(sum & 0x0000ffff);
	check_sum = ((sum2 & 0xffff0000)>>16)+(sum2 & 0x0000ffff);
	check_sum = ~check_sum;
	ip_head[5] = check_sum;
	p=(uint32_t*)TX_PING_CON;
	pan = *p;
	while ((pan & 0x01)  == 0x01){
		pan=*p;
	};
	p = (uint32_t*)TX_BASE;
	*p = 0xffffffff;  p++;
	*p = 0x1100ffff;  p++;
	*p = 0x55443322;  p++;
	*p = ((ip_head[0] & 0xff00)<<8)|0x0008 | ((ip_head[0] & 0x00ff)<<24); p++;
	*p = ((ip_head[1] & 0xff00)>>8)|((ip_head[1] & 0x00ff)<<8)|((ip_head[2] & 0xff00)<<8)|((ip_head[2] & 0x00ff)<<24); p++;
	*p = ((ip_head[3] & 0xff00)>>8)|((ip_head[3] & 0x00ff)<<8)|((ip_head[4] & 0xff00)<<8)|((ip_head[4] & 0x00ff)<<24); p++;
	*p = ((ip_head[5] & 0xff00)>>8)|((ip_head[5] & 0x00ff)<<8)|((ip_head[6] & 0xff00)<<8)|((ip_head[6] & 0x00ff)<<24); p++;
	*p = ((ip_head[7] & 0xff00)>>8)|((ip_head[7] & 0x00ff)<<8)|((ip_head[8] & 0xff00)<<8)|((ip_head[8] & 0x00ff)<<24); p++;
	*p = ((ip_head[9] & 0xff00)>>8)|((ip_head[9] & 0x00ff)<<8)|((ip_head[10] & 0xff00)<<8)|((ip_head[10] & 0x00ff)<<24); p++;
	*p = ((ip_head[11] & 0xff00)>>8)|((ip_head[11] & 0x00ff)<<8)|((ip_head[12] & 0xff00)<<8)|((ip_head[12] & 0x00ff)<<24); p++;
	*p = ((ip_head[13] & 0xff00)>>8)|((ip_head[13] & 0x00ff)<<8)|((*buf)<<16)|((*(buf+1))<<24); p++;
	sum = 2;
	while (sum < data_len){
		sum2 = *(buf+sum);
		sum++;
		if (sum<data_len)
			sum2 = sum2 | ((*(buf+sum))<<8);
		sum++;
		if (sum<data_len)
			sum2 = sum2 | ((*(buf+sum))<<16);
		sum++;
		if (sum<data_len)
			sum2 = sum2 | ((*(buf+sum))<<24);
		sum++;
		*p = sum2;
		p++;
	}

	p =(uint32_t*)TX_PING_LEN;
	*p = total_num+14;
	p=(uint32_t*)TX_PING_CON;
	*p = 0x01;
	pan = *p;
	while ((pan & 0x01)  == 0x01){
		pan=*p;
	};
	//printf("send a pkt\n");
}
