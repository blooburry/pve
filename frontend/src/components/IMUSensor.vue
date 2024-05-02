<template>
    <div class="container">
        <h2> IMU Sensor </h2>
        <div class="sensor">
            <div class="measurement-label"> Mag </div>
            <div :class="{ 'measurement-value': true, 'highlight': magUpdated }"> {{ mag.x }} </div>
            <div :class="{ 'measurement-value': true, 'highlight': magUpdated }"> {{ mag.y }} </div>
            <div :class="{ 'measurement-value': true, 'highlight': magUpdated }"> {{ mag.z }} </div>
            <div class="measurement-label"> Acc </div>
            <div :class="{ 'measurement-value': true, 'highlight': accUpdated }"> {{ acc.x }} </div>
            <div :class="{ 'measurement-value': true, 'highlight': accUpdated }"> {{ acc.y }} </div>
            <div :class="{ 'measurement-value': true, 'highlight': accUpdated }"> {{ acc.z }} </div>
            <div class="measurement-label"> Gyro </div>
            <div :class="{ 'measurement-value': true, 'highlight': gyroUpdated }"> {{ gyro.x }} </div>
            <div :class="{ 'measurement-value': true, 'highlight': gyroUpdated }"> {{ gyro.y }} </div>
            <div :class="{ 'measurement-value': true, 'highlight': gyroUpdated }"> {{ gyro.z }} </div>
        </div>
    </div>
</template>

<script>
import mqtt from 'mqtt';

export default {
    data() {
        return {
            mag: {
                x: 0,
                y: 0,
                z: 0
            },
            acc: {
                x: 0,
                y: 0,
                z: 0
            },
            gyro: {
                x: 0,
                y: 0,
                z: 0
            },
            magUpdated: false,
            accUpdated: false,
            gyroUpdated: false,
        }
    },
    mounted() {
        const client = mqtt.connect({
          host: 'localhost',
          port: 9001,
          protocol: 'ws',
          clientId: 'Zumo GUI'
        });

        client.on('connect', () => {
          console.log('Connected to MQTT broker');

          // Subscribe to MQTT topics
          client.subscribe('/imu/mag');
          client.subscribe('/imu/acc');
          client.subscribe('/imu/gyro');
        });

        // Handle incoming MQTT messages
        client.on('message', (topic, message) => {

            console.log(`Received message: ${message} on topic: ${topic}`);

            switch (topic) {
                case '/imu/mag':
                this.mag = JSON.parse(message);
                this.magUpdated = true;
                setTimeout(() => {
                    this.magUpdated = false;
                }, 500);
                break;
                case '/imu/acc':
                this.acc = JSON.parse(message);
                this.accUpdated = true;
                setTimeout(() => {
                    this.accUpdated = false;
                }, 500);
                break;
                case '/imu/gyro':
                this.gyro = JSON.parse(message);
                this.gyroUpdated = true;
                setTimeout(() => {
                    this.gyroUpdated = false;
                }, 500);
                break;
            }
        });
    }
}

</script>

<style>
    div.container {
        background-color: #d4e8ff;
        padding: 20px;
    }

    div.sensor {
        background-color: white;
        display: grid;
        grid-template-columns: 40% auto auto auto ;
        gap: 5px;
        padding: 10px;
    }

    div.highlight {
        animation: highlight-animation 0.5s forwards;
    }

    @keyframes highlight-animation {
        0% {
            box-shadow: 0px 0px 5px 5px yellow;
        }

        100% {
            box-shadow: 0px 0px 0px opx yellow;
        }
    }
</style>