import paho.mqtt.client as mqtt
import sys

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc, properties):
    print("Connected with result code "+str(rc))

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

def main():
    # Create MQTT client
    client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    client.on_connect = on_connect
    client.on_message = on_message

    # Connect to MQTT broker
    broker_address = "localhost"
    broker_port = 1883
    client.connect(broker_address, broker_port, 60)

    # Start the loop
    client.loop_start()

    # CLI for user input
    while True:
        try:
            topic = input("Enter topic: ")
            message = input("Enter message: ")
            client.publish(topic, message)
            print("Message sent.")
        except KeyboardInterrupt:
            print("Exiting...")
            break

    # Stop the loop
    client.loop_stop()

if __name__ == "__main__":
    main()