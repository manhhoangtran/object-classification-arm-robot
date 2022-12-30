#include <stdio.h>
#include "include.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define pi 3.14159265

uint32_t number_of_pulse_1,number_of_pulse_2,number_of_pulse_3,number_of_pulse_4,number_of_pulse_5,number_of_pulse_6;
uint32_t x_1,x_2,x_3,x_4,x_5,x_6;
uint32_t count_1,count_2,count_3,count_4,count_5,count_6,count_7,count_8,count_9,count_10,count_11,count_12,count_13;
uint8_t l_2,l_3,loi;
uint8_t engine_angel_1,engine_angel_2,engine_angel_3,engine_angel_4;
uint32_t x_axis,y_axis,long_size,classification;
uint8_t prepare_status=0 ,action_status=0 ,trung_gian_status=0,chuan_bi_tha_status=0,tha_status=0,start_procees=0;
uint8_t count=0;
int distance_to_robot,time_to_robot;


static char Buff[100];
char chuoi[20],chuoi_copy[20];
void Timer_ISR_1(void)
{
    TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    if(number_of_pulse_1 ==SysCtlClockGet()/1000000*(500+19000*x_1/1800))
    {
        GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,0);
        number_of_pulse_1 = SysCtlClockGet()/1000000*(19500-19000*x_1/1800);
    }
    else if(number_of_pulse_1 ==SysCtlClockGet()/1000000*(19500-19000*x_1/1800))
    {
        GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,GPIO_PIN_7);
        number_of_pulse_1 = SysCtlClockGet()/1000000*(500+19000*x_1/1800);
    }
    else
    {

    }
    TimerLoadSet(TIMER0_BASE,TIMER_A,number_of_pulse_1);

}

void Timer_ISR_2(void)
{
    TimerIntClear(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
    if(number_of_pulse_2 ==SysCtlClockGet()/1000000*(500+19000*x_2/1800))
    {
        GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,0);
        number_of_pulse_2 = SysCtlClockGet()/1000000*(19500-19000*x_2/1800);
    }
    else if(number_of_pulse_2 ==SysCtlClockGet()/1000000*(19500-19000*x_2/1800))
    {
        GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,GPIO_PIN_6);
        number_of_pulse_2 = SysCtlClockGet()/1000000*(500+19000*x_2/1800);
    }
    else
    {

    }
    TimerLoadSet(TIMER1_BASE,TIMER_A,number_of_pulse_2);

}

void Timer_ISR_3(void)
{
    TimerIntClear(TIMER2_BASE,TIMER_TIMA_TIMEOUT);
    if(number_of_pulse_3 ==SysCtlClockGet()/1000000*(500+19000*x_3/1800))
    {
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_4,0);
        number_of_pulse_3 = SysCtlClockGet()/1000000*(19500-19000*x_3/1800);
    }
    else if(number_of_pulse_3 ==SysCtlClockGet()/1000000*(19500-19000*x_3/1800))
    {
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_4,GPIO_PIN_4);
        number_of_pulse_3 = SysCtlClockGet()/1000000*(500+19000*x_3/1800);
    }
    else
    {

    }
    TimerLoadSet(TIMER2_BASE,TIMER_A,number_of_pulse_3);

}

void Timer_ISR_4(void)
{
    TimerIntClear(TIMER3_BASE,TIMER_TIMA_TIMEOUT);
    if(number_of_pulse_4 ==SysCtlClockGet()/1000000*(500+19000*x_4/1800))
    {
        GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,0);
        number_of_pulse_4 = SysCtlClockGet()/1000000*(19500-19000*x_4/1800);
    }
    else if(number_of_pulse_4 ==SysCtlClockGet()/1000000*(19500-19000*x_4/1800))
    {
        GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,GPIO_PIN_5);
        number_of_pulse_4 = SysCtlClockGet()/1000000*(500+19000*x_4/1800);
    }
    else
    {

    }
    TimerLoadSet(TIMER3_BASE,TIMER_A,number_of_pulse_4);

}
void Timer_ISR_5(void)
{
    TimerIntClear(TIMER4_BASE,TIMER_TIMA_TIMEOUT);
    if(number_of_pulse_5 ==SysCtlClockGet()/1000000*(500+19000*x_5/1800))
    {
        GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,0);
        number_of_pulse_5 = SysCtlClockGet()/1000000*(19500-19000*x_5/1800);
    }
    else if(number_of_pulse_5 ==SysCtlClockGet()/1000000*(19500-19000*x_5/1800))
    {
        GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,GPIO_PIN_4);
        number_of_pulse_5 = SysCtlClockGet()/1000000*(500+19000*x_5/1800);
    }
    else
    {

    }
    TimerLoadSet(TIMER4_BASE,TIMER_A,number_of_pulse_5);

}

