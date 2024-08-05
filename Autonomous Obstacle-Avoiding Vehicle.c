#INCLUDE <16F887.H>
#FUSES NOWDT, PUT, HS, NOPROTECT, NOLVP
#USE DELAY(CLOCK=20M)
//Khai b�o c�c ch�n
//Ch�n ?i?u khi?n motor
#DEFINE     IN1    PIN_D0
#DEFINE     IN2    PIN_D1
#DEFINE     IN3    PIN_D2
#DEFINE     IN4    PIN_D3
//Ch�n ??i m�u LED
#DEFINE     LEDR   PIN_E0
#DEFINE     LEDG   PIN_E1
#DEFINE     LEDB   PIN_E2
//Ch�n ?i?u khi?n ?�n,c�i b?t t?t
#DEFINE     LED    PIN_D4
#DEFINE     COI    PIN_D5
//Ch�n 3 c?m bi?n si�u �m
#DEFINE trigger1 PIN_B0  
#DEFINE echo1 PIN_B1     
#DEFINE trigger2 PIN_B2  
#DEFINE echo2 PIN_B3 
#DEFINE trigger3 PIN_B4  
#DEFINE echo3 PIN_B5 
#USE RS232(BAUD=9600, XMIT=PIN_C6, RCV=PIN_C7)
UNSIGNED INT16 V,tocdo,chedo, DIS=30,DISMID=35;
float khoangcach1 ,khoangcach2, khoangcach3, thoigian1 ,thoigian2,thoigian3;
int16 soxung1,soxung2,soxung3;
//C�c h�m
//H�m ng?t UART
#INT_RDA
VOID NHAN()
{
   IF (KBHIT () ) //Nh?n gi� tr? t? Bluetooth
   {
      V = GETCH ();
   }
   IF ((V == 'A')|| (V == 'M')) // Chuy?n ch? ??
   {
      chedo = V;
   }
}
//H�m ?i?u khi?n motor ph?i
void MOTOR_PHAI(UNSIGNED int8 huong)
      {
   
   SET_PWM1_DUTY (tocdo) ;
   IF (huong == 0) // motor ph?i quay t?i
   {
      
      OUTPUT_HIGH (IN1) ;
      OUTPUT_LOW (IN2) ;
   }
   else IF (huong == 1) // motor ph?i quay l�i
   {
      OUTPUT_LOW (IN1) ;
      OUTPUT_HIGH (IN2) ;
   }
   else IF (huong == 2) // motor ph?i ??ng y�n
   {
      OUTPUT_LOW (IN1) ;
      OUTPUT_LOW (IN2) ;
   }
      }
//H�m ?i?u khi?n motor tr�i      
void MOTOR_TRAI(UNSIGNED int8 huong)
      {
   SET_PWM2_DUTY (tocdo) ;
   IF (huong == 0) // motor tr�i quay t?i
   {
      
      OUTPUT_HIGH (IN3) ;
      OUTPUT_LOW (IN4) ;
   }
   else IF (huong == 1) // motor tr�i quay l�i
   {
      OUTPUT_LOW (IN3) ;
      OUTPUT_HIGH (IN4) ;
   }
   else IF (huong == 2) // motor tr�i ??ng y�n
   {
      OUTPUT_LOW (IN3) ;
      OUTPUT_LOW (IN4) ;
   }
      }
      
