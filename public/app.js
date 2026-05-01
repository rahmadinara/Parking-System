const socket = io();

socket.on("update", (data) => {

  document.getElementById("car1").style.display =
    data.slot1 ? "block" : "none";

  document.getElementById("car2").style.display =
    data.slot2 ? "block" : "none";

  document.getElementById("free").innerText = data.free;

  const status = document.getElementById("status");

  if (data.free == 0) {
    status.innerText = "PARKING FULL";
    status.className = "status full";
  } else {
    status.innerText = "AVAILABLE";
    status.className = "status available";
  }
});