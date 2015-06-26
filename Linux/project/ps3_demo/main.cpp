 /*
 * main.cpp
 *
 *  Created on: 2011. 1. 4.
 *      Author: robotis
 */

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <libgen.h>

#include "mjpg_streamer.h"
#include "LinuxDARwIn.h"

#include "StatusCheck.h"

#ifdef MX28_1024
#define MOTION_FILE_PATH    ((char *)"../../../Data/motion_1024.bin")
#else
#define MOTION_FILE_PATH    ((char *)"../../../Data/motion_4096.bin")
#endif
#define INI_FILE_PATH       ((char *)"../../../Data/config.ini")

#define M_INI	((char *)"../../../Data/slow-walk.ini")
#define SCRIPT_FILE_PATH    "script.asc"

#define U2D_DEV_NAME0       "/dev/ttyUSB0"
#define U2D_DEV_NAME1       "/dev/ttyUSB1"

LinuxCM730 linux_cm730(U2D_DEV_NAME0);
CM730 cm730(&linux_cm730);
int GetCurrentPosition(CM730 &cm730);
////////////////////////////////////////////
Action::PAGE Page;
Action::STEP Step;
////////////////////////////////////////////
int change_current_dir()
{
    char exepath[1024] = {0};
    int status = 0;
		if(readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
        status = chdir(dirname(exepath));
		return status;
}

int main(int argc, char *argv[])
{
		int trackerSel;    
		change_current_dir();

    minIni* ini = new minIni(INI_FILE_PATH); 
		minIni* ini1 = new minIni(M_INI); 
		StatusCheck::m_ini = ini;
		StatusCheck::m_ini1 = ini1;

    //////////////////// Framework Initialize ////////////////////////////
    if(MotionManager::GetInstance()->Initialize(&cm730) == false)
    {
        linux_cm730.SetPortName(U2D_DEV_NAME1);
        if(MotionManager::GetInstance()->Initialize(&cm730) == false)
        {
            printf("Fail to initialize Motion Manager!\n");
            return 0;
        }
    }

    Walking::GetInstance()->LoadINISettings(ini);
	usleep(100);
	MotionManager::GetInstance()->LoadINISettings(ini);

    MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
    MotionManager::GetInstance()->AddModule((MotionModule*)Head::GetInstance());
    MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());

    LinuxMotionTimer linuxMotionTimer;
	linuxMotionTimer.Initialize(MotionManager::GetInstance());
	linuxMotionTimer.Start();
   /////////////////////////////////////////////////////////////////////


    int firm_ver = 0,retry=0;
    //important but allow a few retries
		while(cm730.ReadByte(JointData::ID_HEAD_PAN, MX28::P_VERSION, &firm_ver, 0)  != CM730::SUCCESS)
    {
        fprintf(stderr, "Can't read firmware version from Dynamixel ID %d!! \n\n", JointData::ID_HEAD_PAN);
        retry++;
				if(retry >=3) exit(1);// if we can't do it after 3 attempts its not going to work.
    }

    if(0 < firm_ver && firm_ver < 27)
    {
        Action::GetInstance()->LoadFile(MOTION_FILE_PATH);
    }
    else
        exit(0);


    Walking::GetInstance()->m_Joint.SetEnableBody(false);
    Head::GetInstance()->m_Joint.SetEnableBody(false);
    Action::GetInstance()->m_Joint.SetEnableBody(true);
//    Action::GetInstance()->m_Joint.SetEnableBody(true, true);
    MotionManager::GetInstance()->Reinitialize();
    
    MotionManager::GetInstance()->SetEnable(true);
              

    if(PS3Controller_Start() == 0)
		{
		printf("PS3 controller not installed.\n");
		}
		
	Action::GetInstance()->Start(15);
	while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	

    while(1)
			{
      		StatusCheck::Check(cm730);

		if(StatusCheck::m_is_started == 0)
        continue;
			}

    return 0;
}

