/*
 * Autor Carlos Izquierdo Gómez
 *
 * Esta libreria se desarrollo como complemento al proyecto
 * TEO de la universidad Carlos 3 de Leganes
 *
 * Ultima revisión 17/05/2021
 */

#include "mbed.h"
#include <stdio.h>
#include<math.h> 
#include "DOGXL160.h"
#define NDecimas 1000

#define setComEndH              0xF1
#define setComEndL              0x67
#define setLCDMappingControl    0xC0
#define setScrollLineLSB        0x40
#define setScrollLineMSB        0x50
#define setPanelLoading         0x2B
#define setLCDBiasRatio         0xEB
#define setVbiasPotentiometerH  0x81
#define setVbiasPotentiometerL  0x5F
#define setRAMAddressControl    0x89
#define setDisplayEnable        0xAF



#define pageAddress 0x60
#define columnLSB0 0x00
#define columnMSB0 0x01
#define setAllPixelsOn 0xA5
#define systemReset 0xE2

char A[]={0x00,0x00,0x00,0x00,0x00,0xFC,0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,
          0x00,0x00,0x00,0xF0,0xFF,0x0F,0x00,0x0F,0xFF,0xF0,0x00,0x00,0x00,0x00,         //14 -> Nº de pixeles de ancho
          0x00,0xC0,0xFC,0xFF,0xF3,0xF0,0xF0,0xF0,0xF3,0xFF,0xFC,0xC0,0x00,0x00,
          0xf0,0xff,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0xFF,0xF0,0x00};
char a[]={0xC0,0xF0,0x3c,0x3c,0x3c,0x3c,0x3c,0xF0,0xC0,0x00,
          0xC0,0xF0,0xFC,0x3C,0x3C,0x3C,0x3C,0xFF,0xFF,0x00,                    //10
          0x3F,0xFF,0xF0,0xF0,0xF0,0xF0,0x3C,0xFF,0xFF,0x00};              
char B[]={0xfc,0xfc,0x3c,0x3c,0x3c,0x3c,0x3c,0xfc,0xf0,0xc0,0x00,0x00,
          0xff,0xff,0xc0,0xc0,0xc0,0xc0,0xc0,0xf0,0xff,0x3f,0x00,0x00,
          0xff,0xff,0x03,0x03,0x03,0x03,0x03,0x03,0x0f,0xff,0xfc,0x00,           //12
          0xff,0xff,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0x3c,0x3f,0x0f,0x00};
/*
char b[]={0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
          0xFF,0xFF,0xF0,0x3C,0x3C,0x3C,0xFC,0xFF,0xC0,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,                    //10
          0xFF,0xFF,0x3C,0xF0,0xF0,0xF0,0xFC,0x3F,0x0F,0x00};                              
*/
char C[]={0x00,0xC0,0xF0,0xF0,0x3C,0x3C,0x3C,0x3C,0xFC,0xF0,0xc0,0x00,0x00,
          0xFC,0xff,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x00,              //13
          0xff,0xff,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,0x00,
          0x00,0x0F,0x3F,0x3C,0xf0,0xf0,0xf0,0xf0,0xFC,0x3C,0x0f,0x03,0x00};
char c[]={0xC0,0xF0,0xFC,0x3C,0x3C,0x3C,0xFC,0xF0,0xC0,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00,                    //10
          0x0F,0x3F,0xFC,0xF0,0xF0,0xF0,0xFC,0x3F,0x0F,0x00,};            
char D[]={0xfc,0xfc,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0xf0,0xf0,0xc0,0x00,0x00,
          0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xff,0xfc,0x00,              //13
          0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xff,0xff,0x00,
          0xff,0xff,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0x3c,0x3f,0x0f,0x00,0x00};  
char d[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFC,0x00,
          0xC0,0xF0,0xFC,0x3C,0x3C,0x3C,0xF0,0xFF,0xFF,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,                //10
          0x0F,0x3F,0xFC,0xF0,0xF0,0xF0,0x3C,0xFF,0xFF,0x00};  
char E[]={0xfc,0xfc,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x00,
          0xff,0xff,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,
          0xff,0xff,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,                   //12
          0xff,0xff,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0x00};                                                  
char e[]={0xC0,0xF0,0xFC,0x3C,0x3C,0x3C,0xFC,0xF0,0xC0,0x00,
          0xFF,0xFF,0x3C,0x3C,0x3C,0x3C,0x3C,0x3F,0x3F,0x00,
          0x0F,0x3F,0xFC,0xF0,0xF0,0xF0,0xFC,0x3F,0x0F,0x00};           //10
char F[]={0xfc,0xfc,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x3c,0x00,
          0xff,0xff,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,
          0xff,0xff,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,              //12
          0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};              
/*
char f[]={0x00,0xF0,0xFC,0x3C,0x3C,0x00,
          0x3C,0xFF,0xFF,0x3C,0x3C,0x00,
          0x00,0xFF,0xFF,0x00,0x00,0x00,                                                //6
          0x00,0xFF,0xFF,0x00,0x00,0x00};  
*/
char G[]={0x00,0x00,0xF0,0xF0,0xFc,0x3c,0x3c,0x3c,0x3c,0xfC,0xF0,0xC0,0x00,0x00,
          0xfC,0xff,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x0F,0x00,             //14
          0xff,0xff,0xC0,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0F,0x0F,0xff,0xFF,0x00,
          0x00,0x0f,0x3F,0x3C,0xf0,0xf0,0xf0,0xf0,0xf0,0x3C,0x3C,0xFF,0xFF,0x00};  
char g[]={0xF0,0xFC,0x3F,0x0F,0x0F,0x0F,0x3C,0xFF,0xFF,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,                    //10
          0x03,0x0F,0x3F,0x3C,0x3C,0x3C,0x0F,0xFF,0xFF,0x00,
          0x3C,0xFC,0xF0,0xF0,0xF0,0xF0,0xFC,0x3F,0x03,0x00};  
char H[]={0xfC,0xfC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfC,0xfC,0x00,
          0xff,0xff,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xff,0xfF,0x00,
          0xff,0xff,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0xff,0xff,0x00,              //13
          0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xfF,0x00};  
char h[]={0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
          0xFF,0xFF,0xF0,0x3C,0x3C,0x3C,0xFC,0xF0,0xF0,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,                //10
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00};  
char I[]={0x3C,0x3C,0x3C,0x3C,0xfc,0xfc,0x3C,0x3C,0x3C,0x3C,0x00,
          0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,
          0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,
          0xF0,0xF0,0xF0,0xF0,0xff,0xff,0xF0,0xF0,0xF0,0xF0,0x00,};         //11
char i[]={0x3C,0x3C,0x00,
          0xFC,0xFC,0x00,
          0xFF,0xFF,0x00,                                                           //3
          0xFF,0xFF,0x00};  
          
