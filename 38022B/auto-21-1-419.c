#pragma config(Sensor, port3,  balanceGyro,    sensorVexIQ_Gyro)
#pragma config(Sensor, port4,  LFcolor,        sensorVexIQ_ColorGrayscale)
#pragma config(Sensor, port8,  RFcolor,        sensorVexIQ_ColorGrayscale)
#pragma config(Sensor, port10, turnGyro,       sensorVexIQ_Gyro)
#pragma config(Sensor, port11, tLED,           sensorVexIQ_LED)
#pragma config(Motor,  motor1,          leftMotor,     tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor2,          xMotor,        tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor6,          rightMotor,    tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
#pragma config(Motor,  motor7,          armMotor,      tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor9,          pickMotor1,    tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor12,         pickMotor2,    tmotorVexIQ, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
/*
Author:
       stefan stefan1992@qq.com
Description:
       for the vex iq competition crossover
*/
static int threshold=130;
static int tgd=0;
static int bgd=0;
static float k=3;
/*void remove()
{
	int x=vexRT[ChC];
	int y=vexRT[ChD];
	int z=vexRT[ChB];

	if(abs(x)>movethreshold&&abs(x)>abs(y))
	{
		motor[xMotor]=x;
	}
	else if(abs(y)>movethreshold&&abs(y)>abs(x)&&abs(z)<movethreshold)
	{
		motor[leftMotor]=y;
		motor[rightMotor]=y;
	}
	else if(abs(y)>movethreshold&&abs(y)>abs(x)&&abs(z)>movethreshold)
	{
		motor[leftMotor]=y+z;
		motor[rightMotor]=y-z;
	}
	else if(abs(z)>movethreshold)
	{
		motor[leftMotor]=z;
		motor[rightMotor]=-z;
	}
	else
	{
		motor[leftMotor]=0;
		motor[rightMotor]=0;
		motor[xMotor]=0;
	}
}



void pick()
{
	motor[pickMotor]=vexRT[BtnRUp]*100-vexRT[BtnRDown]*100;
}

void hang()
{
	motor[larmMotor]=vexRT[BtnLUp]*100-vexRT[BtnLDown]*100;
	motor[rarmMotor]=vexRT[BtnLUp]*100-vexRT[BtnLDown]*100;
}*/

void encoderclear()
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	resetMotorEncoder(xMotor);
	resetMotorEncoder(armMotor);
	resetMotorEncoder(pickMotor1);
	resetMotorEncoder(pickMotor2);
}

void moveforward(int speed)
{
	if(nMotorEncoder(rightMotor)>nMotorEncoder(leftMotor))
	{
		motor[leftMotor]=speed;
		motor[rightMotor]=speed-10;
	}
	if (nMotorEncoder(rightMotor)<nMotorEncoder(leftMotor))
	{
		motor[leftMotor]=speed-10;
		motor[rightMotor]=speed;
	}
	if (nMotorEncoder(rightMotor)==nMotorEncoder(leftMotor))
	{
		motor[leftMotor]=speed;
		motor[rightMotor]=speed;
	}
}

void moveback(int speed1)
{
	if(nMotorEncoder(rightMotor)>nMotorEncoder(leftMotor))
	{
		motor[leftMotor]=speed1;
		motor[rightMotor]=speed1-15;
	}
	else if (nMotorEncoder(rightMotor)<nMotorEncoder(leftMotor))
	{
		motor[leftMotor]=speed1-15;
		motor[rightMotor]=speed1;
	}
	else
	{
		motor[leftMotor]=speed1;
		motor[rightMotor]=speed1;
	}
}

void XcountlineRFcolor(int s,int number )
{
	int lastSeen=1;
	int countValue=0;
	clearTimer(T1);
	while(countValue<number&&time1(T1)<3000)
	{
		motor[xMotor]=s;

		if (SensorValue(RFcolor) < threshold)
		{
			if (lastSeen == 1)
			{
				countValue = countValue + 1;
				lastSeen = 0;
			}
		}
		else
		{
			lastSeen = 1;
		}
	}
}

void XcountlineLFcolor(int s,int number)
{
	int lastSeen=1;
	int countValue=0;
	clearTimer(T1);
	while(countValue<number&&time1(T1)<3000)
	{
		motor[xMotor]=s;

		if (SensorValue(LFcolor) < threshold)
		{
			if (lastSeen == 1)
			{
				countValue = countValue + 1;
				lastSeen = 0;
			}
		}
		else
		{
			lastSeen = 1;
		}
	}
	motor[xMotor]=0;
}

