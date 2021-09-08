/* Includes ------------------------------------------------------------------*/
#include "memconf.h"
#include <cpuid.h>



//--------------- Variables ---------------------------------
volatile uint32_t memory_conf[ MAX_SETTINGS_PARAMS ]			= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };



void READ_MEMORY_SETTINGS(void)
{
	uint32_t memory_address = BANK1_WRITE_START_ADDR;
	uint8_t i = 0;

	while( memory_address < BANK1_WRITE_END_ADDR){
		memory_conf[ i++ ] = (*(__IO uint32_t*) memory_address);
		memory_address += 4;

		// Зачем память заполнять мусором и делать лишние операции, если можно выйти раньше
		if( i > MAX_SETTINGS_PARAMS ) break;
	}

	//FIXME: А нужно ли тратить 4байта и лишние операции на это!?
	if( memory_conf[ settings_param_nrd_uid ] > 0xFFFF ){
		memory_conf[ settings_param_nrd_uid ] = (CPU_UID & 0xFFFF);
	}

/*
	if (memory_conf[1]<=4090) { vol_decect_sh_1 = memory_conf[1]; } else { vol_decect_sh_1 = 100; }//POSh
	if (memory_conf[2]<=4090) { vol_decect_sh_2 = memory_conf[2]; } else { vol_decect_sh_2 = 0; }//POSh
	if (memory_conf[3]<=4090) { vol_on_sh_1 = memory_conf[3]; } else { vol_on_sh_1 = 2000; }//POSh
	if (memory_conf[4]<=4090) { vol_on_sh_2 = memory_conf[4]; } else { vol_on_sh_2 = 2000; }//POSh
	if (memory_conf[5]<=1200) { vol_time_move = memory_conf[5]; } else { vol_time_move = 40; }//t_pusk
	if (memory_conf[6]<=10)   { vol_acsel_move = memory_conf[6]; } else { vol_acsel_move = 3; }//pusk
	if (memory_conf[7]<=20)   { vol_cor_limit = memory_conf[7]; } else { vol_cor_limit = 20; }//pusk
	if (memory_conf[8]<=1200) { vol_time_priotkr = memory_conf[8]; } else { vol_time_priotkr = 30; }//pusk
	if (memory_conf[9]<=1200) { vol_time_priotkr2 = memory_conf[9]; } else { vol_time_priotkr2 = 30; }//pusk
	if (memory_conf[10]<=10)   { vol_resm_out_1 = memory_conf[10]; } else { vol_resm_out_1 = 0; }// out
//LCD
	if (memory_conf[11]<=600)  { vol_next_time_out = memory_conf[11]; } else { vol_next_time_out = 120; }//lcd
	if ((memory_conf[12]>20)&(memory_conf[12]<=99))  { vol_next_dim_max = memory_conf[12];  } else { vol_next_dim_max = 90; }//lcd
	if ((memory_conf[13]>4)&(memory_conf[13]<=99))   { vol_next_dim_min = memory_conf[13]; } else { vol_next_dim_min = 10; }//lcd
//Meteo
	if (memory_conf[14]<=900) { vol_block_meteo = memory_conf[14]; } else { vol_block_meteo = 60; }// Vremia block
	if (memory_conf[15]<=30)  { vol_wiat_meteo = memory_conf[15]; } else { vol_wiat_meteo = 2; }// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
	if (memory_conf[16]<=5)   { vol_resm_meteo = memory_conf[16]; } else { vol_resm_meteo = 0; }
	if (memory_conf[17]<=2)   { vol_resm_meteo_grp = memory_conf[17]; } else { vol_resm_meteo_grp = 1; }
//
	if (memory_conf[18]<=5)   { vol_resm_poshar = memory_conf[18]; } else { vol_resm_poshar = 3; }
	if (memory_conf[19]<=999) { Vol_Password = memory_conf[19]; } else { Vol_Password = 0; }
	if (memory_conf[20]<=MAX_DEVICES_COUNT)  { Nom_Dev_Im = memory_conf[20]; } else { Nom_Dev_Im = 1; }
	if (memory_conf[21]<=MAX_DEVICES_COUNT)  { Kolich_CAN = memory_conf[21]; } else { Kolich_CAN = 1; }
	if (memory_conf[22]<=MAX_DEVICES_COUNT)  { Master_Adr_CAN = memory_conf[22]; } else { Master_Adr_CAN = 1; }
	if (memory_conf[23]<=100) { Time_Find_CAN = memory_conf[23]; } else { Time_Find_CAN = 100; }
	if (memory_conf[24]<=2)   { Reshim_CAN = memory_conf[24]; } else { Reshim_CAN = 0; }
	if ((memory_conf[25]>300)&(memory_conf[25]<=6000)) { Vol_Time_Out_Work = memory_conf[25]; Time_Out_Work =  Vol_Time_Out_Work; } else { Vol_Time_Out_Work = 600; Time_Out_Work =  Vol_Time_Out_Work; }
	if (memory_conf[26]<=8)   { Nom_Grp_Im = memory_conf[26]; } else { Nom_Grp_Im = 1; }
	if ((memory_conf[27]>500)&(memory_conf[27]<=5000)) { Vol_Vcc_Clb = memory_conf[27];  } else { Vol_Vcc_Clb = 1550;  }
	if ((memory_conf[28]>500)&(memory_conf[28]<=5000)) { Vol_Vak_Clb = memory_conf[28]; } else { Vol_Vak_Clb = 1550; }
	if ((memory_conf[29]>0)&(memory_conf[29]<=600)) { vol_timeout_pusk = memory_conf[29]; } else { vol_timeout_pusk = 1; }
	if ((memory_conf[30]>0)&(memory_conf[30]<=600)) { vol_timeblock_pusk = memory_conf[30]; } else { vol_timeblock_pusk = 1; }
	if ((memory_conf[31]>0)&(memory_conf[31]<=600)) { vol_timekonz_pusk = memory_conf[31]; } else { vol_timekonz_pusk = 240; }
	if ((memory_conf[32]>0)&(memory_conf[32]<=3))   { resh_konz_pusk = memory_conf[32]; } else { resh_konz_pusk = 0; }
//Time
	if ((memory_conf[33]>2018)&(memory_conf[33]<=2050)) { vol_time_year = memory_conf[33]; }  else { vol_time_year = 2020; }
	if ((memory_conf[34]>1)&(memory_conf[34]<=12))      { vol_time_month = memory_conf[34]; } else { vol_time_month = 9; }
	if ((memory_conf[35]>1)&(memory_conf[35]<=31))      { vol_time_day = memory_conf[35]; }   else { vol_time_day = 1; }
	if ((memory_conf[36]>0)&(memory_conf[36]<=23))      { vol_time_hour = memory_conf[36]; }  else { vol_time_hour = 10; }
	if ((memory_conf[37]>0)&(memory_conf[37]<=59))      { vol_time_min = memory_conf[37]; }   else { vol_time_min = 0; }
	if ((memory_conf[38]>0)&(memory_conf[38]<=59))      { vol_time_sec = memory_conf[38]; }   else { vol_time_sec = 0; }
//DU
	if (memory_conf[39]<=Max_resm_du)   { vol_resm_du = memory_conf[39]; } else { vol_resm_du = 0; }
	if (memory_conf[40]<=Max_resm_aps)   { vol_resm_aps = memory_conf[40]; } else { vol_resm_aps = 0; }
	if (memory_conf[41]<=3)   { Master_VAC = memory_conf[41]; } else { Master_VAC = 0; }
	if (memory_conf[42]<=3)   { Fl_Avt_Block_Ruch = memory_conf[42]; } else { Fl_Avt_Block_Ruch = 0; }
	if (memory_conf[43]<=3600)   { Timer_Kvitir = memory_conf[43]; id_Timer_Kvitir = Timer_Kvitir; } else { Timer_Kvitir = 600; id_Timer_Kvitir = Timer_Kvitir; }
//DU GR
	if (memory_conf[44]<=1)   { vol_du_grp = memory_conf[44]; } else { vol_du_grp = 0; }
	if (memory_conf[45]<=1)   { vol_aps_grp = memory_conf[45];} else { vol_aps_grp = 0; }
//    Out_1_temp
	if (memory_conf[46]<=10)   { temp_resm_out_1_open_close = memory_conf[46];} else { temp_resm_out_1_open_close = 0; }
	if (memory_conf[47]<=64)   { id_work_klap = memory_conf[47]; } else { id_work_klap = 1; }
//Meteo
	if (memory_conf[48]<=255)   { vol_alarm_veter = memory_conf[48]; } else { vol_alarm_veter = 50; }
	if (memory_conf[49]<=255)   { vol_alarm_osadok = memory_conf[49]; } else { vol_alarm_osadok = 100; }
//DU2/APS2
	if (memory_conf[50]<=Max_resm_du)   { vol_resm_du2 = memory_conf[50]; } else { vol_resm_du2 = 0; }
	if (memory_conf[51]<=Max_resm_aps)  { vol_resm_aps2 = memory_conf[51]; } else { vol_resm_aps2 = 0; }
	if (memory_conf[52]<=4090) { vol_decect_sh2_1 = memory_conf[52]; } else { vol_decect_sh2_1 = 100; }
	if (memory_conf[53]<=4090) { vol_decect_sh2_2 = memory_conf[53]; } else { vol_decect_sh2_2 = 0; }
	if (memory_conf[54]<=4090) { vol_on_sh2_1 = memory_conf[54]; } else { vol_on_sh2_1 = 2000; }
	if (memory_conf[55]<=4090) { vol_on_sh2_2 = memory_conf[55]; } else { vol_on_sh2_2 = 2000; }
	if (memory_conf[56]<=1)   { vol_du2_grp = memory_conf[56]; } else { vol_du2_grp = 0; }
	if (memory_conf[57]<=1)   { vol_aps2_grp = memory_conf[57];} else { vol_aps2_grp = 0; }
	if (memory_conf[58]<=5)   { vol_resm_zone1 = memory_conf[58];} else { vol_resm_zone1 = 1; }
	if (memory_conf[59]<=5)   { vol_resm_zone2 = memory_conf[59];} else { vol_resm_zone2 = 1; }
//AKB
	if (memory_conf[60]<=2000)   { Vol_Min_UakbG = memory_conf[60];} else { Vol_Min_UakbG = 5; }
	if (memory_conf[61]<=100)    { Vol_Time_UakbG = memory_conf[61];} else { Vol_Time_UakbG = 10; }
//Zone
	if (memory_conf[62]<=Max_out_zone)  { vol_out_zone1 = memory_conf[62];} else { vol_out_zone1 = 0; }
	if (memory_conf[63]<=Max_out_zone)  { vol_out_zone2 = memory_conf[63];} else { vol_out_zone2 = 0; }
//In
	if (memory_conf[64]<=3)   { vol_resm_in1 = memory_conf[64];} else { vol_resm_in1 = 1; }
	if (memory_conf[65]<=3)   { vol_resm_in2 = memory_conf[65];} else { vol_resm_in2 = 1; }
	if (memory_conf[66]<=3)   { vol_resm_in3 = memory_conf[66];} else { vol_resm_in3 = 0; }
	if (memory_conf[67]<=3)   { vol_resm_in4 = memory_conf[67];} else { vol_resm_in4 = 0; }
//Out
	if (memory_conf[68]<=Max_ReshOut)   { vol_resm_out_2 = memory_conf[68]; } else { vol_resm_out_2 = 4; }
	if (memory_conf[69]<=Max_ReshOut)   { vol_resm_out_3 = memory_conf[69]; } else { vol_resm_out_3 = 3; }
	if (memory_conf[70]<=Max_ReshOut)   { vol_resm_out_4 = memory_conf[70]; } else { vol_resm_out_4 = 0; }
	if (memory_conf[71]<=Max_ReshOut)   { vol_resm_out_5 = memory_conf[71]; } else { vol_resm_out_5 = 0; }
	if (memory_conf[72]<=Max_ReshOut)   { vol_resm_out_6 = memory_conf[72]; } else { vol_resm_out_6 = 0; }
	if (memory_conf[73]<=Max_ReshOut)   { vol_resm_out_7 = memory_conf[73]; } else { vol_resm_out_7 = 0; }
//
	//if (memory_conf[74]<=120)   { Time_Move_M = memory_conf[74]; } else { Time_Move_M = 5; }
	if( memory_conf[ settings_param_time_move_m ] > 120 ) memory_conf[ settings_param_time_move_m ] = 5;
//LCD
   // if(memory_conf[ settings_param_resh_sleep ]<=5) { resh_sleep = memory_conf[ settings_param_resh_sleep ]; } else { resh_sleep = 1; }
	if( memory_conf[ settings_param_resh_sleep ] > 5 ) memory_conf[ settings_param_resh_sleep ] = 1;
//I
	if ((memory_conf[76]>2500)&(memory_conf[76]<=3600)) { Lev_Sred_Idrv = memory_conf[76]; } else { Lev_Sred_Idrv = 3150; }
	if ((memory_conf[77]>2500)&(memory_conf[77]<=3600)) { Lev_Sred_I2drv = memory_conf[77]; } else { Lev_Sred_I2drv = 3150; }
*/
//IP
	if( memory_conf[ settings_param_ip ] == 0x00000000 || memory_conf[ settings_param_ip ] == 0xFFFFFFFF ) memory_conf[ settings_param_ip ] = 3232238279;
}

