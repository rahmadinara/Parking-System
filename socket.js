function initSocket(io, data) {
  io.on("connection", (socket) => {
    socket.emit("update", data);
  });
}

module.exports = initSocket;