char J[]={0x00,0x00,0x00,0x00,0x00,0x00,0xFc,0xFc,0x00,
          0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
          0xC0,0xC0,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,                                     //9
          0x0f,0x3f,0xfC,0xf0,0xf0,0xfC,0x3F,0x0F,0x00};  
      /*    
char j[]={0x00,0x0F,0x0F,0x00,
          0x00,0xFF,0xFF,0x00,
          0x00,0xFF,0xFF,0x00,                                          //4
          0xF0,0xFF,0x3F,0x00};  
*/          
char K[]={0xfc,0xfc,0x00,0x00,0x00,0x00,0x00,0xC0,0xf0,0x3C,0x0C,0x00,0x00,
          0xff,0xff,0x00,0xC0,0xF0,0xFC,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,
          0xff,0xff,0x0F,0x03,0x03,0x0F,0x3C,0xF0,0xC0,0x00,0x00,0x00,0x00,          //13
          0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x3C,0xF0,0xC0,0x00};  
          /*
char k[]={0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
          0xFF,0xFF,0x00,0x00,0xC0,0xF0,0x30,0x0C,0x00,0x00,
          0xFF,0xFF,0x3C,0x3F,0xF3,0xC0,0x00,0x00,0x00,0x00,                    //10
          0xFF,0xFF,0x00,0x00,0x00,0x0F,0x3F,0xF0,0xC0,0x00};  
          */
char L[]={0xfc,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
          0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
          0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,               //12
          0xff,0xff,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0x00};  
char l[]={0xFC,0xFC,0x00,
          0xFF,0xFF,0x00,                                                               //3
          0xFF,0xFF,0x00,
          0xFF,0xFF,0x00};  
char M[]={0xfc,0xfc,0xfc,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFC,0xFC,0xFC,0x00,
          0xff,0xff,0x03,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0xfC,0xfF,0x03,0xFF,0xFF,0x00,       //16
          0xff,0xff,0x00,0x00,0x0F,0xFF,0xF0,0x00,0xF0,0xFF,0x0F,0x00,0x00,0xFF,0xFF,0x00,                   
          0xff,0xff,0x00,0x00,0x00,0x03,0xfF,0xfC,0xFF,0x03,0x00,0x00,0x00,0xFF,0xFF,0x00};  
char m[]={0xFC,0xFC,0xF0,0x3C,0x3C,0x3C,0xFC,0xF0,0xF0,0x3C,0x3C,0x3C,0xFC,0xF0,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,           //15
          0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00};  
char N[]={0xfc,0xfc,0xF0,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFC,0x00,
          0xff,0xff,0x03,0x0F,0xFC,0xF0,0x00,0x00,0x00,0x00,0xff,0xfF,0x00,
          0xff,0xff,0x00,0x00,0x00,0x03,0x3F,0xFC,0xC0,0x00,0xff,0xff,0x00,              //13
          0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x3f,0xFf,0xFF,0x00};  
char n[]={0xFC,0xFC,0xF0,0x3C,0x3C,0x3C,0xFC,0xF0,0xC0,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,                //10
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00};

char O[]={0x00,0xc0,0xf0,0xF0,0x3c,0x3c,0x3c,0x3c,0x3c,0xf0,0xf0,0xc0,0x00,0x00,
          0xfC,0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFC,0x00,
          0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0x00,            //14
          0x00,0x0F,0x3F,0x3C,0xF0,0xF0,0xF0,0xF0,0xF0,0x3C,0x3F,0x0F,0x00,0x00};  
char o[]={0xC0,0xF0,0xFC,0x3C,0x3C,0x3C,0xFC,0xF0,0xC0,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,                        //10
          0x0F,0x3F,0xFC,0xF0,0xF0,0xF0,0xFC,0x3F,0x0F,0x00};  
char P[]={0xFC,0xFC,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0xFC,0xF0,0xC0,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0x00,
          0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x03,0x03,0x00,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};             //12
/*
char p[]={0xFF,0xFF,0x3C,0x0F,0x0F,0x0F,0x3F,0xFC,0xF0,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
          0xFF,0xFF,0x0F,0x3C,0x3C,0x3C,0x3C,0x0F,0x03,0x00,                //10
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};  
char Q[]={0x00,0xF0,0xFC,0x3C,0x0F,0x0F,0x0F,0x0F,0x0F,0x3C,0xFC,0xF0,0x00,0x00,
          0xFF,0xFF,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0x00,    //14
          0x3F,0xFF,0xF0,0x00,0x00,0x00,0x00,0xC0,0xF0,0x00,0xF0,0xFF,0x3F,0x00,
          0x00,0x03,0x0F,0x0F,0x3C,0x3C,0x3C,0x3C,0x3F,0x0F,0x0F,0x3F,0xF0,0x00};  
char q[]={0xF0,0xFC,0x3F,0x0F,0x0F,0x0F,0x3C,0xFF,0xFF,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
          0x03,0x0F,0x3F,0x3C,0x3C,0x3C,0x0F,0xFF,0xFF,0x00,                        //10
          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00};  
*/
char R[]={0xFC,0xFC,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0xFC,0xF0,0xC0,0x00,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0x00,0x00,
          0xFF,0xFF,0x0F,0x0F,0x0F,0x0F,0x0F,0x3F,0xF3,0xC3,0x00,0x00,0x00,         //13
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xC0,0x00};  
char r[]={0xFC,0xFC,0xF0,0x3C,0x3C,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,                                        //6
          0xFF,0xFF,0x00,0x00,0x00,0x00};  

char S[]={0xC0,0xF0,0xF0,0x3C,0x3C,0x3C,0x3C,0x3C,0xF0,0xF0,0x00,0x00,
          0x3F,0xFF,0xF0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0x0F,0x0F,0x00,              //12
          0xC0,0xC0,0x00,0x03,0x03,0x03,0x03,0x0F,0x0F,0xFC,0xF0,0x00,
          0x03,0x3F,0x3C,0xFC,0xF0,0xF0,0xF0,0xF0,0x3C,0x3F,0x0F,0x00};  
char s[]={0xF0,0xF0,0x3C,0x3C,0x3C,0x3C,0xF0,0xF0,0x00,
          0x0F,0x0F,0x3C,0x3C,0x3C,0xF0,0xF0,0xC0,0x00,                             //9
          0x3C,0x3C,0xF0,0xF0,0xF0,0xF0,0x3F,0x0F,0x00};  
char T[]={0x3C,0x3C,0x3C,0x3C,0x3C,0xFC,0xFC,0x3C,0x3C,0x3C,0x3C,0x3C,0x00,
          0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
          0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
          0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00};            //13
char t[]={0x00,0xF0,0xF0,0x00,0x00,0x00,
          0x3C,0xFF,0xFF,0x3C,0x3C,0x00,
          0x00,0xFF,0xFF,0x00,0x00,0x00,                                            //6
          0x00,0x3F,0xFF,0xF0,0xF0,0x00};  
char U[]={0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0xFC,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,         //13
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,
          0x03,0x3F,0x3F,0xFC,0xF0,0xF0,0xF0,0xF0,0xFC,0x3F,0x3F,0x03,0x00};  
char u[]={0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0xFC,0xFC,0x00,
          0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,                        //10
          0x0F,0x3F,0xFC,0xF0,0xF0,0xF0,0x3C,0xFF,0xFF,0x00};  
char V[]={0x3C,0xFC,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFC,0x3C,0x00,
          0x00,0x0F,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,0x0F,0x00,0x00,                //14
          0x00,0x00,0x00,0x3F,0xFF,0xC0,0x00,0xC0,0xFF,0x3F,0x00,0x00,0x00,0x00,
          0x00,0x00,0x00,0x00,0x03,0xFF,0xFC,0xFF,0x03,0x00,0x00,0x00,0x00,0x00};  
