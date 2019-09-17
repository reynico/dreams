# Dreams
Dreams uses temperature, humidity and CO2 concentration to create a Prometheus exporter with consistent data about your environment.

## Shopping list
* [0-5000ppm CO2 sensor](https://www.dfrobot.com/product-1549.html) ($58)
* [DHT-22 temperature and humidity sensor](https://www.dfrobot.com/product-1102.html) ($5.90)
* [FireBeetle ESP32 IoT microcontroller](https://www.dfrobot.com/product-1590.html) ($19)

## Diagram

## Setup
Each [dreams.ino](dreams.ino), [dreams_bedroom.ino](dreams_bedroom.ino) and [dreams_kitchen.ino](dreams_kitchen.ino) belongs to your home exporters. 

### Setup the exporter
* dreams*.ino contains:
  * `host`: The exporter hostname exposed in your router's ARP table 
  * `ip_addr`: The exporter IP address
  * `gw`: The gateway
  * `subnet`: The network subnet
 
Note: Each exporter needs to have a different IP address.
* core.ino contains:
  * `ssid`: The WiFi network name to connect
  * `password`: The WiFi network password to connect

## Prometheus exporter
Once powered up and connected to WiFi, each node serves a single HTML page with a Prometheus-like exporter format:
```
[nico@x220 ~]$ curl 192.168.1.6:9000/metrics
co2_concentration 735.89
temperature_c 20.10
humidity 38.00
```

## Prometheus server configuration
Add to `prometheus.yml`:
```
scrape_configs:
  - job_name: 'dining'
    scrape_interval: 5s
    static_configs:
            - targets: ['192.168.1.6:9000']

  - job_name: 'bedroom'
    scrape_interval: 5s
    static_configs:
            - targets: ['192.168.1.7:9000']

  - job_name: 'kitchen'
    scrape_interval: 5s
    static_configs:
            - targets: ['192.168.1.8:9000']
```

![Grafana Dashboard](https://raw.githubusercontent.com/reynico/dreams/master/grafana.png)