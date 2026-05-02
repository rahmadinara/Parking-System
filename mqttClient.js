const mqtt = require("mqtt");
const data = require("./dataStore");

function initMQTT(io) {

  const client = mqtt.connect("", {
    port: 8883,
    username: "",
    password: ""
  });

  client.on("connect", () => {
    console.log("MQTT Connected");
    client.subscribe("parking/#");
  });

  client.on("message", (topic, message) => {

    const val = message.toString();

    if (topic === "parking/slot1") data.slot1 = Number(val);
    if (topic === "parking/slot2") data.slot2 = Number(val);
    if (topic === "parking/free") data.free = Number(val);
    if (topic === "parking/status") data.status = val;

    // kirim ke web realtime
    io.emit("update", data);
  });

  return client;
}

module.exports = initMQTT;