char v[]={0x3C,0xFC,0x30,0x00,0x00,0x00,0x00,0xC0,0xFC,0x3C,0x00,
          0x00,0x0F,0xFF,0xF0,0x00,0x00,0xF0,0xFF,0x0F,0x00,0x00,                       //11
          0x00,0x00,0x00,0x0F,0xFF,0xFF,0x0F,0x00,0x00,0x00,0x00}; 
           
char W[]={0x3C,0xFC,0xC0,0x00,0x00,0x00,0x00,0x00,0xFC,0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0xC0,0xFC,0x3c,0x00,
          0x00,0x3F,0xFF,0xC0,0x00,0x00,0xC0,0xFF,0x3F,0x00,0x3F,0xFF,0xC0,0x00,0x00,0xC0,0xFF,0x3F,0x00,0x00,
          0x00,0x00,0x0F,0xFF,0xF0,0xC0,0xFF,0x3F,0x00,0x00,0x00,0x3F,0xFF,0xC0,0xF0,0xFF,0x0F,0x00,0x00,0x00,   //20
          0x00,0x00,0x00,0x0F,0xFF,0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0x0F,0x00,0x00,0x00,0x00};  
/*
char w[]={0x3C,0xFC,0xC0,0x00,0x00,0xC0,0xFC,0xFC,0xC0,0x00,0x00,0xC0,0xFC,0x3C,0x00,
          0x00,0x0F,0xFF,0xF0,0xC0,0xFF,0x0F,0x0F,0xFF,0xC0,0xF0,0xFF,0x0F,0x00,0x00,
          0x00,0x00,0x0F,0xFF,0xFF,0x03,0x00,0x00,0x03,0xFF,0xFF,0x0F,0x00,0x00,0x00};  //15
char X[]={0x0C,0x3C,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0x3C,0x0C,0x00,
          0x00,0x00,0x00,0x0F,0x3F,0xF0,0xC0,0xF0,0x3F,0x0F,0x00,0x00,0x00,0x00,
          0x00,0x00,0x00,0xC0,0xF0,0x3C,0x0F,0x3C,0xF0,0xC0,0x00,0x00,0x00,0x00,
          0xC0,0xF0,0x3C,0x0F,0x03,0x00,0x00,0x00,0x03,0x0F,0x3C,0xF0,0xC0,0x00}; 
                 //14
char x[]={0x0C,0x3C,0xF0,0xC0,0x00,0x00,0xC0,0xF0,0x3C,0x0C,0x00,
          0x00,0x00,0x03,0xCF,0xFC,0xFC,0xCF,0x03,0x00,0x00,0x00,                           //11
          0xC0,0xF0,0x3F,0x0F,0x00,0x00,0x0F,0x3F,0xF0,0xC0,0x00}; 
*/           
char Y[]={0x0C,0xFC,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFC,0x0C,0x00,
          0x00,0x00,0x03,0x0F,0xFC,0xF0,0x00,0x00,0xF0,0xFC,0x0F,0x03,0x00,0x00,0x00,
          0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
          0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00};          //15
char y[]={0x0F,0xFF,0xF0,0x00,0x00,0x00,0x00,0xF0,0xFF,0x0F,0x00,
          0x00,0x03,0x3F,0xFC,0xC0,0xC0,0xFC,0x3F,0x03,0x00,0x00,
          0x00,0x00,0x00,0x03,0xFF,0xFF,0x03,0x00,0x00,0x00,0x00,
          0x00,0xF0,0xF0,0xFC,0x0F,0x00,0x00,0x00,0x00,0x00,0x00};  
char Z[]={0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0xFC,0xFC,0x00,
          0x00,0x00,0x00,0x00,0x00,0xF0,0xFC,0x0F,0x03,0x00,0x00,
          0x00,0x00,0xC0,0xFC,0x3F,0x03,0x00,0x00,0x00,0x00,0x00,                               //11
          0xFC,0xFF,0xF3,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0x00};  
/*
char z[]={0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0xFC,0xFC,0x00,
          0x00,0x00,0xC0,0xF0,0x3C,0x0F,0x03,0x00,0x00,
          0xFC,0xFF,0xF3,0xF0,0xF0,0xF0,0xF0,0xF0,0x00}; 

*/
char cero[]={0x00,0xC0,0xF0,0x3C,0x3C,0x3C,0x3C,0xF0,0xC0,0x00,0x00,    //11
             0xFC,0xFF,0x03,0x00,0x00,0x00,0x00,0x03,0xFF,0xFC,0x00, 
             0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00, 
             0x03,0x0F,0x3F,0xF0,0xF0,0xF0,0xF0,0x3F,0x0F,0x03,0x00};                 
char uno[]={0x00,0x00,0x00,0xC0,0xFC,0xFC,0x00, 
            0x0F,0x0F,0x0F,0x03,0xFF,0xFF,0x00,
            0x00,0x00,0x00,0x00,0xFF,0xFF,0x00, 
            0x00,0x00,0x00,0x00,0xFF,0xFF,0x00};
char dos[]={0xC0,0xF0,0xFC,0x3C,0x3C,0x3C,0x3C,0xFC,0xF0,0xC0,0x00,
            0x03,0x03,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0x3F,0x00,
            0x00,0x00,0x00,0xC0,0xF0,0x3C,0x0C,0x0F,0x03,0x00,0x00,
            0xF0,0xFC,0xFF,0xF3,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0x00};
char tres[]={0xC0,0xF0,0xFC,0x3C,0x3C,0x3C,0xFC,0xF0,0xC0,0x00,0x00, 
             0x03,0x03,0x00,0x00,0xC0,0xC0,0xF0,0xFF,0x3F,0x00,0x00,
             0x00,0x00,0x00,0x00,0x03,0x03,0x03,0x0F,0xFF,0xF0,0x00,
             0x0F,0x3F,0xFC,0xF0,0xF0,0xF0,0xF0,0x3C,0x3F,0x0F,0x00};
char cuatro[]={0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0xFC,0xFC,0x00,0x00,0x00, 
               0x00,0x00,0xC0,0xF0,0x3C,0x0F,0x03,0xFF,0xFF,0x00,0x00,0x00,
               0xFC,0xFF,0xF3,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xF0,0xF0,0x00,
               0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00};
char cinco[]={0x00,0x00,0xFC,0xFC,0x3C,0x3C,0x3C,0x3C,0x3C,0x00,0x00, 
              0x00,0xFC,0xFF,0xF3,0xF0,0xF0,0xF0,0xF0,0xC0,0x00,0x00,
              0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0x00,
              0x0F,0x3F,0xFC,0xF0,0xF0,0xF0,0xF0,0x3C,0x3F,0x03,0x00};
char seis[]={0x00,0xC0,0xF0,0xFC,0x3C,0x3C,0x3C,0xFC,0xF0,0xC0,0x00, 
             0xFC,0xFF,0xC3,0xF0,0xF0,0xF0,0xF0,0xF0,0xC3,0x03,0x00,
             0xFF,0xFF,0x03,0x00,0x00,0x00,0x00,0x03,0xFF,0xF0,0x00,
             0x00,0x0F,0x3F,0xFC,0xF0,0xF0,0xF0,0x3C,0x3F,0x03,0x00};
