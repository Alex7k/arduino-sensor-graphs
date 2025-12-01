# Arduino-attached Sensors (Temperature/Humidity + VTOC/eCO2) + Prometheus

## Introduction

WIP

## Setup

1. `docker compose up -d --build`
1. open grafana webui (<http://localhost:3000>). username: `admin`, password: `admin`
1. `Connections -> Data sources -> Add new data source -> Prometheus -> Prometheus server URL = http://arduino_prometheus:9090, Scrape interval = 1s -> Save & test`
1. create new dashboard, select prometheus as data source

## Useful Snippets

Test USB-connected arduino's serial output:

```bash
stty -F /dev/ttyACM0 115200 raw -echo -echoe -echok
cat /dev/ttyACM0
```

Start and rebuild images (e.g. if you made a change to `exporter/arduino_exporter.py`):
```
docker compose up -d --build
```

(It might be a different name than `ttyACM0` if you already have other serial devices connected.)

