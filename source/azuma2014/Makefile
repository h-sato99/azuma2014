# ターゲット実行形式ファイル名
TARGET = azuma2014

# nxtOSEKルートディレクトリ
NXTOSEK_ROOT = ../nxtOSEK

# インクルードパス
USER_INC_PATH= $(NXTOSEK_ROOT)/ecrobot/nxtway_gs_balancer

# ライブラリ
USER_LIB = nxtway_gs_balancer

# Cソースファイル
# 「装置」のソースファイル
DEVICE_PATH = device
DEVICE_SOURCES = $(DEVICE_PATH)/Bluetooth.c $(DEVICE_PATH)/GyroSensor.c $(DEVICE_PATH)/TouchSensor.c $(DEVICE_PATH)/Motor.c $(DEVICE_PATH)/LightSensor.c $(DEVICE_PATH)/SonarSensor.c $(DEVICE_PATH)/LCD.c $(DEVICE_PATH)/Logger.c $(DEVICE_PATH)/Timer.c
# 「要素技術」のソースファイル
TECHNIQUE = technique
TECHNIQUE_SOURCES = $(TECHNIQUE)/Tail.c $(TECHNIQUE)/Wheel.c $(TECHNIQUE)/BalanceControl.c $(TECHNIQUE)/PidControl.c $(TECHNIQUE)/Communication.c $(TECHNIQUE)/Commander.c $(TECHNIQUE)/Distance.c $(TECHNIQUE)/Dash.c
TECHNIQUE_SOURCES_2014 = $(TECHNIQUE)/FrontWheel.c $(TECHNIQUE)/DrivingWheel.c $(TECHNIQUE)/BumpDecision.c $(TECHNIQUE)/TrialDecision.c $(TECHNIQUE)/LineChange.c
# 「競技」のソースファイル
COMPETISION = competision
COMPETISION_SOURCES = $(COMPETISION)/Competision.c $(COMPETISION)/Strategy.c $(COMPETISION)/LineTracer.c $(COMPETISION)/Runner.c $(COMPETISION)/BasicStage.c 
COMPETISION_SOURCES_2014 = $(COMPETISION)/RoboControl.c $(COMPETISION)/Order.c $(COMPETISION)/OrderList.c $(COMPETISION)/Jump.c $(COMPETISION)/Mogul.c $(COMPETISION)/OrderTest.c $(COMPETISION)/Course.c $(COMPETISION)/PendingArea.c $(COMPETISION)/FigureL.c
# 全ソースファイル
TARGET_SOURCES = model_impl.c balancer_param.c $(DEVICE_SOURCES) $(COMPETISION_SOURCES) $(TECHNIQUE_SOURCES) CheckStart.c Calibration.c  $(COMPETISION_SOURCES_2014) $(TECHNIQUE_SOURCES_2014) 

# TOPPERS/ATK1(OSEK)設定ファイル
TOPPERS_OSEK_OIL_SOURCE = ./model_impl.oil

# 下記のマクロは変更しないでください
O_PATH ?= build

include $(NXTOSEK_ROOT)/ecrobot/ecrobot.mak