//H�m ?i?u khi?n xe ch?y ti?n t?i      
VOID TIEN() 
{
   MOTOR_PHAI (0) ;
   MOTOR_TRAI (0) ;
}
//H�m ?i?u khi?n xe ch?y l�i l?i
VOID LUI() 
{
   MOTOR_PHAI (1) ;
   MOTOR_TRAI (1) ;
}
//H�m ?i?u khi?n xe qu?o qua ph?i 
VOID QUEOPHAI() 
{
   MOTOR_PHAI (1) ;
   MOTOR_TRAI (0) ;
}
//H�m ?i?u khi?n xe qu?o qua tr�i
VOID QUEOTRAI() 
{
   MOTOR_PHAI (0) ;
   MOTOR_TRAI (1) ;
}
//H�m ?i?u khi?n xe d?ng l?i
VOID DUNG() 
{
   MOTOR_PHAI (2) ;
   MOTOR_TRAI (2) ;
}
//H�m t�nh kho?ng c�ch c?m bi?n b�n tr�i
 VOID tinhkhoangcach1 () 
{
    OUTPUT_HIGH (trigger1) ;
    delay_us (20) ;
    OUTPUT_LOW (trigger1) ;
    set_timer1 (0) ;
    WHILE ( ! (input (echo1)));
    setup_timer_1 (t1_internal|t1_div_by_4); //Kh?i t?o timer1
    WHILE (input (echo1)) ;
    soxung1 = get_timer1 ();
    setup_timer_1 (t1_disabled) ;
    thoigian1 = soxung1 * 0.2 * 4;
    khoangcach1 = thoigian1 / (2*29.412);
}
//T�nh kho?ng c�ch c?m bi?n ? gi?a
 VOID tinhkhoangcach2 ()
 {
    OUTPUT_HIGH (trigger2) ;
    delay_us (20) ;
    OUTPUT_LOW (trigger2) ;
    set_timer1 (0) ;
    WHILE ( ! (input (echo2)));
    setup_timer_1 (t1_internal|t1_div_by_4) ;
    WHILE (input (echo2)) ;
    soxung2 = get_timer1 ();
    setup_timer_1 (t1_disabled) ;
    thoigian2 = soxung2 * 0.2 * 4;
    khoangcach2 = thoigian2 / (2*29.412);
 }
//T�nh kho?ng c�ch c?m bi?n b�n ph?i
 VOID tinhkhoangcach3 ()
 {
    OUTPUT_HIGH (trigger3) ;
    delay_us (20) ;
    OUTPUT_LOW (trigger3) ;
    set_timer1 (0) ;
    WHILE ( ! (input (echo3)));
    setup_timer_1 (t1_internal|t1_div_by_4) ;
    WHILE (input (echo3)) ;
    soxung3 = get_timer1 ();
    setup_timer_1 (t1_disabled) ;
    thoigian3 = soxung3 * 0.2 * 4;
    khoangcach3 = thoigian3 / (2*29.412);
 }
  //H�m ??i m�u LED
 VOID MAULED (unsigned int8 mau)
 {
    IF (mau == 0) // m�u ??
    {
       OUTPUT_LOW (LEDR) ;
       OUTPUT_HIGH (LEDG) ;
       OUTPUT_HIGH (LEDB) ;
    }
    else IF (mau == 1) // m�u xanh l�
    {
       OUTPUT_HIGH (LEDR) ;
       OUTPUT_LOW (LEDG) ;
       OUTPUT_HIGH (LEDB) ;
    }
    else IF (mau == 2) // m�u xanh d??ng
    {
       OUTPUT_HIGH (LEDR) ;
       OUTPUT_HIGH (LEDG) ;
       OUTPUT_LOW (LEDB) ;
    }
 }
