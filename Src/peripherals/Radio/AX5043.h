#ifndef AX5043_H
#define AX5043_H

#include "globals.h"
#include "stm32l431xx.h"
#include <SPI/spi.h>
#include "RadioLab/RadioLabUHF.h"


#define UHF_SPI_CS SPI1_CS
#define UHF_SPI SPI1

#define AX5043_MAX_FIFO_SIZE 256

#define AX5043_PWRMODE_RST (1 << 7) 

#define AX5043_PWRMODE_DEFAULTVALUES (0b11 << 5)

#define AX5043_PWRMODE_POWERDOWN 0b0000
#define AX5043_PWRMODE_DEEPSLEEP 0b0001
#define AX5043_PWRMODE_STANDBY 0b0101
#define AX5043_PWRMODE_FIFOON 0b0111
#define AX5043_PWRMODE_SYNTHRX 0b1000
#define AX5043_PWRMODE_FULLRX 0b1001
#define AX5043_PWRMODE_WORRX 0b1011
#define AX5043_PWRMODE_SYNTHTX 0b1100
#define AX5043_PWRMODE_FULLTX 0b1101

#define AX5043_TX_FLAGS_PKTSTART (1 << 0)
#define AX5043_TX_FLAGS_PKTEND (1 << 1)
#define AX5043_TX_FLAGS_RESIDUE (1 << 2)
#define AX5043_TX_FLAGS_NOCRC (1 << 3)
#define AX5043_TX_FLAGS_RAW (1 << 4)
#define AX5043_TX_FLAGS_UNENC (1 << 5)

#define AX5043_FIFOCMD_COMMIT 0b000100
#define AX5043_FIFOCMD_ROLLBACK 0b000101
#define AX5043_FIFOCMD_CLEAR_ERROR 0b000010
#define AX5043_FIFOCMD_CLEAR_DATA_AND_FLAGS 0b000011
#define AX5043_FIFOCMD_ASK_COHERENT 0b000001

#define AX5043_FIFODATA_DATA_COMMAND 0xE1


#define AX5043_POWSTAT_SVMODEM (1 << 1)

#define AX5043_CARRIER_HZ 435
#define AX5043_XTAL_HZ 26
#define AX5043_PLLRANGINGA_VCORA 8 //TODO: Get this value
#define AX5043_PLLRANGINGA_RNGSTART (1 << 4)
#define AX5043_PLLRANGINGA_RNGERR (1 << 5)

