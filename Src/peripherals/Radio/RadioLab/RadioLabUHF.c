#include "RadioLab.h"
// TX: fcarrier=435.755MHz dev=  1.600kHz br=  4.800kBit/s pwr= 15.0dBm
// RX: fcarrier=435.755MHz bw=  7.200kHz br=  4.800kBit/s

void ax5043_uhf_set_registers(void) {
	radio_write8(AX5043_REG_MODULATION     ,                              			0x08);
	radio_write8(AX5043_REG_ENCODING       ,                              			0x00);
	radio_write8(AX5043_REG_FRAMING        ,                              			0x26);
	radio_write8(AX5043_REG_PINFUNCSYSCLK  ,                              			0x02);
	radio_write8(AX5043_REG_PINFUNCDCLK    ,                              			0x02);
	radio_write8(AX5043_REG_PINFUNCDATA    ,                              			0x02);
	radio_write8(AX5043_REG_PINFUNCANTSEL  ,                              			0x06);
	radio_write8(AX5043_REG_PINFUNCPWRAMP  ,                              			0x06);
	radio_write8(AX5043_REG_WAKEUPXOEARLY  ,                              			0x01);
	radio_write8(AX5043_REG_IFFREQ1        ,                              			0x01);
	radio_write8(AX5043_REG_IFFREQ0        ,                              			0xE4);
	radio_write8(AX5043_REG_DECIMATION     ,                              			0x16);
	radio_write8(AX5043_REG_RXDATARATE2    ,                              			0x00);
	radio_write8(AX5043_REG_RXDATARATE1    ,                              			0x3D);
	radio_write8(AX5043_REG_RXDATARATE0    ,                              			0x8D);
	radio_write8(AX5043_REG_MAXDROFFSET2   ,                              			0x00);
	radio_write8(AX5043_REG_MAXDROFFSET1   ,                              			0x00);
	radio_write8(AX5043_REG_MAXDROFFSET0   ,                              			0x00);
	radio_write8(AX5043_REG_MAXRFOFFSET2   ,                              			0x80);
	radio_write8(AX5043_REG_MAXRFOFFSET1   ,                              			0x02);
	radio_write8(AX5043_REG_MAXRFOFFSET0   ,                              			0x32);
	radio_write8(AX5043_REG_FSKDMAX1       ,                              			0x00);
	radio_write8(AX5043_REG_FSKDMAX0       ,                              			0xA6);
	radio_write8(AX5043_REG_FSKDMIN1       ,                              			0xFF);
	radio_write8(AX5043_REG_FSKDMIN0       ,                              			0x5A);
	radio_write8(AX5043_REG_AMPLFILTER     ,                              			0x00);
	radio_write8(AX5043_REG_RXPARAMSETS    ,                              			0xF4);
	radio_write8(AX5043_REG_AGCGAIN0       ,                              			0xC5);
	radio_write8(AX5043_REG_AGCTARGET0     ,                              			0x84);
	radio_write8(AX5043_REG_TIMEGAIN0      ,                              			0xF8);
	radio_write8(AX5043_REG_DRGAIN0        ,                              			0xF2);
	radio_write8(AX5043_REG_PHASEGAIN0     ,                              			0xC3);
	radio_write8(AX5043_REG_FREQUENCYGAINA0,                              			0x0F);
	radio_write8(AX5043_REG_FREQUENCYGAINB0,                              			0x1F);
	radio_write8(AX5043_REG_FREQUENCYGAINC0,                              			0x08);
	radio_write8(AX5043_REG_FREQUENCYGAIND0,                              			0x08);
	radio_write8(AX5043_REG_AMPLITUDEGAIN0 ,                              			0x06);
	radio_write8(AX5043_REG_FREQDEV10      ,                              			0x00);
	radio_write8(AX5043_REG_FREQDEV00      ,                              			0x00);
	radio_write8(AX5043_REG_BBOFFSRES0     ,                              			0x00);
	radio_write8(AX5043_REG_AGCGAIN1       ,                              			0xC5);
	radio_write8(AX5043_REG_AGCTARGET1     ,                              			0x84);
	radio_write8(AX5043_REG_AGCAHYST1      ,                              			0x00);
	radio_write8(AX5043_REG_AGCMINMAX1     ,                              			0x00);
	radio_write8(AX5043_REG_TIMEGAIN1      ,                              			0xF6);
	radio_write8(AX5043_REG_DRGAIN1        ,                              			0xF1);
	radio_write8(AX5043_REG_PHASEGAIN1     ,                              			0xC3);
	radio_write8(AX5043_REG_FREQUENCYGAINA1,                              			0x0F);
	radio_write8(AX5043_REG_FREQUENCYGAINB1,                              			0x1F);
	radio_write8(AX5043_REG_FREQUENCYGAINC1,                              			0x08);
	radio_write8(AX5043_REG_FREQUENCYGAIND1,                              			0x08);
	radio_write8(AX5043_REG_AMPLITUDEGAIN1 ,                              			0x06);
	radio_write8(AX5043_REG_FREQDEV11      ,                              			0x00);
	radio_write8(AX5043_REG_FREQDEV01      ,                              			0x43);
	radio_write8(AX5043_REG_FOURFSK1       ,                              			0x16);
	radio_write8(AX5043_REG_BBOFFSRES1     ,                              			0x00);
	radio_write8(AX5043_REG_AGCGAIN3       ,                              			0xFF);
	radio_write8(AX5043_REG_AGCTARGET3     ,                              			0x84);
	radio_write8(AX5043_REG_AGCAHYST3      ,                              			0x00);
	radio_write8(AX5043_REG_AGCMINMAX3     ,                              			0x00);
	radio_write8(AX5043_REG_TIMEGAIN3      ,                              			0xF5);
	radio_write8(AX5043_REG_DRGAIN3        ,                              			0xF0);
	radio_write8(AX5043_REG_PHASEGAIN3     ,                              			0xC3);
	radio_write8(AX5043_REG_FREQUENCYGAINA3,                              			0x0F);
	radio_write8(AX5043_REG_FREQUENCYGAINB3,                              			0x1F);
	radio_write8(AX5043_REG_FREQUENCYGAINC3,                              			0x0C);
	radio_write8(AX5043_REG_FREQUENCYGAIND3,                              			0x0C);
	radio_write8(AX5043_REG_AMPLITUDEGAIN3 ,                              			0x06);
	radio_write8(AX5043_REG_FREQDEV13      ,                              			0x00);
	radio_write8(AX5043_REG_FREQDEV03      ,                              			0x43);
	radio_write8(AX5043_REG_FOURFSK3       ,                              			0x16);
	radio_write8(AX5043_REG_BBOFFSRES3     ,                              			0x00);
	radio_write8(AX5043_REG_MODCFGF        ,                              			0x03);
	radio_write8(AX5043_REG_FSKDEV2        ,                              			0x00);
	radio_write8(AX5043_REG_FSKDEV1        ,                              			0x04);
	radio_write8(AX5043_REG_FSKDEV0        ,                              			0x08);
	radio_write8(AX5043_REG_MODCFGA        ,                              			0x05);
	radio_write8(AX5043_REG_TXRATE2        ,                              			0x00);
	radio_write8(AX5043_REG_TXRATE1        ,                              			0x0C);
	radio_write8(AX5043_REG_TXRATE0        ,                              			0x19);
	radio_write8(AX5043_REG_TXPWRCOEFFB1   ,                              			0x0F);
	radio_write8(AX5043_REG_TXPWRCOEFFB0   ,                              			0xFF);
	radio_write8(AX5043_REG_PLLVCOI        ,                              			0x98);
	radio_write8(AX5043_REG_PLLRNGCLK      ,                              			0x04);
	radio_write8(AX5043_REG_BBTUNE         ,                              			0x0F);
	radio_write8(AX5043_REG_BBOFFSCAP      ,                              			0x77);
	radio_write8(AX5043_REG_PKTADDRCFG     ,                              			0x01);
	radio_write8(AX5043_REG_PKTLENCFG      ,                              			0x80);
	radio_write8(AX5043_REG_PKTLENOFFSET   ,                              			0x00);
	radio_write8(AX5043_REG_PKTMAXLEN      ,                              			0xC8);
	radio_write8(AX5043_REG_MATCH0PAT3     ,                              			0xAA);
	radio_write8(AX5043_REG_MATCH0PAT2     ,                              			0xCC);
	radio_write8(AX5043_REG_MATCH0PAT1     ,                              			0xAA);
	radio_write8(AX5043_REG_MATCH0PAT0     ,                              			0xCC);
	radio_write8(AX5043_REG_MATCH0LEN      ,                              			0x1F);
	radio_write8(AX5043_REG_MATCH0MAX      ,                              			0x1F);
	radio_write8(AX5043_REG_MATCH1PAT1     ,                              			0x55);
	radio_write8(AX5043_REG_MATCH1PAT0     ,                              			0x55);
	radio_write8(AX5043_REG_MATCH1LEN      ,                              			0x8A);
	radio_write8(AX5043_REG_MATCH1MAX      ,                              			0x0A);
	radio_write8(AX5043_REG_TMGTXBOOST     ,                              			0x3E);
	radio_write8(AX5043_REG_TMGTXSETTLE    ,                              			0x31);
	radio_write8(AX5043_REG_TMGRXBOOST     ,                              			0x3E);
	radio_write8(AX5043_REG_TMGRXSETTLE    ,                              			0x31);
	radio_write8(AX5043_REG_TMGRXOFFSACQ   ,                              			0x00);
	radio_write8(AX5043_REG_TMGRXCOARSEAGC ,                              			0x7F);
	radio_write8(AX5043_REG_TMGRXRSSI      ,                              			0x03);
	radio_write8(AX5043_REG_TMGRXPREAMBLE2 ,                              			0x35);
	radio_write8(AX5043_REG_RSSIABSTHR     ,                              			0xE0);
	radio_write8(AX5043_REG_BGNDRSSITHR    ,                              			0x00);
	radio_write8(AX5043_REG_PKTCHUNKSIZE   ,                              			0x0D);
	radio_write8(AX5043_REG_PKTACCEPTFLAGS ,                              			0x20);
	radio_write8(AX5043_REG_DACVALUE1      ,                              			0x00);
	radio_write8(AX5043_REG_DACVALUE0      ,                              			0x00);
	radio_write8(AX5043_REG_DACCONFIG      ,                              			0x00);
	radio_write8(AX5043_REG_REF            ,                              			0x03);
	radio_write8(AX5043_REG_XTALOSC        ,                              			0x04);
	radio_write8(AX5043_REG_XTALAMPL       ,                              			0x00);
	radio_write8(AX5043_REG_0xF1C          ,                              			0x07);
	radio_write8(AX5043_REG_0xF21          ,                              			0x68);
	radio_write8(AX5043_REG_0xF22          ,                              			0xFF);
	radio_write8(AX5043_REG_0xF23          ,                              			0x84);
	radio_write8(AX5043_REG_0xF26          ,                              			0x98);
	radio_write8(AX5043_REG_0xF34          ,                              			0x28);
	radio_write8(AX5043_REG_0xF35          ,                              			0x11);
	radio_write8(AX5043_REG_0xF44          ,                              			0x25);
}