void Timer_ISR_6(void)
{
    TimerIntClear(TIMER5_BASE,TIMER_TIMA_TIMEOUT);
    if(number_of_pulse_6 ==SysCtlClockGet()/1000000*(500+19000*x_6/1800))
    {
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1,0);
        number_of_pulse_6 = SysCtlClockGet()/1000000*(19500-19000*x_6/1800);
    }
    else if(number_of_pulse_6 ==SysCtlClockGet()/1000000*(19500-19000*x_6/1800))
    {
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1,GPIO_PIN_1);
        number_of_pulse_6 = SysCtlClockGet()/1000000*(500+19000*x_6/1800);
    }
    else
    {

    }
    TimerLoadSet(TIMER5_BASE,TIMER_A,number_of_pulse_6);

}
void turn(double x,double y,double z);
void engine_turn_6(uint32_t a);
void Timer_ISR_7(void)
{
    TimerIntClear(WTIMER0_BASE,TIMER_TIMA_TIMEOUT);
    TimerDisable(WTIMER0_BASE, TIMER_A);

    UARTCharPut(UART0_BASE,'X');


}
void prepare_to_action(void);
void gap(void);
void trung_gian();
void chuan_bi_tha(void);
void tha(void);
void Timer_ISR_8(void)
{
    TimerIntClear(WTIMER2_BASE,TIMER_TIMA_TIMEOUT);
    if(start_procees == 1)
    {

        count_8 = count_8+1;
        if(count_8==time_to_robot)
        {

            start_procees = 0;
            action_status = 1;
            count_8 =0;
            gap();

        }
    }
    if(action_status == 1)
    {
        count_9 = count_9+1;
        if(count_9==5)
         {

               action_status = 0;
               chuan_bi_tha_status = 1;
               count_9 =0;
               chuan_bi_tha();


          }
    }




    if(chuan_bi_tha_status == 1)
    {
        count_11 = count_11+1;
        if(count_11==10)
            {

        chuan_bi_tha_status = 0;
        tha_status = 1;
        count_11 =0;
        tha();
             }

    }
    if(tha_status == 1)
    {
        count_12 = count_12+1;
                if(count_12==5)
                    {
                                     // TimerDisable(WTIMER2_BASE, TIMER_A);
                tha_status = 0;
                count_12 =0;
                trung_gian();
                trung_gian_status = 1;
                     }
    }
    if(trung_gian_status == 1)
    {
        count_13 = count_13+1;
                        if(count_13==5)
                            {
                                             // TimerDisable(WTIMER2_BASE, TIMER_A);
                        trung_gian_status = 0;
                        count_13 =0;
                        prepare_to_action();
                            }

    }


    }




void Config_Timer_1(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC); // config timer
    TimerIntRegister(TIMER0_BASE,TIMER_A,&Timer_ISR_1); 
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);


}

void Config_Timer_2(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE,TIMER_CFG_PERIODIC);
    TimerIntRegister(TIMER1_BASE,TIMER_A,&Timer_ISR_2);
    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
}
void Config_Timer_3(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    TimerConfigure(TIMER2_BASE,TIMER_CFG_PERIODIC); // config timer
    TimerIntRegister(TIMER2_BASE,TIMER_A,&Timer_ISR_3);
    IntEnable(INT_TIMER2A);
    TimerIntEnable(TIMER2_BASE,TIMER_TIMA_TIMEOUT);


}

void Config_Timer_4(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    TimerConfigure(TIMER3_BASE,TIMER_CFG_PERIODIC);
    TimerIntRegister(TIMER3_BASE,TIMER_A,&Timer_ISR_4);
    IntEnable(INT_TIMER3A);
    TimerIntEnable(TIMER3_BASE,TIMER_TIMA_TIMEOUT);


}
 void Config_Timer_5(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER4);
    TimerConfigure(TIMER4_BASE,TIMER_CFG_PERIODIC); // config timer
    TimerIntRegister(TIMER4_BASE,TIMER_A,&Timer_ISR_5);
    IntEnable(INT_TIMER4A);
    TimerIntEnable(TIMER4_BASE,TIMER_TIMA_TIMEOUT);


}
void Config_Timer_6(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER5);
    TimerConfigure(TIMER5_BASE,TIMER_CFG_PERIODIC); // config timer
    TimerIntRegister(TIMER5_BASE,TIMER_A,&Timer_ISR_6);
    IntEnable(INT_TIMER5A);
    TimerIntEnable(TIMER5_BASE,TIMER_TIMA_TIMEOUT);
}