int GetCurrentPosition(CM730 &cm730)
{
	int m=Robot::READY,p,j,pos[31];
	int dMaxAngle1,dMaxAngle2,dMaxAngle3;
	double dAngle;
	int rl[6] = { JointData::ID_R_ANKLE_ROLL,JointData::ID_R_ANKLE_PITCH,JointData::ID_R_KNEE,JointData::ID_R_HIP_PITCH,JointData::ID_R_HIP_ROLL,JointData::ID_R_HIP_YAW };
	int ll[6] = { JointData::ID_L_ANKLE_ROLL,JointData::ID_L_ANKLE_PITCH,JointData::ID_L_KNEE,JointData::ID_L_HIP_PITCH,JointData::ID_L_HIP_ROLL,JointData::ID_L_HIP_YAW };

	for(p=0;p<31;p++) 
		{
		pos[p]	= -1;
		}
	for(p=0; p<6; p++)
		{
		if(cm730.ReadWord(rl[p], MX28::P_PRESENT_POSITION_L, &pos[rl[p]], 0) != CM730::SUCCESS)
			{
			printf("Failed to read position %d",rl[p]);
			}
		if(cm730.ReadWord(ll[p], MX28::P_PRESENT_POSITION_L, &pos[ll[p]], 0) != CM730::SUCCESS)
			{
			printf("Failed to read position %d",ll[p]);
			}
		}
	// compare to a couple poses
	// first sitting - page 48
	Action::GetInstance()->LoadPage(48, &Page);
	j = Page.header.stepnum-1;
	dMaxAngle1 = dMaxAngle2 = dMaxAngle3 = 0;
	for(p=0;p<6;p++)
		{
		dAngle = abs(MX28::Value2Angle(pos[rl[p]]) - MX28::Value2Angle(Page.step[j].position[rl[p]]));
		if(dAngle > dMaxAngle1)
			dMaxAngle1 = dAngle;
		dAngle = abs(MX28::Value2Angle(pos[ll[p]]) - MX28::Value2Angle(Page.step[j].position[ll[p]]));
		if(dAngle > dMaxAngle1)
			dMaxAngle1 = dAngle;
		}				
	// squating - page 15
	Action::GetInstance()->LoadPage(15, &Page);
	j = Page.header.stepnum-1;
	for(int p=0;p<6;p++)
		{
		dAngle = abs(MX28::Value2Angle(pos[rl[p]]) - MX28::Value2Angle(Page.step[j].position[rl[p]]));
		if(dAngle > dMaxAngle2)
			dMaxAngle2 = dAngle;
		dAngle = abs(MX28::Value2Angle(pos[ll[p]]) - MX28::Value2Angle(Page.step[j].position[ll[p]]));
		if(dAngle > dMaxAngle2)
			dMaxAngle2 = dAngle;
		}				
	// walkready - page 9
	Action::GetInstance()->LoadPage(9, &Page);
	j = Page.header.stepnum-1;
	for(int p=0;p<6;p++)
		{
		dAngle = abs(MX28::Value2Angle(pos[rl[p]]) - MX28::Value2Angle(Page.step[j].position[rl[p]]));
		if(dAngle > dMaxAngle3)
			dMaxAngle3 = dAngle;
		dAngle = abs(MX28::Value2Angle(pos[ll[p]]) - MX28::Value2Angle(Page.step[j].position[ll[p]]));
		if(dAngle > dMaxAngle3)
			dMaxAngle3 = dAngle;
		}				
	if(dMaxAngle1<20 && dMaxAngle1<dMaxAngle2 && dMaxAngle1<dMaxAngle3)
		m = Robot::SITTING;
	if(dMaxAngle2<20 && dMaxAngle2<dMaxAngle1 && dMaxAngle2<dMaxAngle3)
		m = Robot::READY;
	if(dMaxAngle3<20 && dMaxAngle3<dMaxAngle1 && dMaxAngle3<dMaxAngle2)
		m = Robot::SOCCER;
	printf("Sitting = %d, Squating = %d, Standing = %d\n",dMaxAngle1,dMaxAngle2,dMaxAngle3);
	printf("Robot is %s\n",m==Robot::READY?"Ready":m==Robot::SOCCER?"Soccer":m==Robot::SITTING?"Sitting":"None");
	return m;
}
