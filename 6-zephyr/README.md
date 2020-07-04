# Project init

# pio 
https://docs.platformio.org/en/latest/core/userguide/project/cmd_init.html
```
pio platform install ststm32
platformio project init --board nucleo_f446re --project-option "framework=zephyr" 


pio platform show ststm32
pio platform update 
pio run -t upload
```


# west project
https://docs.zephyrproject.org/2.2.0/guides/west/repo-tool.html
```
./../../common/scripts/setup-zephyr.sh
west build -p auto -b nucleo_f446re app1
west build -p auto -b nucleo_f446re app2
west flash

minicom --device /dev/ttyACM0 --baud 115200
CTRL+A puis Q % pour quitter
```