void YcountlineLFcolor(int s,int number)
{
	int lastSeen=1;
	int countValue=0;
	clearTimer(T1);
	while(countValue<number&&time1(T1)<3000)
	{
		motor[leftMotor]=s;
		motor[rightMotor]=s;

		if (SensorValue(LFcolor) < threshold)
		{
			if (lastSeen == 1)
			{
				countValue = countValue + 1;
				lastSeen = 0;
			}
		}
		else
		{
			lastSeen = 1;
		}
	}
	motor[leftMotor]=0;
	motor[rightMotor]=0;

}

void bigarm(int armspeed,int armEncoder)
{
	resetMotorEncoder(armMotor);
	clearTimer(T4);
	while((armEncoder-abs(getMotorEncoder(armMotor)))>0&&time1(T4)<2500)
	{
		motor[armMotor]=armspeed;
	}
	motor[armMotor]=0;
}
void pickarm(int pspeed,int pEncoder)
{
	resetMotorEncoder(pickMotor1);
	resetMotorEncoder(pickMotor2);
	clearTimer(T4);
	while((pEncoder-abs(getMotorEncoder(pickMotor1)))>0&&time1(T4)<3000)
	{
		motor[pickMotor1]=pspeed;
		motor[pickMotor2]=pspeed;
	}
	motor[pickMotor1]=0;
	motor[pickMotor1]=0;
}

void goX(int xspeed,int xEncoder )
{
	resetMotorEncoder(xMotor);
	clearTimer(T3);
	while(xEncoder-abs(getMotorEncoder(xMotor))>0&&time1(T3)<3000)
	{
		motor[xMotor]=xspeed;
	}
	motor[xMotor]=0;
}

void goY(int yspeed,int yEncoder)
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	clearTimer(T2);
	while(yEncoder>abs(getMotorEncoder(leftMotor))&&time1(T2)<3000)
	{
		motor[leftMotor]=yspeed;
		motor[rightMotor]=yspeed;
	}
	motor[leftMotor]=0;
	motor[rightMotor]=0;
}

void goGY(int gspeed,int gEncoder,int k2)
{
	resetMotorEncoder(leftMotor);
	resetMotorEncoder(rightMotor);
	clearTimer(T2);
	tgd=SensorValue(turnGyro);
	while(gEncoder-abs(getMotorEncoder(leftMotor))>0&&time1(T2)<3000)
	{
		motor[leftMotor]=k2*(SensorValue[turnGyro-tgd])+gspeed;
		motor[rightMotor]=k2*(tgd-SensorValue[turnGyro])+gspeed;
	}
	motor[leftMotor]=0;
	motor[rightMotor]=0;
}
void GyroTurn(float tspeed,float tgyro)
{
	tgd=SensorValue(turnGyro);
	clearTimer(T1);
	while(abs(SensorValue(turnGyro)-tgd)<tgyro&&time1(T1)<3000)
	{
		motor[leftMotor]=tspeed;
		motor[rightMotor]=-1*tspeed;
	}
	motor[leftMotor]=0;
	motor[rightMotor]=0;
}
void stopmove()
{
	motor[leftMotor]=0;
	motor[rightMotor]=0;
	motor[xMotor]=0;
}
void putdown()
{
	pickarm(-100,350);
	motor[pickMotor1]=-80;
	motor[pickMotor2]=-80;
	wait1Msec(300);
	setMotorBrakeMode(pickMotor1,motorCoast);
	setMotorBrakeMode(pickMotor2,motorCoast);
	wait1Msec(100);
	setMotorBrakeMode(pickMotor1,motorHold);
	setMotorBrakeMode(pickMotor2,motorHold);
	motor[pickMotor1]=0;
	motor[pickMotor2]=0;

}
void gopick()
{
	moveforward(100);
	wait1Msec(800);
	moveback(-100);
	wait1Msec(200);
	moveforward(100);
	wait1Msec(1300);
	stopmove();
}



void pickupanddown()
{
	setMotorBrakeMode(pickMotor1,motorHold);
	setMotorBrakeMode(pickMotor2,motorHold);
	pickarm(100,350);
	motor[pickMotor1]=100;
	motor[pickMotor2]=100;
	wait1Msec(300);
	putdown();
}
void position()
{
	if(SensorValue(turnGyro)-tgd>0)
	{
		GyroTurn(30,abs(SensorValue(turnGyro)-tgd)-2);
	}
	if(SensorValue(turnGyro)-tgd<0)
	{
		GyroTurn(-30,abs(SensorValue(turnGyro)-tgd)-2);
	}
}

