# Project Systems Engineering: Zumo32U4 robot

Dit is de Git repo voor het HHS PSE. 

## Dependencies

De GUI communiceert met het embedded systeem via MQTT. Hiervoor is een MQTT broker nodig op `localhost:1883`, die websockets accepteert op poort `9001`. Je kunt een lokale MQTT broker installeren van [Eclipse Mosquitto](https://mosquitto.org/download/). 

### Configuratie voor Websockets: Windows

Je kunt de Mosquitto broker configureren voor Websockets door het `mosquitto.conf` bestand te veranderen in `C:\Program Files\mosquitto`. Dit moet erin staan:

```conf
port 1883
listener 9001
protocol websockets
socket_domain ipv4
allow_anonymous true
```

Je kunt hem starten via de Windows CMD:

```cmd
> net start mosquitto
```

### Configuratie voor Websockets: Linux

Voor Linux moet je een `.conf` bestand aanmaken in `/etc/mosquitto/conf.d` (de naam maakt niet uit). Hier moet hetzelfde in staan als bij de Windows configuratie. Je kunt de broker dan starten met 

```bash
$  mosquitto -v -c /etc/mosquitto/conf.d/custom.conf
```

In dit geval heet het configuratiebestand `custom.conf`.

## Embedded

Deze directory bevat de C++ bestanden die op de Zumo32U4 horen te komen. Hij kan met Arduino IDE gecompileerd en geupload worden naar de Zumo bot.

## Frontend

De Zumo GUI webpagina. Hij is gemaakt met HTML/CSS/JS met als JavaScript framework VueJS. Om hem te starten moet je eerst NodeJS hebben, en dan hetvolgende commando invoeren (in de `frontend` directory): 

```bash
$ npm install 
```

Dan kun je het programma starten met 

```bash
$ npm run serve
```

Als het goed is kun je dan met een browser de GUI openen op `http://localhost:8080/`.

## Testing

Een kleine Python testing tool die MQTT berichten kan sturen zodat de frontend kan worden getest zonder dat het daadwerkelijk moet zijn aangesloten op de Zumo robot.