void Config_Timer_7(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
    TimerConfigure(WTIMER0_BASE,TIMER_CFG_PERIODIC); // config timer
    TimerIntRegister(WTIMER0_BASE,TIMER_A,&Timer_ISR_7);
    IntEnable(INT_WTIMER0A);
    TimerIntEnable(WTIMER0_BASE,TIMER_TIMA_TIMEOUT);


}

void Config_Timer_8(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER2);
    TimerConfigure(WTIMER2_BASE,TIMER_CFG_PERIODIC); // config timer
    TimerIntRegister(WTIMER2_BASE,TIMER_A,&Timer_ISR_8);
    IntEnable(INT_WTIMER2A);
    TimerIntEnable(WTIMER2_BASE,TIMER_TIMA_TIMEOUT);
}

void Config_Dong_co_1(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_7);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,0);

}
void Config_Dong_co_2(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_6);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,0);

}
void Config_Dong_co_3(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_4,0);

}

void Config_Dong_co_4(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_5);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,0);

}
void Config_Dong_co_5(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,0);

}



void Config_Dong_co_6(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1,0);

}


void Input_ISR(void)
{
    GPIOIntClear(GPIO_PORTA_BASE,GPIOIntStatus(GPIO_PORTA_BASE,true));
    // bat timer trong 1s ke tu khi vat di qua het cam bien cho toi khi vat lot vao camera
    // timer 7
    TimerDisable(WTIMER0_BASE, TIMER_A);
    TimerLoadSet(WTIMER0_BASE,TIMER_A,SysCtlClockGet()/2-1);
    TimerEnable(WTIMER0_BASE,TIMER_A);


}


void Config_Switch(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOIntTypeSet(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_FALLING_EDGE);
    GPIOIntRegister(GPIO_PORTA_BASE,&Input_ISR);
    GPIOIntEnable(GPIO_PORTA_BASE,GPIO_INT_PIN_4);
    IntEnable(INT_GPIOA);


}



void engine_turn_1(uint32_t a)
{
    x_1=a;
    TimerDisable(TIMER0_BASE, TIMER_A);
    number_of_pulse_1 = SysCtlClockGet()/1000000*(500+19000*x_1/1800);
    TimerLoadSet(TIMER0_BASE,TIMER_A,number_of_pulse_1);
    TimerEnable(TIMER0_BASE,TIMER_A);

    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,GPIO_PIN_7);
}

void engine_turn_2(uint32_t a)
{
    x_2=a;
    TimerDisable(TIMER1_BASE, TIMER_A);
    number_of_pulse_2 = SysCtlClockGet()/1000000*(500+19000*x_2/1800);
    TimerLoadSet(TIMER1_BASE,TIMER_A,number_of_pulse_2);
    TimerEnable(TIMER1_BASE,TIMER_A);

    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,GPIO_PIN_6);
}
void engine_turn_3(uint32_t a)
{
    x_3=a;
    TimerDisable(TIMER2_BASE, TIMER_A);
    number_of_pulse_3 = SysCtlClockGet()/1000000*(500+19000*x_3/1800);
    TimerLoadSet(TIMER2_BASE,TIMER_A,number_of_pulse_3);
    TimerEnable(TIMER2_BASE,TIMER_A);

    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_4,GPIO_PIN_4);
}

void engine_turn_4(uint32_t a)
{
    x_4=a;
    TimerDisable(TIMER3_BASE, TIMER_A);
    number_of_pulse_4 = SysCtlClockGet()/1000000*(500+19000*x_4/1800);
    TimerLoadSet(TIMER3_BASE,TIMER_A,number_of_pulse_4);
    TimerEnable(TIMER3_BASE,TIMER_A);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,GPIO_PIN_5);
}
void engine_turn_5(uint32_t a)
{
    x_5=a;

    TimerDisable(TIMER4_BASE, TIMER_A);
    number_of_pulse_5 = SysCtlClockGet()/1000000*(500+19000*x_5/1800);
    TimerLoadSet(TIMER4_BASE,TIMER_A,number_of_pulse_5);
    TimerEnable(TIMER4_BASE,TIMER_A);
    GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4,GPIO_PIN_4);

}
void engine_turn_6(uint32_t a)
{
    x_6=a;
    TimerDisable(TIMER5_BASE, TIMER_A);
    number_of_pulse_6 = SysCtlClockGet()/1000000*(500+19000*x_6/1800);
    TimerLoadSet(TIMER5_BASE,TIMER_A,number_of_pulse_6);
    TimerEnable(TIMER5_BASE,TIMER_A);
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1,GPIO_PIN_1);
}


