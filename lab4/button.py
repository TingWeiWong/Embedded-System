import RPi.GPIO as GPIO;
from time import sleep;
GPIO.setmode(GPIO.BCM);
GPIO.setup(26, GPIO.IN, pull_up_down=GPIO.PUD_UP);
GPIO.setup(18, GPIO.OUT);
def my_callback(channel):
    print "falling edge detected on 26"
GPIO.add_event_detect(26, GPIO.FALLING, callback=my_callback, bouncetime=300)
try:
    while(True):
        if (GPIO.input(26)==0):
            GPIO.output(18, False);
            #sleep(1);
        elif (GPIO.input(26)==1):
            GPIO.output(18, True);
            #sleep(1);
except KeyboardInterrupt:
    GPIO.cleanup() # clean up GPIO on CTRL+C exit
GPIO.cleanup() # clean up GPIO on normal exit