char siete[]={0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0x3C,0xFC,0xFC,0x00, 
              0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,0x0F,0x00,0x00,
              0x00,0x00,0x00,0x00,0xF0,0xFF,0x0F,0x00,0x00,0x00,0x00,
              0x00,0x00,0xC0,0xFC,0x3F,0x03,0x00,0x00,0x00,0x00,0x00};
char ocho[]={0x00,0xC0,0xF0,0x3C,0x3C,0x3C,0x3C,0xF0,0xC0,0x00,0x00, 
             0x00,0x0F,0x3F,0xF0,0xC0,0xC0,0xF0,0x3F,0x0F,0x00,0x00,
             0xF0,0xFC,0x0F,0x0F,0x03,0x03,0x0F,0x0F,0xFC,0xF0,0x00,
             0x0F,0x3F,0xFC,0xF0,0xF0,0xF0,0xF0,0xFC,0x3F,0x0F,0x00};
char nueve[]={0x00,0xF0,0xF0,0x3C,0x3C,0x3C,0xFC,0xF0,0xC0,0x00,0x00, 
              0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFC,0x00,
              0x00,0x0F,0x3F,0x3C,0x3C,0x3C,0x3C,0x0F,0xFF,0xFF,0x00,
              0x0F,0x3F,0xFC,0xF0,0xF0,0xF0,0xFC,0x3F,0x0F,0x00,0x00};
char cerrarExclamacion[]={0xFC,0xFC,0x00,
                          0xFF,0xFF,0x00,
                          0xFF,0xFF,0x00,
                          0xF0,0xF0,0x00};
char coma[]={0x0F,0xFF,0x00,
             0x03,0x00,0x00};
char punto[]={0xF0,0xF0,0x00}; 
char dosPuntos[]={0x3C,0x3C,0x00,
                  0x00,0x00,0x00,
                  0xF0,0xF0,0x00};
char menos[]={0xC0,0xC0,0xC0,0xC0,0xC0,0x00,
              0x03,0x03,0x03,0x03,0x03,0x00};                  
char barraInclinada[]={0x00,0x00,0x00,0x00,0xC0,0x3C,0x00,
                       0x00,0x00,0x00,0xF0,0x0F,0x00,0x00,  
                       0x00,0x00,0xFC,0x03,0x00,0x00,0x00,
                       0xC0,0x3F,0x00,0x00,0x00,0x00,0x00}; 
 
I2C lcd(p9,p10); //-> pines 9 and 10 to I2C communication
 
 void inicializacionPantalla(void){
    
    
  lcd.start(); 
  lcd.write(0x78);              // set device address and write mode
  lcd.write(0xAE); 
  lcd.write(0xF1);                        // Set last COM electrode to 103 (number of COM electrodes - 1)
  lcd.write(0x67);                        //
  lcd.write(0xC0);                        // SEG (column) and COM (row) normal
  lcd.write(0x40);                        // Set Display Startline to 0
  lcd.write(0x50);                        //
  lcd.write(0x2B);                        // Set Panelloading
  lcd.write(0xEB);                        // Set Bias to 1/12
  lcd.write(0x81);                        // Set Contrast
  lcd.write(0x5F);                        //
  lcd.write(0x89);                        // Set Auto-Increment
  lcd.write(0xF4);                         // Set Start Column
  lcd.write(0x00);                          //
  lcd.write(0xF5);                          // Set Start Page 
  lcd.write(0x00);                          //
  lcd.write(0xF6);                         // Set End Column
  lcd.write(0x9f);                          //
  lcd.write(0xF7);                          //  Set End Page 
  lcd.write(0x19);                          //
  lcd.write(0xAF);                        // Display on
  lcd.stop();                           // set stop conditon = release bus
  
    }

void limpiarPantalla(void){ 
  
   for (int16_t p = 0; p < 26; p++)  //25 pages
    { 
    seleccionarPagina(p);
    for  (int16_t c = 0; c <160; c++) //160 columns
        { 
        seleccionarColumna(c);
         lcd.start();
         lcd.write(0x7A); 
         lcd.write(0x00);
         lcd.stop();  
            }
     }
  
  }
  void limpiarFilasNumeros(int16_t columnaI,int16_t columnaF,int16_t pagina){
      for (int16_t p = pagina; p < pagina+4; p++)  //25 pages
    { 
      seleccionarPagina(p);
      for  (int16_t c = columnaI; c <columnaF; c++) //160 columns
        { 
        seleccionarColumna(c);
         lcd.start();
         lcd.write(0x7A); 
         lcd.write(0x00);
         lcd.stop();  
            }
     }       
            
  }
  