void turn(double x,double y,double z)
 {
double a_1,a_2,a_3,a_4,r,v,w;
l_2 = 11;
l_3 = 10;
    if (x > 0)
    {
        a_1 = atan(y/x) * 180 / pi;
    }
    else if (x == 0) a_1 = 90;
    else
    {
        a_1 = 180 + atan(y/x) * 180 / pi;
    }
r = sqrt(abs(x)*abs(x) + abs(y)*abs(y));
a_3 = - acos((r*r + z*z - l_2*l_2 - l_3*l_3)/(2*l_2*l_3)) * 180 / pi;
v = l_2 + l_3 * cos(a_3*pi/180);
w = l_3 * sin(a_3*pi/180);
a_2 = atan((z*v -r*w)/(r*v + z*w)) * 180/pi;
a_4 = 90 - a_2 - a_3;
engine_angel_1 = a_1;
engine_angel_2 = 180 - a_2;
engine_angel_3 = 90+a_3;
engine_angel_4 =  a_4;

if(x*x +y*y + z*z <= 21*21)
    {
engine_turn_1(engine_angel_1);
engine_turn_2(engine_angel_2);
engine_turn_3(engine_angel_3);
engine_turn_4(engine_angel_4);
loi = 0;
    }
else loi = 1;

 }


void prepare_to_action(void)
{
    turn(0,17,11.5);
    engine_turn_5(90);
    engine_turn_4(65);
    engine_turn_6(30);



}
void gap(void)
{
  //  code do mo cua canh tay phu hop voi chieu rong qua chuoi
    engine_turn_6(65);

}


void trung_gian()
{
turn(0,13,15);
engine_turn_4(70);

}


void chuan_bi_tha(void)
{
    if(classification == 2)
        {
       if(count == 0)
           {
               turn(-10,0,16);
               engine_turn_4(40);
               engine_turn_5(90);
           }
       if(count == 1)
           {
               turn(-10,0,13);
               engine_turn_4(115);
               engine_turn_5(90);
           }
       if(count == 2)
           {
               turn(-8,8,13);
               engine_turn_5(45);
           }
       if(count == 3)
           {
               turn(-16,5,12.5);
               engine_turn_5(45);
           }
       count = count + 1;
       if(count == 4)   count = 0;

        }
}

void tha(void)
{
    engine_turn_6(35);
}

void string_handle(char str[])
{
    char *p = strtok(str,".");
    int i=0;
    char str1[5][5];
    while(p!= '\0')
    {
        strcpy(str1[i],p);
        i++;
        p = strtok('\0',".");
    }
    x_axis = atoi(str1[0]);
    y_axis = atoi(str1[1]);
    long_size = atoi(str1[2]);
    classification = atoi(str1[3]);
}



void UARTGetBuffer(char *pBuff)
{

    static uint16_t i =0;
    char c;
    while(UARTCharsAvail(UART0_BASE))
    {
        c = UARTCharGet(UART0_BASE);
        *(pBuff+i) = c;
        chuoi[i]=c;
        i++;
    }
    if(c=='A')
    {
      chuoi[i-1]=0;
      i = 0;
      strcpy(chuoi_copy,chuoi);
      string_handle(chuoi_copy);
    }
}
void UART_ISR(void)
{
    UARTIntClear(UART0_BASE,UARTIntStatus(UART0_BASE,true));
    UARTGetBuffer(&Buff[0]);
    double distance=0;
        distance = (640-x_axis)/27.3 + 16.5;
        distance_to_robot = distance * 10;
        time_to_robot = distance_to_robot*70/600-4;
         TimerDisable(WTIMER2_BASE, TIMER_A);
         TimerLoadSet(WTIMER2_BASE,TIMER_A,SysCtlClockGet()/10-1);
         TimerEnable(WTIMER2_BASE,TIMER_A);
         start_procees  = 1;



}


void Config_UART(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE,UART_CLOCK_SYSTEM);
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(),115200,UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    UARTIntRegister(UART0_BASE,&UART_ISR);
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE,UART_INT_RX|UART_INT_RT);
}



int main(void)
{
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);   // 40MHZ
	Config_UART();
	Config_Switch();
	Config_Dong_co_1();
    Config_Dong_co_2();
    Config_Dong_co_3();
    Config_Dong_co_4();
    Config_Dong_co_5();
    Config_Dong_co_6();
    Config_Timer_1();
    Config_Timer_2();
    Config_Timer_3();
    Config_Timer_4();
    Config_Timer_5();
    Config_Timer_6();
    Config_Timer_7();
    Config_Timer_8();
	IntMasterEnable();
	prepare_to_action();
	while(1)
	{

	}

}