void SAVE_MEMORY_SETTINGS(void)
{
	/*
	__disable_irq();
	while( HAL_FLASH_Unlock() != HAL_OK );

	
	HAL_FLASH_Unlock();
	uint32_t NbrOfPage = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR) / FLASH_PAGE_SIZE;
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);

	uint8_t i = 0;
	FLASH_Status FLASHStatus = FLASH_COMPLETE;

	for( i = 0; (i < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); i++){
		FLASHStatus = FLASH_ErasePage(BANK1_WRITE_START_ADDR + (FLASH_PAGE_SIZE * i));
	}

	
//
	memory_address = BANK1_WRITE_START_ADDR;
//

  memory_conf[1] = vol_decect_sh_1;
  memory_conf[2] = vol_decect_sh_2;
  memory_conf[3] = vol_on_sh_1;
  memory_conf[4] = vol_on_sh_2;
  memory_conf[5] = vol_time_move;
  memory_conf[6] = vol_acsel_move;
  memory_conf[7] = vol_cor_limit;
  memory_conf[8] = vol_time_priotkr;
  memory_conf[9] = vol_time_priotkr2;
  memory_conf[10] = vol_resm_out_1;
  memory_conf[11] = vol_next_time_out;
  memory_conf[12] = vol_next_dim_max;
  memory_conf[13] = vol_next_dim_min;
  memory_conf[14] = vol_block_meteo;
  memory_conf[15] = vol_wiat_meteo;
  memory_conf[16] = vol_resm_meteo;
  memory_conf[17] = vol_resm_meteo_grp;
  memory_conf[18] = vol_resm_poshar;
  memory_conf[19] = Vol_Password;
  memory_conf[20] = Nom_Dev_Im;
  memory_conf[21] = Kolich_CAN;
  memory_conf[22] = Master_Adr_CAN;
  memory_conf[23] = Time_Find_CAN;
  memory_conf[24] = Reshim_CAN;
  memory_conf[25] = Vol_Time_Out_Work;
  memory_conf[26] = Nom_Grp_Im;
  memory_conf[27] = Vol_Vcc_Clb;
  memory_conf[28] = Vol_Vak_Clb;
  memory_conf[29] = vol_timeout_pusk;
  memory_conf[30] = vol_timeblock_pusk;
  memory_conf[31] = vol_timekonz_pusk;
  memory_conf[32] = resh_konz_pusk;
  memory_conf[33] = vol_time_year;
  memory_conf[34] = vol_time_month;
  memory_conf[35] = vol_time_day;
  memory_conf[36] = vol_time_hour;
  memory_conf[37] = vol_time_min;
  memory_conf[38] = vol_time_sec;
  memory_conf[39] = vol_resm_du;
  memory_conf[40] = vol_resm_aps;
  memory_conf[41] = Master_VAC;
  memory_conf[42] = Fl_Avt_Block_Ruch;
  memory_conf[43] = Timer_Kvitir;
  memory_conf[44] = vol_du_grp;
  memory_conf[45] = vol_aps_grp;
  memory_conf[46] = temp_resm_out_1_open_close;
  memory_conf[47] = id_work_klap;
  memory_conf[48] = vol_alarm_veter;
  memory_conf[49] = vol_alarm_osadok;
  memory_conf[50] = vol_resm_du2;
  memory_conf[51] = vol_resm_aps2;
  memory_conf[52] = vol_decect_sh2_1;
  memory_conf[53] = vol_decect_sh2_2;
  memory_conf[54] = vol_on_sh2_1;
  memory_conf[55] = vol_on_sh2_2;
  memory_conf[56] = vol_du2_grp;
  memory_conf[57] = vol_aps2_grp;
  memory_conf[58] = vol_resm_zone1;
  memory_conf[59] = vol_resm_zone2;
  memory_conf[60] = Vol_Min_UakbG;
  memory_conf[61] = Vol_Time_UakbG;
  memory_conf[62] = vol_out_zone1;
  memory_conf[63] = vol_out_zone2;
  memory_conf[64] = vol_resm_in1;
  memory_conf[65] = vol_resm_in2;
  memory_conf[66] = vol_resm_in3;
  memory_conf[67] = vol_resm_in4;
  memory_conf[68] = vol_resm_out_2;
  memory_conf[69] = vol_resm_out_3;
  memory_conf[70] = vol_resm_out_4;
  memory_conf[71] = vol_resm_out_5;
  memory_conf[72] = vol_resm_out_6;
  memory_conf[73] = vol_resm_out_7;
  //memory_conf[74] = Time_Move_M;
  //memory_conf[75] = resh_sleep;
//
	

	i = 0;
	while(( memory_address < BANK1_WRITE_END_ADDR) && (FLASHStatus == FLASH_COMPLETE)){
		FLASHStatus = FLASH_ProgramWord( memory_address, memory_conf[ i++ ]);
		memory_address += 4;

		// Зачем память заполнять мусором и делать лижние операции, если можно выйти раньше
		if( i > MAX_SETTINGS_PARAMS ) break;
	}
	FLASH_LockBank1();
	
	while( HAL_FLASH_Lock() != HAL_OK );
	__enable_irq();
	*/
}

void SAVE_MEMORY_PARAM(const uint8_t paramID, const uint32_t value)
{
	__disable_irq();
	while( HAL_FLASH_Unlock() != HAL_OK );

	uint32_t addr = BANK1_WRITE_START_ADDR + ( paramID * 4 );

	HAL_StatusTypeDef status = HAL_ERROR;
	while( status != HAL_OK ){
		status = HAL_FLASH_Program( TYPEPROGRAM_WORD, addr, value );
	}

	while( HAL_FLASH_Lock() != HAL_OK );
	__enable_irq();
}
