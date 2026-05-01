const express = require("express");
const http = require("http");
const socketIo = require("socket.io");

const data = require("./dataStore");
const startMQTT = require("./mqttClient");
const initSocket = require("./socket");

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

// ================= STATIC FILE =================
app.use(express.static("public"));

// ================= INIT SOCKET =================
initSocket(io, data);

// ================= INIT MQTT =================
startMQTT(io);

// ================= START SERVER =================
server.listen(3000, () => {
  console.log("Server running: http://localhost:3000");
});