void ax5043_uhf_set_registers_tx(void) {
	radio_write8(AX5043_REG_PLLLOOP        ,                              			0x0B);
	radio_write8(AX5043_REG_PLLCPI         ,                              			0x10);
	radio_write8(AX5043_REG_PLLVCODIV      ,                              			0x24);
	radio_write8(AX5043_REG_XTALCAP        ,                              			0x00);
	radio_write8(AX5043_REG_0xF00          ,                              			0x0F);
	radio_write8(AX5043_REG_0xF18          ,                              			0x06);
}


void ax5043_uhf_set_registers_rx(void) {
	radio_write8(AX5043_REG_PLLLOOP        ,                              			0x0B);
	radio_write8(AX5043_REG_PLLCPI         ,                              			0x10);
	radio_write8(AX5043_REG_PLLVCODIV      ,                              			0x24);
	radio_write8(AX5043_REG_XTALCAP        ,                              			0x00);
	radio_write8(AX5043_REG_0xF00          ,                              			0x0F);
	radio_write8(AX5043_REG_0xF18          ,                              			0x02);
}


void ax5043_uhf_set_registers_rxwor(void) {
	radio_write8(AX5043_REG_TMGRXAGC,                 0x06);
	radio_write8(AX5043_REG_TMGRXPREAMBLE1,           0x19);
	radio_write8(AX5043_REG_PKTMISCFLAGS,             0x03);
}


void ax5043_uhf_set_registers_rxcont(void) {
	radio_write8(AX5043_REG_TMGRXAGC,                 0x00);
	radio_write8(AX5043_REG_TMGRXPREAMBLE1,           0x00);
	radio_write8(AX5043_REG_PKTMISCFLAGS,             0x00);
}