#define AX5043_SILICONREVISION   0x0000 /* Silicon Revision */
#define AX5043_SCRATCH           0x0001 /* Scratch */
#define AX5043_PWRMODE           0x0002 /* Power Mode */
#define AX5043_POWSTAT           0x0003 /* Power Management Status */
#define AX5043_POWSTICKYSTAT     0x0004 /* Power Management Sticky Status */
#define AX5043_POWIRQMASK        0x0005 /* Power Management Interrupt Mask */
#define AX5043_IRQMASK1          0x0006 /* IRQ Mask 1 */
#define AX5043_IRQMASK0          0x0007 /* IRQ Mask 0 */
#define AX5043_RADIOEVENTMASK1   0x0008 /* Radio Event Mask 1 */
#define AX5043_RADIOEVENTMASK0   0x0009 /* Radio Event Mask 0 */
#define AX5043_IRQINVERSION1     0x000A /* IRQ Inversion 1 */
#define AX5043_IRQINVERSION0     0x000B /* IRQ Inversion 0 */
#define AX5043_IRQREQUEST1       0x000C /* IRQ Request 1 */
#define AX5043_IRQREQUEST0       0x000D /* IRQ Request 0 */
#define AX5043_RADIOEVENTREQ1    0x000E /* Radio Event Request 1 */
#define AX5043_RADIOEVENTREQ0    0x000F /* Radio Event Request 0 */
#define AX5043_MODULATION        0x0010 /* Modulation */
#define AX5043_ENCODING          0x0011 /* Encoding */
#define AX5043_FRAMING           0x0012 /* Framing Mode */
#define AX5043_CRCINIT3          0x0014 /* CRC Initial Value 3 */
#define AX5043_CRCINIT2          0x0015 /* CRC Initial Value 2 */
#define AX5043_CRCINIT1          0x0016 /* CRC Initial Value 1 */
#define AX5043_CRCINIT0          0x0017 /* CRC Initial Value 0 */
#define AX5043_FEC               0x0018 /* Forward Error Correction */
#define AX5043_FECSYNC           0x0019 /* Forward Error Correction Sync Threshold */
#define AX5043_FECSTATUS         0x001A /* Forward Error Correction Status */
#define AX5043_RADIOSTATE        0x001C /* Radio Controller State */
#define AX5043_XTALSTATUS        0x001D /* Crystal Oscillator Status */
#define AX5043_PINSTATE          0x0020 /* Pin State */
#define AX5043_PINFUNCSYSCLK     0x0021 /* Pin Function SYSCLK */
#define AX5043_PINFUNCDCLK       0x0022 /* Pin Function DCLK */
#define AX5043_PINFUNCDATA       0x0023 /* Pin Function DATA */
#define AX5043_PINFUNCIRQ        0x0024 /* Pin Function IRQ */
#define AX5043_PINFUNCANTSEL     0x0025 /* Pin Function ANTSEL */
#define AX5043_PINFUNCPWRAMP     0x0026 /* Pin Function PWRAMP */
#define AX5043_PWRAMP            0x0027 /* PWRAMP Control */
#define AX5043_FIFOSTAT          0x0028 /* FIFO Control */
#define AX5043_FIFODATA          0x0029 /* FIFO Data */
#define AX5043_FIFOCOUNT1        0x002A /* Number of Words currently in FIFO 1 */
#define AX5043_FIFOCOUNT0        0x002B /* Number of Words currently in FIFO 0 */
#define AX5043_FIFOFREE1         0x002C /* Number of Words that can be written to FIFO 1 */
#define AX5043_FIFOFREE0         0x002D /* Number of Words that can be written to FIFO 0 */
#define AX5043_FIFOTHRESH1       0x002E /* FIFO Threshold 1 */
#define AX5043_FIFOTHRESH0       0x002F /* FIFO Threshold 0 */
#define AX5043_PLLLOOP           0x0030 /* PLL Loop Filter Settings */
#define AX5043_PLLCPI            0x0031 /* PLL Charge Pump Current */
#define AX5043_PLLVCODIV         0x0032 /* PLL Divider Settings */
#define AX5043_PLLRANGINGA       0x0033 /* PLL Autoranging A */
#define AX5043_FREQA3            0x0034 /* Frequency A 3 */
#define AX5043_FREQA2            0x0035 /* Frequency A 2 */
#define AX5043_FREQA1            0x0036 /* Frequency A 1 */
#define AX5043_FREQA0            0x0037 /* Frequency A 0 */
#define AX5043_PLLLOOPBOOST      0x0038 /* PLL Loop Filter Settings (Boosted) */
#define AX5043_PLLCPIBOOST       0x0039 /* PLL Charge Pump Current (Boosted) */
#define AX5043_PLLRANGINGB       0x003B /* PLL Autoranging B */
#define AX5043_FREQB3            0x003C /* Frequency B 3 */
#define AX5043_FREQB2            0x003D /* Frequency B 2 */
#define AX5043_FREQB1            0x003E /* Frequency B 1 */
#define AX5043_FREQB0            0x003F /* Frequency B 0 */
#define AX5043_RSSI              0x0040 /* Received Signal Strength Indicator */
#define AX5043_BGNDRSSI          0x0041 /* Background RSSI */
#define AX5043_DIVERSITY         0x0042 /* Antenna Diversity Configuration */
#define AX5043_AGCCOUNTER        0x0043 /* AGC Counter */
#define AX5043_TRKDATARATE2      0x0045 /* Datarate Tracking 2 */
#define AX5043_TRKDATARATE1      0x0046 /* Datarate Tracking 1 */
#define AX5043_TRKDATARATE0      0x0047 /* Datarate Tracking 0 */
#define AX5043_TRKAMPLITUDE1     0x0048 /* Amplitude Tracking 1 */
#define AX5043_TRKAMPLITUDE0     0x0049 /* Amplitude Tracking 0 */
#define AX5043_TRKPHASE1         0x004A /* Phase Tracking 1 */
#define AX5043_TRKPHASE0         0x004B /* Phase Tracking 0 */
#define AX5043_TRKRFFREQ2        0x004D /* RF Frequency Tracking 2 */
#define AX5043_TRKRFFREQ1        0x004E /* RF Frequency Tracking 1 */
#define AX5043_TRKRFFREQ0        0x004F /* RF Frequency Tracking 0 */
#define AX5043_TRKFREQ1          0x0050 /* Frequency Tracking 1 */
#define AX5043_TRKFREQ0          0x0051 /* Frequency Tracking 0 */
#define AX5043_TRKFSKDEMOD1      0x0052 /* FSK Demodulator Tracking 1 */
#define AX5043_TRKFSKDEMOD0      0x0053 /* FSK Demodulator Tracking 0 */
#define AX5043_TRKAFSKDEMOD1     0x0054 /* AFSK Demodulator Tracking 1 */
#define AX5043_TRKAFSKDEMOD0     0x0055 /* AFSK Demodulator Tracking 0 */
#define AX5043_TIMER2            0x0059 /* 1MHz Timer 2 */
#define AX5043_TIMER1            0x005A /* 1MHz Timer 1 */
#define AX5043_TIMER0            0x005B /* 1MHz Timer 0 */
#define AX5043_WAKEUPTIMER1      0x0068 /* Wakeup Timer 1 */
#define AX5043_WAKEUPTIMER0      0x0069 /* Wakeup Timer 0 */
#define AX5043_WAKEUP1           0x006A /* Wakeup Time 1 */
#define AX5043_WAKEUP0           0x006B /* Wakeup Time 0 */
#define AX5043_WAKEUPFREQ1       0x006C /* Wakeup Frequency 1 */
#define AX5043_WAKEUPFREQ0       0x006D /* Wakeup Frequency 0 */
#define AX5043_WAKEUPXOEARLY     0x006E /* Wakeup Crystal Oscillator Early */
#define AX5043_IFFREQ1           0xF100 /* 2nd LO / IF Frequency 1 */
#define AX5043_IFFREQ0           0xF101 /* 2nd LO / IF Frequency 0 */
#define AX5043_DECIMATION        0xF102 /* Decimation Factor */
#define AX5043_RXDATARATE2       0xF103 /* Receiver Datarate 2 */
#define AX5043_RXDATARATE1       0xF104 /* Receiver Datarate 1 */
#define AX5043_RXDATARATE0       0xF105 /* Receiver Datarate 0 */
#define AX5043_MAXDROFFSET2      0xF106 /* Maximum Receiver Datarate Offset 2 */
#define AX5043_MAXDROFFSET1      0xF107 /* Maximum Receiver Datarate Offset 1 */
#define AX5043_MAXDROFFSET0      0xF108 /* Maximum Receiver Datarate Offset 0 */
#define AX5043_MAXRFOFFSET2      0xF109 /* Maximum Receiver RF Offset 2 */
#define AX5043_MAXRFOFFSET1      0xF10A /* Maximum Receiver RF Offset 1 */
#define AX5043_MAXRFOFFSET0      0xF10B /* Maximum Receiver RF Offset 0 */
#define AX5043_FSKDMAX1          0xF10C /* Four FSK Rx Maximum Deviation 1 */
#define AX5043_FSKDMAX0          0xF10D /* Four FSK Rx Maximum Deviation 0 */
#define AX5043_FSKDMIN1          0xF10E /* Four FSK Rx Minimum Deviation 1 */
#define AX5043_FSKDMIN0          0xF10F /* Four FSK Rx Minimum Deviation 0 */
#define AX5043_AFSKSPACE1        0xF110 /* AFSK Space (0) Frequency 1 */
#define AX5043_AFSKSPACE0        0xF111 /* AFSK Space (0) Frequency 0 */
#define AX5043_AFSKMARK1         0xF112 /* AFSK Mark (1) Frequency 1 */
#define AX5043_AFSKMARK0         0xF113 /* AFSK Mark (1) Frequency 0 */
#define AX5043_AFSKCTRL          0xF114 /* AFSK Control */
#define AX5043_AMPLFILTER        0xF115 /* Amplitude Filter */
#define AX5043_FREQUENCYLEAK     0xF116 /* Baseband Frequency Recovery Loop Leakiness */
#define AX5043_RXPARAMSETS       0xF117 /* Receiver Parameter Set Indirection */
#define AX5043_RXPARAMCURSET     0xF118 /* Receiver Parameter Current Set */
#define AX5043_AGCGAIN0          0xF120 /* AGC Speed */
#define AX5043_AGCTARGET0        0xF121 /* AGC Target */
#define AX5043_AGCAHYST0         0xF122 /* AGC Analog Hysteresis */
#define AX5043_AGCMINMAX0        0xF123 /* AGC Analog Update Behaviour */
#define AX5043_TIMEGAIN0         0xF124 /* Time Estimator Bandwidth */
#define AX5043_DRGAIN0           0xF125 /* Data Rate Estimator Bandwidth */
#define AX5043_PHASEGAIN0        0xF126 /* Phase Estimator Bandwidth */
#define AX5043_FREQUENCYGAINA0   0xF127 /* Frequency Estimator Bandwidth A */
#define AX5043_FREQUENCYGAINB0   0xF128 /* Frequency Estimator Bandwidth B */
#define AX5043_FREQUENCYGAINC0   0xF129 /* Frequency Estimator Bandwidth C */
#define AX5043_FREQUENCYGAIND0   0xF12A /* Frequency Estimator Bandwidth D */
#define AX5043_AMPLITUDEGAIN0    0xF12B /* Amplitude Estimator Bandwidth */
#define AX5043_FREQDEV10         0xF12C /* Receiver Frequency Deviation 1 */
#define AX5043_FREQDEV00         0xF12D /* Receiver Frequency Deviation 0 */
#define AX5043_FOURFSK0          0xF12E /* Four FSK Control */
#define AX5043_BBOFFSRES0        0xF12F /* Baseband Offset Compensation Resistors */
#define AX5043_AGCGAIN1          0xF130 /* AGC Speed */
#define AX5043_AGCTARGET1        0xF131 /* AGC Target */
#define AX5043_AGCAHYST1         0xF132 /* AGC Analog Hysteresis */
#define AX5043_AGCMINMAX1        0xF133 /* AGC Analog Update Behaviour */
#define AX5043_TIMEGAIN1         0xF134 /* Time Estimator Bandwidth */
#define AX5043_DRGAIN1           0xF135 /* Data Rate Estimator Bandwidth */
#define AX5043_PHASEGAIN1        0xF136 /* Phase Estimator Bandwidth */
#define AX5043_FREQUENCYGAINA1   0xF137 /* Frequency Estimator Bandwidth A */
#define AX5043_FREQUENCYGAINB1   0xF138 /* Frequency Estimator Bandwidth B */
#define AX5043_FREQUENCYGAINC1   0xF139 /* Frequency Estimator Bandwidth C */
#define AX5043_FREQUENCYGAIND1   0xF13A /* Frequency Estimator Bandwidth D */
#define AX5043_AMPLITUDEGAIN1    0xF13B /* Amplitude Estimator Bandwidth */
#define AX5043_FREQDEV11         0xF13C /* Receiver Frequency Deviation 1 */
#define AX5043_FREQDEV01         0xF13D /* Receiver Frequency Deviation 0 */
#define AX5043_FOURFSK1          0xF13E /* Four FSK Control */
#define AX5043_BBOFFSRES1        0xF13F /* Baseband Offset Compensation Resistors */
#define AX5043_AGCGAIN2          0xF140 /* AGC Speed */
#define AX5043_AGCTARGET2        0xF141 /* AGC Target */
#define AX5043_AGCAHYST2         0xF142 /* AGC Analog Hysteresis */
#define AX5043_AGCMINMAX2        0xF143 /* AGC Analog Update Behaviour */
#define AX5043_TIMEGAIN2         0xF144 /* Time Estimator Bandwidth */
#define AX5043_DRGAIN2           0xF145 /* Data Rate Estimator Bandwidth */
#define AX5043_PHASEGAIN2        0xF146 /* Phase Estimator Bandwidth */
#define AX5043_FREQUENCYGAINA2   0xF147 /* Frequency Estimator Bandwidth A */
#define AX5043_FREQUENCYGAINB2   0xF148 /* Frequency Estimator Bandwidth B */
#define AX5043_FREQUENCYGAINC2   0xF149 /* Frequency Estimator Bandwidth C */
#define AX5043_FREQUENCYGAIND2   0xF14A /* Frequency Estimator Bandwidth D */
#define AX5043_AMPLITUDEGAIN2    0xF14B /* Amplitude Estimator Bandwidth */
#define AX5043_FREQDEV12         0xF14C /* Receiver Frequency Deviation 1 */
#define AX5043_FREQDEV02         0xF14D /* Receiver Frequency Deviation 0 */
#define AX5043_FOURFSK2          0xF14E /* Four FSK Control */
#define AX5043_BBOFFSRES2        0xF14F /* Baseband Offset Compensation Resistors */
#define AX5043_AGCGAIN3          0xF150 /* AGC Speed */
#define AX5043_AGCTARGET3        0xF151 /* AGC Target */
#define AX5043_AGCAHYST3         0xF152 /* AGC Analog Hysteresis */
#define AX5043_AGCMINMAX3        0xF153 /* AGC Analog Update Behaviour */
#define AX5043_TIMEGAIN3         0xF154 /* Time Estimator Bandwidth */
#define AX5043_DRGAIN3           0xF155 /* Data Rate Estimator Bandwidth */
#define AX5043_PHASEGAIN3        0xF156 /* Phase Estimator Bandwidth */
#define AX5043_FREQUENCYGAINA3   0xF157 /* Frequency Estimator Bandwidth A */
#define AX5043_FREQUENCYGAINB3   0xF158 /* Frequency Estimator Bandwidth B */
#define AX5043_FREQUENCYGAINC3   0xF159 /* Frequency Estimator Bandwidth C */
#define AX5043_FREQUENCYGAIND3   0xF15A /* Frequency Estimator Bandwidth D */
#define AX5043_AMPLITUDEGAIN3    0xF15B /* Amplitude Estimator Bandwidth */
#define AX5043_FREQDEV13         0xF15C /* Receiver Frequency Deviation 1 */
#define AX5043_FREQDEV03         0xF15D /* Receiver Frequency Deviation 0 */
#define AX5043_FOURFSK3          0xF15E /* Four FSK Control */
#define AX5043_BBOFFSRES3        0xF15F /* Baseband Offset Compensation Resistors */
#define AX5043_MODCFGF           0xF160 /* Modulator Configuration F */
#define AX5043_FSKDEV2           0xF161 /* FSK Deviation 2 */
#define AX5043_FSKDEV1           0xF162 /* FSK Deviation 1 */
#define AX5043_FSKDEV0           0xF163 /* FSK Deviation 0 */
#define AX5043_MODCFGA           0xF164 /* Modulator Configuration A */
#define AX5043_TXRATE2           0xF165 /* Transmitter Bitrate 2 */
#define AX5043_TXRATE1           0xF166 /* Transmitter Bitrate 1 */
#define AX5043_TXRATE0           0xF167 /* Transmitter Bitrate 0 */
#define AX5043_TXPWRCOEFFA1      0xF168 /* Transmitter Predistortion Coefficient A 1 */
#define AX5043_TXPWRCOEFFA0      0xF169 /* Transmitter Predistortion Coefficient A 0 */
#define AX5043_TXPWRCOEFFB1      0xF16A /* Transmitter Predistortion Coefficient B 1 */
#define AX5043_TXPWRCOEFFB0      0xF16B /* Transmitter Predistortion Coefficient B 0 */
#define AX5043_TXPWRCOEFFC1      0xF16C /* Transmitter Predistortion Coefficient C 1 */
#define AX5043_TXPWRCOEFFC0      0xF16D /* Transmitter Predistortion Coefficient C 0 */
#define AX5043_TXPWRCOEFFD1      0xF16E /* Transmitter Predistortion Coefficient D 1 */
#define AX5043_TXPWRCOEFFD0      0xF16F /* Transmitter Predistortion Coefficient D 0 */
#define AX5043_TXPWRCOEFFE1      0xF170 /* Transmitter Predistortion Coefficient E 1 */
#define AX5043_TXPWRCOEFFE0      0xF171 /* Transmitter Predistortion Coefficient E 0 */
#define AX5043_PLLVCOI           0xF180 /* PLL VCO Current */
#define AX5043_PLLVCOIR          0xF181 /* PLL VCO Current Readback */
#define AX5043_PLLLOCKDET        0xF182 /* PLL Lock Detect Delay */
#define AX5043_PLLRNGCLK         0xF183 /* PLL Autoranging Clock */
#define AX5043_XTALCAP           0xF184 /* Crystal Oscillator Load Capacitance */
#define AX5043_BBTUNE            0xF188 /* Baseband Tuning */
#define AX5043_BBOFFSCAP         0xF189 /* Baseband Offset Compensation Capacitors */
#define AX5043_PKTADDRCFG        0xF200 /* Packet Address Config */
#define AX5043_PKTLENCFG         0xF201 /* Packet Length Configuration */
#define AX5043_PKTLENOFFSET      0xF202 /* Packet Length Offset */
#define AX5043_PKTMAXLEN         0xF203 /* Packet Maximum Length */
#define AX5043_PKTADDR3          0xF204 /* Packet Address 3 */
#define AX5043_PKTADDR2          0xF205 /* Packet Address 2 */
#define AX5043_PKTADDR1          0xF206 /* Packet Address 1 */
#define AX5043_PKTADDR0          0xF207 /* Packet Address 0 */
#define AX5043_PKTADDRMASK3      0xF208 /* Packet Address Mask 3 */
#define AX5043_PKTADDRMASK2      0xF209 /* Packet Address Mask 2 */
#define AX5043_PKTADDRMASK1      0xF20A /* Packet Address Mask 1 */
#define AX5043_PKTADDRMASK0      0xF20B /* Packet Address Mask 0 */
#define AX5043_MATCH0PAT3        0xF210 /* Pattern Match Unit 0, Pattern 3 */
#define AX5043_MATCH0PAT2        0xF211 /* Pattern Match Unit 0, Pattern 2 */
#define AX5043_MATCH0PAT1        0xF212 /* Pattern Match Unit 0, Pattern 1 */
#define AX5043_MATCH0PAT0        0xF213 /* Pattern Match Unit 0, Pattern 0 */
#define AX5043_MATCH0LEN         0xF214 /* Pattern Match Unit 0, Pattern Length */
#define AX5043_MATCH0MIN         0xF215 /* Pattern Match Unit 0, Minimum Match */
#define AX5043_MATCH0MAX         0xF216 /* Pattern Match Unit 0, Maximum Match */
#define AX5043_MATCH1PAT1        0xF218 /* Pattern Match Unit 1, Pattern 1 */
#define AX5043_MATCH1PAT0        0xF219 /* Pattern Match Unit 1, Pattern 0 */
#define AX5043_MATCH1LEN         0xF21C /* Pattern Match Unit 1, Pattern Length */
#define AX5043_MATCH1MIN         0xF21D /* Pattern Match Unit 1, Minimum Match */
#define AX5043_MATCH1MAX         0xF21E /* Pattern Match Unit 1, Maximum Match */
#define AX5043_TMGTXBOOST        0xF220 /* Transmit PLL Boost Time */
#define AX5043_TMGTXSETTLE       0xF221 /* Transmit PLL (post Boost) Settling Time */
#define AX5043_TMGRXBOOST        0xF223 /* Receive PLL Boost Time */
#define AX5043_TMGRXSETTLE       0xF224 /* Receive PLL (post Boost) Settling Time */
#define AX5043_TMGRXOFFSACQ      0xF225 /* Receive Baseband DC Offset Acquisition Time */
#define AX5043_TMGRXCOARSEAGC    0xF226 /* Receive Coarse AGC Time */
#define AX5043_TMGRXAGC          0xF227 /* Receiver AGC Settling Time */
#define AX5043_TMGRXRSSI         0xF228 /* Receiver RSSI Settling Time */
#define AX5043_TMGRXPREAMBLE1    0xF229 /* Receiver Preamble 1 Timeout */
#define AX5043_TMGRXPREAMBLE2    0xF22A /* Receiver Preamble 2 Timeout */
#define AX5043_TMGRXPREAMBLE3    0xF22B /* Receiver Preamble 3 Timeout */
#define AX5043_RSSIREFERENCE     0xF22C /* RSSI Offset */
#define AX5043_RSSIABSTHR        0xF22D /* RSSI Absolute Threshold */
#define AX5043_BGNDRSSIGAIN      0xF22E /* Background RSSI Averaging Time Constant */
#define AX5043_BGNDRSSITHR       0xF22F /* Background RSSI Relative Threshold */
#define AX5043_PKTCHUNKSIZE      0xF230 /* Packet Chunk Size */
#define AX5043_PKTMISCFLAGS      0xF231 /* Packet Controller Miscellaneous Flags */
#define AX5043_PKTSTOREFLAGS     0xF232 /* Packet Controller Store Flags */
#define AX5043_PKTACCEPTFLAGS    0xF233 /* Packet Controller Accept Flags */
#define AX5043_GPADCCTRL         0xF300 /* General Purpose ADC Control */
#define AX5043_GPADCPERIOD       0xF301 /* GPADC Sampling Period */
#define AX5043_GPADC13VALUE1     0xF308 /* GPADC13 Value 1 */
#define AX5043_GPADC13VALUE0     0xF309 /* GPADC13 Value 0 */
#define AX5043_LPOSCCONFIG       0xF310 /* Low Power Oscillator Calibration Configuration */
#define AX5043_LPOSCSTATUS       0xF311 /* Low Power Oscillator Calibration Status */
#define AX5043_LPOSCKFILT1       0xF312 /* Low Power Oscillator Calibration Filter Constant High Byte */
#define AX5043_LPOSCKFILT0       0xF313 /* Low Power Oscillator Calibration Filter Constant Low Byte */
#define AX5043_LPOSCREF1         0xF314 /* Low Power Oscillator Reference Frequency High Byte */
#define AX5043_LPOSCREF0         0xF315 /* Low Power Oscillator Reference Frequency Low Byte */
#define AX5043_LPOSCFREQ1        0xF316 /* Low Power Oscillator Frequency Tuning High Byte */
#define AX5043_LPOSCFREQ0        0xF317 /* Low Power Oscillator Frequency Tuning Low Byte */
#define AX5043_LPOSCPER1         0xF318 /* Low Power Oscillator Period High Byte */
#define AX5043_LPOSCPER0         0xF319 /* Low Power Oscillator Period Low Byte */
#define AX5043_DACVALUE1         0xF330 /* DAC Value 1 */
#define AX5043_DACVALUE0         0xF331 /* DAC Value 0 */
#define AX5043_DACCONFIG         0xF332 /* DAC Configuration */
#define AX5043_0xF00             0xFF00
#define AX5043_POWCTRL1          0xFF08 /* Power Control 1 */
#define AX5043_0xF0C             0xFF0C
#define AX5043_REF               0xFF0D /* Reference */
#define AX5043_XTALOSC           0xFF10 /* Crystal Oscillator Control */
#define AX5043_XTALAMPL          0xFF11 /* Crystal Oscillator Amplitude Control */
#define AX5043_0xF18             0xFF18
#define AX5043_0xF1C             0xFF1C
#define AX5043_0xF21             0xFF21
#define AX5043_0xF22             0xFF22
#define AX5043_0xF23             0xFF23
#define AX5043_0xF26             0xFF26
#define AX5043_0xF30             0xFF30
#define AX5043_0xF31             0xFF31
#define AX5043_0xF32             0xFF32
#define AX5043_0xF33             0xFF33
#define AX5043_0xF34             0xFF34
#define AX5043_0xF35             0xFF35
#define AX5043_0xF44             0xFF44
#define AX5043_MODCFGP           0xFF5F /* Modulator Configuration P */


void radio_init();

void uhf_init();

bool radio_autorange(int carrierHz, int xtalHz);

void radio_transmit(int numBytes, uint8_t *bytesToSend);

bool radio_receive();

void ax5043_write8(uint8_t address, uint8_t data);
uint8_t ax5043_read8(uint32_t address);

typedef struct PACKET_STRUCT {
    int pkt[256];
    int length;
    int isPacketStart;
    int isPacketEnd;
} packet_t;

#endif
