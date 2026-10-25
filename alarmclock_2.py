# https://pixabay.com/sound-effects/search/alarm/ 
import playsound3
import time
from time import sleep
import datetime 
import os 

now = datetime.datetime.now()

CLEAR = "\033[2J"
CLEAR_AND_RETURN = "\033[H"


def alarm(hours, minutes, seconds):


    print(CLEAR)
    
    alarm_time = datetime.datetime.combine(now.date(), datetime.time(hours, minutes, seconds))
    seconds_left = (alarm_time - now).total_seconds()
    time_left_ms = datetime.timedelta(seconds=seconds_left)
    time_left = time_left_ms - datetime.timedelta(microseconds=time_left_ms.microseconds)
    print(f"{CLEAR_AND_RETURN}Alarm will sound in: {time_left}")

    sleep(time_left.total_seconds())

    playsound3.playsound("universfield-digital-alarm-clock-151927.mp3")

hours = int(input("Which hour do you want the alarm to go off: "))
minutes = int(input("Which minute do you want the alarm to go off: "))
seconds = int(input("Which second do you want the alarm to go off: "))

alarm(hours, minutes, seconds)
