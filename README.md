# Arduino-attached Sensors (Temperature/Humidity + VTOC/eCO2) + Prometheus

## Introduction

This project shows you how to read out data from arduino sensors and graph them.

It was intended for use with these sensors:

- [Grove - Temperature & Humidity Sensor V2.0](https://wiki.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DH20/)
- [VOC and eCO2 Gas Sensor (SGP30) v1.1](https://wiki.seeedstudio.com/Grove-VOC_and_eCO2_Gas_Sensor-SGP30/)

And these other parts:

- Arduino: [ARD R3 DIP](https://joy-it.net/de/products/ARD_R3DIP)
- [Seeed Base Shield](https://joy-it.net/de/products/ARD_R3DIP)

If your setup differs, you might need to make some adjustments.

## Setup

1. Connect sensors to any `12C` ports on the arduino shield. If you are not using shield, the connections you need to make are documented online, e.g. in some entries listed in <#Sources>.
1. Install and open [Arduino IDE](https://www.arduino.cc/en/software/)
1. Download ZIP of these libraries: [Adafruit\_SGP30](https://github.com/adafruit/Adafruit_SGP30), [Grove\_Temperature\_And\_Humidity\_Sensor](https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor)
1. Paste the contents of [arduino\_code.ino](arduino_code.ino) into the text editor, make sure right board/port is selected and press the upload button. (Test by checking the **Serial Monitor** with baud set to `115200`)
1. Connect the arduino to your raspberry pi (or other desired linux machine)
1. `docker compose up -d --build`
1. open grafana webui (<http://localhost:3000>). username: `admin`, password: `admin`
1. `Connections -> Data sources -> Add new data source -> Prometheus -> Prometheus server URL = http://arduino_prometheus:9090, Scrape interval = 5s -> Save & test`
1. create new dashboard, add panels for: `temperature_c`, `humidity_percent`, `sgp30_tvoc_ppb`, `sgp30_eco2_ppm`, `sgp30_raw_h2`, `sgp30_raw_ethanol` from data source `prometheus`

## Useful Snippets / Debugging

Test USB-connected arduino's serial output:

```bash
stty -F /dev/ttyACM0 115200 raw -echo -echoe -echok
cat /dev/ttyACM0
```

## Sources

- <https://wiki.seeedstudio.com/Grove-VOC_and_eCO2_Gas_Sensor-SGP30/>
- <https://wiki.seeedstudio.com/Grove-Temperature-Humidity-Sensor-DH20/>
