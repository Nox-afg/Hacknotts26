# https://pixabay.com/sound-effects/search/alarm/ 
# https://pixabay.com/sound-effects/search/alarm/ 
import playsound3
import time
import datetime 
import os 

now = datetime.datetime.now()

CLEAR = "\033[2J"
CLEAR_AND_RETURN = "\033[H"


def timer(seconds):
    time_elapsed = 0

    print(CLEAR)
    while time_elapsed < seconds:
        time.sleep(1)
        time_elapsed += 1

        time_left = seconds - time_elapsed # seconds left in total 
        
        hours_left = time_left // 3600
        new_time_left = time_left % 3600
        minutes_left = new_time_left // 60 # modulo division -- the total in minutes rounded down 
        seconds_left = new_time_left % 60 # the remainder from the modulo division -- i.e. the leftover 

        print(f"{CLEAR_AND_RETURN}Alarm will sound in: {hours_left:02d}:{minutes_left:02d}:{seconds_left:02d}")

    playsound3.playsound("universfield-digital-alarm-clock-151927.mp3")

# collect the hour, minute and second of the alarm (FIX: change the wording of the prompt to the user)
hours = int(input("Which hour do you want the alarm to go off: "))
minutes = int(input("Which minute do you want the alarm to go off: "))
seconds = int(input("Which second do you want the alarm to go off: "))


# calculate the number of seconds until that alarm should go 
alarm_time = datetime.datetime.combine(now.date(), datetime.time(hours, minutes, seconds)) # time we want the alarm to go off at
seconds_left = (alarm_time - now).total_seconds() # turn the alarm time into the number of seconds until it goes off

# count down on that number of seconds
timer(seconds_left)