void limpiarFilasLetras(int16_t columnaI,int16_t columnaF,int16_t pagina){
      for (int16_t p = pagina; p < pagina+5; p++)  //25 pages
    { 
      seleccionarPagina(p);
      for  (int16_t  c= columnaI; c <columnaF; c++) //160 columns
        { 
        seleccionarColumna(c);
         lcd.start();
         lcd.write(0x7A); 
         lcd.write(0x00);
         lcd.stop();  
            }
     }       
            
  }
  
  void seleccionarPagina(int16_t pagina) {
        lcd.start();
   lcd.write(0x78);             //Escribir  comandos
   lcd.write(0x60+pagina);      //posiciona la pagina seleccionada
   lcd.stop();
       }
       
      
   
   void seleccionarColumna(int16_t columna){
       
        lcd.start();
   lcd.write(0x78);  //Escribir  comandos
   lcd.write(0x00+(columna&0x0F));                   // posiciona la parte baja de la columna de la pantalla
   lcd.write(0x10+((columna&0xF0)>>4));              //posiciona la parte alta de la columna                    
   lcd.stop();
       }
       
      
   int imprimirTexto(int16_t columna, int16_t pagina, char  texto[]){
     

                                              
      int16_t pixel=0;
   
   
 seleccionarPagina(pagina);
 seleccionarColumna(columna);
 
       
        //*****envio de string*******
   
   
   //texto[]="CAT";
    
     unsigned char caracter, posicion = 0;  
  do { //writes a font to a block of 8x5 Pixels
    caracter = texto[posicion];
    
    switch (caracter){
     
//////////////////////////////////////////////////
            //                 A
            ///////////////////////////////////////////////////
            case'A':

                    lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<14; pixel++) {
                    lcd.write(A[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=14; pixel<28; pixel++) {
                    lcd.write(A[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=28; pixel<42; pixel++) {
                    lcd.write(A[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=42; pixel<56; pixel++) {
                    lcd.write(A[pixel]);                        //
                }    // Set Contrast
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+14;
                break;
            //////////////////////////////////////////////////
            //                 a
            ///////////////////////////////////////////////////
            case'a':
                    seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(a[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(a[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(a[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+10;
                break;
//////////////////////////////////////////////////
            //                 B
            ///////////////////////////////////////////////////
            case'B':

                    lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<12; pixel++) {
                    lcd.write(B[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=12; pixel<24; pixel++) {
                    lcd.write(B[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=24; pixel<36; pixel++) {
                    lcd.write(B[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=36; pixel<48; pixel++) {
                    lcd.write(B[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+12;
                break;
                /*
            //////////////////////////////////////////////////
            //                 b
            ///////////////////////////////////////////////////
            case'b':

                    lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(b[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(b[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(b[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=30; pixel<40; pixel++) {
                    lcd.write(b[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+10;

                break;
                */
//////////////////////////////////////////////////
            //                 C
            ///////////////////////////////////////////////////
            case'C':

                    lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<13; pixel++) {
                    lcd.write(C[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=13; pixel<26; pixel++) {
                    lcd.write(C[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=26; pixel<39; pixel++) {
                    lcd.write(C[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=39; pixel<52; pixel++) {
                    lcd.write(C[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+13;
                break;
            //////////////////////////////////////////////////
            //                 c
            ///////////////////////////////////////////////////
            case'c':
                    seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(c[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(c[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(c[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+10;
                break;
//////////////////////////////////////////////////
            //                 D
            ///////////////////////////////////////////////////
            case'D':

                    lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<13; pixel++) {
                    lcd.write(D[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=13; pixel<26; pixel++) {
                    lcd.write(D[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=26; pixel<39; pixel++) {
                    lcd.write(D[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=39; pixel<52; pixel++) {
                    lcd.write(D[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+13;
                break;
            //////////////////////////////////////////////////
            //                 d
            ///////////////////////////////////////////////////
            case'd':

                    lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(d[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(d[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(d[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=30; pixel<40; pixel++) {
                    lcd.write(d[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+10;

                break;
//////////////////////////////////////////////////
            //                 E
            ///////////////////////////////////////////////////
            case'E':

                    lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<12; pixel++) {
                    lcd.write(E[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=12; pixel<24; pixel++) {
                    lcd.write(E[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=24; pixel<36; pixel++) {
                    lcd.write(E[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=36; pixel<48; pixel++) {
                    lcd.write(E[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+12;
                break;
            //////////////////////////////////////////////////
            //                 e
            ///////////////////////////////////////////////////
            case'e':
                    seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(e[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(e[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(e[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+10;
                break;
//////////////////////////////////////////////////
            //                 F
            ///////////////////////////////////////////////////
            case'F':

                    lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<12; pixel++) {
                    lcd.write(F[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=12; pixel<24; pixel++) {
                    lcd.write(F[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=24; pixel<36; pixel++) {
                    lcd.write(F[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=36; pixel<48; pixel++) {
                    lcd.write(F[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+12;
                break;
/*
            //////////////////////////////////////////////////
            //                 f
            ///////////////////////////////////////////////////
            case'f':

                    lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<6; pixel++) {
                    lcd.write(f[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=6; pixel<12; pixel++) {
                    lcd.write(f[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=12; pixel<18; pixel++) {
                    lcd.write(f[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=18; pixel<24; pixel++) {
                    lcd.write(f[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+6;

                break;
        */
//////////////////////////////////////////////////
            //                 G
            ///////////////////////////////////////////////////
            case'G':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<14; pixel++) {
                    lcd.write(G[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=14; pixel<28; pixel++) {
                    lcd.write(G[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=28; pixel<42; pixel++) {
                    lcd.write(G[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=42; pixel<56; pixel++) {
                    lcd.write(G[pixel]);                        //
                }    // Set Contrast
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+14;
                break;
            //////////////////////////////////////////////////
            //                 g
            ///////////////////////////////////////////////////
            case'g':
                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(g[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(g[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(g[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+4);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=30; pixel<40; pixel++) {
                    lcd.write(g[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+10;

                break;


            //////////////////////////////////////////////////
            //                 H
            ///////////////////////////////////////////////////
            case'H':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<13; pixel++) {
                    lcd.write(H[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=13; pixel<26; pixel++) {
                    lcd.write(H[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=26; pixel<39; pixel++) {
                    lcd.write(H[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=39; pixel<52; pixel++) {
                    lcd.write(H[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+13;
                break;

            //////////////////////////////////////////////////
            //                 h
            ///////////////////////////////////////////////////
            case'h':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(h[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(h[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(h[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=30; pixel<40; pixel++) {
                    lcd.write(h[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+10;

                break;
//////////////////////////////////////////////////
            //                 I
            ///////////////////////////////////////////////////
            case'I':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<11; pixel++) {
                    lcd.write(I[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=11; pixel<22; pixel++) {
                    lcd.write(I[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=22; pixel<33; pixel++) {
                    lcd.write(I[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=33; pixel<44; pixel++) {
                    lcd.write(I[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+11;
                break;
            //////////////////////////////////////////////////
            //                 i
            ///////////////////////////////////////////////////
            case'i':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<3; pixel++) {
                    lcd.write(i[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=3; pixel<6; pixel++) {
                    lcd.write(i[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=6; pixel<9; pixel++) {
                    lcd.write(i[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=9; pixel<12; pixel++) {
                    lcd.write(i[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+3;

                break;


            //////////////////////////////////////////////////
            //                 J
            ///////////////////////////////////////////////////
            case'J':
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<9; pixel++) {
                    lcd.write(J[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=9; pixel<18; pixel++) {
                    lcd.write(J[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=18; pixel<27; pixel++) {
                    lcd.write(J[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=27; pixel<36; pixel++) {
                    lcd.write(J[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+9;
                break;
    /*            
            //////////////////////////////////////////////////
            //                 j
            ///////////////////////////////////////////////////
            case'j':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<4; pixel++) {
                    lcd.write(j[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=4; pixel<8; pixel++) {
                    lcd.write(j[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=8; pixel<12; pixel++) {
                    lcd.write(j[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=12; pixel<16; pixel++) {
                    lcd.write(j[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+4;

                break;
*/
            //////////////////////////////////////////////////
            //                 K
            ///////////////////////////////////////////////////
            case'K':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<13; pixel++) {
                    lcd.write(K[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=13; pixel<26; pixel++) {
                    lcd.write(K[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=26; pixel<39; pixel++) {
                    lcd.write(K[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=39; pixel<52; pixel++) {
                    lcd.write(K[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+13;
                break;
                /*
            //////////////////////////////////////////////////
            //                 k
            ///////////////////////////////////////////////////
            case'k':
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(k[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(k[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(k[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=30; pixel<40; pixel++) {
                    lcd.write(k[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+10;

                break;
                */
            //////////////////////////////////////////////////
            //                 L
            ///////////////////////////////////////////////////
            case'L':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<12; pixel++) {
                    lcd.write(L[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=12; pixel<24; pixel++) {
                    lcd.write(L[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=24; pixel<36; pixel++) {
                    lcd.write(L[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=36; pixel<48; pixel++) {
                    lcd.write(L[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+12;
                break;
            //////////////////////////////////////////////////
            //                 l
            ///////////////////////////////////////////////////
            case'l':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<3; pixel++) {
                    lcd.write(l[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=3; pixel<6; pixel++) {
                    lcd.write(l[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=6; pixel<9; pixel++) {
                    lcd.write(l[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=9; pixel<12; pixel++) {
                    lcd.write(l[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+3;

                break;
//////////////////////////////////////////////////
            //                 M
            ///////////////////////////////////////////////////
            case'M':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<16; pixel++) {
                    lcd.write(M[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=16; pixel<32; pixel++) {
                    lcd.write(M[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=32; pixel<48; pixel++) {
                    lcd.write(M[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=48; pixel<64; pixel++) {
                    lcd.write(M[pixel]);                        //
                }    // Set Contrast
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+16;
                break;
            //////////////////////////////////////////////////
            //                 m
            ///////////////////////////////////////////////////
            case'm':

                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<15; pixel++) {
                    lcd.write(m[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=15; pixel<30; pixel++) {
                    lcd.write(m[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=30; pixel<45; pixel++) {
                    lcd.write(m[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+15;
                break;

            //////////////////////////////////////////////////
            //                 N
            ///////////////////////////////////////////////////
            case'N':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<13; pixel++) {
                    lcd.write(N[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=13; pixel<26; pixel++) {
                    lcd.write(N[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=26; pixel<39; pixel++) {
                    lcd.write(N[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=39; pixel<52; pixel++) {
                    lcd.write(N[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+13;
                break;
            //////////////////////////////////////////////////
            //                 n
            ///////////////////////////////////////////////////
            case'n':

                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(n[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(n[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(n[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+10;
                break;

            //////////////////////////////////////////////////
            //                 O
            ///////////////////////////////////////////////////
            case'O':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<14; pixel++) {
                    lcd.write(O[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=14; pixel<28; pixel++) {
                    lcd.write(O[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=28; pixel<42; pixel++) {
                    lcd.write(O[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=42; pixel<56; pixel++) {
                    lcd.write(O[pixel]);                        //
                }    // Set Contrast
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+14;
                break;
            //////////////////////////////////////////////////
            //                 o
            ///////////////////////////////////////////////////
            case'o':

                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(o[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(o[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(o[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+10;
                break;
//////////////////////////////////////////////////
            //                 P
            ///////////////////////////////////////////////////
            case'P':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<12; pixel++) {
                    lcd.write(P[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=12; pixel<24; pixel++) {
                    lcd.write(P[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=24; pixel<36; pixel++) {
                    lcd.write(P[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=36; pixel<48; pixel++) {
                    lcd.write(P[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+12;
                break;
            /*    
            //////////////////////////////////////////////////
            //                 p
            ///////////////////////////////////////////////////
            case'p':
                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(p[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(p[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(p[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+4);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=30; pixel<40; pixel++) {
                    lcd.write(p[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+10;

                break;
            //////////////////////////////////////////////////
            //                 Q
            ///////////////////////////////////////////////////
            case'Q':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<14; pixel++) {
                    lcd.write(Q[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=14; pixel<28; pixel++) {
                    lcd.write(Q[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=28; pixel<42; pixel++) {
                    lcd.write(Q[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=42; pixel<56; pixel++) {
                    lcd.write(Q[pixel]);                        //
                }    // Set Contrast
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+14;
                break;
            //////////////////////////////////////////////////
            //                 q
            ///////////////////////////////////////////////////
            case'q':
                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(q[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(q[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(q[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+4);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=30; pixel<40; pixel++) {
                    lcd.write(q[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+10;
                break;
                */
//////////////////////////////////////////////////
            //                 R
            ///////////////////////////////////////////////////
            case'R':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<13; pixel++) {
                    lcd.write(R[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=13; pixel<26; pixel++) {
                    lcd.write(R[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=26; pixel<39; pixel++) {
                    lcd.write(R[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=39; pixel<52; pixel++) {
                    lcd.write(R[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+13;
                break;
            //////////////////////////////////////////////////
            //                 r
            ///////////////////////////////////////////////////
            case'r':

                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<6; pixel++) {
                    lcd.write(r[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=6; pixel<12; pixel++) {
                    lcd.write(r[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=12; pixel<18; pixel++) {
                    lcd.write(r[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+6;

                break;

            //////////////////////////////////////////////////
            //                 S
            ///////////////////////////////////////////////////
            case'S':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<12; pixel++) {
                    lcd.write(S[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=12; pixel<24; pixel++) {
                    lcd.write(S[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=24; pixel<36; pixel++) {
                    lcd.write(S[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=36; pixel<48; pixel++) {
                    lcd.write(S[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+12;
                break;
               
            //////////////////////////////////////////////////
            //                 s
            ///////////////////////////////////////////////////
            case's':

                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<9; pixel++) {
                    lcd.write(s[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=9; pixel<18; pixel++) {
                    lcd.write(s[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=18; pixel<27; pixel++) {
                    lcd.write(s[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+9;
                break;

            //////////////////////////////////////////////////
            //                 T
            ///////////////////////////////////////////////////
            case'T':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<13; pixel++) {
                    lcd.write(T[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=13; pixel<26; pixel++) {
                    lcd.write(T[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=26; pixel<39; pixel++) {
                    lcd.write(T[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=39; pixel<52; pixel++) {
                    lcd.write(T[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+13;
                break;
            //////////////////////////////////////////////////
            //                 t
            ///////////////////////////////////////////////////
            case't':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<6; pixel++) {
                    lcd.write(t[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=6; pixel<12; pixel++) {
                    lcd.write(t[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=12; pixel<18; pixel++) {
                    lcd.write(t[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=18; pixel<24; pixel++) {
                    lcd.write(t[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+6;

                break;


            //////////////////////////////////////////////////
            //                 U
            ///////////////////////////////////////////////////
            case'U':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<13; pixel++) {
                    lcd.write(U[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=13; pixel<26; pixel++) {
                    lcd.write(U[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=26; pixel<39; pixel++) {
                    lcd.write(U[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=39; pixel<52; pixel++) {
                    lcd.write(U[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+13;
                break;

            //////////////////////////////////////////////////
            //                 u
            ///////////////////////////////////////////////////
            case'u':

                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<10; pixel++) {
                    lcd.write(u[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=10; pixel<20; pixel++) {
                    lcd.write(u[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<30; pixel++) {
                    lcd.write(u[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+10;
                break;

            //////////////////////////////////////////////////
            //                 V
            ///////////////////////////////////////////////////
            case'V':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<14; pixel++) {
                    lcd.write(V[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=14; pixel<28; pixel++) {
                    lcd.write(V[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=28; pixel<42; pixel++) {
                    lcd.write(V[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=42; pixel<56; pixel++) {
                    lcd.write(V[pixel]);                        //
                }    // Set Contrast
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+14;
                break;
            //////////////////////////////////////////////////
            //                 v
            ///////////////////////////////////////////////////
            case'v':
                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<11; pixel++) {
                    lcd.write(v[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=11; pixel<22; pixel++) {
                    lcd.write(v[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=22; pixel<33; pixel++) {
                    lcd.write(v[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+11;
                break;
                
            //////////////////////////////////////////////////
            //                 W
            ///////////////////////////////////////////////////
            case'W':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<20; pixel++) {
                    lcd.write(W[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=20; pixel<40; pixel++) {
                    lcd.write(W[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=40; pixel<60; pixel++) {
                    lcd.write(W[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=60; pixel<80; pixel++) {
                    lcd.write(W[pixel]);                        //
                }    // Set Contrast
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+20;
                break;
        /*        
            //////////////////////////////////////////////////
            //                 w
            ///////////////////////////////////////////////////
            case'w':

                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<15; pixel++) {
                    lcd.write(w[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=15; pixel<30; pixel++) {
                    lcd.write(w[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=30; pixel<45; pixel++) {
                    lcd.write(w[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+15;
                break;
            //////////////////////////////////////////////////
            //                 X
            ///////////////////////////////////////////////////
            case'X':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<14; pixel++) {
                    lcd.write(X[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=14; pixel<28; pixel++) {
                    lcd.write(X[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=28; pixel<42; pixel++) {
                    lcd.write(X[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=42; pixel<56; pixel++) {
                    lcd.write(X[pixel]);                        //
                }    // Set Contrast
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+14;
                break;
                
            //////////////////////////////////////////////////
            //                 x
            ///////////////////////////////////////////////////
            case'x':
                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<11; pixel++) {
                    lcd.write(x[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=11; pixel<22; pixel++) {
                    lcd.write(x[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=22; pixel<33; pixel++) {
                    lcd.write(x[pixel]);
                }
                lcd.stop();


                seleccionarPagina(pagina);
                columna=columna+11;
                break;
                */
            //////////////////////////////////////////////////
            //                 Y
            ///////////////////////////////////////////////////
            case'Y':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<15; pixel++) {
                    lcd.write(Y[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=15; pixel<30; pixel++) {
                    lcd.write(Y[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=30; pixel<45; pixel++) {
                    lcd.write(Y[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=45; pixel<60; pixel++) {
                    lcd.write(Y[pixel]);                        //
                }    // Set Contrast
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+15;
                break;
            //////////////////////////////////////////////////
            //                 y
            ///////////////////////////////////////////////////
            case'y':
                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<11; pixel++) {
                    lcd.write(y[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=11; pixel<22; pixel++) {
                    lcd.write(y[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=22; pixel<33; pixel++) {
                    lcd.write(y[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+4);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=33; pixel<44; pixel++) {
                    lcd.write(y[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+11;
                break;
              
            //////////////////////////////////////////////////
            //                 Z
            ///////////////////////////////////////////////////
            case'Z':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<11; pixel++) {
                    lcd.write(Z[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=11; pixel<22; pixel++) {
                    lcd.write(Z[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=22; pixel<33; pixel++) {
                    lcd.write(Z[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=33; pixel<44; pixel++) {
                    lcd.write(Z[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+11;
                break;
                /*
            //////////////////////////////////////////////////
            //                 z
            ///////////////////////////////////////////////////
            case'z':

                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<9; pixel++) {
                    lcd.write(z[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=9; pixel<18; pixel++) {
                    lcd.write(z[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=18; pixel<27; pixel++) {
                    lcd.write(z[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+9;
 
        break;
        */
        //////////////////////////////////////////////////
   //                 0
   ///////////////////////////////////////////////////   
   case '0':
        
       lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(cero[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(cero[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(cero[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(cero[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 1
   ///////////////////////////////////////////////////
        case '1':
        
         lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<7;pixel++){
         lcd.write(uno[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=7;pixel<14;pixel++){
          lcd.write(uno[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=14;pixel<21;pixel++){
          lcd.write(uno[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=21;pixel<28;pixel++){
         lcd.write(uno[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+7;
        break;
        //////////////////////////////////////////////////
   //                 2
   ///////////////////////////////////////////////////
        case'2':
       
          lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(dos[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(dos[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(dos[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(dos[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 3
   ///////////////////////////////////////////////////
        case '3':
        
          lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(tres[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(tres[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(tres[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(tres[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 4
   ///////////////////////////////////////////////////
        case '4':

         lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<12;pixel++){
         lcd.write(cuatro[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=12;pixel<24;pixel++){
          lcd.write(cuatro[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=24;pixel<36;pixel++){
          lcd.write(cuatro[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=36;pixel<48;pixel++){
         lcd.write(cuatro[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+12;
        break;
        //////////////////////////////////////////////////
   //                 5
   ///////////////////////////////////////////////////
        case '5':
     
         lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(cinco[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(cinco[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(cinco[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(cinco[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 6
   ///////////////////////////////////////////////////
        case '6':
       
         lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(seis[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(seis[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(seis[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(seis[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 7
   ///////////////////////////////////////////////////
        case '7':
     
         lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(siete[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(siete[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(siete[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(siete[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
         //////////////////////////////////////////////////
   //                 8
   ///////////////////////////////////////////////////
        case '8':
       
         lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(ocho[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(ocho[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(ocho[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(ocho[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 9
   ///////////////////////////////////////////////////
        case '9':
        
          lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(nueve[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(nueve[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(nueve[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(nueve[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
             //////////////////////////////////////////////////
   //                 -
   ///////////////////////////////////////////////////
    case'-':
    seleccionarPagina(pagina+1);
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<6;pixel++){
         lcd.write(menos[pixel]);                        
                     }    
     lcd.stop();                  
    
    seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=6;pixel<12;pixel++){
          lcd.write(menos[pixel]);                        
                     }   
     lcd.stop();
       
    seleccionarPagina(pagina);  
    columna=columna+6;
    break;
           //////////////////////////////////////////////////
            //                 !
            ///////////////////////////////////////////////////
            case'!':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<3; pixel++) {
                    lcd.write(cerrarExclamacion[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=3; pixel<6; pixel++) {
                    lcd.write(cerrarExclamacion[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=6; pixel<9; pixel++) {
                    lcd.write(cerrarExclamacion[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=9; pixel<12; pixel++) {
                    lcd.write(cerrarExclamacion[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+3;

                break;
                //////////////////////////////////////////////////
            //                 ,
            ///////////////////////////////////////////////////
            case',':
                seleccionarPagina(pagina+3);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<3; pixel++) {
                    lcd.write(coma[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+4);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=3; pixel<6; pixel++) {
                    lcd.write(coma[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+3;

                break;
                 //////////////////////////////////////////////////
            //                 .
            ///////////////////////////////////////////////////
            case'.':
                seleccionarPagina(pagina+3);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<3; pixel++) {
                    lcd.write(punto[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+3;

                break;
            //////////////////////////////////////////////////
            //                 :
            ///////////////////////////////////////////////////
            case':':
                seleccionarPagina(pagina+1);
                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<3; pixel++) {
                    lcd.write(dosPuntos[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=3; pixel<6; pixel++) {
                    lcd.write(dosPuntos[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=6; pixel<9; pixel++) {
                    lcd.write(dosPuntos[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+3;

                break;
            //////////////////////////////////////////////////
            //                 /
            ///////////////////////////////////////////////////
            case'/':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<7; pixel++) {
                    lcd.write(barraInclinada[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=7; pixel<14; pixel++) {
                    lcd.write(barraInclinada[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=14; pixel<21; pixel++) {
                    lcd.write(barraInclinada[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=21; pixel<28; pixel++) {
                    lcd.write(barraInclinada[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+7;
                break;
            //////////////////////////////////////////////
            //
            ///////////////////////////////////////
            case' ':

                lcd.start();
                lcd.write(0x7A);

                for ( pixel=0; pixel<4; pixel++) {
                    lcd.write(0x00);                        //
                }    // Set Contrast
                lcd.stop();
                columna=columna+4;

                break;
        }
    
    posicion++;
    caracter = texto[posicion];
  } while (caracter != 0); //writes until the end of the String  
   return columna;
     }
     
     int imprimirNumero(int16_t columna, int16_t pagina, float valor, uint16_t decimales){
                     
         char arrayNumero[]="";
         switch (decimales){
             
             case 0:
              char numcero=sprintf (arrayNumero, "%3.0f", valor); 
             break;
             case 1:
             char numuno=sprintf (arrayNumero, "%.1f", valor); 
             break;
             case 2:
             char numdos=sprintf (arrayNumero, "%.2f", valor); 
             break;
             case 3:
             char numtres=sprintf (arrayNumero, "%.3f", valor); 
             break;
             case 4:
             char numcuatro=sprintf (arrayNumero, "%.4f", valor); 
             break;
             default:
             char numcinco=sprintf (arrayNumero, "%.5f", valor);
            
              }
              
              
               //char nm=sprintf (cadenaDecimales, "%.0f", decimales); 
              //(float) arrayNumero =valor;
              //char n=sprintf (arrayNumero, "%.cadenaDecimales f", valor); 
         
         int16_t pixel=0;
         
         seleccionarPagina(pagina);
         seleccionarColumna(columna);
         
        // itoa_(valor,arrayNumero);
         
           unsigned char caracter, posicion = 0;  
  do { //writes a font to a block of 8x5 Pixels
    caracter = arrayNumero[posicion];
    
    switch (caracter){
        
   //////////////////////////////////////////////////
   //                 0
   ///////////////////////////////////////////////////   
   case '0':
        
       lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(cero[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(cero[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(cero[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(cero[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 1
   ///////////////////////////////////////////////////
        case '1':
        
         lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<7;pixel++){
         lcd.write(uno[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=7;pixel<14;pixel++){
          lcd.write(uno[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=14;pixel<21;pixel++){
          lcd.write(uno[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=21;pixel<28;pixel++){
         lcd.write(uno[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+7;
        break;
        //////////////////////////////////////////////////
   //                 2
   ///////////////////////////////////////////////////
        case'2':
       
          lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(dos[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(dos[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(dos[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(dos[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 3
   ///////////////////////////////////////////////////
        case '3':
        
          lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(tres[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(tres[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(tres[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(tres[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 4
   ///////////////////////////////////////////////////
        case '4':

         lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<12;pixel++){
         lcd.write(cuatro[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=12;pixel<24;pixel++){
          lcd.write(cuatro[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=24;pixel<36;pixel++){
          lcd.write(cuatro[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=36;pixel<48;pixel++){
         lcd.write(cuatro[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+12;
        break;
        //////////////////////////////////////////////////
   //                 5
   ///////////////////////////////////////////////////
        case '5':
     
         lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(cinco[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(cinco[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(cinco[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(cinco[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 6
   ///////////////////////////////////////////////////
        case '6':
       
         lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(seis[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(seis[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(seis[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(seis[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 7
   ///////////////////////////////////////////////////
        case '7':
     
         lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(siete[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(siete[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(siete[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(siete[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
         //////////////////////////////////////////////////
   //                 8
   ///////////////////////////////////////////////////
        case '8':
       
         lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(ocho[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(ocho[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(ocho[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(ocho[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 9
   ///////////////////////////////////////////////////
        case '9':
        
          lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<11;pixel++){
         lcd.write(nueve[pixel]);                       
                     }     
     lcd.stop();                  
    
    seleccionarPagina(pagina+1);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=11;pixel<22;pixel++){
          lcd.write(nueve[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
    
    lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=22;pixel<33;pixel++){
          lcd.write(nueve[pixel]);                        
                     }     
     lcd.stop();
     seleccionarPagina(pagina+3);
    seleccionarColumna(columna);
    
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=33;pixel<44;pixel++){
         lcd.write(nueve[pixel]);                       
                     }     
     lcd.stop();  
     
    seleccionarPagina(pagina);  
    columna=columna+11;
        break;
        //////////////////////////////////////////////////
   //                 -
   ///////////////////////////////////////////////////
    case'-':
    seleccionarPagina(pagina+1);
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<7;pixel++){
         lcd.write(menos[pixel]);                        
                     }    
     lcd.stop();                  
    
    seleccionarPagina(pagina+2);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=7;pixel<14;pixel++){
          lcd.write(menos[pixel]);                        
                     }   
     lcd.stop();
       
    seleccionarPagina(pagina);  
    columna=columna+7;
    break;
        //////////////////////////////////////////////////
   //                 .
   ///////////////////////////////////////////////////
    case'.':
    seleccionarPagina(pagina+3);
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<3;pixel++){
         lcd.write(punto[pixel]);                        
                     }    
     lcd.stop();                  
     
    seleccionarPagina(pagina);  
    columna=columna+3;
   
   break;
   /////////////////////////////////////////////////
            //                 C
            ///////////////////////////////////////////////////
            case'C':

                    lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<13; pixel++) {
                    lcd.write(C[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=13; pixel<26; pixel++) {
                    lcd.write(C[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=26; pixel<39; pixel++) {
                    lcd.write(C[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=39; pixel<52; pixel++) {
                    lcd.write(C[pixel]);
                }
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+13;
                break;
    //////////////////////////////////////////////////
            //                 V
            ///////////////////////////////////////////////////
            case'V':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<14; pixel++) {
                    lcd.write(V[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=14; pixel<28; pixel++) {
                    lcd.write(V[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=28; pixel<42; pixel++) {
                    lcd.write(V[pixel]);                        //
                }    // Set Contrast
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=42; pixel<56; pixel++) {
                    lcd.write(V[pixel]);                        //
                }    // Set Contrast
                lcd.stop();
                seleccionarPagina(pagina);
                columna=columna+14;
                break;
        //////////////////////////////////////////////////
            //                 /
            ///////////////////////////////////////////////////
            case'/':

                lcd.start();
                lcd.write(0x7A);
                for( pixel=0; pixel<7; pixel++) {
                    lcd.write(barraInclinada[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+1);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=7; pixel<14; pixel++) {
                    lcd.write(barraInclinada[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+2);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=14; pixel<21; pixel++) {
                    lcd.write(barraInclinada[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina+3);
                seleccionarColumna(columna);

                lcd.start();
                lcd.write(0x7A);
                for ( pixel=21; pixel<28; pixel++) {
                    lcd.write(barraInclinada[pixel]);
                }
                lcd.stop();

                seleccionarPagina(pagina);
                columna=columna+7;
                break;
        
   //////////////////////////////////////////////////
   //                 ,
   /////////////////////////////////////////////////// 
     case',':
    seleccionarPagina(pagina+3);
     lcd.start(); 
     lcd.write(0x7A);
         for( pixel=0;pixel<3;pixel++){
         lcd.write(coma[pixel]);                        
                     }    
     lcd.stop();                  
    
    seleccionarPagina(pagina+4);
    seleccionarColumna(columna);
             
     lcd.start(); 
     lcd.write(0x7A);                   
          for ( pixel=3;pixel<6;pixel++){
          lcd.write(coma[pixel]);                        
                     }   
     lcd.stop();  
    seleccionarPagina(pagina);  
    columna=columna+3;
   
   break;
        
         }
          posicion++;
    caracter = arrayNumero[posicion];
  } while (caracter != 0); //writes until the end of the String  
   
   return columna;
     }    
         
void strreverse(char* begin, char* end) 
{   
    char aux;   
    while(end>begin)    
        aux=*end, *end--=*begin, *begin++=aux;  
}
void itoa_(int value, char *str)
{
    char* wstr=str; 
    int sign;   
    div_t res;
    
    if ((sign=value) < 0) value = -value;
    
    do {    
      *wstr++ = (value%10)+'0'; 
    }while(value=value/10);
    
    if(sign<0) *wstr++='-'; 
    *wstr='\0';

    strreverse(str,wstr-1);
}