//Ch??ng tr�nh ch�nh
 VOID MAIN ()
 {
    SET_TRIS_C (0X00);
    SET_TRIS_D (0x00);
    SETUP_CCP1 (CCP_PWM);
    SETUP_CCP2 (CCP_PWM);
    SETUP_TIMER_2 (T2_DIV_BY_16, 249, 1) ;
    OUTPUT_D (0x70);
    tocdo = 500;
   //Khai b�o ng?t
    ENABLE_INTERRUPTS (GLOBAL);
    ENABLE_INTERRUPTS (INT_RDA);
    WHILE (TRUE)
    {
       IF (chedo == 'A') //Ch? ?? Auto
       {
          tocdo = 450;
          SET_PWM2_DUTY (tocdo);
          SET_PWM1_DUTY (tocdo);
          tinhkhoangcach1 ();
          tinhkhoangcach2 ();
          tinhkhoangcach3 ();
          
          //V?t c?n b�n tr�i
          IF (khoangcach1 < DIS&&khoangcach2 > DISMID&&khoangcach3 > DIS)
          {
             QUEOPHAI () ;
             delay_MS (300) ;
          }
          //V?t c?n b�n ph?i
          else IF (khoangcach1 > DIS&&khoangcach2 > DISMID&&khoangcach3 < DIS)
          {
             QUEOTRAI () ;
             delay_MS (300);
          }
          //V?t c?n ph�a tr??c
          else IF (khoangcach1 > DIS&&khoangcach2 < DISMID&&khoangcach3 > DIS)
          {
             IF (khoangcach1 > khoangcach3)
             {
                QUEOTRAI () ;
                delay_MS (300);
             }
             IF (khoangcach1 < khoangcach3)
             {
                QUEOPHAI () ;
                delay_MS (300);
             }
          }
          //V?t c?n ph�a tr??c v� b�n tr�i
          else IF (khoangcach1 < DIS&&khoangcach2 < DISMID&&khoangcach3 > DIS)
          {
             QUEOPHAI () ;
             delay_MS (300);
          }
          //V?t c?n ph�a tr??c v� b�n ph?i
          else IF (khoangcach1 > DIS&&khoangcach2 < DISMID&&khoangcach3 < DIS)
          {
             QUEOTRAI () ;
             delay_MS (300);
          }
          //V?t c?n 2 b�n tr�i ph?i
          else IF (khoangcach1 < DIS&&khoangcach2 > DISMID&&khoangcach3 < DIS)
          {
             QUEOPHAI () ;
             delay_MS (300) ;
          }
          // V?t c?n c? b�n tr�i, ph?i, tr??c
          else IF (khoangcach1 < DIS&&khoangcach2 < DISMID&&khoangcach3 < DIS)
          {
             DUNG () ;
             delay_MS (50);
             LUI () ;
             delay_MS (100);
             QUEOTRAI () ;
             delay_MS (250);
          }
//Khi kh�ng c� v?t c?n
          ELSE
          {
             TIEN () ;
          }
          
          //C�i Led b?t t?t
          IF (khoangcach1 < DIS||khoangcach2 < DISMID||khoangcach3 < DIS)
          {
             MAULED (0) ;
             OUTPUT_LOW (LED) ;
             OUTPUT_LOW (COI) ;
          }
          ELSE
          {
             MAULED (1) ;
             OUTPUT_LOW (LED) ;
             OUTPUT_HIGH (COI) ;
          }
       }
       //Ch? ?? manual
       IF (chedo == 'M')
       {
          SWITCH (V)
          {
             //?i?u ch?nh t?c ??
             CASE '0': tocdo = 550; break;
             CASE '1': tocdo = 600; break;
             CASE '2': tocdo = 650; break;
             CASE '3': tocdo = 700; break;
             CASE '4': tocdo = 750; break;
             CASE '5': tocdo = 800; break;
             CASE '6': tocdo = 850; break;
             CASE '7': tocdo = 900; break;
             CASE '8': tocdo = 950; break;
             CASE '9': tocdo = 1000; break;
  //?i?u khi?n c�c h??ng xe ch?y
             CASE 'F':
             TIEN ();
             BREAK;
             CASE 'B':
             LUI ();
             BREAK;
             CASE 'R':
             QUEOPHAI ();
             BREAK;
             CASE 'L':
             QUEOTRAI ();
             BREAK;
             CASE 'S':
             DUNG ();
             BREAK;
             //B?t t?t ?�n ??
             CASE 'W':
             OUTPUT_LOW (LED) ;
             MAULED (0) ;
             BREAK;
             CASE 'w':
             OUTPUT_HIGH (LED) ;
             //MAULED (0) ;
             BREAK;
  //B?t t?t ?�n xanh l�
             CASE 'X':
             OUTPUT_LOW (LED) ;
             MAULED (1) ;
             BREAK;
             CASE 'x':
             OUTPUT_HIGH (LED) ;
             BREAK;
  //B?t t?t ?�n xanh d??ng
             CASE 'Y':
             OUTPUT_LOW (LED) ;
             MAULED (2) ;
             BREAK;
             CASE 'y':
             OUTPUT_HIGH (LED) ;
             BREAK;
 //B?t t?t c�i
             CASE 'Z':
             OUTPUT_LOW (COI) ;
             BREAK;
             CASE 'z':
             OUTPUT_HIGH (COI) ;
             BREAK;
          }
       }
    }
 }