void Xcheck()
{
	clearTimer(T3);
	while(time1(T3)<1500)
	{
		if(SensorValue(RFcolor)-threshold>30)
		{
			motor[rightMotor]=30;
		}
		else
		{
			motor[rightMotor]=0;
		}


		if(SensorValue(LFcolor)-threshold>30)
		{
			motor[leftMotor]=30;
		}
		else
		{
			motor[leftMotor]=0;
		}
	}

}
void climb()
{
	bgd=SensorValue(balanceGyro);
	encoderclear();
	while(abs(nMotorEncoder[leftMotor])<500)
	{
		motor[leftMotor]=k*(SensorValue[turnGyro-tgd])-90;
		motor[rightMotor]=k*(tgd-SensorValue[turnGyro])-90;
	}
	clearTimer(T4);
	while(SensorValue(balanceGyro)-bgd>-3 && time1(T4)<4000)
	{
	motor[leftMotor]=k*(SensorValue[turnGyro-tgd])-90;
	motor[rightMotor]=k*(tgd-SensorValue[turnGyro])-90;
	}
	stopmove();
}

void climbbalance()
{
	bgd=SensorValue(balanceGyro);
	encoderclear();
	while(SensorValue(balanceGyro)-bgd<14)
	{
		moveback(-60);
	}
	stopmove();
	goY(-40,480);
	clearTimer(T1);
	while(time1(T1)<8000)
	{
		if(SensorValue(balanceGyro)-bgd>9)
		{
			goGY(-40,40,2);
			wait1Msec(200);
		}
		else if(SensorValue(balanceGyro)-bgd<-9)
		{
			goGY(40,40,2);
			wait1Msec(200);
		}
		else
		{
			motor[leftMotor]=0;
			motor[rightMotor]=0;
		}
	}
	motor[leftMotor]=0;
	motor[rightMotor]=0;
}

task PUD()
{
	pickupanddown();
}
void auto60()
{
	resetGyro(balanceGyro);
	resetGyro(turnGyro);
	wait1Msec(2000);
	while(1){if(getTouchLEDValue(tLED)==1){break;}}
	motor[xMotor]=30;
	putdown();
	gopick();


	startTask(PUD);
	moveback(-100);
	wait1Msec(3000);
	stopmove();
	bigarm(100,80);
	motor[xMotor]=30;
	YcountlineLFcolor(100,1);
	goY(100,150);
	XcountlineLFcolor(-100,1);
	goX(-100,200);
	XcountlineLFcolor(-100,1);
	goX(-100,200);
	XcountlineLFcolor(-100,1);
	goX(-100,200);
	motor[xMotor]=-100;
	wait1Msec(600);
	motor[xMotor]=-30;

	gopick();
	goY(-100,600);
	tgd=SensorValue(turnGyro);
	pickarm(100,100);
	XcountlineLFcolor(60,1);
	goX(60,200);
	XcountlineLFcolor(60,1);
  goX(-30,40);
	climb();/////////////////////shangqiao
	goY(-100,900);

	position();


	while(SensorValue(RFcolor)<threshold)
	{
		motor[xMotor]=30;
	}
	goX(30,200);
	XcountlineLFcolor(100,1);
	motor[xMotor]=100;
	wait1Msec(1000);
	motor[xMotor]=-100;
	wait1Msec(200);
	motor[xMotor]=100;
	wait1Msec(500);
	tgd=SensorValue(turnGyro);////
	XcountlineLFcolor(-60,1);
	goX(-60,180);
	position();
	goY(-100,400);
	moveback(-50);
	wait1Msec(600);
	goY(50,50);
	bigarm(100,500);
	motor[armMotor]=100;
	wait1Msec(1000);
	motor[armMotor]=0;
	goY(-50,30);
	bigarm(-100,500);
	motor[armMotor]=-100;
	wait1Msec(600);
	motor[armMotor]=0;
	pickupanddown();
	bigarm(100,100);
	pickarm(50,100);
	Xcheck();
	tgd=SensorValue(turnGyro);
	goY(50,200);
	XcountlineLFcolor(-60,1);
	goX(-60,200);
	goY(-100,400);
	moveback(-50);
	wait1Msec(600);
	goY(50,50);
	bigarm(100,500);
	motor[armMotor]=100;
	wait1Msec(1000);
	motor[armMotor]=0;
	goY(-50,30);
	bigarm(-100,400);
	motor[armMotor]=0;
	pickarm(100,200);
	goY(100,500);

	GyroTurn(60,180);
	XcountlineLFcolor(60,1);
	motor[xMotor]=100;
	wait1Msec(1000);
	tgd=SensorValue(turnGyro);
	motor[xMotor]=30;
	moveback(-100);
	wait1Msec(1700);
	goY(100,700);

	XcountlineLFcolor(-60,1);
	goX(-60,300);
	XcountlineLFcolor(-60,1);
	goX(30,20);
	climbbalance();


}

task main()
{
	auto60();
	while(1){}
}