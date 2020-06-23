
## getting started
https://docs.zephyrproject.org/latest/getting_started/index.html




https://docs.zephyrproject.org/latest/boards/arm/nucleo_f446re/doc/index.html
```
west build -b nucleo_f446re samples/hello_world
west flash
```


# setup 

```
../../../common/scripts/setup-zephyr.sh
cd zephyrproject/zephyr
west build -p auto -b nucleo_f446re samples/basic/blinky
west flash

```
